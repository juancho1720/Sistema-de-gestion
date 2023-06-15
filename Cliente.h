#ifndef CLIENTE_H
#define CLIENTE_H
#include <iostream>
using namespace std;
#include "hstring.h"
#include "Funciones.h"
#include "Fecha.h"
#include "Persona.h"


class Cliente : public Persona
{
private:
    int codigoCliente;
    char nombre[31];
    char apellido[31];
    char dni[12];
    Fecha fechaAlta;
    bool estado;
public:
    //SETTERS
    void setCodigoCliente(int n){codigoCliente = n;}
    void setNombre(const char *n){strcpy(nombre,n);}
    void setApellido(const char *a){strcpy(apellido,a);}
    void setDni(const char *d){strcpy(dni,d);}
    void setEstado(bool e){estado = e;}
    //GETTERS
    int getCodigoCliente(){return codigoCliente;}
    char *getNombre(){return nombre;}
    char *getApellido(){return apellido;}
    char *getDni(){return dni;}
    Fecha getFecha(){return fechaAlta;}
    bool getEstado(){return estado;}
    //FUNCIONES
    void Cargar();
    void Mostrar();
};

#endif // CLIENTE_H
