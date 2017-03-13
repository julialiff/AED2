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
  for(i = 1;i <= V; i++){
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

//ordem do grafo
int ordem(VERTICE *g){
  int t = 0;
  int i;
  NO* p;
  for(i=1;i<=V;i++){
    p = g[i].inicio;
    while(p){
      t++;
      p = p->prox;
    }
  }
  return t;
}


int ordemMatriz(int m[V+1][V+1]){
  int i, j;
  int t = 0;
  for(i=1;i<=V;i++){
    for(j=1;j<=V;j++){
      if(m[i][j] == 1) t++;
    }
  }
  return t;
}

void exibirMatriz(int m[V+1][V+1]){
  int i, j;
  printf("   1 2 3 4 5\n");
  printf(" ___________\n");
  for(i=1;i<=V;i++){
    printf("%d: ", i);
    for(j=1;j<=V;j++){
      printf("%d ", m[i][j]);
    }
    printf("\n");
  }
}

void copiarGrafo(VERTICE *g, VERTICE *f){
  int i;
  NO* p = (NO*) malloc(sizeof(NO));
  for(i=1;i<=V;i++){
    p = g[i].inicio;
    while(p){
      NO* novo = (NO*) malloc(sizeof(NO));
      novo->v = p->v;
      novo->prox = f[i].inicio;
      f[i].inicio = novo;
      p = p->prox;
    }
  }
}

bool compararGrafos(VERTICE *g, int m[V+1][V+1]){
  int i;
  if(ordem(g) != ordemMatriz(m)) return false;
  for(i=1;i<=V;i++){
    NO* p = g[i].inicio;
    while(p){
      if(m[i][p->v] != 1) return false;
      p = p->prox;
    }
  }
  return true;
}

bool compararGrafos2(VERTICE *g, VERTICE *f){
  int i;
  bool achou = false;
  if(ordem(g) != ordem(f)) return false;
  for(i=1;i<=V;i++){
    NO* p = g[i].inicio;
    printf("i: %d **********\n", i);
    while(p){
      NO* q = f[i].inicio;
      while(q){
        printf("p: %d\n", p->v);
        printf("q: %d\n", q->v);
        if(p->v == q->v){
          achou = true;
          break;
        }
        q = q->prox;
      }
      printf("\n");
      if(achou = false) return false;
      else achou = false;
      p = p->prox;
    }
  }
  return true;
}

int main(){
  //grafo em matriz
  int m[V+1][V+1];

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

  exibirMatriz(m);
  printf(" \n\n\n\n");

  //grafo em lista de adjacências
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
  // VERTICE *novo = (VERTICE*) malloc(sizeof(VERTICE)*(V+1));
  // novo = inverterArestas(g);
  // exibir(novo);


  int t = ordem(g);
  int tm = ordemMatriz(m);
  printf("\n Tamanho: %d\n\n", t);
  printf("\n Tamanho matriz: %d\n\n", tm);

  printf("\n\n\n\n\n");
  zerarFlags(g);
  prof(g, 3);


  bool c = compararGrafos(g, m);
  printf("\n Comparar Grafos: %d\n", c);


  VERTICE *f = (VERTICE*) malloc(sizeof(VERTICE)*(V+1));
  inicializar(f);
  copiarGrafo(g, f);
  exibir(f);

  bool c2 = compararGrafos2(g, f);
  printf("\n Comparar Grafos2: %d\n", c2);
}
