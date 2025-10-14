#include "disparador.h"
#include "pilha.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"


typedef struct disparador{
    int i;
    double x,y;
    void* centro;
    Pilha esquerda;
    Pilha direita; 
} stDisparador;

Disparador criarDisparador(int i, double x, double y){
    stDisparador* d = (stDisparador*)malloc(sizeof(stDisparador));
    if(d == NULL){
        printf("Erro ao alocar memória para o disparador");
        return;
    }

    d->i = i;
    d->x = x;
    d->y = y;
    d->esquerda = criarPilha();
    d->direita = criarPilha();

    if(d->esquerda == NULL || d->direita == NULL){
        printf("Erro ao alocar memória para os carregadores do disparador.");
        free(d); //libera o disparador que não teve os carregadores criados
        return;
    }

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


Pilha getConteudoCarEsq(Disparador d){
    if(d == NULL){
        printf("Disparador inexistente");
        return NULL;
    }
    stDisparador* ds = (stDisparador*)d;
    return ds->esquerda;
}

Pilha getConteudoCarDir(Disparador d){
    if(d == NULL){
        printf("Disparador inexistente");
        return NULL;
    }
    stDisparador* ds = (stDisparador*)d;

    return ds->direita;
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
    get
    

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

void destruirDisparador(Disparador ds){
    if(ds == NULL){
        printf("Erro ao acessar o disparador.");
        exit(1);
    }

    stDisparador* d = (stDisparador*)ds;
    liberarMemoriaPilha(d->esquerda);
    liberarMemoriaPilha(d->direita);

    free(d);
}