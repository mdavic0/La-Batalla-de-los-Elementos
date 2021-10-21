# include "vector.h"

Vector::Vector(int l){
    largo = l;
    datos = new Dato_vec[l]; // pido memoria para el vector, de longitud l
    // puntero, esta fuera del objeto. El objeto de tipo vector me va a
    // ocupar 4+8 = 12, y donde esten los datos me ocupara l*sizeof(Dato)
    anular(0,l-1);
}

void Vector::asignar(Dato_vec d, int pos){
    datos[pos] = d;
}

Dato_vec Vector::baja(int pos) {
    Dato_vec eliminar = obtener(pos);
    anular(pos,pos);
    redimensionar(largo-1);
    return eliminar;
}

Dato_vec Vector::obtener(int pos){
    return datos[pos];
}

int Vector::obtener_longitud(){
    return largo;
}

Vector::~Vector(){
    while(largo > 0) {
        Dato_vec borrar = baja(obtener_longitud());
        delete borrar;
    }
    delete [] datos;
}

void Vector::anular(int desde, int hasta){
    for (int i = desde; i <= hasta; i++){
        datos[i] = NULL;
    }
}

int menor(int a, int b){
    if (a < b){
        return a;
    }
    return b;
}
void Vector::redimensionar(int nl){
    int minimo = menor(largo,nl);
    Dato_vec* viejo = datos;
    datos = new Dato_vec[nl];
    copiar(viejo,0,minimo - 1);
    if (nl > largo){
        anular(minimo,nl-1);
    }
    if (largo > 0){
        delete [] viejo;
    }
    largo = nl;
}

void Vector::copiar(Dato_vec* vec, int d, int h){
    for (int i = d; i <= h; i++){
        datos[i] = vec[i];
    }
}

Vector::Vector(const Vector &v) {
    largo = v.largo;
    if (largo > 0){
        datos = new Dato_vec[largo];
        copiar(v.datos,0,largo-1);
    } else{
        datos = 0;
    }
}
