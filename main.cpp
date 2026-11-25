#include <iostream>
#include <limits>
#include "include/Constantes.h"
#include "include/Funciones.h"
#include "include/Carga.h"
#include "include/Mercado.h"
#include "include/Negocio.h"

using namespace std;

int leerEnteroEnRango(const string &mensaje, int minVal, int maxVal) {
    int valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor && valor >= minVal && valor <= maxVal) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }
        cout << "[ERROR] Ingrese un numero entero entre " << minVal << " y " << maxVal << "." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main() {
    cout << "============================================================" << endl;
    cout << "   WATTCONTROL EA3 - GESTOR INTELIGENTE DE ENERGIA (2026)   " << endl;
    cout << "   Negocio asignado: LAVANDERIA (Digitos 4-5)               " << endl;
    cout << "============================================================" << endl;

    string nombreNegocio = leerTextoValido("Ingrese el nombre del negocio (ej. Lavanderia Central): ");
    string responsable = leerTextoValido("Ingrese el nombre del responsable (ej. Javier Zapata): ");

    // Parametros oficiales de Lavanderia (Anexo Proyecto de Aula):
    // Critica: 0.8 kW | Secadora: 6.0 kW | Lavadora: 4.0 kW | Contratada: 9.0 kW
    CargaCritica iluminacionCaja("Iluminacion y caja", 0.8f);
    CargaAplazable secadora("Secadora industrial", 6.0f, 4);
    CargaAplazable lavadora("Lavadora industrial", 4.0f, 5);

    Mercado mercadoXM(78.0f);
    Negocio lavanderia(nombreNegocio, responsable, POTENCIA_CONTRATADA);

    lavanderia.agregarCarga(&iluminacionCaja);
    lavanderia.agregarCarga(&secadora);
    lavanderia.agregarCarga(&lavadora);

    int opcion = 0;
    do {
        cout << "\n-------------------- MENU WATTCONTROL --------------------" << endl;
        cout << "1. Simular la semana real (21 al 27 de septiembre 2026)" << endl;
        cout << "2. Ver reporte semanal y proyeccion de ahorro mensual" << endl;
        cout << "3. Consultar precio XM y costo de una hora puntual" << endl;
        cout << "4. Cambiar nivel de embalses del sistema (actual: "
             << mercadoXM.getNivelEmbalses() << "%)" << endl;
        cout << "0. Salir" << endl;
        cout << "----------------------------------------------------------" << endl;

        opcion = leerEnteroEnRango("Seleccione una opcion: ", 0, 4);

        switch (opcion) {
            case 1:
                lavanderia.simularSemanaReal(mercadoXM);
                break;
            case 2:
                lavanderia.mostrarReporteSemanal(mercadoXM);
                break;
            case 3: {
                int dia = leerEnteroEnRango("Ingrese el dia (0=Lun, 1=Mar, 2=Mie, 3=Jue, 4=Vie, 5=Sab, 6=Dom): ", 0, 6);
                int hora = leerEnteroEnRango("Ingrese la hora (0 a 23): ", 0, 23);
                lavanderia.consultarHoraPuntual(mercadoXM, dia, hora);
                break;
            }
            case 4: {
                int nuevoEmbalse = leerEnteroEnRango("Ingrese el nuevo porcentaje de embalses (0 a 100): ", 0, 100);
                mercadoXM.setNivelEmbalses(static_cast<float>(nuevoEmbalse));
                cout << "[OK] Nivel de embalses actualizado a " << nuevoEmbalse
                     << "%. Vuelva a ejecutar la opcion 1 para recalcular." << endl;
                break;
            }
            case 0:
                cout << "\nCerrando WattControl. Hasta pronto!" << endl;
                break;
        }
    } while (opcion != 0);

    return 0;
}