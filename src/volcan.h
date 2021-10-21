#ifndef VOLCAN_H_INCLUDED
#define VOLCAN_H_INCLUDED

#include "casillero.h"

class Volcan: public Casillero
{
public:
    /*
    PRE: -
    POS: crea un casillero de tipo volcan.
   */
    Volcan(); // constructor

    /*
    PRE: elemento_pj es un string valido - agua, aire, fuego, tierra.
    POS: devuelve el costo base del casillero de tipo volcan.
   */
    int calcular_costo(string elemento_pj);

    /*
     PRE: -
     POS: devuelve el costo base del casillero de tipo volcan.
    */
    int obtener_costo_base();

    /*
    PRE: -
    POS: devuelve "volcan", el tipo de casillero.
   */
    string tipo_casillero();

};


#endif // VOLCAN_H_INCLUDED
