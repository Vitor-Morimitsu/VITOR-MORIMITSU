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
        printf("Erro ao acessar a pilha para receber as fomras da fila.");
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
        printf("Erro ao acessar a id direita do disparador.");
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
    printf("id do carregador %i e o carregador %i na esquerda\n",getIDDisparador(d), idPilhaEsq);
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
        printf("Erro ao acessar o disparador.");
        exit(1);
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

    if(n == 1){ //a forma que está no topo da pilha vai para o centro
        void* novo = getConteudoPilha(origem);
        if(novo == NULL){
            return;
        }

        void* antigo = ds->centro;

        removerPilha(origem);

        ds->centro = novo;

        if(antigo != NULL){//caso exista um conteúdo no centro do disparador
            inserirPilha(destino, antigo);
        }
    }else if(n > 1){
        for(int i = 0;i < n; i++){
            void* novo = getConteudoPilha(origem);
            if(novo == NULL){
                break; // não existe nenhum conteudo na pilha
            }
            void* antigo =ds->centro;
            removerPilha(origem);
            ds->centro = novo;
            if(antigo != NULL){
                inserirPilha(destino, antigo);
            }

        }
    }
}

void destruirDisparador(Disparador ds){
    if(ds == NULL){
        printf("Erro ao acessar o disparador.");
        exit(1);
    }
    free(ds);
}