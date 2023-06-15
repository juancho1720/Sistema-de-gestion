#include "Persona.h"

void Persona::Cargar()
{
    cout << "Domicilio: ";
    cargarCadena(domicilio,30);
    cout << "Telefono: ";
    cargarCadena(telefono,30);
}

void Persona::Mostrar()
{
    cout << "Domicilio: " << domicilio << endl;
    cout << "Telefono: " << telefono << endl;
}
