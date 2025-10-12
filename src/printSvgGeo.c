#include "printSvgGeo.h"
#include "formas.h"
#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include "geo.h"

typedef void* Forma;

typedef void* Fila;

void printSVG(FILE* arqSvg, Fila f, Forma* form){
    if(arqSvg == NULL){
        printf("Erro ao abrir o arquivo .svg");
        return;
    }
    if(f == NULL){
        printf("Fila vazia.");
        return;
    }

    Aux* temp = f


}