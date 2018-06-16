#include <iostream>
#include <sstream>
using namespace std;

#include "Lista.h"
#include "Jugador.h"
#include "Equipo.h"

ResultadoComparacion compararIdE(PtrDato ptrDato1, PtrDato ptrDato2) {
    if (getId(*(Equipo*)ptrDato1) > getId(*(Equipo*)ptrDato2))
        return MAYOR;

    else if (getId(*(Equipo*)ptrDato1) < getId(*(Equipo*)ptrDato2))
        return MENOR;

    else
        return IGUAL;
}

void crear(Equipo &equipo) {
    equipo.id = 0;
    equipo.nombre = "";
    equipo.golesAFavor = 0;
    equipo.golesEnContra = 0;
    equipo.puntos = 0;
    equipo.jugadores = new Lista;
    crearLista(*equipo.jugadores, compararIdE);
}

void crear(Equipo &equipo, int id, string nombre, int golesAFavor, int golesEnContra, int puntos) {
    equipo.id = id;
    equipo.nombre = nombre;
    equipo.golesAFavor = golesAFavor;
    equipo.golesEnContra = golesEnContra;
    equipo.puntos = puntos;
    equipo.jugadores = new Lista;
    crearLista(*equipo.jugadores, compararIdE);
}

void destruir(Equipo &equipo) {
    equipo.id = 0;
    equipo.nombre = "";
    equipo.golesAFavor = 0;
    equipo.golesEnContra = 0;
    equipo.puntos = 0;
    eliminarLista(*equipo.jugadores);
}

void setId(Equipo &equipo, int id) {
    equipo.id = id;
}

int getId(Equipo &equipo) {
    return equipo.id;
}

void setNombre(Equipo &equipo, string nombre) {
    equipo.nombre = nombre;
}

string getNombre(Equipo &equipo) {
    return equipo.nombre;
}

void setGolesAFavor(Equipo &equipo, int golesAFavor) {
    equipo.golesAFavor = golesAFavor;
}

int getGolesAFavor(Equipo &equipo) {
    return equipo.golesAFavor;
}

void setGolesEnContra(Equipo &equipo, int golesEnContra) {
    equipo.golesEnContra = golesEnContra;
}

int getGolesEnContra(Equipo &equipo) {
    return equipo.golesEnContra;
}

void setPuntos(Equipo &equipo, int puntos) {
    equipo.puntos = puntos;
}

int getPuntos(Equipo &equipo) {
    return equipo.puntos;
}

void setJugadores(Equipo &equipo, Lista *jugadores) {
    equipo.jugadores = jugadores;
}

void setJugadores(Equipo &equipo, Jugador *jugador) {
    adicionarFinal(*equipo.jugadores, jugador);
}

Lista* getJugadores(Equipo &equipo) {
    return equipo.jugadores;
}

bool equals(Equipo &equipo, Equipo e) {
    return equipo.id == e.id;
}

string toString(Equipo &equipo) {
    string dato="NULL\n";
    if(getId(equipo)>0){
        dato = "Id: ";
        ostringstream convert;
        convert<<getId(equipo);
        dato+=convert.str()+"\n";
        dato+="Nombre: "+getNombre(equipo)+"\n";
        ostringstream convert2;
        convert2<<getGolesAFavor(equipo);
        dato+="Goles a favor: "+convert2.str()+"\n";
        ostringstream convert3;
        convert3<<getGolesEnContra(equipo);
        dato+="Goles en contra: "+convert3.str()+"\n";
        ostringstream convert4;
        convert4<<getPuntos(equipo);
        dato+="Puntos: "+convert4.str()+"\n";
        PtrNodoLista cursor = primero(*equipo.jugadores);
        while (cursor != fin()) {
            dato+=getNombre(*(Jugador*)cursor->ptrDato)+" || ";
            cursor = siguiente(*equipo.jugadores, cursor);
        }
    }
    return dato;
}
