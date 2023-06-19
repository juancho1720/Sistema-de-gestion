#pragma once

#include "Fecha.h"
#include "Venta.h"

class Pago
{
private:
    Fecha fechaPago;
    char dni[12];
    char apellido[30];
    char nombre[30];
    int numeroRecibo;
    int numFactura;
    float importe;
    int formaPago;
    bool activo;
    Venta regVenta;
public:
    bool Cargar();
    void Mostrar();
    Fecha getFechaPago();
    const char* getDni();
    int getNumeroRecibo();
    int getNumFactura();
    void setNumFactura(int nF);
    float getImporte();
    int getFormaPago();
    void setFormaPago(int fP);
    bool getActivo();
    void setActivo(bool a);
};
