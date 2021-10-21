#ifndef CASILLERO_H_INCLUDED
#define CASILLERO_H_INCLUDED

#include <SFML/Graphics.hpp>

using namespace sf;

#include "personaje.h"
#include "personaje_de_fuego.h"
#include "personaje_de_agua.h"
#include "personaje_de_aire.h"
#include "personaje_de_tierra.h"

const string CAMINO = "camino";
const string LAGO = "lago";
const string MONTANIA = "montaña";
const string PRECIPICIO = "precipicio";
const string VACIO = "vacio";
const string VOLCAN = "volcan";

const int COSTO_CAMINO = 1;
const int COSTO_LAGO = 1;
const int COSTO_MONTANIA = 1;
const int COSTO_PRECIPICIO = 1;
const int COSTO_VACIO = 15;
const int COSTO_VOLCAN = 1;


class Casillero {
protected:
    Personaje* personaje;
    Casillero();

    Texture txt_casillero;
    Sprite spr_casillero;

public:
    /*
     PRE: nuevo es un parametro valido de tipo Personaje*, c es de tipo Coordenada.
     POS: asigna nuevo a personaje y le asigna las coordenadas pasadas por parametro.
     */
    void posicionar_personaje(Personaje* nuevo, Coordenada coordenada);

    /*
     PRE: nuevo es un parametro valido de tipo Personaje*.
     POS: asigna nuevo a personaje.
     */
    void posicionar_personaje(Personaje* nuevo);

    /*
     PRE: -
     POS: devuelve true si hay personaje posicionado en el casillero, false de lo contrario.
     */
    bool hay_personaje();

    /*
     PRE: -
     POS: devuelve el personaje posicionado en el casillero.
     */
    Personaje* obtener_personaje();

    /*
     PRE: elemento_pj es un string valido - agua, aire, fuego, tierra.
     POS: devuelve el costo base del casillero.
    */
    virtual int calcular_costo(string elemento_pj) = 0;

    /*
     PRE: -
     POS: devuelve el costo base del casillero.
    */
    virtual int obtener_costo_base() = 0;

    /*
    PRE: -
    POS: devuelve un string que indica el tipo de casillero.
    */
    virtual string tipo_casillero() = 0;

    virtual ~Casillero();  // destructor

    Sprite obtener_sprite();
    void cargar_graficos();
    void asignar_posicion(float x, float y);
};


#endif // CASILLERO_H_INCLUDED
