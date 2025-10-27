#include "disparador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct disparador{
    int i;
    double x,y;
    void* centro;
    int idEsquerda;
    int idDireita; 
} stDisparador;

Disparador criarDisparador(int i, double x, double y,int idEsquerdo, int idDireito){
    stDisparador* d = (stDisparador*)malloc(sizeof(stDisparador));
    if(d == NULL){
        printf("Erro ao alocar memória para o novo disparador.");
        return NULL;
    }

    d->i = i;
    d->x = x;
    d->y = y;
    d->centro = NULL;
    d->idEsquerda = idEsquerdo;
    d->idDireita = idDireito;
    return d;
}

void* getConteudoCentro(Disparador d) {
    if (d == NULL) {
        return NULL;
    }
    stDisparador* ds = (stDisparador*)d;
    
    return ds->centro;
}

void setConteudoCentro(Disparador d, void* conteudo){
    if(d == NULL){
        printf("Erro ao acessar o disparador para colocar o conteudo no centro\n");
        return;
    }

    stDisparador* ds = (stDisparador*)d;
    ds->centro = conteudo;
}

int getIDDisparador(Disparador d){
    if(d == NULL){
        printf("Erro ao acessar o disparador para retornar a ID.");
        exit(1);
    }
    stDisparador* ds = (stDisparador*)d;

    return ds->i; 
}

double getXDisparador(Disparador d){
    if(d == NULL){
        printf("Erro ao acessar o disparador para retornar a ID.");
        exit(1);
    }

    stDisparador* ds = (stDisparador*)d;
    return ds->x;
}

void carregarPilhaPelaFila(Pilha p, Fila f, int n){
    if(p == NULL){
        printf("Erro ao acessar a pilha para receber as formas da fila.");
        exit(1);
    }
    if(f == NULL){
        printf("Erro ao acessar a fila para passar as formas para pilha.");
        exit(2);
    }
    if(n <= 0){
        return;
    }
    
    No_t noFila = getPrimeiroNoFila(f);

    for(int i = 0; i<n && noFila != NULL;i++){
        void* conteudoInserir = getConteudoDoNoFila(noFila);

        inserirPilha(p,conteudoInserir);

        noFila = getProximoNoFila(noFila);
    }
}

double getYDisparador(Disparador d){
    if(d == NULL){
        printf("Erro ao acessar o disparador para retornar a ID.");
        exit(1);
    }
    stDisparador* ds = (stDisparador*)d;
    return ds->y;
}

int getIDPilhaEsquerda(Disparador d){
    if(d == NULL){
        printf("Erro ao acessar a id esquerda do disparador.");
        return -1;
    }
    stDisparador* ds = (stDisparador*)d;
    return ds->idEsquerda;
}

int getIDPilhaDireita(Disparador d){
    if(d == NULL){
        printf("Erro ao acessar a id direita da pilha do disparador.");
        return -1;
    }
    stDisparador* ds = (stDisparador*)d;
    return ds->idDireita;
}

void setIDDisparador(Disparador d, int i){
    if(d == NULL){
        printf("Disparador inexistente");
        exit(1);
    }
    stDisparador* ds = (stDisparador*)d;
    ds->i = i;
}

void setCarregadorDisparador(Disparador d, int idPilhaEsq, int idPilhaDir){
    if(d == NULL){
        printf("Erro ao acessar o disparador.");
        exit(1);
    }  
    stDisparador* ds = (stDisparador*)d;
    ds->idEsquerda = idPilhaEsq;
    printf("id do disparador %i, id do carregador esquerdo %i, id do carregador direito %i \n",getIDDisparador(d), idPilhaEsq, idPilhaDir);
    ds->idDireita = idPilhaDir;
}

void setPosicaoDisparador(Disparador d, double x, double y){
    if(d == NULL){
        printf("Erro ao posicionar o disparador.");
        exit(1);
    }
    stDisparador* ds = (stDisparador*)d;
    ds->x = x;
    ds->y = y;
}

void pressionaBotao(Disparador d, char lado, int n, Pilha esq, Pilha dir){
    if(d == NULL){
        printf("Erro ao acessar o disparador na função pressionaBotão no disparador.c.\n");
        return;
    }
    if(esq == NULL){
        printf("Pilha esquerda da função pressiona botão está com erro\n");
        return;
    }
    if(dir == NULL){
        printf("Pilha direita da função pressiona botão está com erro\n");
        return;
    }

    stDisparador* ds = (stDisparador*)d;
    
    Pilha origem, destino;
    if(lado == 'e'){
        origem = esq;
        destino = dir;
    }else if(lado == 'd'){
        origem = dir;
        destino = esq;
    }else{
        printf("Lado inválido.");
        return;
    }

    for(int i = 0; i < n;i++){
        void* novo = removerPilha(origem);
        if(novo == NULL){
            printf("Pilha de origem está vazia\n");
            break;
        }

        void* antigo = ds->centro;

        ds->centro = novo;
        //caso haja algo no centro, mover para pilha destino
        if(antigo != NULL){
            inserirPilha(destino, antigo);
        }
    }
}