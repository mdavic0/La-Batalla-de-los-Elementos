#include "grafo.h"

Grafo::Grafo(string nombre_archivo) {
    vertices = new Lista;
    dim_fila = 0;
    dim_columna = 0;
    cargar_mapa(nombre_archivo);
    cargar_tablero();
    conectar_vertices();
    distancias_p_agua = new int*[CANTIDAD_CASILLEROS];
    distancias_p_aire = new int*[CANTIDAD_CASILLEROS];
    distancias_p_fuego = new int*[CANTIDAD_CASILLEROS];
    distancias_p_tierra = new int*[CANTIDAD_CASILLEROS];

    distancias_ataque_tierra = new int*[CANTIDAD_CASILLEROS];

    recorridos_p_agua = new int*[CANTIDAD_CASILLEROS];
    recorridos_p_aire = new int*[CANTIDAD_CASILLEROS];
    recorridos_p_fuego = new int*[CANTIDAD_CASILLEROS];
    recorridos_p_tierra = new int*[CANTIDAD_CASILLEROS];

    for(int i = 0; i < CANTIDAD_CASILLEROS; i++){
        distancias_p_tierra[i] = new int[CANTIDAD_CASILLEROS];
        distancias_p_agua[i] = new int[CANTIDAD_CASILLEROS];
        distancias_p_aire[i] = new int[CANTIDAD_CASILLEROS];
        distancias_p_fuego[i] = new int[CANTIDAD_CASILLEROS];

        distancias_ataque_tierra[i] = new int[CANTIDAD_CASILLEROS];

        recorridos_p_agua[i] = new int[CANTIDAD_CASILLEROS];
        recorridos_p_aire[i] = new int[CANTIDAD_CASILLEROS];
        recorridos_p_fuego[i] = new int[CANTIDAD_CASILLEROS];
        recorridos_p_tierra[i] = new int[CANTIDAD_CASILLEROS];
    }

    floyd_warshall(ELEMENTO_AGUA, distancias_p_agua, recorridos_p_agua);
    floyd_warshall(ELEMENTO_AIRE, distancias_p_aire, recorridos_p_aire);
    floyd_warshall(ELEMENTO_TIERRA, distancias_p_tierra, recorridos_p_tierra);
    floyd_warshall(ELEMENTO_FUEGO, distancias_p_fuego, recorridos_p_fuego);
    floyd_warshall();

}

Lista* Grafo::obtener_vertices() {
    return vertices;
}

void Grafo::cargar_mapa(string archivo) {
    ifstream archivo_mapa;
    archivo_mapa.open(archivo);

    if (archivo_mapa) {

        int i = 0, j = 0;
        string casillero, dim;

        getline(archivo_mapa, dim, ',');
        dim_fila = stoi(dim);
        getline(archivo_mapa, dim);
        dim_columna = stoi(dim);

        for (i; i < dim_fila; i++) {
            for (j; j < dim_columna; j++) {
                getline(archivo_mapa, casillero, ',');
                Casillero* nuevo = crear_casillero(casillero);
                Vertice* nuevo_vertice = new Vertice(nuevo, i, j);
                nuevo->asignar_posicion(200.f + 20.f + (j * 50.f), 170.f + (i * 50.f)); // esto lo explica mauri
                vertices->alta(nuevo_vertice);
            }
            j = 0;
        }
    }

    else {
        cout << "nonopepe" << endl;
        tablero = 0;
    }
}


void Grafo::buscar_vertices_adyacentes(Vertice* vertice) {
    conectar_vertice(vertice, ARRIBA, false);
    conectar_vertice(vertice, ABAJO, false);
    conectar_vertice(vertice, IZQUIERDA, false);
    conectar_vertice(vertice, DERECHA, false);
    conectar_vertice(vertice, ARRIBA_IZQ, true);
    conectar_vertice(vertice, ARRIBA_DER, true);
    conectar_vertice(vertice, ABAJO_IZQ, true);
    conectar_vertice(vertice, ABAJO_DER, true);
}


void Grafo::conectar_vertice(Vertice* vertice, Coordenada direccion, bool es_diagonal) {
    Coordenada nueva = vertice->obtener_coordenadas() + direccion;
    Vertice* vertice_ady = vertices->consulta(nueva);
    if(vertice_ady) crear_y_agregar_arista(vertice, vertice_ady, es_diagonal);
}

void Grafo::conectar_vertices() {
    vertices->reiniciar();
    for (int i = 0; i < dim_fila*dim_columna; i++){
        buscar_vertices_adyacentes(vertices->consulta(i));
    }
}

Casillero* Grafo::crear_casillero(string casillero) {

    Casillero* nuevo_casillero;

    if (casillero == CAMINO) nuevo_casillero = new Camino();
    else if (casillero == LAGO) nuevo_casillero = new Lago();
    else if (casillero == MONTANIA) nuevo_casillero = new Montania();
    else if (casillero == PRECIPICIO) nuevo_casillero = new Precipicio();
    else if (casillero == VACIO) nuevo_casillero = new Vacio();
    else nuevo_casillero = new Volcan();

    return nuevo_casillero;
}

void Grafo::crear_y_agregar_arista(Vertice* origen, Vertice* destino, bool es_diagonal) {
    Arista* nueva;
    if(es_diagonal) nueva = new Arista(origen, destino, 1);
    else nueva = new Arista(origen, destino);
    origen->agregar_arista(nueva, es_diagonal);
}

void Grafo::cargar_tablero() {
    tablero = new Vertice**[dim_fila];
    for(int i = 0; i < dim_fila; i++) tablero[i] = new Vertice*[dim_columna];
    int fila, columna;
    vertices->reiniciar();
    while(vertices->hay_siguiente()) {
        fila = vertices->consulta(vertices->obtener_indice_actual())->obtener_coordenadas().obtener_primera();
        columna = vertices->consulta(vertices->obtener_indice_actual())->obtener_coordenadas().obtener_segunda();
        tablero[fila][columna] = vertices->consulta(vertices->obtener_indice_actual());
        vertices->siguiente();
    }
}

Vertice* Grafo::acceder_tablero(Coordenada coordenada) {
    int f = coordenada.obtener_primera();
    int c = coordenada.obtener_segunda();
    return tablero[f][c];
}

void Grafo::floyd_warshall(string elemento, int** distancias, int** recorridos) { // este va en el constructor de grafo, le pasas todas las matrices atributo y su respectivo elemento para que las inicialice
    int i, j;

    for (i = 0; i < vertices->obtener_cantidad(); i++) {
        for (j = 0; j < vertices->obtener_cantidad(); j++) {
            if (i == j) {
                distancias[i][j] = 0;
            } else {
                distancias[i][j] = INFINITO;
            }
        }
    }


    for (i = 0; i < vertices->obtener_cantidad(); i++) {
        for (int k = 0; k < vertices->obtener_cantidad(); k++) {
            for (j = 0; j < vertices->consulta(i)->obtener_cantidad_aristas(false); j++) {
                if (vertices->consulta(i)->obtener_arista(j, false)->obtener_destino() == vertices->consulta(k)) {
                    Arista *arista_act = vertices->consulta(i)->obtener_arista(j, false);
                    int costo_act = arista_act->obtener_destino()->obtener_casillero()->calcular_costo(elemento);
                    distancias[i][k] = costo_act;
                }
            }
        }
    }
    for (i = 0; i < vertices->obtener_cantidad(); i++) {
        for (j = 0; j < vertices->obtener_cantidad(); j++) {
            recorridos[i][j] = 0;
        }
    }

    for (i = 0; i < vertices->obtener_cantidad(); i++) {
        for (j = 0; j < vertices->obtener_cantidad(); j++) {
            if (distancias[i][j] != INFINITO) {
                recorridos[i][j] = j;
            }
        }
    }
    for (int k = 0; k < vertices->obtener_cantidad(); k++) {
        for (i = 0; i < vertices->obtener_cantidad(); i++) {
            for (j = 0; j < vertices->obtener_cantidad(); j++) {
                if (distancias[i][j] > distancias[i][k] + distancias[k][j]) {
                    distancias[i][j] = distancias[i][k] + distancias[k][j];
                    recorridos[i][j] = recorridos[i][k];
                }
            }
        }
    }
}

string Grafo::camino_minimo(int nodo_inicial, int nodo_final, string elemento){
    int** recorridos;

    if (elemento == ELEMENTO_AGUA) recorridos = recorridos_p_agua;

    if (elemento == ELEMENTO_FUEGO) recorridos = recorridos_p_fuego;

    if (elemento == ELEMENTO_AIRE) recorridos = recorridos_p_aire;

    if (elemento == ELEMENTO_TIERRA) recorridos = recorridos_p_tierra;

    int at = nodo_inicial;
    int final = nodo_final;
    int fila_act = vertices->consulta(at)->obtener_coordenadas().obtener_primera();
    int columna_act = vertices->consulta(at)->obtener_coordenadas().obtener_segunda();
    string camino_minimo = "(" + to_string(fila_act) + ", " + to_string(columna_act) + ")" + "->"; ;
    while (at != final) {
        at = recorridos[at][final];
        fila_act = vertices->consulta(at)->obtener_coordenadas().obtener_primera();
        columna_act = vertices->consulta(at)->obtener_coordenadas().obtener_segunda();

        if (at == final) camino_minimo += "(" + to_string(fila_act) + ", " + to_string(columna_act) + ")";
        else camino_minimo += "(" + to_string(fila_act) + ", " + to_string(columna_act) + ")" + "->";
    }
    return camino_minimo;
}


int Grafo::costo_camino_minimo(Vertice* origen, Vertice* destino) {
    int costo = 0;
    int numero_origen = dim_fila * origen->obtener_coordenadas().obtener_primera() + origen->obtener_coordenadas().obtener_segunda();
    int numero_destino = dim_fila * destino->obtener_coordenadas().obtener_primera() + destino->obtener_coordenadas().obtener_segunda();

    if (origen->obtener_casillero()->obtener_personaje()->de_que_elemento_soy() == ELEMENTO_AGUA) costo = distancias_p_agua[numero_origen][numero_destino];
    else if (origen->obtener_casillero()->obtener_personaje()->de_que_elemento_soy() == ELEMENTO_AIRE) costo = distancias_p_aire[numero_origen][numero_destino];
    else if (origen->obtener_casillero()->obtener_personaje()->de_que_elemento_soy() == ELEMENTO_FUEGO) costo = distancias_p_fuego[numero_origen][numero_destino];
    else costo = distancias_p_tierra[numero_origen][numero_destino];

    return costo;
}


void Grafo::floyd_warshall() { // sobrecarga de floyd warshall, simplemente arma la matriz de costos de distancias (en unidad casillero = 1) de cada vertice, contando diagonales
    int i, j, k;
    for(i = 0; i < vertices->obtener_cantidad(); i++) {
        for(j = 0; j < vertices->obtener_cantidad(); j++) {
            if(i == j) distancias_ataque_tierra[i][j] = 0;
            else distancias_ataque_tierra[i][j] = INFINITO;
        }
    }

    for(i = 0; i < vertices->obtener_cantidad(); i++) {
        for (k = 0; k < vertices->obtener_cantidad(); k++) {
            for (j = 0; j < vertices->consulta(i)->obtener_cantidad_aristas(true); j++) {
                if (vertices->consulta(i)->obtener_arista(j, true)->obtener_destino() == vertices->consulta(k)) {
                    Arista *arista_act = vertices->consulta(i)->obtener_arista(j, true);
                    distancias_ataque_tierra[i][k] = arista_act->obtener_costo();
                }
            }
        }
    }

    for(int k = 0; k < vertices->obtener_cantidad(); k++) {
        for(i = 0; i < vertices->obtener_cantidad(); i++) {
            for(j = 0; j < vertices->obtener_cantidad(); j++) {
                if(distancias_ataque_tierra[i][j] > distancias_ataque_tierra[i][k] + distancias_ataque_tierra[k][j]) {
                    distancias_ataque_tierra[i][j] = distancias_ataque_tierra[i][k] + distancias_ataque_tierra[k][j];
                }
            }
        }
    }
}

Grafo::~Grafo() {
        while (!vertices->vacia()) {
            Vertice *eliminar = vertices->baja_y_devuelve(0);
            delete eliminar;
        }
        delete vertices;

        for (int i = 0; i < dim_fila; i++) delete[] tablero[i];
        delete[] tablero;

        for (int i = 0; i < dim_fila * dim_columna; i++) delete[] distancias_p_agua[i];
        delete[] distancias_p_agua;

        for (int i = 0; i < dim_fila * dim_columna; i++) delete[] distancias_p_aire[i];
        delete[] distancias_p_aire;

        for (int i = 0; i < dim_fila * dim_columna; i++) delete[] distancias_p_fuego[i];
        delete[] distancias_p_fuego;

        for (int i = 0; i < dim_fila * dim_columna; i++) delete[] distancias_p_tierra[i];
        delete[] distancias_p_tierra;

        for (int i = 0; i < dim_fila * dim_columna; i++) delete[] recorridos_p_agua[i];
        delete[] recorridos_p_agua;

        for (int i = 0; i < dim_fila * dim_columna; i++) delete[] recorridos_p_aire[i];
        delete[] recorridos_p_aire;

        for (int i = 0; i < dim_fila * dim_columna; i++) delete[] recorridos_p_fuego[i];
        delete[] recorridos_p_fuego;

        for (int i = 0; i < dim_fila * dim_columna; i++) delete[] recorridos_p_tierra[i];
        delete[] recorridos_p_tierra;

        for (int i = 0; i < dim_fila * dim_columna; i++) delete[] distancias_ataque_tierra[i];
        delete[] distancias_ataque_tierra;
    }
