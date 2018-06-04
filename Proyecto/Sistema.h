#ifndef _SISTEMA_H_
#define _SISTEMA_H_

typedef struct {
    Lista *equipos;
    Lista *jugadores;
    Lista *grupos;
    Lista *partidos;
} Sistema;

void crear(Sistema &sistema);
void destruir(Sistema &sistema);
void levantarEquipos(Sistema &sistema);
void levantarJugadores(Sistema &sistema);
void levantarGrupos(Sistema &sistema);
void levantarPartidos(Sistema &sistema);
void mostrarEquipos(Sistema &sistema);
void mostrarJugadores(Sistema &sistema);
void mostrarGrupos(Sistema &sistema);
void mostrarPartidos(Sistema &sistema);
void bajarEquipos(Sistema &sistema);
void bajarJugadores(Sistema &sistema);
void bajarGrupos(Sistema &sistema);
void bajarPartidos(Sistema &sistema);
Equipo* traerEquipoPorJugador(Sistema &sistema, int id);
Equipo* traerEquipo(Sistema &sistema, int id);
Jugador* traerJugador(Sistema &sistema, int id);
Grupo* traerGrupo(Sistema &sistema, char id);
Partido* traerPartido(Sistema &sistema, int id);

#endif // _SISTEMA_H_
