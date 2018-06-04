#include <iostream>
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
}

void crear(Partido &partido, int id, Equipo *equipoL, Equipo *equipoV, int golesL, int golesV) {
    partido.id = id;
    partido.equipoL = equipoL;
    partido.equipoV = equipoV;
    partido.golesL = golesL;
    partido.golesV = golesV;
}

void destruir(Partido &partido) {
    partido.id = 0;
    destruir(*partido.equipoL);
    destruir(*partido.equipoV);
    partido.golesL = 0;
    partido.golesV = 0;
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

bool equals(Partido &partido, Partido p) {
    return partido.id == p.id;
}

void toString(Partido &partido) {
    cout << "Id: " << partido.id << endl;
    cout << getNombre(*partido.equipoL) << " " << partido.golesL << endl;
    cout << getNombre(*partido.equipoV) << " " << partido.golesV << endl;
}
