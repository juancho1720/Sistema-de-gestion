#include <iostream>
#include <string.h>
#include <iomanip>

using namespace std;

#include "DetalleFactura.h"
#include "ArchivoDetalleFactura.h"
#include "ArchivoArticulo.h"

void DetalleFactura::setCodigoArticulo(int cA)
{
    codigoArticulo = cA;
}

void DetalleFactura::setImporte(float i)
{
    importe = i;
}

void DetalleFactura::setNumeroFactura(int nF)
{
    numeroFactura = nF;
}

int DetalleFactura::getCodigoArticulo()
{
    return codigoArticulo;
}

float DetalleFactura::getImporte()
{
    return importe;
}

int DetalleFactura::getNumeroFactura()
{
    return numeroFactura;
}

const char* DetalleFactura::getDescripcion()
{
    return descripcion;
}

void DetalleFactura::setDescripcion(const char* d)
{
    strcpy(descripcion, d);
}

int DetalleFactura::getCantidadArticulo()
{
    return cantidadArticulo;
}

void DetalleFactura::setCantidadArticulo(int cA)
{
    cantidadArticulo = cA;
}

void DetalleFactura::Mostrar()
{
    cout << left;
    cout << setw(10) << codigoArticulo;
    cout << setw(20) << descripcion;
    cout << setw(10) << cantidadArticulo;
    cout << setw(10) << importe;
}
