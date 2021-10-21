#ifndef VACIO_H_INCLUDED
#define VACIO_H_INCLUDED

#include "casillero.h"

class Vacio: public Casillero
{
public:
    /*
    PRE: -
    POS: crea un casillero de tipo vacio.
   */
    Vacio(); // constructor

    /*
     PRE: elemento_pj es un string valido - agua, aire, fuego, tierra.
     POS: devuelve el costo base del casillero de tipo vacio.
    */
    int calcular_costo(string elemento_pj);

    /*
     PRE: -
     POS: devuelve el costo base del casillero de tipo vacio.
    */
    int obtener_costo_base();

    /*
     PRE: -
     POS: devuelve "vacio", el tipo de casillero.
    */
    string tipo_casillero();

};

#endif // VACIO_H_INCLUDED
