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
bool addArista(Grafo *grafo, int nodo_src, int nodo_dst);
void printMatriz(Grafo *grafo);
int gradoGrafo(Grafo *grafo);
int sumaGrados(Grafo *grafo);
int minGrado(Grafo *grafo);

bool cicloEnGrafo(Grafo *grafo);
bool validarCamino(Grafo *grafo, int *nodos_trayecto, int nodos_a_traversar);
int caminoValido(Grafo *grafo, int **ret_trayecto, int **ret_aristas, int src, int dst);

#endif
