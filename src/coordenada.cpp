#include "coordenada.h"

Coordenada::Coordenada(int primera, int segunda) {
    this->primera = primera;
    this->segunda = segunda;
}

/*Coordenada::Coordenada(const Coordenada& c) {
    *this = c;
}*/

Coordenada Coordenada::operator+(Coordenada c) {
    this->primera += c.primera;
    this->segunda += c.segunda;
    return *this;
}

Coordenada Coordenada::operator=(Coordenada c) {
    if(this != &c) {
        if(c.primera != 0) this->primera = c.primera;
        if(c.segunda != 0) this->segunda = c.segunda;
    }
    return *this;
}

bool Coordenada::operator==(Coordenada c) {
    return this->primera == c.primera && this->segunda == c.segunda;
}

int Coordenada::obtener_primera() {
    return this->primera;
}

int Coordenada::obtener_segunda() {
    return this->segunda;
}

void Coordenada::cambiar_primera(int nueva) {
    this->primera = nueva;
}

void Coordenada::cambiar_segunda(int nueva) {
    this->segunda = nueva;
}