#include <iostream>
#include <string.h>

using namespace std;

#include "ArchivoPago.h"

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

void ArchivoPago::escribirRegistro(Pago reg)
{
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
