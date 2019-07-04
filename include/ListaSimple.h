#ifndef PROYECTO_INCLUDE_LISTASIMPLE_H
#define PROYECTO_INCLUDE_LISTASIMPLE_H
#include <iostream>
#include <exception>
#include "Nodo.h"
using namespace std;

class ListaSimple {
   public:
    ListaSimple();
    ~ListaSimple();
    void InsertarInicio(string, string);
    void InsertarFinal(string, string);
    void InsertarPos (string, string, int);
    bool ListaVacia();
    void Mostrar();
    void BorrarFinal();
    void BorrarInicio();
    void borrarPosicion(int);
    int largoLista();
    string getLlave(unsigned int);
    string getValor(unsigned int);
    void actualizar(string, string);
    bool existeLlave(string);
   private:
    Nodo* primero;
    int largo;
};

#endif // PROYECTO_INCLUDE_LISTASIMPLE_H
