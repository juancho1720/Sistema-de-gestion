#pragma once

#include "Venta.h"

class ArchivoVenta
{
private:
    char nombre[30];
public:
    ArchivoVenta(const char *n);
    Venta leerRegistro(int pos);
    int contarRegistros();
    void escribirRegistro(Venta reg);
    int buscarFactura(int n);
    int sobreEscribirRegistro(Venta reg, int pos);
};
