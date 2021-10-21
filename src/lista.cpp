#include "lista.h"

Lista::Lista() {
    primero = 0;
    actual = primero;
    cantidad = 0;
    indice_actual = 0;
}

void Lista::reiniciar() {
    actual = primero;
    indice_actual = 0;
}

bool Lista::hay_siguiente() {
    return (actual != 0);
}

void Lista::siguiente() {
    if(hay_siguiente()) {
        actual = actual->obtener_siguiente();
        indice_actual++;
    }
}

Dato Lista::obtener_actual() {
    return actual->obtener_dato();
}

int Lista::obtener_indice_actual() {
    return indice_actual;
}

bool Lista::vacia() {
    return (cantidad == 0);
}

void Lista::alta(Dato d) {
    Nodo* nuevo = new Nodo(d);
    if(!primero) primero = nuevo;
    else {
        reiniciar();
        Nodo* aux = actual;
        while(aux->tiene_siguiente()) aux = aux->obtener_siguiente();
        aux->cambiar_siguiente(nuevo);
    }
    cantidad++;
}

void Lista::alta(Dato d, int pos) {
    Nodo* nuevo = new Nodo(d);
    if (pos == 0) {
        nuevo->cambiar_siguiente(primero);
        primero = nuevo;
        reiniciar();
    }
    else {
        Nodo* anterior = obtener_nodo(pos - 1);
        Nodo* siguiente = anterior->obtener_siguiente();
        nuevo->cambiar_siguiente(siguiente);
        anterior->cambiar_siguiente(nuevo);
    }
    cantidad++;
}

Nodo* Lista::obtener_nodo(int pos) {
    Nodo* aux = primero;
    for(int i = 0; i < pos; i++)
        aux = aux->obtener_siguiente();
    return aux;
}

Dato Lista::consulta(int pos) {
    Nodo* aux = obtener_nodo(pos);
    return aux->obtener_dato();
}

Dato Lista::baja_y_devuelve(int pos) {
    Nodo* borrar;
    Dato d;
    if (pos == 0) {
        borrar = primero;
        d = borrar->obtener_dato();
        primero = borrar->obtener_siguiente();
    }else{
        Nodo* anterior = obtener_nodo(pos - 1);
        borrar = anterior->obtener_siguiente();
        d = borrar->obtener_dato();
        Nodo* siguiente = borrar->obtener_siguiente();
        anterior->cambiar_siguiente(siguiente);
    }
    reiniciar();
    delete borrar;
    cantidad--;
    return d;
}

Dato Lista::baja_y_devuelve() {
    Nodo* borrar = actual;
    Dato d;
    if (indice_actual == 0) {
        d = borrar->obtener_dato();
        primero = borrar->obtener_siguiente();
        reiniciar();
    }else{
        Nodo* anterior = obtener_nodo(indice_actual-1);
        borrar = anterior->obtener_siguiente();
        d = borrar->obtener_dato();
        Nodo* siguiente = borrar->obtener_siguiente();
        anterior->cambiar_siguiente(siguiente);
    }
    reiniciar();
    delete borrar;
    cantidad--;
    return d;
}

/*Dato Lista::baja_y_devuelve(string nombre) {
    Dato eliminado;
    if (esta_en_la_lista(nombre)) {
        eliminado = baja_y_devuelve();
    } else {
        eliminado = nullptr;
    }
    return eliminado;
}*/

void Lista::baja(int pos) {
    Nodo* borrar;
    if (pos == 0) {
        borrar = primero;
        primero = borrar->obtener_siguiente();
    }else{
        Nodo* anterior = obtener_nodo(pos - 1);
        borrar = anterior->obtener_siguiente();
        Nodo* siguiente = borrar->obtener_siguiente();
        anterior->cambiar_siguiente(siguiente);
    }
    reiniciar();
    delete borrar;
    cantidad--;
}

Lista::~Lista()  {
    while (! vacia())
        baja(0);
}

int Lista::obtener_cantidad()  {
    return cantidad;
}

bool Lista::esta_en_la_lista(Dato d) {
    bool encontrado = false;
    reiniciar();
    while(hay_siguiente() && !encontrado) {
        if(obtener_actual() == d) encontrado = true;
        else siguiente();
    }
    return encontrado;
}


Dato Lista::consulta(Coordenada coord) {
    Dato vertice = nullptr;
    if(esta_en_la_lista(coord)) {
        vertice = obtener_actual();
    }
    return vertice;
}


bool Lista::esta_en_la_lista(Coordenada coord) {
    bool encontrado = false;
    reiniciar();
    while(hay_siguiente() && !encontrado) {
        if(obtener_actual()->obtener_coordenadas() == coord) encontrado = true;
        else {
            siguiente();
        }
    }
    return encontrado;
}
