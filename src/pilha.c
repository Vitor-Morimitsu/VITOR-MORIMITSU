#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

typedef void* Conteudo;

typedef struct celula{
    Conteudo conteudo;
    struct celula *prox;
}Celula;

typedef struct pilha{
    Celula *topo;
    int tamanho;
}Pilha;

Pilha* criarPilha(){
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    if(p == NULL){
        printf("Erro ao alocar memória para a Pilha");
        exit(1);
    }
    p->tamanho = 0;
    p->topo = NULL;
    return p;
}

void inserirPilha(Pilha* p, Conteudo n){
    Celula* novaCelula = (Celula*)malloc(sizeof(Celula));
    if(novaCelula == NULL){
        printf("Erro ao alocar memória para a nova célula");
        exit(1);
    }
    novaCelula->conteudo = n;
    novaCelula->prox = p->topo;
    p->topo = novaCelula;
    
    p->tamanho++;
}

void removerPilha(Pilha* p){
    if(p == NULL || p->topo == NULL){
        printf("Pilha vazia");
        return;
    }

    Celula* temp = p->topo;
    p->topo = p->topo->prox;
    p->tamanho--;
    free(temp);
}

Conteudo getConteudoPilha(Pilha* p){
    if(p->topo != NULL){
        return p->topo->conteudo;
    }else{
        printf("Pilha está vazia");
        return NULL;
    }
}

Celula* getCelulaPilha(Pilha* p){
    if(p->topo != NULL){
        return p->topo;
    }else{
        printf("Pilha está vazia");
        return -1;
    }
}

int getTamanhoPilha(Pilha* p){
    if(p->topo != NULL){
        return p->tamanho;
    }else{
        printf("Pilha esetá vazia");
        return -1;
    }
}

void liberarMemoriaPilha(Pilha* p){
    if (p == NULL) {
        return;
    }
    while (p->topo != NULL) { 
        removerPilha(p);
    }
    free(p);
}