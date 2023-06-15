#ifndef ARCHIVOPROVEEDORES_H
#define ARCHIVOPROVEEDORES_H
#include "hstring.h"
#include "Proveedor.h"


class ArchivoProveedores
{
private:
    char nombre[30];
    Proveedor reg;
public:
    ArchivoProveedores(const char *n){strcpy(nombre,n);}
    bool escribirRegistro();
    bool listarArchivo();
    Proveedor leerRegistro(int pos);
    int buscarCuit(char *cuit);
    int editarRegistro(Proveedor reg, int pos);
    int getCantidadRegistros();
    int generarNumeroProveedor();
};

#endif // ARCHIVOPROVEEDORES_H
