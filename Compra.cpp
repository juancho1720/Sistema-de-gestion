#include "Compra.h"

void Compra::Cargar()
{
    cout << "Codigo de proveedor: ";
    cin>>codigoProveedor;
    cout << "Codigo de articulo: ";
    cin>>codigoArticulo;
    cout << "Cantidad: ";
    cin>>cantidad;
    cout << "Fecha de compra: ";
    fechaCompra.Cargar();
    activo=true;
}

void Compra::Mostrar()
{
    cout << "Numero de compra: (Sera automatico el numerador al fin)";
    cout<<codigoCompra<<endl;
    cout << "Codigo de proveedor: ";
    cout<<codigoProveedor<<endl;
    cout << "Codigo de articulo: ";
    cout << codigoArticulo<<endl;
    cout << "Cantidad: ";
    cout << cantidad<<endl;
    cout << "Fecha de compra: ";
    fechaCompra.Mostrar();
    cout<<endl;
    if(!activo) cout<<"ESTA BORRADO"<<endl<<endl;
}
