#ifndef CAMINO_H_INCLUDED
#define CAMINO_H_INCLUDED
#include "casillero.h"

class Camino: public Casillero {
public:
    /*
     PRE: -
     POS: crea un casillero de tipo camino.
    */
    Camino();

    /*
     PRE: elemento_pj es un string valido - agua, aire, fuego, tierra.
     POS: devuelve el costo base del casillero de tipo camino.
    */
    int calcular_costo(string elemento_pj);

    /*
    PRE: -
    POS: devuelve el costo base del casillero de tipo camino.
   */
    int obtener_costo_base();

    /*
     PRE: -
     POS: devuelve "camino", el tipo de casillero.
    */
    string tipo_casillero();
};


#endif // CAMINO_H_INCLUDED