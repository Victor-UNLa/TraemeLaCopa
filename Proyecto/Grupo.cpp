#include <iostream>
using namespace std;

#include "Lista.h"
#include "Jugador.h"
#include "Equipo.h"
#include "Grupo.h"

ResultadoComparacion compararPuntos(PtrDato ptrDato1, PtrDato ptrDato2) {
    if (getPuntos(*(Equipo*)ptrDato1) < getPuntos(*(Equipo*)ptrDato2))
        return MAYOR;

    else if (getPuntos(*(Equipo*)ptrDato1) > getPuntos(*(Equipo*)ptrDato2))
        return MENOR;

    else {
        if (getGolesAFavor(*(Equipo*)ptrDato1) -  getGolesEnContra(*(Equipo*)ptrDato1)
            < getGolesAFavor(*(Equipo*)ptrDato2) - getGolesEnContra(*(Equipo*)ptrDato2))
            return MAYOR;

        else if (getGolesAFavor(*(Equipo*)ptrDato1) -  getGolesEnContra(*(Equipo*)ptrDato1)
            > getGolesAFavor(*(Equipo*)ptrDato2) - getGolesEnContra(*(Equipo*)ptrDato2))
            return MENOR;
        else {
            if (getGolesAFavor(*(Equipo*)ptrDato1) < getGolesAFavor(*(Equipo*)ptrDato2))
                return MAYOR;

            else if (getGolesAFavor(*(Equipo*)ptrDato1) > getGolesAFavor(*(Equipo*)ptrDato2))
                return MENOR;

            else
                return IGUAL;
        }
    }
}

void crear(Grupo &grupo) {
    grupo.id = '0';
    grupo.nombre = "";
    grupo.equipos = new Lista;
    crearLista(*grupo.equipos, compararPuntos);
}

void crear(Grupo &grupo, char id, string nombre, Lista *equipos) {
    grupo.id = id;
    grupo.nombre = nombre;
    grupo.equipos = equipos;
    grupo.equipos->compara = compararPuntos;
}

void destruir(Grupo &grupo) {
    grupo.id = '0';
    grupo.nombre = "";
    eliminarLista(*grupo.equipos);
}

void setId(Grupo &grupo, char id) {
    grupo.id = id;
}

char getId(Grupo &grupo) {
    return grupo.id;
}

void setNombre(Grupo &grupo, string nombre) {
    grupo.nombre = nombre;
}

string getNombre(Grupo &grupo) {
    return grupo.nombre;
}

void setEquipos(Grupo &grupo, Lista *equipos) {
    grupo.equipos = equipos;
}

Lista* getEquipos(Grupo &grupo) {
    return grupo.equipos;
}

bool equals(Grupo &grupo, Grupo g) {
    return grupo.id == g.id;
}

void toString(Grupo &grupo) {
    cout << grupo.nombre << endl;
    cout << "Pos" << "\t||" << "Dif" << " \t|| " << "Pun" << " \t|| " << "Equipo" << endl;
    cout << "------------------------------------------" << endl;
    reordenar(*grupo.equipos);
    PtrNodoLista cursor = primero(*grupo.equipos);
    int i = 1;

    while (cursor != fin()) {
        cout << i << " \t||";
        cout << getGolesAFavor(*(Equipo*)cursor->ptrDato) - getGolesEnContra(*(Equipo*)cursor->ptrDato) << " \t|| ";
        cout << getPuntos(*(Equipo*)cursor->ptrDato) << " \t|| ";
        cout << getNombre(*(Equipo*)cursor->ptrDato) << endl;
        i++;
        cursor = siguiente(*grupo.equipos, cursor);
    }

    cout << "Goles del grupo: " << golesPorGrupo(grupo) << endl;
    cout << endl;
}

int golesPorGrupo(Grupo &grupo) {
    PtrNodoLista cursor = primero(*grupo.equipos);
    int golesDelGrupo = 0;

    while (cursor != fin()) {
        golesDelGrupo += getGolesAFavor(*(Equipo*)cursor->ptrDato);
        cursor = siguiente(*grupo.equipos, cursor);
    }

    return golesDelGrupo;
}
