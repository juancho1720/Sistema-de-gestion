#include <iostream>
#include <string.h>
#include <iomanip>

using namespace std;

#include "MenuManager.h"
#include "Cliente.h"
#include "ArchivoCliente.h"
#include "FuncionesGenerales.h"
#include "ArchivoVenta.h"
#include "ArchivoArticulo.h"
#include "ArchivoPago.h"
#include <fstream>

void MenuManager::MenuBienvenida()
{
    cout << right;
    cout << setw(35) << "                      BIENVENIDO AL SISTEMA DE GESTION" << endl;
    cout << setw(35) << "                             <ERROR 404>" << endl << endl;

    cout << setw(35) << "-----------------------------------------------------------------------------" << endl << endl;

    cout << setw(35) << "                      Universidad Tecnologica Nacional" << endl << endl;

    cout << setw(35) << "-----------------------------------------------------------------------------" << endl << endl;

    cout << left;
    cout << setw(35) << "Carrera: Tecnicatura Universitaria en Programacion / Sistemas Informaticos" << endl;
    cout << setw(35) << "Materia: Laboratorio II" << endl << endl;

    cout << setw(35) << "Profesores:" << endl;
    cout << setw(35) << "Simon, Angel" << endl;
    cout << setw(35) << "Lara Campos, Brian Esteban" << endl << endl;

    cout << setw(35) << "Jefes de trabajos practicos:" << endl;
    cout << setw(35) << "Gonzalez, Juan Agustin" << endl;
    cout << setw(35) << "Varela, Mariano" << endl << endl;

    cout << setw(35) << "Ayudantes de trabajos practicos:" << endl;
    cout << setw(35) << "Vargas Pabon" << endl;
    cout << setw(25) << "Gabriel de Jesus" << endl << endl;

    cout << setw(35) << "Alumnos:" << endl;
    cout << setw(35) << "Juan Romero - Legajo 27542" << endl;
    cout << setw(35) << "Juan Manuel Sarmiento - Legajo 27543" << endl;
    cout << setw(35)<< "Valentina Conde - Legajo 25862" << endl << endl;

    system("pause");
    system("cls");
}

void MenuManager::MenuGeneral()
{
    int opcionMenu;

    do
    {
        cout << "MENU PRINCIPAL" << endl;
        cout << "------------------------------" << endl;
        cout << "1- Clientes." << endl;
        cout << "2- Articulos." << endl;
        cout << "3- Ventas." << endl;
        cout << "4- Pagos." << endl;
        cout << "5- Reportes." << endl;
        cout << "6- BackUp." << endl << endl;
        cout << "0- Salir." << endl;
        cin >> opcionMenu;
        switch(opcionMenu)
        {
        case 1:
            system("cls");
            ModuloClientes();
            break;
        case 2:
            system("cls");
            ModuloArticulos();
            break;
        case 3:
            system("cls");
            ModuloVentas();
            break;
        case 4:
            system("cls");
            ModuloPagos();
            break;
        case 5:
            system("cls");
            ModuloReportes();
            break;
        case 6:
            system("cls");
            ModuloBackUp();
            break;
        }
    }
    while(opcionMenu!=0);
}

void MenuManager::ModuloClientes()
{
    int opcionMenu;
    char dni[12];
    int cantClientes;
    int pos;
    char confirmacion;
    Cliente regCliente;
    ArchivoCliente auxArchivoCliente("clientes.dat");
    do
    {
        cout << "MODULO CLIENTE" << endl;
        cout << "------------------------------" << endl;
        cout << "1- Cargar nuevo." << endl;
        cout << "2- Listar todos." << endl;
        cout << "3- Buscar por DNI." << endl;
        cout << "4- Borrar." << endl;
        cout << "5- Modificar limite." << endl << endl;
        cout << "0- Volver al menu principal." << endl;
        cin >> opcionMenu;
        switch(opcionMenu)
        {
        case 1:
            system("cls");
            auxArchivoCliente.escribirRegistro(regCliente);
            break;
        case 2:
            system("cls");
            cantClientes = auxArchivoCliente.contarRegistros();
            if (cantClientes != -1)
            {
                cout << left;
                cout << setw(15) << "Apellido";
                cout << setw(20) << "Nombre";
                cout << setw(15) << "DNI";
                cout << setw(20) << "Monto Maximo" << endl;
                cout << "-------------------------------------------------------------" << endl;
                for (int i=0; i< cantClientes; i++)
                {
                    regCliente = auxArchivoCliente.leerRegistro(i);

                    if (regCliente.getActivo() == true)
                    {
                        regCliente.Mostrar();
                        cout << "-------------------------------------------------------------" << endl;
                    }
                }
            }
            else
            {
                cout << "No hay cliente activos para listar." << endl;
            }
            system("pause");
            break;
        case 3:
            system("cls");
            cout << "DNI: ";
            cargarCadena(dni, 11);
            system("cls");
            pos = auxArchivoCliente.buscarDni(dni);
            if(pos == -1)
            {
                cout<<"No existe un cliente con ese numero de DNI"<<endl;
                system("pause");
            }
            else
            {
                regCliente = auxArchivoCliente.leerRegistro(pos);
                if(regCliente.getActivo() == true)
                {
                    cout << left;
                    cout << setw(15) << "Apellido";
                    cout << setw(20) << "Nombre";
                    cout << setw(15) << "DNI";
                    cout << setw(20) << "Monto Maximo" << endl;
                    cout << "-------------------------------------------------------------" << endl;
                    regCliente.Mostrar();
                    cout << "-------------------------------------------------------------" << endl;
                    system("pause");
                }
                else
                {
                    cout << "No hay clientes activos con ese numero de DNI." << endl;
                    system("pause");
                }
            }
            break;
        case 4:
            system("cls");
            cout << "DNI: ";
            cargarCadena(dni, 11);
            system("cls");
            pos = auxArchivoCliente.buscarDni(dni);
            regCliente = auxArchivoCliente.leerRegistro(pos);
            if(pos == -1 || !regCliente.getActivo())
            {
                cout<<"No existe un cliente con ese numero de DNI"<<endl;
                system("pause");
            }
            else
            {
                cout << "El cliente <" << regCliente.getApellido() << ", " << regCliente.getNombre() << "> sera eliminado." << endl;
                cout << "Confirma??? S/N" << endl;
                cin >> confirmacion;
                if (confirmacion == 's' || confirmacion == 'S')
                {
                    system("cls");
                    regCliente.setActivo(false);
                    auxArchivoCliente.sobreEscribirRegistro(regCliente, pos);
                    cout << "Cliente borrado exitosamente." << endl;
                }
                else
                {
                    system("cls");
                    cout << "El cliente no ha sido borrado." << endl;
                }
                system("pause");
            }
            break;
        case 5:
            system("cls");
            cambiarLimiteDeuda();
            system("pause");
            break;
        }
        system("cls");
    }
    while(opcionMenu!=0);
}

void MenuManager::ModuloVentas()
{

    int opcionMenu;
    char dni[12];
    int cantVentas;
    int cantClientes;
    int pos;
    char confirmacion;
    int nF;
    int mes, anio;
    bool hayVentas;
    bool mostrarTitulo = true;
    float importeTotal = 0;

    ArchivoVenta auxArchivoVenta("ventas.dat");
    Venta regVenta;

    ArchivoCliente auxArchivoCliente("clientes.dat");
    Cliente regCliente;

    ArchivoArticulo auxArchivoArticulo("articulos.dat");
    Articulo regArticulo;

    do
    {
        cout << "MODULO VENTAS" << endl;
        cout << "------------------------------" << endl;
        cout << "1- Cargar nueva." << endl;
        cout << "2- Listar por cliente." << endl;
        cout << "3- Listar todas por mes." << endl;
        cout << "4- Listar por cliente por mes." << endl;
        cout << "5- Anular venta." << endl << endl;
        cout << "0- Volver al menu principal." << endl;
        cin >> opcionMenu;
        switch(opcionMenu)
        {
        case 1:
            system("cls");
            auxArchivoVenta.escribirRegistro(regVenta);
            break;
        case 2:
            system("cls");
            hayVentas = false;
            cout << "DNI: ";
            cargarCadena(dni, 11);
            system("cls");
            cantVentas = auxArchivoVenta.contarRegistros();

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
            break;
        case 3:
            system("cls");
            hayVentas = false;
            cout << "Mes: ";
            cin >> mes;
            cout << "Anio: ";
            cin >> anio;
            system("cls");
            cantVentas = auxArchivoVenta.contarRegistros();
            cantClientes = auxArchivoCliente.contarRegistros();

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
                            if(regVenta.getSaldo() != 0)
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
            break;
        case 4:
            system("cls");
            hayVentas = false;
            cout << "DNI: ";
            cargarCadena(dni, 11);
            cout << "Mes: ";
            cin >> mes;
            cout << "Anio: ";
            cin >> anio;
            system("cls");
            cantVentas = auxArchivoVenta.contarRegistros();
            cantClientes = auxArchivoCliente.contarRegistros();

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
            break;
        case 5:
            system("cls");
            cout << "Numero de Factura: ";
            cin >> nF;
            system("cls");
            pos = auxArchivoVenta.buscarFactura(nF);
            if(pos == -1)
            {
                cout<<"No existe una factura con ese numero"<<endl;
                system("pause");
            }
            else
            {
                cout << "El comprobante seleccionado sera anulado." << endl;
                cout << "Confirma??? S/N" << endl;
                cin >> confirmacion;
                if (confirmacion == 's' || confirmacion == 'S')
                {
                    system("cls");
                    regVenta = auxArchivoVenta.leerRegistro(pos);
                    regVenta.setPaga(true);

                    int cantArticulos = auxArchivoArticulo.contarRegistros();
                    for (int i=0; i<cantArticulos; i++)
                    {
                        regArticulo = auxArchivoArticulo.leerRegistro(i);

                        if (regArticulo.getCodigoArticulo() == regVenta.getCodigoArticulo())
                        {
                            sumarStock(regVenta.getCodigoArticulo(), regVenta.getCatidadVendida());
                        }
                    }
                    auxArchivoVenta.sobreEscribirRegistro(regVenta, pos);
                    cout << "Comprobante anulado exitosamente." << endl;
                }
                else
                {
                    system("cls");
                    cout << "El comprobante no ha sido anulado." << endl;
                }
                system("pause");
            }
            break;
        }
        system("cls");
    }
    while(opcionMenu!=0);
}

void MenuManager::ModuloReportes()
{
    int opcionMenu;
    char dni[12];
    int pos;
    int cantVentas, cantPagos;
    bool noHayDeudores;
    bool hayVentas;
    bool mostrarTitulo;
    float importeTotal = 0;
    ArchivoCliente auxArchivoCliente("clientes.dat");
    Cliente regCliente;
    ArchivoVenta auxArchivoVenta("ventas.dat");
    Venta regVenta;
    ArchivoPago auxArchivoPago("pagos.dat");
    Pago regPago;
    do
    {
        cout << "MODULO REPORTES" << endl;
        cout << "------------------------------" << endl;
        cout << "1- Listar saldos deudores por DNI." << endl;
        cout << "2- Listar todos los saldos deudores." << endl;
        cout << "3- Listar movimientos totales." << endl;
        cout << "4- Cantidad de ventas mensuales por producto." << endl;
        cout << "5- Cantidad de cobranzas por formas de pago." << endl;
        cout << "6- Exportar listado de clientes a Excel." << endl;
        cout << "7- Exportar cuentas corrientes a Excel." << endl << endl;
        cout << "0- Volver al menu principal." << endl;
        cin >> opcionMenu;
        switch(opcionMenu)
        {
        case 1:
            system("cls");
            cout << "DNI: ";
            cargarCadena(dni, 11);
            system("cls");
            pos = auxArchivoCliente.buscarDni(dni);
            if(pos == -1)
            {
                cout<<"No existe un cliente con ese numero de DNI"<<endl;
                system("pause");
            }
            else
            {
                regCliente = auxArchivoCliente.leerRegistro(pos);
                if(regCliente.getActivo() == true && consultarDeudaCliente(regCliente.getDni()) != 0)
                {
                    cout << left;
                    cout << setw(15) << "DNI";
                    cout << setw(20) << "Nombre";
                    cout << setw(20) << "Apellido" << endl;
                    cout << "-------------------------------------------" << endl;
                    regCliente.Mostrar();
                    cout << endl << "Saldo Deudor: $" << consultarDeudaCliente(regCliente.getDni()) << endl << endl;
                    system("pause");
                }
                else
                {
                    cout << "El cliente no posee saldo deudor." << endl;
                    system("pause");
                }
            }
            break;
        case 2:
            system("cls");
            noHayDeudores = true;
            int cantClientes;
            cantClientes = auxArchivoCliente.contarRegistros();

            for (int i=0; i< cantClientes; i++)
            {
                regCliente = auxArchivoCliente.leerRegistro(i);

                if(consultarDeudaCliente(regCliente.getDni()) != 0)
                {
                    cout << left;
                    cout << setw(15) << "DNI";
                    cout << setw(20) << "Nombre";
                    cout << setw(20) << "Apellido" << endl;
                    cout << "-------------------------------------------" << endl;
                    regCliente.Mostrar();
                    cout << endl << "Saldo Deudor: $" << consultarDeudaCliente(regCliente.getDni()) << endl;
                    cout << "-------------------------------------------" << endl << endl << endl;
                    noHayDeudores = false;
                }
            }
            if(noHayDeudores)
            {
                cout << "No hay clientes con saldo deudor." << endl;
            }
            system("pause");
            break;
        case 3:
            system("cls");
            hayVentas = false;
            cantVentas = auxArchivoVenta.contarRegistros();
            cantClientes = auxArchivoCliente.contarRegistros();
            cantPagos = auxArchivoPago.contarRegistros();
            for(int i=0; i<cantClientes; i++)
            {
                importeTotal = 0;

                regCliente = auxArchivoCliente.leerRegistro(i);

                for(int j=0; j<cantVentas; j++)
                {
                    regVenta = auxArchivoVenta.leerRegistro(j);

                    if(regCliente.getActivo() && strcmp(regCliente.getDni(), regVenta.getDni()) == 0)
                    {
                        hayVentas = true;
                        if(mostrarTitulo)
                        {
                            cout << "Cliente: " << regCliente.getApellido() << ", " << regCliente.getNombre() << endl << endl;
                            cout << left;
                            cout << setw(10) << "Tipo";
                            cout << setw(10) << "Numero";
                            cout << setw(10) << "Importe";
                            cout << setw(15) << "Estado";
                            cout << setw(15) << "Fecha";
                            cout << setw(10) << "Saldo Deudor" << endl;
                            cout << "-------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
                            mostrarTitulo = false;
                        }
                        importeTotal += regVenta.getImporte();
                        cout << left;
                        cout << setw(10) << "FC";
                        cout << setw(10) << regVenta.getNumeroFactura();
                        cout << setw(10) << regVenta.getImporte();
                        if (regVenta.getPaga())
                        {
                            cout << setw(15) << "Paga";
                        }
                        if (!regVenta.getPaga())
                        {
                            cout << setw(15) << "Pendiente";
                        }
                        regVenta.getFechaVenta().Mostrar();
                        cout << right;
                        cout << setw(10) << importeTotal;
                        cout << endl;
                        cout << "-------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
                    }
                }

                for(int z=0; z<cantPagos; z++)
                {
                    regPago = auxArchivoPago.leerRegistro(z);

                    if(regCliente.getActivo() && strcmp(regCliente.getDni(), regPago.getDni()) == 0)
                    {
                        if(regCliente.getActivo())
                        {
                            cout << left;
                            mostrarTitulo = false;
                            importeTotal -= regPago.getImporte();
                            cout << left;
                            cout << setw(10) << "RBO";
                            cout << setw(10) << regPago.getNumeroRecibo();
                            cout << setw(10) << regPago.getImporte();
                            if (regPago.getActivo())
                            {
                                cout << setw(15) << "Aplicado";
                            }
                            if (!regPago.getActivo())
                            {
                                cout << setw(15) << "Sin aplicar";
                            }
                            regPago.getFechaPago().Mostrar();
                            cout << right;
                            cout << setw(10) << importeTotal;
                            cout << endl;
                            cout << "-------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
                        }
                    }
                }
                mostrarTitulo = true;
            }
            if(!hayVentas)
            {
                cout << "No existen movimientos para listar." << endl;
            }
            system("pause");
            break;
        case 4:
            system("cls");
            ventasMensualesProductos();
            break;
        case 5:
            system("cls");
            cobrosMensualesTipo();
            break;
        case 6:
            system("cls");
            exportarClientes();
            break;
        case 7:
            system("cls");
            exportarCtasCtes();
            break;
        }
        system("cls");
    }
    while(opcionMenu!=0);
    system("cls");
}

float MenuManager::consultarDeudaCliente(const char *dni)
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

void MenuManager::ModuloArticulos()
{
    int opcionMenu;
    int codigo;
    int cantArticulos;
    int pos;
    char confirmacion;
    Articulo regArticulo;
    ArchivoArticulo auxArchivoArticulo("articulos.dat");
    do
    {
        cout << "MODULO ARTICULOS" << endl;
        cout << "------------------------------" << endl;
        cout << "1- Cargar nuevo." << endl;
        cout << "2- Listar todos." << endl;
        cout << "3- Buscar por codigo." << endl;
        cout << "4- Borrar." << endl;
        cout << "5- Consultar stock por codigo." << endl;
        cout << "6- Cargar stock por codigo." << endl;
        cout << "7- Cambiar precios manualmente." << endl;
        cout << "8- Cambiar todos los precios porcentualmente." << endl << endl;
        cout << "0- Volver al menu principal." << endl;
        cin >> opcionMenu;
        switch(opcionMenu)
        {
        case 1:
            system("cls");
            auxArchivoArticulo.escribirRegistro(regArticulo);
            system("pause");
            break;
        case 2:
            system("cls");
            cantArticulos = auxArchivoArticulo.contarRegistros();
            if (cantArticulos != -1)
            {
                cout << left;
                cout << setw(20) << "Descripcion";
                cout << setw(15) << "Codigo";
                cout << setw(15) << "Stock";
                cout << setw(20) << "Precio Unitario" << endl;
                cout << "------------------------------------------------------------------------------" << endl;
                for (int i=0; i< cantArticulos; i++)
                {
                    regArticulo = auxArchivoArticulo.leerRegistro(i);

                    if (regArticulo.getEstado() == true)
                    {
                        regArticulo.Mostrar();
                        cout << "------------------------------------------------------------------------------" << endl;
                    }
                }
            }
            else
            {
                cout << "No hay articulos activos para listar." << endl;
            }
            system("pause");
            break;
        case 3:
            system("cls");
            cout << "Codigo: ";
            cin >> codigo;
            system("cls");
            pos = auxArchivoArticulo.buscarCodigo(codigo);
            if(pos == -1)
            {
                cout<<"No existe un articulo con ese codigo"<<endl;
                system("pause");
            }
            else
            {
                regArticulo = auxArchivoArticulo.leerRegistro(pos);
                if(regArticulo.getEstado() == true)
                {
                    cout << left;
                    cout << setw(20) << "Descripcion";
                    cout << setw(15) << "Codigo";
                    cout << setw(15) << "Stock";
                    cout << setw(20) << "Precio Unitario" << endl;
                    cout << "------------------------------------------------------------------------------" << endl;
                    regArticulo.Mostrar();
                    cout << "------------------------------------------------------------------------------" << endl;
                    system("pause");
                }
                else
                {
                    cout << "No hay articulo activos con ese codigo." << endl;
                    system("pause");
                }
            }
            break;
        case 4:
            system("cls");
            cout << "Codigo: ";
            cin >> codigo;
            system("cls");
            pos = auxArchivoArticulo.buscarCodigo(codigo);
            regArticulo = auxArchivoArticulo.leerRegistro(pos);
            if(pos == -1 || regArticulo.getEstado() == false)
            {
                cout<<"No existe un articulo con ese codigo"<<endl;
                system("pause");
            }
            else
            {
                cout << "El articulo <" << regArticulo.getDescripcion() << "> sera eliminado." << endl;
                cout << "Confirma??? S/N" << endl;
                cin >> confirmacion;
                if (confirmacion == 's' || confirmacion == 'S')
                {
                    system("cls");
                    regArticulo.setEstado(false);
                    auxArchivoArticulo.sobreEscribirRegistro(regArticulo, pos);
                    cout << "Articulo borrado exitosamente." << endl;
                }
                else
                {
                    system("cls");
                    cout << "El articulo no ha sido borrado." << endl;
                }
                system("pause");
            }
            break;
        case 5:
            system("cls");
            cout << "Codigo: ";
            cin >> codigo;
            system("cls");
            pos = auxArchivoArticulo.buscarCodigo(codigo);
            if(pos == -1)
            {
                cout<<"No existe un articulo con ese codigo"<<endl;
                system("pause");
            }
            else
            {
                regArticulo = auxArchivoArticulo.leerRegistro(pos);
                if(regArticulo.getEstado() == true)
                {
                    cout << left;
                    cout << setw(20) << "Descripcion";
                    cout << setw(15) << "Codigo";
                    cout << setw(15) << "Stock";
                    cout << setw(20) << "Precio Unitario" << endl;
                    cout << "------------------------------------------------------------------------------" << endl;
                    regArticulo.Mostrar();
                    cout << "------------------------------------------------------------------------------" << endl;
                    system("pause");
                }
                else
                {
                    cout << "No hay articulo activos con ese codigo." << endl;
                    system("pause");
                }
            }
            break;
        case 6:
            system("cls");
            cout << "Codigo: ";
            cin >> codigo;
            system("cls");
            pos = auxArchivoArticulo.buscarCodigo(codigo);
            if(pos == -1)
            {
                cout<<"No existe un articulo con ese codigo"<<endl;
                system("pause");
            }
            else
            {
                regArticulo = auxArchivoArticulo.leerRegistro(pos);
                if(regArticulo.getEstado() == true)
                {
                    cout << "Cantidad de unidades a sumar en stock: ";
                    cin >> cantArticulos;
                    sumarStock(codigo, cantArticulos);
                    cout << "Unidades agregadas correctamente al stock." << endl;
                    system("pause");
                }
                else
                {
                    cout << "No hay articulo activos con ese codigo." << endl;
                    system("pause");
                }
            }
            break;
        case 7:
            system("cls");
            auxArchivoArticulo.cambiarPrecios();
            system("pause");
            break;
        case 8:
            system("cls");
            auxArchivoArticulo.aumentarPreciosPorcentual();
            system("pause");
            break;
        }
        system("cls");
    }
    while(opcionMenu!=0);
}

void MenuManager::ModuloPagos()
{
    int opcionPagos;
    ArchivoPago auxArchivoPago("pagos.dat");
    Pago regPago;
    ArchivoCliente auxArchivoCliente("clientes.dat");
    Cliente regCliente;
    int cantPagos;
    int cantClientes;
    int nR, pos;
    int mes, anio;
    bool hayVentas;
    char confirmacion;
    char dni[12];
    bool mostrarTitulo = true;
    float importeTotal = 0;
    do
    {
        cout << "MODULO PAGOS" << endl;
        cout << "------------------------------" << endl;
        cout << "1- Cargar ." << endl;
        cout << "2- Listar por cliente." << endl;
        cout << "3- Listar todos por mes." << endl;
        cout << "4- Anular pago." << endl << endl;
        cout << "0- Volver al menu principal." << endl;
        cin >> opcionPagos;
        switch(opcionPagos)
        {
        case 1:
            system("cls");
            auxArchivoPago.escribirRegistro(regPago);
            break;
        case 2:
            system("cls");
            hayVentas = false;
            mostrarTitulo = true;
            cout << "DNI: ";
            cargarCadena(dni, 11);
            system("cls");
            cantPagos = auxArchivoPago.contarRegistros();
            cantClientes = auxArchivoCliente.contarRegistros();

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

                            if(mostrarTitulo && strcmp(regPago.getDni(), dni) == 0)
                            {
                                hayVentas = true;

                                cout << "Cliente: " << regCliente.getApellido() << ", " << regCliente.getNombre() << endl << endl;
                                cout << left;
                                cout << setw(20) << "Numero de Recibo";
                                cout << setw(20) << "DNI";
                                cout << setw(10) << "Importe";
                                cout << setw(15) << "Factura";
                                cout << setw(15) << "Forma de Pago";
                                cout << setw(15) << "Fecha Recibo" << endl;
                                cout << "-------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
                                mostrarTitulo = false;
                            }
                            if(strcmp(regPago.getDni(), dni) == 0)
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
            break;
        case 3:
            system("cls");
            hayVentas = false;
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

                    if(strcmp(regPago.getDni(), regCliente.getDni()) == 0 && regPago.getFechaPago().getAnio() == anio && regPago.getFechaPago().getMes() == mes)
                    {
                        hayVentas = true;
                        if(mostrarTitulo)
                        {
                            cout << "Cliente: " << regCliente.getApellido() << ", " << regCliente.getNombre() << endl << endl;
                            cout << left;
                            cout << setw(20) << "Numero de Recibo";
                            cout << setw(20) << "DNI";
                            cout << setw(10) << "Importe";
                            cout << setw(20) << "Numero Factura";
                            cout << setw(15) << "Forma de Pago";
                            cout << setw(15) << "Fecha Recibo" << endl;
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
            break;
        case 4:
            system("cls");
            cout << "Numero de Recibo: ";
            cin >> nR;
            system("cls");
            pos = auxArchivoPago.buscarRecibo(nR);
            if(pos < 0)
            {
                cout<<"No existe un recibo con ese numero"<<endl;
                system("pause");
            }
            else
            {
                regPago = auxArchivoPago.leerRegistro(pos);

                cout << "Cliente: " << buscarApellido(regPago.getDni()) << ", " << buscarNombre(regPago.getDni()) << endl << endl;
                cout << left;
                cout << setw(20) << "Numero de Recibo";
                cout << setw(20) << "DNI";
                cout << setw(10) << "Importe";
                cout << setw(15) << "Fecha Recibo" << endl;
                regPago.Mostrar();

                cout << "El comprobante seleccionado sera anulado." << endl;
                cout << "Confirma??? S/N" << endl;
                cin >> confirmacion;

                if (confirmacion == 's' || confirmacion == 'S')
                {
                    regPago.setActivo(false);
                    auxArchivoPago.sobreEscribirRegistro(regPago, pos);

                    sumarDeuda(regPago.getDni(), regPago.getImporte());

                    cout << "Comprobante anulado exitosamente." << endl;
                }
                else
                {
                    system("cls");
                    cout << "El comprobante no ha sido anulado." << endl;
                }
                system("pause");
                system("cls");
            }
            break;
        }
        system("cls");
    }
    while (opcionPagos != 0);
}

void MenuManager::ModuloBackUp()
{
    int op;
    do
    {
        cout << "MODULO BACK UP" << endl;
        cout << "------------------------------" << endl;
        cout << "1- Hacer copia de seguridad." << endl;
        cout << "2- Restaurar copia de seguridad." << endl << endl;
        cout << "0- Volver al menu principal." << endl;
        cin >> op;
        switch(op)
        {
        case 1:
            system("cls");
            MenuBackUp();
            break;
        case 2:
            system("cls");
            MenuRestaurarArchivo();
            break;
        }
    }
    while(op != 0);
}

void MenuManager::MenuBackUp()
{
    int op;
    do
    {
        cout << "HACER BACK UP DE ARCHIVO" << endl;
        cout << "------------------------------" << endl;
        cout << "1- Hacer copia de seguridad de Articulos." << endl;
        cout << "2- Hacer copia de seguridad de Clientes." << endl;
        cout << "3- Hacer copia de seguridad de Pagos." << endl;
        cout << "4- Hacer copia de seguridad de Ventas." << endl << endl;
        cout << "0- Volver al menu principal." << endl;
        cin >> op;
        switch(op)
        {
        case 1:
            system("cls");
            hacerBackupArticulos();
            break;
        case 2:
            system("cls");
            hacerBackupClientes();
            break;
        case 3:
            system("cls");
            hacerBackupPagos();
            break;
        case 4:
            system("cls");
            hacerBackupVentas();
            break;
        }
    }
    while(op!=0);
}

void MenuManager::MenuRestaurarArchivo()
{
    int op;
    do
    {
        cout << "RESTAURAR COPIA DE SEGURIDAD" << endl;
        cout << "------------------------------" << endl;
        cout << "1- Restaurar copia de seguridad de Articulos." << endl;
        cout << "2- Restaurar copia de seguridad de Clientes." << endl;
        cout << "3- Restaurar copia de seguridad de Pagos." << endl;
        cout << "4- Restaurar copia de seguridad de Ventas." << endl << endl;
        cout << "0- Volver al menu principal." << endl;
        cin >> op;
        switch(op)
        {
        case 1:
            system("cls");
            restaurarCopiaArticulos();
            break;
        case 2:
            system("cls");
            restaurarCopiaClientes();
            break;
        case 3:
            system("cls");
            restaurarCopiaPagos();
            break;
        case 4:
            system("cls");
            restaurarCopiaVentas();
            break;
        }
    }
    while(op!=0);
}

int MenuManager::sumarStock(int codigoArticulo, int cantidadArticulo)
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

void MenuManager::ventasMensualesProductos()
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

void MenuManager::cobrosMensualesTipo()
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

void MenuManager::exportarClientes()
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

void MenuManager::exportarCtasCtes()
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

void MenuManager::hacerBackupArticulos()
{
    ArchivoArticulo auxArchivoArticulo("articulos.dat");
    ArchivoArticulo articuloBkp("articulos.bkp");
    int cantArticulos = auxArchivoArticulo.contarRegistros();

    Articulo *vec = new Articulo[cantArticulos];
    if(vec==nullptr)
    {
        cout << "Falla en realizar backup" << endl;
        return;
    }

    auxArchivoArticulo.leerRegistro(vec, cantArticulos);
    articuloBkp.vaciar();
    if(articuloBkp.guardar(vec, cantArticulos))
    {
        cout << "Backup realizado correctamente" << endl;
    }
    else
    {
        cout << "Falla al realizar el backup" << endl;
    }

    delete []vec;
}

void MenuManager::hacerBackupClientes()
{
    ArchivoCliente auxArchivoCliente("clientes.dat");
    ArchivoCliente clientesBkp("clientes.bkp");
    int cantClientes = auxArchivoCliente.contarRegistros();

    Cliente *vec = new Cliente[cantClientes];
    if(vec==nullptr)
    {
        cout << "Falla en realizar backup" << endl;
        return;
    }

    auxArchivoCliente.leerRegistro(vec, cantClientes);
    clientesBkp.vaciar();
    if(clientesBkp.guardar(vec, cantClientes))
    {
        cout << "Backup realizado correctamente" << endl;
    }
    else
    {
        cout << "Falla al realizar el backup" << endl;
    }

    delete []vec;
}

void MenuManager::hacerBackupPagos()
{
    ArchivoPago auxArchivoPago("pagos.dat");
    ArchivoPago pagosBkp("pagos.bkp");
    int cantPagos = auxArchivoPago.contarRegistros();

    Pago *vec = new Pago[cantPagos];
    if(vec==nullptr)
    {
        cout << "Falla en realizar backup" << endl;
        return;
    }

    auxArchivoPago.leerRegistro(vec, cantPagos);
    pagosBkp.vaciar();
    if(pagosBkp.guardar(vec, cantPagos))
    {
        cout << "Backup realizado correctamente" << endl;
    }
    else
    {
        cout << "Falla al realizar el backup" << endl;
    }

    delete []vec;
}

void MenuManager::hacerBackupVentas()
{
    ArchivoVenta auxArchivoVenta("ventas.dat");
    ArchivoVenta ventasBkp("ventas.bkp");
    int cantVentas = auxArchivoVenta.contarRegistros();

    Venta *vec = new Venta[cantVentas];
    if(vec==nullptr)
    {
        cout << "Falla en realizar backup" << endl;
        return;
    }

    auxArchivoVenta.leerRegistro(vec, cantVentas);
    ventasBkp.vaciar();
    if(ventasBkp.guardar(vec, cantVentas))
    {
        cout << "Backup realizado correctamente" << endl;
    }
    else
    {
        cout << "Falla al realizar el backup" << endl;
    }

    delete []vec;
}

void MenuManager::restaurarCopiaArticulos()
{
    ArchivoArticulo auxArchivoArticulo("articulos.dat");
    ArchivoArticulo articuloBkp("articulos.bkp");
    int cantArticulos = articuloBkp.contarRegistros();

    Articulo *vec = new Articulo[cantArticulos];
    if(vec==nullptr)
    {
        cout << "Falla en restaurar backup" << endl;
        return;
    }

    articuloBkp.leerRegistro(vec, cantArticulos);
    auxArchivoArticulo.vaciar();
    if(auxArchivoArticulo.guardar(vec,cantArticulos))
    {
        cout << "Backup restaurado correctamente" << endl;
    }
    else
    {
        cout << "Falla al restaurar el backup" << endl;
    }
    delete []vec;
}

void MenuManager::restaurarCopiaClientes()
{
    ArchivoCliente auxArchivoCliente("clientes.dat");
    ArchivoCliente clienteBkp("clientes.bkp");
    int cantClientes = clienteBkp.contarRegistros();

    Cliente *vec = new Cliente[cantClientes];
    if(vec==nullptr)
    {
        cout << "Falla en restaurar backup" << endl;
        return;
    }

    clienteBkp.leerRegistro(vec, cantClientes);
    auxArchivoCliente.vaciar();
    if(auxArchivoCliente.guardar(vec,cantClientes))
    {
        cout << "Backup restaurado correctamente" << endl;
    }
    else
    {
        cout << "Falla al restaurar el backup" << endl;
    }
    delete []vec;
}

void MenuManager::restaurarCopiaPagos()
{
    ArchivoPago auxArchivoPago("pagos.dat");
    ArchivoPago pagosBkp("pagos.bkp");
    int cantPagos = pagosBkp.contarRegistros();

    Pago *vec = new Pago[cantPagos];
    if(vec==nullptr)
    {
        cout << "Falla en restaurar backup" << endl;
        return;
    }

    pagosBkp.leerRegistro(vec, cantPagos);
    auxArchivoPago.vaciar();
    if(auxArchivoPago.guardar(vec,cantPagos))
    {
        cout << "Backup restaurado correctamente" << endl;
    }
    else
    {
        cout << "Falla al restaurar el backup" << endl;
    }
    delete []vec;
}

void MenuManager::restaurarCopiaVentas()
{
    ArchivoVenta auxArchivoVenta("ventas.dat");
    ArchivoVenta ventasBkp("ventas.bkp");
    int cantVentas = ventasBkp.contarRegistros();

    Venta *vec = new Venta[cantVentas];
    if(vec==nullptr)
    {
        cout << "Falla en restaurar backup" << endl;
        return;
    }

    ventasBkp.leerRegistro(vec, cantVentas);
    auxArchivoVenta.vaciar();
    if(auxArchivoVenta.guardar(vec,cantVentas))
    {
        cout << "Backup restaurado correctamente" << endl;
    }
    else
    {
        cout << "Falla al restaurar el backup" << endl;
    }
    delete []vec;
}

void MenuManager::cambiarLimiteDeuda()
{
    char dni[12];
    float nuevoLimite;
    ArchivoCliente auxArchivoCliente("clientes.dat");
    Cliente regCliente;
    int canClientes = auxArchivoCliente.contarRegistros();
    bool bandera = false;

    cout << "Ingresar DNI del cliente: ";
    cargarCadena(dni, 11);

    for(int x=0;x<canClientes;x++){
        regCliente = auxArchivoCliente.leerRegistro(x);
        if(!strcmp(regCliente.getDni(),dni)){
            cout << "Ingresar nuevo limite: ";
            cin >> nuevoLimite;
            regCliente.setMontoMaximo(nuevoLimite);
            bandera = true;
        }
        auxArchivoCliente.sobreEscribirRegistro(regCliente,x);
    }
    if(bandera){
        cout << "Nuevo limite modificado con exito." << endl;
    }
    else{
        cout << "No existe cliente con ese DNI" << endl;
    }
}

void MenuManager::MenuDespedida()
{
    system("cls");
    cout << "____________________________________________________________" << endl << endl;
    cout << "        Muchas gracias por utilizar nuestro programa!!!" << endl;
    cout << "____________________________________________________________" << endl << endl;
}
