#include <iostream>
#include <string>

using namespace std;

// Constantes oficiales del negocio: Lavanderia Industrial (Digito 4-5)
#define DIAS_SEMANA 7
#define HORAS_DIA 24
#define MAX_CARGAS 5

const float POTENCIA_CONTRATADA = 9.0f;    // kW limite contratado
const float POTENCIA_CRITICA    = 0.8f;    // Iluminacion y caja (0.8 kW)
const float POTENCIA_APLAZ1     = 6.0f;    // Secadora industrial (6.0 kW)
const float POTENCIA_APLAZ2     = 4.0f;    // Lavadora industrial (4.0 kW)
const float PRECIO_CARO         = 700.0f;  // COP/kWh umbral caro

int main() {
    cout << "WattControl v3 - Estructura inicial configurada." << endl;
    return 0;
}