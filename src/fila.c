#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include "disparador.h"
#include "formas.h"
typedef struct stNo {
    void* conteudo;
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

void insereFila(Fila f,void* conteudo, char type) {
    stFila* fila = (stFila*)f;

    stNo* novoNo = (stNo*)malloc(sizeof(stNo));
    if (novoNo == NULL) {
        printf("Erro ao alocar memória para o novo nó");
        exit(1);
    }
    
    novoNo->conteudo = conteudo;
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

void insereFilaDisparadores(Fila FilaDisparadores, void* d){
    if(FilaDisparadores == NULL || d == NULL){
        printf("Erro ao acessar e inserir um disparador na fila de disparadores.");
        exit(1);
    }

    insereFila(FilaDisparadores,(void*)d,'d');

}

void* removeFila(Fila f) {
    stFila* fila = (stFila*)f;
    if (fila == NULL || fila->primeiro == NULL) {
        return NULL; 
    }
    
    stNo* temp = fila->primeiro;
    void* conteudo = temp->conteudo; 

    fila->primeiro = fila->primeiro->prox;
    // free(temp); 
    fila->tamanho--;

    if (fila->primeiro == NULL) {
        fila->ultimo = NULL;
    }
    return conteudo;
}


void* getPrimeiroConteudoFila(Fila f) {
    stFila* fila = (stFila*)f;

    if (fila == NULL || fila->primeiro == NULL) {
        return NULL;
    }
    
    return fila->primeiro->conteudo;
}

void removerPrimeiroNoFila(Fila f) {
    if(f == NULL) return;
    
    stFila* fila = (stFila*)f;
    if(fila->primeiro == NULL) return;
    
    stNo* noRemover = fila->primeiro;
    fila->primeiro = noRemover->prox;

    if(fila->primeiro == NULL) {
        fila->ultimo = NULL;
    }
    
    fila->tamanho--;
    free(noRemover); 
}

void liberarFilaComConteudo(Fila f) {
    if (f == NULL) {
        return;
    }

    No_t atual = getPrimeiroNoFila(f);
    No_t proximo;

    while (atual != NULL) {
        proximo = getProximoNoFila(atual); 

        void* conteudo = getConteudoDoNoFila(atual);       

        if (conteudo != NULL) {
            Forma forma =(Forma)conteudo;
            char tipo = getTipoForma(forma);
            void* fig = getFiguraForma(forma);
            
            if ( tipo == 'r') {
                liberaRetangulo((Retangulo)fig);
            } else if (tipo == 'c') {
                liberaCirculo((Circulo)fig); 
            } else if (tipo == 'l') {
                liberaLinha((Linha)fig); 
            } else if (tipo == 't') {
                liberaTexto((Texto)fig);
            }
            // free(forma); 
        }

        // free(atual);
        atual = proximo; 
    }

    // free(f);
}

No_t getPrimeiroNoFila(Fila f) {
    stFila* fila = (stFila*)f;
    if(f == NULL) return NULL;
    return (No_t)fila->primeiro;
}

No_t getProximoNoFila(No_t no) {
    if (no == NULL) return NULL;
    stNo* no_interno = (stNo*)no; 
    return (No_t)no_interno->prox;
}

void* getConteudoDoNoFila(No_t no) {
    if (no == NULL) return NULL;
    stNo* no_interno = (stNo*)no;
    return no_interno->conteudo;
}

char getTipoDoNoFila(No_t no) {
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

void* percorreFila(Fila f, int posicao){
    if(f == NULL){
        printf("Fila vazia.");
        return NULL;
    }
    if(posicao < 0){
        printf("Posição negativa passada como parâmetro.");
        return NULL;
    }

    No_t noAtual = getPrimeiroNoFila(f);

    for(int i = 0;i<posicao && noAtual != NULL;i++){
        noAtual = getProximoNoFila(noAtual);
    }

    if(noAtual == NULL){
        printf("Posição inválida.");
        return NULL;
    }

    return getConteudoDoNoFila(noAtual);
}

void liberarArena(Fila arena){
    if(arena == NULL){
        printf("Nada a ser liberado com a função liberar Arena\n");
        return;
    }
    No_t atual = getPrimeiroNoFila(arena);
    if(atual == NULL){
        printf("erro ao liberar arena em liberarArena\n");
        return;
    }
    
    while(atual != NULL){
        void* cont = getConteudoDoNoFila(atual);
        No_t proximo = getProximoNoFila(atual);

        // free(cont);
        // free(atual);
        atual = proximo;        
    }
    // free(arena);
    
}