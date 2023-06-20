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

int generarNumeroFactura()
{
    ArchivoVenta auxArchivoVenta("ventas.dat");
    int cantVentas = auxArchivoVenta.contarRegistros();
    return cantVentas+1;
}

int generarNumeroRecibo()
{
    ArchivoPago auxArchivoPago("pagos.dat");
    int cantPagos = auxArchivoPago.contarRegistros();
    return cantPagos+1;
}

float calcularImporteFactura(int codA, int cantV)
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

int sumarStock(int codigoArticulo, int cantidadArticulo)
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
            stock = regArticulo.getStock() + cantidadArticulo;
            regArticulo.setStock(stock);
            auxArchivoArticulo.sobreEscribirRegistro(regArticulo, i);
        }
    }
    return stock;
}

int restarStock(int codigoArticulo, int cantidadVendida)
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

const char *buscarDescripcion(int codigoArticulo)
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

bool cancelarFactura(const char *dni, int numFactura, float importe)
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

int imputarRecibos(const char *dni, float importe)
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
                //restarDeuda(regVenta.getDni(), saldo);
                auxArchivoVenta.sobreEscribirRegistro(regVenta, i);
            }
        }

    }
}

float consultarDeudaCliente(const char *dni)
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

bool comprobarDeuda(const char *dni, float importe)
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

void ventasMensualesProductos()
{
    int cantArticulo, mes, anio;

    ArchivoVenta auxArchivoVenta("ventas.dat");
    Venta regVenta;
    int cantVentas = auxArchivoVenta.contarRegistros();

    ArchivoArticulo auxArchivoArticulo("articulos.dat");
    Articulo regArticulo;
    int cantArticulos = auxArchivoArticulo.contarRegistros();

    cout << "Mes: ";
    cin >> mes;
    cout << "Anio: ";
    cin >> anio;

    for (int i=0; i<cantArticulos; i++)
    {
        cantArticulo = 0;

        regArticulo = auxArchivoArticulo.leerRegistro(i);

        for (int j=0; j<cantVentas; j++)
        {
            regVenta = auxArchivoVenta.leerRegistro(j);

            if (regArticulo.getCodigoArticulo() == regVenta.getCodigoArticulo() && regVenta.getFechaVenta().getAnio() == anio &&regVenta.getFechaVenta().getMes() == mes)
            {
                cantArticulo += regVenta.getCatidadVendida();
            }
        }

        cout << "Articulo: " << regArticulo.getDescripcion() << ". Unidades vendidas: " << cantArticulo << "." << endl;
    }
    system("pause");
}

void cobrosMensualesTipo()
{
    int cant = 0;
    int mes, anio;

    ArchivoPago auxArchivoPago("pagos.dat");
    Pago regPago;
    int cantPagos = auxArchivoPago.contarRegistros();

    cout << "Mes: ";
    cin >> mes;
    cout << "Anio: ";
    cin >> anio;

    for (int i=0; i<3; i++)
    {
        for (int j=0; j<cantPagos; j++)
        {
            regPago = auxArchivoPago.leerRegistro(j);

            if (regPago.getFormaPago() == i+1 && regPago.getFechaPago().getAnio() == anio &&regPago.getFechaPago().getMes() == mes)
            {
                cant ++;
            }
        }
        switch(i)
        {
        case 0:
            cout << "Efvo - "<< "Cantidad de Cobros: " << cant << "." << endl;
            break;
        case 1:
            cout << "Tarjeta - "<< "Cantidad de Cobros: " << cant << "." << endl;
            break;
        case 2:
            cout << "Banco - "<< "Cantidad de Cobros: " << cant << "." << endl;
            break;
        }
        cant = 0;
    }
    system("pause");
}

void exportarClientes()
{
    ArchivoCliente auxArchivoCliente("clientes.dat");
    Cliente regCliente;
    int cantClientes = auxArchivoCliente.contarRegistros();

    ofstream archivoClientes("clientes.csv", ios::out);
    if (!archivoClientes)
    {
        cout << "No se pudo crear el archivo." << endl;
    }
    else
    {
        for (int i=0; i< cantClientes; i++)
        {
            regCliente = auxArchivoCliente.leerRegistro(i);

            if (i==0)
            {
                archivoClientes << "Nombre" << ";" << "Apellido" <<  ";" << "DNI" <<endl;
            }
            archivoClientes << regCliente.getNombre() << ";" << regCliente.getApellido() << ";" << regCliente.getDni() << endl;
        }
        archivoClientes.close();
        cout << "Archivo creado con exito!!!" << endl;
        cout << cantClientes << " clientes exportados a excel" << endl;
        system("pause");
    }
}

void exportarCtasCtes()
{
    ArchivoVenta auxArchivoVenta("ventas.dat");
    Venta regVenta;
    int cantVentas = auxArchivoVenta.contarRegistros();

    ArchivoPago auxArchivoPago("pagos.dat");
    Pago regPago;
    int cantPagos = auxArchivoPago.contarRegistros();
    char dni[12];

    ofstream archivoctasctes("ctas-ctes.csv", ios::out);
    if (!archivoctasctes)
    {
        cout << "No se pudo crear el archivo." << endl;
        system("pause");
    }
    else
    {
        for (int i=0; i< cantVentas; i++)
        {
            regVenta = auxArchivoVenta.leerRegistro(i);

            if (i==0)
            {
                archivoctasctes << "Fecha" << ";" << "Nombre" << ";" << "Apellido" <<  ";" << "Tipo Comprobante" <<  ";" << "Numero" <<  ";" << "Importe" <<
                ";" << "Estado" << endl;
            }
            archivoctasctes << regVenta.getFechaVenta().getAnio() << "/" << regVenta.getFechaVenta().getMes() << "/" << regVenta.getFechaVenta().getDia() << ";" << regVenta.getNombre() << ";" << regVenta.getApellido() << ";" << "F" << ";" << regVenta.getNumeroFactura() << ";" <<
            regVenta.getImporte() << ";";
            if (regVenta.getPaga())
            {
                archivoctasctes << "PAGA" << endl;
            }
            else
            {
                archivoctasctes << "PENDIENTE" << endl;
            }
        }

        for (int i=0; i< cantPagos; i++)
        {
            regPago = auxArchivoPago.leerRegistro(i);
            strcpy(dni, regPago.getDni());
            archivoctasctes << regPago.getFechaPago().getAnio() << "/" << regPago.getFechaPago().getMes() << "/" << regPago.getFechaPago().getDia() << ";" << regPago.getNombre() << ";" << regPago.getApellido()
            << ";" << "RBO" << ";" << regPago.getNumeroRecibo() << ";" << regPago.getImporte() << ";";
            if (regPago.getActivo())
            {
                archivoctasctes << "IMPUTADO" << endl;
            }
            else
            {
                archivoctasctes << "PENDIENTE" << endl;
            }
        }
        archivoctasctes.close();
        cout << "Archivo creado con exito!!!" << endl;
        system("pause");
    }
}
