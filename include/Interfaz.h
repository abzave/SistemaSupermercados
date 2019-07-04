#ifndef PROYECTO_INCLUDE_INTERFAZ_H
#define PROYECTO_INCLUDE_INTERFAZ_H
#define REPORTES        "5"

#include <string>
#include <iostream>

#include "Validacion.h"

class Interfaz{
    public:
        string pedirTipoUsuario();
        string pedirCedula();
        bool preguntarRegistro();
        void imprimirMenu(string);
        string pedirOpcion(string);
        string pedirCiudad();
        string pedirNombre();
        string pedirNombreProducto();
        string pedirTelefono();
        void limpiarPantalla();
        void mostrarMensajeRegistro();
        int procesarOpcion(string, string);
        void imprimirUsuarioNoEncontrado();
        void imprimirSubMenuComprar();
        string pedirCodProducto();
        string pedirCantidad();
        bool preguntarTodos(bool);
        void imprimirDescuento(Usuario*);
        bool preguntarRegistrar();
        void imprimirSubMenuRegistrar();
        void imprimirSubMenuReportes();
        string pedirCodSuper();
        string pedirPrecio();
        void imprimirSubMenuModificar();
        void pause();
    private:
        bool esCedulaValida(string);
        bool esTipoValido(string);
        bool esOpcionValida(string, string);
        bool esNombreValido(string);
        bool esNombreProductoValido(string);
        bool esTelefonoValido(string);
        int getCantidadDeOpciones(string);
        bool esCodValido(string);
        bool esCantidadValida(string);
};

#endif // PROYECTO_INCLUDE_INTERFAZ_H
