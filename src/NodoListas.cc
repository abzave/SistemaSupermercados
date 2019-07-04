#include "NodoListas.h"

NodoListas::NodoListas(string v){
    valor = v;
    abajo = NULL;
    siguiente = NULL;
    anterior = NULL;
}

NodoListas::NodoListas(string v, NodoDoble* abajo, NodoListas* signodo){
    valor = v;
    this->abajo = abajo;
    siguiente = signodo;
}
