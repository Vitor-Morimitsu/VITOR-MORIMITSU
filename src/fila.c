#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include "disparador.h"
#include "formas.h"
typedef struct stNo {
    void* conteudo;
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

void insereFila(Fila f,void* conteudo) {
    stFila* fila = (stFila*)f;
    pont novo = malloc(sizeof(stNoFila));
    if(novo == NULL){
        printf("Falha ao alocar memória para novo nó da fila\n");
        exit(1);
    }
    novo->conteudo = conteudo;
    novo->prox = NULL;
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
        return; 
    }

    pont temp = fila->primeiro;
    fila->primeiro = fila->primeiro->prox;
    fila->tamanho--;
    free(temp);
}

void liberarFila(Fila f) {
    if (f == NULL) {
        return;
    }    
    stFila* fila = (stFila*)f;
    pont atual = fila->primeiro;
    while(atual != NULL){
        pont proximo = atual->prox;
        Pacote pac = (Pacote)atual->conteudo;
        if(pac != NULL){
            freePacote(pac);
        }
        free(atual);
        atual = proximo;
    }
}

void* getPrimeiroConteudoFila(Fila f){
    stFila* fila = (stFila*)f;
    if(f == NULL || fila->primeiro == NULL){
        printf("Não há nada na fila\n");
        return NULL;
    }
    return fila->primeiro->conteudo;
}

int getTamanhoFila(Fila f){
    if(f == NULL){
        return 0;
    }
    stFila* fila = (stFila*)f;
    return fila->tamanho;
}

Disparador encontrarDisparadorPorId(Fila disparadores, int id){
    if(disparadores == NULL){
        printf("Disparador não encontrado");
        return NULL;
    }

    stFila* fila = (stFila*)disparadores;
    pont atual = fila->primeiro;

    while(atual != NULL){
        Disparador d = (Disparador)atual->conteudo;
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
        return NULL;
    }
    stFila* fila = (stFila*)carregadores;
    pont atual = fila->primeiro;
    while(atual != NULL){
        Carregador car = (Carregador)atual->conteudo;
        if(getIDCarregador(car) == id){
            return car;
        }
        atual = atual->prox;
    }

    //não encotrou o carregador com a id passada
    return NULL;
}

Fila clonarFilaChao(Fila original){
    stFila* f = (stFila*)original;
    if(f == NULL){
        printf("Erro ao clonar a fila\n");
        return NULL;
    }
    
    Fila nova = criarFila();
    pont atual = f->primeiro;

    while(atual != NULL){
        Pacote pac = (Pacote)atual->conteudo;
        insereFila(nova, pac);
        atual = atual->prox;
    }
    return nova;
}

Fila clonarFilaDisparadores(Fila original){
    if(original == NULL){
        printf("Fila de disparadores vazia. Erro ao clonar\n");
        return NULL;
    }

    stFila* fila = (stFila*)original;
    pont atual = fila->primeiro;
    Fila nova = criarFila();
    while(atual != NULL){
        Disparador d = (Disparador)atual->conteudo;
        insereFila(nova, d);
        atual = atual->prox;
    }
    return nova;
}

Fila clonarFilaCarregadores(Fila original){
    if(original == NULL){
        printf("Fila de carregadores vazia.Erro ao clonar\n");
        return NULL;
    }
    stFila* fila = (stFila*)original;
    pont atual = fila->primeiro;
    Fila nova = criarFila();
    while(atual != NULL){
        Carregador car = (Carregador)atual->conteudo;
        insereFila(nova, car);
        atual = atual->prox;
    }
    return nova;
}

void liberarClone(Fila clone){
    if(clone == NULL){
        printf("Erro ao acessar a fila clone\n");
        return;
    }
    stFila* fila = (stFila*)clone;
    pont atual = fila->primeiro;

    while(atual != NULL){
        pont proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    free(fila);
}