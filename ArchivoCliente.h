#pragma once

#include "Cliente.h"

class ArchivoCliente
{
private:
    char nombre[30];
public:
    ArchivoCliente(const char *n);
    Cliente leerRegistro(int pos);
    Cliente leerXDni(char *doc);
    int contarRegistros();
    void escribirRegistro();
    void listarTodos();
    void mostrarXDni();
    void borrarCliente();
    void listarDeudoresXDni();
    void listarDeudores();
    void listarMovimientos();
    void listarMovimientosXDni();
    int buscarDni(const char *d);
    int sobreEscribirRegistro(Cliente reg, int pos);
    void leerRegistro(Cliente *vec, int cantidadRegistrosALeer);
    bool guardar(Cliente *vec, int cantidadRegistrosAEscribir);
    void vaciar();
};
