#ifndef _PARTIDO_H_
#define _PARTIDO_H_

enum Estado {SIN_COMENZAR, EN_JUEGO, FINALIZADO};

typedef struct {
    int id;
    Equipo *equipoL;
    Equipo *equipoV;
    int golesL;
    int golesV;
    Estado estado;
} Partido;

void crear(Partido &partido);
void crear(Partido &partido, int id, Equipo *equipoL, Equipo *equipoV, int golesL, int golesV);
void destruir(Partido &partido);
void setId(Partido &partido, int id);
int getId(Partido &partido);
void setEquipoL(Partido &partido, Equipo *equipoL);
Equipo* getEquipoL(Partido &partido);
void setEquipoV(Partido &partido, Equipo *equipoV);
Equipo* getEquipoV(Partido &partido);
void setGolesL(Partido &partido, int golesL);
int getGolesL(Partido &partido);
void setGolesV(Partido &partido, int golesV);
int getGolesV(Partido &partido);
void setEstado(Partido &partido, Estado estado);
Estado getEstado(Partido &partido);
bool equals(Partido &partido, Partido p);
void toString(Partido &partido);

#endif // _PARTIDO_H_
