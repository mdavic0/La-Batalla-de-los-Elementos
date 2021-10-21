#ifndef PRECIPICIO_H_INCLUDED
#define PRECIPICIO_H_INCLUDED

#include "casillero.h"

class Precipicio: public Casillero
{
public:
    /*
    PRE: -
    POS: crea un casillero de tipo precipicio.
   */
    Precipicio(); // constructor

    /*
     PRE: elemento_pj es un string valido - agua, aire, fuego, tierra.
     POS: devuelve el costo base del casillero de tipo precipicio.
    */
    int calcular_costo(string elemento_pj);

    /*
     PRE: -
     POS: devuelve el costo base del casillero de tipo precipicio.
    */
    int obtener_costo_base();

    /*
     PRE: -
     POS: devuelve "precipicio", el tipo de casillero.
    */
    string tipo_casillero();

};

#endif // PRECIPICIO_H_INCLUDED
