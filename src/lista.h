#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include "coordenada.h"
#include "nodo.h"
#include "vertice.h"

class Lista {
private:
    // Atributos
    Nodo* primero;
    Nodo* actual;
    int cantidad;
    int indice_actual = 1;

public:
    /*
    Constructor:
    Crea una lista vacia
    */
    Lista();

    /*
    PRE: 0 < pos <= cantidad + 1
    POS: Inserta el dato d en la posicion pos, la 1 es la primera
         Ademas incrementa cantidad en 1
    */
    void alta(Dato d, int pos);

    /*
    Inserta el dato d al final de la lista, luego incrementa cantidad en 1
    */
    void alta(Dato d);

    /*
    PRE: 0 < pos <= cantidad
    POS: saca el elemento que esta en pos
    */
    void baja(int pos);

    /*
    PRE: 0 < pos <= cantidad
    POS: Saca el elemento que esta en pos y lo devuelve
    */
    Dato baja_y_devuelve(int pos);

    /*
    Saca el elemento que esta en la posicion actual y lo devuelve
    */
    Dato baja_y_devuelve();

    /*
    Si el personaje con el nombre recibido esta en la lista, lo baja y lo devuelve
    Caso contrario devuelve nullptr
    */
    Dato baja_y_devuelve(string nombre);
    /*
     PRE: -
     POS: Devuelve el elemento que tiene coordeanda coord
     */
    Dato consulta(Coordenada coord);

    /*
    PRE: 0 < pos <= cantidad
    POS: Devuelve el elemento que esta en pos
    */
    Dato consulta(int pos);

    /*
    Devuelve el personaje con el nombre recibido por parametro
    Si este no esta en la lista, devuelve nullptr
    */
    Dato consulta(string nombre);

    /*
     PRE: -
     POS: Devuelve true si encuentra la coordenada coord en la lista, false de lo contrario
     */
    bool esta_en_la_lista(Coordenada coord);

    /*
    Devuelve true si la lista esta vacia, false en caso contrario
    */
    bool vacia();

    /*
    Libera memoria
    */
    virtual ~Lista();

    /*
    Devuelve la cantidad de elementos en la lista
    */
    int obtener_cantidad();

    /*
    Reinicia la posicion actual de la lista (vuelve al principio)
    */
    void reiniciar();

    /*
    Devuelve true si hay un elemento despues del actual, false en caso contrario
    */
    bool hay_siguiente();

    /*
    PRE: hay_siguiente()
    POS: avanza la posicion actual a la siguiente
    */
    void siguiente();

    /*
    Devuelve el dato que esta en la posicion actual
    */
    Dato obtener_actual();

    /*
    Devuelve el indice de la posicion actual
    */
    int obtener_indice_actual();

    /*
    Devuelve true si el dato esta en la lista, falso en caso contrario.
    Si el dato esta en la lista, el actual apuntara al mismo
    */
    bool esta_en_la_lista(Dato d);

    /*
    Devuelve true si hay un personaje con el nombre ingresado, falso en caso contrario.
    Si el personaje esta en la lista, el actual apuntara al mismo
    */
    bool esta_en_la_lista(string nombre);

private:
    /*
    PRE: 0 < pos <= cantidad
    POS: devuelve el nodo de la posicion pos
    */
    Nodo* obtener_nodo(int pos);
};


#endif // LISTA_H_INCLUDED
