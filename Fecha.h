#pragma once

class Fecha
{
private:
    int dia,mes, anio;
public:
    void Cargar();
    void Mostrar();
    int getDia();
    int getMes();
    int getAnio();
    void setDia(int d);
    void setMes(int m);
    void setAnio(int a);
};
