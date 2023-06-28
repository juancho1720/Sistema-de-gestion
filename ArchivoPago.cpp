#include <iostream>
#include <string.h>
#include <iomanip>

using namespace std;

#include "ArchivoPago.h"
#include "ArchivoCliente.h"
#include "ArchivoVenta.h"
#include "FuncionesGenerales.h"

ArchivoPago::ArchivoPago(const char *n)
{
    strcpy(nombre, n);
}

Pago ArchivoPago::leerRegistro(int pos)
{
    Pago reg;
    FILE *p = fopen(nombre, "rb");
    if(p == NULL)
    {
        return reg;
    }
    fseek(p, sizeof(Pago)*pos,0);
    fread(&reg, sizeof reg,1, p);
    fclose(p);
    return reg;
}

int ArchivoPago::contarRegistros()
{
    FILE *p = fopen(nombre, "rb");
    if(p == NULL)
    {
        return -1;
    }
    fseek(p, 0,2);
    int tam = ftell(p);
    fclose(p);
    return tam/sizeof(Pago);
}

void ArchivoPago::escribirRegistro()
{
    Pago reg;
    FILE *p = fopen("pagos.dat","ab");
    if(p == NULL)
    {
        cout << "Error archivo.";
    }
    if(reg.Cargar() == true)
    {
        fwrite(&reg, sizeof reg, 1, p);
        fclose(p);
        system("cls");
        cout << "Pago agregado exitosamente!!!" << endl;
        system("pause");
    }
    else
    {
        cout << "Pago no agregado!!!" << endl;
        system("pause");
    }
}

void ArchivoPago::listarXCliente()
{
    bool hayVentas = false;
    bool mostrarTitulo = true;
    char dni[12];
    ArchivoPago auxArchivoPago("pagos.dat");
    Pago regPago;
    int cantPagos = auxArchivoPago.contarRegistros();
    ArchivoCliente auxArchivoCliente("clientes.dat");
    Cliente regCliente;
    int cantClientes = auxArchivoCliente.contarRegistros();
    float importeTotal = 0;
    cout << "DNI: ";
    cargarCadena(dni, 11);
    system("cls");

    if (comprobarClientesExistentes(dni) == true)
    {
        for(int i=0; i<cantClientes; i++)
        {
            regCliente = auxArchivoCliente.leerRegistro(i);

            if(strcmp(regCliente.getDni(), dni) == 0)
            {
                for(int j=0; j<cantPagos; j++)
                {
                    regPago = auxArchivoPago.leerRegistro(j);

                    if(mostrarTitulo && strcmp(regPago.getDni(), dni) == 0 && regPago.getActivo())
                    {
                        hayVentas = true;

                        cout << "Cliente: " << regCliente.getApellido() << ", " << regCliente.getNombre() << endl << endl;
                        cout << left;
                        cout << setw(20) << "Numero de Recibo";
                        cout << setw(20) << "DNI";
                        cout << setw(10) << "Importe";
                        cout << setw(30) << "Concepto";
                        cout << setw(15) << "Forma de Pago";
                        cout << setw(15) << "Fecha Recibo";
                        cout << setw(15) << "Facturas canceladas" << endl;
                        cout << "-------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
                        mostrarTitulo = false;
                    }
                    if(strcmp(regPago.getDni(), dni) == 0 && regPago.getActivo())
                    {
                        importeTotal += regPago.getImporte();
                        regPago.Mostrar();
                        cout << "-------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
                    }
                }
            }
            if (importeTotal != 0)
            {
                cout << "Total Cobrado: $" << importeTotal;
                importeTotal = 0;
                cout << endl << endl;
            }
            mostrarTitulo = true;
        }
        if(!hayVentas)
        {
            cout << "No existen cobranzas de este cliente para este periodo." << endl;
        }
    }
    else
    {
        system("cls");
        cout << "El cliente ingresado no existe." << endl;
    }

    system("pause");
}

void ArchivoPago::listarTodosXMes()
{
    bool hayVentas = false;
    bool mostrarTitulo = true;
    int mes, anio;
    ArchivoPago auxArchivoPago("pagos.dat");
    Pago regPago;
    int cantPagos = auxArchivoPago.contarRegistros();
    ArchivoCliente auxArchivoCliente("clientes.dat");
    Cliente regCliente;
    int cantClientes = auxArchivoCliente.contarRegistros();
    float importeTotal = 0;
    cout << "Mes: ";
    cin >> mes;
    cout << "Anio: ";
    cin >> anio;
    system("cls");
    cantPagos = auxArchivoPago.contarRegistros();
    cantClientes = auxArchivoCliente.contarRegistros();

    for(int i=0; i<cantClientes; i++)
    {
        regCliente = auxArchivoCliente.leerRegistro(i);

        for(int j=0; j<cantPagos; j++)
        {
            regPago = auxArchivoPago.leerRegistro(j);

            if(strcmp(regPago.getDni(), regCliente.getDni()) == 0 && regPago.getFechaPago().getAnio() == anio && regPago.getFechaPago().getMes() == mes && regPago.getActivo())
            {
                hayVentas = true;
                if(mostrarTitulo)
                {
                    cout << "Cliente: " << regCliente.getApellido() << ", " << regCliente.getNombre() << endl << endl;
                    cout << left;
                    cout << setw(20) << "Numero de Recibo";
                    cout << setw(20) << "DNI";
                    cout << setw(10) << "Importe";
                    cout << setw(30) << "Concepto";
                    cout << setw(15) << "Forma de Pago";
                    cout << setw(15) << "Fecha Recibo";
                    cout << setw(15) << "Facturas canceladas" << endl;
                    cout << "-------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
                    mostrarTitulo = false;
                }
                importeTotal += regPago.getImporte();
                regPago.Mostrar();
                cout << "-------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
            }
        }
        if (importeTotal != 0)
        {
            cout << "Total Cobrado: $" << importeTotal;
            importeTotal = 0;
            cout << endl << endl;
        }
        mostrarTitulo = true;
    }
    if(!hayVentas)
    {
        cout << "No existen cobranzas para este periodo." << endl;
    }
    system("pause");
}

void ArchivoPago::imprimirPorPantalla()
{
    int numRecibo;

    ArchivoPago auxArchivoPago("pagos.dat");
    Pago regPago;
    int cantPagos = auxArchivoPago.contarRegistros();

    cout << "Numero de Recibo: " << endl;
    cin >> numRecibo;

    system("cls");

    for(int i=0; i<cantPagos; i++)
    {
        regPago = auxArchivoPago.leerRegistro(i);

        if( numRecibo == regPago.getNumeroRecibo() )
        {

            cout << "Numero de Recibo: " << numRecibo << "                                Fecha: ";
            regPago.getFechaPago().Mostrar();
            cout << left;

            cout << endl << endl;

            cout << "__________________________________________________________________" << endl << endl;

            cout << "                            MUEBLERIA LOS JUANES" << endl;

            cout << "__________________________________________________________________" << endl << endl << endl << endl;

            cout << "Cliente: " << regPago.getApellido() << ", " << regPago.getNombre() << endl << endl << endl << endl;

            cout << setw(30) << "Facturas canceladas";
            cout << setw(25) << "Forma de pago";
            cout << setw(5) << "";
            cout << setw(10) << "Importe" << endl;

            cout << "__________________________________________________________________" << endl << endl;

            if (regPago.getActivo())
            {
                if (regPago.getNumFactura() == 0)
                {
                    cout << setw(30) << "Anticipo";
                }
                else
                {
                    ArchivoVenta auxArchivoVenta("ventas.dat");
                    Venta regVenta;
                    int cantVentas = auxArchivoVenta.contarRegistros();

                    if(cantVentas != 0)
                    {
                        for (int i=0; i<cantVentas; i++)
                        {
                            regVenta = auxArchivoVenta.leerRegistro(i);

                            if (regVenta.getNumeroRecibo() == numRecibo)
                            {
                                cout << right;
                                cout << " [" << regVenta.getNumeroFactura() << "] ";
                            }
                        }
                    }
                }
            }
            else
            {
                cout << setw(30) << "Anulado";
            }

            cout << setw(25) << regPago.getFormaPago();
            cout << setw(5) << "$";
            cout << setw(10) << regPago.getImporte() << endl << endl;

            cout << "__________________________________________________________________" << endl << endl;

            cout << right;
            cout << setw(55) << "Total:";
            cout << left;
            cout << setw(5) << "$";
            cout << setw(5) << regPago.getImporte() << endl << endl;

            system("pause");
            return;
        }
    }
    cout << "El numero de recibo ingresado no existe." << endl;
    system("pause");
}

void ArchivoPago::anular()
{
    int nR;
    char confirmacion;
    ArchivoPago auxArchivoPago("pagos.dat");
    Pago regPago;
    ArchivoVenta auxArchivoVenta("ventas.dat");
    Venta regVenta;
    int cantVentas = auxArchivoVenta.contarRegistros();
    cout << "Numero de Recibo: ";
    cin >> nR;
    system("cls");
    int pos = auxArchivoPago.buscarRecibo(nR);

    if(pos < 0)
    {
        cout<<"No existe un recibo con ese numero"<<endl;
        system("pause");
    }
    else
    {

        regPago = auxArchivoPago.leerRegistro(pos);

        if (regPago.getActivo())
        {
            cout << "Cliente: " << regPago.getApellido() << ", " << regPago.getNombre() << endl << endl;
            cout << left;
            cout << setw(20) << "Numero de Recibo";
            cout << setw(20) << "DNI";
            cout << setw(10) << "Importe";
            cout << setw(30) << "Concepto";
            cout << setw(15) << "Forma de Pago";
            cout << setw(15) << "Fecha";
            cout << setw(15) << "Facturas canceladas" << endl;
            regPago.Mostrar();

            cout << "-------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

            cout << "El comprobante seleccionado sera anulado." << endl;
            cout << "Confirma??? S/N" << endl;
            cin >> confirmacion;

            if (confirmacion == 's' || confirmacion == 'S')
            {
                for (int i=0; i<cantVentas; i++)
                {
                    regVenta = auxArchivoVenta.leerRegistro(i);

                    if (regVenta.getNumeroRecibo() == nR)
                    {
                        regVenta.setPaga(false);
                        regVenta.setSaldo(regVenta.getImporte());
                        auxArchivoVenta.sobreEscribirRegistro(regVenta, i);
                        regVenta = auxArchivoVenta.leerRegistro(auxArchivoVenta.buscarFactura(regPago.getNumFactura()));
                    }
                }

                regPago.setActivo(false);
                auxArchivoPago.sobreEscribirRegistro(regPago, pos);
                sumarSaldoDeudor(regPago.getDni(), regPago.getImporte());

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
            cout << "El comprobante ya ha sido anulado anteriormente." << endl;
        }

        system("pause");
        system("cls");
    }
}

int ArchivoPago::buscarRecibo(int n)
{
    Pago reg;
    FILE *p;
    p = fopen(nombre,"rb");
    if(p == NULL)
    {
        return -2;
    }
    int pos = 0;
    while(fread(&reg, sizeof reg, 1,p) == 1)
    {
        if(reg.getNumeroRecibo() == n)
        {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}

int ArchivoPago::sobreEscribirRegistro(Pago reg, int pos)
{
    FILE *p = fopen(nombre,"rb+");
    if(p == NULL)
    {
        return -1;
    }
    fseek(p, pos*sizeof (Pago), 0);
    int valor = fwrite(&reg, sizeof reg, 1,p);
    fclose(p);
    return valor;
}

void ArchivoPago::leerRegistro(Pago *vec, int cantidadRegistrosALeer)
{
    FILE *p = fopen(nombre, "rb");
    if (p == NULL)
    {
        return ;
    }

    fread(vec, sizeof(Pago), cantidadRegistrosALeer, p);
    fclose(p);
}

bool ArchivoPago::guardar(Pago *vec, int cantidadRegistrosAEscribir)
{
    FILE *p = fopen(nombre, "ab");
    if (p == NULL)
    {
        return false;
    }

    int cantidadRegistrosEscritos = fwrite(vec, sizeof(Pago), cantidadRegistrosAEscribir, p);
    fclose(p);
    return cantidadRegistrosEscritos == cantidadRegistrosAEscribir;
}

void ArchivoPago::vaciar()
{
    FILE *p = fopen(nombre, "wb");
    if (p == NULL)
    {
        return ;
    }
    fclose(p);
}
