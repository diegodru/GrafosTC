#ifndef GRAFOS_H
#define GRAFOS_H

#include "common.h"

typedef struct{
   int src, dst;
}Arista;

typedef struct{
   int cantidadNodos;
   int **nodos;
   int cantidadAristas;
   Arista **aristas;
}Grafo;

Grafo *createGrafo(unsigned int cantidadNodos);
int findArista(Grafo *grafo, int src, int dst);
void addArista(Grafo *grafo, int nodo_src, int nodo_dst);
void printMatriz(Grafo *grafo);
int gradoGrafo(Grafo *grafo);
int sumaGrados(Grafo *grafo);
int minGrado(Grafo *grafo);

bool cicloEnGrafo(Grafo *grafo);
int caminoValido(Grafo *grafo, int **ret_trayecto, int **ret_aristas, int src, int dst);

#endif
