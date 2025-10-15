#include "disparador.h"
#include "pilha.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"


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
        printf("Erro ao alocar memória para o disparador");
        return;
    }

    d->i = i;
    d->x = x;
    d->y = y;
    d->idEsquerda = idEsquerdo;
    d->idDireita = idDireito;
    return d;
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
        return;
    }
    stDisparador* ds = (stDisparador*)d;
    return ds->idEsquerda;
}

int getIDPilhaDireita(Disparador d){
    if(d == NULL){
        printf("Erro ao acessar a id direita do disparador.");
        return;
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
    ds->idDireita = idPilhaDir;
}

void setPosicaoDisparador(Disparador d, double x, double y){
    if(d == NULL){
        printf("Erro ao acessar o disparador para retornar a ID.");
        exit(1);
    }
    stDisparador* ds = (stDisparador*)d;
    ds->x = x;
    ds->y = y;
}

void pressionaBotao(int idDis, char lado, int n){
    if
}

void destruirDisparador(Disparador ds){
    if(ds == NULL){
        printf("Erro ao acessar o disparador.");
        exit(1);
    }
    free(ds);
}