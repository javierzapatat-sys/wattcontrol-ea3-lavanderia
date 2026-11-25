#include "../include/Mercado.h"

Mercado::Mercado(float embalsesInicial) : nivelEmbalses(embalsesInicial) {
    for (int d = 0; d < DIAS_SEMANA; d++) {
        for (int h = 0; h < HORAS_DIA; h++) {
            precios[d][h] = PRECIOS_XM_SEPT2026[d][h];
        }
    }
}

float Mercado::precio(int dia, int hora) const {
    if (dia < 0 || dia >= DIAS_SEMANA || hora < 0 || hora >= HORAS_DIA) {
        return 0.0f;
    }
    return precios[dia][hora];
}

float Mercado::getNivelEmbalses() const {
    return nivelEmbalses;
}

void Mercado::setNivelEmbalses(float nuevoNivel) {
    if (nuevoNivel < 0.0f) {
        nivelEmbalses = 0.0f;
    } else if (nuevoNivel > 100.0f) {
        nivelEmbalses = 100.0f;
    } else {
        nivelEmbalses = nuevoNivel;
    }
}

float Mercado::obtenerHoraMasCaraSemana(int &diaOut, int &horaOut) const {
    return horaMasCara(precios, diaOut, horaOut);
}