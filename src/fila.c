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

    return f;
}

void insereFila(Fila* f, Forma* form, char type){
    Aux* novaForma = (Aux*)malloc(sizeof(Aux));
    if(novaForma == NULL){
        printf("Erro ao alocar memória para a nova forma");
        exit(1);
    }
    
    novaForma->form = form;
    novaForma->type = type;
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

void removeFila(Fila* f){
    if(f == NULL){
        printf("Erro ao acessar a primeira forma da fila.");
        exit(1);
    }

    if(f->primeiro == NULL){
        printf("Fila vazia.");
    }else{
        Aux* temp = f->primeiro;
        f->primeiro = f->primeiro->prox;
        free(temp);
        f->tamanho--;
    }
}

Forma getPrimeiraFormaFila(Fila* f){
    if(f == NULL){
        printf("Erro ao acessar a primeira forma da fila.");
        exit(1);
    }else{
        return f->primeiro->form;
    }

}

void liberarFila(Fila* f){
    if(f == NULL){
        printf("Erro ao acessar a fila para liberação.");
        exit(1);
    }

    Aux* temp;

    for(int i = 0;i<f->tamanho;i++){
        temp = f->primeiro;
        f->primeiro = f->primeiro->prox;
        free(temp);
    }
    free(f);
}