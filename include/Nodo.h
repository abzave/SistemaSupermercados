#ifndef PROYECTO_INCLUDE_NODO_H
#define PROYECTO_INCLUDE_NODO_H
#include<iostream>
#include<string>
using namespace std;

class Nodo {
   public:
    Nodo(string, string);
    Nodo(string, string, Nodo*);
   private:
    string valor;
    string llave;
    Nodo *siguiente;
   friend class ListaSimple;
};

#endif // PROYECTO_INCLUDE_NODO_H
