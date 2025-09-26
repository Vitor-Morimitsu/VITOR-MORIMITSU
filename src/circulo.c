#include "circulo.h"
#include "stdio.h"
#include "stdlib.h"

#define PI 3.14

typedef struct Circulo{
    int i;
    double x;
    double y;
    double r;
    char* corb, corp;
}stCirculo;

Circulo criaCirculo(int i, double x, double y, double r, char* corb, char* corp){
    stCirculo *c = malloc(sizeof(stCirculo));
    c->i = i;
    c->x = x;
    c->y = y;
    c->r = r;
    c->corb = (char*)malloc(strlen(corb) + 1);
    if(c->corb == NULL){
        printf("Erro ao alocar memória para a cor de borda.");
        exit(1);
    }
    strcpy(c->corb, corb);

    c->corp = (char*)malloc(strlen(corp) + 1);
    if(c->corp == NULL){
        printf("Erro ao alocar memória para a cor de preenchimento");
        exit(1);
    }
    strcpy(c->corp, corp);

    return ((stCirculo*)c);
}

int getIDCirculo(Circulo c){
    return ((stCirculo*)c)->i;
}

double getCoordXCirculo(Circulo c){
    return ((stCirculo*)c)->x;
}

double getCoordYCirculo(Circulo c){
    return ((stCirculo*)c)->y;
}

double getRaio(Circulo c){
    return ((stCirculo*)c)->r;
}

char* getCorBCirculo(Circulo c){
    return ((stCirculo*)c)->corb;
}

char* getCorPCirculo(Circulo c){
    return ((stCirculo*)c)->corp;
}

double getAreaCirculo(Circulo c){
    return PI*((stCirculo*)c)->r*((stCirculo*)c)->r;
}

void setIDCirculo(Circulo c, int i){
    ((stCirculo*)c)->i = i;
}

void setXCirculo(Circulo c, double x){
    ((stCirculo*)c)->x = x;
}

void setYCirculo(Circulo c, double y){
    ((stCirculo*)c)->y = y;
}

void setCorbCirculo(Circulo c, char* corb){
    ((stCirculo*)c)->corb = corb;
}

void setCorPCirculo(Circulo c, char* corp){
    ((stCirculo*)c)->corp = corp;
}