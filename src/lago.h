#ifndef LAGO_H_INCLUDED
#define LAGO_H_INCLUDED

#include "casillero.h"

class Lago: public Casillero
{
public:
    /*
     PRE: -
     POS: crea un casillero de tipo lago.
    */
    Lago();// constructor

    /*
     PRE: elemento_pj es un string valido - agua, aire, fuego, tierra.
     POS: devuelve el costo base del casillero de tipo lago.
    */
    int calcular_costo(string elemento_pj);

    /*
    PRE: -
    POS: devuelve el costo base del casillero de tipo lago.
   */
    int obtener_costo_base();

    /*
     PRE: -
     POS: devuelve "lago", el tipo de casillero.
    */
    string tipo_casillero();

};

#endif // LAGO_H_INCLUDED
