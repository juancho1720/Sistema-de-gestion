#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

#include "ArchivoVenta.h"
#include "ArchivoArticulo.h"
#include "ArchivoCliente.h"
#include "ArchivoPago.h"

void cargarCadena(char *pal, int tam)
{
    int i;
    fflush(stdin);
    for(i=0; i<tam; i++)
    {
        pal[i]=cin.get();
        if(pal[i]=='\n') break;
    }
    pal[i]='\0';
    fflush(stdin);
}

const char *buscarNombre(const char *d)
{
    ArchivoCliente auxArchivoCliente("clientes.dat");
    Cliente regCliente;
    int cantClientes =  auxArchivoCliente.contarRegistros();

    for (int i=0; i<cantClientes; i++)
    {
        regCliente = auxArchivoCliente.leerRegistro(i);

        if ( strcmp(regCliente.getDni(),d) == 0)
        {
            return regCliente.getNombre();
        }
    }
    return "Error";
}

const char *buscarApellido(const char *d)
{
    ArchivoCliente auxArchivoCliente("clientes.dat");
    Cliente regCliente;
    int cantClientes =  auxArchivoCliente.contarRegistros();

    for (int i=0; i<cantClientes; i++)
    {
        regCliente = auxArchivoCliente.leerRegistro(i);

        if ( strcmp(regCliente.getDni(),d) == 0)
        {
            return regCliente.getApellido();
        }
    }
    return "Error";
}

bool comprobarClientesExistentes(const char *dni)
{
    ArchivoCliente auxArchivoCliente("clientes.dat");
    Cliente regCliente;
    int cantClientes = auxArchivoCliente.contarRegistros();

    char confirmacion;

    for(int i=0; i<cantClientes; i++)
    {
        regCliente = auxArchivoCliente.leerRegistro(i);

        if(strcmp(regCliente.getDni(),dni) == 0 && regCliente.getActivo())
        {
            if(!regCliente.getActivo())
            {
                cout << "El cliente <" << regCliente.getApellido() << ", " << regCliente.getNombre() << "> ha sido borrado." << endl;
                cout << "Desea activarlo nuevamente??? (S/N)" << endl;
                cin >> confirmacion;
                if (confirmacion == 's' || confirmacion == 'S')
                {
                    regCliente.setActivo(true);
                    auxArchivoCliente.sobreEscribirRegistro(regCliente, i);
                    system("cls");
                    cout << "Cliente reactivado con exito." << endl;
                    system("pause");
                    return true;
                }
                else
                {
                    system("cls");
                    cout << "El cliente no se reactivo." << endl;
                    system("pause");
                    return true;
                }
            }
            return true;
        }
    }
    return false;
}

bool comprobarArticulosExistentes(int codigoArticulo)
{
    ArchivoArticulo auxArchivoArticulo("articulos.dat");
    Articulo regArticulo;
    int cantArticulos = auxArchivoArticulo.contarRegistros();

    for(int i=0; i<cantArticulos; i++)
    {
        regArticulo = auxArchivoArticulo.leerRegistro(i);

        if(codigoArticulo == regArticulo.getCodigoArticulo() && regArticulo.getEstado())
        {
            return true;
        }
    }
    return false;
}

float sumarSaldoDeudor(const char *dni, float importe)
{
    ArchivoCliente auxArchivoCliente("clientes.dat");
    Cliente regCliente;
    int cantClientes = auxArchivoCliente.contarRegistros();

    for (int i=0; i< cantClientes; i++)
    {
        regCliente = auxArchivoCliente.leerRegistro(i);

        if ( strcmp(regCliente.getDni(), dni) == 0)
        {
            regCliente.setSaldoDeudor(regCliente.getSaldoDeudor() + importe);

            auxArchivoCliente.sobreEscribirRegistro(regCliente, i);
        }
    }
    return -1;
}

float restarSaldoDeudor(const char *dni, float importe)
{
    ArchivoCliente auxArchivoCliente("clientes.dat");
    Cliente regCliente;
    int cantClientes = auxArchivoCliente.contarRegistros();

    for (int i=0; i< cantClientes; i++)
    {
        regCliente = auxArchivoCliente.leerRegistro(i);

        if ( strcmp(regCliente.getDni(), dni) == 0)
        {
            regCliente.setSaldoDeudor(regCliente.getSaldoDeudor() - importe);
            auxArchivoCliente.sobreEscribirRegistro(regCliente, i);
        }
    }
    return -1;
}

float sumarSaldoAcreedor(const char *dni, float importe)
{
    ArchivoCliente auxArchivoCliente("clientes.dat");
    Cliente regCliente;
    int cantClientes = auxArchivoCliente.contarRegistros();

    for (int i=0; i< cantClientes; i++)
    {
        regCliente = auxArchivoCliente.leerRegistro(i);

        if ( strcmp(regCliente.getDni(), dni) == 0)
        {
            regCliente.setSaldoAcreedor(regCliente.getSaldoDeudor() + importe);
            auxArchivoCliente.sobreEscribirRegistro(regCliente, i);
            cout << "Cambia saldo acreedor a " << regCliente.getSaldoAcreedor() << endl;
            system("pause");
        }
    }
    return -1;
}

float restarSaldoAcreedor(const char *dni, float importe)
{
    ArchivoCliente auxArchivoCliente("clientes.dat");
    Cliente regCliente;
    int cantClientes = auxArchivoCliente.contarRegistros();

    for (int i=0; i< cantClientes; i++)
    {
        regCliente = auxArchivoCliente.leerRegistro(i);

        if ( strcmp(regCliente.getDni(), dni) == 0)
        {
            regCliente.setSaldoAcreedor(regCliente.getSaldoAcreedor() - importe);
            auxArchivoCliente.sobreEscribirRegistro(regCliente, i);
            cout << "Cambia saldo acreedor a " << regCliente.getSaldoAcreedor() << endl;
            system("pause");
        }
    }
    return -1;
}
