#include "Venta.h"

void Venta::Cargar()
{
    ArchivoArticulos archArticulos("articulos.dat");
    int precioProducto;
    cout << "Numero de venta: (Sera automatico el numerador al fin)";
    cin>>codigoVenta;
    cout << "Codigo de cliente: ";
    cin>>codigoCliente;
    cout << "Codigo de articulo: ";
    cin>>codigoArticulo;
    cout << "Cantidad: ";
    cin>>cantidad;
    cout << "Fecha de compra: ";
    fechaVenta.Cargar();
    precioProducto = archArticulos.getPrecioPorId(codigoArticulo);
    importe = precioProducto*cantidad;

    activo=true;
}

void Venta::Mostrar()
{
    cout << "Numero de venta: (Sera automatico el numerador al fin)";
    cout<<codigoVenta<<endl;
    cout << "Codigo de cliente: ";
    cout<<codigoCliente<<endl;
    cout << "Codigo de articulo: ";
    cout << codigoArticulo<<endl;
    cout << "Cantidad: ";
    cout << cantidad<<endl;
    cout << "Fecha de compra: ";
    fechaVenta.Mostrar();
    cout << "Total: $" << importe << endl;
    cout<<endl;
    if(!activo) cout<<"ESTA BORRADO"<<endl<<endl;
}
