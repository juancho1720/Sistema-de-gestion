#pragma once

#include "Pago.h"

class ArchivoPago
{
private:
    char nombre[30];
public:
    ArchivoPago(const char *n);
    Pago leerRegistro(int pos);
    int contarRegistros();
    void escribirRegistro(Pago reg);
    int buscarRecibo(int n);
    int sobreEscribirRegistro(Pago reg, int pos);
};
