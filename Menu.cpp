#include "Menu.h"
#include "ArchivoClientes.h"
#include "Cliente.h"
#include "ArchivoProveedores.h"
#include "Proveedor.h"
#include "ArchivoArticulos.h"
#include "Articulo.h"
#include "ArchivoCompras.h"
#include "Venta.h"
#include "ArchivoVentas.h"

void Menu::Mostrar()
 {
        ArchivoClientes auxCliente("clientes.dat");
        Cliente regCliente;
        ArchivoProveedores auxProveedor("proveedores.dat");
        Proveedor regProveedor;
        ArchivoArticulos auxArticulos("articulos.dat");
        Articulo regArticulo;
        ArchivoCompras auxCompras("compras.dat");
        Compra regCompra;
        ArchivoVentas auxVentas("ventas.dat");
        Venta regVenta;
        char dni[12];
        char cuit[14];
        int pos;
        int codigo;
        int opcionPrincipal, opcionClientes, opcionProveedores, opcionArticulos, opcionCompra, opcionVenta;
        do
        {
            system("cls");
            cout << "---------MENU PRINCIPAL---------" << endl;
            cout << "1- Clientes." << endl;
            cout << "2- Reportes." << endl;
            cout << "3- Articulos." << endl;
            cout << "4- Cuentas corrientes." << endl;
            cout << "5- Ventas." << endl << endl;
            cout << "0- Salir." << endl;
            cout << "-------------------------------" << endl;
            cout << "Ingrese la opcion deseada: (1/2/3/4/5/0)" << endl;
            cin >> opcionPrincipal;
            switch(opcionPrincipal)
            {
            case 1:
                do
                {
                    system("cls");
                    cout << "---------MENU CLIENTES---------" << endl;
                    cout << "1- Cargar nuevo cliente." << endl;
                    cout << "2- Mostrar todos los clientes." << endl;
                    cout << "3- Buscar cliente por DNI." << endl;
                    cout << "4- Borrar cliente por DNI." << endl;
                    cout << "5- Listar cuenta corriente cliente por DNI. (EN DESARROLLO)" << endl << endl;
                    cout << "0- Volver al menu principal." << endl;
                    cout << "-------------------------------" << endl;
                    cout << "Ingrese la opcion deseada: (1/2/3/4/0)" << endl;
                    cin >> opcionClientes;
                    switch(opcionClientes)
                    {
                    case 1:
                        system("cls");
                        auxCliente.escribirRegistro();
                        system("pause");
                        break;
                    case 2:
                        system("cls");
                        auxCliente.listarArchivo();
                        system("pause");
                        break;
                    case 3:
                        system("cls");
                        cout << "DNI: ";
                        cargarCadena(dni, 11);
                        system("cls");
                        pos = auxCliente.buscarDni(dni);
                        if(pos == -1)
                        {
                            cout<<"No existe un cliente con ese numero de DNI"<<endl;
                            system("pause");
                        }
                        else
                        {
                            regCliente = auxCliente.leerRegistro(pos);
                            regCliente.Mostrar();
                            system("pause");
                        }
                        break;
                    case 4:
                        system("cls");
                        cout << "DNI: ";
                        cargarCadena(dni, 11);
                        system("cls");
                        pos = auxCliente.buscarDni(dni);
                        if(pos == -1)
                        {
                            cout<<"No existe un cliente con ese numero de DNI"<<endl;
                            system("pause");
                        }
                        else
                        {
                            regCliente = auxCliente.leerRegistro(pos);
                            regCliente.setEstado(false);
                            auxCliente.editarRegistro(regCliente, pos);
                            system("pause");
                        }
                        break;
                    case 5:
                        system("cls");
                        //
                        system("pause");
                        break;
                    }
                    system("cls");
                }
                while(opcionClientes!=0);
                break;
            case 2:
                do
                {
                    system("cls");
                    cout << "---------MENU PROVEEDORES---------" << endl;
                    cout << "1- Cargar nuevo proveedor." << endl;
                    cout << "2- Mostrar todos los proveedores." << endl;
                    cout << "3- Buscar proveedor por CUIT." << endl;
                    cout << "4- Borrar proveedor por CUIT." << endl;
                    cout << "5- Listar cuenta corriente proveedor por CUIT. (EN DESARROLLO)" << endl << endl;
                    cout << "0- Volver al menu principal." << endl;
                    cout << "-------------------------------" << endl;
                    cout << "Ingrese la opcion deseada: (1/2/3/4/0)" << endl;
                    cin >> opcionProveedores;
                    switch(opcionProveedores)
                    {
                    case 1:
                        system("cls");
                        auxProveedor.escribirRegistro();
                        system("pause");
                        break;
                    case 2:
                        system("cls");
                        auxProveedor.listarArchivo();
                        system("pause");
                        break;
                    case 3:
                        system("cls");
                        cout << "CUIT: ";
                        cargarCadena(cuit, 13);
                        system("cls");
                        pos = auxProveedor.buscarCuit(cuit);
                        if(pos == -1)
                        {
                            cout<<"No existe un proveedor con ese numero de CUIT"<<endl;
                            system("pause");
                        }
                        else
                        {
                            regProveedor = auxProveedor.leerRegistro(pos);
                            regProveedor.Mostrar();
                            system("pause");
                        }
                        break;
                    case 4:
                        system("cls");
                        cout << "CUIT: ";
                        cargarCadena(cuit, 13);
                        system("cls");
                        pos = auxProveedor.buscarCuit(cuit);
                        if(pos == -1)
                        {
                            cout<<"No existe un proveedor con ese numero de CUIT"<<endl;
                            system("pause");
                        }
                        else
                        {
                            regProveedor = auxProveedor.leerRegistro(pos);
                            regProveedor.setEstado(false);
                            auxProveedor.editarRegistro(regProveedor, pos);
                            system("pause");
                        }
                        break;
                    case 5:
                        system("cls");
                        //
                        system("pause");
                        break;
                    }
                    system("cls");
                }
                while(opcionProveedores!=0);
                break;
            case 3:
                do
                {
                    system("cls");
                    cout << "---------MENU ARTICULOS---------" << endl;
                    cout << "1- Cargar nuevo articulo." << endl;
                    cout << "2- Mostrar todos los articulos." << endl;
                    cout << "3- Buscar articulo por codigo." << endl;
                    cout << "4- Borrar articulo por codigo." << endl << endl;
                    cout << "0- Volver al menu principal." << endl;
                    cout << "-------------------------------" << endl;
                    cout << "Ingrese la opcion deseada: (1/2/3/4/0)" << endl;
                    cin >> opcionArticulos;
                    switch(opcionArticulos)
                    {
                    case 1:
                        system("cls");
                        auxArticulos.escribirRegistro();
                        system("pause");
                        break;
                    case 2:
                        system("cls");
                        auxArticulos.listarArchivo();
                        system("pause");
                        break;
                    case 3:
                        system("cls");
                        cout << "Codigo: ";
                        cin >> codigo;
                        system("cls");
                        pos = auxArticulos.buscarCodigo(codigo);
                        if(pos == -1)
                        {
                            cout<<"No existe un articulo con ese numero de codigo"<<endl;
                            system("pause");
                        }
                        else
                        {
                            regArticulo = auxArticulos.leerRegistro(pos);
                            regArticulo.Mostrar();
                            system("pause");
                        }
                        break;
                    case 4:
                        system("cls");
                        cout << "Codigo: ";
                        cin >> codigo;
                        system("cls");
                        pos = auxArticulos.buscarCodigo(codigo);
                        if(pos == -1)
                        {
                            cout<<"No existe un articulo con ese numero de codigo"<<endl;
                            system("pause");
                        }
                        else
                        {
                            regArticulo = auxArticulos.leerRegistro(pos);
                            regArticulo.setEstado(false);
                            auxArticulos.editarRegistro(regArticulo, pos);
                            system("pause");
                        }
                        break;
                    }
                    system("cls");
                }
                while(opcionArticulos!=0);
                break;
            case 4:
                do
                {
                    system("cls");
                    cout << "---------MENU COMPRAS---------" << endl;
                    cout << "1- Cargar nueva compra." << endl;
                    cout << "2- Mostrar todas las compras." << endl;
                    cout << "3- Listar cuenta corriente de proveedor por CUIT / Nombre - A DEFINIR. (EN DESARROLLO)" << endl;
                    cout << "4- Anular compra por factura. (EN DESARROLLO)" << endl << endl;
                    cout << "0- Volver al menu principal." << endl;
                    cout << "-------------------------------" << endl;
                    cout << "Ingrese la opcion deseada: (1/2/3/4/0)" << endl;
                    cin >> opcionCompra;
                    switch(opcionCompra)
                    {
                    case 1:
                        system("cls");
                        auxCompras.escribirRegistro();
                        system("pause");
                        break;
                    case 2:
                        system("cls");
                        auxCompras.listarArchivo();
                        system("pause");
                        break;
                    case 3:
                        system("cls");
                        //
                        system("pause");
                        break;
                    case 4:
                        system("cls");
                        //
                        system("pause");
                        break;
                    }
                    system("cls");
                }
                while(opcionCompra!=0);
                break;
            case 5:
                do
                {
                    system("cls");
                    cout << "---------MENU VENTAS---------" << endl;
                    cout << "1- Cargar nueva venta." << endl;
                    cout << "2- Mostrar todas las ventas." << endl;
                    cout << "3- Listar cuenta corriente de CLIENTE por DNI / NOMBRE. - A DEFINIR. (EN DESARROLLO)" << endl;
                    cout << "4- Anular venta por factura. (EN DESARROLLO)" << endl << endl;
                    cout << "0- Volver al menu principal." << endl;
                    cout << "-------------------------------" << endl;
                    cout << "Ingrese la opcion deseada: (1/2/3/4/0)" << endl;
                    cin >> opcionVenta;
                    switch(opcionVenta)
                    {
                    case 1:
                        system("cls");
                        auxVentas.escribirRegistro();
                        system("pause");
                        break;
                    case 2:
                        system("cls");
                        auxVentas.listarArchivo();
                        system("pause");
                        break;
                    case 3:
                        system("cls");
                        //
                        system("pause");
                        break;
                    case 4:
                        system("cls");
                        //
                        system("pause");
                        break;
                    }
                    system("cls");
                }
                while(opcionVenta!=0);
                break;
                system("cls");
            }
        }
        while(opcionPrincipal!=0);
    }

