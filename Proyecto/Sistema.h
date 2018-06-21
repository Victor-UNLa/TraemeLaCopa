#ifndef _SISTEMA_H_
#define _SISTEMA_H_
/**
    Axiomas:
    * No se podrá usar el programa hasta que los datos ingresados
    estén validados correctamente.
    * Se considera de mayor prioridad los TDA Partido
    para las "validaciones".
    * Se debe finalizar el partido en curso en la opción
    Administrar partidos, para una correcta carga de puntos para los Equipos.
*/
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
bool verificarGrupo(Lista* equipos,Equipo* equipo);
void validarPartidosFaseFinal(Lista* partidos,Sistema& sistema,string& warning);
bool verificarContinuidadEquipo(Lista* partidos,PtrNodoLista cursor,Equipo* equipo);
bool verificarPartido(Sistema& sistema,Equipo* equipo,int id);
bool isPartidoCreado(Partido* p);
bool isPartidoJugado(Partido* p);
bool isEmpate(Partido* p);
void mostrarTablaPosiciones(Sistema &sistema);
int diferenciaDeGoles(Equipo& e);
int partidosPerdidos(Lista* partidos,Equipo& e);
int partidosEmpatados(Lista* partidos,Equipo& e);
int partidosGanados(Lista* partidos,Equipo& e);
int partidosJugados(Lista* partidos,Equipo& e);
Equipo* traerGanador(Partido* p);
Equipo* traerPerdedor(Partido* p);
void setearFases(Sistema &sistema);

#endif // _SISTEMA_H_
