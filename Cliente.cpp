#include "Cliente.h"

void Cliente::Cargar()
{
    cout << "Nombre: ";
    cargarCadena(nombre,30);
    cout << "Apellido: ";
    cargarCadena(apellido,30);
    cout << "DNI: ";
    cargarCadena(dni,30);
    cout << "Fecha de alta: " << endl;
    fechaAlta.Cargar();
    Persona::Cargar();
    estado = true;
}

void Cliente::Mostrar()
{
    if(estado == true)
    {
        cout << "Codigo cliente: " << codigoCliente << endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Apellido: " << apellido << endl;
        cout << "DNI: " << dni << endl;
        cout << "Fecha de alta: ";
        fechaAlta.Mostrar();
        Persona::Mostrar();
    }
}
