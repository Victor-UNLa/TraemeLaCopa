#include <iostream>
using namespace std;

#include "Lista.h"
#include "Jugador.h"
#include "Equipo.h"
#include "Grupo.h"

ResultadoComparacion compararIdG(PtrDato ptrDato1, PtrDato ptrDato2) {
    if (getId(*(Equipo*)ptrDato1) > getId(*(Equipo*)ptrDato2))
        return MAYOR;

    else if (getId(*(Equipo*)ptrDato1) < getId(*(Equipo*)ptrDato2))
        return MENOR;

    else
        return IGUAL;
}

void crear(Grupo &grupo) {
    grupo.id = '0';
    grupo.nombre = "";
    grupo.equipos = new Lista;
    crearLista(*grupo.equipos, compararIdG);
}

void crear(Grupo &grupo, char id, string nombre, Lista *equipos) {
    grupo.id = id;
    grupo.nombre = nombre;
    grupo.equipos = equipos;
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
    cout << "Id: " << grupo.id << endl;
    cout << "Nombre: " << grupo.nombre << endl;

    PtrNodoLista cursor = primero(*grupo.equipos);
    while (cursor != fin()) {
        cout << getNombre(*(Equipo*)cursor->ptrDato) << " - ";
        cursor = siguiente(*grupo.equipos, cursor);
    }
    cout << endl;
}
