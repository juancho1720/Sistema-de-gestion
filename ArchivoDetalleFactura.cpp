#include <iostream>
#include <string.h>

using namespace std;

#include "ArchivoDetalleFactura.h"

ArchivoDetalleFactura::ArchivoDetalleFactura(const char *n)
{
    strcpy(nombre, n);
}

DetalleFactura ArchivoDetalleFactura::leerRegistro(int pos)
{
    DetalleFactura reg;
    FILE *p = fopen(nombre, "rb");
    if(p == NULL)
    {
        return reg;
    }
    fseek(p, sizeof(DetalleFactura)*pos,0);
    fread(&reg, sizeof reg,1, p);
    fclose(p);
    return reg;
}

int ArchivoDetalleFactura::contarRegistros()
{
    FILE *p = fopen(nombre, "rb");
    if(p == NULL)
    {
        return -1;
    }
    fseek(p, 0,2);
    int tam = ftell(p);
    fclose(p);
    return tam/sizeof(DetalleFactura);
}

void ArchivoDetalleFactura::escribirRegistro(DetalleFactura reg)
{
    char op;
    FILE *p = fopen("detalleFacturas.dat","ab");
    if(p == NULL)
    {
        cout << "Error archivo.";
    }
    fwrite(&reg, sizeof reg, 1, p);
    fclose(p);

}

int ArchivoDetalleFactura::sobreEscribirRegistro(DetalleFactura reg, int pos)
{
    FILE *p = fopen(nombre,"rb+");
    if(p == NULL)
    {
        return -1;
    }
    fseek(p, pos*sizeof (DetalleFactura), 0);
    int valor = fwrite(&reg, sizeof reg, 1,p);
    fclose(p);
    return valor;
}

void ArchivoDetalleFactura::leerRegistro(DetalleFactura *vec, int cantidadRegistrosALeer)
{
    FILE *p = fopen(nombre, "rb");
    if (p == NULL)
    {
        return ;
    }

    fread(vec, sizeof(DetalleFactura), cantidadRegistrosALeer, p);
    fclose(p);
}
