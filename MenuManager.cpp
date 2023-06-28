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
#include "ArchivoDetalleFactura.h"
#include "DetalleFactura.h"
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
                auxArchivoCliente.escribirRegistro();
            break;
        case 2:
            system("cls");
            auxArchivoCliente.listarTodos();
            break;
        case 3:
            system("cls");
            auxArchivoCliente.mostrarXDni();
            break;
        case 4:
            system("cls");
            auxArchivoCliente.borrarCliente();
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

void MenuManager::ModuloArticulos()
{
    int opcionMenu;

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
            auxArchivoArticulo.escribirRegistro();
            system("pause");
            break;
        case 2:
            system("cls");
            auxArchivoArticulo.listarTodos();
            break;
        case 3:
            system("cls");
            auxArchivoArticulo.buscarXCodigo();
            break;
        case 4:
            system("cls");
            auxArchivoArticulo.borrar();
            break;
        case 5:
            system("cls");
            auxArchivoArticulo.consultarStockXCodigo();
            break;
        case 6:
            system("cls");
            auxArchivoArticulo.cargarStock();
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

void MenuManager::ModuloVentas()
{
    int opcionMenu;

    ArchivoVenta auxArchivoVenta("ventas.dat");

    do
    {
        cout << "MODULO VENTAS" << endl;
        cout << "------------------------------" << endl;
        cout << "1- Cargar nueva." << endl;
        cout << "2- Listar por cliente." << endl;
        cout << "3- Listar todas por mes." << endl;
        cout << "4- Listar por cliente por mes." << endl;
        cout << "5- Imprimir por pantalla una factura." << endl;
        cout << "6- Anular venta." << endl << endl;
        cout << "0- Volver al menu principal." << endl;
        cin >> opcionMenu;
        switch(opcionMenu)
        {
        case 1:
            system("cls");
            auxArchivoVenta.escribirRegistro();
            break;
        case 2:
            system("cls");
            auxArchivoVenta.listarXCliente();
            break;
        case 3:
            system("cls");
            auxArchivoVenta.listarXMes();
            break;
        case 4:
            system("cls");
            auxArchivoVenta.listarXClienteXMes();
            break;
        case 5:
            system("cls");
            auxArchivoVenta.imprimirPorPantalla();
            break;
        case 6:
            system("cls");
            auxArchivoVenta.anularVenta();
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
    ArchivoCliente auxArchivoCliente("clientes.dat");
    ArchivoVenta auxArchivoVenta("ventas.dat");

    do
    {
        cout << "MODULO PAGOS" << endl;
        cout << "------------------------------" << endl;
        cout << "1- Cargar ." << endl;
        cout << "2- Listar por cliente." << endl;
        cout << "3- Listar todos por mes." << endl;
        cout << "4- Imprimir por pantalla un recibo." << endl;
        cout << "5- Anular pago." << endl << endl;
        cout << "0- Volver al menu principal." << endl;
        cin >> opcionPagos;
        switch(opcionPagos)
        {
        case 1:
            system("cls");
            auxArchivoPago.escribirRegistro();
            break;
        case 2:
            system("cls");
            auxArchivoPago.listarXCliente();
            break;
        case 3:
            system("cls");
            auxArchivoPago.listarTodosXMes();
            break;
        case 4:
            system("cls");
            auxArchivoPago.imprimirPorPantalla();
            break;
        case 5:
            system("cls");
            auxArchivoPago.anular();
            break;
        }
        system("cls");
    }
    while (opcionPagos != 0);
}

void MenuManager::ModuloReportes()
{
    int opcionMenu;

    ArchivoCliente auxArchivoCliente("clientes.dat");

    do
    {
        cout << "MODULO REPORTES" << endl;
        cout << "------------------------------" << endl << endl;
        cout << "Listados:" << endl;
        cout << "1- Listar saldos deudores por DNI." << endl;
        cout << "2- Listar todos los saldos deudores." << endl;
        cout << "3- Listar movimientos totales." << endl;
        cout << "4- Listar movimientos totales por cliente." << endl<< endl;
        cout << "Informes:" << endl;
        cout << "5- Cantidad de ventas mensuales por producto." << endl;
        cout << "6- Cantidad de cobranzas por formas de pago." << endl << endl;
        cout << "Reportes:" << endl;
        cout << "7- Exportar listado de clientes a Excel." << endl;
        cout << "8- Exportar cuentas corrientes a Excel." << endl;
        cout << "9- Exportar listado de articulos a Excel." << endl << endl;
        cout << "0- Volver al menu principal." << endl;
        cin >> opcionMenu;
        switch(opcionMenu)
        {
        case 1:
            system("cls");
            auxArchivoCliente.listarDeudoresXDni();
            break;
        case 2:
            system("cls");
            auxArchivoCliente.listarDeudores();
            break;
        case 3:
            system("cls");
            auxArchivoCliente.listarMovimientos();
            break;
        case 4:
            system("cls");
            auxArchivoCliente.listarMovimientosXDni();
            break;
        case 5:
            system("cls");
            ventasMensualesProductos();
            break;
        case 6:
            system("cls");
            cobrosMensualesTipo();
            break;
        case 7:
            system("cls");
            exportarClientes();
            break;
        case 8:
            system("cls");
            exportarCtasCtes();
            break;
        case 9:
            system("cls");
            exportarArticulos();
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
        system("cls");
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
            system("pause");
            break;
        case 2:
            system("cls");
            hacerBackupClientes();
            system("pause");
            break;
        case 3:
            system("cls");
            hacerBackupPagos();
            system("pause");
            break;
        case 4:
            system("cls");
            hacerBackupVentas();
            system("pause");
            break;
        }
        system("cls");
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
            system("pause");
            break;
        case 2:
            system("cls");
            restaurarCopiaClientes();
            system("pause");
            break;
        case 3:
            system("cls");
            restaurarCopiaPagos();
            system("pause");
            break;
        case 4:
            system("cls");
            restaurarCopiaVentas();
            system("pause");
            break;
        }
        system("cls");
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

    ArchivoArticulo auxArchivoArticulo("articulos.dat");
    Articulo regArticulo;
    int cantArticulos = auxArchivoArticulo.contarRegistros();

    ArchivoDetalleFactura auxArchivoDetalleFactura("detalleFacturas.dat");
    DetalleFactura regDetalleFactura;
    int cantDetalles = auxArchivoDetalleFactura.contarRegistros();

    cout << "Mes: ";
    cin >> mes;
    cout << "Anio: ";
    cin >> anio;

    for (int i=0; i<cantArticulos; i++)
    {
        cantArticulo = 0;

        regArticulo = auxArchivoArticulo.leerRegistro(i);

        for (int j=0; j<cantDetalles; j++)
        {
            regDetalleFactura = auxArchivoDetalleFactura.leerRegistro(j);

            if (regDetalleFactura.getNumeroFactura() != 0 && regDetalleFactura.getCodigoArticulo() == regArticulo.getCodigoArticulo() && regDetalleFactura.getFechaVenta().getAnio() == anio && regDetalleFactura.getFechaVenta().getMes() == mes)
            {
                cantArticulo += regDetalleFactura.getCantidadArticulo();
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

            if (regPago.getActivo() && regPago.getFormaPago() == i+1 && regPago.getFechaPago().getAnio() == anio &&regPago.getFechaPago().getMes() == mes)
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

void MenuManager::exportarArticulos()
{
    ArchivoArticulo auxArchivoArticulo("articulos.dat");
    Articulo regArticulo;
    int cantArticulos = auxArchivoArticulo.contarRegistros();

    ofstream archivoArticulos("articulos.csv", ios::out);
    if(!archivoArticulos)
    {
        cout << "No se pudo crear el archivo" << endl;
    }
    else
    {
        for(int x=0; x<cantArticulos; x++)
        {
            regArticulo = auxArchivoArticulo.leerRegistro(x);
            if(x==0)
            {
                archivoArticulos << "Descripcion" << ";" << "Stock" << ";" << "Precio unitario" << "Codigo" << endl;
            }
            archivoArticulos << regArticulo.getDescripcion() << ";" << regArticulo.getStock() << ";" << regArticulo.getPrecioUnitario() << ";" << regArticulo.getCodigoArticulo() << endl;
        }
        archivoArticulos.close();
        cout << "Archivo creado con exito" << endl;
        cout << cantArticulos << " articulos exportados a excel" << endl;
        system("pause");
    }
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
            if (regVenta.getActiva())
            {
                if (regVenta.getPaga())
                {
                    archivoctasctes << "PAGA" << endl;
                }
                else
                {
                    archivoctasctes << "PENDIENTE" << endl;
                }
            }
            else
            {
                archivoctasctes << "ANULADA" << endl;
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

    if(cantArticulos<1){
        cout << "No hay registros para guardar." << endl;
        return;
    }

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

    if(cantClientes<1){
        cout << "No hay registros para guardar." << endl;
        return;
    }

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

    if(cantPagos<1){
        cout << "No hay registros para guardar." << endl;
        return;
    }

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

    if(cantVentas<1){
        cout << "No hay registros para guardar." << endl;
        return;
    }

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

    if(cantArticulos<1){
        cout << "No hay archivo para restaurar." << endl;
        return;
    }

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

    if(cantClientes<1){
        cout << "No hay archivo para restaurar." << endl;
        return;
    }

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

    if(cantPagos<1){
        cout << "No hay archivo para restaurar." << endl;
        return;
    }

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

    if(cantVentas<1){
        cout << "No hay archivo para restaurar." << endl;
        return;
    }

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

    for(int x=0; x<canClientes; x++)
    {
        regCliente = auxArchivoCliente.leerRegistro(x);
        if(!strcmp(regCliente.getDni(),dni))
        {
            cout << "Ingresar nuevo limite: ";
            cin >> nuevoLimite;
            while ( nuevoLimite < regCliente.getSaldoDeudor() )
            {
                cout << "El limite no puede ser menor al saldo deudor actual" << endl;
                cout << "Saldo deudor actual: $" << regCliente.getSaldoDeudor() << endl << endl;
                cout << "Ingresar nuevo limite: " << endl;
                cin >> nuevoLimite;
            }
            regCliente.setMontoMaximo(nuevoLimite);
            bandera = true;
        }
        auxArchivoCliente.sobreEscribirRegistro(regCliente,x);
    }
    if(bandera)
    {
        cout << "Nuevo limite modificado con exito." << endl;
    }
    else
    {
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
