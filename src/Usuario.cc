#include "Usuario.h"

BaseDeDatos Usuario::base;

Usuario::Usuario(string cedula, string tipo){
    this->cedula = cedula;
    this->tipo = tipo;
    nombre = obtenerNombre();
    /*telefono = obtenerTelefono();*/
}

Usuario::~Usuario(){
    while(!carrito.ListaVacia()){
        string llave = carrito.getLlave(0);
        quitarDelCarrito(llave, QUITAR_TODO);
    }
}

bool Usuario::estaRegistrado(){
    return !base.esCedulaValida(cedula, tipo);
}

string Usuario::obtenerCedulaArchivo(string datosDeUsuario){
    int posicionDelPrimerSeparador = datosDeUsuario.find(";");
    int posicionDelSegundoSeparador = datosDeUsuario.find(";", posicionDelPrimerSeparador + 1);
    string cedulaArchivo = datosDeUsuario.substr(posicionDelPrimerSeparador + 1, posicionDelSegundoSeparador - 3);
    return cedulaArchivo;
}

string Usuario::obtenerTipoArchivo(string datosUsuario){
    int ultimaPosicion = obtenerUltimaPosicion(datosUsuario);
    string tipoArchivo(1, datosUsuario[ultimaPosicion]);
    return tipoArchivo;
}

int Usuario::obtenerUltimaPosicion(string cadena){
    return cadena.length() - 1;
}

string Usuario::getTipo(){
    return tipo;
}

bool Usuario::esCliente(){
    return tipo == CLIENTE;
}

bool Usuario::puedeRegistrarse(){
    return !estaRegistrado() && esCliente();
}

void Usuario::registrar(string ciudad, string nombre, string telefono){
    base.agregarSolicitud(ciudad, cedula, nombre, telefono);
}

void Usuario::agregarACarrito(string codProducto, string codSuper, int cantidad){
    if(base.existeProductoEnSuper(codProducto, codSuper)){
        codSuperCarrito = codSuper;
        int cantidadExistente = base.getCantidadProducto(codProducto);
        if (cantidadExistente == 0){
            throw logic_error("Ya no quedan existencias de este producto.");
        }
        if(cantidadExistente >= cantidad){
            base.quitarCantidadProducto(codProducto, cantidad);
            if(!carrito.existeLlave(codProducto)){
                if(cantidad == COMPRAR_TODO){
                    cantidad = cantidadExistente;
                }
                carrito.InsertarInicio(to_string(cantidad), codProducto);
            }else{
                cantidad += atoi(carrito.getValor(codProducto).c_str());
                carrito.actualizarLista(codProducto, to_string(cantidad));
            }
        }else{
            throw range_error("Solo hay " + to_string(cantidadExistente) + " productos en existencia.");
        }
    }else{
        throw invalid_argument("El producto no existe en este super.");
    }
}

bool Usuario::existeSuper(string codSuper){
    if(!base.existeCodSuper(codSuper)){
        return false;
    }else{
        return true;
    }
}

string Usuario::getCodSuperCarrito(){
    return codSuperCarrito;
}

bool Usuario::carritoVacio(){
    return carrito.ListaVacia();
}

void Usuario::quitarDelCarrito(string codProducto, int cantidad){
    if(carrito.ListaVacia()){
        throw logic_error("El carrito esta vacio!");
    }
    if(base.existeCodProducto(codProducto) && carrito.existeLlave(codProducto)){
        int cantidadGuardada = atoi(carrito.getValor(codProducto).c_str());
        if(cantidad == QUITAR_TODO){
            base.agregarCantidadProducto(codProducto, cantidadGuardada);
            carrito.borrarPorLlave(codProducto);
        }else if(cantidadGuardada >= cantidad){
            base.agregarCantidadProducto(codProducto, cantidad);
            cantidadGuardada -= cantidad;
            if(cantidadGuardada != 0){
                carrito.actualizarLista(codProducto, to_string(cantidadGuardada));
            }else{
                carrito.borrarPorLlave(codProducto);
            }
        }else{
            throw range_error("Solo tiene " + to_string(cantidadGuardada) + " productos en el carrito.");
        }
    }else{
        throw invalid_argument("El producto no existe");
    }
}

void Usuario::mostrarCarrito(){
    carrito.Mostrar();
}

int Usuario::getDescuento(){
    if(tipo == CLIENTE){
        return 5;
    }else if(tipo == CLIENTE_FUNCIONARIO){
        return 10;
    }else{
        return 0;
    }
}

int Usuario::getDescuento(string cedula){
    if(!base.esCedulaValida(cedula, "0")){
        return 5;
    }else if(!base.esCedulaValida(cedula, "3")){
        return 10;
    }else{
        return 0;
    }
}

string Usuario::getDescuentos(){
    return "Los descuentos son de: 10% para clientes-funcionarios y 5% para clientes";
}

string Usuario::getCedula(){
    return cedula;
}

string Usuario::obtenerNombre(){
    return base.getNombreUsuario(cedula, tipo);
}

string Usuario::getNombre(){
    return nombre;
}

string Usuario::getTelefono(){
    return telefono;
}

string Usuario::obtenerTelefono(){
    return base.getTelefonoUsuario(cedula, tipo);
}

bool Usuario::facturar(){
    if(carrito.ListaVacia()){
        return false;
    }
    userData user;
    user.cedula = this->cedula;
    user.descuento = getDescuento();
    user.nombre = getNombre();
    user.telefono = getTelefono();
    Factura factura(user);
    ListaDobleCircular mismoSuper;
    int largo = carrito.largoLista() - 1;
    string cantidad[carrito.largoLista()];
    int cantidadFinal = 0;
    while(!carrito.ListaVacia()){
        int pos = 0;
        string codSuper = base.getInfoProducto(carrito.getLlave(largo));
        codSuper = obtenerCodSuper(codSuper);
        for(int i = largo; i >= 0; i--){
            string codProducto = carrito.getLlave(i);
            string info = base.getInfoProducto(codProducto);
            if(codSuper == obtenerCodSuper(info)){
                string cantidadProducto = carrito.getValor(codProducto);
                cantidadFinal += atoi(cantidadProducto.c_str());
                mismoSuper.InsertarInicio(info, cantidadProducto);
                base.agregarProductoVendido(codProducto, cantidadProducto + ";" + codSuper);
                cantidad[pos] = cantidadProducto;
                pos++;
                carrito.borrarPos(i);
            }
        }
        base.agregarVisitaSuper(codSuper);
        largo = carrito.largoLista() - 1;
        factura.generar(mismoSuper, cantidad);
        mismoSuper.~ListaDobleCircular();
    }
    base.registrarCompra(cedula, cantidadFinal);
    return true;
}

string Usuario::obtenerCodSuper(string datos){
    int primerSeparador = datos.find(";");
    string codSuper = datos.substr(0, primerSeparador);
    return codSuper;
}

bool Usuario::haySolicitudes(){
    return !base.listaSolicitudVacia();
}

void Usuario::mostrarSolicitud(){
    cout << "Cedula\tCiudad\tNombre\t\tTel.\tTipo" << endl;
    string datos = base.getSolicitud();
    replace(datos.begin(), datos.end(), ';', '\t');
    cout << datos << endl;
}

void Usuario::procesarSolicitud(bool aceptada){
    if(aceptada){
        base.aceptarSolicitud();
    }
    base.borrarSolicitud();
}

void Usuario::registroDirecto(string cedula, string nombre, string telefono, string ciudad, string tipo){
    base.agregarUsuario(ciudad, cedula, nombre, telefono, tipo);
}

string Usuario::ultimosDosProductos(){
    int ultimoProducto = base.getCantidadProductosInventario() - 1;
    string productos;
    if(ultimoProducto == -1){
        return "No hay productos todavia";
    }else if(ultimoProducto == 0){
        productos = base.getProducto(ultimoProducto);
    }else{
        productos = base.getProducto(ultimoProducto);
        productos += "\n";
        productos += base.getProducto(ultimoProducto - 1);
    }
    return productos;
}

string Usuario::productoMasVendido(){
    return "El producto mas vendido es: " + base.getProductoMasVendido();
}

string Usuario::productoMenosVendido(){
    string producto = base.getMenosVendidos();
    if(producto == ""){
        return "No se han vendido productos todavia\n";
    }else{
        return producto;
    }
}

string Usuario::mayorComprador(){
    return "Cliente que mas compro: " + base.getMayorComprador();
}

string Usuario::menorComprador(){
    return "Cliente que menos compro: " + base.getMenorComprador();
}

string Usuario::comprasPorUsuario(){
    return base.cantidadDeCompras();
}

string Usuario::mejorSuper(){
    return base.getSuperMasVisitado();
}

string Usuario::peorSuper(){
    return base.getSuperMenosVisitado();
}

void Usuario::agregarAccionAdmin(){
    base.agregarActividadAdmin(cedula);
}

string Usuario::mejorAdmin(){
    return base.getMejorAdmin();
}

string Usuario::peorAdmin(){
    return base.getPeorAdmin();
}

string Usuario::hacerConsultaPrecio(string codProducto){
    if(!base.existeCodProducto(codProducto)){
        return "El producto no existe.";
    }
    string datos = base.getInfoProducto(codProducto);
    int primerSeparador = datos.find(";");
    int segundoSeparador = datos.find(";", primerSeparador + 1);
    int tercerSeparador = datos.find(";", segundoSeparador + 1);
    string nombre = datos.substr(primerSeparador + 1, segundoSeparador - 3);
    string precio = datos.substr(tercerSeparador + 1, datos.length() - 1);
    return "Producto: " + nombre + "\nPrecio: " + precio + "\n";
}

string Usuario::getProductos(string codSuper){
    return base.getProductosSuper(codSuper);
}

string Usuario::eliminarProducto(string codProducto){
    bool eliminado = base.eliminarDeInventario(codProducto);
    if(eliminado){
        return "Producto elimando con exito!";
    }else{
        return "El producto no existe.";
    }
}

string Usuario::insertarProducto(string codProducto, string codSuper, string nombre, string precio, string cantidad){
    if(base.existeCodSuper(codSuper)){
        if(!base.existeCodProducto(codProducto)){
            string datos = codSuper + ";" + nombre + ";" + cantidad + ";" + precio;
            base.agregarProducto(codProducto, datos);
            return "Producto agregado con exito!\n";
        }else{
            return "El codigo del producto ya existe.\n";
        }
    }else{
        return "El super ingresado no existe.\n";
    }
}

string Usuario::cambiarCodSuper(string codProducto, string codSuper){
    if(base.existeCodSuper(codSuper)){
        if(base.existeCodProducto(codProducto)){
            base.actualizarCodSuper(codProducto, codSuper);
            return "Codigo actualizado!\n";
        }else{
            return "Producto no existe.\n";
        }
    }else{
        return "El super no existe.\n";
    }
}

string Usuario::cambiarNombreProducto(string codProducto, string nombre){
    if(base.existeCodProducto(codProducto)){
        base.actualizarNombreProducto(codProducto, nombre);
        return "Codigo actualizado!\n";
    }else{
        return "Producto no existe.\n";
    }
}

string Usuario::cambiarCantidadProducto(string codProducto, string cantidad){
    if(base.existeCodProducto(codProducto)){
        base.actualizarCantidadProducto(codProducto, cantidad);
        return "Cantidad actualizada!";
    }else{
        return "El producto no existe.";
    }
}

string Usuario::cambiarPrecioProducto(string codProducto, string precio){
    if(base.existeCodProducto(codProducto)){
        base.actualizarPrecioProducto(codProducto, precio);
        return "Precio actualizado!";
    }else{
        return "El producto no existe.";
    }
}

string Usuario::ultimaEliminacion(){
    return base.getUltimoEliminado();
}

string Usuario::ultimoCambio(){
    return base.getUltimoModificado();
}
