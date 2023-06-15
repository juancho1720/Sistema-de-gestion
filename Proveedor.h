#ifndef PROVEEDOR_H
#define PROVEEDOR_H
#include "hstring.h"
#include <iostream>
using namespace std;
#include "Funciones.h"
#include "Fecha.h"
#include "Persona.h"

class Proveedor : public Persona
{
private:
    int codigoProveedor;
    char razonSocial[31];
    char cuit[14];
    Fecha fechaAlta;
    bool estado;
public:
    //SETTERS
    void setCodigoProveedor(int n){codigoProveedor = n;}
    void setRazonSocial(const char *rS){strcpy(razonSocial,rS);}
    void setCuit(const char *c){strcpy(cuit,c);}
    void setEstado(bool e){estado = e;}
    //GETTERS
    int getCodigoProveedor(){return codigoProveedor;}
    char *getRazonSocial(){return razonSocial;}
    char *getCuit(){return cuit;}
    Fecha getFecha(){return fechaAlta;}
    bool getEstado(){return estado;}
    //Funciones
    void Cargar();
    void Mostrar();
};

#endif // PROVEEDOR_H
