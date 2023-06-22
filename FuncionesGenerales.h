#pragma once

void cargarCadena(char *pal, int tam);

const char *buscarNombre(const char *d);

const char *buscarApellido(const char *d);

bool comprobarClientesExistentes(const char *dni);

bool comprobarArticulosExistentes(int codigoArticulo);

float sumarSaldoDeudor(const char *dni, float importe);

float restarSaldoDeudor(const char *dni, float importe);

float sumarSaldoAcreedor(const char *dni, float importe);

float restarSaldoAcreedor(const char *dni, float importe);
