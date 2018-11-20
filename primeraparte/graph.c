/*
* graph.c
*
* Written by Nahuel Brandan, Juan Costamagna, Guillermo Diarte.
* Copyright (c) 2017
*/

#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "graph.h"
#include "readline.h"
#include "hashtable.h"
#include "cola.h"

struct WinterSt {
    u32 n;              // cantidad de vertices.
    u32 m;              // cantidad de lados.
    u32 *secuencia;     // se utiliza para el orden dinámico.
    vertices *alist;  // lista de vertices del grafo.
};

struct successors {
    u32 nombre;         // nombre del vertice.
    u32 color;          // color asignado al vertice.
    u32 etiqueta;       // etiqueta del vertice.

    u32 d;              // cantidad de vecinos.
    u32 len;            // tamaño del arreglo de vecinos.
    u32 list[1];        // lista de etiquetas de los vecinos del vertice.
};

// Devuelve la etiqueta del vértice en cierta posición.
// Recordar que la posicion esta dada por el parametro secuencia.
u32 get_secuencia(WinterIsHere W, u32 posicion) {
    return W->secuencia[posicion];
}

/* Crea un nuevo grafo, con n vertices etiquetados de 0..n-1 y sin aristas.*/
WinterIsHere graph_create(u32 n) {
    WinterIsHere g;
    g = calloc(1, sizeof(struct WinterSt));
    assert(g);
    g->n = n;
    g->m = 0;
    g->secuencia = calloc(n, sizeof(u32));
    g->alist = calloc(n, sizeof(vertices));

    for (u32 i = 0; i < n; i++) {
        // por defecto los ordenamos por las etiquetas.
        g->secuencia[i] = i;

        g->alist[i] = calloc(1, sizeof(struct successors));
        assert(g->alist[i]);

        /* Como se pide que al crear un grafo además se le dé un coloreo
           propio, le asigno un color distinto a cada vértice.*/
        g->alist[i]->color = i+1;	 // color va de 1 a n.
        g->alist[i]->etiqueta = i;   // es la misma que la posicion.
        g->alist[i]->d = 0;          // por ahora 0 vecinos.
        g->alist[i]->len = 1;        // tamaño del arreglo de vecinos.
    }
    return g;
}

WinterIsHere WinterIsComing() {
    char *word  = NULL;  // tendra la primer palabra de una linea. c, p, e, _.
    char *word2 = NULL;  // tendrá el primer vértice del lado.
    char *word3 = NULL;  // tendrá el segundo vértice del lado.
    char *line  = NULL;  // para leer una linea del file.
    u32 first = 0;       // tendrá el primer valor en formato u32.
    u32 second = 0;      // tendrá el segundo valor en formato u32.
    u32 n = 0;           // cantidad de vertices.
    u32 m = 1;           // cantidad de lados.
    u32 etiqueta = 0;
    // etiqueta asignada a un vertice, sera un contador que llevara cuantos
    // vertices ya cree,
    u32 contador = 0;    // lleva la cuenta de lados cargados.
    WinterIsHere grafo = NULL;
    ht *htable = NULL;    // la hashtable.
    // ***********************************************

    // contador < m para que no siga leyendo aún si tuviera más lados.
    while (contador < m) {
        line = readline_from_stdin();
        if (line == NULL)
            /* caso de linea vacia. */
            continue;
        word = strtok(line, " ");
        // caso en que la primer palabra en una letra "c" de comentario.
        if (strcmp(word, "c") == 0) {
            // lo ignoramos.
        } else if (strcmp(word, "p") == 0) {
            // la forma de la entrada es de: p edge 11 20

            word = strtok(NULL, " ");    // contendria edge
            word2 = strtok(NULL, " ");   // contendria 11 en el ejemplo
            word3 = strtok(NULL, "\n");  // contendria 20 en el ejemplo

            sscanf(word2, "%u", &first);
            sscanf(word3, "%u\n", &second);

            // seteo los valores n y m del grafo.
            n = first;
            m = second;
            printf("n = %u, m = %u.\n", n, m);
            // creamos el hash
            htable = hash_create(n);
            assert(htable);

            // creamos un grafo.
            grafo = graph_create(n);
            assert(grafo);

        } else if (strcmp(word, "e") == 0) {
            // la forma de la entrada es de: e 13 28

            word2 = strtok(NULL, " ");
            word3 = strtok(NULL, "\n");

            sscanf(word2, "%u", &first);
            sscanf(word3, "%u\n", &second);

            // controlamos si ya existen dichos vertices.
            // recordar que search() devuelve n sino lo encuentra.
            u32 etiqueta_vertice1 = search(htable, n, first);
            if (etiqueta_vertice1 >= n) {
                // quiere decir que el vertice es nuevo, hay que crearlo.
                insert(htable, n, first, etiqueta);
                // luego usaremos etiqueta_vertice1.
                etiqueta_vertice1 = etiqueta;
                etiqueta++;
            }
            // hacemos lo mismo para el segundo vertice.
            u32 etiqueta_vertice2 = search(htable, n, second);
            if (etiqueta_vertice2 >= n) {
                // quiere decir que el vertice es nuevo, hay que crearlo.
                insert(htable, n, second, etiqueta);
                etiqueta_vertice2 = etiqueta;
                etiqueta++;
            }
            /* En éste punto ya las variables etiqueta_vertice 1 y 2 ya
               tienen el valor de las etiquetas de los respectivos vertices.

               Como el grafo esta ordenado con respecto a ésta etiqueta
               podemos acceder de manera constante al vertice que queremos.
            */

            // seteamos los nombres de vertices en la posicion etiqueta.
            setear_nombre_vertice(grafo, etiqueta_vertice1, first);
            setear_nombre_vertice(grafo, etiqueta_vertice2, second);

            // agregamos las aristas (first, second) y (second, first);
            graph_add_edge(grafo, etiqueta_vertice1, etiqueta_vertice2);
            graph_add_edge(grafo, etiqueta_vertice2, etiqueta_vertice1);

            grafo->m++;
            contador++;
        } else {
            printf("Formato de entrada invalido\n");
            free(line);
            line = NULL;
            return NULL;
        }
        free(line);
        line = NULL;
    }
    // una vez terminada la carga destruimos la hashtable.
    delete_ht(htable, n);
    return (grafo);
}

// Destruye g y libera la memoria alocada. Retorna 1 si anduvo bien y 0 si no.
void Primavera(WinterIsHere g) {
    for (u32 i = 0; i < g->n; i++) {
        // libero cada uno de los vértices.
        free(g->alist[i]);
    }
    free(g->secuencia);
    g->secuencia = NULL;
    free(g->alist);
    g->alist = NULL;
    free(g);
    g = NULL;

}

u32 NumeroVerticesDeColor(WinterIsHere g, u32 i) {
    u32 contador = 0;
    for (u32 j = 0; j < g->n; j++) {
        if (g->alist[j]->color == i) {
            contador++;
        }
    }
    return contador;
}

// es equivalente a buscar el vértice con mayor color.
u32 NumeroDeColores(WinterIsHere g) {
    u32 mayor = 0;
    for (u32 i = 0; i < g->n; i++) {
        if (g->alist[i]->color > mayor) {
            mayor = g->alist[i]->color;
        }
    }
    return mayor;
}

// agregar lado a un grafo existente.
void graph_add_edge(WinterIsHere g, u32 u, u32 v) {
    assert(u < g->n);
    assert(v < g->n);

    // se agranda el arreglo de vecinos si lo llegaramos a necesitar.
    while (g->alist[u]->d >= g->alist[u]->len) {
        g->alist[u]->len *= 2;
        g->alist[u] = realloc(g->alist[u], sizeof(struct successors) +
                        sizeof(u32) * (g->alist[u]->len - 1));
    }

    // ahora agregamos el nuevo vecino.
    g->alist[u]->list[g->alist[u]->d++] = v;

}

// Devuelve el número de vértices de g.
u32 NumeroDeVertices(WinterIsHere g) {
    return g->n;
}

// Devuelve el número de lados (aristas) de g.
u32 NumeroDeLados(WinterIsHere g) {
    return g->m;
}

// Devuelve el grado del vértice con la etiqueta x. (cantidad de vecinos).
u32 GradoDelVertice(WinterIsHere g, u32 x) {
    assert(x < g->n);
    return g->alist[x]->d;
}

u32 ColorDelVertice(WinterIsHere g, u32 x) {
    // Recordemos x es la etiqueta del vértice.
    return g->alist[x]->color;
}

u32 IesimoVecino(WinterIsHere g, u32 x, u32 i) {
    return g->alist[x]->list[i];
}

u32 Greedy(WinterIsHere W) {
    printf("\n\nDentro de Greedy\n");
    u32 n = NumeroDeVertices(W);
    u32 mejor_color = 0;  // color a darle al vértice.

    // k será la cantidad de colores utilizados hasta el momento.
    // Se inicializa en 2 para tener la posicion 0 y 1. La 0 la ignoramos.
    u32 k = 2;

    // primero setear todos los colores de los vertices a 0.
    for (u32 i = 0; i < n; i++) {
        ColorearVertice(W, i, 0);
    }
    printear_colores(W);

    for (u32 i = 0; i < n; i++) {
        /* Pido los colores de los vecinos del vertice i y lo guardo en un
           arreglo de tamaño k, con k cantidad de colores usados hasta el momento.*/
        u32 elemento = W->secuencia[i];
        printf("elemento[%u] = %u\n", i, elemento);
        u32 cantidad_vecinos = GradoDelVertice(W, elemento);
        printf("cantidad_vecinos = %u\n", cantidad_vecinos);

        // creo el array para guardar los colores.
        u32 colores_vecinos[k];

        // seteo los elementos del arreglo en cero.
        for (u32 a = 0; a < k; a++) {
            colores_vecinos[a] = 0;
        }

        // pido y guardo el color del vecino j del vertice i.
        for (u32 j = 0; j < cantidad_vecinos; j++) {
            u32 etiqueta_vecino = IesimoVecino(W, elemento, j);
            colores_vecinos[ColorDelVertice(W, etiqueta_vecino)] = 1;
        }

        printf("Lista de colores de los vecinos\n [ ");
        for (u32 q = 0; q < k; q++){
            printf("%u ", colores_vecinos[q]);
        }
        printf("]\n*******************\n");

        /*  ahora el color a pintar va a ser la posicion del primer
        *  elemento = 0 del arreglo. Omitiendo la posicion 0. */
        u32 j = 1;
        bool flag = true;
        while (j < k && flag) {
            if (colores_vecinos[j] == 0) {
                mejor_color = j;
                flag = false;
            } else {
                j++;
            }
        }

        /*
         En éste punto si flag = false quiere decir que se encontro el mejor color, por lo tanto coloramos
         el vertice i con dicho color.

         Por el contrario si flag = true, indica que no se encontro, por lo tanto necesitamos un color nuevo
         (k+1).
        */

        if (!flag) {
            // es éste punto ya podemos colorear el vértice i con el mejor_color.
            printf("coloreamos el vertice %u con %u\n\n", elemento, mejor_color);
            ColorearVertice(W, elemento, mejor_color);
        } else {
            printf("ELSE: coloreamos el vertice %u con %u\n\n", elemento, k);
            ColorearVertice(W, elemento, k);
            k++;
        }
    }

    /*
    Como k lo inicializamos en 2, le restamos 1 que sobra, (la posicion 0)
    */
    return k-1;
}

int Bipartito(WinterIsHere W) {
    u32 n = NumeroDeVertices(W);

    // creo una cola.
    queue_t * cola = createQueue();

    // primero seteo el color de todos los vertices en 0.
    for (u32 i = 0; i < n; i++) {
        ColorearVertice(W, i, 0);
    }

    // tomo el primer vertice, lo coloreo con 1 y lo encolo.
    ColorearVertice(W, 0, 1);
    enqueue(0, cola);
    bool cut = true;  // cortamos la iteracion cuando NO sea bipartito.
    while (!isEmpty(cola) && cut) {
        u32 head = dequeue(cola);
        u32 color_head = ColorDelVertice(W, head);
        // ahora laburamos siempre con la cabeza.

        // Cantidad de vecinos.
        u32 grado = GradoDelVertice(W, head);

        // coloreamos a cada uno de los vecinos de head que no tengan color 0.
        for (u32 i = 0; i < grado; i++) {
            u32 vecino = IesimoVecino(W, head, i);

            // coloreamos
            if (ColorDelVertice(W, vecino) == 0) {
                ColorearVertice(W, vecino, color_head+1%2);

                // agregamos el vecino a la cola.
                enqueue(vecino, cola);
            }

            // si algun vecino tiene el mismo color que el head
            // cortamos la ejecución, significa que no es bipartito.

            if (ColorDelVertice(W, vecino) == color_head) {
                cut = false;
            }
        }
    }

    if (cut)
        return 1;
    else
        return 0;
}

void ColorearVertice(WinterIsHere W, u32 vertice, u32 color) {
    W->alist[vertice]->color = color;
}

void setear_nombre_vertice(WinterIsHere g, u32 x, u32 nombre) {
    g->alist[x]->nombre = nombre;
}

u32 NombreDelVertice(WinterIsHere W, u32 x) {
    return (W->alist[x]->nombre);
}

static vertices *ver;

int OrdenNaturalComp(const void *ap, const void *bp) {
    u32 a = *((u32*)ap);
    u32 b = *((u32*)bp);

    vertices av = ver[a];
    vertices bv = ver[b];

    if(av->nombre > bv->nombre) return 1;
    if(av->nombre == bv->nombre) return 0;
    return -1;
}

void OrdenNatural(WinterIsHere W) {
    ver = W->alist;
    u32 size = NumeroDeVertices(W);
    qsort(W->secuencia, size, sizeof(u32), OrdenNaturalComp);
}

int OrdenWelshComp(const void *ap, const void *bp) {
    u32 a = *((u32*)ap);
    u32 b = *((u32*)bp);

    vertices av = ver[a];
    vertices bv = ver[b];

    if(av->d < bv->d) return 1;
    if(av->d == bv->d) return 0;
    return -1;
}

void OrdenWelshPowell(WinterIsHere W) {
    ver = W->alist;
    u32 size = NumeroDeVertices(W);
    qsort(W->secuencia, size, sizeof(u32), OrdenWelshComp);
}

static void swap(u32 * array, u32 i, u32 j) {
    u32 t = array[j];
    array[j] = array[i];
    array[i] = t;
}

void AleatorizarVertices(WinterIsHere W, u32 key) {
    u32 size = NumeroDeVertices(W);
    u32 position = 0;
    // primeto seteamos todos los valores en en orden, de 0 a n-1.
    for (u32 i = 0; i < size; i++) {
        W->secuencia[i] = i;
    }
    srand(key);
    for (u32 i = 0; i < size; i++) {
        position = rand();
        position = position % size;

        swap(W->secuencia, i, position);
    }
}

u32 IesimoVerticeEnElOrden(WinterIsHere W, u32 i) {
    return W->secuencia[i];
}

int OrdenPorColor(const void *ap, const void *bp) {
    u32 a = *((u32*)ap);
    u32 b = *((u32*)bp);

    vertices av = ver[a];
    vertices bv = ver[b];

    if(av->color > bv->color) return 1;
    if(av->color == bv->color) return 0;
    return -1;
}

int OrdenPorColorInvertido(const void *ap, const void *bp) {
    u32 a = *((u32*)ap);
    u32 b = *((u32*)bp);

    vertices av = ver[a];
    vertices bv = ver[b];

    if(av->color < bv->color) return 1;
    if(av->color == bv->color) return 0;
    return -1;
}


struct _nodo {
	u32 size;
	u32 * vertices;
};

int OrdenPorCantidad(const void *ap, const void *bp) {
    nodo a = *((nodo*)ap);
    nodo b = *((nodo*)bp);

    if(a->size > b->size) return 1;
    if(a->size == b->size) return 0;
    return -1;
}

int OrdenCantidad2(const void *ap, const void *bp) {
    nodo a = *((nodo*)ap);
    nodo b = *((nodo*)bp);

    if(a->size < b->size) return 1;
    if(a->size == b->size) return 0;
    return -1;
}

static void swap_nodos(nodo *array, u32 i, u32 j) {
    nodo t = array[j];
    array[j] = array[i];
    array[i] = t;
}

void ReordenManteniendoBloqueColores(WinterIsHere W, u32 x) {
    ver = W->alist;
    u32 size = NumeroDeVertices(W);

    // ordeno los vertices con repecto a los colores.
    qsort(W->secuencia, size, sizeof(u32), OrdenPorColor);

    if (x >= 2) {
        // |VC1| <= |VC2| <= ... <= |VCr| si x = 2
        // |VC1| >= |VC2| >= ... >= |VCr| si x = 2

        // el procedimiento es el mismo, con la diferencia en el qsort de
        // ordenacion utilizado para los casos en que x = 2, x = 3, x > 3.

    	// cantidad de colores utilizados.
        u32 maximo_color = NumeroDeColores(W);

        nodo array_colores[maximo_color];

        // inicializacion
        for (u32 i = 0; i < maximo_color; i++) {
        	// los colores van de 1 a n.
        	u32 cant = NumeroVerticesDeColor(W, i+1);

            array_colores[i] = calloc(1, sizeof(struct _nodo));
        	array_colores[i]->size = cant;
            array_colores[i]->vertices = calloc(cant, sizeof(u32));
        }

        // coloco los vertices en los arreglos. Se puede hacer así por que
        // previamente fue ordenado.
        u32 posicion = 0;
        for (u32 i = 0; i < maximo_color; i++) {
            for (u32 j = 0; j < array_colores[i]->size; j++) {
                array_colores[i]->vertices[j] = W->secuencia[posicion];
                posicion++;
            }
        }
		// en éste punto ya tengo un arreglo separado en bloque de colores.

        // ordenar array_colores dependiendo el valor de x.
        if (x == 2)
            qsort(array_colores, maximo_color, sizeof(nodo), OrdenPorCantidad);
        else if (x == 3)
            qsort(array_colores, maximo_color, sizeof(nodo), OrdenCantidad2);
        else {
            srand(x);
            u32 position = 0;
            for (u32 i = 0; i < maximo_color; i++) {
                position = rand();
                position = position % maximo_color;

                swap_nodos(array_colores, i, position);
            }
        }

        // secuencia final colocar en orden los vertices en el arreglo final.
        posicion = 0;
        for (u32 i = 0; i < maximo_color; i++) {
            for (u32 j = 0; j < array_colores[i]->size; j++) {
                W->secuencia[posicion] = array_colores[i]->vertices[j];
                posicion ++;
            }
        }

        // libero la memoria reservada.
        for(u32 i = 0; i < maximo_color; i++) {
            free(array_colores[i]->vertices);
            array_colores[i]->vertices = NULL;
            free(array_colores[i]);
            array_colores[i] = NULL;
        }
    } else if (x == 0) {
        // orden respecto colores = r,1,2,3,..,r-1.
        // tengo que ver la cantidad de vertices que hay con el maximo color.
        u32 maximo_color = NumeroDeColores(W);
        u32 cantidad = NumeroVerticesDeColor(W, maximo_color);

        u32 array_aux[size];
        // array auxiliar.
        // seteo los valores del arreglo en 0.
        for(u32 i = 0; i < size; i++){
            array_aux[i] = 0;
        }

        //coloco al principio los vertices de mayor color.
        for (u32 i = 0; i < cantidad; i++) {
            array_aux[i] = W->secuencia[size-1-i];
        }

        // luego coloco el resto de los colores, en el mismo orden.
        for (u32 i = cantidad; i < size; i++) {
            array_aux[i] = W->secuencia[i - cantidad];
        }

        // ahora al W->secuencia le asigno los valores que tiene array_aux.
        for (u32 i = 0; i < size; i++) {
            W->secuencia[i] = array_aux[i];
        }
    } else if (x == 1) {
        // orden respecto colores = r,r-1,r-2,...,2,1.
  		// orden invertido con respecto a los colores.
    	qsort(W->secuencia, size, sizeof(u32), OrdenPorColorInvertido);
    }
}

/*
* Funciones auxiliares para printear por pantalla el orden
* y el coloreo en dicho orden.
*/

void printear_colores(WinterIsHere W) {
    u32 cantidad = NumeroDeVertices(W);

    printf("Colores en el orden dado = [ ");
    for (u32 i=0; i < cantidad; i++) {
        printf("%u ", ColorDelVertice(W, W->secuencia[i]));
    }
    printf("]\n");
}

void printear_orden(WinterIsHere W) {
    u32 cantidad = NumeroDeVertices(W);

    printf("Orden dado = [ ");
    for (u32 i=0; i < cantidad; i++) {
        printf("%u ", NombreDelVertice(W,   W->secuencia[i]));
    }
    printf("]\n");
}
