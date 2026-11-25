#ifndef MEDIDOR_H
#define MEDIDOR_H

#include "Funciones.h"

class Medidor {
private:
    float totalKWh;
    float costoTotal;

public:
    Medidor() : totalKWh(0.0f), costoTotal(0.0f) {}

    void registrarConsumo(float kw, float precio) {
        totalKWh += kw;
        costoTotal += calcularCosto(kw, precio);
    }

    float getTotalKWh() const { return totalKWh; }
    float getCostoTotal() const { return costoTotal; }

    void reiniciar() {
        totalKWh = 0.0f;
        costoTotal = 0.0f;
    }
};

#endif