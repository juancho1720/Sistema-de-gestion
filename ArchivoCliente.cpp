#include <iostream>
#include <string.h>

using namespace std;

#include "ArchivoCliente.h"

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
    else
    {
        system("cls");
        cout << "Cliente existente." << endl;
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
