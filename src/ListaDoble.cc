#include "ListaDoble.h"

#include <exception>

ListaDoble::ListaDoble(){primero = NULL; largo = 0;}
bool ListaDoble::ListaVacia(){return primero == NULL;}

ListaDoble::~ListaDoble(){
   NodoDoble* aux;
   while(primero) {
      aux = primero;
      primero = primero->siguiente;
      delete aux;
   }
}

int ListaDoble::largoLista(){
    int cont=0;

    NodoDoble* aux;
    aux = primero;
    if(ListaVacia()){
        return cont;
    }else{
        while(aux!=NULL){
        aux=aux->siguiente;
        cont++;
    }
    return cont;
    }

}

void ListaDoble::InsertarInicio(string llave, string v){
   if (ListaVacia())
     primero = new NodoDoble(v, llave);
   else
   {
     primero=new NodoDoble(v, llave, primero);
     primero->siguiente->anterior=primero;
   }
   largo++;
}

void ListaDoble::InsertarFinal(string llave, string v){
   if (ListaVacia())
     primero = new NodoDoble(v, llave);
   else
     { NodoDoble* aux = primero;
        while ( aux->siguiente != NULL)
          aux= aux->siguiente;
        aux->siguiente=new NodoDoble(v, llave);
        aux->siguiente->anterior=aux;
      }
    largo++;
}


void ListaDoble::InsertarPos(string llave, string v,int pos)
{
   if (ListaVacia())
     primero = new NodoDoble(v, llave);
   else{
        if(pos <=1)
          InsertarInicio(llave, v);
        else
        {
             NodoDoble* aux= primero;
             int i =2;
             while((i != pos )&&(aux->siguiente!= NULL)){
                   i++;
                   aux=aux->siguiente;
             }
             NodoDoble* nuevo= new NodoDoble(v, llave);
             nuevo->siguiente=aux->siguiente;
             aux->siguiente=nuevo;
             aux->siguiente->anterior=aux;
             nuevo->siguiente->anterior=nuevo;
        }
    }
    largo++;
}

void ListaDoble::BorrarFinal()
{
    if (ListaVacia()){
     cout << "No hay elementos en la lista:" << endl;

   }else{
        if (primero->siguiente == NULL) {
                primero= NULL;
            } else {

                NodoDoble* aux = primero;
                while (aux->siguiente->siguiente != NULL)
                {
                    aux = aux->siguiente;
                }

              NodoDoble* temp = aux->siguiente;
              aux->siguiente= NULL;


                delete temp;
            }
        }
    largo--;
}

void ListaDoble::BorrarInicio(){
    if (ListaVacia()){
     cout << "No hay elementos en la lista:" << endl;

   }else{
        if (primero->siguiente == NULL) {
                primero= NULL;
            } else {

                NodoDoble* aux = primero;
                primero=primero->siguiente;
                delete aux;
            }
        }
    largo--;
}



void ListaDoble:: borrarPosicion(int pos)
{
     if(ListaVacia())
     {
              cout << "Lista vacia" <<endl;
     }
     else
     {
        if((pos>largoLista())||(pos<0))
        {
        cout << "Error en posicion" << endl;
        }
        else
        {
        if(pos==1)
           BorrarInicio();
        else
        {
          if (pos == largoLista())
             BorrarFinal();
          else
          {
            int cont=2;
            NodoDoble* aux=  primero;
            while(cont<pos)
            {
             aux=aux->siguiente;
             cont++;
            }
            NodoDoble* temp=aux->siguiente;
            aux->siguiente=aux->siguiente->siguiente;
            aux->siguiente->anterior=aux;
            delete temp;
          }
        }
      }
    }
    largo--;
}


void ListaDoble::Mostrar(){
   NodoDoble *aux;
   aux = primero;
   while(aux) {
      cout << aux->llave << ";" << aux->valor << " -> ";
      aux = aux->siguiente;
   }
   cout << endl;
}

string ListaDoble::getLlave(int posicion){
    NodoDoble* aux = primero;
    if (posicion >= largoLista()){
        throw invalid_argument("Error: La posición no existe.");
    }
    for(int i = 0; i < posicion; i++){
        aux = aux->siguiente;
    }
    return aux->llave;
}

string ListaDoble::getValor(string llave){
    NodoDoble* aux = primero;
    while(aux){
        if(aux->llave == llave){
            return aux->valor;
        }
        aux = aux->siguiente;
    }
    return "";
}
