#include "grafo.h"

int main(){
   Grafo *grafo = createGrafo(6);
   addArista(grafo, 0, 5);
   addArista(grafo, 5, 2);
   addArista(grafo, 2, 1);
   addArista(grafo, 3, 4);
   addArista(grafo, 4, 5);
   addArista(grafo, 5, 3);
   printf("Ciclo: %i\n", cicloEnGrafo(grafo));
   int *tr;
   int n = caminoValido(grafo, &tr, 0, 4);
   printf("Nodos Traversados: %i\n", n);
   for(int i = 0; i < n; i++)
      printf("%i\t", tr[i]);
   printf("\n");
   printf("Grado del grafo: %i\n", gradoGrafo(grafo));
   printf("Grado min: %i\n", minGrado(grafo));
   printf("Suma de grados: %i\n", sumaGrados(grafo));
   //printMatriz(grafo);
}
