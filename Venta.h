#ifndef VENTA_H
#define VENTA_H
#include <iostream>
using namespace std;
#include "Fecha.h"
#include "ArchivoArticulos.h"


class Venta
{
private:
    int codigoVenta, codigoCliente, codigoArticulo;
    int cantidad;
    float importe;
    Fecha fechaVenta;
    bool activo;
public:
    //SETTERS
    void setCodigoVenta(const int cV){codigoVenta = cV;}
    void setCodigoCliente(const int cC){codigoCliente = cC;}
    void setCodigoArticulo(const int cA){codigoArticulo = cA;}
    void setCantidad(const int c){cantidad = c;}
    void setImporte(const float _importe){importe=_importe;}
    void setFechaVenta(Fecha f){fechaVenta = f;}
    void setActivo(bool a){activo = a;}
    //GETTERS
    int getCodigoVenta(){return codigoVenta;}
    int getCodigoCliente(){return codigoCliente;}
    int getCodigoArticulo(){return codigoArticulo;}
    int getCantidad(){return cantidad;}
    float getImporte(){return importe;}
    Fecha getFechaVenta(){return fechaVenta;}
    bool getActivo(){return activo;}
    //FUNCIONES
    void Cargar();
    void Mostrar();
};

#endif // VENTA_H
