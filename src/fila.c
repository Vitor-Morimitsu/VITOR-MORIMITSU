#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include "disparador.h"
typedef struct stNo {
    Forma form;
    char type;
    struct stNo* prox;
} stNo;
typedef struct stFila {
    stNo* primeiro;
    stNo* ultimo;
    int tamanho;
} stFila;

Fila criarFila() {
    stFila* f = (stFila*)malloc(sizeof(stFila));
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
    stFila* fila = (stFila*)f;

    stNo* novoNo = (stNo*)malloc(sizeof(stNo));
    if (novoNo == NULL) {
        printf("Erro ao alocar memória para o novo nó");
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
    stFila* fila = (stFila*)f;
    
    if (fila == NULL || fila->primeiro == NULL) {
        return; 
    }
    
    stNo* temp = fila->primeiro;
    fila->primeiro = fila->primeiro->prox;
    free(temp);
    fila->tamanho--;

    if (fila->primeiro == NULL) {
        fila->ultimo = NULL;
    }
}


Forma getPrimeiraFormaFila(Fila f) {
    stFila* fila = (stFila*)f;

    if (fila == NULL || fila->primeiro == NULL) {
        return NULL;
    }
    
    return fila->primeiro->form;
}

void liberarFila(Fila f) {
    stFila* fila = (stFila*)f;

    if (fila == NULL) {
        return;
    }

    stNo* atual = fila->primeiro;
    while (atual != NULL) {
        stNo* temp = atual;
        atual = atual->prox;
        free(temp);
    }
 
    free(fila);
}
No_t getPrimeiroNo(Fila f) {
    stFila* fila = (stFila*)f;
    return fila->primeiro;
}

No_t getProximoNo(No_t no) {
    if (no == NULL) return NULL;
    stNo* no_interno = (stNo*)no; 
    return no_interno->prox;
}

Forma getConteudoDoNo(No_t no) {
    if (no == NULL) return NULL;
    stNo* no_interno = (stNo*)no;
    return no_interno->form;
}

char getTipoDoNo(No_t no) {
    if (no == NULL) return '\0';
    stNo* no_interno = (stNo*)no;
    return no_interno->type;
}

int getTamanhoFila(Fila f){
    if(f == NULL){
        printf("Erro ao acessar a fila.");
        return -1;
    }

    stFila* fila = (stFila*)f;
    return fila->tamanho;
}

Forma percorreFila(Fila f, int posicao){

}