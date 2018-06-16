#include <iostream>
#include <sstream>
using namespace std;

#include "Lista.h"
#include "Jugador.h"
#include "Equipo.h"
#include "Partido.h"

void crear(Partido &partido) {
    partido.id = 0;
    crear(*partido.equipoL);
    crear(*partido.equipoV);
    partido.golesL = 0;
    partido.golesV = 0;
    partido.estado = SIN_COMENZAR;
}

void crear(Partido &partido, int id, Equipo *equipoL, Equipo *equipoV, int golesL, int golesV) {
    partido.id = id;
    partido.equipoL = equipoL;
    partido.equipoV = equipoV;
    partido.golesL = golesL;
    partido.golesV = golesV;
    partido.estado = SIN_COMENZAR;
}

void destruir(Partido &partido) {
    partido.id = 0;
    destruir(*partido.equipoL);
    destruir(*partido.equipoV);
    partido.golesL = 0;
    partido.golesV = 0;
    partido.estado = FINALIZADO;
}

void setId(Partido &partido, int id) {
    partido.id = id;
}

int getId(Partido &partido) {
    return partido.id;
}

void setEquipoL(Partido &partido, Equipo *equipoL) {
    partido.equipoL = equipoL;
}

Equipo* getEquipoL(Partido &partido) {
    return partido.equipoL;
}

void setEquipoV(Partido &partido, Equipo *equipoV) {
    partido.equipoV = equipoV;
}

Equipo* getEquipoV(Partido &partido) {
    return partido.equipoV;
}

void setGolesL(Partido &partido, int golesL) {
    partido.golesL = golesL;
}

int getGolesL(Partido &partido) {
    return partido.golesL;
}

void setGolesV(Partido &partido, int golesV) {
    partido.golesV = golesV;
}

int getGolesV(Partido &partido) {
    return partido.golesV;
}

void setEstado(Partido &partido, Estado estado) {
    partido.estado = estado;
}

Estado getEstado(Partido &partido) {
    return partido.estado;
}

bool equals(Partido &partido, Partido p) {
    return partido.id == p.id;
}

string toString(Partido &partido) {
    string dato="NULL\n";
    if(getId(partido)>0){
        ostringstream convert;
        convert << getId(partido);
        dato="Id: "+convert.str()+"\n";
        dato+=getNombre(*partido.equipoL)+" ";
        ostringstream convert2;
        convert2 << getGolesL(partido);
        dato+=convert2.str()+"\n";
        dato+=getNombre(*partido.equipoV)+" ";
        ostringstream convert3;
        convert3 << getGolesV(partido);
        dato+=convert3.str()+"\n";
    }
    return dato;
}
