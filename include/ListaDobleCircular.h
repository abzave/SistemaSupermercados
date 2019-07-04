#ifndef PROYECTO_INCLUDE_LISTADOBLECIRCULAR_H
#define PROYECTO_INCLUDE_LISTADOBLECIRCULAR_H
#include<NodoDoble.h>


class ListaDobleCircular{
    public:
        ListaDobleCircular();
        ~ListaDobleCircular();
        void InsertarInicio(string, string);
        void InsertarFinal(string, string);
        void InsertarPos (string, string, int);
        bool ListaVacia();
        void Imprimir();
        void Borrar(string);
        void Mostrar();
        void BorrarFinal();
        void BorrarInicio();
        void borrarPorLlave(string);
        void borrarPos(int);
        string getLlave(int);
        string getValor(string);
        int largoLista();
        void actualizarLista(string, string);
        bool existeLlave(string);
   private:
        NodoDoble* primero;
        int largo;
};

#endif // PROYECTO_INCLUDE_LISTADOBLECIRCULAR_H
