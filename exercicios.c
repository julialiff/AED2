#include <stdlib.h>
#include <stdio.h>
#define V 7
// #define NULL 0
#define true 1
#define false 0


typedef int bool;

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

//1. Escreva um algoritmo para contar a quantidade de laços em um grafo.
int ex1(VERTICE *g){
  int lacos = 0;
  int i;
  for(i=1;i<=V;i++){
    NO* p = g[i].inicio;
    while(p){
      if(p->v == i) lacos++;
      p = p->prox;
    }
  }
  return lacos;
}

//2. Variação: remover todos os laços encontrados.
void ex2(VERTICE *g){
  int i;
  for(i=1;i<=V;i++){
    NO* p = g[i].inicio;
    NO* ant = NULL;
    while(p){
      if(p->v == i){
        if(p == g[i].inicio) g[i].inicio = p->prox;
        else ant->prox = p->prox;
      }
      ant = p;
      p = p->prox;
    }
  }
}

//3. Escreva um algoritmo para destruir as arestas de um grafo, tornando-o vazio.
void ex3(VERTICE *g){
  int i;
  for(i=1;i<=V;i++){
    NO* p = g[i].inicio;
    g[i].inicio = NULL;
    while(p){
      NO* aux = p;
      p = p->prox;
      aux->prox = NULL;
      free(aux);
    }
  }
}

//4. Seja um grafo g dirigido. Escreva um algoritmo para retornar o grafo transposto de g.
VERTICE* ex4(VERTICE *g){
  int i;
  VERTICE *t = (VERTICE*) malloc(sizeof(VERTICE)*(V+1));
  inicializar(t);
  for(int i=1;i<=V;i++){
    NO* p = g[i].inicio;
    while(p){
      inserirAresta(t, p->v, i, p->peso);
      p = p->prox;
    }
  }
  return t;
}

//Escreva um algoritmo que dado um grafo m representado em matriz, retorne o mesmo grafo em listas de adjacências.
VERTICE* ex5(bool m[V+1][V+1]){
  VERTICE* novo = (VERTICE*) malloc(sizeof(VERTICE)*(V+1));
  int i, j;
  for(i=1;i<=V;i++){
    for(j=1;j<=V;j++){
      if(m[i][j]==1) inserirAresta(novo, i, j, 0);
    }
  }
  return novo;
}


//Uma árvore enraizada é um grafo acíclico, conexo e dirigido, com um único vértice fonte de onde todas as arestas partem. Escreva um algoritmo que, dado um grafo g, verifique se é uma árvore enraizada ou não, retornando true/false conforme o caso
bool ex6(VERTICE *g){
  //identificar a raiz
  return false;
}

//Seja um grafo g não-dirigido ponderado (com um peso inteiro associado a cada aresta). Escreva um algoritmo que, dado g e um custo mínimo int c, retorne uma cópia de g contendo apenas as arestas de custo maior do que c.
VERTICE* ex7(VERTICE* g, int c){
  VERTICE* aux = (VERTICE*) malloc(sizeof(VERTICE)*(V+1));
  for(int i = 1; i<=V; i++){
    NO* p = g[i].inicio;
    while(p){
      if(p->peso > c){
        inserirAresta(aux, i, p->v, p->peso);
      }
      p = p->prox;
    }
  }
}

int main(){
  VERTICE *g = (VERTICE*) malloc(sizeof(VERTICE)*(V+1));
  // inserirAresta(g, 1, 2);
  // inserirAresta(g, 1, 5);
  // inserirAresta(g, 1, 3);
  // inserirAresta(g, 2, 4);
  // inserirAresta(g, 3, 3);
  // inserirAresta(g, 4, 1);
  // inserirAresta(g, 5, 2);
  inserirAresta(g, 1, 2, 1);
  inserirAresta(g, 1, 3, 3);
  inserirAresta(g, 1, 4, 1);
  inserirAresta(g, 2, 5, 2);
  inserirAresta(g, 3, 5, 2);
  inserirAresta(g, 3, 7, 1);
  inserirAresta(g, 4, 3, 1);
  inserirAresta(g, 4, 6, 1);
  inserirAresta(g, 5, 7, 3);
  inserirAresta(g, 6, 7, 2);

  printf("******Grafo inicial*******\n");
  exibir(g);

  printf("\n\nExercício 1 - contar laços \n");
  int e1 = ex1(g);
  printf("%d \n", e1);

  printf("\n\nExercício 2 - destruir laços \n");
  ex2(g);
  exibir(g);

  printf("\n\nExercício 3 - destruir grafo \n");
  // ex3(g);
  // exibir(g);

  printf("\n\nExercício 4 - transposto \n");
  VERTICE* t = ex4(g);
  exibir(t);

  printf("\n\nExercício 5 - matriz para adjacências\n");
  //grafo em matriz
  bool m[V+1][V+1];

  //inicializar matriz
  int i, j;
  for(i=1; i<=V;i++){
    for(j=1;j<=V;j++){
      m[i][j] = 0;
    }
  }

  m[1][2] = 1;
  m[3][5] = 1;
  m[3][2] = 1;
  m[4][3] = 1;
  m[5][4] = 1;
  m[5][5] = 1;

  VERTICE* mg = ex5(m);
  exibir(mg);

  printf("\n\nExercício 6 - não vai dar não");

  printf("\n\nExercício 7 - Apenas arestas com custo maior que c. \n");
  VERTICE* a = ex7(g, 1);
  exibir(a);
}
