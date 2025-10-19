#include <stdio.h>
#include <stdlib.h>
#include "geo.h"


int main(){
    FILE* teste = fopen("C:/Users/morim/OneDrive/Desktop/ESTRUTURA DE DADOS/retg-decres/retg-decres.geo", "r");
    FILE* arqSvg = fopen("testeSvg.svg", "w");
    Fila f = criarFila();
    lerGeo(teste, arqSvg, f);
    return 0;
}