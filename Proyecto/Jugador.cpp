#include <iostream>
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

void toString(Jugador &jugador) {
    cout << "Id: " << jugador.id << endl;
    cout << "Nombre: " << jugador.nombre<< endl;
    cout << "Goles: " << jugador.goles << endl;
}

