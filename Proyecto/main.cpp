#include <iostream>
using namespace std;
#include <stdlib.h>
#include "Lista.h"
#include "Jugador.h"
#include "Equipo.h"
#include "Grupo.h"
#include "Partido.h"
#include "Sistema.h"

void admPartidos(Sistema &sistema) {
    bool seguir = true;
    int opcion;
    system("cls");
    while(seguir) {
        cout << "1. Registrar inicio de partido." << endl;
        cout << "2. Registrar goles de partido." << endl;
        cout << "3. Registrar fin de partido." << endl;
        cout << "4. Mostrar partidos en curso." << endl;
        cout << "5. Volver." << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1: inicioPartido(sistema); break;
            case 2: golesPartido(sistema); break;
            case 3: finPartido(sistema); break;
            case 4: mostrarPartidosEnCurso(sistema); break;
            case 5: seguir = false; break;
        }
        system("pause");
        system("cls");
    }
}

void reportes(Sistema &sistema) {
    bool seguir = true;
    int opcion;
    system("cls");
    while(seguir) {
        cout << "1. Mostrar goleadores." << endl;
        cout << "2. Mostrar fixture." << endl;
        cout << "3. Mostrar grupos." << endl;
        cout << "4. Volver." << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1: goleadores(sistema); break;
            case 2: mostrarPartidos(sistema); break;
            case 3: mostrarGrupos(sistema); break;
            case 4: seguir = false; break;
        }
        system("pause");
        system("cls");
    }
}

void menu(Sistema &sistema) {
    bool seguir = true;
    int opcion;

    while(seguir) {
        cout << "1. Mostrar equipos." << endl;
        cout << "2. Administrar partidos." << endl;
        cout << "3. Procesar reportes." << endl;
        cout << "4. Salir." << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1: mostrarEquipos(sistema); system("pause"); break;
            case 2: admPartidos(sistema); break;
            case 3: reportes(sistema); break;
            case 4: seguir = false; break;
        }
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
