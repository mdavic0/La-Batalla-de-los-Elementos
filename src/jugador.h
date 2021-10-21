#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED

#include "diccionario.h"
#include "personaje.h"

const int MAX_PERSONAJES = 3;

class Personaje;

class Jugador {
private:
    //Atributos
    Personaje* personajes_elegidos[MAX_PERSONAJES];
    int id;
    int cantidad_personajes;

public:
    /*
     PRE: -
     POS: crea un objeto jugador con cant_personajes = 0
     */
    Jugador(); // constructor

    /*
     PRE: id debe ser de tipo entero
     POS: crea un personaje con id pasado por parametro
     */
    Jugador(int id);
    ~Jugador(); // destructor

    /*
     PRE: nuevo debe ser de tipo Personaje*
     POS: agrega un personaje al vector de personajes_elegidos
     */
    void agregar_personaje(Personaje* nuevo);

    /*
     PRE: -
     POS: devuelve true si el jugador eligio el maximo de personajes, false de lo contrario
     */
    bool eligio_max_personajes();

    /*
   PRE: -
   POS: devuelve true si todos los personajes del jugador tienen vida = 0, false de lo contrario
   */
    bool jugador_perdio();

    /*
    PRE: -
    POS: devuelve los nombres de todos los personajes del jugador
    */
    string personajes();

    /*
    PRE: -
    POS: devuelve los detalles de todos los personajes del jugador
    */
    string detalles_personajes();

    /*
     PRE: -
     POS: devuelve cantidad de personajes vivos del jugador
     */
    int obtener_cantidad_personajes();

    /*
     PRE: -
     POS: devuelve id del jugador
     */
    int obtener_id();

    /*
    PRE: pos es un entero valido
    POS: devuelve el personaje ubicado en la posicion pos, en el vector de personajes del jugador
    */
    Personaje* obtener_personaje(int pos);
};

#endif // JUGADOR_H_INCLUDED

