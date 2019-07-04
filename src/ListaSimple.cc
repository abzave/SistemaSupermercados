#include "ListaSimple.h"

ListaSimple::ListaSimple(){
    primero = NULL;
    largo = 0;
}

bool ListaSimple::ListaVacia(){
    return primero == NULL;
}

ListaSimple::~ListaSimple(){
   Nodo* aux;
   while(primero) {
      aux = primero;
      primero = primero->siguiente;
      delete aux;
   }
   largo = 0;
}

int ListaSimple::largoLista(){
    return largo;
}

void ListaSimple::InsertarInicio(string v, string llave){
   if (ListaVacia())
     primero = new Nodo(v, llave);
   else
     primero=new Nodo (v, llave,primero);
    largo++;
}

void ListaSimple::InsertarFinal(string v, string llave){
   if (ListaVacia())
     primero = new Nodo(v, llave);
   else
     { Nodo* aux = primero;
        while ( aux->siguiente != NULL)
          aux= aux->siguiente;
        aux->siguiente=new Nodo(v, llave);
      }
    largo++;
}


void ListaSimple::InsertarPos(string v, string llave,int pos){
   if (ListaVacia())
     primero = new Nodo(v, llave);
   else{
        if(pos <=1){
          Nodo* nuevo = new Nodo(v, llave);
          nuevo->siguiente= primero;
          primero= nuevo;
        }
        else{
             Nodo* aux= primero;
             int i =2;
             while((i != pos )&&(aux->siguiente!= NULL)){
                   i++;
                   aux=aux->siguiente;
             }
             Nodo* nuevo= new Nodo(v, llave);
             nuevo->siguiente=aux->siguiente;
             aux->siguiente=nuevo;

        }
    }
    largo++;
}

void ListaSimple::BorrarFinal(){
    if (ListaVacia()){
     cout << "No hay elementos en la lista:" << endl;
   }else{
        if (primero->siguiente == NULL) {
                primero= NULL;
            } else {

                Nodo* aux = primero;
                while (aux->siguiente->siguiente != NULL) {
                    aux = aux->siguiente;

                }

              Nodo* temp = aux->siguiente;
              aux->siguiente= NULL;


                delete temp;
            }
        }
}

void ListaSimple::BorrarInicio()
{
    if (ListaVacia()){
     cout << "No hay elementos en la lista:" << endl;

   }else{
        if (primero->siguiente == NULL) {
                primero= NULL;
            } else {

                Nodo* aux = primero;
                primero=primero->siguiente;
                delete aux;
            }
        }
    largo--;
}



void ListaSimple:: borrarPosicion(int pos){
     if(ListaVacia()){
              cout << "Lista vacia" <<endl;
    }else{
         if((pos>largoLista())||(pos<0)){
        cout << "Error en posicion" << endl;
        }else{
        if(pos==1){
        primero=primero->siguiente;
        }else{
          int cont=2;
            Nodo* aux=primero;
            while(cont<pos){
             aux=aux->siguiente;
             cont++;
            }
            aux->siguiente=aux->siguiente->siguiente;
            }
        }
     }
    largo--;
}


void ListaSimple::Mostrar(){
   Nodo *aux;
   aux = primero;
   while(aux) {
      cout << aux->llave << ";" << aux->valor << "-> ";
      aux = aux->siguiente;
   }
   cout << endl;
}

string ListaSimple::getLlave(unsigned int posicion){
    Nodo* aux = primero;
    unsigned int i = 0;
    for(i = 0; i < posicion && aux; i++){
        aux = aux->siguiente;
    }
    if(i != posicion){
        throw invalid_argument("Error: Posición no valida");
    }else{
        return aux->llave;
    }
}

string ListaSimple::getValor(unsigned int posicion){
    Nodo* aux = primero;
    unsigned int i = 0;
    for(i = 0; i < posicion && aux; i++){
        aux = aux->siguiente;
    }
    if(i != posicion){
        throw invalid_argument("Error: Posición no valida");
    }else{
        return aux->valor;
    }
}

void ListaSimple::actualizar(string llave, string valor){
    Nodo* aux = primero;
    Nodo* ant = primero;
    for(int i = 0; i < largoLista(); i++){
        if(aux->llave == llave){
            aux->valor = valor;
            int cantidad = atoi(aux->valor.substr(0, aux->valor.find(";")).c_str());
            int cantidadAnt = atoi(ant->valor.substr(0, ant->valor.find(";")).c_str());
            if(cantidad > cantidadAnt){
                InsertarPos(aux->valor, aux->llave, i - 1);
                borrarPosicion(i + 2);
            }
        }
        ant = aux;
        aux = aux->siguiente;
    }
}

bool ListaSimple::existeLlave(string llave){
    Nodo* aux = primero;
    while(aux){
        if(aux->llave == llave){
            return true;
        }
        aux = aux->siguiente;
    }
    return false;
}

