#ifndef PERSONAJE_DE_AIRE_H_INCLUDED
#define PERSONAJE_DE_AIRE_H_INCLUDED

#include "personaje.h"

class Personaje_de_aire: public Personaje
{
private:
    /*
    Devuelve el elemento del personaje
    */
    string de_que_elemento_soy();

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


public:
    /*
    Constructor
    PRE: 0 <= escudo <= 2, 10 <= vidas <= 100
    POS: crea un personaje de aire con nombre = nombre, escudo = escudo, vidas = vidas y con un valor de energia inicial aleatorio entre 0 y 20
    */
    Personaje_de_aire(string nombre, int escudo, int vidas);

    /*
    Constructor
    PRE: -
    POS: crea un personaje de aire con nombre = nombre, escudo con valores aleatorios entre 0 y 2, vida con valores aleatorios entre 10 y 100 y energia entre 0 y 20
    */
    Personaje_de_aire(string nombre);

    /*
     Constructor
     PRE: los parametros son de tipo valido
     POS: crea un personaje de aire con los valores pasados por parametro
     */
    Personaje_de_aire(string nombre, int escudo, int vidas, int energia, int fila, int columna, int id_jugador, bool se_defiende);

    /*
     Constructor
     PRE: los parametros son de tipo valido
     POS: crea un personaje de aire con los valores pasados por parametro
     */
    Personaje_de_aire(string nombre, int escudo, int vidas, int energia, int fila, int columna, int id_jugador);

    /*
    Como este personaje no necesita alimentarse, este metodo se encarga de recordarselo al usuario
    */
    string alimentar();

    /*
    Devuelve true si el personaje alcanzo el maximo de veces que puede recibir alimento. Caso contrario devuelve false.
    */
    bool alcanzo_max_alimento();

    /*
     PRE: -
     POS: pone se_defiende en true si el personaje de aire tiene energia suficiente para defenderse. Resta energia usada.
     */
    void defender();

    /*
     PRE: los parametros son de tipo valido
     POS: resta a la vida el danio_recibido segun el enemigo, le aplica el escudo.
     */
    void recibe_ataque(string elemento_enemigo, int danio_recibido);

};


#endif // PERSONAJE_DE_AIRE_H_INCLUDED
