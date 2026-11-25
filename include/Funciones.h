#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <string>
#include "Constantes.h"

using namespace std;

// Funcion sobrecargada 1: costo de una hora (kW * precio)
float calcularCosto(float kW, float precio);

// Funcion sobrecargada 2: suma de costos de un arreglo de n elementos
float calcularCosto(const float costos[], int n);

// Funcion propia 1: promedio de valores en un arreglo
float promedio(const float datos[], int n);

// Funcion propia 2: calcula el costo total de la semana desde la matriz [7][24]
float costoSemana(const float matrizCostos[DIAS_SEMANA][HORAS_DIA]);

// Funcion propia 3: encuentra el indice del dia mas caro (0 a 6)
int diaMasCaro(const float costosDia[DIAS_SEMANA]);

// Funcion propia 4: encuentra el dia y hora con el precio de bolsa mas alto
float horaMasCara(const float precios[DIAS_SEMANA][HORAS_DIA], int &diaOut, int &horaOut);

// Funcion propia 5: validacion de texto con empty(), length()/size() y at()
string leerTextoValido(const string &etiqueta);

#endif