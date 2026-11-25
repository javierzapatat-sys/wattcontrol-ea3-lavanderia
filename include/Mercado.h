#ifndef MERCADO_H
#define MERCADO_H

#include "Constantes.h"
#include "Funciones.h"

// Matriz real de precios de bolsa nacional (COP/kWh) de XM: 21 al 27 de septiembre de 2026
// Filas: 0 = Lun 21 ... 6 = Dom 27 | Columnas: 0 = 00:00h ... 23 = 23:00h
const float PRECIOS_XM_SEPT2026[DIAS_SEMANA][HORAS_DIA] = {
    {398, 398, 461, 502, 502, 511, 511, 502, 511, 502, 511, 565, 565, 565, 596, 596, 753, 753, 1093, 1093, 884, 753, 596, 565},
    {415, 415, 421, 499, 499, 538, 538, 510, 499, 499, 538, 573, 538, 573, 661, 712, 1040, 712, 1611, 837, 860, 712, 661, 661},
    {463, 465, 465, 465, 465, 467, 465, 467, 465, 465, 465, 465, 465, 465, 504, 648, 656, 656, 1612, 1273, 940, 656, 648, 580},
    {569, 569, 569, 569, 569, 569, 569, 569, 569, 495, 569, 569, 569, 569, 712, 712, 712, 712, 1601, 1601, 928, 712, 712, 712},
    {526, 526, 526, 526, 526, 537, 537, 642, 537, 537, 537, 642, 537, 970, 970, 970, 970, 970, 1603, 1603, 970, 970, 970, 833},
    {584, 584, 598, 603, 603, 640, 640, 603, 598, 598, 598, 705, 705, 705, 705, 705, 705, 705, 1602, 751, 705, 705, 640, 598},
    {456, 570, 518, 609, 609, 609, 570, 456, 456, 456, 456, 456, 456, 456, 609, 609, 641, 644, 890, 890, 890, 817, 644, 620}
};

class Mercado {
private:
    float precios[DIAS_SEMANA][HORAS_DIA];
    float nivelEmbalses;

public:
    Mercado(float embalsesInicial = 78.0f);

    float precio(int dia, int hora) const;
    float getNivelEmbalses() const;
    void setNivelEmbalses(float nuevoNivel);
    float obtenerHoraMasCaraSemana(int &diaOut, int &horaOut) const;
};

#endif