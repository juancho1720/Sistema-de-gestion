#pragma once

#include "Articulo.h"

class ArchivoBackUp
{
private:
    char nombre[30];
public:
    ArchivoBackUp(const char *n);
    Articulo leerRegistro(int pos);
    int contarRegistros();
    void escribirRegistro(Articulo reg);
    int sobreEscribirRegistro(Articulo reg, int pos);
};

