#include <iostream>
#include <string.h>
#include <iomanip>

using namespace std;

#include "ArchivoArticulo.h"
#include "MenuManager.h"

ArchivoArticulo::ArchivoArticulo(const char *n)
{
    strcpy(nombre, n);
}

Articulo ArchivoArticulo::leerRegistro(int pos)
{
    Articulo reg;
    FILE *p = fopen(nombre, "rb");
    if(p == NULL)
    {
        return reg;
    }
    fseek(p, sizeof(Articulo)*pos,0);
    fread(&reg, sizeof reg,1, p);
    fclose(p);
    return reg;
}

int ArchivoArticulo::contarRegistros()
{
    FILE *p = fopen(nombre, "rb");
    if(p == NULL)
    {
        return -1;
    }
    fseek(p, 0,2);
    int tam = ftell(p);
    fclose(p);
    return tam/sizeof(Articulo);
}

void ArchivoArticulo::escribirRegistro()
{
    Articulo reg;
    FILE *p = fopen("articulos.dat","ab");
    if(p == NULL)
    {
        cout << "Error archivo.";
    }
    if (reg.Cargar() == false)
    {
        fwrite(&reg, sizeof reg, 1, p);
        fclose(p);
        system("cls");
        cout << "Articulo agregado exitosamente!!!" << endl;
    }
    else
    {
        cout << "Articulo existente." << endl;
    }
}

void ArchivoArticulo::listarTodos()
{
    Articulo regArticulo;
    ArchivoArticulo auxArchivoArticulo("articulos.dat");
    int cantArticulos = auxArchivoArticulo.contarRegistros();
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
}

void ArchivoArticulo::buscarXCodigo()
{
    int codigo;
    Articulo regArticulo;
    ArchivoArticulo auxArchivoArticulo("articulos.dat");
    cout << "Codigo: ";
    cin >> codigo;
    system("cls");
    int pos = auxArchivoArticulo.buscarCodigo(codigo);
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
}

void ArchivoArticulo::borrar()
{
    int codigo;
    char confirmacion;
    Articulo regArticulo;
    ArchivoArticulo auxArchivoArticulo("articulos.dat");
    cout << "Codigo: ";
    cin >> codigo;
    system("cls");
    int pos = auxArchivoArticulo.buscarCodigo(codigo);
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
}

void ArchivoArticulo::consultarStockXCodigo()
{
    int codigo;
    Articulo regArticulo;
    ArchivoArticulo auxArchivoArticulo("articulos.dat");
    cout << "Codigo: ";
    cin >> codigo;
    system("cls");
    int pos = auxArchivoArticulo.buscarCodigo(codigo);
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
}

void ArchivoArticulo::cargarStock()
{
    int codigo, cantArticulos;
    Articulo regArticulo;
    ArchivoArticulo auxArchivoArticulo("articulos.dat");
    MenuManager menu;
    cout << "Codigo: ";
    cin >> codigo;
    system("cls");
    int pos = auxArchivoArticulo.buscarCodigo(codigo);
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
            menu.sumarStock(codigo, cantArticulos);
            cout << "Unidades agregadas correctamente al stock." << endl;
            system("pause");
        }
        else
        {
            cout << "No hay articulo activos con ese codigo." << endl;
            system("pause");
        }
    }
}

int ArchivoArticulo::buscarCodigo(int c)
{
    Articulo reg;
    FILE *p;
    p = fopen(nombre,"rb");
    if(p == NULL)
    {
        return -2;
    }
    int pos = 0;
    while(fread(&reg, sizeof reg, 1,p) == 1)
    {
        if(reg.getCodigoArticulo()  == c)
        {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}

int ArchivoArticulo::sobreEscribirRegistro(Articulo reg, int pos)
{
    FILE *p = fopen(nombre,"rb+");
    if(p == NULL)
    {
        return -1;
    }
    fseek(p, pos*sizeof (Articulo), 0);
    int valor = fwrite(&reg, sizeof reg, 1,p);
    fclose(p);
    return valor;
}

void ArchivoArticulo::cambiarPrecios()
{
    float nuevoPrecio;
    ArchivoArticulo auxArchivoArticulo("articulos.dat");
    Articulo regArticulo;
    int cantArticulos = auxArchivoArticulo.contarRegistros();
    int opcionMenu, codidoProducto;
    do
    {
        cout << "1- Cambiar todos los precios." << endl;
        cout << "2- Cambiar el precio de un articulo." << endl << endl;
        cout << "0- Volver al menu principal." << endl;
        cin >> opcionMenu;
        switch(opcionMenu)
        {
        case 1:
            system("cls");
            for (int i=0; i<cantArticulos; i++)
            {
                regArticulo = auxArchivoArticulo.leerRegistro(i);

                cout << left;
                cout << setw(20) << "Descripcion";
                cout << setw(15) << "Codigo";
                cout << setw(15) << "Stock";
                cout << setw(20) << "Precio Unitario" << endl;
                cout << "------------------------------------------------------------------------------" << endl;
                regArticulo.Mostrar();
                cout << "------------------------------------------------------------------------------" << endl;
                cout << "Ingrese nuevo precio: " << endl;
                cin >> nuevoPrecio;

                while (nuevoPrecio <= 0)
                {
                    cout << "El precio debe ser mayor a cero." << endl;
                    cout << "Precio Unitario: ";
                    cin >> nuevoPrecio;
                }

                regArticulo.setPrecioUnitario(nuevoPrecio);
                if (auxArchivoArticulo.sobreEscribirRegistro(regArticulo, i) != 0)
                {
                    system("cls");
                    cout << "Precio modificado con exito!!!" << endl;
                }
            }
            break;
        case 2:
            system("cls");
            cout << "Ingrese el codigo del producto:" << endl;
            cin >> codidoProducto;
            for (int i=0; i<cantArticulos; i++)
            {
                regArticulo = auxArchivoArticulo.leerRegistro(i);

                if (regArticulo.getCodigoArticulo() == codidoProducto)
                {
                    cout << left;
                    cout << setw(20) << "Descripcion";
                    cout << setw(15) << "Codigo";
                    cout << setw(15) << "Stock";
                    cout << setw(20) << "Precio Unitario" << endl;
                    cout << "------------------------------------------------------------------------------" << endl;
                    regArticulo.Mostrar();
                    cout << "------------------------------------------------------------------------------" << endl;
                    cout << "Ingrese nuevo precio: " << endl;
                    cin >> nuevoPrecio;

                    regArticulo.setPrecioUnitario(nuevoPrecio);
                    if (auxArchivoArticulo.sobreEscribirRegistro(regArticulo, i) != 0)
                    {
                        system("cls");
                        cout << "Precio modificado con exito!!!" << endl;
                    }
                }
            }
            break;
        }
    }
    while (opcionMenu != 0);


}

void ArchivoArticulo::aumentarPreciosPorcentual()
{
    float nuevoPrecio;

    ArchivoArticulo auxArchivoArticulo("articulos.dat");
    Articulo regArticulo;
    int cantArticulos = auxArchivoArticulo.contarRegistros();

    cout << "Ingrese el porcentaje a aplicar como nuevo precio: " << endl;
    cin >> nuevoPrecio;

    nuevoPrecio = nuevoPrecio/100+1;

    while (nuevoPrecio <= 0)
    {
        cout << "El precio debe ser mayor a cero." << endl;
        cout << "Precio Unitario: ";
        cin >> nuevoPrecio;
    }

    for (int i=0; i<cantArticulos; i++)
    {
        regArticulo = auxArchivoArticulo.leerRegistro(i);

        regArticulo.setPrecioUnitario(regArticulo.getPrecioUnitario()*nuevoPrecio);
        auxArchivoArticulo.sobreEscribirRegistro(regArticulo, i);
    }
    system("cls");
    cout << "Precio modificado con exito!!!" << endl;
}


void ArchivoArticulo::leerRegistro(Articulo *vec, int cantidadRegistrosALeer)
{
    FILE *p = fopen(nombre, "rb");
    if (p == NULL)
    {
        return ;
    }

    fread(vec, sizeof(Articulo), cantidadRegistrosALeer, p);
    fclose(p);
}



bool ArchivoArticulo::guardar(Articulo *vec, int cantidadRegistrosAEscribir)
{
    FILE *p = fopen(nombre, "ab");
    if (p == NULL)
    {
        return false;
    }

    int cantidadRegistrosEscritos = fwrite(vec, sizeof(Articulo), cantidadRegistrosAEscribir, p);
    fclose(p);
    return cantidadRegistrosEscritos == cantidadRegistrosAEscribir;
}


void ArchivoArticulo::vaciar()
{
    FILE *p = fopen(nombre, "wb");
    if (p == NULL)
    {
        return ;
    }
    fclose(p);
}
