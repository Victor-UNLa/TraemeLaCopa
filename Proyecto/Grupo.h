#ifndef _GRUPO_H_
#define _GRUPO_H_

typedef struct {
    char id;
    string nombre;
    Lista *equipos;
} Grupo;

void crear(Grupo &grupo);
void crear(Grupo &grupo, char id, string nombre, Lista *equipos);
void destruir(Grupo &grupo);
void setId(Grupo &grupo, char id);
char getId(Grupo &grupo);
void setNombre(Grupo &grupo, string nombre);
string getNombre(Grupo &grupo);
void setEquipos(Grupo &grupo, Lista *equipos);
Lista* getEquipos(Grupo &grupo);
bool equals(Grupo &grupo, Grupo g);
string toString(Grupo &grupo);
int golesPorGrupo(Grupo &grupo);

#endif // _GRUPO_H_
