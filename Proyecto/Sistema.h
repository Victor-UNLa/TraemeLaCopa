#ifndef _SISTEMA_H_
#define _SISTEMA_H_

typedef struct {
    Lista *equipos;
    Lista *jugadores;
    Lista *grupos;
    Lista *partidos;
} Sistema;

/******************************************************************************/
/* Definicion de Primitivas */
/*--------------------------*/

/*
  pre : el sistema no debe haber sido creada.
  post: el sistema queda creada y preparada para ser usada.
*/
void crear(Sistema &sistema);

/*----------------------------------------------------------------------------*/
/*
  pre: el sistema debe haberse creado y no destruido.
  post: destruye la instancia del tda y ya no podrá ser usado.
*/
void destruir(Sistema &sistema);

/*----------------------------------------------------------------------------*/
/*
  pre: el sistema debe haberse creado y no destruido.
  post: lee el archivo equipos y muestra por pantalla los datos cargados.
*/
void levantarEquipos(Sistema &sistema);

/*----------------------------------------------------------------------------*/
/*
  pre: el sistema debe haberse creado y no destruido.
  post: lee el archivo jugador y muestra por pantalla los datos cargados.
*/
void levantarJugadores(Sistema &sistema);

/*----------------------------------------------------------------------------*/
/*
  pre: el sistema debe haberse creado y no destruido.
  post: lee el archivo grupos y muestra por pantalla los datos cargados.
*/
void levantarGrupos(Sistema &sistema);

/*----------------------------------------------------------------------------*/
/*
  pre: el sistema debe haberse creado y no destruido.
  post: lee el archivo partidos y muestra por pantalla los datos cargados.
*/
void levantarPartidos(Sistema &sistema);

/*----------------------------------------------------------------------------*/
/*
  pre:
  post:
*/
void mostrarEquipos(Sistema &sistema);

/*----------------------------------------------------------------------------*/
/*
  pre:
  post:
*/
void mostrarJugadores(Sistema &sistema);

/*----------------------------------------------------------------------------*/
/*
  pre:
  post:
*/
void mostrarGrupos(Sistema &sistema);

/*----------------------------------------------------------------------------*/
/*
  pre:
  post:
*/
void mostrarPartidos(Sistema &sistema);

/*----------------------------------------------------------------------------*/
/*
  pre:
  post:
*/
void goleadores(Sistema &sistema);

/*----------------------------------------------------------------------------*/
/*
  pre:
  post:
*/
void bajarEquipos(Sistema &sistema);

/*----------------------------------------------------------------------------*/
/*
  pre:
  post:
*/
void bajarJugadores(Sistema &sistema);

/*----------------------------------------------------------------------------*/
/*
  pre:
  post:
*/
void bajarGrupos(Sistema &sistema);

/*----------------------------------------------------------------------------*/
/*
  pre:
  post:
*/
void bajarPartidos(Sistema &sistema);

/*----------------------------------------------------------------------------*/
/*
  pre:
  post:
*/
Equipo* traerEquipoPorJugador(Sistema &sistema, int id);

/*----------------------------------------------------------------------------*/
/*
  pre:
  post:
*/
Equipo* traerEquipo(Sistema &sistema, int id);

/*----------------------------------------------------------------------------*/
/*
  pre:
  post:
*/
Jugador* traerJugador(Sistema &sistema, int id);

/*----------------------------------------------------------------------------*/
/*
  pre:
  post:
*/
Grupo* traerGrupo(Sistema &sistema, char id);

/*----------------------------------------------------------------------------*/
/*
  pre:
  post:
*/
Partido* traerPartido(Sistema &sistema, int id);

/*----------------------------------------------------------------------------*/
/*
  pre:
  post:
*/
void inicioPartido(Sistema &sistema);

/*----------------------------------------------------------------------------*/
/*
  pre:
  post:
*/
void golesPartido(Sistema &sistema);

/*----------------------------------------------------------------------------*/
/*
  pre:
  post:
*/
void finPartido(Sistema &sistema);

/*----------------------------------------------------------------------------*/
/*
  pre:
  post:
*/
void mostrarPartidosEnCurso(Sistema &sistema);

/*----------------------------------------------------------------------------*/
/*
  pre:
  post:
*/
void porcentajeGoles(Sistema &sistema);

/*----------------------------------------------------------------------------*/
/*
  pre:
  post:
*/
void grupoDeLaMuerte(Sistema &sistema);

/*----------------------------------------------------------------------------*/
/*
  pre:
  post:
*/
bool validar(Sistema& sistema);

/*----------------------------------------------------------------------------*/
/*
  pre:
  post:
*/
void validarEquipo(Lista* equipos,string& warning);

/*----------------------------------------------------------------------------*/
/*
  pre:
  post:
*/
void validarGoles(Lista* equipos,Lista* partidos,string& warning);

/*----------------------------------------------------------------------------*/
/*
  pre:
  post:
*/
void validarEmpates(Lista* partidos,string& warning);

/*----------------------------------------------------------------------------*/
/*
  pre:
  post:
*/
void validarJugadores(Lista* equipos,string& warning);

/*----------------------------------------------------------------------------*/
/*
  pre:
  post:
*/
void validarPuntos(Lista* equipos,Lista* partidos,string& warning);

/*----------------------------------------------------------------------------*/
/*
  pre:
  post:
*/
void validarPartidosFaseInicial(Lista* grupos,Lista* partidos,string& warning);

/*----------------------------------------------------------------------------*/
/*
  pre:
  post:
*/
bool verificarGrupo(Lista* equipos,Equipo* equipo);

/*----------------------------------------------------------------------------*/
/*
  pre:
  post:
*/
void validarPartidosFaseFinal(Lista* partidos,string& warning);

/*----------------------------------------------------------------------------*/
/*
  pre:
  post:
*/
void setearFases(Sistema &sistema);

#endif // _SISTEMA_H_
