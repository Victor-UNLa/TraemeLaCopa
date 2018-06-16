#include <iostream>
#include <sstream>
using namespace std;

#include "Jugador.h"

void crear(Jugador &jugador) {
    jugador.id = 0;
    jugador.nombre = "";
    jugador.goles = 0;
}

void crear(Jugador &jugador, int id, string nombre, int goles) {
    jugador.id = id;
    jugador.nombre = nombre;
    jugador.goles = goles;
}

void destruir(Jugador &jugador) {
    jugador.id = 0;
    jugador.nombre = "";
    jugador.goles = 0;
}

void setId(Jugador &jugador, int id) {
    jugador.id = id;
}

int getId(Jugador &jugador) {
    return jugador.id;
}

void setNombre(Jugador &jugador, string nombre) {
    jugador.nombre = nombre;
}

string getNombre(Jugador &jugador) {
    return jugador.nombre;
}

void setGoles(Jugador &jugador, int goles) {
    jugador.goles = goles;
}

int getGoles(Jugador &jugador) {
    return jugador.goles;
}

bool equals(Jugador &jugador, Jugador j) {
    return jugador.id == j.id;
}

string toString(Jugador &jugador) {
    string dato="NULL\n";
    if(getId(jugador)>0){
        dato="Id: ";
        ostringstream convert;
        convert<<getId(jugador);
        dato+=convert.str()+"\n";
        dato+="Nombre: "+getNombre(jugador)+"\n";
        ostringstream convert2 ;
        convert2<<getGoles(jugador);
        dato+="Goles: "+convert2.str()+"\n";
    }
    return dato;
}

