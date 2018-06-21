#ifndef _PARTIDO_H_
#define _PARTIDO_H_
/**
    Axiomas:
    * Cuando el partido tiene sus dos equipos se considera
    las victorias anteriores correspondientes aceptadas.
    * En el caso de los partidos que aún no se hayan jugado,
    los goles se registrarán con el valor “-1”.

*/
enum Estado {SIN_COMENZAR, EN_JUEGO, FINALIZADO};

typedef struct {
    int id;
    Equipo *equipoL;
    Equipo *equipoV;
    int golesL;
    int golesV;
    Estado estado;
} Partido;

/******************************************************************************/
/* Definicion de Primitivas */
/*--------------------------*/

/*
  pre : el partido no debe haber sido creada.
  post: el partido queda creada y preparada para ser usada con valores 0.
*/
void crear(Partido &partido);

/*----------------------------------------------------------------------------*/
/*
  pre: el partido debe haberse creado y no destruido
  post: deja la instacia de la lista para ser usado. Los parametros se aplica al tda (partido).
*/
void crear(Partido &partido, int id, Equipo *equipoL, Equipo *equipoV, int golesL, int golesV);

/*----------------------------------------------------------------------------*/
/*
  pre: el partido debe haberse creado y no destruido.
  post: destruye la instancia del tda y ya no podrá ser usado.
*/
void destruir(Partido &partido);

/*----------------------------------------------------------------------------*/
/*
  pre: el partido debe haberse creado y no destruido.
  post: asigna el valor de id a la instancia de partido.
*/
void setId(Partido &partido, int id);

/*----------------------------------------------------------------------------*/
/*
  pre: el partido debe haberse creado y no destruido.
  post: devuelve el id.
*/
int getId(Partido &partido);

/*----------------------------------------------------------------------------*/
/*
  pre: el partido debe haberse creado y no destruido.
  post: asigna el valor de equipo local a la instancia de partido.
*/
void setEquipoL(Partido &partido, Equipo *equipoL);

/*----------------------------------------------------------------------------*/
/*
  pre: el partido debe haberse creado y no destruido.
  post: devuelve el equipo local.
*/
Equipo* getEquipoL(Partido &partido);

/*----------------------------------------------------------------------------*/
/*
  pre: el partido debe haberse creado y no destruido.
  post: asigna el valor de equipo visitante a la instancia de partido.
*/
void setEquipoV(Partido &partido, Equipo *equipoV);

/*----------------------------------------------------------------------------*/
/*
  pre: el partido debe haberse creado y no destruido.
  post: devuelve el equipo visitante.
*/
Equipo* getEquipoV(Partido &partido);

/*----------------------------------------------------------------------------*/
/*
  pre: el partido debe haberse creado y no destruido.
  post: asigna el valor de goles local a la instancia de partido.
*/
void setGolesL(Partido &partido, int golesL);

/*----------------------------------------------------------------------------*/
/*
  pre: el partido debe haberse creado y no destruido.
  post: devuelve los goles local.
*/
int getGolesL(Partido &partido);

/*----------------------------------------------------------------------------*/
/*
  pre: el partido debe haberse creado y no destruido.
  post: asigna el valor de goles visitante a la instancia de partido.
*/
void setGolesV(Partido &partido, int golesV);

/*----------------------------------------------------------------------------*/
/*
  pre: el partido debe haberse creado y no destruido.
  post: devuelve los goles visitante.
*/
int getGolesV(Partido &partido);

/*----------------------------------------------------------------------------*/
/*
  pre: el partido debe haberse creado y no destruido.
  post: asigna el valor de estado a la instancia de partido.
*/
void setEstado(Partido &partido, Estado estado);

/*----------------------------------------------------------------------------*/
/*
  pre: el partido debe haberse creado y no destruido.
  post: devuelve el estado.
*/
Estado getEstado(Partido &partido);

/*----------------------------------------------------------------------------*/
/*
  pre: el partido debe haberse creado y no destruido.
  post: devuelve Verdadero o Falso si son iguales los partidos.
*/
bool equals(Partido &partido, Partido p);

/*----------------------------------------------------------------------------*/
/*
  pre: el partido debe haberse creado y no destruido.
  post: devuelve los datos del partido.
*/
string toString(Partido &partido);

#endif // _PARTIDO_H_
