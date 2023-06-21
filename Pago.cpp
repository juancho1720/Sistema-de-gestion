#include <iostream>
#include <string.h>
#include <iomanip>

using namespace std;

#include "Pago.h"
#include "FuncionesGenerales.h"
#include "ArchivoCliente.h"
#include "ArchivoPago.h"
#include "ArchivoVenta.h"

bool Pago::Cargar()
{
    int op;
    fechaPago.Cargar();
    cout << "DNI cliente: ";
    cargarCadena(dni,11);
    strcpy(nombre, buscarNombre(dni));
    strcpy(apellido, buscarApellido(dni));
    if (comprobarClientesExistentes(dni) == true)
    {
        cout << "Importe Cobrado: ";
        cin >> importe;
        while (importe <= 0)
        {
            cout << "La cantidad debe ser mayor a cero." <<endl;
            cout << "Importe Cobrado: ";
            cin >> importe;
            system("cls");
        }
        cout << "Forma de Pago:" << endl;
        cout << "1- Efvo." << endl;
        cout << "2- Tarjeta." << endl;
        cout << "3- Banco." << endl;
        cin >> formaPago;
        numeroRecibo = generarNumeroRecibo();
        do
        {
            cout << "1- Imputar pago a factura." << endl;
            cout << "2- Imputar pago de manera automatica." << endl;
            cin >> op;
        }
        while(op != 1 && op != 2);
        switch(op)
        {
        case 1:
            system("cls");
            cout << "Ingrese numero de factura a cancelar:" << endl;
            cin >> numFactura;
            setNumFactura(numFactura);
            if (cancelarFactura(dni, numFactura, importe))
            {
                activo = true;
                return true;
            }
            if (!cancelarFactura(dni, numFactura, importe))
            {
                return false;
            }
            break;
        case 2:
            system("cls");
            numFactura = imputarRecibos(dni, importe);
            activo = true;
            return true;
            break;
        }
    }
    else
    {
        system("cls");
        cout << "No se cargo el recibo." << endl;
        system("pause");
        return false;
    }
    return false;
    system("cls");
}

void Pago::Mostrar()
{
    cout << left;
    cout << setw(20) << numeroRecibo;
    cout << setw(20) << dni;
    cout << setw(10) << importe;
    if (numFactura == 0)
    {
        cout << setw(20) << "Anticipo";
    }
    else
    {
        cout << setw(20) << numFactura;
    }
    switch(formaPago)
    {
    case 1:
        cout << setw(15) << "Efvo";
        break;
    case 2:
        cout << setw(15) << "Tarjeta";
        break;
    case 3:
        cout << setw(15) << "Banco";
        break;
    }
    fechaPago.Mostrar();
    cout << endl;
}

Fecha Pago::getFechaPago()
{
    return fechaPago;
}

const char* Pago::getNombre()
{
    return nombre;
}

const char* Pago::getApellido()
{
    return apellido;
}

const char* Pago::getDni()
{
    return dni;
}

int Pago::getNumeroRecibo()
{
    return numeroRecibo;
}

int Pago::getNumFactura()
{
    return numFactura;
}

void Pago::setNumFactura(int nF)
{
    numFactura = nF;
}

float Pago::getImporte()
{
    return importe;
}

int Pago::getFormaPago()
{
    return formaPago;
}

void Pago::setFormaPago(int fP)
{
    formaPago = fP;
}

bool Pago::getActivo()
{
    return activo;
}

void Pago::setActivo(bool a)
{
    activo = a;
}

int Pago::generarNumeroRecibo()
{
    ArchivoPago auxArchivoPago("pagos.dat");
    int cantPagos = auxArchivoPago.contarRegistros();
    return cantPagos+1;
}

bool Pago::cancelarFactura(const char *dni, int numFactura, float importe)
{
    ArchivoVenta auxArchivoVenta("ventas.dat");
    Venta regVenta;
    int cantVentas = auxArchivoVenta.contarRegistros();

    for (int i=0; i< cantVentas; i++)
    {
        regVenta = auxArchivoVenta.leerRegistro(i);

        if ( strcmp(regVenta.getDni(), dni) == 0 )
        {
            if (regVenta.getNumeroFactura() == numFactura)
            {
                if (regVenta.getPaga())
                {
                    cout << "La factura ingresada esta paga." << endl;
                    return false;
                }
                else
                {
                    if (regVenta.getImporte() == importe)
                    {
                        regVenta.setPaga(true);
                        regVenta.setSaldo(0);
                        restarDeuda(regVenta.getDni(), importe);
                        auxArchivoVenta.sobreEscribirRegistro(regVenta, i);
                        return true;
                    }
                    else
                    {
                        cout << "El importe ingresado no coincide con el importe de la factura." << endl;
                        return false;
                    }
                }
            }
        }
    }
    cout << "No existe ese numero de factura para el cliente seleccionado." << endl;
    system("pause");
    return false;
}

int Pago::imputarRecibos(const char *dni, float importe)
{
    ArchivoVenta auxArchivoVenta("ventas.dat");
    Venta regVenta;
    int cantVentas = auxArchivoVenta.contarRegistros();

    ArchivoPago auxArchivoPago("pagos.dat");

    for (int i=0; i<cantVentas; i++)
    {
        regVenta = auxArchivoVenta.leerRegistro(i);

        if (strcmp(regVenta.getDni(), dni) == 0)
        {
            if(!regVenta.getPaga() && regVenta.getSaldo() == importe)
            {
                regVenta.setPaga(true);
                regVenta.setSaldo(0);
                restarDeuda(regVenta.getDni(), importe);
                auxArchivoVenta.sobreEscribirRegistro(regVenta, i);
                return regVenta.getNumeroFactura();
            }
            if(!regVenta.getPaga() && regVenta.getSaldo() > importe)
            {
                regVenta.setSaldo(regVenta.getSaldo() - importe);
                restarDeuda(regVenta.getDni(), importe);
                auxArchivoVenta.sobreEscribirRegistro(regVenta, i);
                return regVenta.getNumeroFactura();
            }
            if(!regVenta.getPaga() && regVenta.getSaldo() < importe)
            {
                regVenta.setPaga(true);
                regVenta.setSaldo(0);
                restarDeuda(regVenta.getDni(), importe);
                auxArchivoVenta.sobreEscribirRegistro(regVenta, i);
                return regVenta.getNumeroFactura();
            }
            if(!regVenta.getPaga() && regVenta.getSaldo() == importe)
            {
                regVenta.setPaga(true);
                auxArchivoVenta.sobreEscribirRegistro(regVenta, i);
            }
        }
    }
    return false;
}
