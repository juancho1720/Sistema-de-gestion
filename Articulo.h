#ifndef ARTICULO_H
#define ARTICULO_H
#include "hstring.h"
#include <iostream>
using namespace std;
#include "Funciones.h"


class Articulo
{
private:
    int codigo;
    char descripcion[31];
    float precio;
    bool estado;
public:
    Articulo(int c = 0, const char *d = "VACIO", bool e = false){
    codigo = c;
    strcpy(descripcion,d);
    estado = e;
}
    //SETTERS
    void setCodigo(const int c){codigo = c;}
    void setDescripcion(const char *d){strcpy(descripcion,d);}
    void setEstado(const int e){estado = e;}
    void setPrecio(const float _precio){precio=_precio;}
    //GETTERS
    int getCodigo(){return codigo;}
    char *getDescripcion(){return descripcion;}
    int getEstado(){return estado;}
    float getPrecio(){return precio;}
    //FUNCIONES
    void Cargar();
    void Mostrar();
};

#endif // ARTICULO_H
