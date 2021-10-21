#include "nodo_diccionario.h"
#include<iostream>

#ifndef DICCIONARIO_H
#define DICCIONARIO_H

class Diccionario
{
private:
    // atributos
    Nodo_diccionario* raiz;
    Nodo_diccionario* actual;

private:
    // metodos

    /*
     PRE: nodo, clave, valor son de tipos validos
     POS: da de alta el nodo en el diccionario
     */
    Nodo_diccionario* insertar(Nodo_diccionario* nodo, Clave clave, Valor valor);

    /*
     PRE: nodo es de tipo valido
     POS: imprime el diccionario inorden
     */
    void imprimir_inorden(Nodo_diccionario * nodo);

    /*
     PRE: nodo y clave son de tipo valido
     POS: busca el nodo en el diccionario
     */
    Nodo_diccionario* buscar(Nodo_diccionario* nodo, Clave clave);

    /*
     PRE: nodo es de tipo valido
     POS: elimina todos los elementos del diccionario
     */
    void eliminar_todos(Nodo_diccionario* nodo);

    /*
     PRE: -
     POS: pone actual en raiz
     */
    void reiniciar();


    /*
     PRE: r y v son de tipo valido
     POS: elimina el nodo del diccionario
     */
    Nodo_diccionario* _eliminar(Nodo_diccionario* r, Clave v);


public:
    // metodos

    /*
     PRE: -
     POS: crea un diccionrio (arbol) vacio
     */
    Diccionario();

    /*
     PRE: clave y valor son de tipo valido
     POS: agrega un nuevo nodo a diccionario. El nodo sera raiz si el arbol esta vacio.
     */
    void insertar(Clave clave, Valor valor);


    /*
     PRE: -
     POS: imprime los elementos del diccionario en inorden, de menor a mayor.
     */
    void imprimir_inorden();

    /*
     PRE: clave es de tipo valido
     POS: devuelve true si encuentra la clave en el diccionario, false de lo contrario.
     */
    bool buscar(Clave clave);

    // Finds the minimum value that exist in the Diccionario.
    //Clave buscar_min();

    /*
     PRE: -
     POS: devuelve la raiz
     */
    Nodo_diccionario* obtener_raiz();

    /*
    PRE: -
    POS: devuelve true si el diccionario esta vacio, false de lo contrario
    */
    bool vacio();

    /*
     PRE: -
     POS: elimina todos los nodos del diccionario
     */
    void eliminar_todos();

    /*
    PRE: clave es de tipo valido
    POS: devuelve el valor asociado a la clave pasada por parametro
    */
    Valor consulta(Clave clave);

    /*
     PRE: borrar es de tipo valido
     POS: elimina el nodo asociado a la clave pasada por parametro
     */
    void claves_inorden(Nodo_diccionario* aux, string &claves);

    /*
    PRE: nodo es de tipo valido
    POS: busca el minimo en el diccionario.
    */
    void eliminar(Clave borrar);

    /*
    PRE: nodo es de tipo valido
    POS: busca el sucesor en el diccionario.
    */
    Nodo_diccionario* minimo(Nodo_diccionario* nodo);

    /*
      PRE: nodo es de tipo valido
      POS: busca el sucesor en el diccionario.
      */
    Nodo_diccionario* buscar_sucesor(Nodo_diccionario* nodo);

    /*
     PRE: clave es de tipo valido
     POS: devuelve true si existe el nodo asociado a dicha clave en el diccionario, false de lo contrario.
     */
    bool esta(Clave clave);

    /*
     PRE: -
     POS: libera memoria
     */
    ~Diccionario(); // destructor
};
#endif //ABB_Diccionario_H