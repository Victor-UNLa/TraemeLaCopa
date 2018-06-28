#include <fstream>
#include <cstring>
#include <cstdlib>
#include <windows.h>
#include <stdexcept>
#include <sstream>
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

/*----------------------------------------------------------------------------*/
ResultadoComparacion compararEquipo(PtrDato ptrDato1, PtrDato ptrDato2) {
    if (getId(*(Equipo*)ptrDato1) > getId(*(Equipo*)ptrDato2))
        return MAYOR;

    else if (getId(*(Equipo*)ptrDato1) < getId(*(Equipo*)ptrDato2))
        return MENOR;

    else
        return IGUAL;
}

/*----------------------------------------------------------------------------*/
ResultadoComparacion compararJugador(PtrDato ptrDato1, PtrDato ptrDato2) {
    if (getId(*(Jugador*)ptrDato1) > getId(*(Jugador*)ptrDato2))
        return MAYOR;

    else if (getId(*(Jugador*)ptrDato1) < getId(*(Jugador*)ptrDato2))
        return MENOR;

    else
        return IGUAL;
}

/*----------------------------------------------------------------------------*/
ResultadoComparacion compararGrupo(PtrDato ptrDato1, PtrDato ptrDato2) {
    if (getId(*(Grupo*)ptrDato1) > getId(*(Grupo*)ptrDato2))
        return MAYOR;

    else if (getId(*(Grupo*)ptrDato1) < getId(*(Grupo*)ptrDato2))
        return MENOR;

    else
        return IGUAL;
}

/*----------------------------------------------------------------------------*/
ResultadoComparacion compararPartido(PtrDato ptrDato1, PtrDato ptrDato2) {
    if (getId(*(Partido*)ptrDato1) > getId(*(Partido*)ptrDato2))
        return MAYOR;

    else if (getId(*(Partido*)ptrDato1) < getId(*(Partido*)ptrDato2))
        return MENOR;

    else
        return IGUAL;
}

/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
void destruir(Sistema &sistema) {
    eliminarLista(*sistema.equipos);
    eliminarLista(*sistema.jugadores);
    eliminarLista(*sistema.grupos);
    eliminarLista(*sistema.partidos);
}

/*----------------------------------------------------------------------------*/
void levantarEquipos(Sistema &sistema) {
    ifstream archivo;

    archivo.open("archivos/equipos.txt", ios::in);

    if(archivo.fail()) {
        cout << "Error al abrir el archivo" << endl;
        exit(1);
    }

    string id, nombre, golesAFavor, golesEnContra, puntos;

    bool flag=false;
    int vectorValidar[32];
    int i = 0;
    string letras = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    while (!archivo.eof()) {
        getline(archivo, id, ';');
        getline(archivo, nombre, ';');
        getline(archivo, golesAFavor, ';');
        getline(archivo, golesEnContra, ';');
        getline(archivo, puntos);

        Equipo *e = new Equipo;

        /**Valido si el id de equipo tiene una letra, si es asi el programa no funciona */
        bool errorLetra = false;
        if(atoi(id.c_str())==atoi(letras.c_str())){
            cout<<"------------------------------------------------"<<endl;
            cout << "Error el equipo en el id tiene una letra, deberia tener numero"<< endl;
            cout << "No se puede cargar el equipo:" << nombre<< endl;
            //si entro aca hago el id es positivo para que no entre al otro error
            errorLetra = true;
            flag=true;
        }

        /**Valido si el id de equipo no tiene una letra y tiene un id negativo, si es asi el programa no funciona */
        if (!errorLetra){
        if(atoi(id.c_str())<=0){
                cout<<"------------------------------------------------"<<endl;
                cout << "Error el equipo tiene el id negativo"<< endl;
                cout << "No se puede cargar el equipo:" << nombre<< endl;
                flag=true;
            }
        }

        /**Valido si el id de equipo tiene mas de 32 equipos, si es asi el programa no funciona */
        if(atoi(id.c_str())>32) {
            cout<<"------------------------------------------------"<<endl;
            cout << "Error el id del equipo no debe ser mayor de 32"<< endl;
            flag=true;
        }

        /**Valido si el id de equipo esta repetido, si es asi el programa no funciona */
        for (int indice=0; indice<i; indice++){
            if (vectorValidar[indice]==atoi(id.c_str())){
                cout<<"------------------------------------------------"<<endl;
                cout << "Error el id:  " << atoi(id.c_str()) << " esta repetido"<<endl;
                cout << "No se puede cargar el equipo:" << nombre<< endl;
                flag=true;
            }
        }

        /**Valido si los goles a favor o goles en contra no este en un valor negativo, si es asi el programa no funciona */
        if(atoi(golesAFavor.c_str())<0 || atoi(golesEnContra.c_str())<0){
            cout<<"------------------------------------------------"<<endl;
            cout<<"No se puede ingresar los goles con un valor negativo"<<endl;
            cout<<"Revise los goles de "<<nombre<<endl;
            flag=true;
        }

        /**Valido si los puntos no sean menor que cero o mayor que 9, si es asi el programa no funciona */
        if(atoi(puntos.c_str())>9 || atoi(puntos.c_str())<0 || atoi(puntos.c_str())==8){
            cout<<"------------------------------------------------"<<endl;
            cout<<"Los puntos ingresados no son validos"<<endl;
            cout<<"Revise los puntos de "<<nombre<<endl;
            flag=true;
        }

        vectorValidar[i] = atoi(id.c_str());
        i = i +1;
        crear(*e, atoi(id.c_str()), nombre, atoi(golesAFavor.c_str()), atoi(golesEnContra.c_str()), atoi(puntos.c_str()));
        adicionarFinal(*sistema.equipos, e);
    }

    if(flag==true){
        exit(1);
    }

    reordenar(*sistema.equipos);

    archivo.close();
}

/*----------------------------------------------------------------------------*/
void levantarJugadores(Sistema &sistema) {
    ifstream archivo;

    archivo.open("archivos/jugadores.txt", ios::in);

    if(archivo.fail()) {
        cout << "Error al abrir el archivo" << endl;
        exit(1);
    }

    string id, nombre, goles, equipo;

    int vectorValidar[1000];
    int i = 0;
    bool flag=false;
    bool aux=false;
    string letras = "abcdefghijklmnopqrstuvwxyzABECDEFGHIJKLMNOPQRSTVWXYZ";

    while (!archivo.eof()) {
        getline(archivo, id, ';');
        getline(archivo, nombre, ';');
        getline(archivo, goles, ';');
        getline(archivo, equipo);

        Jugador *j = new Jugador;

        /**Valido si el id de jugador tiene letra, si es asi el programa no funciona */
        bool errorLetra = false;
        if(atoi(id.c_str())==atoi(letras.c_str())){
            cout<<"------------------------------------------------"<<endl;
            cout << "Error un jugador en el id tiene una letra, deberia tener numero"<< endl;
            cout << "No se puede cargar el jugador:" << nombre<< endl;
            errorLetra = true;
            flag=true;
        }

        /**Valido si el id de jugador tiene un valor negativo, si es asi el programa no funciona */
        if (!errorLetra){
        if(atoi(id.c_str())<=0){
                cout<<"------------------------------------------------"<<endl;
                cout << "Error el jugador tiene el id negativo"<< endl;
                cout << "No se puede cargar el jugador:" << nombre<< endl;
                flag=true;
             }
        }

        /**Valido si el jugador tiene un equipo con un valor negativo, si es asi el programa no funciona */
        if(atoi(equipo.c_str())<=0){
            cout<<"------------------------------------------------"<<endl;
            cout << "Error en el jugador por un id negativo del equipo"<< endl;
            cout << "No se puede cargar el jugador:" << nombre<< "  por error de id de equipo "<< endl;
            flag=true;
        }

        aux=false;
        PtrNodoLista cursor=primero(*sistema.equipos);
        while(cursor!=fin()){
            if(atoi(equipo.c_str())==getId(*(Equipo*)cursor->ptrDato)){
                aux=true;
            }
            cursor=siguiente(*sistema.equipos,cursor);
        }

        /**Valido si el jugador no tiene equipo con id, si es asi el programa no funciona */
        if(!aux){
            cout<<"------------------------------------------------"<<endl;
            cout<<"Error en la carga del jugador "<<nombre<<endl;
            cout<<"No existe el equipo con id: "<<atoi(equipo.c_str())<<endl;
            flag=true;
        }

        /**Valido si el id de jugador esta repetido, si es asi el programa no funciona */
        for (int indice=0; indice<i; indice++){
            if (vectorValidar[indice]==atoi(id.c_str())){
                cout<<"------------------------------------------------"<<endl;
                cout << "Error el id:  " << atoi(id.c_str()) << " esta repetido"<<endl;
                cout << "No se puede cargar el jugador:" << nombre<< endl;
                flag=true;
            }
        }

        if(atoi(goles.c_str())>getGolesAFavor(*traerEquipo(sistema,atoi(equipo.c_str())))){
            cout<<"------------------------------------------------"<<endl;
            cout<<"La cantidad de goles marcados por "<< id <<" "<<nombre<<endl;
            cout<<"Es mayor a la cantidad de goles de su equipo"<<endl;
            flag=true;
        }

        int sumgol=0;

        cursor=primero(*getJugadores(*traerEquipo(sistema,atoi(equipo.c_str()))));
        while(cursor!=fin()){
            sumgol=sumgol+getGoles(*(Jugador*)cursor->ptrDato);
            cursor=siguiente(*getJugadores(*traerEquipo(sistema,atoi(equipo.c_str()))),cursor);
        }

        if((sumgol+atoi(goles.c_str()))>getGolesAFavor(*traerEquipo(sistema,atoi(equipo.c_str())))){
            cout<<"------------------------------------------------"<<endl;
            cout<<"Con la cantidad de goles marcados por "<<nombre<<endl;
            cout<<"Se supera la cantidad de goles a favor de su Seleccion"<<endl;
            flag=true;
        }

        vectorValidar[i] = atoi(id.c_str());
        i = i +1;

        crear(*j, atoi(id.c_str()), nombre, atoi(goles.c_str()));

        setJugadores(*traerEquipo(sistema, atoi(equipo.c_str())), j);

        adicionarFinal(*sistema.jugadores, j);
    }

    if(flag==true){
        exit(1);
    }

    reordenar(*sistema.jugadores);

    archivo.close();
}

/*----------------------------------------------------------------------------*/
void levantarGrupos(Sistema &sistema) {
    ifstream archivo;

    archivo.open("archivos/grupos.txt", ios::in);

    if(archivo.fail()) {
        cout << "Error al abrir el archivo" << endl;
        exit(1);
    }

    string id, nombre, e1, e2, e3, e4;
    bool flag=false,encontrado=false,encontrado1=false,encontrado2=false;
    bool encontrado3=false;
    string letras = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTVWXYZ";

    while (!archivo.eof()) {
        getline(archivo, id, ';');
        getline(archivo, nombre, ';');
        getline(archivo, e1, ';');
        getline(archivo, e2, ';');
        getline(archivo, e3, ';');
        getline(archivo, e4);

        /** Validacion para los id*/
        if(id[0]<'A' || id[0]>'H'){
            cout<<"------------------------------------------------"<<endl;
            cout<<"Se ingreso el id de un grupo de forma incorrecta"<<endl;
            flag=true;
        }

        /** Validacion para letra en algun id de equipo*/
        bool errorLetra = false;
        if(atoi(e1.c_str())==atoi(letras.c_str()) || atoi(e2.c_str())==atoi(letras.c_str()) || atoi(e3.c_str())==atoi(letras.c_str()) || atoi(e4.c_str())==atoi(letras.c_str())){
            cout<<"------------------------------------------------"<<endl;
            cout << "Error, en el grupo "<<id<<endl;
            cout << "Se ingreso un equipo con id en letras" <<endl;
            errorLetra = true;
            flag=true;
        }

        /** Validacion id de equipo negativo o 0 y todos los grupos esten completos*/
        if(atoi(e2.c_str())<=0 || atoi(e3.c_str())<=0 || atoi(e4.c_str())<=0 || atoi(e1.c_str())<=0){
            if(e1=="" || e2=="" || e3=="" || e4==""){
                cout<<"------------------------------------------------"<<endl;
                cout<<"Al grupo "<<id<<" le falta algun equipo"<<endl;
                flag=true;
            }else{
                if(!errorLetra){
                    cout<<"------------------------------------------------"<<endl;
                    cout<<"Hay un id negativo o con id 0 en el grupo "<<id<<endl;
                    flag=true;
                }
            }
        }

        /** Validacion para que no haya dos ids iguales en el mismo grupo */
        if(atoi(e1.c_str())==atoi(e2.c_str()) || atoi(e1.c_str())== atoi(e3.c_str()) || atoi(e1.c_str())==atoi(e4.c_str())){
            cout<<"------------------------------------------------"<<endl;
            cout<<"El grupo: "<<id<<" tiene dos equipos con el id: "<<atoi(e1.c_str())<<endl;
            flag=true;
        }
        if(atoi(e2.c_str())==atoi(e3.c_str()) || atoi(e2.c_str())==atoi(e4.c_str())){
            cout<<"------------------------------------------------"<<endl;
            cout<<"El grupo: "<<id<<" tiene dos equipos con el id: "<<atoi(e2.c_str())<<endl;
            flag=true;
        }
        if(atoi(e3.c_str())==atoi(e4.c_str())){
            cout<<"------------------------------------------------"<<endl;
            cout<<"El grupo: "<<id<<" tiene dos equipos con el id: "<<atoi(e3.c_str())<<endl;
            flag=true;
        }

        /** Validacion de que no haya dos equipos con el mismo id en distintos grupos*/
        PtrNodoLista cursor = primero(*sistema.grupos);
        while(cursor!=fin()){
            PtrNodoLista cursor2 = primero(*(getEquipos(*(Grupo*)cursor->ptrDato)));
            if(id[0]==getId(*(Grupo*)cursor->ptrDato)){
                if(id[0]!=0){
                    cout<<"------------------------------------------------"<<endl;
                    cout<<"hay dos o mas grupos con el id: "<<id<<endl;
                    flag=true;
                }
            }
            while(cursor2!=fin()){
                if(atoi(e1.c_str())==getId(*(Equipo*)cursor2->ptrDato) && atoi(e1.c_str())>0){
                    cout<<"------------------------------------------------"<<endl;
                    cout<<"el equipo con id: "<<atoi(e1.c_str())<<" esta cargado en dos grupos distintos"<<endl;
                    flag=true;
                }
                if(atoi(e2.c_str())==getId(*(Equipo*)cursor2->ptrDato) && atoi(e2.c_str())>0){
                    cout<<"------------------------------------------------"<<endl;
                    cout<<"el equipo con id: "<<atoi(e2.c_str())<<" esta cargado en dos grupos distintos"<<endl;
                    flag=true;
                }
                if(atoi(e3.c_str())==getId(*(Equipo*)cursor2->ptrDato) && atoi(e3.c_str())>0){
                    cout<<"------------------------------------------------"<<endl;
                    cout<<"el equipo con id: "<<atoi(e3.c_str())<<" esta cargado en dos grupos distintos"<<endl;
                    flag=true;
                }
                if(atoi(e4.c_str())==getId(*(Equipo*)cursor2->ptrDato) && atoi(e4.c_str())>0){
                    cout<<"------------------------------------------------"<<endl;
                    cout<<"el equipo con id: "<<atoi(e4.c_str())<<" esta cargado en dos grupos distintos"<<endl;
                    flag=true;
                }
                cursor2=siguiente(*(getEquipos(*(Grupo*)cursor->ptrDato)),cursor2);
            }
            cursor=siguiente(*sistema.grupos,cursor);
        }

        /** Validacion para que equipos ingresados existan*/
        cursor=primero(*sistema.equipos);
        encontrado1=false;encontrado2=false;encontrado3=false;
        encontrado=false;
        while(cursor!=fin()){
            if(atoi(e2.c_str())==getId(*(Equipo*)cursor->ptrDato)){
                encontrado=true;
            }
            if(atoi(e1.c_str())==getId(*(Equipo*)cursor->ptrDato)){
                encontrado1=true;
            }
            if(atoi(e3.c_str())==getId(*(Equipo*)cursor->ptrDato)){
                encontrado2=true;
            }
            if(atoi(e4.c_str())==getId(*(Equipo*)cursor->ptrDato)){
                encontrado3=true;
            }
            cursor=siguiente(*sistema.equipos,cursor);
        }

        if(!encontrado || !encontrado2 || !encontrado1 || !encontrado3){
            if(!errorLetra){
                cout<<"------------------------------------------------"<<endl;
                cout<<"En el grupo "<<id<<endl;
                cout<<"Se ingreso un id de equipo que no existe"<<endl;
                flag=true;
            }
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

/*----------------------------------------------------------------------------*/
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
    bool flag=false;

    while (!archivo.eof()) {
        getline(archivo, id, ';');
        getline(archivo, e1, ';');
        getline(archivo, e2, ';');
        getline(archivo, golL, ';');
        getline(archivo, golV);

        /**Valido si el id de partido si tiene un valor negativo, si es asi el programa no funciona */
        if(atoi(id.c_str())<=0){
            cout<<"------------------------------------------------"<<endl;
            cout << "Error el partido tiene el id negativo"<< endl;
            flag=true;
        }

        /**Valido si el id de partido esta repetido, si es asi el programa no funciona */
        for (int indice=0; indice<i; indice++){
            if (vectorValidar[indice]==atoi(id.c_str())){
                cout<<"------------------------------------------------"<<endl;
                cout << "Error el id:  " << atoi(id.c_str()) << " esta repetido"<<endl;
                flag=true;
            }
        }

        vectorValidar[i] = atoi(id.c_str());
        i = i +1;

        Partido *p = new Partido;
        crear(*p, atoi(id.c_str()),traerEquipo(sistema, atoi(e1.c_str())),traerEquipo(sistema, atoi(e2.c_str())),
              atoi(golL.c_str()),atoi(golV.c_str()));

        if(isPartidoJugado(p))setEstado(*p,FINALIZADO);

        adicionarFinal(*sistema.partidos, p);
    }

    if(flag==true){
        exit(1);
    }

    reordenar(*sistema.partidos);

    archivo.close();
}

/*----------------------------------------------------------------------------*/
void mostrarEquipos(Sistema &sistema) {
    PtrNodoLista cursor = primero(*sistema.equipos);

    while(cursor != fin()) {
        cout << toString(*(Equipo*)cursor->ptrDato)<< endl;
        cout << endl;
        cursor = siguiente(*sistema.equipos, cursor);
    }
}

/*----------------------------------------------------------------------------*/
void mostrarJugadores(Sistema &sistema) {
    PtrNodoLista cursor = primero(*sistema.jugadores);

    while(cursor != fin()) {
        cout << toString(*(Jugador*)cursor->ptrDato);
        cout << endl;
        cursor = siguiente(*sistema.jugadores, cursor);
    }
}

/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
void mostrarPartidos(Sistema &sistema) {
    PtrNodoLista cursor = primero(*sistema.partidos);

    while(cursor != fin()) {
        if (getGolesL(*(Partido*)cursor->ptrDato) != -1) {
            cout << toString(*(Partido*)cursor->ptrDato)<< endl;
            cout << endl;
        }
        if (!isPartidoJugado((Partido*)cursor->ptrDato)) {

            if(isPartidoCreado((Partido*)cursor->ptrDato)){
                cout <<"Id: "<<getId(*(Partido*)cursor->ptrDato)<< endl;
                cout <<getNombre(*getEquipoL(*(Partido*)cursor->ptrDato))<< endl;
                cout <<getNombre(*getEquipoV(*(Partido*)cursor->ptrDato))<< endl;
            }else{
                cout << "Id: "<<getId(*(Partido*)cursor->ptrDato)<<"\nNo fue creado"<< endl;
            }

            cout << endl;
        }
        cursor = siguiente(*sistema.partidos, cursor);
    }
}

/*----------------------------------------------------------------------------*/
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
    sistema.jugadores->compara = compararJugador;
    reordenar(*sistema.jugadores);
}

/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
Equipo* traerEquipo(Sistema &sistema, int id) {
    PtrNodoLista cursor = primero(*sistema.equipos);
    Equipo *e = new Equipo;
    crear(*e);
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

/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
bool validar(Sistema& sistema){
    string warning="";
    boolean values=true;
    try{
        validarPartidoCerrados(sistema,warning);
        validarEquipo(sistema.equipos,warning);
        validarGoles(sistema.equipos,sistema.partidos,warning);
        validarEmpates(sistema.partidos,warning);
        //validarJugadores(sistema.equipos,warning);
        validarPuntos(sistema.equipos,sistema.partidos,warning);
        validarPartidosFaseInicial(sistema.grupos,sistema.partidos,warning);
        //validarFaseClasificion(sistema,warning);
        validarClasificacionOctavos(sistema,warning);
        validarClasificacionCuartos(sistema,warning);
        verificarOctavosDeFinal(sistema,warning);
        validarPartidosFaseFinal(sistema.partidos,sistema,warning);
        if(warning!="") throw invalid_argument(warning);
        ordenarEquiposDeGrupos(*sistema.grupos);
    }catch(invalid_argument& e){
        cout << e.what() << endl;
        values=false;
        system("pause");
    }
    system("cls");
    return values;
}
/*----------------------------------------------------------------------------*/
/* Se encontró solución ordenando los grupos */
void ordenarEquiposDeGrupos(Lista& grupos){
    PtrNodoLista cursor = primero(grupos);
    while(cursor != fin() && !listaVacia(grupos)) {
        reordenar(*getEquipos(*(Grupo*)cursor->ptrDato));
        cursor = siguiente(grupos, cursor);
    }
}
/*----------------------------------------------------------------------------*/
/* Valida los Jugadores de cada Equipo que no se encuentre en otro Equipo */
void validarEquipo(Lista* equipos,string& warning){
    PtrNodoLista cursorE = primero(*equipos);
    while(cursorE != fin() && !listaVacia(*equipos)){
        PtrNodoLista cursorEAux = primero(*equipos);
        while(cursorEAux != fin()){
            if(!equals(*(Equipo*)cursorE->ptrDato,*(Equipo*)cursorEAux->ptrDato)){

                PtrNodoLista cursorJ = primero(*getJugadores(*(Equipo*)cursorE->ptrDato));
                while(cursorJ != fin() && !listaVacia(*getJugadores(*(Equipo*)cursorE->ptrDato))){
                    PtrNodoLista cursorJAux = primero(*getJugadores(*(Equipo*)cursorEAux->ptrDato));
                    while(cursorJAux != fin() && !listaVacia(*getJugadores(*(Equipo*)cursorEAux->ptrDato))){
                        if(equals(*(Jugador*)cursorJ->ptrDato,*(Jugador*)cursorJAux->ptrDato)){
                            warning+="Jugador en otro Equipo -> "+getNombre(*(Equipo*)cursorE->ptrDato)+"\n";
                        }
                        cursorJAux=siguiente(*getJugadores(*(Equipo*)cursorE->ptrDato),cursorJAux);
                    }
                    cursorJ=siguiente(*getJugadores(*(Equipo*)cursorE->ptrDato),cursorJ);
                }

            }
            cursorEAux=siguiente(*equipos,cursorEAux);
        }
        cursorE = siguiente(*equipos,cursorE);
    }
}

/*----------------------------------------------------------------------------*/
/* Valida los goles de cada Equipo con respecto a los partidos jugados */
void validarGoles(Lista* equipos,Lista* partidos,string& warning){
    int sumaGAFavor=0,sumaGEnContra=0;
    PtrNodoLista cursorE = primero(*equipos);
    while(cursorE != fin() && !listaVacia(*equipos)){

        PtrNodoLista cursorP = primero(*partidos);
        while(cursorP != fin() && !listaVacia(*partidos)){
            if(isPartidoJugado((Partido*)cursorP->ptrDato)){
                if(equals(*getEquipoL(*(Partido*)cursorP->ptrDato),*(Equipo*)cursorE->ptrDato)){
                    sumaGAFavor+=getGolesL(*(Partido*)cursorP->ptrDato);
                    sumaGEnContra+=getGolesV(*(Partido*)cursorP->ptrDato);
                }else if(equals(*getEquipoV(*(Partido*)cursorP->ptrDato),*(Equipo*)cursorE->ptrDato)){
                    sumaGAFavor+=getGolesV(*(Partido*)cursorP->ptrDato);
                    sumaGEnContra+=getGolesL(*(Partido*)cursorP->ptrDato);
                }
            }
            cursorP = siguiente(*partidos,cursorP);
        }
        ostringstream convert1,convert2,convert3,convert4;
        convert1 << getGolesAFavor(*(Equipo*)cursorE->ptrDato);
        convert2 << sumaGAFavor;
        convert3 << getGolesEnContra(*(Equipo*)cursorE->ptrDato);
        convert4 << sumaGEnContra;
        if(convert1.str()!=convert2.str()){
            warning+="Los golesAFavor para Equipo -> "+getNombre(*(Equipo*)cursorE->ptrDato)
            +" son incorrectos. goles ["+convert1.str()+"] de ["+convert2.str()+"] goles encontrados\n";
        }
        if(convert3.str()!=convert4.str()){
            warning+="Los GolesEnContra para Equipo -> "+getNombre(*(Equipo*)cursorE->ptrDato)
            +" son incorrectos. goles ["+convert3.str()+"] de ["+convert4.str()+"] goles encontrados\n";
        }

        sumaGAFavor=0;sumaGEnContra=0;
        cursorE = siguiente(*equipos,cursorE);
    }
}

/*----------------------------------------------------------------------------*/
/* Valida Ronda de eliminatorias que no halla empates */
void validarEmpates(Lista* partidos,string& warning){
    PtrNodoLista cursorP = primero(*partidos);
    while(cursorP != fin() && !listaVacia(*partidos)){
        if(isPartidoJugado((Partido*)cursorP->ptrDato) && getId(*(Partido*)cursorP->ptrDato)>48 &&
            isPartidoCreado((Partido*)cursorP->ptrDato)){
            if(isEmpate((Partido*)cursorP->ptrDato)){
                ostringstream convert;
                convert << getId(*(Partido*)cursorP->ptrDato);
                warning+="El Partido id["+ convert.str()+"] esta en empate\n";
            }
        }
        cursorP = siguiente(*partidos,cursorP);
    }
}

/*----------------------------------------------------------------------------*/
/* Valida los goles de los jugadores con respecto al Equipo (GolesAFavor) */
void validarJugadores(Lista* equipos,string& warning){
    int sumG=0;
    PtrNodoLista cursor = primero(*equipos);
    while(cursor!=fin() && !listaVacia(*equipos)){

        PtrNodoLista cursorJ=primero(*getJugadores(*(Equipo*)cursor->ptrDato));
        while (cursorJ!=fin() && !listaVacia(*getJugadores(*(Equipo*)cursor->ptrDato))){
            sumG+=getGoles(*(Jugador*)cursorJ->ptrDato);
            cursorJ=siguiente(*getJugadores(*(Equipo*)cursor->ptrDato),cursorJ);
        }
        ostringstream convert,convert2,convert3;
        convert<<sumG;
        convert2<<getGolesAFavor(*(Equipo*)cursor->ptrDato);
        convert3<<getId(*(Equipo*)cursor->ptrDato);
        if(convert.str()!=convert2.str()){
            warning+="Los Goleadores del Equipo ["+convert3.str()+"] ["+getNombre(*(Equipo*)cursor->ptrDato)
                   +"] su suma es incorrecta, GolesAFavor["+convert2.str()+"] goleadores: "+convert.str()+" goles \n";
        }

        sumG=0;
        cursor=siguiente(*equipos,cursor);
    }
}

/*----------------------------------------------------------------------------*/
/* Valida los puntos de cada Equipo */
void validarPuntos(Lista* equipos,Lista* partidos,string& warning){

    PtrNodoLista cursorE=primero(*equipos);
    int puntos=0;
    while(cursorE!=fin() && !listaVacia(*equipos)){

        PtrNodoLista cursorP=primero(*partidos);
        while(cursorP!=fin() && !listaVacia(*partidos)){

            if(getId(*(Partido*)cursorP->ptrDato)<=48 && isPartidoJugado((Partido*)cursorP->ptrDato)){
                if(equals(*(Equipo*)cursorE->ptrDato,*getEquipoL(*(Partido*)cursorP->ptrDato))){
                    if (getGolesL(*(Partido*)cursorP->ptrDato) > getGolesV(*(Partido*)cursorP->ptrDato)) {
                        puntos+=3;
                    }else if(isEmpate((Partido*)cursorP->ptrDato)) {
                        puntos+=1;
                    }
                }else if(equals(*(Equipo*)cursorE->ptrDato,*getEquipoV(*(Partido*)cursorP->ptrDato))){
                    if (getGolesL(*(Partido*)cursorP->ptrDato) < getGolesV(*(Partido*)cursorP->ptrDato)) {
                        puntos+=3;
                    }else if(isEmpate((Partido*)cursorP->ptrDato)) {
                        puntos+=1;
                    }
                }
            }
            cursorP=siguiente(*partidos,cursorP);
        }
        ostringstream convert,convert2,convert3;
        convert << getId(*(Equipo*)cursorE->ptrDato);
        convert2 << puntos;
        convert3 << getPuntos(*(Equipo*)cursorE->ptrDato);
        if(puntos!=getPuntos(*(Equipo*)cursorE->ptrDato)){
            warning+="Puntos del Equipo id["+convert.str()+"] "+getNombre(*(Equipo*)cursorE->ptrDato)
            +" son incorrectos: ["+convert3.str()+ "] se calculo -> ["+convert2.str()+"]\n";
        }
        puntos=0;
        cursorE=siguiente(*equipos,cursorE);
    }

}

/*----------------------------------------------------------------------------*/
/* Valida 1ra Ronda si el Equipo completa el cuadrangular simple de partidos a jugar */
void validarPartidosFaseInicial(Lista* grupos,Lista* partidos,string& warning){
    PtrNodoLista cursorG=primero(*grupos);
    int contP=0;
    while(cursorG!=fin() && !listaVacia(*grupos)){
        PtrNodoLista cursorE=primero(*getEquipos(*(Grupo*)cursorG->ptrDato));
        while(cursorE!=fin() && !listaVacia(*getEquipos(*(Grupo*)cursorG->ptrDato))){

            PtrNodoLista cursorP=primero(*partidos);
            while(cursorP!=fin() && !listaVacia(*partidos)){

                if(getId(*(Partido*)cursorP->ptrDato)<=48){
                    // verifico si es del grupo su rival
                    ostringstream convert;
                    convert << getId(*(Partido*)cursorP->ptrDato);
                    if(equals(*(Equipo*)cursorE->ptrDato,*getEquipoL(*(Partido*)cursorP->ptrDato))){
                        if(!verificarGrupo(getEquipos(*(Grupo*)cursorG->ptrDato),getEquipoV(*(Partido*)cursorP->ptrDato))){
                            warning+="El Partido id ["+convert.str()+"] Equipo Local ["+getNombre(*getEquipoL(*(Partido*)cursorP->ptrDato))
                            +"] .su rival no es del grupo ["+getNombre(*(Grupo*)cursorG->ptrDato)+"] No se puede concretar partido\n";
                        }
                        contP++;
                    }else if(equals(*(Equipo*)cursorE->ptrDato,*getEquipoV(*(Partido*)cursorP->ptrDato))){
                        if(!verificarGrupo(getEquipos(*(Grupo*)cursorG->ptrDato),getEquipoL(*(Partido*)cursorP->ptrDato))){
                            warning+="El Partido id ["+convert.str()+"] Equipo Visitante ["+getNombre(*getEquipoV(*(Partido*)cursorP->ptrDato))
                            +"] .su rival no es del grupo ["+getNombre(*(Grupo*)cursorG->ptrDato)+"] No se puede concretar partido\n";
                        }
                        contP++;
                    }
                }
                cursorP=siguiente(*partidos,cursorP);
            }
            if(contP!=3){
                ostringstream convert,convert2;
                convert << getId(*(Equipo*)cursorE->ptrDato);
                convert2 << contP;
                warning+="El Equipo id ["+convert.str()+"] ["+getNombre(*(Equipo*)cursorE->ptrDato)
                +"] no completa el cuadrangular simple, se calcula -> ["+convert2.str()
                +"] partidos que jugara\n";
            }
            contP=0;
            cursorE=siguiente(*getEquipos(*(Grupo*)cursorG->ptrDato),cursorE);
        }
        cursorG=siguiente(*grupos,cursorG);
    }
}

/*----------------------------------------------------------------------------*/
/* Valida 1ra Ronda si el Equipo pasa a octavos correctamente */
void validarFaseClasificion(Sistema& sistema,string& warning){
    ordenarEquiposDeGrupos(*sistema.grupos);
    if(verificarPartidos(sistema.partidos,1,48)){
        PtrNodoLista cursor = primero(*sistema.grupos);
        while(cursor != fin() && !listaVacia(*sistema.grupos)) {
            /*si todos los partidos de la fase uno fue jugados*/
            if(!localizar(traerGanadores(getEquipos(*(Grupo*)cursor->ptrDato),sistema.partidos)[0],sistema,49,57)){
                ostringstream convert;
                convert << getId(*traerGanadores(getEquipos(*(Grupo*)cursor->ptrDato),sistema.partidos)[0]);
                warning+="El Equipo id ["+convert.str()+"] ["+getNombre(*traerGanadores(getEquipos(*(Grupo*)cursor->ptrDato),sistema.partidos)[0])
                        +"] Gano la fase Inicial y no se encuentra en 8vos\n";
            }
            if(!localizar(traerGanadores(getEquipos(*(Grupo*)cursor->ptrDato),sistema.partidos)[1],sistema,49,57)) {
                ostringstream convert;
                convert << getId(*traerGanadores(getEquipos(*(Grupo*)cursor->ptrDato),sistema.partidos)[1]);
                warning+="El Equipo id ["+convert.str()+"] ["+getNombre(*traerGanadores(getEquipos(*(Grupo*)cursor->ptrDato),sistema.partidos)[1])
                        +"] Gano la fase Inicial y no se encuentra en 8vos\n";
            }

        cursor = siguiente(*sistema.grupos, cursor);
        }
    }
}
/*se compara la ronda de partidos si estan finalizados*/
bool verificarPartidos(Lista* partidos,int i,int f){
    bool values=true;
    PtrNodoLista cursor = primero(*partidos);
    while(cursor != fin() && !listaVacia(*partidos) &&
          getId(*(Partido*)cursor->ptrDato)>=i &&
          getId(*(Partido*)cursor->ptrDato)<=f && values==true) {
        if(!isPartidoJugado((Partido*)cursor->ptrDato))values=false;
        cursor = siguiente(*partidos, cursor);
    }
    return values;
}
Equipo** traerGanadores(Lista* equipos,Lista* partidos){
    Equipo* e[2];
    e[0]=new Equipo;e[1]=new Equipo;
    crear(*e[0]);crear(*e[1]);
    int cont=2;bool opc2=false;
    while(cont!=0){
        PtrNodoLista cursor = primero(*equipos);
        while(cursor != fin() && !listaVacia(*equipos)) {
            if(opc2==false){ //de cada 4 devuelvo 2 equipos
                if(verificarVictoriaPuntos(*(Equipo*)cursor->ptrDato,equipos)){
                e[0]=(Equipo*)cursor->ptrDato;
                cont--;}
                cursor = siguiente(*equipos, cursor);
                if(verificarVictoriaPuntos(*(Equipo*)cursor->ptrDato,equipos)){
                e[1]=(Equipo*)cursor->ptrDato;
                cont--;}
            }else{
                if(verificarVictoriaDifGoles(*(Equipo*)cursor->ptrDato,equipos,partidos) && getId(*e[0])==0){
                e[0]=(Equipo*)cursor->ptrDato;
                cont--;}
                cursor = siguiente(*equipos, cursor);
                if(verificarVictoriaDifGoles(*(Equipo*)cursor->ptrDato,equipos,partidos) && getId(*e[1])==0){
                e[1]=(Equipo*)cursor->ptrDato;
                cont--;}
                cont=0;
            }
            cursor = siguiente(*equipos, cursor);
        }
        if(cont!=0){
            opc2=true;
        }
    }
    return e;
}
bool verificarVictoriaPuntos(Equipo& e,Lista* equipos){
    int cont=0;
    bool values=false;
    PtrNodoLista cursor = primero(*equipos);
    while(cursor != fin() && !listaVacia(*equipos)) {
        if(!equals(e,*(Equipo*)cursor->ptrDato)){
            if(getPuntos(e)>getPuntos(*(Equipo*)cursor->ptrDato))cont++;
        }
        cursor = siguiente(*equipos, cursor);
    }
    if(cont>=2)values=true;
    return values;
}
bool verificarVictoriaDifGoles(Equipo& e,Lista* equipos,Lista* partidos){
    int cont=0;
    bool values=false;
    PtrNodoLista cursor = primero(*equipos);
    while(cursor != fin() && !listaVacia(*equipos)) {
        if(!equals(e,*(Equipo*)cursor->ptrDato)){
            if(diferenciaDeGoles(partidos,e,1,48)>diferenciaDeGoles(partidos,*(Equipo*)cursor->ptrDato,1,48))cont++;
        }
        cursor = siguiente(*equipos, cursor);
    }
    if(cont>=1)values=true;
    return values;
}
bool localizar(Equipo* equipo,Sistema& s,int i,int f){
    bool values=false;
    for(int j=i;j<f && values==false;j++){
        if(verificarPartido(s,equipo,j))values=true;
    }
    return values ;
}
/*----------------------------------------------------------------------------*/
/* Valida 8vos si los equipos no se repiten */
void verificarOctavosDeFinal(Sistema& s,string& warning){
    bool values=false;
    int cont=0;
    PtrNodoLista cursorP=primero(*s.partidos);
    while(cursorP!=fin() && !listaVacia(*s.partidos) ){
        if(getId(*(Partido*)cursorP->ptrDato)>48 &&
           getId(*(Partido*)cursorP->ptrDato)<57 &&
           isPartidoCreado((Partido*)cursorP->ptrDato)){
            for(int i=49;i<=56;i++){
                if(verificarPartido(s,getEquipoL(*(Partido*)cursorP->ptrDato),i))cont++;
            }
            if(cont!=1){
                warning+="Error en Octavos de final: Equipo Local ["+getNombre(*getEquipoL(*(Partido*)cursorP->ptrDato))+"] repetido\n";
            }
            cont=0;
            for(int i=49;i<=56;i++){
                if(verificarPartido(s,getEquipoV(*(Partido*)cursorP->ptrDato),i))cont++;
            }
            if(cont!=1){
                warning+="Error en Octavos de final: Equipo Visitante ["+getNombre(*getEquipoV(*(Partido*)cursorP->ptrDato))+"] repetido\n";
            }
        }
        cont=0;
        cursorP=siguiente(*s.partidos,cursorP);
    }
}
/*----------------------------------------------------------------------------*/
/* Valida 8vos de Final si el Equipo que gano, paso a 4tos */
void validarClasificacionOctavos(Sistema& s,string& warning){

  bool values=false;
  if(!verificarPartidos(s.partidos,49,56)){
    for(int i=49;i<57;i++){
        Equipo* e=traerGanador(traerPartido(s,i));
        for(int j=57;j<=60;j++){
            if(equals(*e,*getEquipoL(*traerPartido(s,j))) || equals(*e,*getEquipoV(*traerPartido(s,j))))values=true;;
        }
        if(!values){
            ostringstream convert;
            convert << getId(*e);
            warning+="El Equipo id ["+convert.str()+"] ["+getNombre(*e)
                    +"] Gano la fase de 8vos y no se encuentra en 4tos\n";
        }
        values=false;
    }
  }
}
/* Valida 4tos de Final si el Equipo que gano, paso a SemiFinal */
void validarClasificacionCuartos(Sistema& s,string& warning){
  ordenarEquiposDeGrupos(*s.grupos);
  bool values=false;
  if(!verificarPartidos(s.partidos,57,60)){
    for(int i=57;i<61;i++){
        Equipo* e=traerGanador(traerPartido(s,i));
        for(int j=61;j<=62;j++){
            if(equals(*e,*getEquipoL(*traerPartido(s,j))) || equals(*e,*getEquipoV(*traerPartido(s,j))))values=true;
        }
        if(!values){
            ostringstream convert;
            convert << getId(*e);
            warning+="El Equipo id ["+convert.str()+"] ["+getNombre(*e)
                    +"] Gano la fase de 4tos y no se encuentra en SemiFinal\n";
        }
        values=false;
    }
  }
}

/*----------------------------------------------------------------------------*/
/* Valida 2da Ronda si el Equipo que juega es correcto */
void validarPartidosFaseFinal(Lista* partidos,Sistema& sistema,string& warning){
    PtrNodoLista cursorP=primero(*partidos);
    while(cursorP!=fin() && !listaVacia(*partidos)){

        if(getId(*(Partido*)cursorP->ptrDato)>48 && isPartidoCreado((Partido*)cursorP->ptrDato)){
            /* para partido del 49 al 62*/
            if(getId(*(Partido*)cursorP->ptrDato)<63){
                if(verificarContinuidadEquipo(partidos,siguiente(*partidos,cursorP),traerPerdedor((Partido*)cursorP->ptrDato))){
                    ostringstream convert,convert2;
                    convert << getId(*traerPerdedor((Partido*)cursorP->ptrDato));
                    convert2 << getId(*(Partido*)cursorP->ptrDato);
                    warning+="El Equipo id ["+convert.str()+"] ["+getNombre(*traerPerdedor((Partido*)cursorP->ptrDato))
                    +"] Perdio fase Eliminatoria. se encontro en el partido id ["+convert2.str()+"]\n";
                }
            }else if(getId(*(Partido*)cursorP->ptrDato)==63){
                /* para 3er y 4to puesto*/
                if(!verificarPartido(sistema,traerPerdedor(traerPartido(sistema, 61)),63) ){
                    ostringstream convert;
                    convert << getId(*traerPerdedor(traerPartido(sistema, 61)));
                    warning+="El Partido para 3er y 4to puesto id [63] tiene Equipo erroneo, siendo id ["+convert.str()+"] ["
                    +getNombre(*traerPerdedor(traerPartido(sistema, 61)))+"] posible correcto\n";
                }
                if(!verificarPartido(sistema,traerPerdedor(traerPartido(sistema, 62)),63) ){
                    ostringstream convert;
                    convert << getId(*traerPerdedor(traerPartido(sistema, 62)));
                    warning+="El Partido para 3er y 4to puesto id [63] tiene Equipo erroneo, siendo id ["+convert.str()+"] ["
                    +getNombre(*traerPerdedor(traerPartido(sistema, 62)))+"] posible correcto\n";
                }
            }else{
                /* para 1er y 2do puesto*/
                if(!verificarPartido(sistema,traerGanador(traerPartido(sistema, 61)),64) ){
                    ostringstream convert;
                    convert << getId(*traerGanador(traerPartido(sistema, 61)));
                    warning+="El Partido para 1er y 2do puesto id [64] tiene Equipo erroneo, siendo id ["+convert.str()+"] ["
                    +getNombre(*traerGanador(traerPartido(sistema, 61)))+"] posible correcto\n";
                }
                if(!verificarPartido(sistema,traerGanador(traerPartido(sistema, 62)),64) ){
                    ostringstream convert;
                    convert << getId(*traerGanador(traerPartido(sistema, 62)));
                    warning+="El Partido para 1er y 2do puesto id [64] tiene Equipo erroneo, siendo id ["+convert.str()+"] ["
                    +getNombre(*traerGanador(traerPartido(sistema, 62)))+"] posible correcto\n";
                }
            }
        }
        cursorP=siguiente(*partidos,cursorP);
    }
}

/*----------------------------------------------------------------------------*/
/* Verifico partidos imcompletos */
void validarPartidoCerrados(Sistema& s,string& warning){
    bool values=true;
    Equipo* e=new Equipo;
    crear(*e);
    for(int j=1;j<=64;j++){
        Partido *p=traerPartido(s,j);
        if(!isPartidoCreado(p) && !isPartidoJugado(p)
           && (!equals(*getEquipoL(*p),*e) || !equals(*getEquipoV(*p),*e))){
            ostringstream convert;
            convert << getId(*traerPartido(s,j));
            warning+="El Partido id ["+convert.str()+"] incompleto\n";
        }
    }
}
/*----------------------------------------------------------------------------*/
bool verificarPartido(Sistema& sistema,Equipo* equipo,int id){
    bool values=false;
    if(equals(*getEquipoL(*traerPartido(sistema, id)),*equipo)
       ||equals(*getEquipoV(*traerPartido(sistema, id)),*equipo))values=true;
    return values;
}
/*----------------------------------------------------------------------------*/
bool verificarContinuidadEquipo(Lista* partidos,PtrNodoLista cursor,Equipo* equipo){
    bool values=false;
    while(cursor!=fin() && !values && getId(*(Partido*)cursor->ptrDato)<63){
        if(equals(*getEquipoL(*(Partido*)cursor->ptrDato),*equipo) ||
           equals(*getEquipoV(*(Partido*)cursor->ptrDato),*equipo)){values=true;}
        cursor=siguiente(*partidos,cursor);
    }
    return values;
}
/*----------------------------------------------------------------------------*/
bool verificarGrupo(Lista* equipos,Equipo* equipo){
    bool values=false;
    PtrNodoLista cursor=primero(*equipos);
    while(cursor!=fin() && !listaVacia(*equipos)){
        if(equals(*(Equipo*)cursor->ptrDato,*equipo))values=true;
        cursor=siguiente(*equipos,cursor);
    }
    return values;
}
/*----------------------------------------------------------------------------*/
bool isPartidoJugado(Partido* p){
    return getGolesL(*p)!=-1 || getGolesV(*p)!=-1;
}
/*----------------------------------------------------------------------------*/
bool isPartidoCreado(Partido* p){
    return getId(*getEquipoL(*p))!=0 && getId(*getEquipoV(*p))!=0;
}
/*----------------------------------------------------------------------------*/
bool isEmpate(Partido* p){
    return getGolesL(*p)==getGolesV(*p);
}
/*----------------------------------------------------------------------------*/
Equipo* traerGanador(Partido* p){
    if (getGolesL(*p) > getGolesV(*p))
        return getEquipoL(*p);
    else
        return getEquipoV(*p);
}
/*----------------------------------------------------------------------------*/
Equipo* traerPerdedor(Partido* p){
    if (getGolesL(*p) < getGolesV(*p))
        return getEquipoL(*p);
    else
        return getEquipoV(*p);
}

/*----------------------------------------------------------------------------*/
// Tabla de valores por Equipos < >
void mostrarTablaPosiciones(Sistema &sistema) {
    PtrNodoLista cursor = primero(*sistema.grupos);

    int golesTotales = 0;
    while(cursor != fin() && !listaVacia(*sistema.grupos)) {

        if(getId(*(Grupo*)cursor->ptrDato)>0){
            cout << getNombre(*(Grupo*)cursor->ptrDato) << endl;
            cout << "Pos" << "\t||" << "Dif" << " \t|| " << "Pun" << " \t|| " << "Equipo" << endl;
            cout << "------------------------------------------" << endl;
            reordenar(*getEquipos(*(Grupo*)cursor->ptrDato));
            PtrNodoLista cursorE = primero(*getEquipos(*(Grupo*)cursor->ptrDato));
            int i = 1;
            while (cursorE != fin() && !listaVacia(*getEquipos(*(Grupo*)cursor->ptrDato))) {
                cout << i << " \t||";
                cout << getGolesAFavor(*(Equipo*)cursorE->ptrDato) - getGolesEnContra(*(Equipo*)cursorE->ptrDato) << " \t|| ";
                cout << getPuntos(*(Equipo*)cursorE->ptrDato) << " \t|| ";
                cout << getNombre(*(Equipo*)cursorE->ptrDato) << endl;
                i++;
                cursorE = siguiente(*getEquipos(*(Grupo*)cursor->ptrDato), cursorE);
            }
            cout << "Goles del grupo: " << golesPorGrupo(*(Grupo*)cursor->ptrDato) << endl;
            cout << endl;
        }
        golesTotales += golesPorGrupo(*(Grupo*)cursor->ptrDato);
        cout << endl;
        cursor = siguiente(*sistema.grupos, cursor);
    }
    cout << "Total de goles: " << golesTotales << endl;
}
/*----------------------------------------------------------------------------*/
int diferenciaDeGoles(Lista* partidos,Equipo& e,int i,int f){
    return traerGolesAFavor(partidos,e,i,f) - traerGolesEnContra(partidos,e,i,f);
}
/*----------------------------------------------------------------------------*/
int traerGoles(Partido* p,Equipo& e){
    int goles=0;
    if(equals(*getEquipoL(*p),e))
        goles=getGolesL(*p);
    else
        goles=getGolesV(*p);
    return goles;
}
/*----------------------------------------------------------------------------*/
int traerGolesAFavor(Lista* partidos,Equipo& e,int i,int f){
    PtrNodoLista cursorP=primero(*partidos);
    int cont=0;
    while(cursorP!=fin() && !listaVacia(*partidos) && getId(*(Partido*)cursorP->ptrDato)>=i && getId(*(Partido*)cursorP->ptrDato)<=f){

        if(isPartidoJugado((Partido*)cursorP->ptrDato) ){
            if(equals(*getEquipoL(*(Partido*)cursorP->ptrDato),e)
               ||equals(*getEquipoV(*(Partido*)cursorP->ptrDato),e))cont+=traerGoles((Partido*)cursorP->ptrDato,e);
        }

        cursorP=siguiente(*partidos,cursorP);
    }
    return cont;
}
/*----------------------------------------------------------------------------*/
int traerGolesEnContra(Lista* partidos,Equipo& e,int i,int f){
    PtrNodoLista cursorP=primero(*partidos);
    int cont=0;
    while(cursorP!=fin() && !listaVacia(*partidos) && getId(*(Partido*)cursorP->ptrDato)>=i && getId(*(Partido*)cursorP->ptrDato)<=f){

        if(isPartidoJugado((Partido*)cursorP->ptrDato) ){
            if(equals(*getEquipoL(*(Partido*)cursorP->ptrDato),e)){
                cont+=traerGoles((Partido*)cursorP->ptrDato,*getEquipoV(*(Partido*)cursorP->ptrDato));
            }else if(equals(*getEquipoV(*(Partido*)cursorP->ptrDato),e)){
                cont+=traerGoles((Partido*)cursorP->ptrDato,*getEquipoL(*(Partido*)cursorP->ptrDato));
            }
        }

        cursorP=siguiente(*partidos,cursorP);
    }
    return cont;
}

/*----------------------------------------------------------------------------*/
void setearFases(Sistema &sistema){

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
            setEquipoL(*traerPartido(sistema, 64),getEquipoL(*traerPartido(sistema, 61)));
        }else{
            setEquipoL(*traerPartido(sistema, 64),getEquipoV(*traerPartido(sistema, 61)));
        }
        if(getGolesL(*traerPartido(sistema, 62)) > getGolesV(*traerPartido(sistema, 62))){
            setEquipoV(*traerPartido(sistema, 64),getEquipoL(*traerPartido(sistema, 62)));
        }else{
            setEquipoV(*traerPartido(sistema, 64),getEquipoV(*traerPartido(sistema, 62)));
        }

    }

}

/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
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

        }
        //comprobacion de cuartos de final
        if((id>=57) && (id<=60)){
            cout<<"partido de cuartos:"<<endl;
            encontrado = esCuartos(sistema);

        }
        //comprobacion de semifinal
        if((id>=61) && (id<=62)){
            cout<<"partido de semifinal:"<<endl;
            encontrado = esSemis(sistema);

        }
        //comprobacion de tercer y cuarto puesto
        if(id==63){
            cout<<"partido de tercer y cuarto puesto"<<endl;
            encontrado = es3erY4to(sistema);

        }
        //comprobacion de la final
        if(id==64){
            cout<<"partido FINAL"<<endl;
            encontrado = esFinal(sistema);

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
            cout <<endl;
        }
    }
}

/*----------------------------------------------------------------------------*/
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

        /**Mensaje de goles*/
        int sumgol=0;
        cursor=primero(*sistema.equipos);
        while(cursor!=fin()){
            sumgol=sumgol+getGolesAFavor(*(Equipo*)cursor->ptrDato);
            cursor=siguiente(*sistema.equipos,cursor);
        }
        if(sumgol<100 && sumgol%10==0){
            cout<<"ATENCION!!!"<<endl;
            cout<<"Se han alcanzado los "<<sumgol<<" goles en el mundial."<<endl;
        }
        if(sumgol>=100 && sumgol%100==0){
            cout<<"ATENCION!!!"<<endl;
            cout<<"Se han alcanzado los "<<sumgol<<" goles en el mundial."<<endl;
        }

    }
    else if (getEstado(*p) == SIN_COMENZAR){
        cout << "El partido no se esta jugando" << endl;
    }
    else {
        cout << "El partido ya se jugo" << endl;
    }
}

/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
void mostrarPartidosEnCurso(Sistema &sistema) {
    PtrNodoLista cursor = primero(*sistema.partidos);

    while(cursor != fin()) {
        if (getEstado(*(Partido*)cursor->ptrDato) == EN_JUEGO) {
            cout << toString(*(Partido*)cursor->ptrDato)<< endl;
        }
        cursor = siguiente(*sistema.partidos, cursor);
    }
}

/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
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
