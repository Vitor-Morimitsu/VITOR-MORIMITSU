#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

typedef void* Conteudo;

typedef struct stcelula{
    Conteudo conteudo;
    struct stcelula *prox;
}stCelula;

typedef struct stpilha{
    stCelula *topo;
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

void inserirPilha(Pilha p, Conteudo n){
    if(p == NULL){
        printf("Erro ao acessar a pilha.");
        exit(1);
    }
    stPilha* pilha = (stPilha*)p;

    stCelula* novaCelula = (stCelula*)malloc(sizeof(stCelula));
    if(novaCelula == NULL){
        printf("Erro ao criar a nova célula para inserir na pilha.");
        exit(1);
    }

    novaCelula->conteudo = n;
    novaCelula->prox = pilha->topo;
    pilha->topo = novaCelula;
    pilha->tamanho++;
}

void removerPilha(Pilha p){
    stPilha* pilha = (stPilha*)p;
    if(pilha == NULL||pilha->topo == NULL){
        return;
    }

    stCelula* temp = pilha->topo;
    pilha->topo = pilha->topo->prox;
    free(temp);
    pilha->tamanho--;
}

Conteudo getConteudoPilha(Pilha p){
    if(p == NULL){
        printf("Erro ao acessar o conteúdo da pilha");
        return NULL;
    }
    stPilha* pilha = (stPilha*)p;
    if(pilha != NULL && pilha->topo != NULL){
        return pilha->topo->conteudo;
    }else{
        return NULL;
    }
}

int getTamanhoPilha(Pilha p){
    if(p == NULL){
        printf("Erro ao acessar o tamanho da pilha.");
        return NULL;
    }

    stPilha* pilha = (stPilha*)p;
    return pilha->tamanho;
}

void liberarMemoriaPilha(Pilha p){
    if (p == NULL) {
        printf("Erro ao acessar a pilha para liberar a memória.");
        return NULL;
    }

    stPilha* pilha = (stPilha*)p;
    while(pilha->topo != NULL){
        removerPilha(pilha);
    }

    free(pilha);
}