#ifndef GRAFOS_H
#define GRAFOS_H

#include "common.h"

typedef struct{
   int cantidadNodos;
   int **nodos;
}Grafo;

Grafo *createGrafo(unsigned int cantidadNodos);
void addArista(Grafo *grafo, int nodo_src, int nodo_dst);
void printMatriz(Grafo *grafo);
int gradoGrafo(Grafo *grafo);
int sumaGrados(Grafo *grafo);
int minGrado(Grafo *grafo);

bool cicloEnGrafo(Grafo *grafo);
int caminoValido(Grafo *grafo, int **ret_trayecto, int src, int dst);

#endif
