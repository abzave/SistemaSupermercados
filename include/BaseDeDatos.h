#ifndef PROYECTO_INCLUDE_BASEDEDATOS_H
#define PROYECTO_INCLUDE_BASEDEDATOS_H
#define ES_PRIMERO      true
#define ES_SEGUNDO      false
#define COMPRAR_TODO    -10

#include <fstream>

#include "ListaSimple.h"
#include "ListaDeListas.h"
#include "ListaDoble.h"
#include "ListaDobleCircular.h"

class BaseDeDatos
{
    public:
        BaseDeDatos();
        ~BaseDeDatos();
        bool esCedulaValida(string, string);
        void agregarSolicitud(string, string, string, string);
        string obtenerCodDeCiudad(string);
        bool existeCodProducto(string);
        bool existeProductoEnSuper(string, string);
        string getNombreProducto(string);
        int getCantidadProducto(string);
        void quitarCantidadProducto(string, int);
        void agregarCantidadProducto(string, int);
        string getNombreUsuario(string, string);
        string getTelefonoUsuario(string, string);
        string getInfoProducto(string);
        string getSolicitud();
        bool listaSolicitudVacia();
        bool existeCodSuper(string);
        void aceptarSolicitud();
        void borrarSolicitud();
        void agregarUsuario(string ,string, string, string, string);
        string getProducto(int);
        int getCantidadProductosInventario();
        void agregarProductoVendido(string, string);
        string getProductoMasVendido();
        string getMenosVendidos();
        void registrarCompra(string, int);
        string getMayorComprador();
        string getMenorComprador();
        string cantidadDeCompras();
        string getSuperMasVisitado();
        string getSuperMenosVisitado();
        void agregarVisitaSuper(string);
        void agregarActividadAdmin(string);
        string getMejorAdmin();
        string getPeorAdmin();
        string getProductosSuper(string);
        bool eliminarDeInventario(string);
        void agregarProducto(string, string);
        void actualizarCodSuper(string, string);
        void actualizarNombreProducto(string, string);
        void actualizarCantidadProducto(string, string);
        void actualizarPrecioProducto(string, string);
        string getUltimoModificado();
        string getUltimoEliminado();
    private:
        void cargarInformacion();
        void cargarCiudades();
        void cargarUsuarios();
        void cargarSupers();
        void cargarInventario();
        void actualizarProductoVendido(string, string);
        bool esCodCiudadValido(string);
        bool existeCodCiudad(string);
        bool yaHaSidoVendido(string);
        bool yaHaComprado(string);
        bool yaHaSidoVisitado(string);
        string obtenerPrimerCod(string);
        string obtenerLlave(string);
        string obtenerTipo(string);
        string quitarLlave(string, bool);
        string quitarTipo(string);
        string getNombreSuper(string);
        string cambiarCantidad(string, string);
        ListaSimple listaSimpleCiudades;
        ListaDeListas listaDeListasUsuarios;
        ListaDoble listaDobleSuper;
        ListaDobleCircular listaDobleCircularInventario;
        static ListaSimple listaSolicitud;
        static ListaSimple productosVendidos;
        static ListaSimple registroDeCompras;
        static ListaSimple visitasSuper;
        static ListaSimple actividadDeAdministradores;
        static string ultimoModificado;
        static string ultimoEliminado;
};

#endif // PROYECTO_INCLUDE_BASEDEDATOS_H
