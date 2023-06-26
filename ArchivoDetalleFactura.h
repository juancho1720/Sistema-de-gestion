#pragma once

#include "DetalleFactura.h"

class ArchivoDetalleFactura
{
private:
    char nombre[30];
public:
    ArchivoDetalleFactura(const char *n);
    DetalleFactura leerRegistro(int pos);
    int contarRegistros();
    void escribirRegistro(DetalleFactura reg);
    /*void listarTodos();
    void buscarXCodigo();
    void borrar();
    void consultarStockXCodigo();
    void cargarStock();
    int buscarCodigo(int c);*/
    int sobreEscribirRegistro(DetalleFactura reg, int pos);
    /*void cambiarPrecios();
    void aumentarPreciosPorcentual();*/
    void leerRegistro(DetalleFactura *vec, int cantidadRegistrosALeer);
    /*bool guardar(Articulo *vec, int cantidadRegistrosAEscribir);
    void vaciar();*/
};
