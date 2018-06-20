#ifndef _GRUPO_H_
#define _GRUPO_H_

typedef struct {
    char id;
    string nombre;
    Lista *equipos;
} Grupo;

/******************************************************************************/
/* Definicion de Primitivas */
/*--------------------------*/

/*
  pre : el grupo no debe haber sido creada.
  post: el grupo queda creada y preparada para ser usada con valores 0.
*/
void crear(Grupo &grupo);

/*----------------------------------------------------------------------------*/
/*
  pre: el grupo debe haberse creado y no destruido
  post: deja la instacia de la lista para ser usado. Los parametros se aplica al tda (grupo).
*/
void crear(Grupo &grupo, char id, string nombre, Lista *equipos);

/*----------------------------------------------------------------------------*/
/*
  pre: el grupo debe haberse creado y no destruido.
  post: destruye la instancia del tda y ya no podrá ser usado.
*/
void destruir(Grupo &grupo);

/*----------------------------------------------------------------------------*/
/*
  pre: el grupo debe haberse creado y no destruido.
  post: asigna el valor de id a la instancia de grupo.
*/
void setId(Grupo &grupo, char id);

/*----------------------------------------------------------------------------*/
/*
  pre: el grupo debe haberse creado y no destruido.
  post: devuelve el id.
*/
char getId(Grupo &grupo);

/*----------------------------------------------------------------------------*/
/*
  pre: el grupo debe haberse creado y no destruido.
  post: asigna el valor de nombre a la instancia de grupo.
*/
void setNombre(Grupo &grupo, string nombre);

/*----------------------------------------------------------------------------*/
/*
  pre: el grupo debe haberse creado y no destruido.
  post: devuelve el nombre.
*/
string getNombre(Grupo &grupo);

/*----------------------------------------------------------------------------*/
/*
  pre: el grupo debe haberse creado y no destruido.
  post: asigna el valor de equipos a la instancia de grupo.
*/
void setEquipos(Grupo &grupo, Lista *equipos);

/*----------------------------------------------------------------------------*/
/*
  pre: el grupo debe haberse creado y no destruido.
  post: devuelve los equipos.
*/
Lista* getEquipos(Grupo &grupo);

/*----------------------------------------------------------------------------*/
bool equals(Grupo &grupo, Grupo g);

/*----------------------------------------------------------------------------*/
string toString(Grupo &grupo);

/*----------------------------------------------------------------------------*/
int golesPorGrupo(Grupo &grupo);

#endif // _GRUPO_H_
