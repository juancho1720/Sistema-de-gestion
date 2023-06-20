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

        if(strcmp(regCliente.getDni(),dni) == 0)
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
            else
            {
                system("cls");
                cout << "El cliente ingresado ya existe." << endl;
                system("pause");
                return true;
            }
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


float sumarDeuda(const char *dni, float importe)
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

float restarDeuda(const char *dni, float importe)
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


void imputarSaldos()
{
    ArchivoVenta auxArchivoVenta("venta.dat");
    Venta regVenta;
    int cantVentas = auxArchivoVenta.contarRegistros();

    ArchivoCliente auxArchivoCliente("clientes.dat");
    Cliente regCliente;
    int cantClientes = auxArchivoCliente.contarRegistros();

    ArchivoPago auxArchivoPago("pagos.dat");
    Pago regPago;
    int cantPagos = auxArchivoPago.contarRegistros();

    float saldo = regCliente.getSaldoDeudor();

    for (int i=0; i<cantVentas; i++)
    {
        regVenta = auxArchivoVenta.leerRegistro(i);

        for (int j=0; j< cantClientes; j++)
        {
            regCliente = auxArchivoCliente.leerRegistro(j);

            if (!regVenta.getPaga() && regVenta.getSaldo() == regCliente.getSaldoDeudor())
            {
                regVenta.setPaga(true);
                regVenta.setSaldo(0);
                restarDeuda(regVenta.getDni(), saldo);
                auxArchivoVenta.sobreEscribirRegistro(regVenta, i);
            }
        }

        for (int i=0; i<cantPagos; i++)
        {
            regPago = auxArchivoPago.leerRegistro(i);

            if (!regPago.getActivo() && regVenta.getSaldo() == 0)
            {
                regVenta.setPaga(true);
                restarDeuda(regVenta.getDni(), saldo);
                auxArchivoVenta.sobreEscribirRegistro(regVenta, i);
            }
        }

    }
}

