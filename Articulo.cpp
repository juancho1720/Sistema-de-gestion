#include "Articulo.h"



void Articulo::Cargar()
{
    cout << "Codigo: ";
    cin >> codigo;
    cout << "Descripcion: ";
    cargarCadena(descripcion,30);
    cout << "Precio: ";
    cin >> precio;
    estado = true;
}


void Articulo::Mostrar()
{
    if(estado == true)
    {
        cout << "Codigo: " << codigo << endl;
        cout << "Descripcion: " << descripcion << endl;
        cout << "Precio: " << precio << endl;
    }
}

