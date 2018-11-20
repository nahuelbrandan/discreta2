#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "constantes.h"
#include "hashtable.h"

struct DataItem {
    bool utilizado;
    u32 key;
    u32 data;
};

ht* hash_create(u32 size){
    ht *htable = NULL;
    htable = calloc(size, sizeof(ht));

    for (u32 i = 0; i < size; i++) {
        htable[i] = calloc(1, sizeof(struct DataItem));
        htable[i]->utilizado = false;
        htable[i]->key = 0;
        htable[i]->data = 0;
    }
    return htable;
}

u32 hashCode(u32 size, u32 key) {
    return key % size;
}

/*
* Retorna size sino lo encuentra.
* Utilizamos éste valor ya que def es igual a la etiqueta, el cual va de 0
* a size-1, por lo tanto nunva llega a usar el valor size.
*/

// no recorremos todo el arreglo para ver si se encuentra. Colsultamos desde
// el hashIndex hasta el primer elemento libre que encontremos.
u32 search(ht *hashArray, u32 size, u32 key) {
    // get the hash
    u32 hashIndex = hashCode(size, key);
    u32 contador = 0;

    // moverme en el arreglo hasta encontrar un elemento utilizado.
    bool cut = true;
    while (contador < size && cut) {
        if (hashArray[hashIndex]->utilizado){
            if (hashArray[hashIndex]->key == key){
                return hashArray[hashIndex]->data;
            }
        } else {
            cut = false;
            // si encontramos un elemento no usado quiere decir que no se
            // encuentra el que buscamos. Sino en el peor de los casos se
            // hubiera cargado en éste elemento.
        }
        // go to next cell
        hashIndex++;
        // wrap around the table
        hashIndex %= size;
        contador++;
    }
    return size;
}

void insert(ht *hashArray,u32 size, u32 key, u32 data) {
    // get the hash
    u32 hashIndex = hashCode(size, key);
    // move in array until an empty cell
    while (hashArray[hashIndex]->utilizado) {
        // go to next cell
        hashIndex++;
        // wrap around the table
        hashIndex %= size;
    }
    hashArray[hashIndex]->key = key;
    hashArray[hashIndex]->data = data;
    hashArray[hashIndex]->utilizado = true;
}

void delete_ht(ht *hashArray, u32 size) {
    for (u32 i = 0; i < size; i++) {
        free(hashArray[i]);
        hashArray[i] = NULL;
    }
    free(hashArray);
    hashArray = NULL;
}

void display(ht *hashArray, u32 size) {
    for (u32 i = 0; i < size; i++) {
        if (hashArray[i] != NULL)
            printf(" (%u,%u)", hashArray[i]->key, hashArray[i]->data);
        else
            printf(" ~~ ");
    }
    printf("\n");
}
