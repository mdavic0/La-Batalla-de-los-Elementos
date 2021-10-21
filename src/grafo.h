#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#include <fstream>
#include <iostream>
#include <string>

#include "camino.h"
#include "lago.h"
#include "montania.h"
#include "precipicio.h"
#include "vacio.h"
#include "volcan.h"
#include "lista.h"
#include "vertice.h"

using namespace std;

const int MIN_CANT_ARISTAS = 2;

const Coordenada ARRIBA = Coordenada(-1,0);
const Coordenada ABAJO= Coordenada(1,0);
const Coordenada IZQUIERDA= Coordenada(0,-1);
const Coordenada DERECHA= Coordenada(0,1);

const Coordenada ARRIBA_IZQ = Coordenada(-1,-1);
const Coordenada ABAJO_IZQ = Coordenada(1,-1);
const Coordenada ARRIBA_DER = Coordenada(-1,1);
const Coordenada ABAJO_DER = Coordenada(1,1);

const int CANTIDAD_CASILLEROS = 64;
const int INFINITO = 9999;

class Grafo {
private:
    Lista* vertices;
    int dim_fila;
    int dim_columna;
    Vertice*** tablero;

    int** distancias_p_agua;
    int** recorridos_p_agua;

    int** distancias_p_aire;
    int** recorridos_p_aire;

    int** distancias_p_fuego;
    int** recorridos_p_fuego;

    int** distancias_p_tierra;
    int** recorridos_p_tierra;

    int** distancias_ataque_tierra;

public:
    /*
	Constructor
	 PRE: nombre_archivo es de tipo valido
	 POS: inicializa un grafo a partir del archivo pasado por parametro
	 */
    Grafo(string nombre_archivo);

    /*
     PRE: todos los parametros son validos
     POS: conecta el vertice pasado por parametro en la direccion indicada. Lo agrega al array de diagonales si es_diagonal es true.
     */
    void conectar_vertice(Vertice* vertice, Coordenada direccion, bool es_diagonal);

    /*
    PRE: -
    POS: busca vertices adyacentes
    */
    void conectar_vertices();

    /*
     PRE: -
     POS: devuelve la lista de vertices
     */
    Lista* obtener_vertices();

    /*
     PRE: coordenada es de tipo valido
     POS: devuelve el vertice de la coordeanda pedida
     */
    Vertice* acceder_tablero(Coordenada coordenada);

    /*
    PRE: todos los parametros son validos
    POS: devuelve el costo de ir desde origen hasta destino
    */
    int costo_camino_minimo(Vertice* origen, Vertice* destino);

    /*
     PRE: todos los parametros son validos
     POS: devuelve el camino minimo entre el nodo inicial y el final, segun el elemento del personaje
     */
    string camino_minimo(int nodo_inicial, int nodo_final, string elemento);

    ~Grafo(); // destructor
private:
    /*
	 PRE: v es de tipo valido
	 POS: busca los vertices adyacentes a v
	 */
    void buscar_vertices_adyacentes(Vertice* v);

    /*
    PRE: archivo es de tipo string
    POS: carga el mapa desde el archivo
    */
    void cargar_mapa(string archivo);

    /*
     PRE: -
     POS: carga el tablero de vertices
     */
    void cargar_tablero();

     /*
     PRE: casillero es string
     POS: crea un casillero del tipo pasado por parametro
      */
    Casillero* crear_casillero(string casillero);

    /*
     PRE: los parametros son validos
     POS: crea una arista con origen y destino indicados y la agrega a la lista. Si es_diagonal es true, lo agrega a la lista de diagonales
     */
    void crear_y_agregar_arista(Vertice* origen, Vertice* destino, bool es_diagonal);

    /*
     PRE: -
     POS: elimina la matriz
     */
    void destruir_matriz();

    /*
     PRE: todos los parametros son validos
     POS: arma las matrices de camino minimo a traves del metodo floyd-warshall
     */
    void floyd_warshall(string elemento, int** distancias, int** recorridos);

    /*
     PRE: -
     POS: arma las matrices de camino minimo de tierra a traves del metodo floyd-warshall
     */
    void floyd_warshall();


};
#endif // GRAFO_H_INCLUDED