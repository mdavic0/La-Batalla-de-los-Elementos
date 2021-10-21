#ifndef MONTANIA_H_INCLUDED
#define MONTANIA_H_INCLUDED

#include "casillero.h"

class Montania: public Casillero
{
public:
    /*
    PRE: -
    POS: crea un casillero de tipo montania.
   */
    Montania(); // constructor

    /*
     PRE: elemento_pj es un string valido - agua, aire, fuego, tierra.
     POS: devuelve el costo base del casillero de tipo montania.
    */
    int calcular_costo(string elemento_pj);

    /*
     PRE: -
     POS: devuelve el costo base del casillero de tipo montania.
    */
    int obtener_costo_base();

    /*
     PRE: -
     POS: devuelve "montania", el tipo de casillero.
    */
    string tipo_casillero();

};

#endif // MONTANIA_H_INCLUDED
