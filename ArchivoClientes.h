#ifndef ARCHIVOCLIENTES_H
#define ARCHIVOCLIENTES_H
#include "hstring.h"
#include "Cliente.h"


class ArchivoClientes
{
private:
    char nombre[30];
    Cliente reg;
public:
    ArchivoClientes(const char *n){strcpy(nombre,n);}
    bool escribirRegistro();
    bool listarArchivo();
    Cliente leerRegistro(int pos);
    int buscarDni(char *dni);
    int editarRegistro(Cliente reg, int pos);
    int getCantidadRegistros();
    int generarNumeroCliente();
};

#endif // ARCHIVOCLIENTES_H
