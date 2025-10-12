#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include "disparador.h"
typedef struct no {
    Forma form;
    char type;
    struct no* prox;
} No;
typedef struct fila_interna {
    No* primeiro;
    No* ultimo;
    int tamanho;
} Fila_interna;

Fila criarFila() {
    Fila_interna* f = (Fila_interna*)malloc(sizeof(Fila_interna));
    if (f == NULL) {
        perror("Erro ao alocar memória para a fila");
        return NULL; 
    }

    f->primeiro = NULL;
    f->ultimo = NULL;
    f->tamanho = 0;
    return f;
}

void insereFila(Fila f, Forma form, char type) {
    Fila_interna* fila = (Fila_interna*)f;

    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        perror("Erro ao alocar memória para o novo nó");
        exit(1);
    }
    
    novoNo->form = form;
    novoNo->type = type;
    novoNo->prox = NULL;

    if (fila->primeiro == NULL) {
        fila->primeiro = novoNo;
        fila->ultimo = novoNo;
    } else {
        fila->ultimo->prox = novoNo;
        fila->ultimo = novoNo;
    }
    fila->tamanho++;
}

void removeFila(Fila f) {
    Fila_interna* fila = (Fila_interna*)f;
    
    if (fila == NULL || fila->primeiro == NULL) {
        return; 
    }
    
    No* temp = fila->primeiro;
    fila->primeiro = fila->primeiro->prox;
    free(temp);
    fila->tamanho--;

    if (fila->primeiro == NULL) {
        fila->ultimo = NULL;
    }
}


Forma getPrimeiraFormaFila(Fila f) {
    Fila_interna* fila = (Fila_interna*)f;

    if (fila == NULL || fila->primeiro == NULL) {
        return NULL;
    }
    
    return fila->primeiro->form;
}

void liberarFila(Fila* f) {
    Fila_interna* fila = (Fila_interna*)f;

    if (fila == NULL) {
        return;
    }

    No* atual = fila->primeiro;
    while (atual != NULL) {
        No* temp = atual;
        atual = atual->prox;
        free(temp);
    }
 
    free(fila);
}