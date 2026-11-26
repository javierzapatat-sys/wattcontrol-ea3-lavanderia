#ifndef NEGOCIO_H
#define NEGOCIO_H

#include <string>
#include "Constantes.h"
#include "Funciones.h"
#include "Carga.h"
#include "Medidor.h"
#include "Mercado.h"

using namespace std;


class Negocio {
private:
    string nombreNegocio;
    string responsable;
    float potenciaContratada;
    Carga* cargas[MAX_CARGAS];
    int numCargas;
    Medidor medidor;
    float costos[DIAS_SEMANA][HORAS_DIA];
    float costosSinGestor[DIAS_SEMANA][HORAS_DIA];
    int diasCumplidos[MAX_CARGAS];
    bool semanaSimulada;

public:
    Negocio(string nombre, string resp, float potContratada);

    void agregarCarga(Carga* c);
    void simularSemanaReal(const Mercado &mercado);
    void mostrarReporteSemanal(const Mercado &mercado) const;
    void consultarHoraPuntual(const Mercado &mercado, int dia, int hora) const;
    bool estaSimulada() const { return semanaSimulada; }
};

#endif