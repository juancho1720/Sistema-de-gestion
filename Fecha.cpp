#include <iostream>
#include <string.h>
#include <iomanip>
#include <ctime>

using namespace std;

#include "Fecha.h"

void Fecha::Cargar()
{
    time_t now = time(0);

    tm * time = localtime(&now);

    cout << "Fecha: " << time -> tm_mday << "/" << time -> tm_mon + 1 << "/" << time -> tm_year + 1900 << endl;
    dia = time -> tm_mday;
    mes = time -> tm_mon +1;
    anio = time -> tm_year +1900;
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
