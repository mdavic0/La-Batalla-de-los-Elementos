#ifndef VERTICE_H_INCLUDED
#define VERTICE_H_INCLUDED
#include "casillero.h"
#include "camino.h"
#include "lago.h"
#include "montania.h"
#include "precipicio.h"
#include "vacio.h"
#include "volcan.h"
#include "coordenada.h"
#include "vector.h"

const int MAX_CANT_ARISTAS_SIN_DIAGONALES = 4;
const int MAX_CANT_ARISTAS_CON_DIAGONALES = 8;

class Arista;

class Vertice {
private:
    Arista** vertices_ady;
    Arista** vertices_ady_y_diagonales;
    int cant_aristas;
    int cant_aristas_contando_diagonales;
    Casillero* casillero; // el datazo
    Coordenada coordenadas; // el ID

public:
    /*
     PRE: casillero es un objeto de tipo Casillero*, primera y segunda son de tipo entero.
     POS: crea un objeto Vertice con casillero, primera y segunda iguales a los parametros pasados.
     */
    Vertice(Casillero* casillero, int primera, int segunda);

    /*
     PRE: -
     POS: crea un objeto Vertice con casillero = 0 y coordenada (0,0)
     */
    Vertice();

    /*
     PRE: nueva es un objeto de tipo Arista, contando_diagonales es un booleano.
     POS: agrega nueva al vector de aristas contando diagonales si el bool es true, o al vector sin diagonales si es false.
     */
    void agregar_arista(Arista* nueva, bool contando_diagonales);

    /*
     PRE: -
     POS: devuelve las coordenadas del vertice.
     */
    Coordenada obtener_coordenadas();

    /*
     PRE: destino es un objeto de tipo Vertice* y contando_diagonales es un booleano.
     POS: devuelve true si hay una arista que conecte con destino, false de lo contrario. Se fija en el vector con diagonales
          si contando_diagonales es true, sin ellas de lo contrario.
     */
    bool hay_arista(Vertice* destino, bool contando_diagonales);

    /*
    PRE: contando_diagonales es booleano.
    POS: devuelve la cantidad de aristas en el vector con diagonales si contando_diagonales es true, o en el vector sin ellas si es false.
    */
    int obtener_cantidad_aristas(bool contando_diagonales);

    /*
    PRE: pos es un entero, contando_diagonales es booleano.
    POS: devuelve la arista en posicion pos en el vector con diagonales si contando_diagonales es true, o en el vector sin ellas si es false.
    */
    Arista* obtener_arista(int pos, bool contando_diagonales);

    /*
    PRE: -
    POS: devuelve el casillero.
    */
    Casillero* obtener_casillero();

    /*
     POS: libera la memoria
     */
    ~Vertice(); // destructor
};
#endif // VERTICE_H_INCLUDED