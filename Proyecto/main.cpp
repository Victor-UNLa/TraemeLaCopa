#include <iostream>
using namespace std;
#include <stdlib.h>
#include "Lista.h"
#include "Jugador.h"
#include "Equipo.h"
#include "Grupo.h"
#include "Partido.h"
#include "Sistema.h"

void ABM(Sistema &sistema) {
    mostrarEquipos(sistema);
}

void admPartidos(Sistema &sistema) {
    mostrarPartidos(sistema);

    int id;
    cout << "Traer partido por id: ";
    cin >> id;
    toString(*traerPartido(sistema, id));

    int golL, golV;
    cout << "\nGoles del equipo local: ";
    cin >> golL;
    cout << "Goles del equipo visitante: ";
    cin >> golV;
    cout << endl;

    setGolesL(*traerPartido(sistema, id), golL);
    setGolesV(*traerPartido(sistema, id), golV);

    toString(*traerPartido(sistema, id));
}

void reportes(Sistema &sistema) {
    int id;
    cout << "Traer equipo por id del jugador: ";
    cin >> id;
    toString(*traerEquipoPorJugador(sistema, id));
}

void menu(Sistema &sistema) {
    bool seguir = true;
    int opcion;

    void (*funcion[3])(Sistema &sistema);
    funcion[0] = ABM;
    funcion[1] = admPartidos;
    funcion[2] = reportes;

    while(seguir) {
        cout << "1. Altas, Bajas y Modificaciones." << endl;
        cout << "2. Administrar partidos." << endl;
        cout << "3. Procesar reportes." << endl;
        cout << "4. Salir." << endl;
        cin >> opcion;

        switch(opcion) {
            default: if(opcion > 0 && opcion <= 3) funcion[opcion - 1] (sistema); break;
            case 4: seguir = false; break;
        }
        system("pause");
        system("cls");
    }
}

int main() {
    Sistema *sistema = new Sistema;
    crear(*sistema);

    levantarEquipos(*sistema);
    levantarJugadores(*sistema);
    levantarGrupos(*sistema);
    levantarPartidos(*sistema);

    menu(*sistema);

    bajarEquipos(*sistema);
    bajarJugadores(*sistema);
    bajarGrupos(*sistema);
    bajarPartidos(*sistema);

    destruir(*sistema);
    delete sistema;

    return 0;
}
