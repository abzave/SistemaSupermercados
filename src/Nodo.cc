#include "Nodo.h"

Nodo::Nodo(string valor, string llave){
    this->valor = valor;
    this->llave = llave;
    siguiente = NULL;
}

Nodo::Nodo(string valor, string llave, Nodo* siguiente){
    this->valor = valor;
    this->llave = llave;
    this->siguiente = siguiente;
}
