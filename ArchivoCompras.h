#ifndef ARCHIVOCOMPRAS_H
#define ARCHIVOCOMPRAS_H
#include "Compra.h"
#include "hstring.h"


class ArchivoCompras
{
private:
    char nombre[30];
    Compra reg;
public:
    ArchivoCompras(const char *n){strcpy(nombre, n);}
    bool escribirRegistro();
    bool listarArchivo();
    Compra leerRegistro(int pos);
    int editarRegistro(Compra reg, int pos);
    int getCantidadRegistros();
};

#endif // ARCHIVOCOMPRAS_H
