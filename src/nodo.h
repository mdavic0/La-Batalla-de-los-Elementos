#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED

#include "vertice.h"

typedef Vertice* Dato;

class Nodo {
private:
    // Atributos
    Dato dato;
    Nodo* siguiente;

public:
    /*
    Constructor:
    Crea un nodo con dato = d y siguiente = 0
    */
    Nodo(Dato d);

    /*
    Cambia el dato del nodo por d
    */
    void cambiar_dato(Dato d);

    /*
    Cambia siguiente por s
    */
    void cambiar_siguiente(Nodo* s);

    /*
    Devuelve el dato del nodo
    */
    Dato obtener_dato();

    /*
    Devuelve el siguiente nodo
    */
    Nodo* obtener_siguiente();

    /*
    Devuelve true si hay un nodo siguiente, false en caso contrario
    */
    bool tiene_siguiente();
};

#endif // NODO_H_INCLUDED
