#include "chao.h"
#include "stdio.h"
#include "stdlib.h"
#include "disparador.h"

typedef void* Forma;

typedef struct auxiliar{
    Forma* form;
    char type;
    struct auxiliar* prox;
}Aux;

typedef struct fila{
    Aux* primeiro;
    Aux* ultimo;
    int tamanho;
}Fila;

Fila* criarChao(){
    Fila* f = (Fila*)malloc(sizeof(Fila));
    if(f == NULL){
        printf("Erro ao alocar memória para a fila");
        return NULL;
    }

    f->primeiro = NULL;
    f->tamanho = 0;
    f->ultimo = NULL;

    return ((Fila*)f);
}

void insereChao(Fila* f, Forma* form){
    Aux* novaForma = (Aux*)malloc(sizeof(Aux));
    if(novaForma == NULL){
        printf("Erro ao alocar memória para a nova forma");
        exit(1);
    }
    if(f == NULL){
        printf("Fila inexistente");
        exit(1);
    }
    
    novaForma->form = form;
    novaForma->prox = NULL;

    //caso a fila esteja vazia
    if(f->primeiro == NULL){
        f->primeiro = novaForma;
        f->ultimo = novaForma;
    }else{ // fila já contém elementos
        f->ultimo->prox = novaForma;
        f->ultimo = novaForma;
    }
    f->tamanho++;
}

void removeChao(Fila* f) {
    if (f == NULL || f->primeiro == NULL) {
        printf("Não existe nenhuma forma no chão para remover.");
        return;
    }

    Aux* temp = f->primeiro; 

    f->primeiro = f->primeiro->prox;

    if (f->primeiro == NULL) {
        f->ultimo = NULL;
    }

    free(temp);
    f->tamanho--;
}

Forma getPrimeiroElementoChao(Fila* f){
    if(f == NULL){
        printf("Chão inexistente.");
        return NULL;
    }
    return f->primeiro->form;
}

void liberarChao(Fila* f) {
    if (f == NULL) {
        return;
    }

    Aux* atual = f->primeiro;
    Aux* proximo;

    while (atual != NULL) {
        proximo = atual->prox; 
        free(atual);           
        atual = proximo;       
    }

    free(f);
}