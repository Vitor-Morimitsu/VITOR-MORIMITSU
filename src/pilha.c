#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"
#include "fila.h"
typedef struct stcelula{
    Conteudo conteudo;
    struct stcelula *prox;
}stCelula;

typedef struct stpilha{
    int id;
    stCelula *topo;
    int tamanho;
}stPilha;

Pilha criarPilha(int ID){
    stPilha* p = (stPilha*)malloc(sizeof(stPilha));
    if(p == NULL){
        printf("Erro ao alocar memória para a Pilha");
        exit(1);
    }
    p->id = ID;
    p->tamanho = 0;
    p->topo = NULL;
    return p;
}

void inserirPilha(Pilha p, Conteudo cont){
    if(p == NULL){
        prinf("Erro ao acessar a pilha.");
        return;
    }
    stPilha* pilha = (stPilha*)p;

    stCelula* novaCelula = (stCelula*)malloc(sizeof(novaCelula));
    if(novaCelula == NULL){
        printf("Erro ao acessar a nova celula criada");
        return;
    }
    novaCelula->conteudo=cont;
    novaCelula->prox = pilha->topo;
    pilha->topo = novaCelula;
    pilha->tamanho++;
}

void carregarPilhaPelaFila(Pilha p, Fila f, int n){
    if(p == NULL){
        printf("Erro ao acessar a pilha.");
        exit(1);
    }
    if(f == NULL){
        printf("Erro ao acessar a fila.");
        exit(2);
    }
    if(n <= 0){
        return;
    }
    stPilha* pilha = (stPilha*)p;
    No_t noFila = getPrimeiroNo(f);

    for(int i = 0; i<n && noFila != NULL;i++){
        Conteudo conteudoInserir = getConteudoDoNo(noFila);

        stCelula* novaCelula = (stCelula*)malloc(sizeof(stCelula));
        if(novaCelula == NULL){
            printf("Erro ao alocar memória para o novo nó.");
            exit(1);
        }

        novaCelula->conteudo = conteudoInserir;
        novaCelula->prox = pilha->topo;

        pilha->topo = novaCelula;
        pilha->tamanho++;
        noFila = getProximoNo(noFila);
    }
}

void removerPilha(Pilha p){
    stPilha* pilha = (stPilha*)p;
    if(pilha == NULL||pilha->topo == NULL){
        return;
    }

    stCelula* temp = pilha->topo;
    pilha->topo = pilha->topo->prox;
    free(temp);
    pilha->tamanho--;
}

Conteudo getConteudoPilha(Pilha p){
    if(p == NULL){
        printf("Erro ao acessar o conteúdo da pilha");
        return NULL;
    }
    stPilha* pilha = (stPilha*)p;
    if(pilha != NULL && pilha->topo != NULL){
        return pilha->topo->conteudo;
    }else{
        return NULL;
    }
}

int getIDPilha(Pilha p){
    if(p == NULL){
        printf("Erro ao acessar a pilha.");
        return -1;
    }
    stPilha* pilha = (stPilha*)p;
    return pilha->id;
}

int getTamanhoPilha(Pilha p){
    if(p == NULL){
        printf("Erro ao acessar o tamanho da pilha.");
        return 0;
    }

    stPilha* pilha = (stPilha*)p;
    return pilha->tamanho;
}

void liberarMemoriaPilha(Pilha p){
    if (p == NULL) {
        printf("Erro ao acessar a pilha para liberar a memória.");
        return;
    }

    stPilha* pilha = (stPilha*)p;
    while(pilha->topo != NULL){
        removerPilha(p);
    }

    free(pilha);
}

No_t getNoTopo(Pilha p) {
    if (p == NULL) return NULL;
    stPilha* pilha = (stPilha*)p;
    return pilha->topo; 
}

No_t getProximoNo(No_t no) {
    if (no == NULL) return NULL;
    stCelula* celula_interna = (stCelula*)no; 
    return celula_interna->prox;
}

Conteudo getConteudoDoNo(No_t no) {
    if (no == NULL) return NULL;
    stCelula* celula_interna = (stCelula*)no;
    return celula_interna->conteudo;
}