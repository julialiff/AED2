#include <stdlib.h>
#include <stdio.h>
#define V 9
#define true 1
#define false 0

//aresta
typedef struct aux{
  int v;
  struct aux *prox;
  // bool expressa;
  int peso;
}NO;

typedef struct s{
  int flag;
  NO* inicio;
}VERTICE;

void inicializar(VERTICE *g){
  for(int i=1;i<=V;i++){
    g[i].inicio = NULL;
  }
}

bool arestaExiste(VERTICE *g, int i, int j, NO **ant){
  *ant = NULL;
  NO* p = g[i].inicio;
  while(p){
    if(p->v == j) return true;
    *ant = p;
    p = p->prox;
  }
  return false;
}

// void inserirAresta(VERTICE *g, int i, int j, bool express){
void inserirAresta(VERTICE *g, int i, int j, int peso){
  NO** ant = (NO**) malloc(sizeof(NO));
  if(arestaExiste(g, i, j, ant)) return;
  NO* novo = (NO*) malloc(sizeof(NO));
  novo->v = j;
  novo->peso = peso;
  novo->prox = g[i].inicio;
  // novo->expressa = express;
  g[i].inicio = novo;
}

void exibir(VERTICE *g){
  int i;
  NO *p;
  for(i=1;i<=V;i++){
    printf("(%d) -> ", i);
    p = g[i].inicio;
    while(p){
      printf("%d (%d) -> ", p->v, p->peso);
      p = p->prox;
    }
    printf("\n");
  }
}

int contaLacos(VERTICE* g){
  int lacos = 0;
  for(int i=1; i<=V; i++){
    NO* p = g[i].inicio;
    while(p){
      if(p->v == i) lacos++;
      p = p->prox;
    }
  }
  return lacos;
}

void removeLacos(VERTICE* g){
  for(int i=1; i<=V; i++){
    NO* p = g[i].inicio;
    NO* ant = NULL;
    while(p){
      if(p->v == i){
        if(ant == NULL) g[i].inicio = p->prox;
        else ant->prox = p->prox;
      }
      ant = p;
      p = p->prox;
    }
  }
}

void destruirGrafo(VERTICE *g){
  for(int i=1; i<=V; i++){
    NO* p = g[i].inicio;
    while(p){
      NO* aux = p;
      free(p);
      p = aux->prox;
    }
    g[i].inicio = NULL;
  }
}

VERTICE* transposto(VERTICE *g){
  VERTICE* t = (VERTICE*) malloc(sizeof(VERTICE)*(V+1));
  for(int i=1; i<=V; i++){
    NO* p = g[i].inicio;
    while(p){
      printf("p->v: %d, i: %d, p->peso: %d \n", p->v, i, p->peso);
      inserirAresta(t, p->v, i, p->peso);
      p = p->prox;
    }
  }
  return t;
}

VERTICE* matrizParaAdjacencia(bool m[V+1][V+1]){
  VERTICE* r = (VERTICE*) malloc(sizeof(VERTICE)*(V+1));
  for(int i=1; i<=V; i++){
    for(int j=1; j<=V; j++){
      if(m[i][j]) inserirAresta(r, i, j, 1);
    }
  }
  return r;
}

int main(){
  VERTICE *g = (VERTICE*) malloc(sizeof(VERTICE)*(V+1));
  inicializar(g);
  inserirAresta(g, 1, 2, 30);
  inserirAresta(g, 2, 6, 20);
  inserirAresta(g, 2, 7, 30);
  inserirAresta(g, 3, 1, 20);
  inserirAresta(g, 3, 4, 20);
  inserirAresta(g, 5, 8, 10);
  inserirAresta(g, 6, 7, 10);
  inserirAresta(g, 9, 4, 80);
  inserirAresta(g, 9, 7, 80);

  // exibir(g);
  // printf("\n\n");
  // int lacos = contaLacos(g);
  // printf("%d \n", lacos);
  // removeLacos(g);
  // printf("\n\n");
  // exibir(g);

  // VERTICE* t = transposto(g);
  // printf("\n\n");
  // exibir(t);

  bool m[V+1][V+1];
  for(int i=1; i<=V; i++){
    for(int j=1; j<=V; j++){
      m[i][j] = 0;
    }
  }
  m[1][2] = 1;
  m[2][6] = 1;
  m[2][7] = 1;
  m[3][1] = 1;
  m[3][4] = 1;
  m[5][8] = 1;
  m[6][7] = 1;
  m[9][4] = 1;
  m[9][7] = 1;

  VERTICE* r = matrizParaAdjacencia(m);
  exibir(r);
  return 0;
}
