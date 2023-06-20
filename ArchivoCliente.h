#pragma once

#include "Cliente.h"

class ArchivoCliente
{
private:
    char nombre[30];
public:
    ArchivoCliente(const char *n);
    Cliente leerRegistro(int pos);
    int contarRegistros();
    void escribirRegistro(Cliente reg);
    int buscarDni(const char *d);
    int sobreEscribirRegistro(Cliente reg, int pos);
    void leerRegistro(Cliente *vec, int cantidadRegistrosALeer);
    bool guardar(Cliente *vec, int cantidadRegistrosAEscribir);
    void vaciar();
};
