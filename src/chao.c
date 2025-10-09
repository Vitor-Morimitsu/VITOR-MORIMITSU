#include "chao.h"
#include "stdio.h"
#include "stdlib.h"
#include "disparador.h"
#include "formas.h"
#include "fila.h"

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

    f = criarFila;

    return ((Fila*)f);
}

void insereChao(Fila* f, Forma* form,char type){
    Aux* novaForma = (Aux*)malloc(sizeof(Aux));
    if(novaForma == NULL){
        printf("Erro ao alocar memória para a nova forma");
        exit(1);
    }
    if(f == NULL){
        printf("Fila inexistente");
        exit(1);
    }
    
    insereFila(f, form, type);
    f->tamanho++;
}

void removeChao(Fila* f) {
    if (f == NULL || f->primeiro == NULL) {
        printf("Não existe nenhuma forma no chão para remover.");
        return;
    }

    removeFila(f);
    f->tamanho--;
}

Forma getPrimeiroElementoChao(Fila* f){
    if(f == NULL){
        printf("Chão inexistente.");
        return NULL;
    }
    
    getPrimeiraFormaFila(f);
}

void liberarChao(Fila* f) {
    if (f == NULL) {
        return;
    }

    liberarFila(f);
}