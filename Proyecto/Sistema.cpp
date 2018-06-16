#include <fstream>
#include <cstring>
#include <cstdlib>
#include <windows.h>
#include <iostream>
using namespace std;
#include "Lista.h"
#include "Jugador.h"
#include "Equipo.h"
#include "Grupo.h"
#include "Partido.h"
#include "Sistema.h"

ResultadoComparacion compararGoles(PtrDato ptrDato1, PtrDato ptrDato2) {
    if (getGoles(*(Jugador*)ptrDato1) < getGoles(*(Jugador*)ptrDato2))
        return MAYOR;

    else if (getGoles(*(Jugador*)ptrDato1) > getGoles(*(Jugador*)ptrDato2))
        return MENOR;

    else
        return IGUAL;
}

ResultadoComparacion compararEquipo(PtrDato ptrDato1, PtrDato ptrDato2) {
    if (getId(*(Equipo*)ptrDato1) > getId(*(Equipo*)ptrDato2))
        return MAYOR;

    else if (getId(*(Equipo*)ptrDato1) < getId(*(Equipo*)ptrDato2))
        return MENOR;

    else
        return IGUAL;
}

ResultadoComparacion compararJugador(PtrDato ptrDato1, PtrDato ptrDato2) {
    if (getId(*(Jugador*)ptrDato1) > getId(*(Jugador*)ptrDato2))
        return MAYOR;

    else if (getId(*(Jugador*)ptrDato1) < getId(*(Jugador*)ptrDato2))
        return MENOR;

    else
        return IGUAL;
}

ResultadoComparacion compararGrupo(PtrDato ptrDato1, PtrDato ptrDato2) {
    if (getId(*(Grupo*)ptrDato1) > getId(*(Grupo*)ptrDato2))
        return MAYOR;

    else if (getId(*(Grupo*)ptrDato1) < getId(*(Grupo*)ptrDato2))
        return MENOR;

    else
        return IGUAL;
}

ResultadoComparacion compararPartido(PtrDato ptrDato1, PtrDato ptrDato2) {
    if (getId(*(Partido*)ptrDato1) > getId(*(Partido*)ptrDato2))
        return MAYOR;

    else if (getId(*(Partido*)ptrDato1) < getId(*(Partido*)ptrDato2))
        return MENOR;

    else
        return IGUAL;
}

void crear(Sistema &sistema) {
    sistema.equipos = new Lista;
    crearLista(*sistema.equipos, compararEquipo);
    sistema.jugadores = new Lista;
    crearLista(*sistema.jugadores, compararJugador);
    sistema.grupos = new Lista;
    crearLista(*sistema.grupos, compararGrupo);
    sistema.partidos = new Lista;
    crearLista(*sistema.partidos, compararPartido);
}

void destruir(Sistema &sistema) {
    eliminarLista(*sistema.equipos);
    eliminarLista(*sistema.jugadores);
    eliminarLista(*sistema.grupos);
    eliminarLista(*sistema.partidos);
}

void levantarEquipos(Sistema &sistema) {
    ifstream archivo;

    archivo.open("archivos/equipos.txt", ios::in);

    if(archivo.fail()) {
        cout << "Error al abrir el archivo" << endl;
        exit(1);
    }

    string id, nombre, golesAFavor, golesEnContra, puntos;

    int vectorValidar[32];
    int i = 0;

    while (!archivo.eof()) {
        getline(archivo, id, ';');
        getline(archivo, nombre, ';');
        getline(archivo, golesAFavor, ';');
        getline(archivo, golesEnContra, ';');
        getline(archivo, puntos);

        Equipo *e = new Equipo;
        if(atoi(id.c_str())<=0){
            cout << "Error el equipo tiene el id negativo"<< endl;
            cout << "No se puede cargar el equipo:" << nombre<< endl;
        }

        for (int indice=0; indice<i; indice++){
            if (vectorValidar[indice]==atoi(id.c_str())){
                cout << "Error el id:  " << atoi(id.c_str()) << " esta repetido"<<endl;
                cout << "No se puede cargar el equipo:" << nombre<< endl;
            }
        }

        vectorValidar[i] = atoi(id.c_str());
        i = i +1;
        crear(*e, atoi(id.c_str()), nombre, atoi(golesAFavor.c_str()), atoi(golesEnContra.c_str()), atoi(puntos.c_str()));
        adicionarFinal(*sistema.equipos, e);
    }

    reordenar(*sistema.equipos);

    archivo.close();
}

void levantarJugadores(Sistema &sistema) {
    ifstream archivo;

    archivo.open("archivos/jugadores.txt", ios::in);

    if(archivo.fail()) {
        cout << "Error al abrir el archivo" << endl;
        exit(1);
    }

    string id, nombre, goles, equipo;

    int vectorValidar[100];
    int i = 0;
    bool error = false;

    while (!archivo.eof()) {
        getline(archivo, id, ';');
        getline(archivo, nombre, ';');
        getline(archivo, goles, ';');
        getline(archivo, equipo);

        Jugador *j = new Jugador;
        if(atoi(id.c_str())<=0){
            cout << "Error el jugador tiene el id negativo"<< endl;
            cout << "No se puede cargar el jugador:" << nombre<< endl;
            system("pause");
            exit(0);
        }

        for (int indice=0; indice<i; indice++){
            if (vectorValidar[indice]==atoi(id.c_str())){
                cout << "Error el id:  " << atoi(id.c_str()) << " esta repetido"<<endl;
                cout << "No se puede cargar el jugador:" << nombre<< endl;
                system("pause");
                exit(0);
            }
        }

        vectorValidar[i] = atoi(id.c_str());
        i = i +1;
        crear(*j, atoi(id.c_str()), nombre, atoi(goles.c_str()));

        setJugadores(*traerEquipo(sistema, atoi(equipo.c_str())), j);

        adicionarFinal(*sistema.jugadores, j);
    }

    reordenar(*sistema.jugadores);

    archivo.close();
}

void levantarGrupos(Sistema &sistema) {
    ifstream archivo;

    archivo.open("archivos/grupos.txt", ios::in);

    if(archivo.fail()) {
        cout << "Error al abrir el archivo" << endl;
        exit(1);
    }

    string id, nombre, e1, e2, e3, e4;
    bool flag=false;

    while (!archivo.eof()) {
        getline(archivo, id, ';');
        getline(archivo, nombre, ';');
        getline(archivo, e1, ';');
        getline(archivo, e2, ';');
        getline(archivo, e3, ';');
        getline(archivo, e4);

        /** Validacion para saber si todos los grupos estan completos*/
        if(e1=="" || e2=="" || e3=="" || e4==""){
            cout<<"Al grupo "<<id<<" le falta algun equipo"<<endl;
            flag=true;
        }

        /** Validacion para que no haya dos ids iguales en el mismo grupo */
        if(atoi(e1.c_str())==atoi(e2.c_str()) || atoi(e1.c_str())== atoi(e3.c_str()) || atoi(e1.c_str())==atoi(e4.c_str())){
            cout<<"El grupo: "<<id<<" tiene dos equipos con el id: "<<atoi(e1.c_str())<<endl;
            flag=true;
        }
        if(atoi(e2.c_str())==atoi(e3.c_str()) || atoi(e2.c_str())==atoi(e4.c_str())){
            cout<<"El grupo: "<<id<<" tiene dos equipos con el id: "<<atoi(e2.c_str())<<endl;
            flag=true;
        }
        if(atoi(e3.c_str())==atoi(e4.c_str())){
            cout<<"El grupo: "<<id<<" tiene dos equipos con el id: "<<atoi(e3.c_str())<<endl;
            flag=true;
        }

        /** Validacion de que no haya dos equipos con el mismo id en distintos grupos*/
        PtrNodoLista cursor = primero(*sistema.grupos);
        while(cursor!=fin()){
            PtrNodoLista cursor2 = primero(*(getEquipos(*(Grupo*)cursor->ptrDato)));
            if(id[0]==getId(*(Grupo*)cursor->ptrDato)){
                cout<<"hay dos grupos con el id: "<<id<<endl;
                flag=true;
            }
            while(cursor2!=fin()){
                if(atoi(e1.c_str())==getId(*(Equipo*)cursor2->ptrDato)){
                    cout<<"el equipo con id: "<<atoi(e1.c_str())<<" esta cargado en dos grupos distintos"<<endl;
                    flag=true;
                }
                if(atoi(e2.c_str())==getId(*(Equipo*)cursor2->ptrDato)){
                    cout<<"el equipo con id: "<<atoi(e2.c_str())<<" esta cargado en dos grupos distintos"<<endl;
                    flag=true;
                }
                if(atoi(e3.c_str())==getId(*(Equipo*)cursor2->ptrDato)){
                    cout<<"el equipo con id: "<<atoi(e3.c_str())<<" esta cargado en dos grupos distintos"<<endl;
                    flag=true;
                }
                if(atoi(e4.c_str())==getId(*(Equipo*)cursor2->ptrDato)){
                    cout<<"el equipo con id: "<<atoi(e4.c_str())<<" esta cargado en dos grupos distintos"<<endl;
                    flag=true;
                }
                cursor2=siguiente(*(getEquipos(*(Grupo*)cursor->ptrDato)),cursor2);
            }
            cursor=siguiente(*sistema.grupos,cursor);
        }

        Lista *equipos = new Lista;
        crearLista(*equipos, compararEquipo);
        adicionarFinal(*equipos, traerEquipo(sistema, atoi(e1.c_str())));
        adicionarFinal(*equipos, traerEquipo(sistema, atoi(e2.c_str())));
        adicionarFinal(*equipos, traerEquipo(sistema, atoi(e3.c_str())));
        adicionarFinal(*equipos, traerEquipo(sistema, atoi(e4.c_str())));

        Grupo *g = new Grupo;
        crear(*g, id[0], nombre, equipos);
        adicionarFinal(*sistema.grupos, g);
    }

    if(flag==true){
        exit(1);
    }

    reordenar(*sistema.grupos);

    archivo.close();
}

void levantarPartidos(Sistema &sistema) {
    ifstream archivo;

    archivo.open("archivos/partidos.txt", ios::in);

    if(archivo.fail()) {
        cout << "Error al abrir el archivo" << endl;
        exit(1);
    }

    string id, e1, e2, golL, golV;

    int vectorValidar[64];
    int i = 0;

    while (!archivo.eof()) {
        getline(archivo, id, ';');
        getline(archivo, e1, ';');
        getline(archivo, e2, ';');
        getline(archivo, golL, ';');
        getline(archivo, golV);

        if(atoi(id.c_str())<=0){
            cout << "Error el partido tiene el id negativo"<< endl;
            system("pause");
            exit(0);
        }

        for (int indice=0; indice<i; indice++){
            if (vectorValidar[indice]==atoi(id.c_str())){
                cout << "Error el id:  " << atoi(id.c_str()) << " esta repetido"<<endl;
                system("pause");
                exit(0);
            }
        }

        vectorValidar[i] = atoi(id.c_str());
        i = i +1;

        Partido *p = new Partido;
        crear(*p, atoi(id.c_str()),traerEquipo(sistema, atoi(e1.c_str())),traerEquipo(sistema, atoi(e2.c_str())),
              atoi(golL.c_str()),atoi(golV.c_str()));



        /*if((atoi(golL.c_str())!=-1)&&(atoi(golV.c_str())!=-1)){
            setEstado(*p,FINALIZADO);
        }*/



        adicionarFinal(*sistema.partidos, p);
    }

    reordenar(*sistema.partidos);

    archivo.close();
}

void mostrarEquipos(Sistema &sistema) {
    PtrNodoLista cursor = primero(*sistema.equipos);

    while(cursor != fin()) {
        cout << toString(*(Equipo*)cursor->ptrDato)<< endl;
        cout << endl;
        cursor = siguiente(*sistema.equipos, cursor);
    }
}

void mostrarJugadores(Sistema &sistema) {
    PtrNodoLista cursor = primero(*sistema.jugadores);

    while(cursor != fin()) {
        cout << toString(*(Jugador*)cursor->ptrDato);
        cout << endl;
        cursor = siguiente(*sistema.jugadores, cursor);
    }
}

void mostrarGrupos(Sistema &sistema) {
    PtrNodoLista cursor = primero(*sistema.grupos);

    int golesTotales = 0;
    while(cursor != fin()) {
        cout << toString(*(Grupo*)cursor->ptrDato);
        golesTotales += golesPorGrupo(*(Grupo*)cursor->ptrDato);
        cout << endl;
        cursor = siguiente(*sistema.grupos, cursor);
    }
    cout << "Total de goles: " << golesTotales << endl;
}

void mostrarPartidos(Sistema &sistema) {
    PtrNodoLista cursor = primero(*sistema.partidos);

    while(cursor != fin()) {
        if (getGolesL(*(Partido*)cursor->ptrDato) != -1) {
            cout << toString(*(Partido*)cursor->ptrDato)<< endl;
            cout << endl;
        }
        cursor = siguiente(*sistema.partidos, cursor);
    }
}

void goleadores(Sistema &sistema) {
    sistema.jugadores->compara = compararGoles;
    reordenar(*sistema.jugadores);
    PtrNodoLista cursor = primero(*sistema.jugadores);
    int goles = getGoles(*(Jugador*)cursor->ptrDato);
    int jugadoresPorGol = 0;
    int totalDeJugadores = 0;
    int totalDeGoles = 0;

    if (goles != 0) {
        cout << "Jugadores con " << goles << " goles\n" << endl;
        while (cursor != fin()) {
            if (goles > getGoles(*(Jugador*)cursor->ptrDato)) {
                cout << "Cantidad de jugadores: " << jugadoresPorGol << "\n" << endl;
                jugadoresPorGol = 0;
                goles = getGoles(*(Jugador*)cursor->ptrDato);
                if (goles == 0) {
                    cout << "\n\nTotal de jugadores: " << totalDeJugadores << endl;
                    cout << "Total de goles: " << totalDeGoles << endl;
                    break;
                }
                cout << "\nJugadores con " << goles << " goles\n" << endl;
            }
            totalDeJugadores++;
            totalDeGoles += getGoles(*(Jugador*)cursor->ptrDato);
            jugadoresPorGol++;
            cout << "\t-" << getNombre(*(Jugador*)cursor->ptrDato) << endl;
            cursor = siguiente(*sistema.jugadores, cursor);
            cout << endl;
        }
    }
}

void bajarEquipos(Sistema &sistema) {
    ofstream archivo;

    archivo.open("archivos/equipos.txt", ios::out);

    if(archivo.fail()) {
        cout << "Error al abrir el archivo" << endl;
        exit(1);
    }

    PtrNodoLista cursor = primero(*sistema.equipos);
    while (siguiente(*sistema.equipos, cursor) != fin()) {
        archivo << getId(*(Equipo*)cursor->ptrDato) << ";" << getNombre(*(Equipo*)cursor->ptrDato) << ";" <<
        getGolesAFavor(*(Equipo*)cursor->ptrDato) << ";" << getGolesEnContra(*(Equipo*)cursor->ptrDato) << ";" <<
        getPuntos(*(Equipo*)cursor->ptrDato) << endl;
        cursor = siguiente(*sistema.equipos, cursor);
    }

    archivo << getId(*(Equipo*)cursor->ptrDato) << ";" << getNombre(*(Equipo*)cursor->ptrDato) << ";" <<
    getGolesAFavor(*(Equipo*)cursor->ptrDato) << ";" << getGolesEnContra(*(Equipo*)cursor->ptrDato) << ";" <<
    getPuntos(*(Equipo*)cursor->ptrDato);

    archivo.close();
}

void bajarJugadores(Sistema &sistema) {
    ofstream archivo;

    archivo.open("archivos/jugadores.txt", ios::out);

    if(archivo.fail()) {
        cout << "Error al abrir el archivo" << endl;
        exit(1);
    }

    PtrNodoLista cursor = primero(*sistema.jugadores);
    while (siguiente(*sistema.jugadores, cursor) != fin()) {
        archivo << getId(*(Jugador*)cursor->ptrDato) << ";" << getNombre(*(Jugador*)cursor->ptrDato) << ";" <<
        getGoles(*(Jugador*)cursor->ptrDato) << ";" << getId(*traerEquipoPorJugador(sistema, getId(*(Jugador*)cursor->ptrDato))) << endl;
        cursor = siguiente(*sistema.jugadores, cursor);
    }

    archivo << getId(*(Jugador*)cursor->ptrDato) << ";" << getNombre(*(Jugador*)cursor->ptrDato) << ";" <<
    getGoles(*(Jugador*)cursor->ptrDato) << ";" << getId(*traerEquipoPorJugador(sistema, getId(*(Jugador*)cursor->ptrDato)));

    archivo.close();
}

void bajarGrupos(Sistema &sistema) {
    ofstream archivo;

    archivo.open("archivos/grupos.txt", ios::out);

    if(archivo.fail()) {
        cout << "Error al abrir el archivo" << endl;
        exit(1);
    }

    PtrNodoLista cursor = primero(*sistema.grupos);
    while (siguiente(*sistema.grupos, cursor) != fin()) {
        archivo << getId(*(Grupo*)cursor->ptrDato) << ";" << getNombre(*(Grupo*)cursor->ptrDato);

        Lista *e = getEquipos(*(Grupo*)cursor->ptrDato);
        PtrNodoLista c = primero(*e);
        while (c != fin()) {
            archivo << ";" << getId(*(Equipo*)c->ptrDato);
            c = siguiente(*e, c);
        }
        archivo << endl;

        cursor = siguiente(*sistema.grupos, cursor);
    }

    archivo << getId(*(Grupo*)cursor->ptrDato) << ";" << getNombre(*(Grupo*)cursor->ptrDato);

    Lista *e = getEquipos(*(Grupo*)cursor->ptrDato);
    PtrNodoLista c = primero(*e);
    while (c != fin()) {
        archivo << ";" << getId(*(Equipo*)c->ptrDato);
        c = siguiente(*e, c);
    }

    archivo.close();
}

void bajarPartidos(Sistema &sistema) {
    ofstream archivo;

    archivo.open("archivos/partidos.txt", ios::out);

    if(archivo.fail()) {
        cout << "Error al abrir el archivo" << endl;
        exit(1);
    }

    PtrNodoLista cursor = primero(*sistema.partidos);
    while (siguiente(*sistema.partidos, cursor) != fin()) {
        archivo << getId(*(Partido*)cursor->ptrDato) << ";" << getId(*getEquipoL(*(Partido*)cursor->ptrDato)) << ";" <<
        getId(*getEquipoV(*(Partido*)cursor->ptrDato)) << ";" << getGolesL(*(Partido*)cursor->ptrDato) << ";" <<
        getGolesV(*(Partido*)cursor->ptrDato) << endl;
        cursor = siguiente(*sistema.partidos, cursor);
    }

    archivo << getId(*(Partido*)cursor->ptrDato) << ";" << getId(*getEquipoL(*(Partido*)cursor->ptrDato)) << ";" <<
    getId(*getEquipoV(*(Partido*)cursor->ptrDato)) << ";" << getGolesL(*(Partido*)cursor->ptrDato) << ";" <<
    getGolesV(*(Partido*)cursor->ptrDato);

    archivo.close();
}

Equipo* traerEquipoPorJugador(Sistema &sistema, int id) {
    PtrNodoLista cursor = primero(*sistema.equipos);
    Equipo *e = new Equipo;
    bool encontrado = false;

    while (cursor != fin() && !encontrado) {
        Lista *l = getJugadores(*(Equipo*)cursor->ptrDato);
        PtrNodoLista c = primero(*l);
        while (c != fin() && !encontrado) {
            if (getId(*(Jugador*)c->ptrDato) == id) {
                e = ((Equipo*)cursor->ptrDato);
                encontrado = true;
            }
            c = siguiente(*l, c);
        }

        cursor = siguiente(*sistema.equipos, cursor);
    }

    return e;
}

Equipo* traerEquipo(Sistema &sistema, int id) {
    PtrNodoLista cursor = primero(*sistema.equipos);
    Equipo *e = new Equipo;
    bool encontrado = false;

    while (cursor != fin() && !encontrado) {
        if (getId(*(Equipo*)cursor->ptrDato) == id) {
            e = (Equipo*)cursor->ptrDato;
            encontrado = true;
        }
        cursor = siguiente(*sistema.equipos, cursor);
    }

    return e;
}

bool esOctavos(Sistema &sistema){
    bool bandera=false;
    PtrNodoLista cursor = primero(*sistema.partidos);

    while (cursor != fin()) {
        if(getId(*(Partido*)cursor->ptrDato)<=48){
            if ((getGolesL(*(Partido*)cursor->ptrDato) == -1)&&(getGolesV(*(Partido*)cursor->ptrDato) == -1)) {
                bandera = true;
            }
        }
        cursor = siguiente(*sistema.partidos, cursor);
    }
    return bandera;
}

bool esCuartos(Sistema &sistema){
    bool bandera=false;
    PtrNodoLista cursor = primero(*sistema.partidos);

    while (cursor != fin()) {
        if(getId(*(Partido*)cursor->ptrDato)<=56){
            if ((getGolesL(*(Partido*)cursor->ptrDato) == -1)&&(getGolesV(*(Partido*)cursor->ptrDato) == -1)) {
                bandera = true;
            }
        }
        cursor = siguiente(*sistema.partidos, cursor);
    }
    return bandera;
}

bool esSemis(Sistema &sistema){
    bool bandera=false;
    PtrNodoLista cursor = primero(*sistema.partidos);

    while (cursor != fin()) {
        if(getId(*(Partido*)cursor->ptrDato)<=60){
            if ((getGolesL(*(Partido*)cursor->ptrDato) == -1)&&(getGolesV(*(Partido*)cursor->ptrDato) == -1)) {
                bandera = true;
            }
        }
        cursor = siguiente(*sistema.partidos, cursor);
    }
    return bandera;
}


bool es3erY4to(Sistema &sistema){
    bool bandera=false;
    PtrNodoLista cursor = primero(*sistema.partidos);

    while (cursor != fin()) {
        if(getId(*(Partido*)cursor->ptrDato)<=62){
            if ((getGolesL(*(Partido*)cursor->ptrDato) == -1)&&(getGolesV(*(Partido*)cursor->ptrDato) == -1)) {
                bandera = true;
            }
        }
        cursor = siguiente(*sistema.partidos, cursor);
    }
    return bandera;
}

bool esFinal(Sistema &sistema){
    bool bandera=false;
    PtrNodoLista cursor = primero(*sistema.partidos);

    while (cursor != fin()) {
        if(getId(*(Partido*)cursor->ptrDato)<=63){
            if ((getGolesL(*(Partido*)cursor->ptrDato) == -1)&&(getGolesV(*(Partido*)cursor->ptrDato) == -1)) {
                bandera = true;
            }
        }
        cursor = siguiente(*sistema.partidos, cursor);
    }
    return bandera;
}


void setearFases(Sistema &sistema){
    /*
    bool octavos=false;
    bool cuartos=false;
    bool semi=false;
    bool tercerYcuarto=false;
    bool fina=false;

    cuartos = esCuartos(sistema);
    semi = esSemis(sistema);
    tercerYcuarto = es3erY4to(sistema);
    fina = esFinal(sistema);

    ///comprobacion de cuartos de final
        PtrNodoLista cursor = primero(*sistema.partidos);

        while (cursor != fin()) {
            if(getId(*(Partido*)cursor->ptrDato)<=56){
                if ((getGolesL(*(Partido*)cursor->ptrDato) == -1)&&(getGolesV(*(Partido*)cursor->ptrDato) == -1)) {
                    cuartos = true;
                }
            }
            cursor = siguiente(*sistema.partidos, cursor);
        }
    ///comprobacion semifinal
        PtrNodoLista cursorSemi = primero(*sistema.partidos);

        while (cursorSemi != fin()) {
            if(getId(*(Partido*)cursorSemi->ptrDato)<=60){
                if ((getGolesL(*(Partido*)cursorSemi->ptrDato) == -1)&&(getGolesV(*(Partido*)cursorSemi->ptrDato) == -1)) {
                    semi = true;
                }
            }
            cursorSemi = siguiente(*sistema.partidos, cursorSemi);
        }
        ///comprobacion de tercer y cuarto puesto
            PtrNodoLista cursorTercer = primero(*sistema.partidos);

            while (cursorTercer != fin() ) {
                if(getId(*(Partido*)cursorTercer->ptrDato)<=62){
                    if ((getGolesL(*(Partido*)cursorTercer->ptrDato) == -1)&&(getGolesV(*(Partido*)cursorTercer->ptrDato) == -1)) {
                        tercerYcuarto = true;
                    }
                }
                cursorTercer = siguiente(*sistema.partidos, cursorTercer);
            }

        ///comprobacion de la final
            PtrNodoLista cursorFinal = primero(*sistema.partidos);

            while (cursorFinal != fin()) {
                if(getId(*(Partido*)cursorFinal->ptrDato)<=63){
                    if ((getGolesL(*(Partido*)cursorFinal->ptrDato) == -1)&&(getGolesV(*(Partido*)cursorFinal->ptrDato) == -1)) {
                        fina = true;
                    }
                }
                cursorFinal = siguiente(*sistema.partidos, cursorFinal);
            }
    */
    if(!esOctavos(sistema)){
        Equipo *ePrimero = new Equipo;
        Equipo *eSegundo = new Equipo;
        PtrNodoLista cursor1 = primero(*sistema.grupos);
        Grupo *g = new Grupo;
        while (cursor1 != fin()) {
            Partido *p;
            Lista *l = getEquipos(*(Grupo*)cursor1->ptrDato);
            g = (Grupo*)cursor1->ptrDato;
            PtrNodoLista cursor2 = primero(*l);

            Equipo *e = new Equipo;
            while (cursor2 != fin()) {
                //primero (*l)->ptrDato
                ePrimero = (Equipo*)primero (*l)->ptrDato;
                eSegundo = (Equipo*)siguiente(*l,primero (*l))->ptrDato;

                e = (Equipo*)cursor2->ptrDato;

                cursor2 = siguiente(*l, cursor2);
            }
            switch(getId(*(Grupo*)g)){
                case 'A':
                    p = traerPartido(sistema, 49);
                    setEquipoL(*p,ePrimero);
                    p = traerPartido(sistema, 51);
                    setEquipoV(*p,eSegundo);
                    break;
                case 'B':
                    p = traerPartido(sistema, 51);
                    setEquipoL(*p,ePrimero);
                    p = traerPartido(sistema, 49);
                    setEquipoV(*p,eSegundo);
                    break;
                case 'C':
                    p = traerPartido(sistema, 50);
                    setEquipoL(*p,ePrimero);
                    p = traerPartido(sistema, 52);
                    setEquipoV(*p,eSegundo);
                    break;
                case 'D':
                    p = traerPartido(sistema, 52);
                    setEquipoL(*p,ePrimero);
                    p = traerPartido(sistema, 50);
                    setEquipoV(*p,eSegundo);
                    break;
                case 'E':
                    p = traerPartido(sistema, 53);
                    setEquipoL(*p,ePrimero);
                    p = traerPartido(sistema, 55);
                    setEquipoV(*p,eSegundo);
                    break;
                case 'F':
                    p = traerPartido(sistema, 55);
                    setEquipoL(*p,ePrimero);
                    p = traerPartido(sistema, 53);
                    setEquipoV(*p,eSegundo);
                    break;
                case 'G':
                    p = traerPartido(sistema, 54);
                    setEquipoL(*p,ePrimero);
                    p = traerPartido(sistema, 56);
                    setEquipoV(*p,eSegundo);
                    break;
                case 'H':
                    p = traerPartido(sistema, 56);
                    setEquipoL(*p,ePrimero);
                    p = traerPartido(sistema, 54);
                    setEquipoV(*p,eSegundo);
                    break;

            }
            cursor1 = siguiente(*sistema.grupos, cursor1);
        }

        if(!esCuartos(sistema)){

            ///primer partido de cuartos
            if(getGolesL(*traerPartido(sistema, 49)) > getGolesV(*traerPartido(sistema, 49))){
                setEquipoL(*traerPartido(sistema, 57),getEquipoL(*traerPartido(sistema, 49)));
            }else{
                setEquipoL(*traerPartido(sistema, 57),getEquipoV(*traerPartido(sistema, 49)));
            }
            if(getGolesL(*traerPartido(sistema, 50)) > getGolesV(*traerPartido(sistema, 50))){
                setEquipoV(*traerPartido(sistema, 57),getEquipoL(*traerPartido(sistema, 50)));
            }else{
                setEquipoV(*traerPartido(sistema, 57),getEquipoV(*traerPartido(sistema, 50)));
            }

            ///segundo partido de cuartos
            if(getGolesL(*traerPartido(sistema, 51)) > getGolesV(*traerPartido(sistema, 51))){
                setEquipoL(*traerPartido(sistema, 58),getEquipoL(*traerPartido(sistema, 51)));
            }else{
                setEquipoL(*traerPartido(sistema, 58),getEquipoV(*traerPartido(sistema, 51)));
            }
            if(getGolesL(*traerPartido(sistema, 52)) > getGolesV(*traerPartido(sistema, 52))){
                setEquipoV(*traerPartido(sistema, 58),getEquipoL(*traerPartido(sistema, 52)));
            }else{
                setEquipoV(*traerPartido(sistema, 58),getEquipoV(*traerPartido(sistema, 52)));
            }

            ///tercer partido de cuartos
            if(getGolesL(*traerPartido(sistema, 53)) > getGolesV(*traerPartido(sistema, 53))){
                setEquipoL(*traerPartido(sistema, 59),getEquipoL(*traerPartido(sistema, 53)));
            }else{
                setEquipoL(*traerPartido(sistema, 59),getEquipoV(*traerPartido(sistema, 53)));
            }
            if(getGolesL(*traerPartido(sistema, 54)) > getGolesV(*traerPartido(sistema, 54))){
                setEquipoV(*traerPartido(sistema, 59),getEquipoL(*traerPartido(sistema, 54)));
            }else{
                setEquipoV(*traerPartido(sistema, 59),getEquipoV(*traerPartido(sistema, 54)));
            }

            ///cuarto partido de cuartos
            if(getGolesL(*traerPartido(sistema, 55)) > getGolesV(*traerPartido(sistema, 55))){
                setEquipoL(*traerPartido(sistema, 60),getEquipoL(*traerPartido(sistema, 55)));
            }else{
                setEquipoL(*traerPartido(sistema, 60),getEquipoV(*traerPartido(sistema, 55)));
            }
            if(getGolesL(*traerPartido(sistema, 56)) > getGolesV(*traerPartido(sistema, 56))){
                setEquipoV(*traerPartido(sistema, 60),getEquipoL(*traerPartido(sistema, 56)));
            }else{
                setEquipoV(*traerPartido(sistema, 60),getEquipoV(*traerPartido(sistema, 56)));
            }
        }
    }
    if(!esSemis(sistema)){
        ///primer partido semis
        if(getGolesL(*traerPartido(sistema, 57)) > getGolesV(*traerPartido(sistema, 57))){
            setEquipoL(*traerPartido(sistema, 61),getEquipoL(*traerPartido(sistema, 57)));
        }else{
            setEquipoL(*traerPartido(sistema, 61),getEquipoV(*traerPartido(sistema, 57)));
        }
        if(getGolesL(*traerPartido(sistema, 58)) > getGolesV(*traerPartido(sistema, 58))){
            setEquipoV(*traerPartido(sistema, 61),getEquipoL(*traerPartido(sistema, 58)));
        }else{
            setEquipoV(*traerPartido(sistema, 61),getEquipoV(*traerPartido(sistema, 58)));
        }

        ///segundo partido de semis
        if(getGolesL(*traerPartido(sistema, 59)) > getGolesV(*traerPartido(sistema, 59))){
            setEquipoL(*traerPartido(sistema, 62),getEquipoL(*traerPartido(sistema, 59)));
        }else{
            setEquipoL(*traerPartido(sistema, 62),getEquipoV(*traerPartido(sistema, 59)));
        }
        if(getGolesL(*traerPartido(sistema, 60)) > getGolesV(*traerPartido(sistema, 60))){
            setEquipoV(*traerPartido(sistema, 62),getEquipoL(*traerPartido(sistema, 60)));
        }else{
            setEquipoV(*traerPartido(sistema, 62),getEquipoV(*traerPartido(sistema, 60)));
        }
    }
    if(!es3erY4to(sistema)){
        ///3er y cuarto puesto
        if(getGolesL(*traerPartido(sistema, 61)) < getGolesV(*traerPartido(sistema, 61))){
            setEquipoL(*traerPartido(sistema, 63),getEquipoL(*traerPartido(sistema, 61)));
        }else{
            setEquipoL(*traerPartido(sistema, 63),getEquipoV(*traerPartido(sistema, 61)));
        }
        if(getGolesL(*traerPartido(sistema, 62)) < getGolesV(*traerPartido(sistema, 62))){
            setEquipoV(*traerPartido(sistema, 63),getEquipoL(*traerPartido(sistema, 62)));
        }else{
            setEquipoV(*traerPartido(sistema, 63),getEquipoV(*traerPartido(sistema, 62)));
        }
    }
    if(!esFinal(sistema)){
        ///FINAL!!!!!!!!!!!!!!!!!!
        if(getGolesL(*traerPartido(sistema, 61)) > getGolesV(*traerPartido(sistema, 61))){
            setEquipoL(*traerPartido(sistema, 63),getEquipoL(*traerPartido(sistema, 61)));
        }else{
            setEquipoL(*traerPartido(sistema, 63),getEquipoV(*traerPartido(sistema, 61)));
        }
        if(getGolesL(*traerPartido(sistema, 62)) > getGolesV(*traerPartido(sistema, 62))){
            setEquipoV(*traerPartido(sistema, 63),getEquipoL(*traerPartido(sistema, 62)));
        }else{
            setEquipoV(*traerPartido(sistema, 63),getEquipoV(*traerPartido(sistema, 62)));
        }

    }

}

Jugador* traerJugador(Sistema &sistema, int id) {
    PtrNodoLista cursor = primero(*sistema.jugadores);
    Jugador *j = new Jugador;
    bool encontrado = false;

    while (cursor != fin() && !encontrado) {
        if (getId(*(Jugador*)cursor->ptrDato) == id) {
            j = (Jugador*)cursor->ptrDato;
            encontrado = true;
        }
        cursor = siguiente(*sistema.jugadores, cursor);
    }

    return j;
}

Grupo* traerGrupo(Sistema &sistema, char id) {
    PtrNodoLista cursor = primero(*sistema.grupos);
    Grupo *g = new Grupo;
    bool encontrado = false;

    while (cursor != fin() && !encontrado) {
        if (getId(*(Grupo*)cursor->ptrDato) == id) {
            g = (Grupo*)cursor->ptrDato;
            encontrado = true;
        }
        cursor = siguiente(*sistema.grupos, cursor);
    }

    return g;
}

Partido* traerPartido(Sistema &sistema, int id) {
    PtrNodoLista cursor = primero(*sistema.partidos);
    Partido *p = new Partido;
    bool encontrado = false;

    while (cursor != fin() && !encontrado) {
        if (getId(*(Partido*)cursor->ptrDato) == id) {
            p = (Partido*)cursor->ptrDato;
            encontrado = true;
        }
        cursor = siguiente(*sistema.partidos, cursor);
    }

    return p;
}

void inicioPartido(Sistema &sistema) {
    int id;
    bool encontrado = false;
    cout << "Ingrese id del partido: ";
    cin >> id;

    if((id<=0)||(id>=65)) cout<<"id incorrecto"<<endl;

    Partido *p = traerPartido(sistema, id);

    if (id > 0 && id < 65) {
        //comprobacion de octavos de final
        if((id>=49) && (id<=56)){
            cout<<"partido de octavos:"<<endl;
            encontrado = esOctavos(sistema);
            /*
            PtrNodoLista cursor = primero(*sistema.partidos);

            while (cursor != fin() && !encontrado) {
                if(getId(*(Partido*)cursor->ptrDato)<=48){
                    if ((getGolesL(*(Partido*)cursor->ptrDato) == -1)&&(getGolesV(*(Partido*)cursor->ptrDato) == -1)) {
                        encontrado = true;
                    }
                }
                cursor = siguiente(*sistema.partidos, cursor);
            }*/
        }
        //comprobacion de cuartos de final
        if((id>=57) && (id<=60)){
            cout<<"partido de cuartos:"<<endl;
            encontrado = esCuartos(sistema);
            /*
            PtrNodoLista cursor = primero(*sistema.partidos);

            while (cursor != fin() && !encontrado) {
                if(getId(*(Partido*)cursor->ptrDato)<=56){
                    if ((getGolesL(*(Partido*)cursor->ptrDato) == -1)&&(getGolesV(*(Partido*)cursor->ptrDato) == -1)) {
                        encontrado = true;
                    }
                }
                cursor = siguiente(*sistema.partidos, cursor);
            }*/
        }
        //comprobacion de semifinal
        if((id>=61) && (id<=62)){
            cout<<"partido de semifinal:"<<endl;
            encontrado = esSemis(sistema);
            /*
            PtrNodoLista cursor = primero(*sistema.partidos);

            while (cursor != fin() && !encontrado) {
                if(getId(*(Partido*)cursor->ptrDato)<=60){
                    if ((getGolesL(*(Partido*)cursor->ptrDato) == -1)&&(getGolesV(*(Partido*)cursor->ptrDato) == -1)) {
                        encontrado = true;
                    }
                }
                cursor = siguiente(*sistema.partidos, cursor);
            }*/
        }
        //comprobacion de tercer y cuarto puesto
        if(id==63){
            cout<<"partido de tercer y cuarto puesto"<<endl;
            encontrado = es3erY4to(sistema);
            /*
            PtrNodoLista cursor = primero(*sistema.partidos);

            while (cursor != fin() && !encontrado) {
                if(getId(*(Partido*)cursor->ptrDato)<=62){
                    if ((getGolesL(*(Partido*)cursor->ptrDato) == -1)&&(getGolesV(*(Partido*)cursor->ptrDato) == -1)) {
                        encontrado = true;
                    }
                }
                cursor = siguiente(*sistema.partidos, cursor);
            }*/
        }
        //comprobacion de la final
        if(id==64){
            cout<<"partido FINAL"<<endl;
            encontrado = esFinal(sistema);
            /*
            PtrNodoLista cursor = primero(*sistema.partidos);

            while (cursor != fin() && !encontrado) {
                if(getId(*(Partido*)cursor->ptrDato)<=63){
                    if ((getGolesL(*(Partido*)cursor->ptrDato) == -1)&&(getGolesV(*(Partido*)cursor->ptrDato) == -1)) {
                        encontrado = true;
                    }
                }
                cursor = siguiente(*sistema.partidos, cursor);
            }*/
        }

        if(encontrado){
                cout<<"no se puede iniciar el partido hasta no completar la fase anterior"<<endl;
        }
        else{
            if (getGolesL(*p) == -1) {
                setEstado(*p, EN_JUEGO);
                setGolesL(*p, 0);
                setGolesV(*p, 0);
                cout << "Partido en juego\n" << endl;
            }
            else if (getEstado(*p) == EN_JUEGO) {
                cout << "El partido ya se esta jugando" << endl;
            }
            else {
                cout << "El partido ya se jugo" << endl;
            }

            cout << toString(*p)<<endl;
        }
    }
}

void golesPartido(Sistema &sistema) {
    int id = 0;

    cout << "Ingrese id del partido: ";
    cin >> id;

    Partido *p = traerPartido(sistema, id);

    if (getEstado(*p) == EN_JUEGO) {
        cout << getId(*getEquipoL(*p)) << ": " << getNombre(*getEquipoL(*p)) << endl;
        cout << getId(*getEquipoV(*p))<< ": " << getNombre(*getEquipoV(*p)) << endl;

        id = 0;
        while (getId(*getEquipoL(*p)) != id && getId(*getEquipoV(*p)) != id) {
            cout << "\nIngrese id del equipo: ";
            cin >> id;
        }

        Equipo *e = traerEquipo(sistema, id);
        PtrNodoLista cursor = primero(*e->jugadores);

        while (cursor != fin()) {
            cout << getId(*(Jugador*)cursor->ptrDato) << ": " << getNombre(*(Jugador*)cursor->ptrDato) << endl;
            cursor = siguiente(*e->jugadores, cursor);
        }

        id = 0;
        while (traerEquipoPorJugador(sistema, id) != e) {
            cout << "\nIngrese id del jugador: ";
            cin >> id;
        }

        Jugador *j = traerJugador(sistema, id);

        setGoles(*j, getGoles(*j) + 1);
        setGolesAFavor(*e, getGolesAFavor(*e) + 1);

        if (equals(*e, *getEquipoL(*p))){
            setGolesL(*p, getGolesL(*p) + 1);
            setGolesEnContra(*getEquipoV(*p), getGolesEnContra(*getEquipoV(*p)) + 1);
        }
        else {
            setGolesV(*p, getGolesV(*p) + 1);
            setGolesEnContra(*getEquipoL(*p), getGolesEnContra(*getEquipoL(*p)) + 1);
        }

        string frase = "\nGOOOOOOOOOOOOOOOOL de " + getNombre(*e) + ": " + getNombre(*j);
        int i = 0;

        while(frase[i] != '\0') {
            cout << frase[i];
            i++;
            Sleep(90);
        }
        cout << endl;

    }
    else if (getEstado(*p) == SIN_COMENZAR){
        cout << "El partido no se esta jugando" << endl;
    }
    else {
        cout << "El partido ya se jugo" << endl;
    }
}

void finPartido(Sistema &sistema) {
    int id;

    cout << "Ingrese id del partido: ";
    cin >> id;

    Partido *p = traerPartido(sistema, id);

    if (getEstado(*p) == EN_JUEGO) {
        setEstado(*p, FINALIZADO);

        if (getId(*p) <= 48) {
            if (getGolesL(*p) > getGolesV(*p)) {
                setPuntos(*getEquipoL(*p), getPuntos(*getEquipoL(*p)) + 3);
            }
            else if (getGolesL(*p) == getGolesV(*p)) {
                setPuntos(*getEquipoL(*p), getPuntos(*getEquipoL(*p)) + 1);
                setPuntos(*getEquipoV(*p), getPuntos(*getEquipoV(*p)) + 1);
            }
            else {
                setPuntos(*getEquipoV(*p), getPuntos(*getEquipoV(*p)) + 3);
            }
        }

        cout << "Partido finalizado\n" << endl;
        cout << toString(*p) << endl;
    }
    else {
        cout << "El partido no estaba en juego" << endl;
    }
}

void mostrarPartidosEnCurso(Sistema &sistema) {
    PtrNodoLista cursor = primero(*sistema.partidos);

    while(cursor != fin()) {
        if (getEstado(*(Partido*)cursor->ptrDato) == EN_JUEGO) {
            cout << toString(*(Partido*)cursor->ptrDato)<< endl;
        }
        cursor = siguiente(*sistema.partidos, cursor);
    }
}

void porcentajeGoles(Sistema &sistema) {
    PtrNodoLista cursor = primero(*sistema.partidos);
    int golesL = 0;
    int golesV = 0;

    while(cursor != fin()) {
        if (getGolesL(*(Partido*)cursor->ptrDato) > -1 && getGolesV(*(Partido*)cursor->ptrDato) > -1) {
            golesL += getGolesL(*(Partido*)cursor->ptrDato);
            golesV += getGolesV(*(Partido*)cursor->ptrDato);
        }
        cursor = siguiente(*sistema.partidos, cursor);
    }
    if (golesL > 0 || golesV > 0) {
        cout << "Porcentaje de goles Locales: " << golesL * 100 / (golesL + golesV) << endl;
        cout << "Goles Locales: " << golesL << endl;
        cout << "\nPorcentaje de goles Visitantes: " << golesV * 100 / (golesL + golesV) << endl;
        cout << "Goles Visitantes: " << golesV << endl;
    }
    else
        cout << "Todavia no hubo goles" << endl;
}

void grupoDeLaMuerte(Sistema &sistema) {
    PtrNodoLista cursor = primero(*sistema.grupos);
    char id = 'A';

    while(cursor != fin()) {
        if (golesPorGrupo(*traerGrupo(sistema, id)) < golesPorGrupo(*(Grupo*)cursor->ptrDato))
            id = getId(*(Grupo*)cursor->ptrDato);
        cursor = siguiente(*sistema.grupos, cursor);
    }
    cout << "Grupo de la muerte: " << getNombre(*traerGrupo(sistema, id)) << endl;
}
