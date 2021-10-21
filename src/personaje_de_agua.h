#ifndef _H_INCLUDED
#define _H_INCLUDED

#include "personaje.h"

class Personaje_de_agua: public Personaje
{
private:
    // Atributos
    int veces_alimentado = 0;

public:
    /*
    Constructor
    PRE: 0 <= escudo <= 2, 10 <= vidas <= 100
    POS: crea un personaje de agua con nombre = nombre, escudo = escudo, vidas = vidas y con un valor de energia inicial aleatorio entre 0 y 20
    */
    Personaje_de_agua(string nombre, int escudo, int vidas);

    /*
    Constructor
    PRE: -
    POS: crea un personaje de agua con nombre = nombre, y sus valores de escudo, vida y energia aleatorios entre las cotas definidas en personaje.h
    */
    Personaje_de_agua(string nombre);

    /*
     Constructor
     PRE: los parametros son de tipo valido
     POS: crea un personaje de agua con los valores pasados por parametro
     */
    Personaje_de_agua(string nombre, int escudo, int vidas, int energia, int fila, int columna, int id_jugador, bool se_defiende);

    /*
     Constructor
     PRE: los parametros son de tipo valido
     POS: crea un personaje de agua con los valores pasados por parametro
     */
    Personaje_de_agua(string nombre, int escudo, int vidas, int energia, int fila, int columna, int id_jugador);

    /*
    Incrementa la energia segun la energia recuperada determinada en personaje.h (mientras el personaje no haya superado el maximo de veces que puede ser alimentado)
    */
    string alimentar();

    /*
     PRE: -
     POS: pone se_defiende en true si el personaje de agua tiene energia suficiente para defenderse. Resta energia usada y cura al personaje.
     */
    void defender();

    /*
     PRE: los parametros son de tipo valido
     POS: resta a la vida el danio_recibido segun el enemigo, le aplica el escudo.
     */
    void recibe_ataque(string elemento_enemigo, int danio_recibido);

private:
    /*
    Devuelve el elemento del personaje
    */
    string de_que_elemento_soy();

    /*
    Devuelve true si el personaje alcanzo el maximo de veces que puede recibir alimento. Caso contrario devuelve false.
    */
    bool alcanzo_max_alimento();

    /*
     PRE: -
     POS: devuelve la energia minima necesaria para realizar la defensa;
     */
    int obtener_energia_minima_defensa();

    /*
     PRE: -
     POS: devuelve la energia minima necesaria para realizar el ataque;
     */
    int obtener_energia_minima_ataque();

};

#endif // _H_INCLUDED
