#ifndef _EQUIPO_H_
#define _EQUIPO_H_

typedef struct {
    int id;
    string nombre;
    int golesAFavor;
    int golesEnContra;
    int puntos;
    Lista *jugadores;
} Equipo;

void crear(Equipo &equipo);
void crear(Equipo &equipo, int id, string nombre, int golesAFavor, int golesEnContra, int puntos);
void destruir(Equipo &equipo);
void setId(Equipo &equipo, int id);
int getId(Equipo &equipo);
void setNombre(Equipo &equipo, string nombre);
string getNombre(Equipo &equipo);
void setGolesAFavor(Equipo &equipo, int golesAFavor);
int getGolesAFavor(Equipo &equipo);
void setGolesEnContra(Equipo &equipo, int golesEnContra);
int getGolesEnContra(Equipo &equipo);
void setPuntos(Equipo &equipo, int puntos);
int getPuntos(Equipo &equipo);
void setJugadores(Equipo &equipo, Lista *jugadores);
void setJugadores(Equipo &equipo, Jugador *jugador);
Lista* getJugadores(Equipo &equipo);
bool equals(Equipo &equipo, Equipo e);
void toString(Equipo &equipo);

#endif // _EQUIPO_H_
