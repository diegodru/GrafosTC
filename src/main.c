#include "grafo.h"
#include "draw.h"
#include "gvc.h"

#define COLOR "skyblue"

void initGrafo(unsigned int cantidadNodos){
   gvc = gvContext();
   g = agopen("g", Agundirected, 0);
   grafo = createGrafo(cantidadNodos);
   nodos = (Agnode_t**)malloc(sizeof(Agnode_t*) * cantidadNodos);
   for(int i = 0; i < cantidadNodos; i++){
      char name[3];
      sprintf(name, "%i", i);
      nodos[i] = agnode(g, name, 1);
   }
}

void agAddArista(int src, int dst){
   addArista(grafo, src, dst);
   Agedge_t **tmp = malloc(sizeof(Agedge_t*) * cantAristas + 1);
   memcpy(tmp, aristas, sizeof(Agedge_t*) * cantAristas);
   free(aristas);
   aristas = tmp;
   aristas[cantAristas++] = agedge(g, nodos[src], nodos[dst], 0, 1);
}

void colorearCamino(int src, int dst){
   int *trayecto, *tr_aristas;
   int nodosTraversados = caminoValido(grafo, &trayecto, &tr_aristas, src, dst);
   for(int i = 0; i < nodosTraversados; i++){
      agsafeset(nodos[trayecto[i]], "color", COLOR, "");
      agsafeset(nodos[trayecto[i]], "style", "filled", "");
   }
   agsafeset(aristas[tr_aristas[0]], "label", "inicio", "");
   for(int i = 0; i < nodosTraversados - 1; i++){
      agsafeset(aristas[tr_aristas[i]], "color", COLOR, "");
   }
   agsafeset(aristas[tr_aristas[nodosTraversados - 2]], "label", "final", "");
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
   int *tr, *ar;
   int n = caminoValido(grafo, &tr, &ar, 1, 3);
   printf("Nodos Traversados: %i\n", n);
   for(int i = 0; i < n; i++)
      printf("%i\t", tr[i]);
   printf("\n");
   for(int i = 0; i < n - 1; i++)
      printf("%i\t", ar[i]);
   printf("\n");
   printf("Grado del grafo: %i\n", gradoGrafo(grafo));
   printf("Grado min: %i\n", minGrado(grafo));
   printf("Suma de grados: %i\n", sumaGrados(grafo));
   //printMatriz(grafo);
   */
   initGrafo(6);
   agAddArista(0, 5);
   agAddArista(5, 2);
   agAddArista(2, 1);
   agAddArista(3, 4);
   agAddArista(4, 5);
   agAddArista(5, 3);
   agAddArista(1, 4);
   gvLayout(gvc, g, "neato");
   colorearCamino(0, 2);
   gvLayoutJobs(gvc, g);
   gvRender(gvc, g, "pdf", stdout);
   gvFreeLayout(gvc, g);
   agclose(g);
   return(gvFreeContext(gvc));
}
