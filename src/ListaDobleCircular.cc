#include "ListaDobleCircular.h"

#include <exception>

ListaDobleCircular::ListaDobleCircular(){
    primero = NULL;
    largo = 0;
}

ListaDobleCircular::~ListaDobleCircular(){
    while(primero) {
        BorrarInicio();
   }
}

int ListaDobleCircular::largoLista(){
    return largo;

}

void ListaDobleCircular::InsertarInicio(string v, string llave){
   if (ListaVacia()){
     primero = new NodoDoble(v, llave);
     primero->anterior=primero;
     primero->siguiente=primero;
   }else{
     NodoDoble* nuevo=new NodoDoble (v, llave);
     nuevo->siguiente=primero;
     nuevo->anterior= primero->anterior;
     primero->anterior->siguiente=nuevo;
     nuevo->siguiente->anterior=nuevo;
     primero= nuevo;
   }
   largo++;
}

void ListaDobleCircular::InsertarFinal(string v, string llave){
   if (ListaVacia()){
     primero = new NodoDoble(v, llave);
     primero->anterior=primero;
     primero->siguiente=primero;
   }else{
     NodoDoble* nuevo = new NodoDoble(v, llave);
     nuevo->anterior = primero->anterior;
     nuevo->siguiente=primero->anterior->siguiente;
     primero->anterior->siguiente=nuevo;
     primero->anterior=nuevo;
    }
    largo++;
}


void ListaDobleCircular::InsertarPos(string v, string llave,int pos)
{
   if (ListaVacia())
   {
     primero = new NodoDoble(v, llave);
     primero->anterior=primero;
     primero->siguiente=primero;
   }
   else
   {
      if(pos <=1)
        InsertarInicio(v, llave);
       else
       {
        if (pos==largoLista())
          InsertarFinal(v, llave);
        else
        {
             NodoDoble* aux= primero;
             int i =2;
             while((i != pos )&&(aux->siguiente!= primero))
             {
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
   }
   largo++;
}

void ListaDobleCircular::BorrarFinal()
{
    if (ListaVacia())
      cout << "No hay elementos en la lista:" << endl;
    else{
      if (primero->siguiente == primero){
        NodoDoble* temp= primero;
        primero= NULL;
        delete temp;
      }else{
         NodoDoble* aux = primero;
         while (aux->siguiente->siguiente != primero)
              aux = aux->siguiente;
         NodoDoble* temp = aux->siguiente;
         aux->siguiente= primero;
         primero->anterior=aux;
         delete temp;
      }
      largo--;
    }
}

void ListaDobleCircular::BorrarInicio()
{
    if (ListaVacia())
      cout << "No hay elementos en la lista:" << endl;
    else
    {
     if (primero->siguiente == primero)
     {
         NodoDoble* temp= primero;
        primero= NULL;
        delete temp;
     }
     else{
        NodoDoble* aux = primero->anterior;
        NodoDoble* temp= primero;
        aux->siguiente=primero->siguiente;
        primero=primero->siguiente;
        primero->anterior=aux;
        delete temp;
      }
       largo--;
    }
}

void ListaDobleCircular:: borrarPorLlave(string llave){
  if(ListaVacia())
    cout << "Lista vacia" <<endl;
  else{
       NodoDoble* aux =  primero;
       while(aux->siguiente != primero){
         if(aux->llave == llave){
            break;
         }
         aux=aux->siguiente;
       }
       NodoDoble* temp = aux;
       if(aux == primero->anterior){
            if(aux->llave != llave){
                throw invalid_argument("La llave no existe.");
            }else{
                BorrarFinal();
            }
       }else if(aux == primero){
            BorrarInicio();
       }else{
            aux->anterior->siguiente = aux->siguiente;
            aux->siguiente->anterior = aux->anterior;
            largo--;
       }
       delete temp;
    }
}

void ListaDobleCircular::borrarPos(int pos){
    if (pos >= largoLista()){
        throw invalid_argument("Posicion no valida.");
    }
  if(ListaVacia()){
    cout << "Lista vacia" <<endl;
  }else if(pos < 1){
      BorrarInicio();
  }else if(pos == largoLista() - 1){
    BorrarFinal();
  }else{
       NodoDoble* aux =  primero;
       for(int i = 0; i < pos; i++){
            aux = aux->siguiente;
       }
       NodoDoble* temp = aux;
        aux->anterior->siguiente = aux->siguiente;
        aux->siguiente->anterior = aux->anterior;
       delete temp;
       largo--;
    }
}

void ListaDobleCircular::Mostrar(){
    if(!ListaVacia()){
       NodoDoble* aux=primero;
       while(aux->siguiente!=primero)
         {

          cout << aux->llave << ";" << aux->valor << " -> ";
          aux = aux->siguiente;
         }
         cout << aux ->llave << ";" <<aux->valor<<" ->";
         cout<<endl;
    }
}

bool ListaDobleCircular::ListaVacia(){
    return primero == NULL;
}

string ListaDobleCircular::getLlave(int posicion){
    if(posicion >= largoLista()){
        throw invalid_argument("Error: Posicion no valida.");
    }
    NodoDoble* aux = primero;
    for(int i = 0; i < posicion; i++){
        aux = aux->siguiente;
    }
    return aux->llave;
}

string ListaDobleCircular::getValor(string llave){
    NodoDoble* aux = primero;
    while(aux->siguiente != primero){
        if(aux->llave == llave){
            return aux->valor;
        }
        aux = aux->siguiente;
    }
    if (aux->llave == llave){return aux->valor;}
    return "";
}

void ListaDobleCircular::actualizarLista(string llave, string valor){
    NodoDoble* aux = primero;
    while(aux->siguiente != primero){
        if(aux->llave == llave){
            aux->valor = valor;
            break;
        }
        aux = aux->siguiente;
    }
    if (aux->llave == llave){aux->valor = valor;}
}

bool ListaDobleCircular::existeLlave(string llave){
    NodoDoble* aux = primero;
    if(ListaVacia()){return false;}
    while(aux->siguiente != primero){
        if(aux->llave == llave){
            return true;
        }
        aux = aux->siguiente;
    }
    if (aux->llave == llave){return true;}
    return false;
}
