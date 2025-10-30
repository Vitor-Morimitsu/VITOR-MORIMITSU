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
    novo->forma = forma;
    novo->prox = NULL;
    fila->ultimo = novo;

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

Disparador procuraNaFilaDisparadores(Fila disparadores, int id){
    if(disparadores == NULL){
        printf("Erro ao procurar disparador na fila\n");
        exit(1);
    }

    stFila* fila = (stFila*)disparadores;
    pont atual = fila->primeiro;
    while(atual != NULL){
        Disparador d = (Disparador)atual->forma;
        int idDis = getIDDisparador(d);
        if(idDis == id){
            return d;
        }
        atual = atual->prox;
    }
    
    //Disparador não encontrado
    return NULL;
}

Carregador procuraNaFilaCarregadores(Fila carregadores, int id){
    if(carregadores == NULL || id == 0){
        printf("Erro ao procurar carregador na fila\n");
        exit(1);
    }

    stFila* fila = (stFila*)carregadores;
    pont atual = fila->primeiro;
    while(atual != NULL){
        Carregador car = (Carregador)atual->forma;
        int idCar = getIDCarregador(car);
        if(idCar == id){
            return car;
        }
        atual = atual->prox;
    }

    //Não encontrou o carregador
    return NULL;
}
