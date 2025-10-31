#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disparador.h"
#include "carregador.h"
#include "fila.h"
#include "pilha.h"

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

void atch(Disparador d,Carregador car, char lado){
    if(d == NULL || car == NULL){
        printf("Impossível realizar o atch \n");
        exit(1);
    }
    stDisparador* ds = (stDisparador*)d;
    if(lado == 'e'){
        ds->esquerdo = car;
    }else{
        ds->direito = car;
    }
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

Forma engatilhada(Disparador d){
    return ((stDisparador*)d)->centro;
}

int shft(Disparador d, char lado){
    stDisparador* ds = (stDisparador*)d;
    if(ds == NULL || ds->direito == NULL || ds->esquerdo == NULL){
        printf("Erro ao realizar o comanodo shft do disparador\n");
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

double getYDisparador(Disparador d){
    if(d == NULL){
        printf("Erro ao acessar o disparador para retornar a ID.");
        exit(1);
    }
    stDisparador* ds = (stDisparador*)d;
    return ds->y;
}

void setIDDisparador(Disparador d, int i){
    if(d == NULL){
        printf("Disparador inexistente");
        exit(1);
    }
    stDisparador* ds = (stDisparador*)d;
    ds->i = i;
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

void destruirDisparador(Disparador d){
    if(d == NULL){
        printf("Erro ao destruir o disparador\n");
        exit(1);
    }
    stDisparador* ds = (stDisparador*)d;
    destruirCarregador(ds->direito);
    destruirCarregador(ds->esquerdo);
    free(ds);
}

Carregador getCarregadorDisparador(Disparador d, char lado){
    if(d == NULL){
        printf("Erro ao acessar o disparador\n");
        exit(1);
    }
    stDisparador* ds = (stDisparador*)d;
    Carregador car;
    if(lado == 'e'){
        return ds->esquerdo;
    }else if(lado == 'd'){
        return ds->direito;
    }else{
        printf("Lado inválido\n");
    }
}