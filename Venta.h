#pragma once

#include "Cliente.h"
#include "Fecha.h"




class Venta
{
private:
    Fecha fechaVenta;
    char dni[12];
    char apellido[30];
    char nombre[30];
    int codigoArticulo;
    char descripcionArticulo[30];
    int cantidadVendida;
    int numeroFactura;
    int numeroRecibo;
    float importe;
    float saldo;
    bool paga;
    bool activa;
    Cliente regCliente;
public:
    bool Cargar();
    void Mostrar();
    Fecha getFechaVenta();
    const char* getDni();
    const char *getApellido();
    const char *getNombre();
    int getNumeroFactura();
    int getNumeroRecibo();
    void setNumeroRecibo(int nR);
    int getCodigoArticulo();
    const char *getDescripcionArticulo();
    int getCatidadVendida();
    float getImporte();
    void setSaldo(float s);
    float getSaldo();
    bool getPaga();
    void setPaga(bool a);
    bool getActiva();
    void setActiva(bool p);
    void setDescripcionArticulo(const char *dA);
    int generarNumeroFactura();
    float consultarDeudaCliente(const char *dni);
    const char *buscarDescripcion(int codigoArticulo);
    int restarStock(int codigoArticulo, int cantidadVendida);
    void sumarStock(int nF);
    float calcularImporteFactura(int codA, int cantV);
    bool comprobarDeuda(const char *dni, float importe);
};
