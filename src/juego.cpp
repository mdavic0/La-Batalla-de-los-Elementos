#include "juego.h"

Juego::Juego(){
    tablero = new Grafo(ARCHIVO_MAPA);

    Jugador* j1 = new Jugador();
    Jugador* j2 = new Jugador();

    jugadores[JUGADOR_1] = j1;
    jugadores[JUGADOR_2] = j2; // a chequear jaja malisimo bro que hacia
    pos_personaje = 0;
    determinar_primer_turno();
    termino = false;
    opcion_seleccionada = 0;
    esta_activo_menu_juego = true;
    esta_activo_sub_menu_juego = false;
}


bool Juego::comenzo() {
    return obtener_jugador(JUGADOR_1)->eligio_max_personajes() && obtener_jugador(JUGADOR_2)->eligio_max_personajes();
}


void Juego::jugar() {
    ventana_juego = new RenderWindow(VideoMode(800, 600, 32), TITULO);
    ventana_juego->setMouseCursorVisible(false);
    ventana_juego->setVerticalSyncEnabled(true);
    ventana_juego->setFramerateLimit(60);

    cargar_graficos();

    if(!partida_cargada) posicionar_personajes();

    while(!termino){

        interfaz_menu_juego();

    }
}


Jugador* Juego::obtener_jugador(int jugador) {
    if(jugador == JUGADOR_1 || jugador == JUGADOR_2) return jugadores[jugador];
    return nullptr;
}


Grafo * Juego::obtener_grafo() {
    return tablero;
}


Juego::~Juego() {
    if (tablero) delete tablero;
}


void Juego::determinar_primer_turno() {
    srand(time(nullptr));
    turno = rand() % 1 + 0;
}


int Juego::turnar() {
    if (turno % 2 == 0) return JUGADOR_1;
    return JUGADOR_2;
}


void Juego::chequear_subturno() {
    int turno_act = turnar();
    Jugador* jugador_act = jugadores[turno_act];

    if(pos_personaje >= jugador_act->obtener_cantidad_personajes()) {
        pos_personaje = 0;
        
        turno++;
    }
}


void Juego::posicionar_personajes() {
    Text mensaje;
    mensaje.setFont(fuente);

    int personajes_posicionados = 0;

    while(!termino && personajes_posicionados < 6){
        Coordenada coordenada = coordenada_valida_moverse();

        tablero->obtener_vertices()->consulta(coordenada)->obtener_casillero()->posicionar_personaje(jugadores[turnar()]->obtener_personaje(pos_personaje), coordenada);

        turno++;

        if(personajes_posicionados % 2 != 0) pos_personaje++;

        chequear_subturno();

        personajes_posicionados++;
    }

}

void Juego::alimentar() {
    Text mensaje;
    mensaje.setFont(fuente);

    int turno_act = turnar();
    Jugador* jugador_act = jugadores[turno_act];
    Personaje * personaje_act = jugador_act->obtener_personaje(pos_personaje);
    if (personaje_act->obtener_vida() > 0) {


        mensaje.setString(personaje_act->alimentar());

        if (personaje_act->alcanzo_max_alimento() || personaje_act->de_que_elemento_soy() == ELEMENTO_AIRE) {
            imprimir_mensaje(mensaje);
        } else {
            imprimir_mensaje(mensaje);

            opciones_menu_juego[opcion_seleccionada].setFillColor(Color::White);
            opciones_menu_juego[0].setFillColor(Color::Yellow);
            interfaz_sub_menu_juego();
        }
    }else {
        mensaje.setString("El personaje esta muerto!");
        imprimir_mensaje(mensaje);
    }
}

void Juego::atacar() {
    Text mensaje;
    mensaje.setFont(fuente);

    int turno_act = turnar();
    Jugador* jugador_act = jugadores[turno_act];
    Personaje * personaje_act = jugador_act->obtener_personaje(pos_personaje);
    Coordenada coord_act = personaje_act->obtener_coordenadas();

    if(personaje_act->obtener_vida() > 0) {

        if (personaje_act->obtener_energia() >= MIN_ENERGIA_ATAQUE) {
            if (personaje_act->de_que_elemento_soy() == ELEMENTO_AGUA) {
                if (personaje_act->obtener_energia() >= MIN_ENERGIA_ATAQUE_AGUA) {
                    Coordenada nueva = coordenada_valida_atacar();
                    if (tablero->acceder_tablero(
                            nueva)->obtener_casillero()->obtener_personaje()->obtener_id_jugador() !=
                        personaje_act->obtener_id_jugador()) {
                        ataque_p_agua(nueva);
                    } else {
                        mensaje.setString("El ataque a un aliado no esta permitido!");
                        imprimir_mensaje(mensaje);
                        //cout << "El ataque a un aliado no esta permitido!" << endl;
                        return;
                    }
                }
            } else if (personaje_act->de_que_elemento_soy() == ELEMENTO_TIERRA) {
                if (personaje_act->obtener_energia() >= MIN_ENERGIA_ATAQUE_TIERRA) {
                    Coordenada nueva = coordenada_valida_atacar();
                    if (tablero->acceder_tablero(
                            nueva)->obtener_casillero()->obtener_personaje()->obtener_id_jugador() !=
                        personaje_act->obtener_id_jugador()) {
                        ataque_p_tierra(coord_act, nueva);
                    } else {
                        mensaje.setString("El ataque a un aliado no esta permitido!");
                        imprimir_mensaje(mensaje);
                        //cout << "El ataque a un aliado no esta permitido!" << endl;
                        return;
                    }
                }
            } else if (personaje_act->de_que_elemento_soy() == ELEMENTO_FUEGO) {
                if (personaje_act->obtener_energia() >= MIN_ENERGIA_ATAQUE_FUEGO) {
                    ataque_p_fuego(coord_act);
                }
            } else {
                if (personaje_act->obtener_energia() >= MIN_ENERGIA_ATAQUE_AIRE) {
                    ataque_p_aire();
                }else {
                     mensaje.setString(ENERGIA_INSUFICIENTE + "\nEnergia actual: " + to_string(personaje_act->obtener_energia()) + ", Energia necesaria: " + to_string(personaje_act->obtener_energia_minima_ataque()));
                    imprimir_mensaje(mensaje);
                    return;
                }
            }

            opciones_sub_menu_juego[opcion_seleccionada].setFillColor(Color::White);
            opciones_sub_menu_juego[0].setFillColor(Color::Yellow);

            personaje_act->restar_energia(personaje_act->obtener_energia_minima_ataque());
            jugadores[turnar()]->obtener_personaje(pos_personaje)->cambiar_turno();

            pos_personaje++;
            chequear_subturno();

            if (obtener_jugador(JUGADOR_1)->jugador_perdio() || obtener_jugador(JUGADOR_2)->jugador_perdio()) {
                fin_del_juego();
            } else if (pos_personaje == 0) {
                interfaz_guardar_salir();
            } else {
                interfaz_menu_juego();
            }

        } else {
            mensaje.setString(ENERGIA_INSUFICIENTE + "\nEnergia actual: " + to_string(personaje_act->obtener_energia()) + ", Energia necesaria: " + to_string(personaje_act->obtener_energia_minima_ataque()));
            imprimir_mensaje(mensaje);
            //cout << ENERGIA_INSUFICIENTE << "\nEnergia actual: " << personaje_act->obtener_energia() << ", Energia necesaria: " << personaje_act->obtener_energia_minima_ataque() << endl;
        }
    } else {
        mensaje.setString("El personaje esta muerto!");
        imprimir_mensaje(mensaje);
    }
}

void Juego::ataque_p_tierra(Coordenada coord_act, Coordenada enemigo) {
    int distancia;
    int danio;
    if(tablero->acceder_tablero(enemigo)->obtener_casillero()->hay_personaje()) {
        distancia = tablero->costo_camino_minimo(tablero->acceder_tablero(coord_act), tablero->acceder_tablero(enemigo));
        if(distancia <= 2) danio = ATAQUE_BASE_TIERRA_FUERTE;
        else if(2 < distancia && distancia <= 4) danio = ATAQUE_BASE_TIERRA_MEDIO;
        else danio = ATAQUE_BASE_TIERRA_DEBIL;
        tablero->acceder_tablero(enemigo)->obtener_casillero()->obtener_personaje()->recibe_ataque(ELEMENTO_TIERRA, danio);
    }
}

void Juego::ataque_p_fuego(Coordenada coord_act) {
    if(turnar() == JUGADOR_1) {
        for(int i = 0; i < jugadores[JUGADOR_2]->obtener_cantidad_personajes(); i++) {
            Personaje* enemigo = jugadores[JUGADOR_2]->obtener_personaje(i);
            if(coord_act.obtener_primera() == enemigo->obtener_coordenadas().obtener_primera() || coord_act.obtener_primera() + 1 == enemigo->obtener_coordenadas().obtener_primera() || coord_act.obtener_primera() - 1 == enemigo->obtener_coordenadas().obtener_primera()) {
                enemigo->recibe_ataque(ELEMENTO_FUEGO, ATAQUE_BASE_FUEGO);
            }
        }
    } else {
        for(int i = 0; i < jugadores[JUGADOR_1]->obtener_cantidad_personajes(); i++) {
            Personaje* enemigo = jugadores[JUGADOR_1]->obtener_personaje(i);
            if(coord_act.obtener_primera() == enemigo->obtener_coordenadas().obtener_primera() || coord_act.obtener_primera() + 1 == enemigo->obtener_coordenadas().obtener_primera() || coord_act.obtener_primera() - 1 == enemigo->obtener_coordenadas().obtener_primera()) {
                enemigo->recibe_ataque(ELEMENTO_FUEGO, ATAQUE_BASE_FUEGO);
            }
        }
    }
}

void Juego::ataque_p_agua(Coordenada enemigo) {
    if(tablero->acceder_tablero(enemigo)->obtener_casillero()->obtener_personaje()) {
        tablero->acceder_tablero(enemigo)->obtener_casillero()->obtener_personaje()->recibe_ataque(ELEMENTO_AGUA, ATAQUE_BASE_AGUA);
    }
}

void Juego::ataque_p_aire() {
    if(turnar() == JUGADOR_1) {
        for(int i = 0; i < jugadores[JUGADOR_2]->obtener_cantidad_personajes(); i++) {
            jugadores[JUGADOR_2]->obtener_personaje(i)->recibe_ataque(ELEMENTO_AIRE, ATAQUE_BASE_AIRE);
        }
    } else {
        for(int i = 0; i < jugadores[JUGADOR_1]->obtener_cantidad_personajes(); i++) {
            jugadores[JUGADOR_1]->obtener_personaje(i)->recibe_ataque(ELEMENTO_AIRE, ATAQUE_BASE_AIRE);
        }
    }
}

void Juego::defenderse() {
    Text mensaje;
    mensaje.setFont(fuente);

    int turno_act = turnar();
    Jugador *jugador_act = jugadores[turno_act];
    Personaje *personaje_act = jugador_act->obtener_personaje(pos_personaje);

    if(personaje_act->obtener_vida() > 0) {

        if (personaje_act->de_que_elemento_soy() == ELEMENTO_AGUA) defensa_p_agua(personaje_act);
        else if (personaje_act->de_que_elemento_soy() == ELEMENTO_AIRE) defensa_p_aire(personaje_act);
        else if (personaje_act->de_que_elemento_soy() == ELEMENTO_FUEGO) personaje_act->defender();
        else defensa_p_tierra(personaje_act);

        if (personaje_act->obtener_se_defiende()) {
            opciones_sub_menu_juego[opcion_seleccionada].setFillColor(Color::White);
            opciones_sub_menu_juego[0].setFillColor(Color::Yellow);

            jugadores[turnar()]->obtener_personaje(pos_personaje)->cambiar_turno();

            pos_personaje++;
            chequear_subturno();

            if (pos_personaje == 0) {
                interfaz_guardar_salir();
            } else {
                interfaz_menu_juego();
            }

        } else {
            mensaje.setString(
                    ENERGIA_INSUFICIENTE + "\nEnergia actual: " + to_string(personaje_act->obtener_energia()) +
                    ", Energia necesaria: " + to_string(personaje_act->obtener_energia_minima_defensa()));
            imprimir_mensaje(mensaje);
            //cout << ENERGIA_INSUFICIENTE << "\nEnergia actual: " << personaje_act->obtener_energia()<< ", Energia necesaria: " << personaje_act->obtener_energia_minima_defensa() << endl;
        }
    } else{
        mensaje.setString("El personaje esta muerto!");
        imprimir_mensaje(mensaje);
    }
}

void Juego::defensa_p_agua(Personaje* pj) {
    pj->defender();
    if(pj->obtener_se_defiende()){
        int id_jugador = pj->obtener_id_jugador();
        Jugador* jugador_act = jugadores[id_jugador];
        int n_personajes = jugador_act->obtener_cantidad_personajes();
        for(int i = 0; i < n_personajes; i++) {
            Personaje * personaje_a_curar = jugador_act->obtener_personaje(i);
            if (personaje_a_curar != nullptr && personaje_a_curar->esta_vivo() && personaje_a_curar != pj) personaje_a_curar->curar(10);
        }
    }
}

void Juego::defensa_p_aire(Personaje* pj) {
    pj->defender();
    if(pj->obtener_se_defiende()){
        Coordenada nueva = coordenada_valida_moverse();
        if(!tablero->acceder_tablero(nueva)->obtener_casillero()->obtener_personaje()) {
            tablero->acceder_tablero(pj->obtener_coordenadas())->obtener_casillero()->posicionar_personaje(nullptr);
            tablero->acceder_tablero(pj->obtener_coordenadas())->obtener_casillero()->posicionar_personaje(pj, nueva);
        }
    }
}

void Juego::defensa_p_tierra(Personaje* pj) {
    pj->defender();
}

void Juego::moverse() {
    Text mensaje;
    mensaje.setFont(fuente);

    int turno_act = turnar();
    Jugador* jugador_act = jugadores[turno_act];
    Personaje* personaje_act = jugador_act->obtener_personaje(pos_personaje);
    Coordenada coord_act = personaje_act->obtener_coordenadas();
    Vertice* vertice_actual = tablero->acceder_tablero(coord_act);

    Coordenada nueva = coordenada_valida_moverse();

    int energia_minima = tablero->costo_camino_minimo(tablero->acceder_tablero(coord_act), tablero->acceder_tablero(nueva));

    if(personaje_act->obtener_vida() > 0) {
        if (personaje_act->obtener_energia() >= energia_minima) {
            if (!tablero->acceder_tablero(nueva)->obtener_casillero()->obtener_personaje()) {
                int nodo_inicial = 8 * coord_act.obtener_primera() + coord_act.obtener_segunda();
                int nodo_final = 8 * nueva.obtener_primera() + nueva.obtener_segunda();
                string elemento = personaje_act->de_que_elemento_soy();
                string camino_minimo = tablero->camino_minimo(nodo_inicial, nodo_final, elemento);

                personaje_act->mover(nueva.obtener_primera(), nueva.obtener_segunda(), energia_minima);
                vertice_actual->obtener_casillero()->posicionar_personaje(nullptr);
                tablero->acceder_tablero(nueva)->obtener_casillero()->posicionar_personaje(personaje_act, nueva);

                mensaje.setString("Camino minimo para ir desde (" + to_string(coord_act.obtener_primera()) + ", " +
                                  to_string(coord_act.obtener_segunda()) + ") hasta (" +
                                  to_string(nueva.obtener_primera()) + ", " + to_string(nueva.obtener_segunda()) +
                                  ") :\n" + camino_minimo);
                imprimir_mensaje(mensaje);

                mensaje.setString(
                        "Moverse le costo: " + to_string(energia_minima) + " puntos de energia al personaje: " +
                        personaje_act->nombre_personaje());
                imprimir_mensaje(mensaje);

                mensaje.setString("Energia actual: " + to_string(personaje_act->obtener_energia()));
                imprimir_mensaje(mensaje);

                cout << "Camino minimo para ir desde (" << coord_act.obtener_primera() << ", "
                     << coord_act.obtener_segunda() << ") hasta (" << nueva.obtener_primera() << ", "
                     << nueva.obtener_segunda() << ") :\n" << camino_minimo << endl;
                cout << "Moverse le costo: " << energia_minima << " puntos de energia al personaje: "
                     << personaje_act->nombre_personaje() << endl;
                cout << "Energia actual: " << personaje_act->obtener_energia() << endl;

                opciones_menu_juego[opcion_seleccionada].setFillColor(Color::White);
                opciones_menu_juego[0].setFillColor(Color::Yellow);
                interfaz_sub_menu_juego();
            } else {
                mensaje.setString("Ya hay un personaje en ese casillero ");
                imprimir_mensaje(mensaje);
                //cout << "Ya hay un personaje en ese casillero " << endl;
            }
        } else {
            mensaje.setString("El personaje no tiene suficiente energia para moverse:\nEnergia actual: " +
                              to_string(personaje_act->obtener_energia()) + ", Energia necesaria: " +
                              to_string(energia_minima));
            imprimir_mensaje(mensaje);
            //cout << "El personaje no tiene suficiente energia para moverse:\nEnergia actual: " << personaje_act->obtener_energia() << ", Energia necesaria: " << energia_minima << endl;
        }
    } else {
        mensaje.setString("El personaje esta muerto!");
        imprimir_mensaje(mensaje);
    };
}

void Juego::pasar_opcion() {

    if(esta_activo_menu_juego){
        opciones_menu_juego[opcion_seleccionada].setFillColor(Color::White);
        opciones_menu_juego[0].setFillColor(Color::Yellow);
        interfaz_sub_menu_juego();
    }

    if(esta_activo_sub_menu_juego){
        opciones_sub_menu_juego[opcion_seleccionada].setFillColor(Color::White);
        opciones_sub_menu_juego[0].setFillColor(Color::Yellow);

        jugadores[turnar()]->obtener_personaje(pos_personaje)->cambiar_turno();

        pos_personaje++;
        chequear_subturno();

        if(pos_personaje == 0){

            interfaz_guardar_salir();
        }else{
            interfaz_menu_juego();
        }

    }
}

void Juego::cargar_graficos() {
    fuente.loadFromFile("../Graficos/Daily Hours.ttf");

    txt_fondo.loadFromFile("../Graficos/fondo.jpeg");
    spr_fondo.setTexture(txt_fondo);
    spr_fondo.setScale((float)ventana_juego->getSize().x / spr_fondo.getTexture()->getSize().x , (float)ventana_juego->getSize().y / spr_fondo.getTexture()->getSize().y);
    Color color_fondo(255, 255, 255, 30); //(semi transparente);
    spr_fondo.setColor(color_fondo);

    cargar_graficos_detalles_personajes();

    titulo.setFont(fuente);
    titulo.setFillColor(Color::White);
    titulo.setString(TITULO);
    titulo.setCharacterSize(60);
    titulo.setPosition(sf::Vector2f(ventana_juego->getSize().x / 2.0  , 5.0));
    titulo.setOrigin(titulo.getGlobalBounds().width / 2, titulo.getGlobalBounds().height / 2);

    for (int i = 0; i < MAX_PERSONAJES; i++){
        spr_personajes_jugador_1[i] = jugadores[JUGADOR_1]->obtener_personaje(i)->obtener_sprite();
        spr_personajes_jugador_1[i].setScale(80.f / spr_personajes_jugador_1[i].getTexture()->getSize().x , 80.f / spr_personajes_jugador_1[i].getTexture()->getSize().y);
        spr_personajes_jugador_1[i].setPosition(detalles_personajes_jugador_1.getGlobalBounds().width + spr_personajes_jugador_1[i].getGlobalBounds().width / 1.5, ventana_juego->getSize().y / 2.3 + (float)(135 * i));

        spr_personajes_jugador_2[i] = jugadores[JUGADOR_2]->obtener_personaje(i)->obtener_sprite();
        spr_personajes_jugador_2[i].setScale(80.f / spr_personajes_jugador_2[i].getTexture()->getSize().x , 80.f / spr_personajes_jugador_2[i].getTexture()->getSize().y);
        spr_personajes_jugador_2[i].setPosition(ventana_juego->getSize().x - detalles_personajes_jugador_2.getGlobalBounds().width - spr_personajes_jugador_2[i].getGlobalBounds().width / 1.5, ventana_juego->getSize().y / 2.3 + (float)(135 * i));
    }

    cargar_graficos_turno();

    cargar_graficos_menu_juego();

    cargar_graficos_sub_menu_juego();

    cargar_graficos_guardar_salir();

}

void Juego::cargar_graficos_menu_juego() {
    opciones_menu_juego[0].setString(ALIMENTARSE);
    opciones_menu_juego[1].setString(MOVERSE);
    opciones_menu_juego[2].setString(PASAR_OPCION);

    for(int i = 0; i < OPCIONES_VALIDAS_MENU_JUEGO; i++){
        opciones_menu_juego[i].setFont(fuente);
        opciones_menu_juego[i].setFillColor(sf::Color::White);
        opciones_menu_juego[i].setCharacterSize(18);
        opciones_menu_juego[i].setPosition(sf::Vector2f((float)ventana_juego->getSize().x / 2  , 65 + (i * 20.0)));
        opciones_menu_juego[i].setOrigin(opciones_menu_juego[i].getGlobalBounds().width / 2, opciones_menu_juego[i].getGlobalBounds().height / 2);
    }

    opciones_menu_juego[0].setFillColor(sf::Color::Yellow);
}


void Juego::cargar_graficos_sub_menu_juego() {
    opciones_sub_menu_juego[0].setString(DEFENDERSE);
    opciones_sub_menu_juego[1].setString(ATACAR);
    opciones_sub_menu_juego[2].setString(PASAR_OPCION);

    for(int i = 0; i < OPCIONES_VALIDAS_SUB_MENU_JUEGO; i++){
        opciones_sub_menu_juego[i].setFont(fuente);
        opciones_sub_menu_juego[i].setFillColor(sf::Color::White);
        opciones_sub_menu_juego[i].setCharacterSize(18);
        opciones_sub_menu_juego[i].setPosition(sf::Vector2f((float)ventana_juego->getSize().x / 2  , 65 + (i * 20.0)));
        opciones_sub_menu_juego[i].setOrigin(opciones_sub_menu_juego[i].getGlobalBounds().width / 2, opciones_sub_menu_juego[i].getGlobalBounds().height / 2);
    }

    opciones_sub_menu_juego[0].setFillColor(sf::Color::Yellow);
}


void Juego::cargar_graficos_detalles_personajes() {
    detalles_personajes_jugador_1.setString("PERSONAJES\nJUGADOR 1: \n\n" + obtener_jugador(0)->detalles_personajes());
    detalles_personajes_jugador_1.setFont(fuente);
    detalles_personajes_jugador_1.setFillColor(Color::White);
    detalles_personajes_jugador_1.setCharacterSize(16);
    detalles_personajes_jugador_1.setOrigin(detalles_personajes_jugador_1.getGlobalBounds().width / 2, detalles_personajes_jugador_1.getGlobalBounds().height / 2);
    detalles_personajes_jugador_1.setPosition(10 + detalles_personajes_jugador_1.getGlobalBounds().width / 2, 70 + (float)ventana_juego->getSize().y / 2);

    detalles_personajes_jugador_2.setString("PERSONAJES\nJUGADOR 2: \n\n" + obtener_jugador(1)->detalles_personajes());
    detalles_personajes_jugador_2.setFont(fuente);
    detalles_personajes_jugador_2.setFillColor(Color::White);
    detalles_personajes_jugador_2.setCharacterSize(16);
    detalles_personajes_jugador_2.setOrigin(detalles_personajes_jugador_2.getGlobalBounds().width / 2, detalles_personajes_jugador_2.getGlobalBounds().height / 2);
    detalles_personajes_jugador_2.setPosition((float)ventana_juego->getSize().x - 10 - detalles_personajes_jugador_2.getGlobalBounds().width / 2, 70 + (float)ventana_juego->getSize().y / 2);
}


void Juego::cargar_graficos_turno() {
    turno_actual.setFont(fuente);
    turno_actual.setFillColor(Color::Cyan);
    turno_actual.setCharacterSize(22);

    while(! (jugadores[turnar()]->obtener_personaje(pos_personaje)->esta_vivo())){
        pos_personaje++;
        chequear_subturno();   
    }

    turno_actual.setString("Turno JUGADOR: " + to_string(turnar() + 1) + "  PERSONAJE: " + jugadores[turnar()]->obtener_personaje(pos_personaje)->nombre_personaje());
    turno_actual.setOrigin(turno_actual.getGlobalBounds().width / 2, turno_actual.getGlobalBounds().height / 2);
    turno_actual.setPosition((float)ventana_juego->getSize().x / 2, (float)ventana_juego->getSize().y - (float )turno_actual.getCharacterSize() - 3.f);
}


void Juego::cargar_graficos_guardar_salir() {
    opciones_guardar_salir[0].setString(GUARDAR_PARTIDA);
    opciones_guardar_salir[1].setString(SEGUIR_JUGANDO);

    for(int i = 0; i < OPCIONES_VALIDAS_GUARDAR_SALIR; i++){
        opciones_guardar_salir[i].setFont(fuente);
        opciones_guardar_salir[i].setFillColor(sf::Color::White);
        opciones_guardar_salir[i].setCharacterSize(18);
        opciones_guardar_salir[i].setPosition(sf::Vector2f((float)ventana_juego->getSize().x / 2  , 85 + (i * 20.0)));
        opciones_guardar_salir[i].setOrigin(opciones_guardar_salir[i].getGlobalBounds().width / 2, opciones_guardar_salir[i].getGlobalBounds().height / 2);
    }

    opciones_guardar_salir[0].setFillColor(sf::Color::Yellow);
}


void Juego::dibujar_juego() {
    ventana_juego->draw(spr_fondo);
    ventana_juego->draw(titulo);

    cargar_graficos_detalles_personajes(); //OBS: se carga cada vez que se dibuja el juego, ya que los datos se van modificando
    ventana_juego->draw(detalles_personajes_jugador_1);
    ventana_juego->draw(detalles_personajes_jugador_2);

    for(int i = 0; i < MAX_PERSONAJES; i++){
        ventana_juego->draw(spr_personajes_jugador_1[i]);
        ventana_juego->draw(spr_personajes_jugador_2[i]);
    }

    cargar_graficos_turno(); //OBS: se carga cada vez que se dibuja el juego, ya que los datos se van modificando
    ventana_juego->draw(turno_actual);

    dibujar_tablero();
    dibujar_personajes();
}


void Juego::dibujar_tablero() {
    tablero->obtener_vertices()->reiniciar();

    Lista * vertices = tablero->obtener_vertices();

    while(vertices->hay_siguiente()){

        ventana_juego->draw(vertices->obtener_actual()->obtener_casillero()->obtener_sprite());

        vertices->siguiente();
    }
}

//OBS: Si bien es la misma logica que dibujar_tablero(), si dibujo ambas cosas al mismo tiempo se van pisando (cosas de SFML);
void Juego::dibujar_personajes() {
    tablero->obtener_vertices()->reiniciar();

    Lista * vertices = tablero->obtener_vertices();

    while(vertices->hay_siguiente()){

        if(vertices->obtener_actual()->obtener_casillero()->hay_personaje() && vertices->obtener_actual()->obtener_casillero()->obtener_personaje()->esta_vivo()){
            ventana_juego->draw(vertices->obtener_actual()->obtener_casillero()->obtener_personaje()->obtener_sprite());
        }else {
            vertices->obtener_actual()->obtener_casillero()->posicionar_personaje(nullptr);
        }

        vertices->siguiente();
    }
}


void Juego::dibujar_menu_juego() {
    for (int i = 0; i < OPCIONES_VALIDAS_MENU_JUEGO; i++)
    {
        ventana_juego->draw(opciones_menu_juego[i]);
    }
}


void Juego::dibujar_sub_menu_juego() {
    for (int i = 0; i < OPCIONES_VALIDAS_SUB_MENU_JUEGO; i++)
    {
        ventana_juego->draw(opciones_sub_menu_juego[i]);
    }
}


void Juego::dibujar_guardar_salir() {
    for (int i = 0; i < OPCIONES_VALIDAS_GUARDAR_SALIR; i++)
    {
        ventana_juego->draw(opciones_guardar_salir[i]);
    }
}


void Juego::interfaz_menu_juego() {
    opcion_seleccionada = 0;

    esta_activo_sub_menu_juego = false;
    esta_activo_menu_juego = true;

    while(!termino && esta_activo_menu_juego)
    {
        ventana_juego->clear();

        dibujar_juego();
        dibujar_menu_juego();
        procesar_eventos_menu_juego();

        ventana_juego->display();
    }
}


void Juego::interfaz_sub_menu_juego() {
    opcion_seleccionada = 0;
    esta_activo_menu_juego = false;
    esta_activo_sub_menu_juego = true;

    while(!termino && esta_activo_sub_menu_juego)
    {
        ventana_juego->clear();

        dibujar_juego();
        dibujar_sub_menu_juego();
        procesar_eventos_sub_menu_juego();

        ventana_juego->display();
    }
}


void Juego::interfaz_guardar_salir() {
    opcion_seleccionada = 0;
    esta_activo_menu_juego = false;
    esta_activo_sub_menu_juego = false;
    opciones_guardar_salir[0].setFillColor(Color::Yellow);
    opciones_guardar_salir[1].setFillColor(Color::White);

    while(!termino && !esta_activo_menu_juego){
        ventana_juego->clear();

        dibujar_juego();
        dibujar_guardar_salir();
        procesar_eventos_guardar_salir();

        ventana_juego->display();
    }
}


void Juego::procesar_eventos_menu_juego() {
    Event evento{};

    while (!termino && ventana_juego->pollEvent(evento))
    {
        switch (evento.type)
        {
            case sf::Event::KeyReleased:
                switch (evento.key.code)
                {
                    case sf::Keyboard::Up:
                        subir_menu_juego();
                        break;

                    case sf::Keyboard::Down:
                       bajar_menu_juego();
                        break;

                    case sf::Keyboard::Return:
                        switch (obtener_opcion_seleccionada())
                        {
                            case 0: {
                                alimentar();
                                break;
                            }
                            case 1:
                                moverse();
                                break;
                            case 2:
                                pasar_opcion();
                                break;
                        }
                        break;
                }

                break;

            case sf::Event::Closed:
                salir();
                break;
        }
    }
}


void Juego::procesar_eventos_sub_menu_juego() {
    Event evento{};

    while (!termino && ventana_juego->pollEvent(evento))
    {
        switch (evento.type)
        {
            case sf::Event::KeyReleased:
                switch (evento.key.code)
                {
                    case sf::Keyboard::Up:
                        subir_sub_menu_juego();
                        break;

                    case sf::Keyboard::Down:
                        bajar_sub_menu_juego();
                        break;

                    case sf::Keyboard::Return:
                        switch (obtener_opcion_seleccionada())
                        {
                            case 0:
                                defenderse();
                                break;
                            case 1:
                                atacar();
                                break;
                            case 2:
                                pasar_opcion();
                                break;
                        }
                        break;
                }
                break;

            case sf::Event::Closed:
                salir();
                break;
        }
    }
}


void Juego::procesar_eventos_guardar_salir() {
    Event evento{};

    while (!termino && ventana_juego->pollEvent(evento))
    {
        switch (evento.type)
        {
            case sf::Event::KeyReleased:
                switch (evento.key.code)
                {
                    case sf::Keyboard::Up:
                        subir_guardar_salir();
                        break;

                    case sf::Keyboard::Down:
                        bajar_guardar_salir();
                        break;

                    case sf::Keyboard::Return:
                        switch (obtener_opcion_seleccionada())
                        {
                            case 0:
                                guardar_partida();
                                break;
                            case 1:
                                seguir_jugando();
                                break;
                        }
                        break;
                }
                break;

            case sf::Event::Closed:
                salir();
                break;
        }
    }
}


void Juego::subir_menu_juego() {
    if (opcion_seleccionada - 1 >= 0)
    {
        opciones_menu_juego[opcion_seleccionada].setFillColor(sf::Color::White);
        opcion_seleccionada--;
        opciones_menu_juego[opcion_seleccionada].setFillColor(sf::Color::Yellow);
    }
}


void Juego::bajar_menu_juego() {
    if (opcion_seleccionada + 1 < OPCIONES_VALIDAS_MENU_JUEGO)
    {
        opciones_menu_juego[opcion_seleccionada].setFillColor(sf::Color::White);
        opcion_seleccionada++;
        opciones_menu_juego[opcion_seleccionada].setFillColor(sf::Color::Yellow);
    }
}


void Juego::subir_sub_menu_juego() {
    if (opcion_seleccionada - 1 >= 0)
    {
        opciones_sub_menu_juego[opcion_seleccionada].setFillColor(sf::Color::White);
        opcion_seleccionada--;
        opciones_sub_menu_juego[opcion_seleccionada].setFillColor(sf::Color::Yellow);
    }
}


void Juego::bajar_sub_menu_juego() {
    if (opcion_seleccionada + 1 < OPCIONES_VALIDAS_SUB_MENU_JUEGO)
    {
        opciones_sub_menu_juego[opcion_seleccionada].setFillColor(sf::Color::White);
        opcion_seleccionada++;
        opciones_sub_menu_juego[opcion_seleccionada].setFillColor(sf::Color::Yellow);
    }
}


void Juego::subir_guardar_salir() {
    if (opcion_seleccionada - 1 >= 0)
    {
        opciones_guardar_salir[opcion_seleccionada].setFillColor(sf::Color::White);
        opcion_seleccionada--;
        opciones_guardar_salir[opcion_seleccionada].setFillColor(sf::Color::Yellow);
    }
}


void Juego::bajar_guardar_salir() {
    if (opcion_seleccionada + 1 < OPCIONES_VALIDAS_GUARDAR_SALIR)
    {
        opciones_guardar_salir[opcion_seleccionada].setFillColor(sf::Color::White);
        opcion_seleccionada++;
        opciones_guardar_salir[opcion_seleccionada].setFillColor(sf::Color::Yellow);
    }
}


void Juego::seguir_jugando() {
    interfaz_menu_juego();
}


int Juego::obtener_opcion_seleccionada() const {
    return opcion_seleccionada;
}


void Juego::imprimir_mensaje(Text mensaje) {
    Clock reloj = Clock();
    Time tiempo = Time();

    mensaje.setCharacterSize(22);
    mensaje.setOrigin(mensaje.getGlobalBounds().width / 2, mensaje.getGlobalBounds().height / 2);
    mensaje.setPosition((float)ventana_juego->getSize().x / 2, opciones_menu_juego[1].getPosition().y);

    while(tiempo.asSeconds() < 3) {

        ventana_juego->clear();

        tiempo = reloj.getElapsedTime();

        dibujar_juego();
        ventana_juego->draw(mensaje);

        ventana_juego->display();
    }
}


string Juego::pedir_coordenada() {
    esta_activo_menu_juego = false;

    string coordenada;

    Text pedir_coordenada("Ingrese la posicion (0 <= FILA <= 7, 0 <= COLUMNA <= 7) : ", fuente);
    pedir_coordenada.setPosition(sf::Vector2f(ventana_juego->getSize().x / 2.0  , opciones_menu_juego[0].getPosition().y));
    pedir_coordenada.setCharacterSize(22);
    pedir_coordenada.setOrigin(pedir_coordenada.getGlobalBounds().width / 2, pedir_coordenada.getGlobalBounds().height / 2);

    Text texto_de_entrada("", fuente);
    texto_de_entrada.setPosition(sf::Vector2f(ventana_juego->getSize().x / 2.0  , opciones_menu_juego[2].getPosition().y));
    texto_de_entrada.setCharacterSize(22);
    Clock reloj;
    Event evento{};

    while (!esta_activo_menu_juego)
    {
        ventana_juego->clear();

        while (ventana_juego->pollEvent(evento))
        {
            switch (evento.type)
            {
                case sf::Event::TextEntered:
                    if (std::isprint(evento.text.unicode))
                        coordenada += evento.text.unicode;

                case sf::Event::KeyReleased:
                    switch (evento.key.code)
                    {
                        case sf::Keyboard::BackSpace:
                            if (!coordenada.empty())
                                coordenada.pop_back();
                            break;

                        case sf::Keyboard::Return:
                            esta_activo_menu_juego = true;
                            break;
                    }

                    break;

                case sf::Event::Closed:
                    salir();
                    break;
            }
        }

        static sf::Time efecto_texto;
        static bool mostrar_efecto;

        efecto_texto += reloj.restart();

        if (efecto_texto >= sf::seconds(0.5f))
        {
            mostrar_efecto = !mostrar_efecto;
            efecto_texto = sf::Time::Zero;
        }

        texto_de_entrada.setString(coordenada + (mostrar_efecto ? '_' : ' '));

        dibujar_juego();
        texto_de_entrada.setOrigin(texto_de_entrada.getGlobalBounds().width / 2, texto_de_entrada.getGlobalBounds().height / 2);
        ventana_juego->draw(pedir_coordenada);
        ventana_juego->draw(texto_de_entrada);
        ventana_juego->display();
    }

    return coordenada;
}


Coordenada Juego::coordenada_valida_moverse() {
    Text mensaje;
    mensaje.setFont(fuente);

    int fila, columna;
    Coordenada coordenada;
    bool coordenada_valida = false;

    while(!coordenada_valida) {
        string posicion_personaje = pedir_coordenada();

        if(posicion_personaje.length() != 3 || !isdigit(posicion_personaje[0]) || !isdigit(posicion_personaje[2])){
            mensaje.setString("La coordenada ingresada no es valida!");
            imprimir_mensaje(mensaje);
        } else {

            char primera_coord[2];
            primera_coord[0] = posicion_personaje[0];
            primera_coord[1] = '\0';
            char segunda_coord[2];
            segunda_coord[0] = posicion_personaje[2];
            segunda_coord[1] = '\0';

            fila = atoi(primera_coord);
            columna = atoi(segunda_coord);

            if (0 <= columna && columna <= 7 && 0 <= fila && fila <= 7) {

                coordenada = Coordenada(fila, columna);

                if (!tablero->obtener_vertices()->consulta(coordenada)->obtener_casillero()->hay_personaje()) {
                    coordenada_valida = true;
                } else {
                    mensaje.setString("La posicion (" + to_string(coordenada.obtener_primera()) + ", " +
                                      to_string(coordenada.obtener_segunda()) + ") esta ocupada!");
                    imprimir_mensaje(mensaje);
                }
            } else {
                mensaje.setString("La coordenada ingresada no es valida!");
                imprimir_mensaje(mensaje);
            }
        }
    }
    return coordenada;
}

Coordenada Juego::coordenada_valida_atacar() {
    Text mensaje;
    mensaje.setFont(fuente);

    int fila, columna;
    Coordenada coordenada;
    bool coordenada_valida = false;

    while(!coordenada_valida) {
        string posicion_personaje = pedir_coordenada();

        if(posicion_personaje.length() != 3 || !isdigit(posicion_personaje[0]) || !isdigit(posicion_personaje[2])){
            mensaje.setString("La coordenada ingresada no es valida!");
            imprimir_mensaje(mensaje);
        } else {
            char primera_coord[2];
            primera_coord[0] = posicion_personaje[0];
            primera_coord[1] = '\0';
            char segunda_coord[2];
            segunda_coord[0] = posicion_personaje[2];
            segunda_coord[1] = '\0';

            fila = atoi(primera_coord);
            columna = atoi(segunda_coord);

            if (0 <= columna && columna <= 7 && 0 <= fila && fila <= 7) {

                coordenada = Coordenada(fila, columna);

                if (tablero->obtener_vertices()->consulta(coordenada)->obtener_casillero()->hay_personaje()) {
                    coordenada_valida = true;
                } else {
                    mensaje.setString(
                            "No hay ningun personaje en la posicion: (" + to_string(coordenada.obtener_primera()) + ", " + to_string(coordenada.obtener_segunda()) + ")!");
                    imprimir_mensaje(mensaje);
                }
            } else {
                mensaje.setString("La coordenada ingresada no es valida!");
                imprimir_mensaje(mensaje);
            }
        }
    }
    return coordenada;
}

bool Juego::cargar_partida(string archivo_carga) {
    ifstream carga;
    carga.open(archivo_carga);

    if(carga) {

        string turno_act; // primer turno desde la partida guardada
        string id_jugador;
        string elemento;
        string nombre;
        string escudo;
        string vida;
        string energia;
        string fila;
        string columna;

        getline(carga, turno_act);

        this->turno = stoi(turno_act);
        pos_personaje = 0;

        while(getline(carga, id_jugador, ',')) {
            getline(carga, elemento, ',');
            getline(carga, nombre, ',');
            getline(carga, escudo, ',');
            getline(carga, vida, ',');
            getline(carga, energia, ',');
            getline(carga, fila, ',');
            getline(carga, columna);
            crear_y_ubicar_personaje(elemento, nombre, stoi(escudo), stoi(vida), stoi(energia), stoi(fila), stoi(columna), stoi(id_jugador)); // aca crea y carga los pj en las listas de pj elegidos de cada jugador, segun el id, y luego los posiciona en el vertice correspondiente del tablero
        }
        partida_cargada = true;
        return true;
    }
    partida_cargada = false;
    return false;
}

void Juego::crear_y_ubicar_personaje(string elemento, string nombre, int escudo, int vida, int energia, int fila, int columna, int id_jugador) {
    Personaje* nuevo;
    if(elemento == ELEMENTO_AGUA) nuevo = new Personaje_de_agua(nombre, escudo, vida, energia, fila, columna, id_jugador);
    else if(elemento == ELEMENTO_AIRE) nuevo = new Personaje_de_aire(nombre, escudo, vida, energia, fila, columna, id_jugador);
    else if(elemento == ELEMENTO_FUEGO) nuevo = new Personaje_de_fuego(nombre, escudo, vida, energia, fila, columna, id_jugador);
    else if(elemento == ELEMENTO_TIERRA) nuevo = new Personaje_de_tierra(nombre, escudo, vida, energia, fila, columna, id_jugador);
    Coordenada c = Coordenada(fila, columna);
    tablero->acceder_tablero(c)->obtener_casillero()->posicionar_personaje(nuevo);
    jugadores[id_jugador]->agregar_personaje(nuevo);
}

void Juego::guardar_partida() {
    ofstream carga;
    carga.open(ARCHIVO_CARGA); // hacemos una constante de esto

    int id_jugador;
    string elemento;
    string nombre;
    int escudo;
    int vidas;
    int energia;
    int fila;
    int columna;

    carga << turnar() << '\n';

    for(int i = 0; i < MAX_CANT_JUGADORES; i++) {
        id_jugador = i;
        for(int j = 0; j < jugadores[id_jugador]->obtener_cantidad_personajes(); j++) {
            carga << id_jugador << ',';
            elemento = jugadores[id_jugador]->obtener_personaje(j)->de_que_elemento_soy();
            carga << elemento << ',';
            nombre = jugadores[id_jugador]->obtener_personaje(j)->nombre_personaje();
            carga << nombre << ',';
            escudo = jugadores[id_jugador]->obtener_personaje(j)->obtener_escudo();
            carga << escudo << ',';
            vidas = jugadores[id_jugador]->obtener_personaje(j)->obtener_vida();
            carga << vidas << ',';
            energia = jugadores[id_jugador]->obtener_personaje(j)->obtener_energia();
            carga << energia << ',';
            fila = jugadores[id_jugador]->obtener_personaje(j)->obtener_coordenadas().obtener_primera();
            carga << fila << ',';
            columna = jugadores[id_jugador]->obtener_personaje(j)->obtener_coordenadas().obtener_segunda();
            carga << columna << '\n';
        }
    }
    salir();
}

void Juego::salir() {
    termino = true;
    esta_activo_menu_juego = false;
    esta_activo_sub_menu_juego = false;
    ventana_juego->close();
}

void Juego::fin_del_juego() {
    Text mensaje, fin_del_juego;
    string ganador;
    Clock reloj = Clock();
    Time tiempo = Time();

    mensaje.setFont(fuente);
    fin_del_juego.setFont(fuente);
    fin_del_juego.setString("FIN DEL JUEGO");
    fin_del_juego.setCharacterSize(120);
    fin_del_juego.setOrigin(fin_del_juego.getGlobalBounds().width / 2, fin_del_juego.getGlobalBounds().height / 2);
    fin_del_juego.setPosition((float)ventana_juego->getSize().x / 2, (float)ventana_juego->getSize().y / 4);


    if(obtener_jugador(JUGADOR_1)->jugador_perdio()) ganador = "JUGADOR 2";
    else ganador = "JUGADOR 1";

    mensaje.setString("GANADOR: " + ganador);
    mensaje.setCharacterSize(80);
    mensaje.setOrigin(mensaje.getGlobalBounds().width / 2, mensaje.getGlobalBounds().height / 2);
    mensaje.setPosition((float)ventana_juego->getSize().x / 2, (float)ventana_juego->getSize().y / 2);

    while(tiempo.asSeconds() < 5) {

        ventana_juego->clear();

        tiempo = reloj.getElapsedTime();

        ventana_juego->draw(spr_fondo);
        ventana_juego->draw(fin_del_juego);
        ventana_juego->draw(mensaje);

        ventana_juego->display();
    }

    if(partida_cargada) remove("partida.csv");

    salir();
}
