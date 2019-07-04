#ifndef PROYECTO_INCLUDE_NODOLISTAS_H
#define PROYECTO_INCLUDE_NODOLISTAS_H
#include "NodoDoble.h"

class NodoListas{
    public:
        NodoListas(string);
        NodoListas(string, NodoDoble*, NodoListas*);
   private:
        string valor;
        NodoListas *siguiente;
        NodoListas *anterior;
        NodoDoble *abajo;
   friend class ListaDeListas;
};

#endif // PROYECTO_INCLUDE_NODOLISTAS_H
