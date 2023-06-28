#include <iostream>
#include <string.h>
#include <iomanip>

using namespace std;

#include "Venta.h"
#include "FuncionesGenerales.h"
#include "ArchivoVenta.h"
#include "ArchivoArticulo.h"
#include "ArchivoCliente.h"
#include "DetalleFactura.h"
#include "ArchivoDetalleFactura.h"

bool Venta::Cargar()
{
    char op;

    bool sinNumero = true;
    ArchivoCliente auxArchivoCliente("clientes.dat");
    ArchivoDetalleFactura auxArchivoDetalleFactura("detalleFacturas.dat");
    DetalleFactura regDetalleFactura;

    fechaVenta.Cargar();
    cout << "DNI cliente: ";
    cargarCadena(dni,11);
    importe = 0;
    regCliente = auxArchivoCliente.leerXDni(dni);

    if (comprobarClientesExistentes(dni) == true)
    {
        cout << "Deuda actual del cliente: $" << regCliente.getSaldoDeudor() - regCliente.getSaldoAcreedor() << endl;

        do
        {
            cout << "Codigo de Producto: ";
            cin >> codigoArticulo;

            if (comprobarArticulosExistentes(codigoArticulo) == true)
            {
                setDescripcionArticulo(buscarDescripcion(codigoArticulo));
                cout << "Cantidad: ";
                cin >> cantidadVendida;
                while (cantidadVendida <= 0)
                {
                    cout << "La cantidad debe ser mayor a cero." <<endl;
                    system("pause");
                    system("cls");
                    cout << "Cantidad: ";
                    cin >> cantidadVendida;
                }

                if (restarStock(codigoArticulo, cantidadVendida) >= 0)
                {

                    importe += calcularImporteFactura(codigoArticulo, cantidadVendida);

                    if (sinNumero)
                    {
                        numeroFactura = generarNumeroFactura();
                        numeroRecibo = 0;
                        sinNumero = false;
                    }

                    regDetalleFactura.setCodigoArticulo(codigoArticulo);
                    regDetalleFactura.setDescripcion(buscarDescripcion(codigoArticulo));
                    regDetalleFactura.setCantidadArticulo(cantidadVendida);
                    regDetalleFactura.setImporte(calcularImporteFactura(codigoArticulo, cantidadVendida));
                    regDetalleFactura.setNumeroFactura(numeroFactura);
                    regDetalleFactura.setActivo(true);

                    auxArchivoDetalleFactura.escribirRegistro(regDetalleFactura);

                    sumarSaldoDeudor(dni, calcularImporteFactura(codigoArticulo, cantidadVendida));

                    if (!comprobarDeuda(dni, importe))
                    {
                        sumarSaldoDeudor(dni, (importe*-1) );

                        sumarStock(numeroFactura);

                        system("cls");
                        cout << "El cliente supera el monto habilitado de deuda en su cuenta corriente." << endl;
                        system("pause");
                        return false;
                    }

                }
                else
                {
                    sumarStock(numeroFactura);

                    sumarSaldoDeudor(dni, (importe*-1) );

                    system("cls");
                    cout << "No hay stock suficiente para realizar esta venta." << endl;
                    system("pause");
                    return false;
                }
            }
            else
            {
                restarStock( codigoArticulo, -(cantidadVendida) );
                system("cls");
                cout << "No existen articulos con ese codigo." << endl;
                system("pause");
                return false;
            }

            cout << "Desea cargar otro articulo a la venta??? (S/N)" << endl;
            cin >> op;

        }
        while (op == 's' || op == 's');

        strcpy(nombre, buscarNombre(dni));
        strcpy(apellido, buscarApellido(dni));

        saldo = importe;

        paga = false;

        activa = true;

        return true;

    }
    else
    {
        system("cls");
        cout << "No existen clientes con ese DNI." << endl;
        system("pause");
        return false;
    }
}

void Venta::Mostrar()
{
    cout << left;
    cout << setw(10) << codigoArticulo;
    cout << setw(20) << descripcionArticulo;
    cout << setw(10) << cantidadVendida;
    cout << setw(20) << numeroFactura;
    cout << setw(10) << importe;
    if(activa)
    {
        if(paga)
        {
            cout << setw(15) << "Paga";
        }
        if(!paga)
        {
            cout << setw(15) << "Pendiente";
        }
        if (saldo != 0 )
        {
            cout << setw(10) << saldo;
        }
    }
    else
    {
        cout << setw(15) << "Anulada";
    }

    fechaVenta.Mostrar();

    cout << endl;
}

Fecha Venta::getFechaVenta()
{
    return fechaVenta;
}

const char* Venta::getDni()
{
    return dni;
}

const char *Venta::getApellido()
{
    return apellido;
}

const char *Venta::getNombre()
{
    return nombre;
}

int Venta::getNumeroFactura()
{
    return numeroFactura;
}

int Venta::getNumeroRecibo()
{
    return numeroRecibo;
}

void Venta::setNumeroRecibo(int nR)
{
    numeroRecibo = nR;
}

int Venta::getCodigoArticulo()
{
    return codigoArticulo;
}

const char *Venta::getDescripcionArticulo()
{
    return descripcionArticulo;
}

int Venta::getCatidadVendida()
{
    return cantidadVendida;
}

float Venta::getImporte()
{
    return importe;
}

void Venta::setSaldo(float s)
{
    saldo = s;
}

float Venta::getSaldo()
{
    return saldo;
}

bool Venta::getPaga()
{
    return paga;
}

void Venta::setPaga(bool p)
{
    paga = p;
}

bool Venta::getActiva()
{
    return activa;
}

void Venta::setActiva(bool a)
{
    activa = a;
}

void Venta::setDescripcionArticulo(const char *dA)
{
    strcpy(descripcionArticulo, dA);
}

int Venta::generarNumeroFactura()
{
    ArchivoVenta auxArchivoVenta("ventas.dat");
    int cantVentas = auxArchivoVenta.contarRegistros();
    return cantVentas+1;
}

float Venta::consultarDeudaCliente(const char *dni)
{
    float saldo = 0;

    ArchivoVenta auxArchivoVenta("ventas.dat");
    Venta regVenta;
    int cantVentas = auxArchivoVenta.contarRegistros();

    ArchivoCliente auxArchivoCliente("clientes.dat");

    for (int i=0; i< cantVentas; i++)
    {
        regVenta = auxArchivoVenta.leerRegistro(i);

        if ( strcmp(dni, regVenta.getDni()) == 0 && !regVenta.getPaga())
        {
            saldo += regVenta.getSaldo();
        }
    }

    return saldo;
}

const char* Venta::buscarDescripcion(int codigoArticulo)
{
    ArchivoArticulo auxArchivoArticulo("articulos.dat");
    Articulo regArticulo;
    int cantArticulos = auxArchivoArticulo.contarRegistros();

    for(int i=0; i<cantArticulos; i++)
    {
        regArticulo = auxArchivoArticulo.leerRegistro(i);

        if(codigoArticulo == regArticulo.getCodigoArticulo())
        {
            return regArticulo.getDescripcion();
        }
    }
    return "Error";
}

int Venta::restarStock(int codigoArticulo, int cantidadVendida)
{
    ArchivoArticulo auxArchivoArticulo("articulos.dat");
    Articulo regArticulo;
    int cantArticulos = auxArchivoArticulo.contarRegistros();

    int stock;

    for (int i=0; i< cantArticulos; i++)
    {
        regArticulo = auxArchivoArticulo.leerRegistro(i);

        if (regArticulo.getCodigoArticulo() == codigoArticulo)
        {
            stock = regArticulo.getStock() - cantidadVendida;

            if (stock >= 0)
            {
                regArticulo.setStock(stock);
                auxArchivoArticulo.sobreEscribirRegistro(regArticulo, i);
            }
        }
    }
    return stock;
}

void Venta::sumarStock(int nF)
{
    ArchivoArticulo auxArchivoArticulo("articulos.dat");
    Articulo regArticulo;
    int cantArticulos = auxArchivoArticulo.contarRegistros();

    ArchivoDetalleFactura auxAchivoDetalleFactura("detalleFacturas.dat");
    DetalleFactura regDetalleFactura;
    int cantDetalles = auxAchivoDetalleFactura.contarRegistros();

    for (int j=0; j<cantArticulos; j++)
    {
        regArticulo = auxArchivoArticulo.leerRegistro(j);

        for (int i=0; i< cantDetalles; i++)
        {
            regDetalleFactura = auxAchivoDetalleFactura.leerRegistro(i);

            if ( regDetalleFactura.getNumeroFactura() == nF && regDetalleFactura.getCodigoArticulo() == regArticulo.getCodigoArticulo() )
            {
                regArticulo.setStock( regArticulo.getStock() + regDetalleFactura.getCantidadArticulo() );
                auxArchivoArticulo.sobreEscribirRegistro(regArticulo, j);

                regDetalleFactura.setNumeroFactura(0);
                auxAchivoDetalleFactura.sobreEscribirRegistro(regDetalleFactura, i);
            }
        }

    }
}

float Venta::calcularImporteFactura(int codA, int cantV)
{
    ArchivoArticulo auxArchivoArticulo("articulos.dat");
    Articulo regArticulo;
    int cantArticulos = auxArchivoArticulo.contarRegistros();

    for(int i=0; i<cantArticulos; i++)
    {
        regArticulo = auxArchivoArticulo.leerRegistro(i);

        if(regArticulo.getCodigoArticulo() == codA)
        {
            return regArticulo.getPrecioUnitario() * cantV;
        }
    }
    return -1;
}

bool Venta::comprobarDeuda(const char *dni, float importe)
{
    ArchivoCliente auxArchivoCliente("clientes.dat");
    Cliente regCliente;

    int pos = auxArchivoCliente.buscarDni(dni);
    regCliente = auxArchivoCliente.leerRegistro(pos);

    if (regCliente.getMontoMaximo() < consultarDeudaCliente(dni) + importe)
    {
        return false;
    }
    return true;

}
