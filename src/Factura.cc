#include "Factura.h"

int Factura::cantidadFacturas = 0;

Factura::Factura(userData user){
    this->user = user;
}

/*
 * Funcionamiento: Crea el archivo de la factura
 * Entradas: La información de la compra en una lista doble circular y una array con las cantidades compradas
 */
void Factura::generar(ListaDobleCircular infoProducto, string cantidad[]){
    cantidadFacturas++;
    ofstream archivo("Factura" + to_string(cantidadFacturas) + ".txt");
    archivo << generarTexto(infoProducto, cantidad);
    archivo.close();
}

/*
 * Funcionamiento: Crea el texto de la factura
 * Entradas: La información de la compra en una lista doble circular y una array con las cantidades compradas
 * Salidas: Texto a ingresar en la factura
 */
string Factura::generarTexto(ListaDobleCircular infoProducto, string cantidad[]){
    string datos = infoProducto.getValor(cantidad[0]);
    string codSuper = obtenerCodSuper(datos);
    int descuento = user.descuento;
    int totalAPagar = 0;
    string texto = "Factura consecutiva: ";
    texto += to_string(cantidadFacturas);
    texto += "\n\n";
    texto += "Cedula: " + user.cedula + "\n";
    texto += "Nombre: " + user.nombre + "\n";
    texto += "Telefono: " + user.telefono + "\n";
    texto += "Codigo super: " + codSuper;
    texto += "\n\n";
    texto += "Producto\tCantidad\tPrecio\tTotal\n";
    int pos = infoProducto.largoLista() - 1;
    while(!infoProducto.ListaVacia()){
        datos = infoProducto.getValor(cantidad[pos]);
        string producto = obtenerProducto(datos);
        string precio = obtenerPrecio(datos);
        string total = calcularTotal(obtenerPrecio(datos), cantidad[pos]);
        totalAPagar += atoi(total.c_str());
        texto += producto + "\t\t" + cantidad[pos] + "\t\t" + precio + "\t" + total + "\n";
        infoProducto.BorrarInicio();
        pos--;
    }
    texto += "\n";
    texto += "\t\t\t\t\tTotal: " + to_string(totalAPagar) + "\n";
    texto += "\t\t\t\t\tDescuento: " + to_string(descuento) + "%\n";
    texto += "\t\t\t\t\tMonto Final: " + to_string(totalAPagar - (totalAPagar * descuento / 100)) + "\n";
    return texto;
}

/*
 * Funcionamiento: Extrae de los datos el código del super
 * Entradas: datos a analizar
 * Salidas: código del super
 */
string Factura::obtenerCodSuper(string datos){
    int primerSeparador = datos.find(";");
    string codSuper = datos.substr(0, primerSeparador);
    return codSuper;
}

/*
 * Funcionamiento: Extrae de los datos el código del producto
 * Entradas: datos a analizar
 * Salidas: código del producto
 */
string Factura::obtenerProducto(string datos){
    int primerSeparador = datos.find(";");
    int segundoSeparador = datos.find(";", primerSeparador + 1);
    string producto = datos.substr(primerSeparador + 1, segundoSeparador - 3);
    return producto;
}

/*
 * Funcionamiento: Extrae de los datos el precio del producto
 * Entradas: datos a analizar
 * Salidas: precio del producto
 */
string Factura::obtenerPrecio(string datos){
    int primerSeparador = datos.find(";");
    int segundoSeparador = datos.find(";", primerSeparador + 1);
    int tercerSepardor = datos.find(";", segundoSeparador + 1);
    string precio = datos.substr(tercerSepardor + 1, datos.length() - 1);
    return precio;
}

/*
 * Funcionamiento: Calcula el total a pagar (sin descuento)
 * Entradas: precio del producto y una referencia a una cantidad
 * Salidas: total a pagar
 */
string Factura::calcularTotal(string precio, string& cantidad){
    int precioInt = atoi(precio.c_str());
    int cantidadInt = atoi(cantidad.c_str());
    int total = precioInt * cantidadInt;
    return to_string(total);
}
