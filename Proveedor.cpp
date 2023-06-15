#include "Proveedor.h"

void Proveedor::Cargar()
{
    cout << "Razon social: ";
    cargarCadena(razonSocial,30);
    cout << "CUIT: ";
    cargarCadena(cuit,30);
    cout << "Fecha de alta: " << endl;
    fechaAlta.Cargar();
    Persona::Cargar();
    estado = true;
}

void Proveedor::Mostrar()
{

    if(estado == true)
    {
        cout << "Codigo proveedor: " << codigoProveedor << endl;
        cout << "Razon social: " << razonSocial << endl;
        cout << "CUIT: " << cuit << endl;
        cout << "Fecha de alta: ";
        fechaAlta.Mostrar();
        Persona::Mostrar();
    }

}
