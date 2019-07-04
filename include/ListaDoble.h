#ifndef LISTADOBLE_H
#define LISTADOBLE_H
#include "NodoDoble.h"

class ListaDoble
{
    public:
        ListaDoble();
        ~ListaDoble();
        void InsertarInicio(string, string);
        void InsertarFinal(string, string);
        void InsertarPos (string, string, int);
        void EliminarInicio();
        void EliminarFinal();
        void EliminarPos(int);
        bool ListaVacia();
        void Imprimir();
        void Borrar(int);
        void Mostrar();
        void BorrarFinal();
        void BorrarInicio();
        void borrarPosicion(int);
        string getLlave(int);
        int largoLista();
        string getValor(string);
   private:
        NodoDoble* primero;
        int largo;
};

#endif // LISTADOBLE_H
