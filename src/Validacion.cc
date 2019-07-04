#include "Validacion.h"

bool Validacion::esNumerico(string cadena){
    for(unsigned int i = 0; i < cadena.length(); i++){
        if(!isdigit(cadena[i])){
            return false;
        }
    }
    return true;
}

bool Validacion::esUnCaracter(string cadena){
    return cadena.length() == 1;
}

bool Validacion::estaDentroDelRangoDeTipo(string tipo){
    int tipoInt = atoi(tipo.c_str());
    if(tipoInt < 0 || tipoInt > 3){
        return false;
    }else{
        return true;
    }
}

bool Validacion::esYoN(string respuesta){
    bool esY = respuesta == "Y" || respuesta == "y";
    bool esN = respuesta == "N" || respuesta == "n";
    return esY || esN;
}

bool Validacion::pasarDeRespuestaABool(string respuesta){
    switch(respuesta[0]){
        case 'Y':
        case 'y':
            return true;
        case 'N':
        case 'n':
            return false;
        default:
            throw invalid_argument("Error: La respuesta no es Y/N");
    }
}

bool Validacion::existeCiudad(string ciudad){
    BaseDeDatos base;
    if(base.obtenerCodDeCiudad(ciudad) == ""){
        return false;
    }else{
        return true;
    }
}

bool Validacion::tieneNumeros(string cadena){
    for(unsigned int i = 0; i < cadena.length(); i++){
        if(isdigit(cadena[i])){
            return true;
        }
    }
    return false;
}

bool Validacion::tieneCaracteresEspeciales(string cadena){
    for(unsigned int i = 0; i < cadena.length(); i++){
        if(cadena[i] < ' '){
            return true;
        }else if(cadena[i] > ' ' && cadena[i] < 'A'){
            return true;
        }else if(cadena[i] > 'Z' && cadena[i] < 'a'){
            return true;
        }else if(cadena[i] > 'z' && cadena[i] < 127){
            return true;
        }else if(cadena[i] != 'á' && cadena[i] != 'é' && cadena[i] != 'í' && cadena[i] != 'ó' && cadena[i] != 'ú' && cadena[i] != 'ü' && cadena[i] >= 127){
            return true;
        }
    }
    return false;
}

int Validacion::RequerimientosOpcion(string opcion, string tipoUsuario){
    if(tipoUsuario == CLIENTE || tipoUsuario == CLIENTE_FUNCIONARIO){
        switch(opcion[0]){
            case '0':
                return NO_REQUIRE_INFO;
            case '1':
                return REQUIRE_LLAVE;
            case '2':
                return NO_REQUIRE_INFO;
            case '3':
                return REQUIRE_LLAVE;
            case '4':
                return NO_REQUIRE_INFO;
            case '5':
                return NO_REQUIRE_INFO;
            default:
                return OPCION_NO_VALIDA;
        }
    }else if(tipoUsuario == ADMINISTRADOR){
        switch(opcion[0]){
            case '0':
                return NO_REQUIRE_INFO;
            case '1':
                return REQUIRE_TODA_LA_INFO;
            case '2':
                return REQUIRE_LLAVE;
            case '3':
                return REQUIRE_TODA_LA_INFO;
            case '4':
                return REQUIRE_LLAVE;
            case '5':
                return NO_REQUIRE_INFO;
            case '6':
                return REQUIRE_LLAVE;
            case '7':
                return NO_REQUIRE_INFO;
            case '8':
                return NO_REQUIRE_INFO;
            default:
                return OPCION_NO_VALIDA;
        }
    }else if(tipoUsuario == VENDEDOR){
        switch(opcion[0]){
            case '0':
                return NO_REQUIRE_INFO;
            case '1':
                return REQUIRE_LLAVE;
            case '2':
                return REQUIRE_LLAVE;
            case '3':
                return REQUIRE_LLAVE;
            default:
                return OPCION_NO_VALIDA;
        }
    }else if(tipoUsuario == CLIENTE_SIN_REGISTRAR){
        switch(opcion[0]){
            case '0':
                return NO_REQUIRE_INFO;
            case '1':
                return REQUIRE_LLAVE;
            case '2':
                return REQUIRE_LLAVE;
            default:
                return OPCION_NO_VALIDA;
        }
    }else{
        return CLIENTE_NO_VALIDO;
    }
}
