#include <iostream>
#include <iomanip>
#include "../include/Negocio.h"

using namespace std;


Negocio::Negocio(string nombre, string resp, float potContratada)
    : nombreNegocio(nombre), responsable(resp), potenciaContratada(potContratada),
      numCargas(0), semanaSimulada(false) {
    for (int i = 0; i < MAX_CARGAS; i++) {
        cargas[i] = nullptr;
        diasCumplidos[i] = 0;
    }
    for (int d = 0; d < DIAS_SEMANA; d++) {
        for (int h = 0; h < HORAS_DIA; h++) {
            costos[d][h] = 0.0f;
            costosSinGestor[d][h] = 0.0f;
        }
    }
}

void Negocio::agregarCarga(Carga* c) {
    if (numCargas < MAX_CARGAS && c != nullptr) {
        cargas[numCargas] = c;
        diasCumplidos[numCargas] = 0;
        numCargas++;
    }
}

void Negocio::simularSemanaReal(const Mercado &mercado) {
    medidor.reiniciar();
    for (int i = 0; i < numCargas; i++) {
        diasCumplidos[i] = 0;
    }

    float embalses = mercado.getNivelEmbalses();
    int alertasPotencia = 0;

    cout << "\n============================================================" << endl;
    cout << "  SIMULACION SEMANA REAL XM (21 AL 27 DE SEPTIEMBRE 2026)" << endl;
    cout << "  Negocio: " << nombreNegocio << " | Responsable: " << responsable << endl;
    cout << "  Potencia contratada: " << fixed << setprecision(1) << potenciaContratada
         << " kW | Embalses: " << embalses << "%" << endl;
    cout << "============================================================" << endl;

    for (int d = 0; d < DIAS_SEMANA; d++) {
        for (int i = 0; i < numCargas; i++) {
            cargas[i]->reiniciarHoras();
        }

        for (int h = 0; h < HORAS_DIA; h++) {
            float precioHora = mercado.precio(d, h);
            float potenciaTotalSinGestor = 0.0f;

            // Evaluar reglas base (Reglas 1 a 5) mediante polimorfismo
            for (int i = 0; i < numCargas; i++) {
                potenciaTotalSinGestor += cargas[i]->getPotencia();
                if (cargas[i]->debeEncender(h, precioHora, embalses)) {
                    cargas[i]->encender();
                } else {
                    cargas[i]->apagar();
                }
            }

            // Calcular potencia encendida y verificar Regla 6 (limite contratado)
            float potenciaEncendida = 0.0f;
            for (int i = 0; i < numCargas; i++) {
                if (cargas[i]->estaEncendida()) {
                    potenciaEncendida += cargas[i]->getPotencia();
                }
            }

            while (potenciaEncendida > potenciaContratada) {
                int idxMayorAplazable = -1;
                float maxPotAplazable = -1.0f;

                for (int i = 0; i < numCargas; i++) {
                    if (cargas[i]->estaEncendida() && cargas[i]->esAplazable()) {
                        if (cargas[i]->getPotencia() > maxPotAplazable) {
                            maxPotAplazable = cargas[i]->getPotencia();
                            idxMayorAplazable = i;
                        }
                    }
                }

                if (idxMayorAplazable == -1) {
                    break;
                }

                cargas[idxMayorAplazable]->apagar();
                potenciaEncendida -= maxPotAplazable;
                alertasPotencia++;

                if (alertasPotencia <= 3) {
                    cout << "[ALERTA REGLA 6] " << NOMBRES_DIAS[d] << " " << setw(2) << setfill('0') << h
                         << ":00h -> Potencia excedia " << setfill(' ') << potenciaContratada
                         << " kW. Se apago aplazable mayor: " << cargas[idxMayorAplazable]->getNombre()
                         << " (" << maxPotAplazable << " kW)." << endl;
                }
            }

            if (alertasPotencia > 3 && d == DIAS_SEMANA - 1 && h == HORAS_DIA - 1) {
                cout << "[INFO REGLA 6] Total de eventos de proteccion por potencia contratada en la semana: "
                     << alertasPotencia << " horas." << endl;
            }

            // Calcular y guardar costos en la matriz costos[7][24]
            float costoHoraGestor = 0.0f;
            for (int i = 0; i < numCargas; i++) {
                costoHoraGestor += cargas[i]->costoHora(precioHora);
            }

            costos[d][h] = costoHoraGestor;
            costosSinGestor[d][h] = calcularCosto(potenciaTotalSinGestor, precioHora);
            medidor.registrarConsumo(potenciaEncendida, precioHora);
        }

        // Verificar cumplimiento de horas minimas diarias de cada carga aplazable
        for (int i = 0; i < numCargas; i++) {
            if (cargas[i]->esAplazable()) {
                if (cargas[i]->getHorasUso() >= cargas[i]->getHorasMinimas()) {
                    diasCumplidos[i]++;
                }
            }
        }
    }

    semanaSimulada = true;
    cout << "\n[OK] Simulacion semanal completada exitosamente (168 horas evaluadas)." << endl;
}

void Negocio::mostrarReporteSemanal(const Mercado &mercado) const {
    if (!semanaSimulada) {
        cout << "\n[AVISO] Primero debe ejecutar la opcion 1 (Simular la semana real)." << endl;
        return;
    }

    float costosDiaGestor[DIAS_SEMANA];
    float costosDiaSinGestor[DIAS_SEMANA];

    for (int d = 0; d < DIAS_SEMANA; d++) {
        costosDiaGestor[d] = calcularCosto(costos[d], HORAS_DIA);
        costosDiaSinGestor[d] = calcularCosto(costosSinGestor[d], HORAS_DIA);
    }

    float totalSemanaGestor = costoSemana(costos);
    float totalSemanaSinGestor = costoSemana(costosSinGestor);
    float ahorroSemanal = totalSemanaSinGestor - totalSemanaGestor;
    float porcentajeAhorro = (totalSemanaSinGestor > 0.0f)
                             ? (ahorroSemanal / totalSemanaSinGestor) * 100.0f
                             : 0.0f;
    float ahorroMensual = ahorroSemanal * 4.0f;

    int idxDiaCaro = diaMasCaro(costosDiaGestor);
    int diaPico = 0, horaPico = 0;
    float precioMaxSemana = mercado.obtenerHoraMasCaraSemana(diaPico, horaPico);

    cout << "\n==========================================================================" << endl;
    cout << "  REPORTE SEMANAL WATTCONTROL - " << nombreNegocio << endl;
    cout << "  Responsable: " << responsable << endl;
    cout << "==========================================================================" << endl;
    cout << left << setw(16) << "Dia"
         << right << setw(18) << "Sin Gestor (COP)"
         << right << setw(18) << "Con Gestor (COP)"
         << right << setw(18) << "Ahorro (COP)" << endl;
    cout << "--------------------------------------------------------------------------" << endl;

    cout << fixed << setprecision(2);
    for (int d = 0; d < DIAS_SEMANA; d++) {
        float ahorroDia = costosDiaSinGestor[d] - costosDiaGestor[d];
        cout << left << setw(16) << NOMBRES_DIAS[d]
             << right << setw(18) << costosDiaSinGestor[d]
             << right << setw(18) << costosDiaGestor[d]
             << right << setw(18) << ahorroDia << endl;
    }

    cout << "--------------------------------------------------------------------------" << endl;
    cout << left << setw(16) << "TOTAL SEMANA"
         << right << setw(18) << totalSemanaSinGestor
         << right << setw(18) << totalSemanaGestor
         << right << setw(18) << ahorroSemanal << endl;
    cout << "==========================================================================" << endl;

    cout << "\n--- INDICADORES CLAVE DE LA SEMANA ---" << endl;
    cout << "1. Dia mas caro (con gestor): " << NOMBRES_DIAS[idxDiaCaro]
         << " ($" << costosDiaGestor[idxDiaCaro] << " COP)" << endl;
    cout << "2. Hora mas cara de bolsa XM: " << NOMBRES_DIAS[diaPico]
         << " a las " << setw(2) << setfill('0') << horaPico << ":00h" << setfill(' ')
         << " ($" << precioMaxSemana << " COP/kWh)" << endl;
    cout << "3. Promedio diario con gestor: $" << promedio(costosDiaGestor, DIAS_SEMANA) << " COP/dia" << endl;
    cout << "4. Energia total consumida:    " << medidor.getTotalKWh() << " kWh" << endl;
    cout << "5. Ahorro semanal logrado:     $" << ahorroSemanal << " COP ("
         << porcentajeAhorro << "%)" << endl;
    cout << "6. Proyeccion ahorro mensual:  $" << ahorroMensual << " COP (x 4 semanas)" << endl;

    cout << "\n--- CUMPLIMIENTO DE HORAS MINIMAS (CARGAS APLAZABLES) ---" << endl;
    for (int i = 0; i < numCargas; i++) {
        if (cargas[i]->esAplazable()) {
            cout << "- " << cargas[i]->getNombre()
                 << " (minimo " << cargas[i]->getHorasMinimas() << " h/dia): cumplio "
                 << diasCumplidos[i] << " de " << DIAS_SEMANA << " dias." << endl;
        }
    }
    cout << "==========================================================================" << endl;
}

void Negocio::consultarHoraPuntual(const Mercado &mercado, int dia, int hora) const {
    if (dia < 0 || dia >= DIAS_SEMANA || hora < 0 || hora >= HORAS_DIA) {
        cout << "[ERROR] Dia u hora fuera de rango." << endl;
        return;
    }
    float p = mercado.precio(dia, hora);
    cout << "\nConsulta -> " << NOMBRES_DIAS[dia] << " a las "
         << setw(2) << setfill('0') << hora << ":00h" << setfill(' ')
         << " | Precio XM: $" << fixed << setprecision(2) << p << " COP/kWh";
    if (semanaSimulada) {
        cout << " | Costo simulado Lavanderia: $" << costos[dia][hora] << " COP";
    }
    cout << endl;
}