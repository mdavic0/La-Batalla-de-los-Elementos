#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#include "jugador.h"
#include "grafo.h"
#include <string>
#include <cstdio>

#include <SFML/Graphics.hpp>

using namespace sf;

const string TITULO = "La Batalla De Los Elementos";

const int JUGADOR_1 = 0;
const int JUGADOR_2 = 1;
const int MAX_CANT_JUGADORES = 2;

const int OPCIONES_VALIDAS_GUARDAR_SALIR = 2;
const int OPCIONES_VALIDAS_MENU_JUEGO = 3;
const int OPCIONES_VALIDAS_SUB_MENU_JUEGO = 3;

const string GUARDAR_PARTIDA = "Guardar y salir";
const string SEGUIR_JUGANDO = "Seguir jugando";

const string ALIMENTARSE = "Alimentarse";
const string MOVERSE = "Moverse";
const string PASAR_OPCION = "Pasar opcion";

const string DEFENDERSE = "Defenderse";
const string ATACAR = "Atacar";

const string ARCHIVO_MAPA = "../Mapa/mapa.csv";
const string ARCHIVO_CARGA = "../PartidasGuardadas/partida.csv";
const string ARCHIVO_PERSONAJES = "../CargarPersonajes/personajes.csv";

const string ERROR_NO_HAY_PERSONAJE = "No hay un personaje en esa posicion";

class Juego {
private:
    // Atributos
    Grafo* tablero;
    Jugador* jugadores[MAX_CANT_JUGADORES];
    int turno;
    int pos_personaje;
    bool esta_activo_menu_juego;
    bool esta_activo_sub_menu_juego;
    int opcion_seleccionada;
    bool termino;
    bool partida_cargada;

    //Parte grafica SFML:
    RenderWindow* ventana_juego;

    Font fuente;
    Text titulo;

    Text opciones_menu_juego[OPCIONES_VALIDAS_MENU_JUEGO];
    Text opciones_sub_menu_juego[OPCIONES_VALIDAS_SUB_MENU_JUEGO];
    Text opciones_guardar_salir[OPCIONES_VALIDAS_GUARDAR_SALIR];

    Text turno_actual;
    Text detalles_personajes_jugador_1;
    Text detalles_personajes_jugador_2;

    Sprite spr_personajes_jugador_1[MAX_PERSONAJES];
    Sprite spr_personajes_jugador_2[MAX_PERSONAJES];

    Texture txt_fondo;
    Sprite spr_fondo;

public:
    /*
	Constructor
	 PRE:-
	 POS: inicializa un nuevo juego. Incializa el tablero y los personajes.
	 */
    Juego();

    /*
     PRE: -
     POS: devuelve true si ambos jugadores eligieron el max de personajes, false de lo contrario
     */
    bool comenzo();

    /*
     PRE: -
     POS: inicializa el juego y su interfaz
     */
    void jugar();

    /*
   PRE: jugador es de tipo valido
   POS: devuelve un objeto Jugador*
   */
    Jugador* obtener_jugador(int jugador);

    /*
     PRE: -
     POS: devuelve el tablero del juego.
     */
    Grafo * obtener_grafo();

    /*
	 PRE: archivo_carga es de tipo valido
	 POS: carga una partida guardada
	 */
    bool cargar_partida(string archivo_carga);

    ~Juego(); // destructor

private:
    /*
     PRE: los parametros son de tipo valido
     POS: crea un personaje con los parametros pasados y lo ubica en el tablero
     */
    void crear_y_ubicar_personaje(string elemento, string nombre, int escudo, int vida, int energia, int fila, int columna, int id_jugador);

    /*
	 PRE: -
	 POS: determina el primer turno de manera aleatoria
	 */
    void determinar_primer_turno();

    /*
    PRE: -
    POS: indica de que jugador es el turno
    */
    int turnar();

    /*
    PRE: -
    POS: Verifica a que personaje del jugador del que es el turno le toca,
     en caso de que le toque al personaje 3, incrementa el turno actual
    */
    void chequear_subturno();

    /*
	 PRE: -
	 POS: posiciona personajes en el tablero al iniciar el juego
	 */
    void posicionar_personajes();

    /*
     PRE: -
     POS: alimenta al personaje del cual es el turno actual
     */
    void alimentar();

    /*
	 PRE: -
	 POS: realiza el ataque segun el elemento
	 */
    void atacar();

    /*
     PRE: enemigo es de tipo Coordenada
     POS: realiza el ataque de personaje de agua
     */
    void ataque_p_agua(Coordenada enemigo);

    /*
     PRE: -
     POS: realiza el ataque de personaje de aire
     */
    void ataque_p_aire();

    /*
    PRE: coord_act es de tipo Coordenada
    POS: realiza el ataque de personaje de fuego
    */
    void ataque_p_fuego(Coordenada coord_act);

    /*
     PRE: enemigo y coord_act son de tipo Coordenada
     POS: realiza el ataque de personaje de tierra
     */
    void ataque_p_tierra(Coordenada coord_act, Coordenada enemigo);

    /*
    PRE: -
    POS: defiende a un personaje segun su elemento
    */
    void defenderse();

    /*
     PRE: pj es de tipo Personaje*
     POS: realiza la defensa de personaje de agua
     */
    void defensa_p_agua(Personaje* pj);

    /*
     PRE: pj es de tipo Personaje*
     POS: realiza la defensa de personaje de aire
     */
    void defensa_p_aire(Personaje* pj);

    /*
     PRE: pj es de tipo Personaje*
     POS: realiza la defensa de personaje de tierra
     */
    void defensa_p_tierra(Personaje* pj);

    /*
     PRE: -
     POS: mueve a un personaje segun su energia y posicion
     */
    void moverse();


    /*
     PRE: -
     POS: Si se elige pasar_opcion estando activo el menu_juego pasa al sub_menu,
          si se elige estando activo el sub_menu cambia turno
     */
    void pasar_opcion();

    /*
	 PRE: -
	 POS: guarda la partida en un archivo csv "partida.csv", la primera linea es el turno desde el cual se guardó
     la partida
	 */
    void guardar_partida();

    /*
	 PRE: -
	 POS: Cargan graficos para la interfaz del juego
	 */
    void cargar_graficos();
    void cargar_graficos_menu_juego();
    void cargar_graficos_sub_menu_juego();
    void cargar_graficos_detalles_personajes();
    void cargar_graficos_turno();
    void cargar_graficos_guardar_salir();

    /*
	 PRE: Los graficos ya fueron cargados
	 POS: Dibujan en la ventana del juego los graficos
	 */
    void dibujar_juego();
    void dibujar_tablero();
    void dibujar_personajes();
    void dibujar_menu_juego();
    void dibujar_sub_menu_juego();
    void dibujar_guardar_salir();

    /*
	 PRE: -
	 POS: Muestra el menu en la ventana del juego;
	 */
    void interfaz_menu_juego();

    /*
	 PRE: -
	 POS: Muestra el sub_menu en la ventana del juego;
	 */
    void interfaz_sub_menu_juego();

    /*
	 PRE: -
	 POS: Muestra opciones para guardar_salir o para seguir
          jugando en la ventana del juego;
	 */
    void interfaz_guardar_salir();

    /*
	 PRE: -
	 POS: Procesan los eventos que ocurren en cada instante en la ventana del juego,
     si el usuario elige una opcion, ejecuta el metodo correspondiente;
	 */
    void procesar_eventos_menu_juego();
    void procesar_eventos_sub_menu_juego();
    void procesar_eventos_guardar_salir();

    /*
	 PRE: -
	 POS: Marcan con color amarillo la opcion_seleccionada,
          y con blanco la opcion seleccionada anterior;
	 */
    void subir_menu_juego();
    void bajar_menu_juego();
    void subir_sub_menu_juego();
    void bajar_sub_menu_juego();
    void subir_guardar_salir();
    void bajar_guardar_salir();

    void seguir_jugando();

    /*
	 PRE: -
	 POS: Devuelve el atributo opcion_seleccionada;
	 */
    int obtener_opcion_seleccionada() const;

    /*
	 PRE: Recibe un mensaje de tipo Text
	 POS: Imprime el mensaje en la ventana del juego;
	 */
    void imprimir_mensaje(Text mensaje);

    /*
	 PRE: -
	 POS: Pide al usuario una coordenada y la devuelve;
	 */
    string pedir_coordenada();

    /*
	 PRE: -
	 POS: Devuelve una coordenada valida para moverse;
	 */
    Coordenada coordenada_valida_moverse();

    /*
	 PRE: -
	 POS: Devuelve una coordenada valida para atacar;
	 */
    Coordenada coordenada_valida_atacar();

    /*
	 PRE: -
	 POS: Cierra el juego;
	 */
    void salir();

    void fin_del_juego();
};


#endif // JUEGO_H_INCLUDED
