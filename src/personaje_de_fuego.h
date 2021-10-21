#ifndef PERSONAJE_DE_FUEGO_H_INCLUDED
#define PERSONAJE_DE_FUEGO_H_INCLUDED

#include "personaje.h"

class Personaje_de_fuego: public Personaje
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

    /*
     PRE: -
     POS: Si la energia llega a 0 , le resta 5 puntos de vida;
     */
    void restar_vida();

public:
    /*
    Constructor
    PRE: 0 <= escudo <= 2, 10 <= vidas <= 100
    POS: crea un personaje de fuego con nombre = nombre, escudo = escudo, vidas = vidas y con un valor de energia inicial aleatorio entre 0 y 20
    */
    Personaje_de_fuego(string nombre, int escudo, int vidas);

    /*
    Constructor
    PRE: -
    POS: crea un personaje de fuego con nombre = nombre, y sus valores de escudo, vida y energia aleatorios entre las cotas definidas en personaje.h
    */
    Personaje_de_fuego(string nombre);


    /*
     Constructor
     PRE: los parametros son de tipo valido
     POS: crea un personaje de fuego con los valores pasados por parametro
     */
    Personaje_de_fuego(string nombre, int escudo, int vidas, int energia, int fila, int columna, int id_jugador, bool se_defiende);


    /*
     Constructor
     PRE: los parametros son de tipo valido
     POS: crea un personaje de fuego con los valores pasados por parametro
     */
    Personaje_de_fuego(string nombre, int escudo, int vidas, int energia, int fila, int columna, int id_jugador);

    /*
    Incrementa la vida segun la vida recuperada determinada en personaje.h
    */
    string alimentar();

    /*
    Devuelve true si el personaje alcanzo el maximo de veces que puede recibir alimento. Caso contrario devuelve false.
    */
    bool alcanzo_max_alimento();

    /*
    PRE: -
    POS: pone se_defiende en true si el personaje de fuego tiene energia suficiente para defenderse. Resta energia usada y lo cura.
    */
    void defender();

    /*
    PRE: los parametros son de tipo valido
    POS: resta a la vida el danio_recibido segun el enemigo, le aplica el escudo.
    */
    void recibe_ataque(string elemento_enemigo, int danio_recibido);

};


#endif // PERSONAJE_DE_FUEGO_H_INCLUDED
