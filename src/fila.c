#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include "disparador.h"
#include "formas.h"
typedef struct stNo {
    Forma forma;
    struct stNo* prox;
}stNoFila;

typedef stNoFila* pont;
typedef void* Fila;
typedef struct{
    pont primeiro;
    pont ultimo;
    int tamanho;
} stFila;

Fila criarFila() {
    stFila* f = (stFila*)malloc(sizeof(stFila));
    if (f == NULL) {
        perror("Erro ao alocar memória para a fila\n");
        return NULL; 
    }

    f->primeiro = NULL;
    f->ultimo = NULL;
    f->tamanho = 0;
    return f;
}

void insereFila(Fila f,Forma forma) {
    stFila* fila = (stFila*)f;
    pont novo = malloc(sizeof(stNoFila));
    if(novo == NULL){
        printf("Falha ao alocar memória para novo nó da fila\n");
        exit(1);
    }

    if(fila->primeiro == NULL){
        fila->primeiro = novo;
        fila->ultimo = novo;
    }else{
        fila->ultimo->prox = novo;
        fila->ultimo = novo;
    }

    fila->tamanho++;    
}

void removeFila(Fila f) {
    stFila* fila = (stFila*)f;
    if (fila == NULL || fila->primeiro == NULL) {//fila vazia ou inexistente
        return NULL; 
    }

    pont temp = fila->primeiro;
    fila->primeiro = fila->primeiro->prox;
    fila->tamanho--;
    free(temp);
}

Forma getPrimeiroConteudoFila(Fila f) {
    stFila* fila = (stFila*)f;
    if (fila == NULL || fila->primeiro == NULL) {
        return NULL;
    }
    return fila->primeiro->forma;
}

void liberarFilaComConteudo(Fila f) {
    if (f == NULL) {
        return;
    }    
}

int getTamanhoFila(Fila f){
    stFila* fila = (stFila*)f;
    return fila->tamanho;
}

Disparador encontrarDisparadorPorId(Fila disparadores, int id){
    if(disparadores == NULL){
        printf("Disparador não encontrado");
        exit(1);
    }

    stFila* fila = (stFila*)disparadores;
    pont atual = fila->primeiro;

    while(atual != NULL){
        Disparador d = (Disparador)atual->forma;
        if(getIDDisparador(d) == id){
            return d;
        }
        atual = atual->prox;
    }

    //não encontrou o disparador com a id passada
    return NULL;
}

Carregador encontrarCarregadorPorId(Fila carregadores, int id){
    if(carregadores == NULL){
        printf("Carregador não encontrado\n");
        exit(1);
    }
    stFila* fila = (stFila*)carregadores;
    pont atual = fila->primeiro;
    while(atual != NULL){
        Carregador car = (Carregador*)atual->forma;
        if(getIDCarregador(car) == id){
            return car;
        }
        atual = atual->prox;
    }

    //não encotrou o carregador com a id passada
    return NULL;
}
