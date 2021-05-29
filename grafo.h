#ifndef GRAFOS_H
#define GRAFOS_H

#include "common.h"

struct Node{
   int id;
};

typedef struct{
   struct Node *src, *dst;
}Arista;

typedef struct{
   unsigned int cantidadNodos;
   unsigned int cantidadAristas;
   struct Node **nodos;
   Arista **aristas;
}Grafo;

void printMatriz(Grafo *grafo);
Arista *createArista(struct Node *src, struct Node *dst);
Grafo *createGrafo(unsigned int cantidadNodos);
Grafo *addArista(Grafo *grafo, Arista *arista);
Arista **cicloEnGrafo(Grafo *grafo);

#endif
