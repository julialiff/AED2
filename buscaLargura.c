#include <stdlib.h>
#include <stdio.h>
#define V 5
// #define NULL 0
#define true 1
#define false 0


typedef int bool;


//*****GRAFO*****

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

void zerarFlags(VERTICE *g){
  int i;
  for(i = 1; i<=V; i++){
    g[i].flag = 0;
  }
}

//******FILA******
typedef struct{
  NO* inicio;
  NO* fim;
}FILA;

void inicializarFila(FILA *f){
  f->inicio = NULL;
  f->fim = NULL;
}

void entrarFila(FILA *f, int ch){
  NO* novo;
  novo = (NO*) malloc(sizeof(NO));
  novo->v = ch;
  novo->prox = NULL;
  if(f->fim) f->fim->prox = novo;
  else f->inicio = novo;
  f->fim = novo;
}

int sairFila(FILA *f){
  NO* aux;
  int ch;
  if(!f->inicio) return(-1);
  ch = f->inicio->v;
  aux = f->inicio;
  f->inicio = f->inicio->prox;
  free(aux);
  if(!f->inicio) f->fim = NULL;
  return(ch);
}

void largura(VERTICE *g, int i){
  zerarFlags(g);
  FILA f;
  inicializarFila(&f);
  g[i].flag = 1;
  entrarFila(&f, i);
  while(f.inicio){
    i = sairFila(&f);
    printf("%d \n", i);
    NO* p = g[i].inicio;
    while(p){
      if(g[p->v].flag == 0){
        entrarFila(&f, p->v);
        g[p->v].flag = 1;
      }
      p = p->prox;
    }
    g[i].flag = 2;
  }
}

int main(){
  VERTICE *g = (VERTICE*) malloc(sizeof(VERTICE)*(V+1));
  inicializar(g);
  inserirAresta(g, 1, 5);
  inserirAresta(g, 1, 3);
  inserirAresta(g, 1, 2);
  inserirAresta(g, 2, 4);
  inserirAresta(g, 3, 3);
  inserirAresta(g, 4, 1);
  inserirAresta(g, 5, 2);

  exibir(g);
  printf("\n\n");
  largura(g, 1);
}
