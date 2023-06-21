#pragma once
#include "ArchivoArticulo.h"


class MenuManager
{
public:
    void MenuBienvenida();
    void MenuGeneral();
    void ModuloClientes();
    void ModuloVentas();
    void ModuloReportes();
    void ModuloArticulos();
    void ModuloPagos();
    void ModuloBackUp();
    float consultarDeudaCliente(const char *dni);
    int sumarStock(int codigoArticulo, int cantidadArticulo);
    void ventasMensualesProductos();
    void cobrosMensualesTipo();
    void exportarClientes();
    void exportarCtasCtes();
    void MenuBackUp();
    void MenuRestaurarArchivo();
    void hacerBackupArticulos();
    void hacerBackupClientes();
    void hacerBackupPagos();
    void hacerBackupVentas();
    void restaurarCopiaArticulos();
    void restaurarCopiaClientes();
    void restaurarCopiaPagos();
    void restaurarCopiaVentas();
    void MenuDespedida();
};
