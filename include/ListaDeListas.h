#ifndef PROYECTO_INCLUDE_LISTADELISTAS_H
#define PROYECTO_INCLUDE_LISTADELISTAS_H
#define CANTIDAD_DE_TIPOS       4
#include<string>
#include<exception>
#include "NodoListas.h"

using namespace std;

class ListaDeListas{
    public:
        ListaDeListas();
        ~ListaDeListas();
        void InsertarFinal(string);
        void eliminarAbajoInicio(string);
        void eliminarAbajoFinal(string);
        void eliminarAbajoPos(string, int);
        bool ListaVacia();
        void Imprimir();
        void Borrar(string);
        void Mostrar();
        void BorrarFinal();
        void BorrarInicio();
        void borrarPosicion(int);
        int largoLista();
        void insertarUsuario(string, string, string);
        void mostrarAbajo(string);
        string getLlave(unsigned int, string);
        int getLargoUsuarios(string);
        string getValorUsuario(string, string);
        string getCedula(string, int);
   private:
        NodoListas* primero;
        int largo;
        int largoUsuarios[CANTIDAD_DE_TIPOS];
};

#endif // PROYECTO_INCLUDE_LISTADELISTAS_H
