#include "grafo.h"
#include "draw.h"
#include "menu.h"

#define PDF_FILE "grafo.pdf"
#define CAMINO_COLOR "skyblue"
#define SHAPE "circle"

static GVC_t *gvc;
static Agraph_t *g;
static Grafo *grafo;
static Agnode_t **nodos;
static Agedge_t **aristas;
static int cantAristas;

void menuColorearValidarCamino(FILE *pdf){
   printf("Ingrese una lista con cada nodo\npor el cual desea traversar. (Cada Nodo separado por una coma ','): ");
   char str[256];
   scanf("%s", str);
   char *tok = strtok(str, ",");
   int *trayecto = malloc(0), tamano = 0;
   while(tok){
      int *tmp = malloc(sizeof(int) * tamano + 1);
      memcpy(tmp, trayecto, sizeof(int) * tamano);
      tmp[tamano++] = atoi(tok);
      free(trayecto);
      trayecto = tmp;
      tok = strtok(NULL, ",");
   }
   if(!validarCamino(grafo, trayecto, tamano))
      resetColors();
   else
      colorearCaminoValido(trayecto, tamano);
   pdf = fopen(PDF_FILE, "w");
   gvLayout(gvc, g, "neato");
   gvLayoutJobs(gvc, g);
   gvRender(gvc, g, "pdf", pdf);
   gvFreeLayout(gvc, g);
   fclose(pdf);
}

void menuColorearBuscarCamino(FILE *pdf){
   char buf[8];
   int src, dst;
   printf("Ingrese Nodo de inicio: ");
   scanf("%s", buf);
   src = atoi(buf);
   printf("Ingrese Nodo de destino: ");
   scanf("%s", buf);
   dst = atoi(buf);
   colorearCamino(src, dst);
   pdf = fopen(PDF_FILE, "w");
   gvLayout(gvc, g, "neato");
   gvLayoutJobs(gvc, g);
   gvRender(gvc, g, "pdf", pdf);
   gvFreeLayout(gvc, g);
   fclose(pdf);
}

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
   if(!addArista(*graf, src, dst))
      return;
   Agedge_t **tmp = malloc(sizeof(Agedge_t*) * cantAristas + 1);
   memcpy(tmp, aristas, sizeof(Agedge_t*) * cantAristas);
   free(aristas);
   aristas = tmp;
   printf("cant: %i\n", cantAristas);
   aristas[cantAristas++] = agedge(g, nodos[src], nodos[dst], 0, 1);
}

void resetColors(){
   for(int i = 0; i < grafo->cantidadNodos; i++){
      agsafeset(nodos[i], "color", "black", "");
      agsafeset(nodos[i], "style", "solid", "");
   }
   for(int i = 0; i < grafo->cantidadAristas; i++){
      agsafeset(aristas[i], "color", "black", "");
      agsafeset(aristas[i], "label", "", "");
   }
}

void colorearCamino(int src, int dst){
   int *trayecto, *tr_aristas;
   int nodosTraversados;
   if(!(nodosTraversados = caminoValido(grafo, &trayecto, &tr_aristas, src, dst)))
         return;
   for(int i = 0; i < nodosTraversados; i++){
      agsafeset(nodos[trayecto[i]], "color", CAMINO_COLOR, "");
      agsafeset(nodos[trayecto[i]], "style", "filled", "");
   }
   for(int i = 0; i < nodosTraversados - 1; i++){
      agsafeset(aristas[tr_aristas[i]], "color", CAMINO_COLOR, "");
   }
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
   FILE *pdf;
   while(1){
      printf(BANNER "\n");
      if(!grafo)
         printf("\
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
            9.Salvar grafo en un pdf\n\
            10.Buscar un Camino y salvarlo en el pdf\n\
            11.Validar Camnio y salvarlo en el pdf\n");
      printf("\
            12.Salir\n\n");
      char buf[10];
      printf("Seleccione una Opcion: ");
      scanf("%s", buf);
      if(atoi(buf) == 0)
         continue;
      if(!grafo && atoi(buf) > 1 && atoi(buf) < 11)
         continue;
      switch(atoi(buf)){
         case 1:
            if(!grafo)
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
            resetColors();
            pdf = fopen(PDF_FILE, "w");
            gvLayout(gvc, g, "neato");
            gvLayoutJobs(gvc, g);
            gvRender(gvc, g, "pdf", pdf);
            gvFreeLayout(gvc, g);
            fclose(pdf);
            break;
         case 10:
            menuColorearBuscarCamino(pdf);
            break;
         case 11:
            menuColorearValidarCamino(pdf);
            break;
         case 12:
            agclose(g);
            return(gvFreeContext(gvc));
            exit(0);
      }
   }
}
