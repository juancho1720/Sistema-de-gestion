#include <iostream>
#include <string.h>
#include <iomanip>

using namespace std;

#include "FuncionesGenerales.h"
#include "Cliente.h"
#include "ArchivoCliente.h"

bool Cliente::Cargar()
{
    cout << "Apellido: ";
    cargarCadena(apellido,29);
    cout << "Nombre: ";
    cargarCadena(nombre,29);
    cout << "DNI: ";
    cargarCadena(dni,11);
    activo = true;
    if(comprobarClientesExistentes(dni) == false)
    {
        saldoDeudor = 0;
        saldoAcreedor = 0;
        cout << "Monto maximo de Deuda Habilitado: " << endl;
        cin >> montoMaximo;
        while (montoMaximo < 0)
        {
            cout << "El monto no puede ser menor a $0.-" << endl << endl;
            cout << "Ingresar nuevo limite: " << endl;
            cin >> montoMaximo;
        }
        return true;
    }
    else
    {
        system("cls");
        cout << "El cliente ingresado ya existe." << endl;
        system("pause");
        return false;
    }
}

void Cliente::Mostrar()
{
    if (activo == true)
    {
        cout << setw(15) << apellido;
        cout << setw(20) << nombre;
        cout << setw(20) << dni;
        cout << setw(20) << montoMaximo << endl;
    }
}

const char* Cliente::getApellido()
{
    return apellido;
}

const char* Cliente::getNombre()
{
    return nombre;
}

const char* Cliente::getDni()
{
    return dni;
}

void Cliente::setDni(const char *d)
{
    strcpy(dni,d);
}

void Cliente::setApellido(const char *a)
{
    strcpy(apellido,a);
}

bool Cliente::getActivo()
{
    return activo;
}

void Cliente::setActivo(bool a)
{
    activo = a;
}

void Cliente::setSaldoDeudor(float s)
{
    saldoDeudor = s;
}

float Cliente::getSaldoDeudor()
{
    return saldoDeudor;
}

void Cliente::setSaldoAcreedor(float s)
{
    saldoAcreedor = s;
}

float Cliente::getSaldoAcreedor()
{
    return saldoAcreedor;
}
void Cliente::setMontoMaximo(float mM)
{
    montoMaximo = mM;
}

float Cliente::getMontoMaximo()
{
    return montoMaximo;
}

