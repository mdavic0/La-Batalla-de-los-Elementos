#include "personaje.h"

Personaje::Personaje(string nombre, int escudo, int vidas) {
    this->nombre = nombre;
    this->escudo = escudo;
    this->vidas = vidas;
    srand(vidas * energia * (int)nombre[0] * (int)nombre[nombre.length() - 1] * time(nullptr));
    this->energia = rand() % (VALOR_MAX_ENERGIA - VALOR_MIN_ENERGIA + 1) + VALOR_MIN_ENERGIA;
    this->id_jugador = NO_ELEGIDO;
}

Personaje::Personaje(string nombre) {
    this->nombre = nombre;
    srand(vidas * energia * (int)nombre[0] * (int)nombre[nombre.length() - 1] * time(nullptr));
    this->escudo = rand() % (VALOR_MAX_ESCUDO - VALOR_MIN_ESCUDO + 1) + VALOR_MIN_ESCUDO;
    this->vidas = rand() % (VALOR_MAX_VIDA - VALOR_MIN_VIDA + 1) + VALOR_MIN_VIDA;
    this->energia = rand() % (VALOR_MAX_ENERGIA - VALOR_MIN_ENERGIA + 1) + VALOR_MIN_ENERGIA;
    this->id_jugador = NO_ELEGIDO;
}

Personaje::Personaje(string nombre, int escudo, int vidas, int energia, int fila, int columna, int id_jugador) {
    this->nombre = nombre;
    this->escudo = escudo;
    this->vidas = vidas;
    this->energia = energia;
    this->coord_personaje = Coordenada(fila, columna);
    this->id_jugador = id_jugador;
}

Personaje::Personaje(string nombre, int escudo, int vidas, int energia, int fila, int columna, int id_jugador, bool se_defiende) {
    this->nombre = nombre;
    this->escudo = escudo;
    this->vidas = vidas;
    this->energia = energia;
    this->coord_personaje = Coordenada(fila, columna);
    this->id_jugador = id_jugador;
    this->se_defiende = se_defiende;
}

Personaje::~Personaje() {
}

void Personaje::asignar_coordenadas_pj(int fila, int columna) {
    coord_personaje = Coordenada(fila, columna);
    spr_personaje.setPosition(200.f + 20.f + (columna * 50.f), 170.f + (fila * 50.f));
    spr_personaje.setScale((float)65 / spr_personaje.getTexture()->getSize().x , (float)65 / spr_personaje.getTexture()->getSize().y);
}

void Personaje::elegir(int id_jugador) {
    this->id_jugador = id_jugador;
}

string Personaje::nombre_personaje() {
    return nombre;
}

bool Personaje::obtener_se_defiende() {
    return se_defiende;
}

string Personaje::detalles_personaje() {
   string detalles = "Nombre: " + nombre + '\n' +
           "Elemento: " + de_que_elemento_soy() + '\n' +
           "Escudo: " + to_string(escudo) + '\n' +
           "Vidas: " + to_string(vidas) + '\n' +
           "Energia: " + to_string(energia) + '\n' +
           "Posicion: (" + to_string(coord_personaje.obtener_primera()) + ", "  + to_string(coord_personaje.obtener_segunda()) + ")\n";

    return detalles;
}

bool Personaje::esta_vivo() {
    return vidas > 0;
}

void Personaje::restar_energia(int costo_energia) {
    energia -= costo_energia;
    if (energia < 0) energia = 0;
}

int Personaje::aplicar_escudo(int danio_recibido) {
    if (VALOR_MIN_ESCUDO < escudo < VALOR_MAX_ESCUDO) danio_recibido -= danio_recibido*0.1;
    else if (escudo == VALOR_MAX_ESCUDO) danio_recibido -= danio_recibido*0.2;
    else if (escudo > VALOR_MAX_ESCUDO) danio_recibido -= danio_recibido*0.8;
    return danio_recibido;
}

void Personaje::mover(int fila, int columna, int energia_minima) {
    if(energia >= energia_minima) {
        coord_personaje.cambiar_primera(fila);
        coord_personaje.cambiar_segunda(columna);
        energia -= energia_minima;
        if (energia < 0) energia = 0;
    } else cout << ENERGIA_INSUFICIENTE << endl;
}

int Personaje::obtener_id_jugador() {
    return id_jugador;
}

int Personaje::obtener_energia(){
    return energia;
}

int Personaje::obtener_vida(){
    return vidas;
}

int Personaje::obtener_escudo(){
    return escudo;
}

Sprite Personaje::obtener_sprite() {
    return spr_personaje;
}

void Personaje::cargar_graficos() {

    int numero_personaje = numero_aleatorio();

    string ruta = "../Graficos/Personaje_de_" + de_que_elemento_soy() + to_string(numero_personaje) + ".png";

    txt_personaje.loadFromFile(ruta);
    spr_personaje.setTexture(txt_personaje);
    spr_personaje.setOrigin(spr_personaje.getGlobalBounds().width / 2, spr_personaje.getGlobalBounds().height / 2);
}

int Personaje::numero_aleatorio() {
    srand(vidas * energia * (int)nombre[0] * (int)nombre[nombre.length() - 1] * time(nullptr));
    return rand() % 3 + 1;
}

Coordenada Personaje::obtener_coordenadas(){
    return coord_personaje;
}

void Personaje::curar(int curar){
    this->vidas = this->vidas + curar;
    if(this->vidas > 100) this->vidas = 100;
}

void Personaje::cambiar_turno() {
    if(de_que_elemento_soy() == ELEMENTO_AIRE){
        energia += ENERGIA_RECUPERADA_P_AIRE;
        if (energia > VALOR_MAX_ENERGIA) energia = VALOR_MAX_ENERGIA;
    }
}

