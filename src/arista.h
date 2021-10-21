#ifndef ARISTA_H_INCLUDED
#define ARISTA_H_INCLUDED
#include "vertice.h"

class Vertice;

class Arista {
private:
    // atributos
    Vertice* origen;
    Vertice* destino;
    int costo;
public:
    /*
     PRE: -
     POS: crea una arista con origen = 0, destino = 0 y costo = 0.
     */
    Arista();

    /*
     PRE: -
     POS: crea una arista con origen, destino y costo pasados por parametro.
     */
    Arista(Vertice* origen, Vertice* destino, int costo);

    /*
    PRE: -
    POS: crea una arista con origen y destino pasados por parametro y costo = 0.
    */
    Arista(Vertice* origen, Vertice* destino);

    /*
     PRE: -
     POS: devuelve vertice destino.
     */
    Vertice* obtener_destino();

    /*
    PRE: -
    POS: devuelve vertice origen.
    */
    Vertice* obtener_origen();

    /*
     PRE: -
     POS: devuelve costo.
     */
    int obtener_costo();

    /*
    PRE: costo es un entero valido.
    POS: asigna dicho costo a la arista
    */
    void insertar_costo(int costo);

    // destructor
    ~Arista();
};
#endif // ARISTA_H_INCLUDED
