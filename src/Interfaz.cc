#include "Interfaz.h"

/*
 * Funcionamiento: Pide al usuario el tipo de ingreso
 * Salidas: Tipo de usuario ingresado
 */
string Interfaz::pedirTipoUsuario(){
    string tipoUsuario;
    do{
        cout << "Ingrese el tipo de usuario: ";
        cin >> tipoUsuario;
    }while(!esTipoValido(tipoUsuario));
    return tipoUsuario;
}

/*
 * Funcionamiento: Pide al usuario su cédula
 * Salidas: Cédula ingresada
 */
string Interfaz::pedirCedula(){
    string cedula;
    do{
        cout << "Ingrese el numero de cedula: ";
        cin >> cedula;
    }while(!esCedulaValida(cedula));
    return cedula;
}

/*
 * Funcionamiento: Valida la cédula ingresada
 * Entradas: número de cédula
 * Salidas: true/false si es valida
 */
bool Interfaz::esCedulaValida(string cedula){
    Validacion validar;
    if(!validar.esNumerico(cedula)){
        cout << "Error: Debe ingresar una cedula numerica." << endl;
        return false;
    }else if(cedula.length() != 4){
        return false;
    }else{
        return true;
    }
}

/*
 * Funcionamiento: Valida el tipo de usuario
 * Entradas: tipo de usuario a validar
 * Salidas: true/false si el tipo es valido
 */
bool Interfaz::esTipoValido(string tipoUsuario){
    Validacion validar;
    if(!validar.esUnCaracter(tipoUsuario)){
        cout << "Error: El tipo debe ser un solo numero." << endl;
        return false;
    }else if(!validar.esNumerico(tipoUsuario)){
        cout << "Error: El tipo debe ser un numero." << endl;
        return false;
    }else if(!validar.estaDentroDelRangoDeTipo(tipoUsuario)){
        cout << "Error: El tipo debe estar entre 0 y 3" << endl;
        return false;
    }else{
        return true;
    }
}

/*
 * Funcionamiento: Pregunta al usuario que si quiere registrarse
 * Salidas: true/false si el usuario ingresó Y/N
 */
bool Interfaz::preguntarRegistro(){
    Validacion validar;
    string respuesta;
    bool noEsRespuestaValida = false;
    do{
        if(noEsRespuestaValida){
            cout << "Solo puede ingresar Y o N." << endl;
        }
        cout << "No se encuentra registrado. Desea registrarse? (Y/N): ";
        cin >> respuesta;
        noEsRespuestaValida = !validar.esYoN(respuesta);
    }while(noEsRespuestaValida);
    return validar.pasarDeRespuestaABool(respuesta);
}

/*
 * Funcionamiento: Imprime el ménu principal
 * Entradas: tipo de usuario loggeado
 */
void Interfaz::imprimirMenu(string tipoUsuario){
    limpiarPantalla();
    switch(tipoUsuario[0]){
        case CLIENTE[0]:
        case CLIENTE_FUNCIONARIO[0]:
            cout << "1) Consultar precio" << endl;
            cout << "2) Consultar descuento" << endl;
            cout << "3) Consultar productos" <<  endl;
            cout << "4) Comprar" << endl;
            cout << "5) Facturacion" << endl;
            cout << "0) Salir" << endl;
            break;
        case ADMINISTRADOR[0]:
            cout << "1) Insertar producto" << endl;
            cout << "2) Eliminar producto" << endl;
            cout << "3) Modificar producto" << endl;
            cout << "4) Consultar precio" << endl;
            cout << "5) Consultar descuentos" << endl;
            cout << "6) Consultar productos de un super" << endl;
            cout << "7) Registrar clientes" << endl;
            cout << "8) Reportes" << endl;
            cout << "0) Salir" << endl;
            break;
        case VENDEDOR[0]:
            cout << "1) Consultar precio" << endl;
            cout << "2) Consultar descuento de un cliente" << endl;
            cout << "3) Consultar productos de un super" << endl;
            cout << "0) Salir" << endl;
            break;
        case CLIENTE_SIN_REGISTRAR[0]:
            cout << "1) Consultar precio" << endl;
            cout << "2) Consultar productos" << endl;
            cout << "0) Salir" << endl;
            break;
        default:
            cout << "Tipo de usuario no valido." << endl;
    }
}

/*
 * Funcionamiento: Pide al usuario una opción del menú
 * Entradas: tipo de usuario
 * Salidas: opción ingresada
 */
string Interfaz::pedirOpcion(string tipo){
    string respuesta;
    bool noEsRespuetaValida = false;
    int cantidadDeOpciones = getCantidadDeOpciones(tipo);
    do{
        if(noEsRespuetaValida){
            cout << "Debe ingresar un numero entre 0 y " << cantidadDeOpciones - 1 << endl;
        }
        cout << "Ingrese una opcion: ";
        cin >> respuesta;
        noEsRespuetaValida = !esOpcionValida(respuesta, tipo);
    }while(noEsRespuetaValida);
    return respuesta;
}

/*
 * Funcionamiento: Verifica si la opción dada es valida acorde al tipo de usuario y menú
 * Entradas: Tipo de usuario y la opción ingresada
 * Salidas: true/false si la opción es valida
 */
bool Interfaz::esOpcionValida(string respuesta, string tipoUsuario){
    int cantidadOpciones = getCantidadDeOpciones(tipoUsuario);
    Validacion validador;
    if(respuesta.length() != 1 && tipoUsuario != REPORTES){
        return false;
    }else if(!validador.esNumerico(respuesta)){
        return false;
    }else if (atoi(respuesta.c_str()) < 0 || atoi(respuesta.c_str()) >= cantidadOpciones){
        return false;
    }else if(tipoUsuario == REPORTES && respuesta.length() == 2){
        if(respuesta == "10" || respuesta == "11" || respuesta == "12"){
            return true;
        }else{
            return false;
        }
    }else{
        return true;
    }
}

int Interfaz::getCantidadDeOpciones(string tipoUsuario){
    int tipo = atoi(tipoUsuario.c_str());
    switch(tipo){
        case 0:
            return 6;
        case 1:
            return 9;
        case 2:
            return 4;
        case 3:
            return 7;
        case 4:
            return 3;
        case 5:
            return 13;
        case 6:
            return 5;
        default:
            return 0;
    }
}

/*
 * Funcionamiento: Pide al usuario la ciudad de procedencia
 * Salidas: Ciudad ingresada
 */
string Interfaz::pedirCiudad(){
    string ciudad;
    Validacion validador;
    bool noEsCiudadValida = false;
    do{
        if(noEsCiudadValida){
            cout << "La ciudad ingresada no ha sido encontrada." << endl;
        }
        cout << "Ingrese su ciudad de residencia: ";
        fflush(stdin);
        getline(cin, ciudad);
        noEsCiudadValida = !validador.existeCiudad(ciudad);
    }while(noEsCiudadValida);
    return ciudad;
}

void Interfaz::limpiarPantalla(){
    string cls;
    #ifdef __linux__
        cls = "clear";
    #else
        cls = "cls";
    #endif // __linux__
    system(cls.c_str());
}

/*
 * Funcionamiento: Pide al usuario su nombre
 * Salidas: regresa el nombre ingresado
 */
string Interfaz::pedirNombre(){
    string nombre;
    bool noEsNombreValido = false;
    do{
        if(noEsNombreValido){
            cout << "Debe ingresar su nombre." << endl;
        }
        cout << "Ingrese su nombre completo: ";
        fflush(stdin);
        getline(cin, nombre);
        noEsNombreValido = !esNombreValido(nombre);
    }while(noEsNombreValido);
    return nombre;
}

/*
 * Funcionamiento: Pide al usuario el nombre para el producto
 * Salidas: El nombre ingresado
 */
string Interfaz::pedirNombreProducto(){
    string nombre;
    bool noEsNombreValido = false;
    do{
        if(noEsNombreValido){
            cout << "El nombre no puede tener caracteres especiales." << endl;
        }
        cout << "Ingrese el nombre del producto: ";
        fflush(stdin);
        getline(cin, nombre);
        noEsNombreValido = !esNombreProductoValido(nombre);
    }while(noEsNombreValido);
    return nombre;
}

/*
 * Funcionamiento: Valida el nombre ingresado
 * Entradas: nombre a validar
 * Salidas: true/false si es valido
 */
bool Interfaz::esNombreValido(string nombre){
    Validacion validador;
    if(validador.esNumerico(nombre)){
        return false;
    }else if(validador.esUnCaracter(nombre)){
        return false;
    }else if(validador.tieneNumeros(nombre)){
        return false;
    }else if(validador.tieneCaracteresEspeciales(nombre)){
        return false;
    }else if(nombre.find(" ") < 3 || nombre.find(" ") > nombre.length()){
        return false;
    }else{
        return true;
    }
}

/*
 * Funcionamiento: Valida el nombre del producto
 * Entradas: nombre a validar
 * Salidas: true/false si cumple las condiciones
 */
bool Interfaz::esNombreProductoValido(string nombre){
    Validacion validador;
    if(validador.esNumerico(nombre)){
        return false;
    }else if(validador.esUnCaracter(nombre)){
        return false;
    }else if(validador.tieneNumeros(nombre)){
        return false;
    }else if(validador.tieneCaracteresEspeciales(nombre)){
        return false;
    }else{
        return true;
    }
}

/*
 * Funcionamiento: Pide al usuario su número de telefono
 * Salidas: número ingresado
 */
string Interfaz::pedirTelefono(){
    string telefono;
    bool noEsTelefonoValido = false;
    do{
        if(noEsTelefonoValido){
            cout << "Debe ingresar un numero de telefono valido" << endl;
        }
        cout << "Ingrese su numero de telefono: ";
        cin >> telefono;
        noEsTelefonoValido = !esTelefonoValido(telefono);
    }while(noEsTelefonoValido);
    return telefono;
}

/*
 * Funcionamiento: Valida el telefono
 * Entradas: número de telefono
 * Salidas: true/false si es valido
 */
bool Interfaz::esTelefonoValido(string telefono){
    Validacion validador;
    if(!validador.esNumerico(telefono)){
        return false;
    }else{
        return true;
    }
}

/*
 * Funcionamiento: Muestra el mensaje de éxito del registro
 */
void Interfaz::mostrarMensajeRegistro(){
    cout << "Su solicitud ha sido enviada! Debe esperar a que esta sea aceptada." << endl;
    limpiarPantalla();
}

/*
 * Funcionamiento: Muestra el mensaje error de loggeo
 */
void Interfaz::imprimirUsuarioNoEncontrado(){
    cout << "El usuario no ha sido encontrado." << endl;
}

void Interfaz::imprimirSubMenuComprar(){
    limpiarPantalla();
    cout << "1) Agregar al carrito" << endl;
    cout << "2) Sacar del carrito" << endl;
    cout << "0) salir" << endl;
}

string Interfaz::pedirCodProducto(){
    string codProducto;
    bool noEsCodValido = false;
    do{
        if(noEsCodValido){
            cout << "Debe ingresar un codigo valido" << endl;
        }
        cout << "Ingrese el codigo del producto: ";
        cin >> codProducto;
        noEsCodValido = !esCodValido(codProducto);
    }while(noEsCodValido);
    return codProducto;
}

bool Interfaz::esCodValido(string codigo){
    Validacion validador;
    if(!validador.esNumerico(codigo)){
        return false;
    }else if(codigo.length() != 2){
        return false;
    }
    return true;
}

string Interfaz::pedirCantidad(){
    string cantidad;
    bool noEsCantidadValido = false;
    do{
        if(noEsCantidadValido){
            cout << "Debe ingresar un numero positivo" << endl;
        }
        cout << "Ingrese la cantidad del producto: ";
        cin >> cantidad;
        noEsCantidadValido = !esCantidadValida(cantidad);
    }while(noEsCantidadValido);
    return cantidad;
}

bool Interfaz::esCantidadValida(string cantidad){
    Validacion validador;
    if(!validador.esNumerico(cantidad)){
        return false;
    }else{
        return true;
    }
}

bool Interfaz::preguntarTodos(bool agregar){
    Validacion validar;
    string respuesta;
    bool noEsRespuestaValida = false;
    do{
        if(noEsRespuestaValida){
            cout << "Solo puede ingresar Y o N." << endl;
        }
        if(agregar){
            cout << "Desea agregarlos todos? (Y/N): ";
        }else{
            cout << "Desea quitarlos todos? (Y/N): ";
        }
        cin >> respuesta;
        noEsRespuestaValida = !validar.esYoN(respuesta);
    }while(noEsRespuestaValida);
    return validar.pasarDeRespuestaABool(respuesta);
}

void Interfaz::imprimirDescuento(Usuario* user){
    cout << "Su descuento es del " << user->getDescuento() << "%." << endl;
}

bool Interfaz::preguntarRegistrar(){
    Validacion validar;
    string respuesta;
    bool noEsRespuestaValida = false;
    do{
        if(noEsRespuestaValida){
            cout << "Solo puede ingresar Y o N." << endl;
        }
        cout << "Desea registrar al cliente? (Y/N): ";
        cin >> respuesta;
        noEsRespuestaValida = !validar.esYoN(respuesta);
    }while(noEsRespuestaValida);
    return validar.pasarDeRespuestaABool(respuesta);
}

void Interfaz::imprimirSubMenuRegistrar(){
    limpiarPantalla();
    cout << "1) Procesar solicitudes" << endl;
    cout << "2) Agregar usuario" << endl;
    cout << "0) salir" << endl;
}

void Interfaz::imprimirSubMenuReportes(){
    limpiarPantalla();
    cout << "1) Ultimos dos productos ingresados al inventario." << endl;
    cout << "2) Ultimo producto modificado." << endl;
    cout << "3) Ultimo producto eliminado." << endl;
    cout << "4) Producto mas vendido." << endl;
    cout << "5) Producto menos vendido por super." << endl;
    cout << "6) Cliente que mas compro." << endl;
    cout << "7) Cliente que menos compro." << endl;
    cout << "8) Cantidad de compras por cliente." << endl;
    cout << "9) Super mas visitado." << endl;
    cout << "10) Super menos visitado." << endl;
    cout << "11) Administrador que mas trabajo." << endl;
    cout << "12) Administrador que no trabajo." << endl;
    cout << "0) Salir." << endl;
}

string Interfaz::pedirCodSuper(){
    string codSuper;
    bool noEsCodValido = false;
    do{
        if(noEsCodValido){
            cout << "Debe ingresar un codigo valido" << endl;
        }
        cout << "Ingrese el codigo del super: ";
        cin >> codSuper;
        noEsCodValido = !esCodValido(codSuper);
    }while(noEsCodValido);
    return codSuper;
}

string Interfaz::pedirPrecio(){
    string precio;
    bool noEsPrecioValido = false;
    do{
        if(noEsPrecioValido){
            cout << "Debe ingresar un numero positivo" << endl;
        }
        cout << "Ingrese el precio del producto: ";
        cin >> precio;
        noEsPrecioValido = !esCantidadValida(precio);
    }while(noEsPrecioValido);
    return precio;
}

void Interfaz::imprimirSubMenuModificar(){
    limpiarPantalla();
    cout << "1) Codigo del super" << endl;
    cout << "2) Nombre" << endl;
    cout << "3) Cantidad" << endl;
    cout << "4) Precio" << endl;
    cout << "0) Salir" << endl;
}

void Interfaz::pause(){
    #ifdef __linux__
        cin.ignore();
        cin.get();
    #else
        system("pause");
    #endif // __linux__
}
