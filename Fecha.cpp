#include "Fecha.h"

void Fecha::Cargar()
{
    cout << "Dia:";
    cin>>dia;
    cout << "Mes:";
    cin>>mes;
    cout << "Anio:";
    cin>>anio;
}

void Fecha::Mostrar()
{
    cout<<dia<<"/";
    cout<<mes<<"/";
    cout<<anio<<endl;
}
