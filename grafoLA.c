#include <stdlib.h>
#include <stdio.h>
#define V 5
// #define NULL 0
#define true 1
#define false 0


typedef int bool;

typedef struct aux{
  int v;
  struct aux *prox;
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

void inserirAresta(VERTICE *g, int i, int j){
  NO** ant = (NO**) malloc(sizeof(NO));
  if(arestaExiste(g, i, j, ant)) return;
  NO* novo = (NO*) malloc(sizeof(NO));
  novo->v = j;
  novo->prox = g[i].inicio;
  g[i].inicio = novo;
}

void exibir(VERTICE *g){
  int i;
  NO *p;
  for(i=1;i<=V;i++){
    printf("(%d) -> ", i);
    p = g[i].inicio;
    while(p){
      printf("%d -> ", p->v);
      p = p->prox;
    }
    printf("\n");
  }
}

void excluir(VERTICE *g, int i, int j){
  NO *ant = (NO*) malloc(sizeof(NO));
  NO* p = (NO*) malloc(sizeof(NO));
  if(!arestaExiste(g, i, j, &ant)) return;
  if(ant == NULL){
    g[i].inicio = g[i].inicio->prox;
  }
  else{
    ant->prox = ant->prox->prox;
  }
}

void inserirNaoDirigido(VERTICE *g, int i, int j){
  NO** ant = (NO**) malloc(sizeof(NO));
  bool q = arestaExiste(g, i, j, ant);
  NO* novo = (NO*) malloc(sizeof(NO));
  NO* novo2 = (NO*) malloc(sizeof(NO));
  novo->v = j;
  novo->prox = g[i].inicio;
  g[i].inicio = novo;

  novo2->v = i;
  novo2->prox = g[j].inicio;
  g[j].inicio = novo2;
}

int grauSaida(VERTICE *g, int i){
  NO *p = g[i].inicio;
  int grau = 0;
  while(p){
    grau++;
    p = p->prox;
  }
  return grau;
}


//grau de entrada
int grauEntrada(VERTICE *g, int j){
  int i;
  int grau = 0;
  NO* p = (NO*) malloc(sizeof(NO));
  for(i = 1; i <= V; i++){
    p = g[i].inicio;
    while(p){
      if(p->v == j) grau++;
      p = p->prox;
    }
  }
  return grau;
}


//inverter arestas
VERTICE* inverterArestas(VERTICE *g){
  int i;
  VERTICE *novo = (VERTICE*) malloc(sizeof(VERTICE)*(V+1));
  inicializar(novo);
  NO* p = (NO*) malloc(sizeof(NO));
  for(i = 0;i <= V; i++){
    p = g[i].inicio;
    while(p){
      inserirAresta(novo, p->v, i);
      p = p->prox;
    }
  }
  return novo;
}

//zerar flags
void zerarFlags(VERTICE *g){
  int i;
  for(i = 1; i<=V; i++){
    g[i].flag = 0;
  }
}


//busca em profundidade
void prof(VERTICE *g, int i){
  g[i].flag = 1;
  NO *p = g[i].inicio;
  while(p){
    if(g[p->v].flag == 0){
      prof(g, p->v);
      printf("%d \n", p->v);
    }
    p = p->prox;
  }
  g[i].flag = 2;
}

int main(){
  // NO *ant;
  VERTICE *g = (VERTICE*) malloc(sizeof(VERTICE)*(V+1));
  inicializar(g);
  inserirAresta(g, 1, 2);
  inserirAresta(g, 3, 5);
  inserirAresta(g, 3, 2);
  inserirAresta(g, 4, 3);
  inserirAresta(g, 5, 4);
  inserirAresta(g, 5, 5);
  exibir(g);
  // excluir(g, 3, 2);
  // excluir(g, 3, 5);
  // printf("\n\n\n\n\n");

  // inserirNaoDirigido(g, 1, 3);
  // inserirNaoDirigido(g, 2, 1);
  // inserirNaoDirigido(g, 2, 4);
  // inserirNaoDirigido(g, 3, 5);
  // inserirNaoDirigido(g, 3, 4);
  // inserirNaoDirigido(g, 2, 5);
  // inserirNaoDirigido(g, 2, 3);
  // exibir(g);

  int gs = grauSaida(g, 5);
  printf("\nGrau de saída: %d \n ", gs);
  int ge = grauEntrada(g, 2);
  printf("\nGrau de entrada: %d \n ", ge);
  VERTICE *novo = (VERTICE*) malloc(sizeof(VERTICE)*(V+1));
  novo = inverterArestas(g);
  exibir(novo);

  printf("\n\n\n\n\n");
  zerarFlags(g);
  prof(g, 3);
}

