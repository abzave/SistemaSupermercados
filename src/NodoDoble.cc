#include "NodoDoble.h"

NodoDoble::NodoDoble(string v, string llave){
    valor = v;
    this->llave = llave;
    siguiente = NULL;
    anterior =NULL;
}

NodoDoble::NodoDoble(string v, string llave, NodoDoble* signodo){
    valor = v;
    this->llave = llave;
    siguiente = signodo;
}
