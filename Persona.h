#ifndef PERSONA_H
#define PERSONA_H
#include "Funciones.h"
#include "hstring.h"


class Persona
{
private:
    char domicilio[30];
    char telefono[31];
public:
    //SETTERS
    void setDomicilio(const char *_domicilio){strcpy(domicilio,_domicilio);}
    void setTelefono(const char *_telefono){strcpy(telefono,_telefono);}
    //GETTERS
    char *getDomicilio(){return domicilio;}
    char *getTelefono(){return telefono;}
    //FUNCIONES
    void Cargar();
    void Mostrar();
};

#endif // PERSONA_H
