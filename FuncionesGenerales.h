#pragma once

void cargarCadena(char *pal, int tam);

const char *buscarNombre(const char *d);

const char *buscarApellido(const char *d);

bool comprobarClientesExistentes(const char *dni);

bool comprobarArticulosExistentes(int codigoArticulo);

float sumarDeuda(const char *dni, float importe);

//imputarSaldos
float restarDeuda(const char *dni, float importe);

//imputarSaldos COMENTO LA FUNCION Y NO TIRA ERROR. BUSCAR DONDE SE USA.
void imputarSaldos();

