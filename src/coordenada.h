#ifndef COORDENADA_H_INCLUDED
#define COORDENADA_H_INCLUDED

class Coordenada {
private:
    int primera, segunda;
public:
    /*
     PRE: -
     POS: crea un objeto Coordenada con coord primera y segunda igual a 0.
     */
    Coordenada(): primera(0), segunda(0) {}

    /*
     PRE: primera y segunda son enteros.
     POS: crea un objeto Coordenada con coord primera y segunda pasada por parametro.
     */
    Coordenada(const int primera, const int segunda);

    /*
     PRE: c es un objeto de tipo Coordenada.
     POS: realiza la suma entre dos objetos de tipo Coordenada.
     */
    Coordenada operator+(Coordenada c);

    /*
    PRE: c es un objeto de tipo Coordenada.
    POS: asigna c a otro objeto de tipo Coordenada.
    */
    Coordenada operator=(Coordenada c);

    /*
     PRE: c es un objeto de tipo Coordenada.
     POS: compara c con otro objeto de tipo Coordenada.
     */
    bool operator==(Coordenada c);

    /*
     PRE: -
     POS: devuelve el valor de la primera coordenada del objeto.
     */
    int obtener_primera();

    /*
     PRE: -
     POS: devuelve el valor de la segunda coordenada del objeto.
     */
    int obtener_segunda();

    /*
     PRE: nueva es de tipo entero.
     POS: asigna nueva a primera.
     */
    void cambiar_primera(int nueva);

    /*
     PRE: nueva es de tipo entero.
     POS: asigna nueva a segunda.
     */
    void cambiar_segunda(int nueva);

};
#endif // COORDENADA_H_INCLUDED