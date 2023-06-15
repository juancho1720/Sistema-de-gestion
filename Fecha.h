#ifndef FECHA_H
#define FECHA_H
#include <iostream>
using namespace std;


class Fecha
{
private:
    int dia,mes,anio;
public:
    //SETTERS
    void setDia(const int _dia){dia=_dia;}
    void setMes(const int _mes){mes=_mes;}
    void setAnio(const int _anio){anio=_anio;}
    //GETTERS
    int getDia(){return dia;}
    int getMes(){return mes;}
    int getAnio(){return anio;}
    //Funciones
    void Cargar();
    void Mostrar();
};

#endif // FECHA_H
