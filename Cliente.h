#pragma once

class Cliente
{
private:
    char apellido[30];
    char nombre[30];
    char dni[12];
    float saldoDeudor;
    float saldoAcreedor;
    float montoMaximo;
    bool activo;
public:
    bool Cargar();
    void Mostrar();
    const char* getApellido();
    const char* getNombre();
    const char* getDni();
    void setDni(const char *d);
    void setApellido(const char *a);
    bool getActivo();
    void setActivo(bool a);
    void setSaldoDeudor(float s);
    float getSaldoDeudor();
    void setSaldoAcreedor(float s);
    float getSaldoAcreedor();
    void setMontoMaximo(float mM);
    float getMontoMaximo();
};
