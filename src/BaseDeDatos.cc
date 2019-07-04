/*
 * Creado por: Abraham Meza Vega
 * Última modificación: 19/09/18
 * Versión: C++11
 */

#include "BaseDeDatos.h"

ListaSimple BaseDeDatos::listaSolicitud;
ListaSimple BaseDeDatos::productosVendidos;
ListaSimple BaseDeDatos::registroDeCompras;
ListaSimple BaseDeDatos::visitasSuper;
ListaSimple BaseDeDatos::actividadDeAdministradores;
string BaseDeDatos::ultimoModificado = "Todavia no ha habido modificaciones\n";
string BaseDeDatos::ultimoEliminado = "Todavia no se han eliminados productos\n";

BaseDeDatos::BaseDeDatos(){
    cargarInformacion();
}

BaseDeDatos::~BaseDeDatos(){
    listaDeListasUsuarios.~ListaDeListas();
    listaDobleCircularInventario.~ListaDobleCircular();
    listaDobleSuper.~ListaDoble();
    listaSimpleCiudades.~ListaSimple();
    listaSolicitud.~ListaSimple();
    productosVendidos.~ListaSimple();
    registroDeCompras.~ListaSimple();
    visitasSuper.~ListaSimple();
    actividadDeAdministradores.~ListaSimple();
}

/*
 * Funcionamiento: Carga la información de los archivos
 */
void BaseDeDatos::cargarInformacion(){
    cargarCiudades();
    cargarUsuarios();
    cargarSupers();
    cargarInventario();
}

/*
 * Funcionamiento: Carga la información del archivo "Ciudad.txt" y la guarda en una lista simple
 */
void BaseDeDatos::cargarCiudades(){
    string datosCiudad;
    ifstream archivo("Ciudad.txt");
    while(getline(archivo, datosCiudad)){
        string codCiudad = obtenerPrimerCod(datosCiudad);
        string nombre = quitarLlave(datosCiudad, ES_PRIMERO);
        if(esCodCiudadValido(datosCiudad)){
            listaSimpleCiudades.InsertarFinal(nombre, codCiudad);
        }
    }
    archivo.close();
}

/*
 * Funcionamiento: Carga la información del archivo "Usuarios.txt" y la guarda en una lista de listas
 */
void BaseDeDatos::cargarUsuarios(){
    string datosUsuario;
    ifstream archivo("Usuarios.txt");
    while(getline(archivo, datosUsuario)){
        string cedula = obtenerLlave(datosUsuario);
        string tipo = obtenerTipo(datosUsuario);
        string codCiudad = obtenerPrimerCod(datosUsuario);
        if(esCedulaValida(cedula, tipo) && existeCodCiudad(codCiudad)){
            datosUsuario = quitarLlave(datosUsuario, ES_SEGUNDO);
            datosUsuario = quitarTipo(datosUsuario);
            listaDeListasUsuarios.insertarUsuario(datosUsuario, cedula, tipo);
        }
    }
    archivo.close();
}

/*
 * Funcionamiento: Carga la información del archivo "supermercado.txt" y la guarda en una lista doble
 */
void BaseDeDatos::cargarSupers(){
    string datosSuper;
    ifstream archivo("supermercado.txt");
    while(getline(archivo, datosSuper)){
        string codCiudad = obtenerPrimerCod(datosSuper);
        string codSuper = obtenerLlave(datosSuper);
        if(existeCodCiudad(codCiudad) && !existeCodSuper(codSuper)){
            datosSuper = quitarLlave(datosSuper, ES_SEGUNDO);
            listaDobleSuper.InsertarFinal(codSuper, datosSuper);
        }
    }
    archivo.close();
}

/*
 * Funcionamiento: Carga la información del archivo "Inventario.txt" y la guarda en una lista doble circular
 */
void BaseDeDatos::cargarInventario(){
    string datosProducto;
    ifstream archivo("Inventario.txt");
    while(getline(archivo, datosProducto)){
        string codSuper = obtenerPrimerCod(datosProducto);
        string codProducto = obtenerLlave(datosProducto);
        if(existeCodSuper(codSuper) && !existeCodProducto(codProducto)){
            datosProducto = quitarLlave(datosProducto, ES_SEGUNDO);
            listaDobleCircularInventario.InsertarFinal(datosProducto, codProducto);
        }
    }
    archivo.close();
}

/*
 * Funcionamiento: Verifica si el código de la ciudad ya existe
 * Entradas: Datos de la ciudad a verificar
 * Salidas: true/false si el código de los ciudad no existe
 */
bool BaseDeDatos::esCodCiudadValido(string datosCiudad){
    if(listaSimpleCiudades.ListaVacia()){
        return true;
    }else{
        string codCiudad = obtenerPrimerCod(datosCiudad);
        return !existeCodCiudad(codCiudad);
    }
}

/*
 * Funcionamiento: Recorta los datos dados dejando solo el primer código
 * Entradas: Datos a particionar
 * Salidas: string con el primer código de los datos
 */
string BaseDeDatos::obtenerPrimerCod(string datos){
    int primerSeparador = datos.find(";");
    string codCiudad = datos.substr(0, primerSeparador);
    return codCiudad;
}

/*
 * Funcionamiento: Verifica si ya existe un código de ciudad
 * Entradas: Código de ciudad a verificar
 * Salidas: true/false si ya existe el código
 */
bool BaseDeDatos::existeCodCiudad(string codCiudad){
    for(int i = 0; i < listaSimpleCiudades.largoLista(); i++){
        string codLista = obtenerPrimerCod(listaSimpleCiudades.getLlave(i));
        if(codCiudad == codLista){
            return true;
        }
    }
    return false;
}

/*
 * Funcionamiento: Quita el primer o segundo código de los datos
 * Entradas: datos a modificar y true/false si el código se encuentra al inicio
 * Salidas: datos sin el código removido
 */
string BaseDeDatos::quitarLlave(string datos, bool estaAlInicio){
    int primerSeparador = datos.find(";");
    int largoDatos = datos.length() - 1;
    if(estaAlInicio){
        return datos.substr(primerSeparador + 1, largoDatos);
    }else{
        string primerDato = datos.substr(0, primerSeparador);
        datos = datos.substr(primerSeparador + 1, largoDatos);
        primerSeparador = datos.find(";");
        datos = datos.substr(primerSeparador + 1, largoDatos);
        return primerDato + ";" + datos;
    }
}

/*
 * Funcionamiento: Quita el último caracter de un string
 * Entradas: Datos de un usuario
 * Salidas: datos sin el último caracter
 */
string BaseDeDatos::quitarTipo(string datosUsuario){
    int largoDatos = datosUsuario.length() - 1;
    return datosUsuario.substr(0, largoDatos - 1);
}

/*
 * Funcionamiento: Particiona un string para quedarse solo con el segundo código
 * Entradas: datos a particionar
 * Salidas: código particionado
 */
string BaseDeDatos::obtenerLlave(string datos){
    int primerSeparador = datos.find(";");
    int segundoSeparador = datos.find(";", primerSeparador + 1);
    return datos.substr(primerSeparador + 1, segundoSeparador - 3);
}

/*
 * Funcionamiento: Devuelve el último caracter de un string
 * Entradas: Datos de un usuario
 * Salidas: Ultimo caracter del string
 */
string BaseDeDatos::obtenerTipo(string datosUsuario){
    int largoDatos = datosUsuario.length() - 1;
    if(datosUsuario[largoDatos] == 13){
        largoDatos--;
    }
    string tipo = "";
    return tipo += datosUsuario[largoDatos];
}

/*
 * Funcionamiento: Verifca si una cedula existe
 * Entradas: cédula del usuario y el tipo del mismo
 * Salidas: true/false si la cédula existe
 */
bool BaseDeDatos::esCedulaValida(string cedula, string tipo){
    for(int i = 0; i < listaDeListasUsuarios.getLargoUsuarios(tipo); i++){
        if(cedula == listaDeListasUsuarios.getLlave(i, tipo)){
            return false;
        }
    }
    return true;
}

/*
 * Funcionamiento: Verifica si existe un código de un super
 * Entradas: Código del super
 * Salidas: true/false si el código existe
 */
bool BaseDeDatos::existeCodSuper(string codSuper){
    for(int i = 0; i < listaDobleSuper.largoLista(); i++){
        if(codSuper == listaDobleSuper.getLlave(i)){
            return true;
        }
    }
    return false;
}

/*
 * Funcionamiento: verifica si existe un código de producto
 * Entradas: código del producto
 * Salidas: true/false si este existe
 */
bool BaseDeDatos::existeCodProducto(string codProducto){
    for(int i = 0; i < listaDobleCircularInventario.largoLista(); i++){
        if(codProducto == listaDobleCircularInventario.getLlave(i)){
            return true;
        }
    }
    return false;
}

/*
 * Funcionamiento: Verifica si exite un producto en un super
 * Entradas: código del producto y el código del super
 * Salidas: true/false si el producto está es ese super
 */
bool BaseDeDatos::existeProductoEnSuper(string codProducto, string codSuper){
    for(int i = 0; i < listaDobleCircularInventario.largoLista(); i++){
        string codProductoTemp = listaDobleCircularInventario.getLlave(i);
        string codSuperTemp = listaDobleCircularInventario.getValor(codProductoTemp);
        codSuperTemp = obtenerPrimerCod(codSuperTemp);
        if(codProducto == codProductoTemp && codSuper == codSuperTemp){
            return true;
        }
    }
    return false;
}

/*
 * Funcionamiento: Añade un elemento a las lista de solicitudes
 * Entradas: datos del usuario(ciudad, cedula, nombre y telefono)
 */
void BaseDeDatos::agregarSolicitud(string ciudad, string cedula, string nombre, string telefono){
    string codCiudad = obtenerCodDeCiudad(ciudad);
    string datosUsuario = codCiudad + ";" + nombre + ";" + telefono + ";0";
    listaSolicitud.InsertarFinal(datosUsuario, cedula);
}

/*
 * Funcionamiento: Dada una ciudad este busca el código de la misma
 * Entradas: nombre de la ciudad
 * Salidas: código de la ciudad
 */
string BaseDeDatos::obtenerCodDeCiudad(string ciudad){
    for(int i = 0; i < listaSimpleCiudades.largoLista(); i++){
        if(ciudad == listaSimpleCiudades.getValor(i)){
            return listaSimpleCiudades.getLlave(i);
        }
    }
    return "";
}

/*
 * Funcionamiento: Dado un código de producto busca su nombre
 * Entradas: código del producto
 * Salidas: nombre del producto
 */
string BaseDeDatos::getNombreProducto(string codProducto){
    string datos = listaDobleCircularInventario.getValor(codProducto);
    string nombre = obtenerLlave(datos);
    return nombre;
}

/*
 * Funcionamiento: Busca la cantidad existente de un producto
 * Entradas: código del producto
 * Salidas: cantidad del producto
 */
int BaseDeDatos::getCantidadProducto(string codProducto){
    string datos = listaDobleCircularInventario.getValor(codProducto);
    int primerSeparador = datos.find(";");
    int segundoSeparador = datos.find(";", primerSeparador + 1);
    int tercerSeparador = datos.find(";", segundoSeparador + 1);
    return atoi(datos.substr(segundoSeparador + 1, tercerSeparador - 3).c_str());
}

/*
 * Funcionamiento: Reduce la cantidad de un producto
 * Entradas: código del producto y la cantidad a restar
 */
void BaseDeDatos::quitarCantidadProducto(string codProducto, int cantidad){
    string datos;
    if(cantidad == COMPRAR_TODO){
        datos = cambiarCantidad(codProducto, "0");
    }else{
        int total = getCantidadProducto(codProducto);
        total -= cantidad;
        datos = cambiarCantidad(codProducto, to_string(total));
    }
    listaDobleCircularInventario.actualizarLista(codProducto, datos);
}

/*
 * Funcionamiento: Actualiza la cantidad de un producto
 * Entradas: código del producto y la nueva cantidad
 * Salidas: Datos del producto con la cantidad actualizada
 */
string BaseDeDatos::cambiarCantidad(string codProducto, string cantidad){
    string datos = listaDobleCircularInventario.getValor(codProducto);
    int primerSeparador = datos.find(";");
    int segundoSeparador = datos.find(";", primerSeparador + 1);
    int tercerSeparador = datos.find(";", segundoSeparador + 1);
    string precio = datos.substr(tercerSeparador + 1, datos.length() - 1);
    datos = datos.substr(0, segundoSeparador + 1);
    datos += cantidad + ";" + precio;
    return datos;
}

/*
 * Funcionamiento: Aumenta la cantidad de un producto
 * Entradas: código del producto y la cantidad a añadir
 */
void BaseDeDatos::agregarCantidadProducto(string codProducto, int cantidad){
    int total = getCantidadProducto(codProducto);
    total += cantidad;
    string datos = cambiarCantidad(codProducto, to_string(total));
    listaDobleCircularInventario.actualizarLista(codProducto, datos);
}

/*
 * Funcionamiento: Dada la cédula de un usuario devuelve su nombre
 * Entradas: cedula y tipo del usuario
 * Salidas: nombre del usuario
 */
string BaseDeDatos::getNombreUsuario(string cedula, string tipo){
    string nombre = "";
    string datos = listaDeListasUsuarios.getValorUsuario(cedula, tipo);
    int primerSeparador = datos.find(";");
    int segundoSeparador = datos.find(";", primerSeparador + 1);
    nombre = datos.substr(primerSeparador + 1, segundoSeparador - 3);
    return nombre;
}

/*
 * Funcionamiento: Dada la cédula del usuario devuelve su telefono
 * Entradas: cedula y tipo del usuario
 * Salidas: telefono del usuario
 */
string BaseDeDatos::getTelefonoUsuario(string cedula, string tipo){
    string datos = listaDeListasUsuarios.getValorUsuario(cedula, tipo);
    int primerSeparador = datos.find(";");
    int segundoSeparador = datos.find(";", primerSeparador + 1);
    int tercerSeparador = datos.find(";", segundoSeparador + 1);
    string telefono = datos.substr(segundoSeparador + 1, tercerSeparador - 3);
    return telefono;
}

string BaseDeDatos::getInfoProducto(string codProducto){
    return listaDobleCircularInventario.getValor(codProducto);
}

string BaseDeDatos::getSolicitud(){
    return listaSolicitud.getLlave(0) + ";" + listaSolicitud.getValor(0);
}

bool BaseDeDatos::listaSolicitudVacia(){
    return listaSolicitud.ListaVacia();
}

/*
 * Funcionamiento: Pasa datos de la lista de solicitudes a la lista de usuarios
 */
void BaseDeDatos::aceptarSolicitud(){
    string llave = listaSolicitud.getLlave(0);
    string datos = listaSolicitud.getValor(0);
    string tipo = obtenerTipo(datos);
    datos = quitarTipo(datos);
    listaDeListasUsuarios.insertarUsuario(datos, llave, tipo);
}

void BaseDeDatos::borrarSolicitud(){
    listaSolicitud.BorrarInicio();
}

/*
 * Funcionamiento: Inserta un usuario en la sublista correspondiente
 * Entradas: Datos del usuario(cédula, nombre, telefono, ciudad y tipo)
 */
void BaseDeDatos::agregarUsuario(string cedula, string nombre, string telefono, string ciudad, string tipo){
    string codCiudad = obtenerCodDeCiudad(ciudad);
    string datos = codCiudad + ";" + nombre + ";" + telefono + ";" + tipo;
    listaDeListasUsuarios.insertarUsuario(datos, cedula, tipo);
}

/*
 * Funcionamiento: Busca un producto en el inventario
 * Entradas: posición en la lista
 * Salidas: datos del producto
 */
string BaseDeDatos::getProducto(int posicion){
    string cedula = listaDobleCircularInventario.getLlave(posicion);
    string datos = listaDobleCircularInventario.getValor(cedula);
    return cedula + ";" + datos;
}

int BaseDeDatos::getCantidadProductosInventario(){
    return listaDobleCircularInventario.largoLista();
}

/*
 * Funcionamiento: Agrega un producto a la lista de productos vendidos
 * Entradas: Código del producto y cantidad de este
 */
void BaseDeDatos::agregarProductoVendido(string codProducto, string cantidad){
    if(yaHaSidoVendido(codProducto)){
        int cant = atoi(cantidad.substr(0, cantidad.find(";")).c_str());
        for(int i = 0; i < productosVendidos.largoLista(); i++){
            string datos = productosVendidos.getLlave(i);
            if(codProducto == datos){
                string cantidadVieja = productosVendidos.getValor(i);
                int cantVieja = atoi(cantidadVieja.substr(0, cantidadVieja.find(";")).c_str());
                cant += cantVieja;
                break;
            }
        }
        cantidad = to_string(cant) + ";" + cantidad.substr(cantidad.find(";") + 1, cantidad.length());
        actualizarProductoVendido(codProducto, cantidad);
    }else{
        if(productosVendidos.ListaVacia()){
            productosVendidos.InsertarInicio(cantidad, codProducto);
        }else{
            bool agregado = false;
            for(int i = 0; i < productosVendidos.largoLista(); i++){
                string cantidadPos = productosVendidos.getValor(i);
                int cant = atoi(cantidad.substr(0, cantidad.find(";")).c_str());
                int cantPos = atoi(cantidadPos.substr(0, cantidadPos.find(";")).c_str());
                if(cant >= cantPos){
                    productosVendidos.InsertarPos(cantidad, codProducto, i);
                    agregado = true;
                    break;
                }
            }
            if(!agregado){
                productosVendidos.InsertarFinal(cantidad, codProducto);
            }
        }
    }
}

/*
 * Funcionamiento: Verifica si un producto ya ha sido vendido en el pasado
 * Entradas: código del producto
 * Salidas: true/false si ya ha sido vendido
 */
bool BaseDeDatos::yaHaSidoVendido(string codProducto){
    if(productosVendidos.ListaVacia()){
        return false;
    }else{
        for(int i = 0; i < productosVendidos.largoLista(); i++){
            if(productosVendidos.getLlave(i) == codProducto){
                return true;
            }
        }
        return false;
    }
}

void BaseDeDatos::actualizarProductoVendido(string codProducto, string cantidad){
    productosVendidos.actualizar(codProducto, cantidad);
}

string BaseDeDatos::getProductoMasVendido(){
    if(productosVendidos.ListaVacia()){
        return "Ninguno.";
    }
    string codProducto = productosVendidos.getLlave(0);
    string datos = productosVendidos.getValor(0);
    int primerSeparador = datos.find(";");
    string cantidad = datos.substr(0, primerSeparador);
    return  getNombreProducto(codProducto) + " con " + cantidad + " unidades.";
}

string BaseDeDatos::getMenosVendidos(){
    string texto = "";
    for(int i = 0; i < listaDobleSuper.largoLista(); i++){
        string codSuper = listaDobleSuper.getLlave(i);
        for(int j = productosVendidos.largoLista() - 1; j >= 0 ; j--){
            string codProducto = productosVendidos.getLlave(j);
            string datos = productosVendidos.getValor(j);
            int primerSeparador = datos.find(";");
            string codSuperProduc = datos.substr(primerSeparador + 1, datos.length()- 1);
            if(codSuper == codSuperProduc){
                texto += getNombreSuper(codSuper) + ": ";
                texto += getNombreProducto(codProducto);
                string cantidad = datos.substr(0, primerSeparador);
                texto += " con " + cantidad + " unidades.\n";
                break;
            }
        }
    }
    return texto;
}

string BaseDeDatos::getNombreSuper(string codSuper){
    string datos = listaDobleSuper.getValor(codSuper);
    int primerSeparador = datos.find(";");
    string nombreSuper = datos.substr(primerSeparador + 1, datos.length());
    return nombreSuper;
}

/*
 * Funcionamiento: Añade la compra al historial
 * Entradas: cedula del comprador y la cantidad comprada
 */
void BaseDeDatos::registrarCompra(string cedula, int cantidad){
    if(yaHaComprado(cedula)){
        for(int i = 0; i < registroDeCompras.largoLista(); i++){
            if(cedula == registroDeCompras.getLlave(i)){
                string cantidadGuarda = registroDeCompras.getValor(i);
                cantidad += atoi(cantidadGuarda.c_str());
                registroDeCompras.actualizar(cedula, to_string(cantidad));
                break;
            }
        }
    }else{
        registroDeCompras.InsertarInicio(to_string(cantidad), cedula);
    }
}

bool BaseDeDatos::yaHaComprado(string cedula){
    return registroDeCompras.existeLlave(cedula);
}

string BaseDeDatos::getMayorComprador(){
    string cedula = "";
    int cantidad = 0;
    for(int i = 0; i < registroDeCompras.largoLista(); i++){
        int cantidadGuardada = atoi(registroDeCompras.getValor(i).c_str());
        if(cantidadGuardada >= cantidad){
            cedula = registroDeCompras.getLlave(i);
            cantidad = cantidadGuardada;
        }
    }
    if(cedula != ""){
        string posibleNombre = getNombreUsuario(cedula, "0");
        if(posibleNombre != ""){
            return posibleNombre + " con " + to_string(cantidad) + " productos comprados";
        }else{
            return getNombreUsuario(cedula, "3") + " con " + to_string(cantidad) + " productos comprados";
        }
    }else{
        return "Ninguno";
    }
}

string BaseDeDatos::getMenorComprador(){
    string cedula = "";
    if(registroDeCompras.ListaVacia()){
        return "Ninguno";
    }
    int cantidad = atoi(registroDeCompras.getValor(0).c_str());
    for(int i = 0; i < registroDeCompras.largoLista(); i++){
        int cantidadGuardada = atoi(registroDeCompras.getValor(i).c_str());
        if(cantidadGuardada <= cantidad){
            cedula = registroDeCompras.getLlave(i);
            cantidad = cantidadGuardada;
        }
    }
    if(cedula != ""){
        string posibleNombre = getNombreUsuario(cedula, "0");
        if(posibleNombre != ""){
            return posibleNombre + " con " + to_string(cantidad) + " productos comprados";
        }else{
            return getNombreUsuario(cedula, "3") + " con " + to_string(cantidad) + " productos comprados";
        }
    }
    return "Ninguno";
}

/*
 * Funcionamiento: Devuelve la cantidad de compras realizadas por cada usuario
 * Salidas: Registro de compras con formato
 */
string BaseDeDatos::cantidadDeCompras(){
    if(registroDeCompras.ListaVacia()){
        return "No ha habido compras aun.";
    }
    string texto = "";
    for(int i = 0; i < registroDeCompras.largoLista(); i++){
        string cedula = registroDeCompras.getLlave(i);
        string cantidadCompras = registroDeCompras.getValor(i);
        string posibleNombre = getNombreUsuario(cedula, "0");
        if(posibleNombre != ""){
            texto += posibleNombre + " con " + cantidadCompras + " productos comprados\n";
        }else{
            texto += getNombreUsuario(cedula, "3") + " con " + cantidadCompras + " productos comprados\n";
        }
    }
    return texto;
}

/*
 * Funcionamiento: Añade una visita a un super al registro
 * Entradas: código del super visitado
 */
void BaseDeDatos::agregarVisitaSuper(string codSuper){
    if(visitasSuper.ListaVacia()){
        visitasSuper.InsertarInicio("1", codSuper);
    }else{
        if(yaHaSidoVisitado(codSuper)){
            string visitasPrevias;
            for(int i = 0; i < visitasSuper.largoLista(); i++){
                if(visitasSuper.getLlave(i) == codSuper){
                    visitasPrevias = visitasSuper.getValor(i);
                    break;
                }
            }
            int visitas = atoi(visitasPrevias.c_str());
            visitas++;
            visitasSuper.actualizar(codSuper, to_string(visitas));
        }else{
            visitasSuper.InsertarInicio("1", codSuper);
        }
    }
}

/*
 * Funcionamiento: Verifica si un super ya ha sido visitado
 * Entradas: código del super
 * Salidas: true/false si ya ha sido visitado
 */
bool BaseDeDatos::yaHaSidoVisitado(string codSuper){
    if(visitasSuper.ListaVacia()){
        return false;
    }else{
        for(int i = 0; i < visitasSuper.largoLista(); i++){
            if(visitasSuper.getLlave(i) == codSuper){
                return true;
            }
        }
        return false;
    }
}

string BaseDeDatos::getSuperMasVisitado(){
    if(visitasSuper.ListaVacia()){
        return "Aun no han habido compras.";
    }else{
        int pos = 0;
        int visitas = 0;
        for(int i = 0; i < visitasSuper.largoLista(); i++){
            int visitasAux = atoi(visitasSuper.getValor(i).c_str());
            if(visitasAux > visitas){
                pos = i;
                visitas = visitasAux;
            }
        }
        string nombreSuper = getNombreSuper(visitasSuper.getLlave(pos));
        return "El super mas visitado es " + nombreSuper + " con " + to_string(visitas) + " visitas.";
    }
}

string BaseDeDatos::getSuperMenosVisitado(){
    if(visitasSuper.ListaVacia()){
        return "Aun no han habido compras.";
    }else{
        int pos = 0;
        int visitas = atoi(visitasSuper.getValor(0).c_str());
        for(int i = 0; i < visitasSuper.largoLista(); i++){
            int visitasAux = atoi(visitasSuper.getValor(i).c_str());
            if(visitasAux < visitas){
                pos = i;
                visitas = visitasAux;
            }
        }
        string nombreSuper = getNombreSuper(visitasSuper.getLlave(pos));
        return "El super menos visitado es " + nombreSuper + " con " + to_string(visitas) + " visitas.";
    }
}

/*
 * Funcionamiento: Agrega un log geo de un administrador al registro
 * Entradas: cedula del administrador
 */
void BaseDeDatos::agregarActividadAdmin(string cedula){
    if(actividadDeAdministradores.ListaVacia()){
        actividadDeAdministradores.InsertarInicio("1", cedula);
    }else{
        if(yaHaSidoVisitado(cedula)){
            string accionesPrevias;
            for(int i = 0; i < actividadDeAdministradores.largoLista(); i++){
                if(actividadDeAdministradores.getLlave(i) == cedula){
                    accionesPrevias = actividadDeAdministradores.getValor(i);
                    break;
                }
            }
            int acciones = atoi(accionesPrevias.c_str());
            acciones++;
            actividadDeAdministradores.actualizar(cedula, to_string(acciones));
        }else{
            actividadDeAdministradores.InsertarInicio("1", cedula);
        }
    }
}

string BaseDeDatos::getMejorAdmin(){
    if(actividadDeAdministradores.ListaVacia()){
        return "Todavia no ha ingresado administradores";
    }else{
        int pos = 0;
        int actividades = 0;
        for(int i = 0; i < actividadDeAdministradores.largoLista(); i++){
            int actividadesAux = atoi(actividadDeAdministradores.getValor(i).c_str());
            if(actividadesAux > actividades){
                pos = i;
                actividades = actividadesAux;
            }
        }
        string nombreAdmin = getNombreUsuario(actividadDeAdministradores.getLlave(pos), "1");
        return "El administrador que mas trabajo fue " + nombreAdmin + " con " + to_string(actividades) + " actividades realizadas.";
    }
}

string BaseDeDatos::getPeorAdmin(){
    if(actividadDeAdministradores.ListaVacia()){
        return "Todavia no ha ingresado administradores";
    }else{
        string texto = "Admistradores que no trabajaron: \n";
        for(int i = 0; i < listaDeListasUsuarios.getLargoUsuarios("1"); i++){
            bool agregar = true;
            string cedula = listaDeListasUsuarios.getCedula("1", i);
            for(int j = 0; j < actividadDeAdministradores.largoLista(); j++){
                string cedulaAdmin = actividadDeAdministradores.getLlave(j);
                if(cedula == cedulaAdmin){
                    agregar = false;
                    break;
                }
            }
            if(agregar){
                texto += getNombreUsuario(cedula, "1") + "\n";
            }
        }
        return texto;
    }
}

string BaseDeDatos::getProductosSuper(string codSuper){
    if(!existeCodSuper(codSuper)){
        return "El super no existe.";
    }
    bool tieneProductos = false;
    string texto = "El super " + getNombreSuper(codSuper) + " tiene:\n\n";
    for(int i = 0; i < listaDobleCircularInventario.largoLista(); i++){
        string codProducto = listaDobleCircularInventario.getLlave(i);
        string codSuperTemp = listaDobleCircularInventario.getValor(codProducto);
        codSuperTemp = obtenerPrimerCod(codSuperTemp);
        if(codSuper == codSuperTemp){
            texto += "Codigo: " + codProducto + "\n";
            texto += "Producto: " + getNombreProducto(codProducto) + "\n\n";
            tieneProductos = true;
        }
    }
    if(!tieneProductos){
        texto += "El inventario vacio\n";
    }
    return texto;
}

/*
 * Funcionamiento: Eliminau un producto del inventario
 * Entradas: código del producto
 * Salidas: true/false si se pudo eliminar
 */
bool BaseDeDatos::eliminarDeInventario(string codProducto){
    if(!existeCodProducto(codProducto)){
        return false;
    }else{
        string nombre = getNombreProducto(codProducto);
        listaDobleCircularInventario.borrarPorLlave(codProducto);
        ultimoEliminado = "El ultimo producto elimnado fue: " + nombre + "\n";
        return true;
    }
}

void BaseDeDatos::agregarProducto(string codProducto, string datos){
    listaDobleCircularInventario.InsertarInicio(datos, codProducto);
}

/*
 * Funcionamiento: Cambia el códgo del super de un producto
 * Entradas: código del producto y código del super
 */
void BaseDeDatos::actualizarCodSuper(string codProducto, string codSuper){
    string datos = listaDobleCircularInventario.getValor(codProducto);
    string nombre = getNombreProducto(codProducto);
    datos = quitarLlave(datos, ES_PRIMERO);
    datos = codSuper + ";" + datos;
    listaDobleCircularInventario.actualizarLista(codProducto, datos);
    ultimoModificado = "El ultimo producto modificado fue: " + nombre + "al que se le cambio el codigo del super por: " + codSuper + "\n";
}

/*
 * Funcionamiento: Cambia el nombre de un producto
 * Entradas: código del producto y el nuevo nombre
 */
void BaseDeDatos::actualizarNombreProducto(string codProducto, string nombre){
    string datos = listaDobleCircularInventario.getValor(codProducto);
    string nombreViejo = getNombreProducto(codProducto);
    string codSuper = obtenerPrimerCod(datos);
    datos = quitarLlave(datos, ES_PRIMERO);
    datos = quitarLlave(datos, ES_PRIMERO);
    datos = codSuper + ";" + nombre + ";" + datos;
    listaDobleCircularInventario.actualizarLista(codProducto, datos);
    ultimoModificado = "El ultimo producto modificado fue: " + nombreViejo + "al que se le cambio el nombre por: " + nombre + "\n";
}

/*
 * Funcionamiento: cambia la cantidad de un producto
 * Entradas: Código del producto y la nueva cantidad
 */
void BaseDeDatos::actualizarCantidadProducto(string codProducto, string cantidad){
    string nombre = getNombreProducto(codProducto);
    string datos = cambiarCantidad(codProducto, cantidad);
    listaDobleCircularInventario.actualizarLista(codProducto, datos);
    ultimoModificado = "El ultimo producto modificado fue: " + nombre + "al que se le cambio la cantidad por: " + cantidad + "\n";
}

/*
 * Funcionamiento: Cambia el precio de un producto
 * Entradas: código del producto y el nuevo precio
 */
void BaseDeDatos::actualizarPrecioProducto(string codProducto, string precio){
    string datos = listaDobleCircularInventario.getValor(codProducto);
    string codSuper = obtenerPrimerCod(datos);
    datos = quitarLlave(datos, ES_PRIMERO);
    string nombre = obtenerPrimerCod(datos);
    datos = quitarLlave(datos, ES_PRIMERO);
    string cantidad = obtenerPrimerCod(datos);
    datos = codSuper + ";" + nombre + ";" + cantidad + ";" + precio;
    listaDobleCircularInventario.actualizarLista(codProducto, datos);
    ultimoModificado = "El ultimo producto modificado fue: " + nombre + " al que se le cambio el precio por: " + precio + "\n";
}

string BaseDeDatos::getUltimoEliminado(){
    return ultimoEliminado;
}

string BaseDeDatos::getUltimoModificado(){
    return ultimoModificado;
}
