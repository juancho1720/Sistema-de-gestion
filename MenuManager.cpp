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
        cout << "4- Borrar." << endl << endl;
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
            if(pos == -1 || regCliente.getActivo() == false)
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
        cout << "5- Cantidad de ventas mensuales por formas de pago." << endl;
        cout << "6- ." << endl << endl;
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
            importeTotal = 0;
            for(int i=0; i<cantClientes; i++)
            {
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
                                cout << setw(15) << "Sin aplicar";
                            }
                            if (!regPago.getActivo())
                            {
                                cout << setw(15) << "Aplicado";
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
        }
        system("cls");
    }
    while(opcionMenu!=0);
    system("cls");
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
    bool mostrarTitulo = true;
    float importeTotal = 0;
    do
    {
        cout << "MODULO PAGOS" << endl;
        cout << "------------------------------" << endl;
        cout << "1- Cargar ." << endl;
        cout << "2- Listar por cliente. (SIN HACER)" << endl;
        cout << "3- Listar todos por mes." << endl;
        cout << "4- Listar por cliente por mes. (SIN HACER)" << endl;
        cout << "5- Anular pago." << endl << endl;
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

                    if( strcmp(regPago.getDni(), regCliente.getDni()) == 0 && regPago.getFechaPago().getAnio() == anio && regPago.getFechaPago().getMes() == mes && regCliente.getActivo() && !regPago.getActivo())
                    {
                        hayVentas = true;
                        if(mostrarTitulo)
                        {
                            cout << "Cliente: " << regCliente.getApellido() << ", " << regCliente.getNombre() << endl << endl;
                            cout << left;
                            cout << setw(20) << "Numero de Recibo";
                            cout << setw(20) << "DNI";
                            cout << setw(10) << "Importe";
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
            break;
        case 5:
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
            //hacerBackUp();
            break;
        case 2:
            //restaurarBackUp();
            break;
        }
    }
    while(op != 0);
}
