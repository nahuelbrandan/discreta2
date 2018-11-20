#ifndef BRANDAN_COSTAMAGNA_DIARTE_GRAPH_H_
#define BRANDAN_COSTAMAGNA_DIARTE_GRAPH_H_

/* basic directed graph type */
#include "constantes.h"

typedef struct WinterSt *WinterIsHere;
typedef struct successors *vertices;
typedef struct _nodo *nodo;

// Funciones De Construcción/Destrucción del grafo

WinterIsHere WinterIsComing();
/*
* aloca memoria, inicializa una estructura WinterSt ,lee un grafo desde standard
* input en el formato indicado, lo carga  y devuelve un puntero a ésta.
* Ademas debe colorea cada vertice con un color distinto (ésto es un coloreo propio)
* En caso de error, la función devolverá un puntero a NULL.
*/

void Primavera(WinterIsHere);
/*
* Destruye W y libera la memoria alocada.
* Retorna 1 si todo anduvo bien y 0 si no.
*/


// Funciones de coloreo

u32 Greedy(WinterIsHere W);
/*
* Corre greedy en W con el orden interno que debe estar guardado de alguna
* forma dentro de W. Devuelve el numero de colores que se obtiene.
*/

int Bipartito(WinterIsHere W);
/*
* Devuelve 1 si W es bipartito, 0 si no.
* Ademas, si devuelve 1, colorea W con un coloreo propio de dos colores.
*/


// Funciones para extraer información de datos del grafo

u32 NumeroDeVertices(WinterIsHere);
/* Devuelve el número de vértices de W. */

u32 NumeroDeLados(WinterIsHere);
/* Devuelve el número de lados (aristas) de W. */

u32 NumeroVerticesDeColor(WinterIsHere W, u32 i);
/* Retorna el número de vértices de color i. (debe retornar 0 si no hay
* vertices de color i).*/

u32 NumeroDeColores(WinterIsHere W);
/*
* Devuelve la cantidad de colores usados en el coloreo que tiene en ese momento W.
* es decir, el maximo color utilizado.
*/

u32 IesimoVerticeEnElOrden(WinterIsHere W, u32 i);
/*
* Devuelve la etiqueta del vértice numero i en el orden guardado en ese momento en W.
* (el ı́ndice 0 indica el primer vértice, el ı́ndice 1 el segundo, etc)
*/


// Funciones de ordenación
void OrdenNatural(WinterIsHere W);
void OrdenWelshPowell(WinterIsHere W);
void AleatorizarVertices(WinterIsHere W, u32 x);
void ReordenManteniendoBloqueColores(WinterIsHere W, u32 x);

// Funciones de los vertices

u32 ColorDelVertice(WinterIsHere W, u32 x);
/* Devuelve el nombre real del vértice cuya etiqueta es x. */

u32 GradoDelVertice(WinterIsHere W, u32 x);
/*
* el grado de un vértice es el número de aristas incidentes al vértice,
* es decir la cantidad de vecinos que posee el vertice con la etiqueta 'X'.
*/

u32 IesimoVecino(WinterIsHere W, u32 x, u32 i);
/*
* Devuelve la etiqueta del vécino numero i del vertice cuya etiqueta es x.
*/


// Funciones auxiliares, no exijidas en el proyecto.

/* add an edge to an existing graph */
void graph_add_edge(WinterIsHere, u32 source, u32 sink);

/* return 1 if edge (source, sink) exists), 0 otherwise */
int graph_has_edge(WinterIsHere, u32 source, u32 sink);

void ColorearVertice(WinterIsHere W, u32 vertice, u32 color);

// Del grafo W, al vertice x le coloco el nombre 'nombre'.
void setear_nombre_vertice(WinterIsHere W, u32 x, u32 nombre);

// Devuelve el nombre del vertice con la etiqueta x.
u32 NombreDelVertice(WinterIsHere W, u32 x);

/* Devuelve la etiqueta del vértice en cierta posición. */
u32 get_secuencia(WinterIsHere W, u32 posicion);

void printear_colores(WinterIsHere W);

void printear_orden(WinterIsHere W);

#endif  // BRANDAN_COSTAMAGNA_DIARTE_GRAPH_H_
