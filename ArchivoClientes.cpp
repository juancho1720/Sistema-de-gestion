#include "ArchivoClientes.h"

bool ArchivoClientes::escribirRegistro()
{
    FILE *p;
    p = fopen(nombre,"ab");
    if(p == NULL)
    {
        return false;
    }
    reg.setCodigoCliente(generarNumeroCliente());
    reg.Cargar();
    bool escribio = fwrite(&reg, sizeof reg, 1, p);
    fclose(p);
    return escribio;
}

bool ArchivoClientes::listarArchivo()
{
    Cliente reg;
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

Cliente ArchivoClientes::leerRegistro(int pos)
{
    Cliente reg;
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

int ArchivoClientes::buscarDni(char *dni)
{
    Cliente reg;
    FILE *p;
    int pos = 0;
    p = fopen(nombre,"rb");
    if(p == NULL)
    {
        return -2;
    }
    while(fread(&reg,sizeof reg,1,p))
    {
        if(strcmp(reg.getDni(),dni) == 0)
        {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}


int ArchivoClientes::editarRegistro(Cliente reg, int pos)
{
    FILE *p;
    p = fopen(nombre,"rb+");
    if(p == NULL)
    {
        return -1;
    }
    fseek(p,pos*sizeof(Cliente),0);
    int valor = fwrite(&reg,sizeof reg,1,p);
    fclose(p);
    return valor;
}


int ArchivoClientes::getCantidadRegistros()
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

    return bytes / sizeof(Cliente);
}


int ArchivoClientes::generarNumeroCliente()
{
    ArchivoClientes auxArchivoClientes("clientes.dat");

    return auxArchivoClientes.getCantidadRegistros() + 1;
}



























