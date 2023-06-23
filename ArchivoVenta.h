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
    void escribirRegistro();
    void listarXCliente();
    void listarXMes();
    void listarXClienteXMes();
    void imprimirPorPantalla();
    void anularVenta();
    int buscarFactura(int n);
    int sobreEscribirRegistro(Venta reg, int pos);
    void leerRegistro(Venta *vec, int cantidadRegistrosALeer);
    bool guardar(Venta *vec, int cantidadRegistrosAEscribir);
    void vaciar();
};
