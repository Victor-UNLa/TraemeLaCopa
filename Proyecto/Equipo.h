#ifndef _EQUIPO_H_
#define _EQUIPO_H_
/**
    Axiomas:
    * Los golesAFavor del Equipo se validan en a la suma de
    goles de sus jugadores
*/
typedef struct {
    int id;
    string nombre;
    int golesAFavor;
    int golesEnContra;
    int puntos;
    Lista *jugadores;
} Equipo;


/******************************************************************************/
/* Definicion de Primitivas */
/*--------------------------*/

/*
  pre : el equipo no debe haber sido creada.
  post: el equipo queda creada y preparada para ser usada con valores 0.
*/
void crear(Equipo &equipo);

/*----------------------------------------------------------------------------*/
/*
  pre: el equipo debe haberse creado y no destruido
  post: deja la instacia de la lista para ser usado. Los parametros se aplica al tda (equipo).
*/
void crear(Equipo &equipo, int id, string nombre, int golesAFavor, int golesEnContra, int puntos);

/*----------------------------------------------------------------------------*/
/*
  pre: el equipo debe haberse creado y no destruido.
  post: destruye la instancia del tda y ya no podrá ser usado.
*/
void destruir(Equipo &equipo);

/*----------------------------------------------------------------------------*/
/*
  pre: el equipo debe haberse creado y no destruido.
  post: asigna el valor de id a la instancia de equipo.
*/
void setId(Equipo &equipo, int id);

/*----------------------------------------------------------------------------*/
/*
  pre: el equipo debe haberse creado y no destruido.
  post: devuelve el id.
*/
int getId(Equipo &equipo);

/*----------------------------------------------------------------------------*/
/*
  pre: el equipo debe haberse creado y no destruido.
  post: asigna el valor de nombre a la instancia de equipo.
*/
void setNombre(Equipo &equipo, string nombre);

/*----------------------------------------------------------------------------*/
/*
  pre: el equipo debe haberse creado y no destruido.
  post: devuelve el nombre.
*/
string getNombre(Equipo &equipo);

/*----------------------------------------------------------------------------*/
/*
  pre: el equipo debe haberse creado y no destruido.
  post: asigna el valor de goles a favor a la instancia de equipo.
*/
void setGolesAFavor(Equipo &equipo, int golesAFavor);

/*----------------------------------------------------------------------------*/
/*
  pre: el equipo debe haberse creado y no destruido.
  post: devuelve el goles a favor.
*/
int getGolesAFavor(Equipo &equipo);

/*----------------------------------------------------------------------------*/
/*
  pre: el equipo debe haberse creado y no destruido.
  post: asigna el valor de goles en contra a la instancia de equipo.
*/
void setGolesEnContra(Equipo &equipo, int golesEnContra);

/*----------------------------------------------------------------------------*/
/*
  pre: el equipo debe haberse creado y no destruido.
  post: devuelve el goles en contra.
*/
int getGolesEnContra(Equipo &equipo);

/*----------------------------------------------------------------------------*/
/*
  pre: el equipo debe haberse creado y no destruido.
  post: asigna el valor de puntos a la instancia de equipo.
*/
void setPuntos(Equipo &equipo, int puntos);

/*----------------------------------------------------------------------------*/
/*
  pre: el equipo debe haberse creado y no destruido.
  post: devuelve el puntos.
*/
int getPuntos(Equipo &equipo);

/*----------------------------------------------------------------------------*/
/*
  pre: el equipo debe haberse creado y no destruido.
  post: asigna el valor de jugadores a la instancia de equipo.
*/
void setJugadores(Equipo &equipo, Lista *jugadores);

/*----------------------------------------------------------------------------*/
/*
  pre: el equipo debe haberse creado y no destruido.
  post: asigna el valor de jugadores.
*/
void setJugadores(Equipo &equipo, Jugador *jugador);

/*----------------------------------------------------------------------------*/
/*
  pre: el equipo debe haberse creado y no destruido.
  post: devuelve los jugadores.
*/
Lista* getJugadores(Equipo &equipo);

/*----------------------------------------------------------------------------*/
/*
  pre: la instancia del tda(equipo,e) debe haberse creado y no destruido.
  post: devuelve Verdadero o Falso si son iguales los equipos.
*/
bool equals(Equipo &equipo, Equipo e);

/*----------------------------------------------------------------------------*/
/*
  pre: la instancia del tda(equipo) debe haberse creado y no destruido.
  post: devuelve los datos del equipo.
*/
string toString(Equipo &equipo);


#endif // _EQUIPO_H_
