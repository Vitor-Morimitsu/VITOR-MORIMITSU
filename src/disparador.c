#include "disparador.h"
#include "pilha.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"


typedef struct disparador{
    int i;
    void* centro;
    Pilha* esquerda;
    Pilha* direita; 
} Disparador;

Disparador* criarDisparador(int i, Pilha* esquerda, Pilha* direita){
    Disparador* d = (Disparador*)malloc(sizeof(Disparador));
    if(d == NULL){
        printf("Erro ao alocar memória para o disparador");
        return NULL;
    }

    d->i = i;
    d->esquerda = esquerda;
    d->direita = direita;


    return d;
}

int getIDDisparador(Disparador* d){
    return d->i;
}

Pilha* getConteudoCarEsq(Disparador* d){
    if(d == NULL){
        printf("Disparador inexistente");
        return NULL;
    }
    return d->esquerda;
}

Celula getConteudoCarDir(Disparador* d){
    if(d == NULL){
        printf("Disparador inexistente");
        return NULL;
    }
    return d->direita;
}

void setIDDisparador(Disparador* d, int i){
    if(d == NULL){
        printf("Disparador inexistente");
        exit(1);
    }
    d->i = i;
}
