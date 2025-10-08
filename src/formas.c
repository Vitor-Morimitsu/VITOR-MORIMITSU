#include <stdio.h>
#include <stdlib.h>
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "disparador.h"
#include "pilha.h"
#include <math.h>

typedef void* Forma;

typedef struct forma{
    Forma fig;
    char tipo;
}stForma;

Forma criaRetanguloForma(int i, double x, double y, double w, double h, char* corb, char* corp){
    stForma* f = malloc(sizeof(stForma));
    if(f == NULL){
        printf("Erro ao alocar memória para a nova forma.");
        return NULL;
    }
    
    f->fig = criaRetangulo(i,x,y,w,h,corb,corp);
    f->tipo = 'r';

    return f;
}

Forma criaCirculoForma(int i, double x, double y, double r, char* corb, char* corp){
    stForma* f = malloc(sizeof(stForma));
    if(f == NULL){
        printf("Erro ao alocar memória para a nova forma.");
        return NULL;
    }

    f->fig = criaCirculo(i,x,y,r,corb,corp);
    f->tipo = 'c';

    return f;
}

Forma criaLinhaForma(int i, double x1, double y1, double x2, double y2, char* cor){
    stForma* f = malloc(sizeof(stForma));
    if(f == NULL){
        printf("Erro ao alocar memória para a nova forma.");
        return NULL;
    }

    f->fig = criarLinha(i,x1,y1,x2,y2,cor);
    f->tipo = 'l';

    return f;
}

Forma criaTextoForma(int i, double x, double y, char* corb, char* corp, char a, char* txto, Estilo ts){
    stForma* f = malloc(sizeof(stForma));
    if(f == NULL){
        printf("Erro ao alocar memória para a nova forma.");
        return NULL;
    }

    f->fig = criarTexto(i,x,y,corb,corp,a,txto,ts);
    f->tipo = 't';

    return f;
}

char getTipoForma(Forma f) {
    if (f == NULL) {
        printf("Erro ao buscar a ID da forma");
        return NULL;
    }

    stForma* formaWrapper = (stForma*)f;

    switch (formaWrapper->tipo) {
        case 'r': {
            Retangulo ret = (Retangulo*)formaWrapper->fig;
            return getIDRetangulo(ret); 
        }
        case 'c': {
            Circulo circ = (Circulo*)formaWrapper->fig;
            return getIDCirculo(circ); 
        }
        case 'l': {
            Linha lin = (Linha*)formaWrapper->fig;
            return getIDLinha(lin);
        }
        case 't': {
            Texto txt = (Texto*)formaWrapper->fig;
            return getIDTexto(txt);
        }
        default:
            // Tipo de forma desconhecido
            return -1; 
    }
}

double getXForma(Forma f){
    if(f == NULL){
        printf("Erro ao buscar a coordenada X da forma.");
        return NAN;
    }

    stForma* tipoForma = (stForma*)f;

    switch (tipoForma->tipo){
        case 'r':{
            Retangulo ret =(Retangulo)tipoForma->fig;
            return getCoordXRetangulo(ret);
        }
        case 'c':{
            Circulo cir = (Circulo)tipoForma->fig;
            return getCoordXCirculo(cir);
        }
        case 'l':{
            Linha lin = (Linha)tipoForma->fig;
            return getX1Linha(lin);
        }
        case 't':{
            Texto txt=(Texto)tipoForma->fig;
            return getCoordXTexto(txt);
        }
        default:
            return -1;
    }
}
double getYForma(Forma f){
    if(f == NULL){
        printf("Erro ao buscar a coordenada y da forma");
        return NAN;
    }

    stForma* tipoForma = (stForma*)f;
    switch (tipoForma->tipo){
        case 'r': {
            Retangulo ret = (Retangulo)tipoForma->fig;
            return getCoordYRetangulo(ret);
        }
        case 'c':{
            Circulo circ = (Circulo)tipoForma->fig;
            return getCoordYCirculo(circ);
        }
        case 'l':{
            Linha lin = (Linha)tipoForma->fig;
            return getY1Linha(lin);
        }
        case 't':{
            Texto txt = (Texto)tipoForma->fig;
            return getCoordXTexto(txt);
        }
    }
}

void liberaForma(Forma f){
    if(f == NULL){
        return; 
    }

    stForma* formaWrapper = (stForma*)f;

    switch (formaWrapper->tipo) {
        case 'r':
            liberaRetangulo(formaWrapper->fig);
            break;
        case 'c':
            liberaCirculo(formaWrapper->fig);
            break;
        case 'l':
            liberaLinha(formaWrapper->fig);
            break;
        case 't':
            liberaTexto(formaWrapper->fig);
            break;
    }

    free(formaWrapper);
}