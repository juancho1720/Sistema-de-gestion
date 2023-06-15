#ifndef ARCHIVOARTICULOS_H
#define ARCHIVOARTICULOS_H
#include "hstring.h"
#include "Articulo.h"


class ArchivoArticulos
{
private:
    char nombre[30];
    Articulo reg;
public:
    ArchivoArticulos(const char *n){strcpy(nombre,n);}
    bool escribirRegistro();
    bool listarArchivo();
    Articulo leerRegistro(int pos);
    float getPrecioPorId(int cod);
    int buscarCodigo(int cod);
    int editarRegistro(Articulo reg, int pos);
    int getCantidadRegistros();
};

#endif // ARCHIVOARTICULOS_H
