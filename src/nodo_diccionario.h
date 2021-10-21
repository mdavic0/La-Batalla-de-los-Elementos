#ifndef NODO_DICCIONARIO_H_INCLUDED
#define NODO_DICCIONARIO_H_INCLUDED

#include <string>
#include "personaje.h"

using namespace std;

typedef string Clave;
typedef Personaje* Valor;

class Nodo_diccionario
{
private:
    Clave clave;
    Valor valor;
    Nodo_diccionario* izq;
    Nodo_diccionario* der;
    //Nodo_diccionario* padre;

public:
    /*
     PRE: clave y valor son de tipo valido.
     POS: crea un Nodo_diccionario con clave y valor pasados por parametro.
     */
    Nodo_diccionario(Clave clave, Valor valor);

    /*
     PRE: -
     POS: devuelve la clave
     */
    Clave obtener_clave();

    /*
     PRE: -
     POS: devuelve el valor
     */
    Valor obtener_valor();

    /*
     PRE: nueva es de tipo Clave
     POS: asigna nueva a la clave del nodo.
     */
    void asignar_clave(Clave nueva);

    /*
     PRE: nuevo es de tipo Valor
     POS: asigna nuevo al valor del nodo.
     */
    void asignar_valor(Valor nuevo);

    /*
     PRE: izq es de tipo Nodo_diccionario*
     POS: asigna hijo izquierdo al nodo
     */
    void asignar_izq(Nodo_diccionario* izq);

    /*
     PRE: der es de tipo Nodo_diccionario*
     POS: asigna hijo derecho al nodo
     */
    void asignar_der(Nodo_diccionario* der);

    /*
     PRE: -
     POS: devuelve derecho
     */
    Nodo_diccionario* obtener_der();

    /*
    PRE: -
    POS: devuelve izquierdo
    */
    Nodo_diccionario* obtener_izq();

    /*
     PRE: -
     POS: devuelve true si el nodo es hoja, false de lo contrario
     */
    bool es_hoja();

    /*
     PRE: -
     POS: devuelve true si el nodo solo tiene hijo derecho, false de lo contrario.
     */
    bool solo_hijo_der();

    /*
     PRE: -
     POS: devuelve true si el nodo solo tiene hijo izquierdo, false de lo contrario.
     */
    bool solo_hijo_izq();

    /*
     PRE: -
     POS: libera memoria
     */
    ~Nodo_diccionario(); // destructor
};
#endif //Nodo_diccionario_Hif //Nodo_diccionario_H