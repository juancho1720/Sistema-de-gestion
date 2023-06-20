#include <iostream>
#include <string.h>

using namespace std;

#include "ArchivoVenta.h"

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

void ArchivoVenta::escribirRegistro(Venta reg)
{
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
