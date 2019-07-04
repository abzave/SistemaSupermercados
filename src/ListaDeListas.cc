#include "ListaDeListas.h"

ListaDeListas::ListaDeListas(){
    primero = NULL;
    largo = 0;
    for(int i = 0; i < CANTIDAD_DE_TIPOS; i++){
        InsertarFinal(to_string(i));
        largoUsuarios[i] = 0;
    }
}

ListaDeListas::~ListaDeListas(){
    while(largoLista() > 0){
        BorrarFinal();
    }
}

int ListaDeListas::largoLista(){
    return largo;

}

void ListaDeListas::InsertarFinal(string v){
    if (ListaVacia()){
        primero = new NodoListas(v);
        primero->anterior=primero;
        primero->siguiente=primero;
    }else{
        NodoListas* nuevo = new NodoListas(v);
        nuevo->anterior = primero->anterior;
        nuevo->siguiente=primero->anterior->siguiente;
        primero->anterior->siguiente=nuevo;
        primero->anterior=nuevo;
    }
}

void ListaDeListas::BorrarFinal()
{
    if (ListaVacia())
      cout << "No hay elementos en la lista:" << endl;
    else
    {
      if (primero->siguiente == primero){
        while(primero->abajo){
            eliminarAbajoFinal(primero->valor);
        }
        NodoListas* temp= primero;
        primero= NULL;
        delete temp;
      }
      else
      {
         NodoListas* aux = primero;
         while (aux->siguiente->siguiente != primero)
              aux = aux->siguiente;
         while(aux->abajo){
            eliminarAbajoFinal(aux->valor);
         }
         NodoListas* temp = aux->siguiente;
         aux->siguiente= primero;
         primero->anterior=aux;
         delete temp;
      }
    }
}

void ListaDeListas::BorrarInicio()
{
    if (ListaVacia())
      cout << "No hay elementos en la lista:" << endl;
    else
    {
     if (primero->siguiente == primero)
     {
         NodoListas* temp= primero;
        primero= NULL;
        delete temp;
     }
     else
     {
        NodoListas* aux = primero->anterior;
        NodoListas* temp= primero;
        aux->siguiente=primero->siguiente;
        primero=primero->siguiente;
        primero->anterior=aux;
        delete temp;
      }
    }
}

void ListaDeListas:: borrarPosicion(int pos)
{

  if(ListaVacia())
    cout << "Lista vacia" <<endl;
  else
  {
   if((pos>largoLista())||(pos<0))
        cout << "Error en posicion" << endl;
   else
   {
      if(pos==1)
        BorrarInicio();
      else
      {
       int cont=2;
       NodoListas* aux=  primero;
       while(cont<pos)
       {
         aux=aux->siguiente;
         cont++;
       }
       NodoListas* temp = aux->siguiente;
       aux->siguiente=aux->siguiente->siguiente;
       delete temp;
     }
    }
  }
}

void ListaDeListas::Mostrar(){
   NodoListas* aux=primero;
   while(aux->siguiente!=primero)
     {

      cout << aux->valor << "-> ";
      aux = aux->siguiente;
     }
     cout<<aux->valor<<"->";
     cout<<endl;
}

bool ListaDeListas::ListaVacia(){
    return primero == NULL;
}

void ListaDeListas::insertarUsuario(string datos, string cedula, string tipo){
    NodoListas *aux = primero;
    while(tipo != aux->valor){
        aux = aux->siguiente;
    }
    if(!aux->abajo){
        aux->abajo = new NodoDoble(datos, cedula);
        aux->abajo->siguiente = aux->abajo;
        aux->abajo->anterior = aux->abajo;
    }else{
        NodoDoble *aux2 = aux->abajo->anterior;
        NodoDoble* nuevo = new NodoDoble(datos, cedula);
        nuevo->anterior = aux2;
        nuevo->siguiente = aux->abajo;
        aux->abajo->anterior=nuevo;
        aux2->siguiente=nuevo;
    }
    largoUsuarios[atoi(tipo.c_str())]++;

}

void ListaDeListas::mostrarAbajo(string tipo){
    NodoListas *aux = primero;
    while(tipo != aux->valor){
        aux = aux->siguiente;
    }
    NodoDoble* aux2 = aux->abajo;
    while(aux2->siguiente!=aux->abajo){
      cout << aux2->llave << ";" << aux2->valor << " -> ";
      aux2 = aux2->siguiente;
     }
     cout << aux2->llave << ";" << aux2->valor << " -> ";
     cout<<endl;
}

string ListaDeListas::getLlave(unsigned int posicion, string tipo){
    NodoListas *aux = primero;
    while(tipo != aux->valor){
        aux = aux->siguiente;
    }
    NodoDoble* aux2 = aux->abajo;
    if(aux2){
        aux2 = aux2->siguiente;
        unsigned int i;
        for(i = 0; i < posicion && aux2 != aux->abajo; i++){
            aux2 = aux2->siguiente;
        }
        if(i != posicion){
            throw invalid_argument("Error: Posicion no valida.");
        }else{
            return aux2->llave;
        }
    }else{
        throw invalid_argument("Error: Posicion no valida.");
    }
}

int ListaDeListas::getLargoUsuarios(string tipo){
    return largoUsuarios[atoi(tipo.c_str())];
}

void ListaDeListas::eliminarAbajoFinal(string tipo){
     NodoListas *aux = primero;
    while(tipo != aux->valor){
        aux = aux->siguiente;
    }
    NodoDoble *aux2 = aux->abajo;
    if (aux2){
        NodoDoble* temp = aux->abajo;
        if (aux->abajo->siguiente == aux->abajo){
            aux->abajo = NULL;
            delete temp;
        }else{
            while (temp->siguiente->siguiente != aux->abajo)
                temp = temp->siguiente;
            NodoDoble* temp2 = temp->siguiente;
            temp->siguiente= aux->abajo;
            aux->abajo->anterior=temp;
            delete temp2;
      }
    }
    largoUsuarios[atoi(tipo.c_str())]--;
}

string ListaDeListas::getValorUsuario(string cedula, string tipo){
     NodoListas *aux = primero;
    while(tipo != aux->valor){
        aux = aux->siguiente;
    }
    NodoDoble* aux2 = aux->abajo;
    while(aux2->siguiente != aux->abajo){
        if(aux2->llave == cedula){
            return aux2->valor;
        }
        aux2 = aux2->siguiente;
    }
    if(aux2->llave == cedula){return aux2->valor;}
    return "";
}

string ListaDeListas::getCedula(string tipo, int pos){
    NodoListas *aux = primero;
    while(tipo != aux->valor){
        aux = aux->siguiente;
    }
    NodoDoble* aux2 = aux->abajo;
    for(int i = 0; i < pos; i++){
        aux2 = aux2->siguiente;
    }
    return aux2->llave;
}

