#include <iostream>
#include <string.h>
#include <iomanip>

using namespace std;

#include "ArchivoCliente.h"
#include "FuncionesGenerales.h"

ArchivoCliente::ArchivoCliente(const char *n)
{
    strcpy(nombre, n);
}

Cliente ArchivoCliente::leerRegistro(int pos)
{
    Cliente reg;
    FILE *p = fopen(nombre, "rb");
    if(p == NULL)
    {
        return reg;
    }
    fseek(p, sizeof(Cliente)*pos,0);
    fread(&reg, sizeof reg,1, p);
    fclose(p);
    return reg;
}

int ArchivoCliente::contarRegistros()
{
    FILE *p = fopen(nombre, "rb");
    if(p == NULL)
    {
        return -1;
    }
    fseek(p, 0,2);
    int tam = ftell(p);
    fclose(p);
    return tam/sizeof(Cliente);
}

void ArchivoCliente::escribirRegistro(Cliente reg)
{
    FILE *p = fopen("clientes.dat","ab");
    if(p == NULL)
    {
        cout << "Error archivo.";
    }
    if (reg.Cargar() == true)
    {
        fwrite(&reg, sizeof reg, 1, p);
        fclose(p);
        system("cls");
        cout << "Cliente agregado exitosamente!!!" << endl;
        system("pause");
    }
}

void ArchivoCliente::listarTodos()
{
    Cliente regCliente;
    ArchivoCliente auxArchivoCliente("clientes.dat");
    int cantClientes = auxArchivoCliente.contarRegistros();
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
}

void ArchivoCliente::mostrarXDni()
{
    char dni[12];
    Cliente regCliente;
    ArchivoCliente auxArchivoCliente("clientes.dat");
    cout << "DNI: ";
    cargarCadena(dni, 11);
    system("cls");
    int pos = auxArchivoCliente.buscarDni(dni);
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
}

void ArchivoCliente::borrarCliente()
{
    char dni[12];
    char confirmacion;
    Cliente regCliente;
    ArchivoCliente auxArchivoCliente("clientes.dat");
    cout << "DNI: ";
    cargarCadena(dni, 11);
    system("cls");
    int pos = auxArchivoCliente.buscarDni(dni);
    regCliente = auxArchivoCliente.leerRegistro(pos);
    if(pos == -1 || !regCliente.getActivo())
    {
        cout<<"No existe un cliente con ese numero de DNI"<<endl;
        system("pause");
    }
    else
    {
        if(regCliente.getSaldoDeudor() == 0 && regCliente.getSaldoAcreedor() == 0)
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
        }
        else
        {
            system("cls");
            cout << "El cliente tiene saldo acreedor o deudor pendiente y no se puede borrar." << endl;
        }

        system("pause");
    }
}

int ArchivoCliente::buscarDni(const char *d)
{
    Cliente reg;
    FILE *p;
    p = fopen(nombre,"rb");
    if(p == NULL)
    {
        return -2;
    }
    int pos = 0;
    while(fread(&reg, sizeof reg, 1,p) == 1)
    {
        if(strcmp(reg.getDni(),d) == 0)
        {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}

int ArchivoCliente::sobreEscribirRegistro(Cliente reg, int pos)
{
    FILE *p = fopen(nombre,"rb+");
    if(p == NULL)
    {
        return -1;
    }
    fseek(p, pos*sizeof (Cliente), 0);
    int valor = fwrite(&reg, sizeof reg, 1,p);
    fclose(p);
    return valor;
}

void ArchivoCliente::leerRegistro(Cliente *vec, int cantidadRegistrosALeer)
{
    FILE *p = fopen(nombre, "rb");
    if (p == NULL)
    {
        return ;
    }

    fread(vec, sizeof(Cliente), cantidadRegistrosALeer, p);
    fclose(p);
}

bool ArchivoCliente::guardar(Cliente *vec, int cantidadRegistrosAEscribir)
{
    FILE *p = fopen(nombre, "ab");
    if (p == NULL)
    {
        return false;
    }

    int cantidadRegistrosEscritos = fwrite(vec, sizeof(Cliente), cantidadRegistrosAEscribir, p);
    fclose(p);
    return cantidadRegistrosEscritos == cantidadRegistrosAEscribir;
}

void ArchivoCliente::vaciar()
{
    FILE *p = fopen(nombre, "wb");
    if (p == NULL)
    {
        return ;
    }
    fclose(p);
}








