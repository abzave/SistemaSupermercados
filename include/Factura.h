#ifndef FACTURA_H
#define FACTURA_H

#include <fstream>
#include <string>
#include "ListaDobleCircular.h"

struct userData{
            int descuento;
            string nombre;
            string cedula;
            string telefono;
};

class Factura{
    public:
        Factura(userData);
        void generar(ListaDobleCircular, string[]);
    private:
        static int cantidadFacturas;
        string generarTexto(ListaDobleCircular, string[]);
        string obtenerCodSuper(string);
        string obtenerProducto(string);
        string obtenerPrecio(string);
        string calcularTotal(string, string&);
        userData user;
};

#endif // FACTURA_H
