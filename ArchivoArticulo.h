#pragma once

#include "Articulo.h"

class ArchivoArticulo
{
private:
    char nombre[30];
public:
    ArchivoArticulo(const char *n);
    Articulo leerRegistro(int pos);
    int contarRegistros();
    void escribirRegistro();
    void listarTodos();
    void buscarXCodigo();
    void borrar();
    void consultarStockXCodigo();
    void cargarStock();
    int buscarCodigo(int c);
    int sobreEscribirRegistro(Articulo reg, int pos);
    void cambiarPrecios();
    void aumentarPreciosPorcentual();
    void leerRegistro(Articulo *vec, int cantidadRegistrosALeer);
    bool guardar(Articulo *vec, int cantidadRegistrosAEscribir);
    void vaciar();
};
