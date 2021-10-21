#ifndef PERSONAJE_H_INCLUDED
#define PERSONAJE_H_INCLUDED

#include <SFML/Graphics.hpp>

using namespace sf;

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "coordenada.h"

using namespace std;

const string ELEMENTO_AIRE = "aire";
const string ELEMENTO_FUEGO = "fuego";
const string ELEMENTO_AGUA = "agua";
const string ELEMENTO_TIERRA = "tierra";

const string ALIMENTO_P_AGUA = "plancton";
const string ALIMENTO_P_TIERRA = "hierbas";
const string ALIMENTO_P_FUEGO = "madera";
const string ALIMENTO_P_AIRE = "Este personaje no necesita alimentarse ";

const int ATAQUE_BASE_AGUA = 20;
const int ATAQUE_BASE_AIRE = 15;
const int ATAQUE_BASE_FUEGO = 20;
const int ATAQUE_BASE_TIERRA_DEBIL = 10;
const int ATAQUE_BASE_TIERRA_MEDIO = 20;
const int ATAQUE_BASE_TIERRA_FUERTE = 30;

const int ATAQUE_FUERTE_AGUA = 30;
const int ATAQUE_DEBIL_AGUA = 10;
const int ATAQUE_FUERTE_AIRE = 20;
const int ATAQUE_DEBIL_AIRE = 10;
const int ATAQUE_FUERTE_FUEGO = 30;
const int ATAQUE_DEBIL_FUEGO = 10;
const int ATAQUE_FUERTE_TIERRA = 20; // +20
const int ATAQUE_DEBIL_TIERRA = 10;

const int MIN_ENERGIA_DEFENSA_AGUA = 12;
const int MIN_ENERGIA_DEFENSA_AIRE = 15;
const int MIN_ENERGIA_DEFENSA_FUEGO = 10;
const int MIN_ENERGIA_DEFENSA_TIERRA = 5;

const int MIN_ENERGIA_ATAQUE = 5;
const int MIN_ENERGIA_ATAQUE_AGUA = 5;
const int MIN_ENERGIA_ATAQUE_TIERRA = 6;
const int MIN_ENERGIA_ATAQUE_FUEGO = 5;
const int MIN_ENERGIA_ATAQUE_AIRE = 8;

const int VALOR_MIN_VIDA = 10;
const int VALOR_MAX_VIDA = 100;
const int VALOR_MIN_ESCUDO = 0;
const int VALOR_MAX_ESCUDO = 2;
const int VALOR_MIN_ENERGIA = 0;
const int VALOR_MAX_ENERGIA = 20;

const int ENERGIA_RECUPERADA_P_AGUA = 10;
const int ENERGIA_RECUPERADA_P_AIRE = 5;
const int ENERGIA_RECUPERADA_P_TIERRA = 8;
const int ENERGIA_RECUPERADA_P_FUEGO = 10;
const int VIDA_RECUPERADA_P_FUEGO = 15;

const int CURACION_ALIADOS_PERSONAJE_AGUA = 10;
const int CURACION_PERSONAJE_AGUA = 50;
const int CURACION_PERSONAJE_FUEGO = 10;
const int MAX_VECES_ALIMENTADO_P_AGUA = 3;
const int PUNTOS_EXTRA_ESCUDO_TIERRA = 2;

const string ENERGIA_INSUFICIENTE = "Energia insuficiente.";

const int NO_ELEGIDO = -1;

class Personaje {
protected:
    // Atributos
    string nombre;
    int escudo;
    int vidas;
    int energia;
    Coordenada coord_personaje;
    int id_jugador;
    bool se_defiende;


    // Constructores
    /*
    PRE: -
    POS: crea un personaje de tierra con nombre = nombre, escudo = escudo, vidas = vidas y energia con valores aleatorios entre 0 y 20
    */
    Personaje(string nombre, int escudo, int vidas);

    /*
    PRE: -
    POS: crea un personaje de tierra con nombre = nombre escudo con valores aleatorios entre 0 y 2, vida con valores aleatorios entre 10 y 100 y energia entre 0 y 20
    */
    Personaje(string nombre);

    /*
   PRE: -
   POS: crea un personaje con los valores ingresados. Vamos a utilizar este método al cargar_partida la partida.
   */
    Personaje(string nombre, int escudo, int vidas, int energia, int fila, int columna, int id_jugador);

    /*
   PRE: -
   POS: crea un personaje con los valores ingresados. Vamos a utilizar este metodo al cargar la partida.
   */
    Personaje(string nombre, int escudo, int vidas, int energia, int fila, int columna, int id_jugador, bool se_defiende);

    Texture txt_personaje;
    Sprite spr_personaje;

public:

    /*
    Destructor
    */
    virtual ~Personaje();

    /*
    Crea una nueva coordenada para el personaje con los valores de fila y columna recibidos por parametro
     */
    void asignar_coordenadas_pj(int fila, int columna);

    /*
    Devuelve el nombre del personaje
    */
    string nombre_personaje();

    /*
    Devuelve los detalles del personaje (nombre, elemento, escudo, vidas y energia)
    */
    string detalles_personaje();

    /*
    Alimenta al personaje, incrementando la energia segun el elemento del cual sea el personaje
    Para el personaje de aire, dado que no necesita alimentarse, este metodo se encarga de recordarselo al usuario
    */
    virtual string alimentar() = 0;

    /*
    Devuelve true si el personaje alcanzo el maximo de veces que puede recibir alimento. Caso contrario devuelve false.
    */
    virtual bool alcanzo_max_alimento() = 0;

    /*
    PRE: -
    POS: devuelve true si vida > 0, false de lo contrario.
    */
    bool esta_vivo();

    /*
    PRE: costo_energia es un dato valido.
    POS: resta costo_energia a la energia del personaje.
    */
    void restar_energia(int costo_energia);

    /*
    Devuelve el elemento del personaje
    */
    virtual string de_que_elemento_soy() = 0;

    /*
     PRE: id_jugador es un entero valido
     POS: asigna el parametro id_jugador al atributo
     */
    void elegir(int id_jugador);

    /*
     PRE: -
     POS: devuelve atributo se_defiende.
     */
    bool obtener_se_defiende();

    /*
     PRE: danio_recibido es un entero valido.
     POS: devuelve el danio recibido por el personaje, reduciendo el danio por porcentaje segun el escudo del personaje.
     */
    int aplicar_escudo(int danio_recibido);

    /*
     PRE: -
     POS: pone se_defiende en true si la energia es necesaria para realizar la defensa, false de lo contrario
     */
    virtual void defender() = 0;

    /*
    PRE: elemento_enemigo y danio_recibido son datos validos
    POS: resta el danio_recibido al personaje, luego de aplicar defensas
    */
    virtual void recibe_ataque(string elemento_enemigo, int danio_recibido) = 0;

    /*
     PRE: fila, columna y energia_minima son datos enteros.
     POS: cambia las coordendas de personaje por las pasadas por parametro si tiene energia suficiente.
     */
    void mover(int fila, int columna, int energia_minima);

    /*
     PRE: -
     POS: devuelve id_jugador
     */
    int obtener_id_jugador();

    /*
     PRE: -
     POS: devuelve vida
     */
    int obtener_vida();

    /*
     PRE: -
     POS: devuelve energia
     */
    int obtener_energia();

    /*
     PRE: -
     POS: devuelve escudo
     */
    int obtener_escudo();

    /*
     PRE: -
     POS: devuelve coordenada del personaje
     */
    Coordenada obtener_coordenadas();

    /*
     PRE: vida es un entero
     POS: suma el parametro a la vida actual del personaje
     */
    void curar(int vida);

    /*
     PRE: los graficos fueron cargados
     POS: devuelve el grafico (sprite) del personaje;
     */
    Sprite obtener_sprite();

    /*
     PRE: -
     POS: carga los graficos de personaje;
     */
    void cargar_graficos();

    /*
     PRE: -
     POS: devuelve un numero aleatorio entre 1 y 3;
     */
    int numero_aleatorio();

    /*
     PRE: -
     POS: Aumenta 5 puntos de energia al personaje de aire despues de cad turno;
     */
    void cambiar_turno(); //obs: lo usa el pj de aire cada vez que pasa su turno;

    /*
     PRE: -
     POS: devuelve la energia minima necesaria para realizar la defensa;
     */
    virtual int obtener_energia_minima_defensa() = 0;

    /*
     PRE: -
     POS: devuelve la energia minima necesaria para realizar el ataque;
     */
    virtual int obtener_energia_minima_ataque() = 0;
};

#endif // PERSONAJE_H_INCLUDED
