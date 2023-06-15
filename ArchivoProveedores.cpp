#include "ArchivoProveedores.h"

bool ArchivoProveedores::escribirRegistro()
{
    FILE *p;
    p = fopen(nombre,"ab");
    if(p == NULL)
    {
        return false;
    }
    reg.setCodigoProveedor(generarNumeroProveedor());
    reg.Cargar();
    bool escribio = fwrite(&reg, sizeof reg, 1, p);
    fclose(p);
    return escribio;
}


bool ArchivoProveedores::listarArchivo()
{
    Proveedor reg;
    FILE *p;
    p = fopen(nombre,"rb");
    if(p == NULL)
    {
        return false;
    }
    while(fread(&reg, sizeof reg, 1, p) == 1)
    {
        reg.Mostrar();
        cout << endl;
    }
    fclose(p);
    return true;
}


Proveedor ArchivoProveedores::leerRegistro(int pos)
{
    Proveedor reg;
    FILE *p;
    p = fopen(nombre,"rb");
    if(p == NULL)
    {
        return reg;
    }
    fseek(p, pos*sizeof reg, 0);
    FILE *pCli = p;
    int leyo = fread(&reg, sizeof reg, 1, pCli);
    fclose(p);
    if(leyo == 0)
    {
        reg.Mostrar();
    }
    return reg;
}


int ArchivoProveedores::buscarCuit(char *cuit)
{
    Proveedor reg;
    FILE *p;
    int pos = 0;
    p = fopen(nombre,"rb");
    if(p == NULL)
    {
        return -2;
    }
    while(fread(&reg, sizeof reg, 1,p) == 1)
    {
        if(strcmp(reg.getCuit(),cuit) == 0)
        {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}


int ArchivoProveedores::editarRegistro(Proveedor reg, int pos)
{
    FILE *p;
    p = fopen(nombre,"rb+");
    if(p == NULL)
    {
        return -1;
    }
    fseek(p, pos*sizeof (Proveedor), 0);
    int valor = fwrite(&reg, sizeof reg, 1,p);
    fclose(p);
    return valor;
}


int ArchivoProveedores::getCantidadRegistros()
{
    FILE *p;
    p = fopen(nombre, "rb");
    if (p == NULL)
    {
        return 0;
    }
    fseek(p, 0, SEEK_END);
    int bytes = ftell(p);
    fclose(p);

    return bytes / sizeof(Proveedor);
}


int ArchivoProveedores::generarNumeroProveedor()
{
    ArchivoProveedores auxArchivoProveedores("proveedores.dat");

    return auxArchivoProveedores.getCantidadRegistros() + 1;
}




















