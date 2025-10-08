#include "fila.h"
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

Fila* criarFila(){
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

void insereFila(Fila* f, Forma* form){
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
    }
    if(f->ultimo->prox == NULL){ // fila já contém elementos
        f->ultimo->prox = novaForma;
        f->ultimo = novaForma;
    }
    f->tamanho++;
}