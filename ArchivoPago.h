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
    void escribirRegistro();
    void listarXCliente();
    void listarTodosXMes();
    void anular();
    int buscarRecibo(int n);
    int sobreEscribirRegistro(Pago reg, int pos);
    void leerRegistro(Pago *vec, int cantidadRegistrosALeer);
    bool guardar(Pago *vec, int cantidadRegistrosAEscribir);
    void vaciar();
};
