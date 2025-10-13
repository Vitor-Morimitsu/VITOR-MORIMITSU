#include "disparador.h"
#include "pilha.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"


typedef struct disparador{
    int i;
    double x,y;
    void* centro;
    Pilha esquerda;
    Pilha direita; 
} Disparador;

Disparador criarDisparador(int i, double x, double y){
    Disparador* d = (Disparador*)malloc(sizeof(Disparador));
    if(d == NULL){
        printf("Erro ao alocar memória para o disparador");
        return;
    }

    d->i = i;
    d->x = x;
    d->y = y;
    d->esquerda = criarPilha();
    d->direita = criarPilha();

    if(d->esquerda == NULL || d->direita == NULL){
        printf("Erro ao alocar memória para os carregadores do disparador.");
        free(d); //libera o disparador que não teve os carregadores criados
        return;
    }

    return d;
}

int getIDDisparador(Disparador* d){
    return ((Disparador*)d)->i;
}

Celula getConteudoCarEsq(Disparador* d){
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
