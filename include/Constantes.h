#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <string>

using namespace std;

// =========================================================================
// PARAMETROS OFICIALES DEL NEGOCIO: LAVANDERIA INDUSTRIAL (DIGITO 4-5)
// =========================================================================
#define DIAS_SEMANA 7
#define HORAS_DIA 24
#define MAX_CARGAS 5

const float POTENCIA_CONTRATADA = 9.0f;    // kW limite contratado
const float POTENCIA_CRITICA    = 0.8f;    // Iluminacion y caja (0.8 kW)
const float POTENCIA_APLAZ1     = 6.0f;    // Secadora industrial (6.0 kW - mayor potencia)
const float POTENCIA_APLAZ2     = 4.0f;    // Lavadora industrial (4.0 kW)

const int   MIN_HORAS_APLAZ1    = 5;       // Horas minimas diarias Secadora
const int   MIN_HORAS_APLAZ2    = 6;       // Horas minimas diarias Lavadora

const float PRECIO_CARO         = 700.0f;  // COP/kWh umbral caro Lavanderia
const float PRECIO_ESCASEZ      = 1605.0f; // COP/kWh alerta critica de racionamiento (break)
const float EMBALSES_ALERTA     = 40.0f;   // % minimo de embalses antes de alerta hidrica

const int   PICO_INICIO         = 18;      // 6:00 PM
const int   PICO_FIN            = 20;      // 8:00 PM

const string NOMBRES_DIAS[DIAS_SEMANA] = {
    "Lunes 21 Sep", "Martes 22 Sep", "Miercoles 23 Sep",
    "Jueves 24 Sep", "Viernes 25 Sep", "Sabado 26 Sep", "Domingo 27 Sep"
};

#endif