#ifndef MENUSFML_MENU_H
#define MENUSFML_MENU_H
#include <SFML/Graphics.hpp>

#include "personaje.h"
#include "personaje_de_agua.h"
#include "personaje_de_aire.h"
#include "personaje_de_fuego.h"
#include "personaje_de_tierra.h"
#include <fstream>
#include "diccionario.h"
#include "juego.h"

using namespace  std;

const int OPCIONES_VALIDAS_MENU = 6;
const int OPCIONES_VALIDAS_SUB_MENU = 4;

const string ERROR_APERTURA = "No se pudo abrir el archivo de personajes";
const string ERROR_DICCIONARIO_VACIO = "No hay personajes en el diccionario";
const string ERROR_PERSONAJE_NO_DISPONIBLE = "El personaje no esta disponible";

const string MENSAJE_BIENVENIDA = "Bienvenido!";

const string AGREGAR_PERSONAJE = "Agregar un nuevo personaje a la lista";
const string ELIMINAR_PERSONAJE = "Eliminar un personaje de la lista";
const string MOSTRAR_NOMBRES = "Mostrar todos los nombres de los personajes";
const string BUSCAR_DETALLES = "Buscar por nombre los detalles de un personaje en particular";
const string COMENZAR_JUEGO = "Comenzar juego";
const string SELECCIONAR_PERSONAJE = "Seleccionar personaje";
const string SALIR = "Salir";

using namespace sf;

class Menu {

private:

   //Atributos

    Diccionario* personajes;

    int opcion_seleccionada;
    Font fuente;
    Text titulo;
    Text opciones_menu[OPCIONES_VALIDAS_MENU];
    Text opciones_sub_menu[OPCIONES_VALIDAS_SUB_MENU];

    RenderWindow* ventana_menu;

    Texture txt_fondo;
    Sprite spr_fondo;
    Text turno_actual;

    bool esta_activo;
    bool esta_activo_sub_menu;

    Juego juego;
    int turno_seleccion;

public:
    /*
   Constructor:
   Crea un menu con el diccionario de personajes vacio.
   */
    Menu();

    /*
    Destructor:
    Libera memoria
    */
    ~Menu();

    /*
    PRE: El archivo debe ser de tipo csv con el formato elemento,nombre,escudo,vida
    POS: Lee el archivo con el nombre recibido por parametro y, si pudo abrirse, crea personajes con los datos del mismo y los carga a la lista de personajes
    */
    void cargar_personajes(string archivo);

private:
    /*
	 PRE: -
	 POS: Muestra el menu en la ventana;
	 */
    void interfaz_menu();

    /*
	 PRE: -
	 POS: Muestra el sub_menu en la ventana;
	 */
    void interfaz_sub_menu();

    /*
   PRE: -
   POS: Cargan graficos para la interfaz del menu
   */
    void cargar_graficos();
    void cargar_graficos_turno();
    void cargar_graficos_menu();
    void cargar_graficos_sub_menu();

    /*
	 PRE: -
	 POS: Procesan los eventos que ocurren en cada instante en la ventana,
     si el usuario elige una opcion, ejecuta el metodo correspondiente;
	 */
    void procesar_eventos();
    void procesar_eventos_sub_menu();

    /*
	 PRE: Los graficos ya fueron cargados
	 POS: Dibujan en la ventana del menu los graficos
	 */
    void dibujar_menu();
    void dibujar_sub_menu();

    /*
	 PRE: -
	 POS: Marcan con color amarillo la opcion_seleccionada,
          y con blanco la opcion seleccionada anterior;
	 */
    void subir();
    void bajar();
    void subir_sub_menu();
    void bajar_sub_menu();

    /*
	 PRE: -
	 POS: Devuelve el atributo opcion_seleccionada;
	 */
    int obtener_opcion_seleccionada() const;

    /*
    Crea un personaje segun el elemento, nombre, valor de escudo y valor de vida ingresados
    */
    void cargar_personaje_segun_elemento(string elemento, string nombre, int escudo, int vida);

    /*
    PRE: Elemento debe ser agua, aire tierra o fuego
    POS: Crea un personaje segun el elemento y nombre, el resto de los atributos son aleatorios manteniendose en sus cotas
    */
    void cargar_personaje_segun_elemento(string elemento, string nombre);

    /*
    PRE: Elemento debe ser agua, aire tierra o fuego
    POS: Agrega un nuevo personaje a la lista de personajes
    */
    void agregar_nuevo_personaje();

    /*
    Elimina el personaje del nombre ingresado por el usuario
    */
    void eliminar_personaje();

    /*
    Imprime por pantalla los nombres de los personajes de el diccionario
    */
    void mostrar_nombres_personajes();

    /*
    Muestra los detalles del personaje del cual el usuario solicita por nombre
     (si es que hay un personaje con dicho nombre en el diccionario)
    */
    void detalles_personaje();

    /*
    Apaga el menu, cortando con el ciclo y libera memoria
    */
    void salir();

    /*
    Imprime por pantalla el mensaje de bienvenida
    */
    void mensaje_bienvenida();


    /*
    Pide al usuario que ingrese un elemento (debe ser agua, aire, fuego o tierra) y lo devuelve
    */
    string pedir_elemento_personaje();

    /*
    Pide al usuario un nombre y lo devuelve
    */
    string pedir_nombre_personaje();

    /*
	 PRE: -
	 POS: Pide al usuario un nombre, si dicho nombre esta el en diccionario, agrega el
     personaje con dicha clave al vector de personajes del jugador del que sea el turno;
	 */
    void seleccionar_personaje();

    /*
	 PRE: -
	 POS: Devuelve el turno actual;
	 */
    int determinar_turno_seleccion();

    /*
	 PRE: Recibe un mensaje de tipo Text
	 POS: Imprime el mensaje en la ventana del menu;
	 */
    void imprimir_mensaje(Text mensaje);

};


#endif //MENUSFML_MENU_H
