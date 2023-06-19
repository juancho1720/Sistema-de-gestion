#pragma once

void cargarCadena(char *pal, int tam);

int generarNumeroFactura();

int generarNumeroRecibo();

float calcularImporteFactura(int codA, int cantV);

const char *buscarNombre(const char *d);

const char *buscarApellido(const char *d);

bool comprobarClientesExistentes(const char *dni);

bool comprobarArticulosExistentes(int codigoArticulo);

int sumarStock(int codigoArticulo, int cantidadArticulo);

int restarStock(int codigoArticulo, int cantidadVendida);

float sumarDeuda(const char *dni, float importe);

float restarDeuda(const char *dni, float importe);

const char *buscarDescripcion(int codigoArticulo);

bool cancelarFactura(const char *dni, int numFactura, float importe);

int imputarRecibos(const char *dni, float importe);

void imputarSaldos();

float consultarDeudaCliente(const char *dni);

bool comprobarDeuda(const char *dni, float importe);

void ventasMensualesProductos();

void cobrosMensualesTipo();

void exportarCsv();
