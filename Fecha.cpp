#include <iostream>
#include <string.h>
#include <iomanip>

using namespace std;

#include "Fecha.h"

void Fecha::Cargar()
{
    cout << "Dia: ";
    cin>>dia;
    cout << "Mes: ";
    cin>>mes;
    cout << "Anio: ";
    cin>>anio;
}

void Fecha::Mostrar()
{
    cout << left;
    cout << dia << "/"  << mes << "/"  << anio;
    cout << setw(15);
}

int Fecha::getDia()
{
    return dia;
}

int Fecha::getMes()
{
    return mes;
}

int Fecha::getAnio()
{
    return anio;
}

void Fecha::setDia(int d)
{
    dia=d;
}

void Fecha::setMes(int m)
{
    mes=m;
}

void Fecha::setAnio(int a)
{
    anio=a;
}
