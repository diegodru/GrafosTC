#include "cgraph.h"
#include "grafo.h"
#include "draw.h"
#include "gvc.h"
#include "menu.h"

#define CAMINO_COLOR "skyblue"
#define SHAPE "circle"

static GVC_t *gvc;
static Agraph_t *g;
static Grafo *grafo;
static Agnode_t **nodos;
static Agedge_t **aristas;
static int cantAristas;

/*
void initGrafo(unsigned int cantidadNodos, GVC_t **gvc, 
      Agraph_t **g, Grafo **grafo);
void agAddArista(Grafo **graf, int src, int dst);
void colorearCamino(int src, int dst);
void colorearCaminoValido(int *nodos_a_traversar, int cantidadNodos);
*/

void anadirArista(){
   char buf[8];
   int src, dst;
   printf("Ingrese Nodo de inicio: ");
   scanf("%s", buf);
   src = atoi(buf);
   printf("Ingrese Nodo de destino: ");
   scanf("%s", buf);
   dst = atoi(buf);
   agAddArista(&grafo, src, dst);
}

void crearGrafo(){
   char buf[8];
   int cantidadNodos;
   printf("Ingrese la cantidad de Nodos deseados en el grafo: ");
   scanf("%s", buf);
   if((cantidadNodos = atoi(buf)) == 0)
      return;
   initGrafo(cantidadNodos, &gvc, &g, &grafo);
}

void initGrafo(unsigned int cantidadNodos, GVC_t **gvc, Agraph_t **g, 
      Grafo **grafo){
   *gvc = gvContext();
   *g = agopen("g", Agundirected, 0);
   *grafo = createGrafo(cantidadNodos);
   nodos = (Agnode_t**)malloc(sizeof(Agnode_t*) * cantidadNodos);
   cantAristas = 0;
   for(int i = 0; i < cantidadNodos; i++){
      char name[3];
      sprintf(name, "%i", i);
      nodos[i] = agnode(*g, name, 1);
      agsafeset(nodos[i], "shape", SHAPE, "");
   }
}

void agAddArista(Grafo **graf, int src, int dst){
   addArista(*graf, src, dst);
   Agedge_t **tmp = malloc(sizeof(Agedge_t*) * cantAristas + 1);
   memcpy(tmp, aristas, sizeof(Agedge_t*) * cantAristas);
   free(aristas);
   aristas = tmp;
   printf("cant: %i\n", cantAristas);
   aristas[cantAristas++] = agedge(g, nodos[src], nodos[dst], 0, 1);
}

void colorearCamino(int src, int dst){
   int *trayecto, *tr_aristas;
   int nodosTraversados = caminoValido(grafo, &trayecto, &tr_aristas, src, dst);
   for(int i = 0; i < nodosTraversados; i++){
      agsafeset(nodos[trayecto[i]], "color", CAMINO_COLOR, "");
      agsafeset(nodos[trayecto[i]], "style", "filled", "");
   }
   agsafeset(aristas[tr_aristas[0]], "label", "inicio", "");
   for(int i = 0; i < nodosTraversados - 1; i++){
      agsafeset(aristas[tr_aristas[i]], "color", CAMINO_COLOR, "");
   }
   agsafeset(aristas[tr_aristas[nodosTraversados - 2]], "label", "final", "");
}

void colorearCaminoValido(int *nodos_a_traversar, int cantidadNodos){
   if(!validarCamino(grafo, nodos_a_traversar, cantidadNodos))
      return;
   for(int i = 0; i < cantidadNodos; i++){
      agsafeset(nodos[nodos_a_traversar[i]], "color", CAMINO_COLOR, "");
      agsafeset(nodos[nodos_a_traversar[i]], "style", "filled", "");
   }
   agsafeset(aristas[findArista(grafo, nodos_a_traversar[0], nodos_a_traversar[1])], "label", "inicio", "");
   for(int i = 1; i < cantidadNodos; i++)
      agsafeset(aristas[findArista(grafo, nodos_a_traversar[i - 1], nodos_a_traversar[i])], "color", CAMINO_COLOR, "");
   agsafeset(aristas[findArista(grafo, nodos_a_traversar[cantidadNodos - 2], nodos_a_traversar[cantidadNodos - 1])], "label", "final", "");
}

int main(int argc, char *argv[]){
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
   int nodosATravesar[] = { 1, 2, 5 };
   printf("Valido: %i\n", validarCamino(grafo, nodosATravesar, 3));
   //printMatriz(grafo);
   */
   /*
   initGrafo(6, &gvc, &g, &grafo, &nodos);
   agAddArista(0, 5);
   agAddArista(5, 2);
   agAddArista(2, 1);
   agAddArista(3, 4);
   agAddArista(4, 5);
   agAddArista(5, 3);
   agAddArista(1, 4);
   gvLayout(gvc, g, "neato");
   int nodosATravesar[] = { 1, 2, 5 };
   colorearCaminoValido(nodosATravesar, 3);
   
   //colorearCamino(atoi(argv[1]), atoi(argv[2]));
   gvLayoutJobs(gvc, g);
   gvRender(gvc, g, "pdf", stdout);
   gvFreeLayout(gvc, g);
   agclose(g);
   return(gvFreeContext(gvc));
   */
   FILE *pdf;
   while(1){
      printf(BANNER "\n\
            1.Crear Grafo\n");
      if(grafo)
         printf("\
            2.Agregar Arista\n\
            3.Imprimir Matriz de Adyacencia\n\
            4.Calcular Grado del grafo\n\
            5.Calcular la suma de los grados de las vertices\n\
            6.Calcular el grado minimo de las vertices\n\
            7.Validar Camino\n\
            8.Detectar Ciclo\n\
            9.Salvar grafo en un pdf\n");
      printf("\
            10.Salir\n\n");
      char buf[10];
      printf("Seleccione una Opcion: ");
      scanf("%s", buf);
      if(atoi(buf) == 0)
         continue;
      switch(atoi(buf)){
         case 1:
            crearGrafo();
            break;
         case 2:
            anadirArista();
            break;
         case 3:
            printMatriz(grafo);
            break;
         case 4:
            printf("Grado del grafo: %i\n", gradoGrafo(grafo));
            break;
         case 5:
            printf("Suma de los Grados: %i\n", sumaGrados(grafo));
            break;
         case 6:
            printf("El grado minimo: %i\n", minGrado(grafo));
            break;
         case 7:
            break;
         case 8:
            printf("%s"RESET"\n", (cicloEnGrafo(grafo) ? VERDE"Si hay un ciclo en el grafo!" : ROJO"No se encontraron ciclos"));
            break;
         case 9:
            pdf = fopen("test.pdf", "w");
            gvLayout(gvc, g, "neato");
            gvLayoutJobs(gvc, g);
            gvRender(gvc, g, "pdf", pdf);
            gvFreeLayout(gvc, g);
            fclose(pdf);
            break;
         case 10:
         case 11:
         default:
            agclose(g);
            return(gvFreeContext(gvc));
            exit(0);
      }
   }
}
