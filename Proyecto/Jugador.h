#ifndef _JUGADOR_H_
#define _JUGADOR_H_

typedef struct {
    int id;
    string nombre;
    int goles;
} Jugador;

/******************************************************************************/
/* Definicion de Primitivas */
/*--------------------------*/

/*
  pre : el jugador no debe haber sido creada.
  post: el jugador queda creada y preparada para ser usada con valores 0.
*/
void crear(Jugador &jugador);

/*----------------------------------------------------------------------------*/
/*
  pre: el jugador debe haberse creado y no destruido
  post: deja la instacia de la lista para ser usado. Los parametros se aplica al tda (jugador).
*/
void crear(Jugador &jugador, int id, string nombre, int goles);

/*----------------------------------------------------------------------------*/
/*
  pre: el jugador debe haberse creado y no destruido.
  post: destruye la instancia del tda y ya no podrá ser usado.
*/
void destruir(Jugador &jugador);

/*----------------------------------------------------------------------------*/
/*
  pre: el jugador debe haberse creado y no destruido.
  post: asigna el valor de id a la instancia de jugador.
*/
void setId(Jugador &jugador, int id);

/*----------------------------------------------------------------------------*/
/*
  pre: el jugador debe haberse creado y no destruido.
  post: devuelve el id.
*/
int getId(Jugador &jugador);

/*----------------------------------------------------------------------------*/
/*
  pre: el jugador debe haberse creado y no destruido.
  post: asigna el valor de nombre a la instancia de jugador.
*/
void setNombre(Jugador &jugador, string nombre);

/*----------------------------------------------------------------------------*/
/*
  pre: el jugador debe haberse creado y no destruido.
  post: devuelve el nombre.
*/
string getNombre(Jugador &jugador);

/*----------------------------------------------------------------------------*/
/*
  pre: el jugador debe haberse creado y no destruido.
  post: asigna el valor de goles a la instancia de jugador.
*/
void setGoles(Jugador &jugador, int goles);

/*----------------------------------------------------------------------------*/
/*
  pre: el jugador debe haberse creado y no destruido.
  post: devuelve los goles.
*/
int getGoles(Jugador &jugador);

/*----------------------------------------------------------------------------*/
bool equals(Jugador &jugador, Jugador j);

/*----------------------------------------------------------------------------*/
string toString(Jugador &jugador);

#endif // _JUGADOR_H_
