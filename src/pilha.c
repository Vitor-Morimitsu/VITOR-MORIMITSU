#include "pilha.h"
typedef struct stcelula{
    Pacote pacote;
    struct stcelula *prox;
}stNoPilha;

typedef stNoPilha* pont;
typedef struct {
    pont topo;
    int tamanho;
}stPilha;

Pilha criarPilha(){
    stPilha* p = (stPilha*)malloc(sizeof(stPilha));
    if(p == NULL){
        printf("Erro ao alocar memória para a Pilha");
        exit(1);
    }
    p->tamanho = 0;
    p->topo = NULL;
    return p;
}

void inserirPilha(Pilha p,Pacote pac){
    if(p == NULL){
        printf("Erro ao acessar a pilha para adicionar uma nova celula\n.");
        exit(1);
    }
    stPilha* pilha = (stPilha*)p;

    pont novaCelula = malloc(sizeof(stNoPilha));
    if(novaCelula == NULL){
        printf("Erro ao criar a nova celula criada\n");
        exit(1);
    }
    novaCelula->pacote = pac;
    novaCelula->prox = pilha->topo;
    pilha->topo = novaCelula;
    pilha->tamanho++;
}

void removerPilha(Pilha p){
    stPilha* pilha = (stPilha*)p;
    if(pilha == NULL||pilha->topo == NULL){
        return;
    }

    stNoPilha* temp = pilha->topo;
    pilha->topo = pilha->topo->prox;
    free(temp);
    pilha->tamanho--;
}

Pacote getPacoteTopoPilha(Pilha p){
    stPilha* pilha =(stPilha*)p;
    if(p == NULL || pilha->topo == NULL){
        printf("Erro ao acessar o conteúdo da pilha");
        return NULL;
    }
    
    return pilha->topo->pacote;
}

int getTamanhoPilha(Pilha p){
    if(p == NULL){
        printf("Erro ao acessar o tamanho da pilha.");
        return 0;
    }
    return ((stPilha*)p)->tamanho;
}

void destruirPilha(Pilha p){
    stPilha* pilha = (stPilha*)p;
    if(pilha == NULL){
        printf("Pilha vazia. Impossível destruir.\n");
        exit(1);
    }

    pont atual = pilha->topo;
    pont apagar;
    while(atual != NULL){
        apagar = atual;
        atual = atual->prox;
        freePacote(apagar->pacote);
        free(apagar);
    }
    free(pilha);
}