#include "diccionario.h"
#include "nodo_diccionario.h"
using namespace std;


Diccionario::Diccionario() {
    this->raiz = 0;
    this->actual = raiz;
}


Nodo_diccionario* Diccionario::insertar(Nodo_diccionario* nodo, Clave clave, Valor valor) {

    if (nodo == NULL) {
        nodo = new Nodo_diccionario(clave, valor);
    }

    else if (clave > nodo->obtener_clave()) {
        nodo->asignar_der(insertar(nodo->obtener_der(), clave, valor));
    }

    else {
        nodo->asignar_izq(insertar(nodo->obtener_izq(), clave, valor));
    }
    return nodo;
}


void Diccionario::insertar(Clave clave, Valor valor)
{
    this->raiz = insertar(this->raiz, clave, valor);
}


void Diccionario::imprimir_inorden(Nodo_diccionario* nodo)
{
    if (nodo != NULL)
    {
        imprimir_inorden(nodo->obtener_izq());
        cout << nodo->obtener_clave() << ' ';
        imprimir_inorden(nodo->obtener_der());
    }
}


void Diccionario::imprimir_inorden()
{
    if (raiz)
        this->imprimir_inorden(this->raiz);
}


Nodo_diccionario* Diccionario::buscar(Nodo_diccionario* nodo, Clave clave)
{
    if(!nodo) return nodo;

    if (nodo->obtener_clave() == clave) {
        actual = nodo;
        return nodo;
    }

    if (clave > nodo->obtener_clave())
        return buscar(nodo->obtener_der(), clave);
    return buscar(nodo->obtener_izq(), clave);
}


bool Diccionario::buscar(Clave clave)
{
    reiniciar();
    Nodo_diccionario* resultado = buscar(this->raiz, clave);

    return resultado != NULL;
}

void Diccionario::reiniciar() {
    actual = raiz;
}

Valor Diccionario::consulta(Clave clave) {
    reiniciar();
    if(buscar(clave)) return actual->obtener_valor();
    return 0;
}

Nodo_diccionario* Diccionario::obtener_raiz(){
    return this->raiz;
}


bool Diccionario::vacio()
{
    return this->raiz == NULL;
}


void Diccionario::eliminar_todos(Nodo_diccionario* nodo)
{
    if (nodo==NULL)
        return;

    this->eliminar_todos(nodo->obtener_izq());
    this->eliminar_todos(nodo->obtener_der());
    delete nodo;
}


void Diccionario::eliminar_todos()
{
    this->eliminar_todos(this->raiz);
}

Diccionario::~Diccionario()
{
    this->eliminar_todos();
}

Nodo_diccionario* Diccionario::buscar_sucesor(Nodo_diccionario* nodo)
{
    if (nodo->obtener_der() != NULL)
    {
        return minimo(nodo->obtener_der());
    }
    Nodo_diccionario* sucesor = NULL;
    Nodo_diccionario* ancestro = this->raiz;
    while(ancestro != nodo) {
        if(nodo->obtener_clave() < ancestro->obtener_clave()) {
            sucesor = ancestro;
            ancestro = ancestro->obtener_izq();
        }
        else
            ancestro = ancestro->obtener_der();
    }
    return sucesor;
}


void Diccionario::eliminar(Clave borrar) { // te devuelve la wea que bajas, como una consulta que ademas de consultar por clave te baja el coso xd
    if(esta(borrar)) this->raiz = _eliminar(this->raiz, borrar);
}

Nodo_diccionario* Diccionario::_eliminar(Nodo_diccionario* r, Clave v)
{
    if(!r) return 0;
    else if(v < r->obtener_clave()) r->asignar_izq(_eliminar(r->obtener_izq(), v));
    else if(v > r->obtener_clave()) r->asignar_der(_eliminar(r->obtener_der(), v));
    else {
        if(!r->obtener_izq()) {
            Nodo_diccionario* temp = r->obtener_der();
            delete r;
            return temp;
        } else if(!r->obtener_der()) {
            Nodo_diccionario* temp = r->obtener_izq();
            delete r;
            return temp;
        } else {
            Nodo_diccionario* temp = minimo(r->obtener_der());
            r->asignar_clave(temp->obtener_clave());
            r->asignar_valor(temp->obtener_valor());
            r->asignar_der(_eliminar(r->obtener_der(), temp->obtener_clave()));
        }
    }
    return r;
}

Nodo_diccionario* Diccionario::minimo(Nodo_diccionario* nodo)
{
    Nodo_diccionario* act = nodo;
    while(act->obtener_izq()) act = act->obtener_izq();
    return act;
}

bool Diccionario::esta(Clave clave) {
    if(buscar(clave)) return true;
    return false;
}


void Diccionario::claves_inorden(Nodo_diccionario* aux, string &claves) {
    // recorrido inorden: subarbol izquierdo - raiz - subarbol derecho
    if (aux != nullptr) { // caso base: raiz = 0, subarbol vacio, corta la recursividad
        claves_inorden(aux->obtener_izq(), claves);

        claves += aux->obtener_clave() + '\n';

        claves_inorden(aux->obtener_der(), claves);
    }
}