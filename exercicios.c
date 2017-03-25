#include <stdlib.h>
#include <stdio.h>
#define V 5
// #define NULL 0
#define true 1
#define false 0


typedef int bool;

//aresta
typedef struct aux{
  int v;
  struct aux *prox;
  // bool expressa;
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
void inserirAresta(VERTICE *g, int i, int j){
  NO** ant = (NO**) malloc(sizeof(NO));
  if(arestaExiste(g, i, j, ant)) return;
  NO* novo = (NO*) malloc(sizeof(NO));
  novo->v = j;
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
      printf("%d -> ", p->v);
      p = p->prox;
    }
    printf("\n");
  }
}

//contar número de laços no grafoa
void ex1(){
  a = 1;
}

//remover laços

int main(){
  VERTICE *g = (VERTICE*) malloc(sizeof(VERTICE)*(V+1));
  inserirAresta(g, 1, 2);
  inserirAresta(g, 1, 5);
  inserirAresta(g, 1, 3);
  inserirAresta(g, 2, 4);
  inserirAresta(g, 3, 3);
  inserirAresta(g, 4, 1);
  inserirAresta(g, 5, 2);

  exibir(g);
}
