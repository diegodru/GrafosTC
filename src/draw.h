#ifndef DRAW_H
#define DRAW_H

#include <gvc.h>
#include "cgraph.h"
#include "grafo.h"

static GVC_t *gvc;
static Agraph_t *g;
static Grafo *grafo;
static Agnode_t **nodos;
static Agedge_t **aristas;
static int cantAristas = 0;

static void initGrafo(unsigned int cantidadNodos);
static void agAddArista(int src, int dst);

#endif
