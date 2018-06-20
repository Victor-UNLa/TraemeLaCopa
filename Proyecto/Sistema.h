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
void goleadores(Sistema &sistema);
void bajarEquipos(Sistema &sistema);
void bajarJugadores(Sistema &sistema);
void bajarGrupos(Sistema &sistema);
void bajarPartidos(Sistema &sistema);
Equipo* traerEquipoPorJugador(Sistema &sistema, int id);
Equipo* traerEquipo(Sistema &sistema, int id);
Jugador* traerJugador(Sistema &sistema, int id);
Grupo* traerGrupo(Sistema &sistema, char id);
Partido* traerPartido(Sistema &sistema, int id);
void inicioPartido(Sistema &sistema);
void golesPartido(Sistema &sistema);
void finPartido(Sistema &sistema);
void mostrarPartidosEnCurso(Sistema &sistema);
void porcentajeGoles(Sistema &sistema);
void grupoDeLaMuerte(Sistema &sistema);

bool validar(Sistema& sistema);
void validarEquipo(Lista* equipos,string& warning);
void validarGoles(Lista* equipos,Lista* partidos,string& warning);
void validarEmpates(Lista* partidos,string& warning);
void validarJugadores(Lista* equipos,string& warning);
void validarPuntos(Lista* equipos,Lista* partidos,string& warning);
void validarPartidosFaseInicial(Lista* grupos,Lista* partidos,string& warning);
void validarPartidosFaseFinal(Lista* partidos,string& warning);
void setearFases(Sistema &sistema);

#endif // _SISTEMA_H_
