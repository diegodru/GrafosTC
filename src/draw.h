#ifndef DRAW_H
#define DRAW_H

#include <gvc.h>
#include "cgraph.h"
#include "grafo.h"

#define COLOR "skyblue"

static GVC_t *gvc;
static Agraph_t *g;
static Grafo *grafo;
static Agnode_t **nodos;
static Agedge_t **aristas;
static int cantAristas;

void initGrafo(unsigned int cantidadNodos, GVC_t **gvc, 
      Agraph_t **g, Grafo **grafo);
void agAddArista(Grafo **graf, int src, int dst);
void colorearCamino(int src, int dst);
void colorearCaminoValido(int *nodos_a_traversar, int cantidadNodos);
void resetColors();

#endif
