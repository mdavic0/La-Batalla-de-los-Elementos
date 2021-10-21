#include "casillero.h"

Casillero::Casillero() {
    personaje = 0;
}

Casillero::~Casillero() {
}

bool Casillero::hay_personaje() {
    return personaje != 0;
}

Personaje* Casillero::obtener_personaje() {
    return personaje;
}

void Casillero::posicionar_personaje(Personaje* nuevo, Coordenada coordenada) {
    nuevo->asignar_coordenadas_pj(coordenada.obtener_primera(), coordenada.obtener_segunda());
    personaje = nuevo;
}

void Casillero::posicionar_personaje(Personaje *nuevo) {
    personaje = nuevo;
}

Sprite Casillero::obtener_sprite() {
    return spr_casillero;
}

void Casillero::asignar_posicion(float x, float y) {
    spr_casillero.setOrigin(spr_casillero.getGlobalBounds().width / 2, spr_casillero.getGlobalBounds().height / 2);
    spr_casillero.setPosition(x, y);
}

void Casillero::cargar_graficos() {
    string ruta = "../Graficos/" + tipo_casillero() + ".png";

    txt_casillero.loadFromFile(ruta);
    spr_casillero.setTexture(txt_casillero);
    spr_casillero.setScale((float)45 / spr_casillero.getTexture()->getSize().x , (float)45 / spr_casillero.getTexture()->getSize().y);
}

