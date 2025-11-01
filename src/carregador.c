#include "carregador.h"

typedef struct{
    int id;
    Pilha pilha;
}stCarregador;

Carregador criarCarregador(int i){
    stCarregador* car = malloc(sizeof(stCarregador));
    if(car == NULL){
        printf("Erro ao alocar memória para o novo carregador\n");
        exit(1);
    }

    car->id = i;
    car->pilha = criarPilha();

    return((stCarregador*)car);
}

int getIDCarregador(Carregador car){
    stCarregador* c = (stCarregador*)car;
    if(c == NULL){
        printf("Erro ao achar o carregador\n");
        exit(1);
    }

    return c->id;
}

void destruirCarregador(Carregador car){
    stCarregador* c = (stCarregador*)car;
    if(c == NULL){
        printf("Erro ao destruir o carregador\n");
        return;
    }

    destruirPilha(c->pilha);
    free(c);
}

Pilha getPilhaCarregador(Carregador car){
    return ((stCarregador*)car)->pilha;
}