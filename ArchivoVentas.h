#ifndef ARCHIVOVENTAS_H
#define ARCHIVOVENTAS_H
#include "hstring.h"
#include "Venta.h"


class ArchivoVentas
{
private:
    char nombre[30];
    Venta reg;
public:
    ArchivoVentas(const char *n){strcpy(nombre, n);}
    bool escribirRegistro();
    bool listarArchivo();
    Venta leerRegistro(int pos);
    int editarRegistro(Venta reg, int pos);
    int getCantidadRegistros();
};

#endif // ARCHIVOVENTAS_H
