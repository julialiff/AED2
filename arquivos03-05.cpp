// Complexidade de E/S
// Índices residentes
FILE *arq = fopen ...
int n;
REGISTRO r;
scanf(" %s", &n);
fseek(arq, 0, SEEK_SET);
bool achou = false;
while(1==fread(&r, sizeof(REGISTRO), 1)){
  if(r.nrousp == n){
    achou = true;
    break;
  }
}
if(!achou) //ERRO

// Ordenação de arquivos
// Key Sort
// (1) Ler chaves e endereços (acesso sequencial)
// (2) Ordenar (em memória) (SEM CUSTO)
// (3) Reescrever arquivo na ordem certa (fseek para cada leitura e para cada escrita)
