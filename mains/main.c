/*
* main.c
*
* Written by Nahuel Brandan
* Copyright (c) 2017 Nahuel Brandan.
*
*/

#include "JonSnow.h"
 #include <time.h>

int main(void) {
    WinterIsHere g;
    g = WinterIsComing();

    // corremos Greedy.
    printf("Corremos greedy\n");
    u32 chi_mejor = 100000, chi_temporal = 0; // tomamos cien mil como infinito
    clock_t start = clock(), diff;

    for (u32 i = 0; i < 1; i++) {
        // AleatorizarVertices(g, i);
        printear_orden(g);

        chi_temporal = Greedy(g);

        if (chi_temporal < chi_mejor)
            chi_mejor = chi_temporal;
    }
    diff = clock() - start;

    printf("Chi = %u\n", chi_mejor);
    printf("*******************************************\n");
    int msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("Time taken %d seconds %d milliseconds\n\n", msec/1000, msec%1000);
    // ***************************************************
/*
    OrdenNatural(g);
    printf("\nOrden natural.\n");
    printear_orden(g);
    printear_colores(g);

    ReordenManteniendoBloqueColores(g, 0);
    printf("\nReorden manteniendo bloques con parametro 0\n");
    printf("Orden con color: r,1,2,3,...,r-1.\n");
    printear_orden(g);
    printear_colores(g);

    ReordenManteniendoBloqueColores(g, 1);
    printf("\nReorden manteniendo bloques con parametro 1\n");
    printf("Orden con color: r,r-1,r-2,...,2,1.\n");
    printear_orden(g);
    printear_colores(g);

    ReordenManteniendoBloqueColores(g, 2);
    printf("\nReorden manteniendo bloques con parametro 2\n");
    printf("Orden por cantidad: de menor a mayor.\n");
    printear_orden(g);
    printear_colores(g);

    ReordenManteniendoBloqueColores(g, 3);
    printf("\nReorden manteniendo bloques con parametro 3\n");
    printf("Orden por cantidad: de mayor a menor.\n");
    printear_orden(g);
    printear_colores(g);

    ReordenManteniendoBloqueColores(g, 4);
    printf("\nReorden manteniendo bloques con parametro 4\n");
    printf("Aleatorio dependiendo de x. Pero siempre en bloques.\n");
    printear_orden(g);
    printear_colores(g);

    ReordenManteniendoBloqueColores(g, 5);
    printf("\nReorden manteniendo bloques con parametro 5\n");
    printf("Aleatorio dependiendo de x. Pero siempre en bloques.\n");
    printear_orden(g);
    printear_colores(g);


    OrdenWelshPowell(g);
    printf("\nOrden welsh powell.\n");
    printear_orden(g);
    printear_colores(g);

    AleatorizarVertices(g , 5);
    printf("\nOrden aleatorio con key=5.\n");
    printear_orden(g);
    printear_colores(g);

    AleatorizarVertices(g , 32);
    printf("\nOrden aleatorio con key=32.\n");
    printear_orden(g);
    printear_colores(g);

    ReordenManteniendoBloqueColores(g, 2);
    printf("\nOrden RMBC con key=2.\n");
    printear_orden(g);
    printear_colores(g);

    ReordenManteniendoBloqueColores(g, 3);
    printf("\nOrden RMBC con key=3.\n");
    printear_orden(g);
    printear_colores(g);

    ReordenManteniendoBloqueColores(g, 1);
    printf("\nOrden RMBC con key=1.\n");
    printear_orden(g);
    printear_colores(g);

    ReordenManteniendoBloqueColores(g, 0);
    printf("\nOrden RMBC con key=0.\n");
    printear_orden(g);
    printear_colores(g);

    int res = Bipartito(g);
    if (res) {
        printf("BIPARTITO\n");
    } else {
        printf("NO ES BIPARTITO\n");
    }
*/
    // free it
    Primavera(g);
    return 0;
}
