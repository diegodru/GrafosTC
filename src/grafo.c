#include "grafo.h"

Grafo *createGrafo(unsigned int cantidadNodos){
   Grafo *grafo = (Grafo*)malloc(sizeof(Grafo));
   grafo->nodos = (int**)malloc(sizeof(int*) * cantidadNodos);
   for(int i = 0; i < cantidadNodos; i++){
      grafo->nodos[i] = (int*)malloc(sizeof(int) * cantidadNodos);
      for(int j = 0; j < cantidadNodos; j++)
         grafo->nodos[i][j] = 0;
   }
   grafo->cantidadNodos = cantidadNodos;
   return grafo;
}

//ineficiente
int findArista(Grafo *grafo, int src, int dst){
   for(int i = 0; i < grafo->cantidadAristas; i++){
      int gr_src = grafo->aristas[i]->src,
          gr_dst = grafo->aristas[i]->dst;
      if((gr_src == src && gr_dst == dst) ||
            (gr_dst == src && gr_src == dst))
         return i;
   }
   return -1;
}

void addArista(Grafo *grafo, int nodo_src, int nodo_dst){
   if(nodo_src >= grafo->cantidadNodos || nodo_src < 0 ||
         nodo_dst >= grafo->cantidadNodos || nodo_dst < 0)
      return;
   Arista **tmp = malloc(sizeof(Arista*) * grafo->cantidadAristas + 1);
   memcpy(tmp, grafo->aristas, sizeof(Arista*) * grafo->cantidadAristas);
   free(grafo->aristas);
   grafo->aristas = tmp;
   Arista *ar = malloc(sizeof(Arista));
   ar->src = nodo_src;
   ar->dst = nodo_dst;
   grafo->aristas[grafo->cantidadAristas++] = ar;
   grafo->nodos[nodo_src][nodo_dst] = 1;
   grafo->nodos[nodo_dst][nodo_src] = 1;
}

void printMatriz(Grafo *grafo){
   printf("\t");
   int cantidadNodos = grafo->cantidadNodos;
   for(int i = 0; i < cantidadNodos; i++)
      printf("%i\t", i);
   printf("\n");
   for(int i = 0; i < cantidadNodos; i++){
      printf("%i\t", i);
      for(int j = 0; j < cantidadNodos; j++)
         printf("%i\t", grafo->nodos[i][j]);
      printf("\n");
   }
   printf("\n");
}

int gradoGrafo(Grafo *grafo){
   int grado = 0;
   int cantidadNodos = grafo->cantidadNodos;
   for(int i = 0; i < cantidadNodos; i++){
      int grado_actual = 0;
      for(int j = 0; j < cantidadNodos; j++)
         grado_actual += grafo->nodos[i][j];
      if(grado_actual > grado)
         grado = grado_actual;
   }
   return grado;
}

// No estoy seguro
int sumaGrados(Grafo *grafo){
   int suma = 0;
   int cantidadNodos = grafo->cantidadNodos;
   for(int i = 0; i < cantidadNodos; i++){
      for(int j = 0; j < cantidadNodos; j++)
         suma += grafo->nodos[i][j];
   }
   return suma;
}

int minGrado(Grafo *grafo){
   int min = grafo->cantidadNodos;
   int cantidadNodos = grafo->cantidadNodos;
   for(int i = 0; i < cantidadNodos; i++){
      int grado_actual = 0;
      for(int j = 0; j < cantidadNodos; j++)
         grado_actual += grafo->nodos[i][j];
      if(grado_actual < min && grado_actual > 0)
         min = grado_actual;
   }
   return min;
}

bool recurseGrafoCiclo(bool *visitado, int prevNodo, int nodoActual, Grafo *grafo){
   if(visitado[nodoActual]++)
      return true;
   for(int i = 0; i < grafo->cantidadNodos; i++){
      if(grafo->nodos[nodoActual][i] && i != prevNodo)
         if(recurseGrafoCiclo(visitado, nodoActual, i, grafo))
            return true;
   }
   return false;
}

bool cicloEnGrafo(Grafo *grafo){
   bool *visitado = malloc(sizeof(int) * grafo->cantidadNodos);
   return recurseGrafoCiclo(visitado, 0, 0, grafo);
}

bool 
recurseGrafoCamino(bool *visitado, int *trayecto, int *aristas, 
      int *nodosTraversados, int prevNodo, int nodoActual, int dst, Grafo *grafo){
   if(visitado[nodoActual]++)
      return false;
   if((*nodosTraversados) > 0)
      aristas[(*nodosTraversados) - 1] = findArista(grafo, prevNodo, nodoActual);
   trayecto[(*nodosTraversados)++] = nodoActual;
   if(nodoActual == dst)
      return true;
   for(int i = 0; i < grafo->cantidadNodos; i++){
      if(grafo->nodos[nodoActual][i] && i != prevNodo && i != nodoActual){
         if(recurseGrafoCamino(visitado, trayecto, aristas,
                  nodosTraversados, nodoActual, i, dst, grafo))
            return true;
      }
   }
   (*nodosTraversados)--;
   return false;
}

int caminoValido(Grafo *grafo, int **ret_trayecto, int **ret_aristas, int src, int dst){
   bool *visitado = malloc(sizeof(int) * grafo->cantidadNodos);
   for(int i = 0; i < grafo->cantidadNodos; i++)
      visitado[i] = 0;
   int *trayecto = malloc(sizeof(int) * grafo->cantidadNodos), 
       *aristas = malloc(sizeof(int) * grafo->cantidadAristas);
   int nodosTraversados = 0;
   recurseGrafoCamino(visitado, trayecto, aristas, &nodosTraversados,
         -1, src, dst, grafo);
   (*ret_trayecto) = malloc(sizeof(int) * nodosTraversados);
   (*ret_aristas) = malloc(sizeof(int) * nodosTraversados - 1);
   memcpy((*ret_trayecto), trayecto, sizeof(int) * (nodosTraversados));
   memcpy((*ret_aristas), aristas, sizeof(int) * (nodosTraversados - 1));
   return nodosTraversados;
}

