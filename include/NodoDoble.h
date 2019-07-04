#ifndef PROYECTO_INCLUDE_NODODOBLE_H
#define PROYECTO_INCLUDE_NODODOBLE_H
#include <iostream>
using namespace std;

class NodoDoble{
   public:
    NodoDoble(string, string);
    NodoDoble(string, string, NodoDoble*);
   private:
    string valor;
    string llave;
    NodoDoble *siguiente;
    NodoDoble *anterior;
   friend class ListaDoble;
   friend class ListaDobleCircular;
   friend class ListaDeListas;
};

#endif // PROYECTO_INCLUDE_NODODOBLE_H
