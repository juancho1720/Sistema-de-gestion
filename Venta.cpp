#include <iostream>
#include <string.h>
#include <iomanip>

using namespace std;

#include "Venta.h"
#include "FuncionesGenerales.h"

bool Venta::Cargar()
{
    fechaVenta.Cargar();
    cout << "DNI cliente: ";
    cargarCadena(dni,11);
    if (comprobarClientesExistentes(dni) == true)
    {
        cout << "Deuda actual del cliente: $" << consultarDeudaCliente(dni) << endl;
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
                strcpy(nombre, buscarNombre(dni));
                strcpy(apellido, buscarApellido(dni));
                numeroFactura = generarNumeroFactura();
                importe = calcularImporteFactura(codigoArticulo, cantidadVendida);

                if (!comprobarDeuda(dni, importe))
                {
                    cout << "El cliente supera el monto habilitado de deuda en su cuenta corriente." << endl;
                    system("pause");
                    return false;
                }
                saldo = importe;
                sumarDeuda(dni, importe);
                paga = false;
                return true;
            }
            else
            {
                system("cls");
                cout << "No hay stock suficiente para realizar esta venta." << endl;
                system("pause");
                return false;
            }
        }
        else
        {
            system("cls");
            cout << "No existen articulos con ese codigo." << endl;
            system("pause");
            return false;
        }
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
    if(paga)
    {
        cout << setw(15) << "Paga";
    }
    if(!paga)
    {
        cout << setw(15) << "Pendiente";
    }
    cout << setw(10) << saldo;
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

void Venta::setDescripcionArticulo(const char *dA)
{
    strcpy(descripcionArticulo, dA);
}
