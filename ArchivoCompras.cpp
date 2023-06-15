#include "ArchivoCompras.h"

bool ArchivoCompras::escribirRegistro()
{
    Compra reg;
    FILE *p;
    p = fopen(nombre,"ab");
    if(p == NULL)
    {
        return false;
    }
    reg.Cargar();
    bool escribio = fwrite(&reg, sizeof reg, 1, p);
    fclose(p);
    return escribio;
}


bool ArchivoCompras::listarArchivo()
{
    Compra reg;
    FILE *p;
    p = fopen(nombre,"rb");
    if(p == NULL)
    {
        return false;
    }
    while(fread(&reg, sizeof reg, 1, p))
    {
        reg.Mostrar();
        cout << endl;
    }
    fclose(p);
    return true;
}


Compra ArchivoCompras::leerRegistro(int pos)
{
    Compra reg;
    FILE *p;
    p=fopen(nombre, "rb");
    if(p==NULL) return reg;
    fseek(p, sizeof reg*pos,0);
    fread(&reg, sizeof reg,1, p);
    fclose(p);
    return reg;
}


int ArchivoCompras::getCantidadRegistros()
{
    FILE *p;
    p=fopen(nombre, "rb");
    if(p==NULL) return -1;
    fseek(p, 0,2);
    int tam=ftell(p);
    fclose(p);
    return tam/sizeof(Compra);
}


int ArchivoCompras::editarRegistro(Compra reg, int pos)
{
    FILE *p;
    p = fopen(nombre,"rb+");
    if(p == NULL)
    {
        return -1;
    }
    fseek(p,pos*sizeof(Compra),0);
    int valor = fwrite(&reg,sizeof reg,1,p);
    fclose(p);
    return valor;
}













