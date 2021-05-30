#ifndef DRAW_H
#define DRAW_H

#include <gvc.h>
#include "grafo.h"

#define COLOR "skyblue"

static GVC_t *gvc;
static Agraph_t *g;
static Grafo *grafo;
static Agnode_t **nodos;
static Agedge_t **aristas;
static int cantAristas = 0;

void initGrafo(unsigned int cantidadNodos);
void agAddArista(int src, int dst);
void colorearCamino(int src, int dst);

#endif
