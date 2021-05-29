#include "grafo.h"

Arista *createArista(struct Node *src, struct Node *dst){
   Arista *res = (Arista*)malloc(sizeof(Arista*));
   res->src = src;
   res->dst = dst;
   return res;
}

Grafo *createGrafo(unsigned int cantidadNodos){
   Grafo *res = (Grafo*)malloc(sizeof(Grafo*));
   res->cantidadNodos = cantidadNodos;
   res->nodos = malloc(sizeof(struct Node*) * cantidadNodos);
   for(int i = 0; i < cantidadNodos; i++){
      res->nodos[i] = malloc(sizeof(struct Node));
      res->nodos[i]->id = i + 1;
   }
   res->cantidadAristas = 0;
   return res;
}

Grafo *addArista(Grafo *grafo, Arista *arista){
   Arista **aristas = malloc(sizeof(Arista*) * grafo->cantidadAristas + 1);
   memcpy(aristas, grafo->aristas, sizeof(Arista*) * grafo->cantidadAristas);
   free(grafo->aristas);
   aristas[grafo->cantidadAristas++] = arista;
   grafo->aristas = aristas;
   return grafo;
}

void printMatriz(Grafo *grafo){
   printf("\t");
   for(int i = 0; i < grafo->cantidadNodos; i++)
      printf("%i\t", grafo->nodos[i]->id);
   printf("\n");
   for(int i = 0; i < grafo->cantidadNodos; i++){
      printf("%i\t", grafo->nodos[i]->id);
      for(int j = 0; j < grafo->cantidadNodos; j++){
      }
   }

}
