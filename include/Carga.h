#ifndef CARGA_H
#define CARGA_H

#include <string>
#include "Constantes.h"
#include "Funciones.h"

using namespace std;

class Carga {
protected:
    string nombre;
    float potenciaKW;
    bool encendida;
    int horasUso;

public:
    Carga(string n, float p) : nombre(n), potenciaKW(p), encendida(false), horasUso(0) {}
    virtual ~Carga() {}

    // Metodo virtual puro para polimorfismo
    virtual bool debeEncender(int hora, float precio, float embalses) = 0;
    virtual bool esAplazable() const = 0;
    virtual int getHorasMinimas() const { return 0; }

    void encender() {
        encendida = true;
        horasUso++;
    }

    void apagar() {
        encendida = false;
    }

    void reiniciarHoras() {
        horasUso = 0;
        encendida = false;
    }

    float costoHora(float precio) const {
        return encendida ? calcularCosto(potenciaKW, precio) : 0.0f;
    }

    string getNombre() const { return nombre; }
    float getPotencia() const { return potenciaKW; }
    bool estaEncendida() const { return encendida; }
    int getHorasUso() const { return horasUso; }
};

class CargaCritica : public Carga {
public:
    CargaCritica(string n, float p) : Carga(n, p) {}

    bool debeEncender(int hora, float precio, float embalses) override {
        (void)hora; (void)precio; (void)embalses;
        return true; // Regla 1: Siempre encendida
    }

    bool esAplazable() const override { return false; }
};

class CargaAplazable : public Carga {
private:
    int horasMinimas;

public:
    CargaAplazable(string n, float p, int hMin) : Carga(n, p), horasMinimas(hMin) {}

    int getHorasMinimas() const override { return horasMinimas; }
    bool esAplazable() const override { return true; }

    bool debeEncender(int hora, float precio, float embalses) override {
        if (embalses < EMBALSES_ALERTA) return false;              // Regla 2
        if (hora >= PICO_INICIO && hora <= PICO_FIN) return false; // Regla 3
        if (precio > PRECIO_CARO) return false;                    // Regla 4
        return true;                                               // Regla 5
    }
};

#endif