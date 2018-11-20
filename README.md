# Proyecto de Matemática Discreta II-2017 #

## Integrantes:

* Nahuel Brandan. nahuelbrandan123@gmail.com

* Juan Costamagna. jcostamagna2000@hotmail.com

* Guillermo Diarte. guillermo_diarte@hotmail.com
***

## Objetivo del proyecto.

* El objetivo es cargar y dar un coloreo propio de sus vértices.

* Proveer las implementaciones de la especificación proveída por la cátedra.

![alt text](https://userscontent2.emaze.com/images/28a71159-458e-4c1c-be14-9a92f6c46241/f987d1af-ec10-43b1-98d8-80c9603703c5image13.jpeg "grafo coloreado")
***

## Diseño general del programa.
![alt text](https://k61.kn3.net/3/7/C/3/6/9/5EE.jpg "diseño general")

### Explicación general de cada uno de los TAD's.

* **JonSnow:**
    No provee ninguna funcionalidad, simplemente hace las llamadas a otros TAD's, sirve para que cuando creemos un main solamente tenemos que importar ésta interfaz.

* **graph:**
    Provee la funcionalidad propia del grafo, es el TAD más importante.

* **readline:**
    Provee la funcionalidad para la lectura del archivo de entrada. Éste TAD es reciclado de uno de los proyectos de Algoritmos y Estructuras de datos II.

* **cola:**
    Provee la funcionalidad básica de una cola, se obtuvo de wikipedia con ciertas modificaciones por nuestra parte.

* **hashtable:**
    Es una hashtable básica utilizada para poder chequear si un vértice ya fue creado previamente. Es un arreglo con un tamaño fijo, donde cada uno de sus elementos son punteros a una estructura DataItem.

* **constantes:**
    Unicamente contiene el tipo u32.
***

## Estructuras.

Las estructuras del grafo tienen la siguiente forma:

![alt text](https://k61.kn3.net/6/D/1/D/1/4/E2A.jpg "estructuras.")


La estructura WinterSt representa el grafo, y successors reprensenta los vértices.
***

## Greedy.
A lo largo del proyecto fuimos optimizando greedy para que cada vez demore menos, aqui una explicación de los pasos que hicimos:

### primera implementación:

* Para cada uno de los vértices, obtenidos del orden dado por secuencia[] hacemos:

	* Creamos un arreglo, de tamaño m (cantidad de vecinos), y lo 			completamos con el color de cada uno de los vecinos.

	* Luego a éste arreglo, tal cual está, hacemos un ciclo, revisando si existe el color 'i'. Si existe recorremos de nuevo el arreglo consultando 'i+1'. Sino existe coloreamos el vértice con dicho color 'i'.

Ésta implementación no es para nada óptima ya que en el peor de los casos podria recorrer múltiples veces el arreglo completo.

#### Tiempo de demora:

Al menos media hora para cada iteración de Greedy en el grafo de 2 millones de vértices y 10 millones de aristas.
***

### segunda implementación:
Una optimización al algoritmo anterior que no nos tomó mucho tiempo reconocerla es ordenar el arreglo de colores de los vecinos, ésto lo haciamos con la función qsort, proveida por la función stdlib, que tiene un orden n*log(n).

Con ésta optimización ya no hace falta recorrer todo el arreglo para saber si se encuentra el color 'i', podemos parar una vez que encontramos un valor mayor a 'i', ya que estamos seguros que tampoco se encontrará en las posiciones posteriores.

#### Tiempo de demora:

Una iteracion tardaba en promedio 5 segundos en las computadoras de la facu, para 1000 iteraciones eran al rededor de hora y media. Aceptable pero no lo suficiente.
***

### tercera implementación:

La última gran optimización, no se nos ocurrio a nosotros, sino que nos fue proveida la idea por un amigo integrante de otro grupo.

La idea es en vez de crear un arreglo de tamaño 'm' cantidad de vecinos, crear un arreglo de tamaño cantidad de colores utilizados hasta ése momento.

el algoritmo es el siguiente:

* Para cada uno de los vértices hacemos:

* Creamos un arreglo de tamaño 'cantidad de colores usados', seteamos todos los valores en cero.

* Consultamos el color de cada uno de los vecinos del vértice, cambiando el valor a 1 en la posición igual al color dado.

* Una vez hecho lo anterior para todos los vecinos, recorremos el arreglo en orden ascendente hasta encontrar un 0. Si lo encontramos quiere deecir que ése color no fue utilizado así que coloreamos el vértice con el valor de la posición. Sino encontramos ningún 0 quiere decir que todos los colores hasta el momento han sido utilizados, por lo tanto necesitamos usar un nuevo color.


#### Tiempo de demora:

En las computadoras de la facu tomó medio segundo una iteración de Greedy, para el grafo de 2 millones 'n' y 10 millones 'm'.

Esto indica que las 1000 iteraciones demoraría unos 8 minutos, excelente!.
***

## Consultas importantes a responder:

#### ¿Cómo solucionarion el problema si un vertice ya fue cargado previamente?
Utilizando un hashtable. Una vez terminada la carga ésta es eliminada.

#### ¿Qué tipo de estructura han pensado para los vecinos?
Los vecinos de un vértice es simplemente un arreglo que contienen las etiquetas de los vecinos. Asi con éstas etquetas podemos acceder al vértice propio del vecino.
***

## Funciones interesantes de comentar.

* **Bipartito**

fue un poco más complicado de lo que se pensó, hasta que eventualmente llegamos a la conclusión que necesitariamos un TAD cola para ir encolando los vertices que vamos coloreando, para poder así obtener un orden BFS.

* **ReordenManteniendoBloqueColores**

Primero se ordenan los vértices según el color de éstos.
Si la entrada es un '2' -> listo, ya está ordenado de ésta forma.
Si la entrada es un '3' -> se da vuelta el orden, swapeando (1,n) (2,n-1).. etc, hasta n/2.

Si la entrada es un '0' -> simplemente revisamos el mayor color, la cantidad de éstos y los enviamos al principio del arreglo.

Si la entrada es un '2' -> de la misma forma que en el caso de '0', pero ahora teniendo en cuenta ademas el segundo mayor color.
***

## Comentarios:

* Resulto más divertido e interesante de lo que esperabamos.

* Como no se nos pide, no guardamos el mejor coloreo del grafo, es decir el coloreo con el cual utilizo Chi colores.

* Siempre se tuvo como objetivo hacer código claro, entendible y actualizable.

## Contras.

* El tamaño del arreglo que utiliza la hashtable es fijo (esta seteado en 2 millones). Igual ésta estructura se utiliza únicamente en la carga del grafo, asi que no es un gran consumo de memoria prolongado.

* Según ésta ejecución con valgrind, con el grafo de 2 millones de vertices y 10 millones de aristas estaría utilizando al rededor de 1,5GB, es mucho, aunque el lado bueno es que no tiene memory leacks.

![alt text](https://k60.kn3.net/E/C/7/4/9/1/F6C.png "valgrind resultado")

### Ejecución:

Situados en el directorio raiz hacemos:

	gcc primeraparte/*.c mains/main.c -o greedy -Iprimeraparte -Wall -Werror -Wextra -pedantic -O3 -std=c99

y luego ejecutamos con:

	./greedy


O sino podemos utilizamos un makefile para compilar. Para probar hacer:

	make
	./greedy < in/chico

	"make clean" para limpiar.

En ambos casos estoy suponiendo que existe el archivo mains/main.c

Ejecución con valgrind.
valdrind:

	valgrind --leak-check=full ./greedy < in/grafo
	valgrind --leak-check=full --show-leak-kinds=all ./greedy < in/grafo

***
***



## **Mejoras luego de la devolución del profesor:**

* Se cambio el formato de entrada, para que ahora sea por stdin.

* Con respecto a la función **ReordenManteniendoBloqueColores()** claramente leimos la especificación muy muy mal. Se necesito de un cambio radical en la implementación.

En los casos en que el parámetro de entrada 'x' es 2,3, o mayor se aplica la misma idea, con la diferencia en la ordenación posterior utilizada.

![alt text](https://k61.kn3.net/5/F/9/E/6/1/0CF.jpg "reorden por bloque")

En el caso en que las entradas son 0 o 1 se las mejoraron pero la idea utilizada sigue siendo la misma que antes.

* Los algoritmos de ordenacion **OrdenNatural** y **WelshPowell** tambien se arreglaron.

* Uno de nuestro mayores problemas en la primera entrega fue utilizar una hashtable con un tamaño estático. Eso se reemplazo ahora por uno dinámico de tamaño n.Éste ahora se pasa por parámetro a las funciones.

* Por último la reserva de memoria en graph_create() fue modificada, es cierto que la anterior funcionaba, pero era poco intuitiva.


Se realizaron todas las modificaciones pedidas en la devolución.

***
## Mejoras luego de la segunda devolición.

Resulta que en Greedy teniamos un pequeño gran error.

Dentro de Greedy, en la parte de código donde ya coloreamos el vértice:

    if (!flag) {
        ColorearVertice(W, elemento, mejor_color);
    } else {
        k++;
        ColorearVertice(W, elemento, k);
    }

En el else tenemos que primero colorear con k, y luego a ésta variable sumarle uno. Quedando de la forma:

    if (!flag) {
        ColorearVertice(W, elemento, mejor_color);
    } else {
        ColorearVertice(W, elemento, k);
	    k++;
    }

Por último el return tiene que ser 'k-1' en vez de 'k' ya que no tomamos en cuenta la posición 0, 'k' tiene un elemento más del Chi correspondiente.

pd: le dejé los últimos printf de testeo que utilicé, para una mejor utilizacion eliminarselos.

