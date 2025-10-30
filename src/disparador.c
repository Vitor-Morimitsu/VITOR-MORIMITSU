#include "disparador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "carregador.h"

typedef struct disparador{
    int i;
    double x,y;
    Forma centro;
    Carregador esquerdo;
    Carregador direito;
} stDisparador;

Disparador criarDisparador(int i, double x, double y){
    stDisparador* d = (stDisparador*)malloc(sizeof(stDisparador));
    if(d == NULL){
        printf("Erro ao alocar memória para o novo disparador.");
        return NULL;
    }

    d->i = i;
    d->x = x;
    d->y = y;
    d->centro = NULL;
    d->esquerdo = NULL;
    d->direito = NULL;
    return d;
}


int getIDDisparador(Disparador d){
    stDisparador* ds = (stDisparador*)d;
    if(ds == NULL){
        printf("Id do disparador não encontrada\n");
        exit(1);
    }

    return ds->i;
}

Forma getConteudoCentro(Disparador d) {
    if (d == NULL) {
        return NULL;
    }
    return((stDisparador*)d)->centro;
}

int shft(Disparador d, char lado){
    stDisparador* ds = (stDisparador*)d;
    if(ds == NULL || ds->direito == NULL || ds->esquerdo){
        printf("Erro ao preparar o disparo do disparador\n");
        exit(1);
    }
    Carregador original = (lado == 'd') ? ds->direito : ds->esquerdo;
    Carregador destino = (lado == 'e') ? ds->esquerdo : ds->direito;

    if(ds->centro != NULL){
        if(destino != NULL){
            Pilha pDestino = getPilhaCarregador(destino);
            inserirPilha(pDestino, ds->centro);
        }else{
            printf("Carregador de destino não existe\n");
            exit(1);
        }
        ds->centro = NULL;
    }

    if(original != NULL){
        Pilha pOriginal = getPilhaCarregador(original);
        if(getTamanhoPilha(original) != 0){
            removerPilha(original);
        }else{
            ds->centro = NULL;
            return 0;
        }
    }
}

Forma dsp(Disparador d){
    stDisparador* ds = (stDisparador*)d;
    if(d == NULL){
        printf("Erro ao realizar o disparo da forma\n");
        exit(1);
    }

    Forma disparada = ds->centro;
    ds->centro = NULL;

    return disparada;
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