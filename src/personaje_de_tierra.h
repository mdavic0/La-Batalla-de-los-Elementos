#ifndef PERSONAJE_DE_TIERRA_H_INCLUDED
#define PERSONAJE_DE_TIERRA_H_INCLUDED

#include "personaje.h"

class Personaje_de_tierra: public Personaje
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
    POS: crea un personaje de tierra con nombre = nombre, escudo = escudo, vidas = vidas y con un valor de energia inicial aleatorio entre 0 y 20
    */
    Personaje_de_tierra(string nombre, int escudo, int vidas);

    /*
    Constructor
    PRE: -
    POS: crea un personaje de tierra con nombre = nombre, escudo con valores aleatorios entre 0 y 2, vida con valores aleatorios entre 10 y 100 y energia entre 0 y 20
    */
    Personaje_de_tierra(string nombre);

    /*
    Constructor
    PRE: los parametros son de tipo valido
    POS: crea un personaje de tierra con los valores pasados por parametro
    */
    Personaje_de_tierra(string nombre, int escudo, int vidas, int energia, int fila, int columna, int id_jugador, bool se_defiende);

    /*
    Constructor
    PRE: los parametros son de tipo valido
    POS: crea un personaje de tierra con los valores pasados por parametro
    */
    Personaje_de_tierra(string nombre, int escudo, int vidas, int energia, int fila, int columna, int id_jugador);

    /*
    Incrementa la energia segun la energia recuperada determinada en personaje.h
    */
    string alimentar();

    /*
    Devuelve true si el personaje alcanzo el maximo de veces que puede recibir alimento. Caso contrario devuelve false.
    */
    bool alcanzo_max_alimento();

    /*
    PRE: -
    POS: pone se_defiende en true si el personaje de tierra tiene energia suficiente para defenderse. Incrementa el escudo y resta energia usada.
    */
    void defender();

    /*
    PRE: el parametro es de tipo valido
    POS: incrementa el escudo del personaje.
    */
    void incrementar_escudo(bool incrementar);

    /*
     PRE: los parametros son de tipo valido
     POS: resta a la vida el danio_recibido segun el enemigo, le aplica el escudo.
     */
    void recibe_ataque(string elemento_enemigo, int danio_recibido);

    /*
     PRE: distancia es de tipo valido
     POS: calcula el danio por hacerle a un personaje enemigo segun la distancia a la que se encuentra del personaje de tierra
     */
    int calcular_danio_segun_distancia(int distancia);

};

#endif // PERSONAJE_DE_TIERRA_H_INCLUDED
