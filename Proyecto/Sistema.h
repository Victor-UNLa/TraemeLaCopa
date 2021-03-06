#ifndef _SISTEMA_H_
#define _SISTEMA_H_
/**
    Axiomas:

    * No se podr� usar el programa hasta que los datos ingresados
    est�n validados correctamente.
    * Se considera de mayor prioridad los TDA Partido
    para las "validaciones".
    * Se debe completar la fase de partidos en estado finalizados
    para que se validen la siguiente etapa.
    * Se debe finalizar el partido en curso en la opci�n
    Administrar partidos, para una correcta carga de puntos para los Equipos.
    * Los golesAFavor del Equipo se validan con la suma de
    goles de sus jugadores

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
void validarFaseClasificion(Sistema& sistema,string& warning);
void validarClasificacionOctavos(Sistema& s,string& warning);
void validarClasificacionCuartos(Sistema& s,string& warning);
void verificarOctavosDeFinal(Sistema& s,string& warning);
void validarPartidosFaseFinal(Lista* partidos,Sistema& sistema,string& warning);
void validarPartidoCerrados(Sistema& s,string& warning);
bool verificarGrupo(Lista* equipos,Equipo* equipo);
bool verificarContinuidadEquipo(Lista* partidos,PtrNodoLista cursor,Equipo* equipo);
bool verificarPartido(Sistema& sistema,Equipo* equipo,int id);
bool verificarPartidos(Lista* partidos,int i,int f);
bool verificarVictoriaDifGoles(Equipo& e,Lista* equipos,Lista* partidos);
bool verificarVictoriaPuntos(Equipo& e,Lista* equipos);
bool localizar(Equipo* equipo,Sistema& s,int i,int f);
bool isPartidoCreado(Partido* p);
bool isPartidoJugado(Partido* p);
bool isEmpate(Partido* p);
void mostrarTablaPosiciones(Sistema &sistema);
int diferenciaDeGoles(Lista* partidos,Equipo& e,int i,int f);
int traerGolesAFavor(Lista* partidos,Equipo& e,int i,int f);
int traerGolesEnContra(Lista* partidos,Equipo& e,int i,int f);
void ordenarEquiposDeGrupos(Lista& grupos);
Equipo* traerGanador(Partido* p);
Equipo* traerPerdedor(Partido* p);
Equipo** traerGanadores(Lista* equipos,Lista* partidos);
void setearFases(Sistema &sistema);

#endif // _SISTEMA_H_
