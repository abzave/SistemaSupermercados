#ifndef PROYECTO_INCLUDE_VALIDACION_H
#define PROYECTO_INCLUDE_VALIDACION_H
#define OPCION_NO_VALIDA    -2
#define CLIENTE_NO_VALIDO   -1
#define NO_REQUIRE_INFO      0
#define REQUIRE_LLAVE        1
#define REQUIRE_TODA_LA_INFO 3

#include <string>

#include "Usuario.h"

class Validacion{
    public:
        bool esNumerico(string);
        bool esUnCaracter(string);
        bool estaDentroDelRangoDeTipo(string);
        bool esYoN(string);
        bool pasarDeRespuestaABool(string);
        bool existeCiudad(string);
        bool tieneNumeros(string);
        bool tieneCaracteresEspeciales(string);
        int RequerimientosOpcion(string, string);
};

#endif // PROYECTO_INCLUDE_VALIDACION_H
