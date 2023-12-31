#pragma once

#include "DetalleFactura.h"
#include "Fecha.h"

class DetalleFactura
{
private:
    int codigoArticulo;
    char descripcion[30];
    int cantidadArticulo;
    float importe;
    int numeroFactura;
    Fecha fechaVenta;
    bool activo;
public:

    bool Cargar(int codigoArticulo, float importe, int nF);
    void setCodigoArticulo(int cA);
    void setImporte(float i);
    void setNumeroFactura(int numeroFactura);
    int getCodigoArticulo();
    float getImporte();
    int getNumeroFactura();
    const char* getDescripcion();
    int getCantidadArticulo();
    void setCantidadArticulo(int cA);
    void setDescripcion(const char* d);
    Fecha getFechaVenta();
    void setFechaVenta(Fecha fV);
    void setActivo(bool a);
    bool getActivo();
    void Mostrar();
};

