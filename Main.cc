/*
 * Creado por: Abraham Meza Vega
 * Última modificación: 19/09/18
 * Versión: C++11
 */

#include "Interfaz.h"

Usuario logIn();
string menuPrincipal(string);
void hacerRegistro(Usuario*);
void opcionSinRequerimientos(string, Usuario*);
void verificarOpcionCliente(string, Usuario*);
void opcionComprar(Usuario*);
void verificarOpcionComprar(string, Usuario*);
void agregarAlCarrito(string, string, int, Usuario*);
void opcionRegistrarCliente(Usuario*);
void procesarOpcionReportes(Usuario*, string);
void opcionUnaLlave(string, Usuario*);
void opcionTodaInfo(string, Usuario*);
void verificarOpcionModificar(string, Usuario*);

int main(){
    Usuario user = logIn();
    Interfaz consola;
    Validacion validador;
    string tipoUsuario = user.getTipo();
    string opcion;
    if(user.estaRegistrado()){
        if(tipoUsuario == ADMINISTRADOR){
            user.agregarAccionAdmin();
        }
    }else if (user.puedeRegistrarse()){
        tipoUsuario = CLIENTE_SIN_REGISTRAR;
        bool regstrarse = consola.preguntarRegistro();
        if(regstrarse){
            hacerRegistro(&user);
        }
    }else{
        consola.limpiarPantalla();
        consola.imprimirUsuarioNoEncontrado();
        main();
    }
    while(true){
        opcion = menuPrincipal(tipoUsuario);
        if (opcion == "0"){
                user.~Usuario();
                break;
        }
        int requerimietos = validador.RequerimientosOpcion(opcion, tipoUsuario);
        if(requerimietos == NO_REQUIRE_INFO){
            consola.limpiarPantalla();
            opcionSinRequerimientos(opcion, &user);
        }else if(requerimietos == REQUIRE_LLAVE){
            consola.limpiarPantalla();
            opcionUnaLlave(opcion, &user);
        }else if(requerimietos == REQUIRE_TODA_LA_INFO){
            consola.limpiarPantalla();
            opcionTodaInfo(opcion, &user);
        }else{
            cout << "La opcion ingresada no es valida" << endl;
        }
    }
    consola.limpiarPantalla();
    main();
    return 0;
}

/*
 * Funcionamiento: Despliega la pantalla de log in.
 * Salida: Devuelve una instancia de un usuario con la información recaudada
 */
Usuario logIn(){
    Interfaz consola;
    string cedula = consola.pedirCedula();
    string tipoUsuario = consola.pedirTipoUsuario();
    cout << endl;
    Usuario usuario(cedula, tipoUsuario);
    return usuario;
}

/*
 * Funcionamiento: Despliega en pantalla el menú principal.
 * Entradas: Un string que contiene la numeración correspondiente al tipo de usuario
 * Salidas: Retorna la opcion ingresada por el usuario
 */
string menuPrincipal(string tipoUsuario){
    Interfaz consola;
    consola.imprimirMenu(tipoUsuario);
    string opcion = consola.pedirOpcion(tipoUsuario);
    return opcion;
}

/*
 * Funcionamiento: Pide al usuario sus datos para realizar un registro.
 * Entradas: Recibe un puntero al usuario.
 */
void hacerRegistro(Usuario* user){
    Interfaz consola;
    consola.limpiarPantalla();
    string ciudad = consola.pedirCiudad();
    string nombre = consola.pedirNombre();
    string telefono = consola.pedirTelefono();
    user->registrar(ciudad, nombre, telefono);
    consola.mostrarMensajeRegistro();
}

/*
 * Funcionamiento: Ya que la opción no requiere que se dote de más información (
 * al menos en una primera instancia) se procesa la opción ingresada y se imprimen sus resultados
 * Entradas: Recibe la opción a procesar y un puntero al usuario.
 */
void opcionSinRequerimientos(string opcion, Usuario* user){
    string tipoUsuario = user->getTipo();
    Interfaz consola;
    if(tipoUsuario == CLIENTE || tipoUsuario == CLIENTE_FUNCIONARIO){
        verificarOpcionCliente(opcion, user);
    }else if(tipoUsuario == ADMINISTRADOR){
        switch(opcion[0]){
            case '5':
                cout << user->getDescuentos() << endl;
                consola.pause();
                break;
            case '7':{
                opcionRegistrarCliente(user);
                break;
            }
            case '8':
                while(true){
                    consola.imprimirSubMenuReportes();
                    string opcionReportes = consola.pedirOpcion(REPORTES);
                    if(opcionReportes == "0"){
                        break;
                    }
                    procesarOpcionReportes(user, opcionReportes);
                }
                break;
        }
    }
}

/*
 * Funcionamiento: Procesa la opción ingresada en el contexto de un cliente (usuario tipo 0 o 3).
 * Entradas: Se le debe de proveer de la opcion a procesar y de un puntero al usuario.
 */
void verificarOpcionCliente(string opcion, Usuario* user){
    Interfaz consola;
    switch(opcion[0]){
            case '2':
                consola.imprimirDescuento(user);
                consola.pause();
                break;
            case '4':
                opcionComprar(user);
                break;
            case '5':
                bool pudoFacturar = user->facturar();
                if(pudoFacturar){
                    cout << "Factura creada!" << endl;
                }else{
                    cout << "No hay articulos en el carrito" << endl;
                }
                consola.pause();
                break;
        }
}

/*
 * Funcionamiento: Imprime en pantalla el submenú correspondiente a la opción de comprar.
 * Entradas: Un puntero al usuario
 */
void opcionComprar(Usuario* user){
    Interfaz consola;
    while(true){
        consola.imprimirSubMenuComprar();
        cout << endl;
        cout << "Carrito: ";
        user->mostrarCarrito();
        cout << endl << endl;
        string opcion = consola.pedirOpcion(CLIENTE_SIN_REGISTRAR);
        if(opcion == "0"){
            break;
        }
        verificarOpcionComprar(opcion, user);
    }
}

/*
 * Funcionamiento: Procesa la opción ingresada en el submenú de comprar.
 * Entradas: Opción a procesar y un puntero al usuario.
 */
void verificarOpcionComprar(string opcion, Usuario* user){
    Interfaz consola;
    consola.limpiarPantalla();
    if(opcion == "1"){
        string codSuper;
        if(user->carritoVacio()){
            codSuper = consola.pedirCodSuper();
            if(!user->existeSuper(codSuper)){
                cout << "El super no existe." << endl;
                consola.pause();
                consola.limpiarPantalla();
            }
        }else{
            codSuper = user->getCodSuperCarrito();
        }
        string codProducto = consola.pedirCodProducto();
        int cantidad = atoi(consola.pedirCantidad().c_str());
        if(cantidad != 0){
            agregarAlCarrito(codProducto, codSuper, cantidad, user);
        }
    }else if(opcion == "2"){
        string codProducto = consola.pedirCodProducto();
        int cantidad = atoi(consola.pedirCantidad().c_str());
        try{
            user->quitarDelCarrito(codProducto, cantidad);
        }catch(invalid_argument& e){
            cout << e.what() << endl;
            consola.pause();
            verificarOpcionComprar(opcion, user);
        }catch(range_error& e2){
            cout << e2.what() << endl;
            bool quitarTodos = consola.preguntarTodos(false);
            if(quitarTodos){
                user->quitarDelCarrito(codProducto, QUITAR_TODO);
            }
        }catch(logic_error& e3){
            cout << e3.what() << endl;
            consola.pause();
        }
    }
}

/*
 * Funcionamiento: Agrega productos al carrito.
 * Entradas: el código del producto a ingresar, el código del super en el que se comprará, la cantidad a ingresar y un puntero al usuario.
 */
void agregarAlCarrito(string codProducto, string codSuper, int cantidad, Usuario* user){
    Interfaz consola;
    try{
        user->agregarACarrito(codProducto, codSuper, cantidad);
    }catch(invalid_argument& e){
        cout << e.what() << endl;
        consola.pause();
        verificarOpcionComprar("1", user);
    }catch(range_error& e2){
        cout << e2.what() << endl;
        bool comprarTodos = consola.preguntarTodos(true);
        if(comprarTodos){
            user->agregarACarrito(codProducto, codSuper, COMPRAR_TODO);
        }
    }catch(logic_error& e3){
        cout << e3.what() << endl;
        consola.pause();
    }
}

/*
 * Funcionamiento: Imprime el submenú de la opción de registrar clientes.
 * Entradas: Un puntero al usuario.
 */
void opcionRegistrarCliente(Usuario* user){
    Interfaz consola;
    while(true){
        consola.imprimirSubMenuRegistrar();
        string opcionReg = consola.pedirOpcion(CLIENTE_SIN_REGISTRAR);
        if(opcionReg == "0"){break;}
        switch(opcionReg[0]){
            case '1':
                consola.limpiarPantalla();
                while(user->haySolicitudes()){
                    user->mostrarSolicitud();
                    bool registrar = consola.preguntarRegistrar();
                    user->procesarSolicitud(registrar);
                }
                cout << "No hay solicitudes" << endl;
                consola.pause();
                break;
            case '2':
                consola.limpiarPantalla();
                string ciudad = consola.pedirCiudad();
                string nombre = consola.pedirNombre();
                string telefono = consola.pedirTelefono();
                string tipo = consola.pedirTipoUsuario();
                string cedula = consola.pedirCedula();
                user->registroDirecto(cedula, nombre, telefono, ciudad, tipo);
                break;
        }
    }
}

/*
 * Funcionamiento: Procesa la opción dada en el submenú de repotes.
 * Entradas: Un puntero al usuario y la opción ingresada.
 */
void procesarOpcionReportes(Usuario* user, string opcion){
    Interfaz consola;
    consola.limpiarPantalla();
    if (opcion == "10"){
        cout << user->peorSuper() << endl;
        consola.pause();
    }else if(opcion == "11"){
        cout << user->mejorAdmin() << endl;
        consola.pause();
    }else if(opcion == "12"){
        cout << user->peorAdmin();
        consola.pause();
    }else{
        switch(opcion[0]){
            case '1':
                cout << user->ultimosDosProductos() << endl;
                consola.pause();
                break;
            case '2':
                cout << user->ultimoCambio() << endl;
                consola.pause();
                break;
            case '3':
                cout << user->ultimaEliminacion() << endl;
                consola.pause();
                break;
            case '4':
                cout << user->productoMasVendido() << endl;
                consola.pause();
                break;
            case '5':
                cout << user->productoMenosVendido() << endl;
                consola.pause();
                break;
            case '6':
                cout << user->mayorComprador() << endl;
                consola.pause();
                break;
            case '7':
                cout << user->menorComprador() << endl;
                consola.pause();
                break;
            case '8':
                cout << user->comprasPorUsuario() << endl;
                consola.pause();
                break;
            case '9':
                cout << user->mejorSuper() << endl;
                consola.pause();
                break;
        }
    }
}

/*
 * Funcionamiento: Procesa las opciones que requiere el ingreso de una llave para continuar.
 * Entradas: La opción a ser procesada y un puntero al usuario.
 */
void opcionUnaLlave(string opcion, Usuario* user){
    Interfaz consola;
    string tipoUsuario = user->getTipo();
    if(tipoUsuario == CLIENTE || tipoUsuario == CLIENTE_FUNCIONARIO){
        switch(opcion[0]){
            case '1':{
                string codProducto = consola.pedirCodProducto();
                cout << user->hacerConsultaPrecio(codProducto) << endl;
                consola.pause();
                break;
            }
            case '3':
                string codSuper = consola.pedirCodSuper();
                cout << user->getProductos(codSuper) << endl;
                consola.pause();
                break;
        }
    }else if(tipoUsuario == ADMINISTRADOR){
         switch(opcion[0]){
            case '2':{
                string codProducto = consola.pedirCodProducto();
                cout << user->eliminarProducto(codProducto) << endl;
                consola.pause();
                break;
            }
            case '4':{
                string codProducto = consola.pedirCodProducto();
                cout << user->hacerConsultaPrecio(codProducto) << endl;
                consola.pause();
                break;
            }
            case '6':{
                string codSuper = consola.pedirCodSuper();
                cout << user->getProductos(codSuper) << endl;
                consola.pause();
                break;
            }
        }
    }else if(tipoUsuario == VENDEDOR){
        switch(opcion[0]){
            case '1':{
                string codProducto = consola.pedirCodProducto();
                cout << user->hacerConsultaPrecio(codProducto) << endl;
                cin.ignore().get();
                consola.pause();
                break;
            }
            case '2':{
                string cedula = consola.pedirCedula();
                int descuento = user->getDescuento(cedula);
                if(descuento){
                    cout << "El descuento de este cliente es de: " + to_string(descuento)+ "%" << endl;
                }else{
                    cout << "El usuario no está registrado." << endl;
                }
                consola.pause();
                break;
            }
            case '3':{
                string codSuper = consola.pedirCodSuper();
                cout << user->getProductos(codSuper) << endl;
                consola.pause();
                break;
            }
        }
    }
}

/*
 * Funcionamiento: Procesa las opciones que requieren que se brinde toda la información para un registro.
 * Entradas: opcion ingresada y un puntero al usuario.
 */
void opcionTodaInfo(string opcion, Usuario* user){
    Interfaz consola;
    string tipoUsuario = user->getTipo();
    switch(opcion[0]){
        case '1':{
            string codProducto = consola.pedirCodProducto();
            string codSuper = consola.pedirCodSuper();
            string nombre = consola.pedirNombreProducto();
            string cantidad = consola.pedirCantidad();
            string precio = consola.pedirPrecio();
            cout << user->insertarProducto(codProducto, codSuper, nombre, precio, cantidad) << endl;
            consola.pause();
            break;
        }
        case '3':
            while(true){
                consola.imprimirSubMenuModificar();
                string opcion = consola.pedirOpcion("6");
                if(opcion == "0"){
                    break;
                }
                verificarOpcionModificar(opcion, user);
                consola.pause();
            }
    }
}

/*
 * Funcionamiento: Procesa la opción ingresada en el submenú de reportes
 * Entradas: opción a procesar y un puntero al usuario.
 */
void verificarOpcionModificar(string opcion, Usuario* user){
    Interfaz consola;
    consola.limpiarPantalla();
    string codProducto = consola.pedirCodProducto();
    switch(opcion[0]){
        case '1':{
            string codSuper = consola.pedirCodSuper();
            cout << user->cambiarCodSuper(codProducto, codSuper) << endl;
            break;
        }
        case '2':{
            string nombre = consola.pedirNombreProducto();
            cout << user->cambiarNombreProducto(codProducto, nombre) << endl;
            break;
        }
        case '3':{
            string cantidad = consola.pedirCantidad();
            cout << user->cambiarCantidadProducto(codProducto, cantidad) << endl;
            break;
        }
        case '4':
            string precio = consola.pedirPrecio();
            cout << user->cambiarPrecioProducto(codProducto, precio) << endl;
            break;
    }
}
