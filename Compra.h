#ifndef COMPRA_H
#define COMPRA_H
#include <iostream>
using namespace std;
#include "Fecha.h"


class Compra
{
private:
    int codigoCompra, codigoProveedor, codigoArticulo;
    int cantidad;
    float importe;
    Fecha fechaCompra;
    bool activo;
public:
    //SETTERS
    void setCodigoCompra(const int cC){codigoCompra = cC;}
    void setCodigoProveedor(const int cP){codigoProveedor = cP;}
    void setCodigoArticulo(const int cA){codigoArticulo = cA;}
    void setCantidad(const int c){cantidad = c;}
    void setFechaCompra(Fecha f){fechaCompra = f;}
    void setImporte(const float _importe){importe=_importe;}
    void setActivo(bool a){activo = a;}
    //GETTERS
    int getCodigoCompra(){return codigoCompra;}
    int getCodigoProveedor(){return codigoProveedor;}
    int getCodigoArticulo(){return codigoArticulo;}
    int getCantidad(){return cantidad;}
    float getImporte(){return importe;}
    Fecha getFechaCompra(){return fechaCompra;}
    bool getActivo(){return activo;}
    //Funciones
    void Cargar();
    void Mostrar();
};

#endif // COMPRA_H
