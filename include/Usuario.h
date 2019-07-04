#ifndef PROYECTO_INCLUDE_USUARIO_H
#define PROYECTO_INCLUDE_USUARIO_H
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

#include "BaseDeDatos.h"
#include "Factura.h"

#define CLIENTE                 "0"
#define ADMINISTRADOR           "1"
#define VENDEDOR                "2"
#define CLIENTE_FUNCIONARIO     "3"
#define CLIENTE_SIN_REGISTRAR   "4"
#define COMPRAR_TODO            -10
#define QUITAR_TODO             -11

class Usuario{
    public:
        Usuario(string, string);
        ~Usuario();
        bool estaRegistrado();
        bool esCliente();
        bool puedeRegistrarse();
        string getTipo();
        void registrar(string, string, string);
        void agregarACarrito(string,  string, int);
        void quitarDelCarrito(string, int);
        void mostrarCarrito();
        int getDescuento();
        int getDescuento(string);
        string getDescuentos();
        string getCedula();
        string getNombre();
        string getTelefono();
        bool facturar();
        bool haySolicitudes();
        void mostrarSolicitud();
        void procesarSolicitud(bool);
        void registroDirecto(string, string, string, string, string);
        string ultimosDosProductos();
        string productoMasVendido();
        string productoMenosVendido();
        string mayorComprador();
        string menorComprador();
        string comprasPorUsuario();
        string mejorSuper();
        string peorSuper();
        void agregarAccionAdmin();
        string mejorAdmin();
        string peorAdmin();
        string hacerConsultaPrecio(string);
        string getProductos(string);
        string eliminarProducto(string);
        string insertarProducto(string, string, string, string, string);
        string cambiarCodSuper(string, string);
        string cambiarNombreProducto(string, string);
        string cambiarCantidadProducto(string, string);
        string cambiarPrecioProducto(string, string);
        string ultimoCambio();
        string ultimaEliminacion();
        bool existeSuper(string);
        bool carritoVacio();
        string getCodSuperCarrito();
    private:
        string cedula;
        string tipo;
        string nombre;
        string telefono;
        string obtenerCedulaArchivo(string);
        string obtenerTipoArchivo(string);
        string obtenerNombre();
        string obtenerTelefono();
        int obtenerUltimaPosicion(string);
        string obtenerCodSuper(string);
        static BaseDeDatos base;
        ListaDobleCircular carrito;
        string codSuperCarrito;
};

#endif // PROYECTO_INCLUDE_USUARIO_H
