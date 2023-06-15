#include "ArchivoArticulos.h"

bool ArchivoArticulos::escribirRegistro()
{
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

bool ArchivoArticulos::listarArchivo()
{
        Articulo reg;
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


Articulo ArchivoArticulos::leerRegistro(int pos)
{
        Articulo reg;
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


int ArchivoArticulos::buscarCodigo(int cod)
{
        Articulo reg;
        FILE *p;
        int pos = 0;
        p = fopen(nombre,"rb");
        if(p == NULL)
        {
            return -2;
        }
        while(fread(&reg, sizeof reg, 1,p))
        {
            if(reg.getCodigo() == cod)
            {
                fclose(p);
                return pos;
            }
            pos++;
        }
        fclose(p);
        return -1;
    }



int ArchivoArticulos::editarRegistro(Articulo reg, int pos)
 {
        FILE *p;
        p = fopen(nombre,"rb+");
        if(p == NULL)
        {
            return -1;
        }
        fseek(p, pos*sizeof (Articulo), 0);
        int valor = fwrite(&reg, sizeof reg, 1,p);
        fclose(p);
        return valor;
    }

int ArchivoArticulos::getCantidadRegistros()
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

    return bytes / sizeof(Articulo);
}


float ArchivoArticulos::getPrecioPorId(int cod)
{
    Articulo reg;
        FILE *p;
        p = fopen(nombre,"rb");
        if(p == NULL)
        {
            return -2;
        }
        while(fread(&reg, sizeof reg, 1,p))
        {
            if(reg.getCodigo() == cod)
            {
                fclose(p);
                return reg.getPrecio();
            }
        }
        fclose(p);
        return -1;
}
































