#include <iostream>
#include <string.h>
#include <iomanip>

using namespace std;

#include "Articulo.h"
#include "FuncionesGenerales.h"
#include "ArchivoArticulo.h"

Articulo::Articulo()
{
    stock = 0;
}

bool Articulo::Cargar()
{
    cout << "Descripcion: ";
    cargarCadena(descripcion,29);
    cout << "Codigo de Articulo: ";
    cin >> codigoArticulo;
    if(comprobarArticulosExistentes(codigoArticulo) == false)
    {
        cout << "Cantidad: ";
        cin >> cantidadArticulo;
        setStock(cantidadArticulo);
        cout << "Precio Unitario: ";
        cin >> precioUnitario;

        while (precioUnitario <= 0)
        {
            cout << "El precio debe ser mayor a cero." << endl;
            cout << "Precio Unitario: ";
            cin >> precioUnitario;
        }

        estado = true;

        return false;
    }
    else
    {
        return true;
    }
}

void Articulo::Mostrar()
{
    if (estado == true)
    {
        cout << left;
        cout << setw(20) << descripcion;
        cout << setw(15) << codigoArticulo;
        cout << setw(15) << stock;
        cout << setw(20) << precioUnitario;
        cout << endl;
    }
}

const char* Articulo::getDescripcion()
{
    return descripcion;
}

int Articulo::getCodigoArticulo()
{
    return codigoArticulo;
}

int Articulo::getCantidadArticulo()
{
    return cantidadArticulo;
}

void Articulo::setCantidadArticulo(int cA)
{
    cantidadArticulo = cA;
}

float Articulo::getPrecioUnitario()
{
    return precioUnitario;
}

void Articulo::setPrecioUnitario(float pU)
{
    precioUnitario = pU;
}

int Articulo::getStock()
{
    return stock;
}

void Articulo::setStock(int s)
{
    stock = s;
}

void Articulo::setCodigoArticulo(int c)
{
    codigoArticulo = c;
}

bool Articulo::getEstado()
{
    return estado;
}

void Articulo::setEstado(bool e)
{
    estado = e;
}


