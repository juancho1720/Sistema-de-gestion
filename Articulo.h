#pragma once

class Articulo
{
private:
    char descripcion[30];
    int codigoArticulo;
    int cantidadArticulo;
    int stock;
    float precioUnitario;
    bool estado;
public:
    Articulo();
    bool Cargar();
    void Mostrar();
    const char* getDescripcion();
    int getCodigoArticulo();
    int getCantidadArticulo();
    float getPrecioUnitario();
    void setPrecioUnitario(float pU);
    int getStock();
    void setStock(int s);
    bool getEstado();
    void setEstado(bool e);
};
