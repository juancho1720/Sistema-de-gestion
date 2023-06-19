#include <iostream>
#include <string.h>

using namespace std;

#include "ArchivoBackUp.h"

ArchivoBackUp::ArchivoBackUp(const char *n)
{
    strcpy(nombre, n);
}

Articulo ArchivoBackUp::leerRegistro(int pos)
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

int ArchivoBackUp::contarRegistros()
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

void ArchivoBackUp::escribirRegistro(Articulo reg)
{
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

int ArchivoBackUp::sobreEscribirRegistro(Articulo reg, int pos)
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
