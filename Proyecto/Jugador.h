#ifndef _JUGADOR_H_
#define _JUGADOR_H_

typedef struct {
    int id;
    string nombre;
    int goles;
} Jugador;

void crear(Jugador &jugador);
void crear(Jugador &jugador, int id, string nombre, int goles);
void destruir(Jugador &jugador);
void setId(Jugador &jugador, int id);
int getId(Jugador &jugador);
void setNombre(Jugador &jugador, string nombre);
string getNombre(Jugador &jugador);
void setGoles(Jugador &jugador, int goles);
int getGoles(Jugador &jugador);
bool equals(Jugador &jugador, Jugador j);
void toString(Jugador &jugador);

#endif // _JUGADOR_H_
