#include "colisoes.h"
#include <math.h>
#include "circulo.h"
#include "retangulo.h" 
#include "linha.h"
#include "texto.h"

int circuloSobrepoeCirculo(Forma f1, Forma f2){
    if(f1 == NULL || f2 == NULL){
        printf("Erro ao acessar as formas.");
        return -1;
    }

    Circulo* c1 = (Circulo*)f1;
    Circulo* c2 = (Circulo*)f2;

    double x1 = getCoordXCirculo(c1); 
    double y1 = getCoordYCirculo(c1);
    double r1 = getRaioCirculo(c1);

    double x2 = getCoordXCirculo(c2);
    double y2 = getCoordYCirculo(c2);
    double r2 = getRaioCirculo(c2);

    //ver se as figuras se sobrepõem
    double dx = x1 - x2;
    double dy = y1 - y2;
    double distanciaEntreCentros = sqrt(dx * dx + dy * dy);
    
    if(distanciaEntreCentros <= (r1+r2)){//figuras se sobrepõem
        return 1;
    }else{
        return 0;
    }
}

int circuloSobrepoeRetangulo(Forma f1, Forma f2);

int circuloSobrepoeLinha(Forma f1, Forma f2);

int circuloSobrepoeTexto(Forma f1, Forma f2);

int retanguloSobrepoeLinha(Forma f1, Forma f2);

int retanguloSobrepoeRetangulo(Forma f1, Forma f2);

int retanguloSobrepoeTexto(Forma f1, Forma f2);

int linhaSobrepoeTexto(Forma f1, Forma f2);

int formasSobrepoem(Forma f1, Forma f2);