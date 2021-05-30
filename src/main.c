#include "cgraph.h"
#include "grafo.h"
//#include "draw.h"
#include "gvc.h"

static GVC_t *gvc;
static Agraph_t *g;
static Grafo *grafo;
static Agnode_t **nodos;
static Agedge_t **aristas;
static int cantAristas = 0;

void initGrafo(unsigned int cantidadNodos){
   gvc = gvContext();
   g = agopen("g", Agundirected, 0);
   grafo = createGrafo(cantidadNodos);
   nodos = (Agnode_t**)malloc(sizeof(Agnode_t*) * cantidadNodos);
   for(int i = 0; i < cantidadNodos; i++){
      char name[3];
      sprintf(name, "%i", i + 1);
      nodos[i] = agnode(g, name, 1);
   }
}

void agAddArista(int src, int dst){
   printf("1\n");
   addArista(grafo, src, dst);
   printf("2\n");
   Agedge_t **tmp = malloc(sizeof(Agedge_t*) * cantAristas + 1);
   printf("3\n");
   memcpy(tmp, aristas, sizeof(Agedge_t*) * cantAristas);
   printf("4\n");
   free(aristas);
   printf("5\n");
   aristas = tmp;
   printf("6\n");
   aristas[cantAristas++] = agedge(g, nodos[src], nodos[dst], 0, 1);
   printf("7\n");
}

int main(){
   /*
   Grafo *grafo = createGrafo(6);
   addArista(grafo, 0, 5);
   addArista(grafo, 5, 2);
   addArista(grafo, 2, 1);
   addArista(grafo, 3, 4);
   addArista(grafo, 4, 5);
   addArista(grafo, 5, 3);
   printf("Ciclo: %i\n", cicloEnGrafo(grafo));
   int *tr;
   int n = caminoValido(grafo, &tr, 1, 3);
   printf("Nodos Traversados: %i\n", n);
   for(int i = 0; i < n; i++)
      printf("%i\t", tr[i]);
   printf("\n");
   printf("Grado del grafo: %i\n", gradoGrafo(grafo));
   printf("Grado min: %i\n", minGrado(grafo));
   printf("Suma de grados: %i\n", sumaGrados(grafo));
   printMatriz(grafo);
   */
   //initGrafo(6);
   gvc = gvContext();
   g = agopen("g", Agundirected, 0);
   int cantidadNodos = 6;
   grafo = createGrafo(cantidadNodos);
   nodos = (Agnode_t**)malloc(sizeof(Agnode_t*) * cantidadNodos);
   for(int i = 0; i < cantidadNodos; i++){
      char name[3];
      sprintf(name, "%i", i + 1);
      nodos[i] = agnode(g, name, 1);
   }
   agAddArista(1, 4);
   Agedge_t *e = agedge(g, nodos[1], nodos[5], 0, 1);
   printf("1\n");
   gvLayout(gvc, g, "neato");
   printf("2\n");
   gvRender(gvc, g, "pdf", stdout);
   printf("3\n");
   gvFreeLayout(gvc, g);
   printf("4\n");
   agclose(g);
   return(gvFreeContext(gvc));
}
