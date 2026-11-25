#include <iostream>
#include <cctype>
#include "../include/Funciones.h"

using namespace std;

float calcularCosto(float kW, float precio) {
    return kW * precio;
}

float calcularCosto(const float costos[], int n) {
    float suma = 0.0f;
    for (int i = 0; i < n; i++) {
        suma += costos[i];
    }
    return suma;
}

float promedio(const float datos[], int n) {
    if (n <= 0) return 0.0f;
    return calcularCosto(datos, n) / n;
}

float costoSemana(const float matrizCostos[DIAS_SEMANA][HORAS_DIA]) {
    float total = 0.0f;
    for (int d = 0; d < DIAS_SEMANA; d++) {
        total += calcularCosto(matrizCostos[d], HORAS_DIA);
    }
    return total;
}

int diaMasCaro(const float costosDia[DIAS_SEMANA]) {
    int idxMayor = 0;
    for (int d = 1; d < DIAS_SEMANA; d++) {
        if (costosDia[d] > costosDia[idxMayor]) {
            idxMayor = d;
        }
    }
    return idxMayor;
}

float horaMasCara(const float precios[DIAS_SEMANA][HORAS_DIA], int &diaOut, int &horaOut) {
    diaOut = 0;
    horaOut = 0;
    float maxPrecio = precios[0][0];
    for (int d = 0; d < DIAS_SEMANA; d++) {
        for (int h = 0; h < HORAS_DIA; h++) {
            if (precios[d][h] > maxPrecio) {
                maxPrecio = precios[d][h];
                diaOut = d;
                horaOut = h;
            }
        }
    }
    return maxPrecio;
}

string leerTextoValido(const string &etiqueta) {
    string texto;
    bool valido = false;
    do {
        cout << etiqueta;
        getline(cin, texto);

        if (texto.empty()) {
            cout << "[ERROR] El campo no puede estar vacio." << endl;
        } else if (texto.length() < 3 || texto.size() < 3) {
            cout << "[ERROR] Debe tener minimo 3 caracteres." << endl;
        } else if (!isupper(static_cast<unsigned char>(texto.at(0)))) {
            cout << "[ERROR] La primera letra debe ser MAYUSCULA (ej. Lavanderia Central)." << endl;
        } else {
            valido = true;
        }
    } while (!valido);
    return texto;
}