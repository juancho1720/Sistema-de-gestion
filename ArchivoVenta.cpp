#include <iostream>
#include <string.h>
#include <iomanip>

using namespace std;

#include "ArchivoVenta.h"
#include "ArchivoCliente.h"
#include "ArchivoArticulo.h"
#include "MenuManager.h"
#include "FuncionesGenerales.h"

ArchivoVenta::ArchivoVenta(const char *n)
{
    strcpy(nombre, n);
}

Venta ArchivoVenta::leerRegistro(int pos)
{
    Venta reg;
    FILE *p = fopen(nombre, "rb");
    if(p == NULL)
    {
        return reg;
    }
    fseek(p, sizeof(Venta)*pos,0);
    fread(&reg, sizeof reg,1, p);
    fclose(p);
    return reg;
}

int ArchivoVenta::contarRegistros()
{
    FILE *p = fopen(nombre, "rb");
    if(p == NULL)
    {
        return -1;
    }
    fseek(p, 0,2);
    int tam = ftell(p);
    fclose(p);
    return tam/sizeof(Venta);
}

void ArchivoVenta::escribirRegistro()
{
    Venta reg;
    FILE *p = fopen("ventas.dat","ab");
    if(p == NULL)
    {
        cout << "Error archivo.";
    }
    if(reg.Cargar() == true)
    {
        fwrite(&reg, sizeof reg, 1, p);
        fclose(p);
        system("cls");
        cout << "Venta agregada exitosamente!!!" << endl;
        system("pause");
    }
}

void ArchivoVenta::listarXCliente()
{
    bool hayVentas = false;
    bool mostrarTitulo;
    char dni[12];
    ArchivoVenta auxArchivoVenta("ventas.dat");
    Venta regVenta;
    cout << "DNI: ";
    cargarCadena(dni, 11);
    system("cls");
    int cantVentas = auxArchivoVenta.contarRegistros();

    for(int i=0; i<cantVentas; i++)
    {
        regVenta = auxArchivoVenta.leerRegistro(i);

        if( strcmp(regVenta.getDni(),dni) == 0)
        {
            hayVentas = true;
            if(mostrarTitulo)
            {
                cout << "Cliente: " << regVenta.getApellido() << ", " << regVenta.getNombre() << endl << endl;
                cout << left;
                cout << setw(10) << "Codigo";
                cout << setw(20) << "Descripcion";
                cout << setw(10) << "Cantidad";
                cout << setw(20) << "Numero de Factura";
                cout << setw(10) << "Importe";
                cout << setw(15) << "Estado";
                if(regVenta.getSaldo() != 0)
                {
                    cout << setw(10) << "Saldo";
                }
                cout << setw(15) << "Fecha Factura" << endl;
                cout << "-------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
                mostrarTitulo = false;
            }
            regVenta.Mostrar();
            cout << "-------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
        }
    }
    if(!hayVentas)
    {
        cout << "No existen ventas para este cliente." << endl;
    }
    mostrarTitulo = true;
    system("pause");
}

void ArchivoVenta::listarXMes()
{
    bool hayVentas = false;
    bool mostrarTitulo;
    float importeTotal = 0;
    int mes, anio;
    ArchivoVenta auxArchivoVenta("ventas.dat");
    Venta regVenta;
    int cantVentas = auxArchivoVenta.contarRegistros();
    ArchivoCliente auxArchivoCliente("clientes.dat");
    Cliente regCliente;
    int cantClientes = auxArchivoCliente.contarRegistros();
    cout << "Mes: ";
    cin >> mes;
    cout << "Anio: ";
    cin >> anio;
    system("cls");

    for(int i=0; i<cantClientes; i++)
    {
        regCliente = auxArchivoCliente.leerRegistro(i);

        for(int j=0; j<cantVentas; j++)
        {
            regVenta = auxArchivoVenta.leerRegistro(j);

            if( regVenta.getFechaVenta().getAnio() == anio && regVenta.getFechaVenta().getMes() == mes && strcmp(regCliente.getDni(),regVenta.getDni()) == 0 && regCliente.getActivo())
            {
                hayVentas = true;
                if(mostrarTitulo)
                {
                    cout << "Cliente: " << regVenta.getApellido() << ", " << regVenta.getNombre() << endl << endl;
                    cout << left;
                    cout << setw(10) << "Codigo";
                    cout << setw(20) << "Descripcion";
                    cout << setw(10) << "Cantidad";
                    cout << setw(20) << "Numero de Factura";
                    cout << setw(10) << "Importe";
                    cout << setw(15) << "Estado";
                    if(regVenta.getActiva() && regVenta.getSaldo() != 0)
                    {
                        cout << setw(10) << "Saldo";
                    }
                    cout << setw(15) << "Fecha Factura" << endl;
                    cout << "-------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
                    mostrarTitulo = false;
                }
                importeTotal += regVenta.getImporte();
                regVenta.Mostrar();
                cout << "-------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
            }
        }
        if (importeTotal != 0)
        {
            cout << "Total Facturado: $" << importeTotal;
            importeTotal = 0;
            cout << endl << endl;
        }
        mostrarTitulo = true;
    }
    if(!hayVentas)
    {
        cout << "No existen ventas para este cliente." << endl;
    }
    system("pause");
}

void ArchivoVenta::listarXClienteXMes()
{
    bool hayVentas = false;
    bool mostrarTitulo;
    float importeTotal = 0;
    char dni[12];
    int mes, anio;
    ArchivoVenta auxArchivoVenta("ventas.dat");
    Venta regVenta;
    int cantVentas = auxArchivoVenta.contarRegistros();
    ArchivoCliente auxArchivoCliente("clientes.dat");
    Cliente regCliente;
    int cantClientes = auxArchivoCliente.contarRegistros();

    cout << "DNI: ";
    cargarCadena(dni, 11);
    cout << "Mes: ";
    cin >> mes;
    cout << "Anio: ";
    cin >> anio;
    system("cls");

    for(int i=0; i<cantClientes; i++)
    {
        regCliente = auxArchivoCliente.leerRegistro(i);

        for(int j=0; j<cantVentas; j++)
        {
            regVenta = auxArchivoVenta.leerRegistro(j);

            if( regVenta.getFechaVenta().getAnio() == anio && regVenta.getFechaVenta().getMes() == mes && strcmp(regCliente.getDni(),regVenta.getDni()) == 0 && strcmp(regCliente.getDni(),dni) == 0 && regCliente.getActivo())
            {
                hayVentas = true;
                if(mostrarTitulo)
                {
                    cout << "Cliente: " << regVenta.getApellido() << ", " << regVenta.getNombre() << endl << endl;
                    cout << left;
                    cout << setw(10) << "Codigo";
                    cout << setw(20) << "Descripcion";
                    cout << setw(10) << "Cantidad";
                    cout << setw(20) << "Numero de Factura";
                    cout << setw(10) << "Importe";
                    cout << setw(15) << "Estado";
                    cout << setw(10) << "Saldo";
                    cout << setw(15) << "Fecha Factura" << endl;
                    cout << "-------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
                    mostrarTitulo = false;
                }
                importeTotal += regVenta.getImporte();
                regVenta.Mostrar();
                cout << "-------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
            }
        }
        if (importeTotal != 0)
        {
            cout << "Total Facturado: $" << importeTotal;
            importeTotal = 0;
            cout << endl << endl;
        }
        mostrarTitulo = true;
    }
    if(!hayVentas)
    {
        cout << "No existen ventas para este cliente." << endl;
    }
    system("pause");
}

void ArchivoVenta::imprimirPorPantalla()
{
    int numFactura;

    ArchivoVenta auxArchivoVenta("ventas.dat");
    Venta regVenta;
    int cantVentas = auxArchivoVenta.contarRegistros();

    cout << "Numero de Factura: " << endl;
    cin >> numFactura;

    system("cls");

    for(int i=0; i<cantVentas; i++)
    {
        regVenta = auxArchivoVenta.leerRegistro(i);

        if( numFactura == regVenta.getNumeroFactura() )
        {

            cout << "Numero de Factura: " << numFactura << "                                Fecha: ";
            regVenta.getFechaVenta().Mostrar();
            cout << left;

            cout << endl << endl;

            cout << "__________________________________________________________________" << endl << endl;

            cout << "                            MUEBLERIA LOS JUANES" << endl;

            cout << "__________________________________________________________________" << endl << endl << endl << endl;

            cout << "Cliente: " << regVenta.getApellido() << ", " << regVenta.getNombre() << endl << endl << endl << endl;

            cout << setw(10) << "Codigo";
            cout << setw(45) << "Detalle";
            cout << setw(5) << "";
            cout << setw(10) << "Importe" << endl;

            cout << "__________________________________________________________________" << endl << endl;

            cout << setw(10) << regVenta.getCodigoArticulo();
            cout << setw(45) << regVenta.getDescripcionArticulo();
            cout << setw(5) << "$";
            cout << setw(10) << regVenta.getImporte() << endl << endl;

            cout << "__________________________________________________________________" << endl << endl;

            cout << right;
            cout << setw(55) << "Total:";
            cout << left;
            cout << setw(5) << "$";
            cout << setw(5) << regVenta.getImporte() << endl << endl;

            system("pause");
            return;
        }
    }
    cout << "El numero de factura ingresado no existe." << endl;
    system("pause");
}

void ArchivoVenta::anularVenta()
{
    ArchivoVenta auxArchivoVenta("ventas.dat");
    Venta regVenta;
    ArchivoArticulo auxArchivoArticulo("articulos.dat");
    Articulo regArticulo;
    MenuManager menu;
    ArchivoCliente auxArchivoCliente("clientes.dat");
    Cliente regCliente;
    char confirmacion;
    int nF;
    cout << "Numero de Factura: ";
    cin >> nF;
    system("cls");
    int pos = auxArchivoVenta.buscarFactura(nF);
    if(pos == -1)
    {
        cout<<"No existe una factura con ese numero"<<endl;
        system("pause");
    }
    else
    {
        regVenta = auxArchivoVenta.leerRegistro(pos);

        if (regVenta.getActiva())
        {
            if(regVenta.getSaldo() == regVenta.getImporte())
            {
                cout << "El comprobante seleccionado sera anulado." << endl;
                cout << "Confirma??? S/N" << endl;
                cin >> confirmacion;
                if (confirmacion == 's' || confirmacion == 'S')
                {
                    system("cls");
                    regVenta = auxArchivoVenta.leerRegistro(pos);
                    regVenta.setPaga(true);
                    regVenta.setActiva(false);

                    int cantArticulos = auxArchivoArticulo.contarRegistros();
                    for (int i=0; i<cantArticulos; i++)
                    {
                        regArticulo = auxArchivoArticulo.leerRegistro(i);

                        if (regArticulo.getCodigoArticulo() == regVenta.getCodigoArticulo())
                        {
                            menu.sumarStock(regVenta.getCodigoArticulo(), regVenta.getCatidadVendida());
                        }
                    }
                    auxArchivoVenta.sobreEscribirRegistro(regVenta, pos);

                    regCliente = auxArchivoCliente.leerRegistro(auxArchivoCliente.buscarDni(regVenta.getDni()));
                    regCliente.setSaldoDeudor( regCliente.getSaldoDeudor() - regVenta.getImporte() );
                    auxArchivoCliente.sobreEscribirRegistro(regCliente, auxArchivoCliente.buscarDni(regVenta.getDni()));
                    cout << "Comprobante anulado exitosamente." << endl;
                }
                else
                {
                    system("cls");
                    cout << "El comprobante no ha sido anulado." << endl;
                }
            }
            else
            {
                system("cls");
                cout << "No se puede anular una factura con un recibo aplicado." << endl;
            }
        }
        else
        {
            system("cls");
            cout << "La factura ya ha sido anulada anteriormente." << endl;
        }

        system("pause");
    }
}

int ArchivoVenta::buscarFactura(int n)
{
    Venta reg;
    FILE *p;
    p = fopen(nombre,"rb");
    if(p == NULL)
    {
        return -2;
    }
    int pos = 0;
    while(fread(&reg, sizeof reg, 1,p) == 1)
    {
        if(reg.getNumeroFactura() == n)
        {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}

int ArchivoVenta::sobreEscribirRegistro(Venta reg, int pos)
{
    FILE *p = fopen(nombre,"rb+");
    if(p == NULL)
    {
        return -1;
    }
    fseek(p, pos*sizeof (Venta), 0);
    int valor = fwrite(&reg, sizeof reg, 1,p);
    fclose(p);
    return valor;
}

void ArchivoVenta::leerRegistro(Venta *vec, int cantidadRegistrosALeer)
{
    FILE *p = fopen(nombre, "rb");
    if (p == NULL)
    {
        return ;
    }

    fread(vec, sizeof(Venta), cantidadRegistrosALeer, p);
    fclose(p);
}



bool ArchivoVenta::guardar(Venta *vec, int cantidadRegistrosAEscribir)
{
    FILE *p = fopen(nombre, "ab");
    if (p == NULL)
    {
        return false;
    }

    int cantidadRegistrosEscritos = fwrite(vec, sizeof(Venta), cantidadRegistrosAEscribir, p);
    fclose(p);
    return cantidadRegistrosEscritos == cantidadRegistrosAEscribir;
}


void ArchivoVenta::vaciar()
{
    FILE *p = fopen(nombre, "wb");
    if (p == NULL)
    {
        return ;
    }
    fclose(p);
}
