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

    Circulo c = (Circulo*)f1;
    
}

int circuloSobrepoeRetangulo(Forma f1, Forma f2);

int circuloSobrepoeLinha(Forma f1, Forma f2);

int circuloSobrepoeTexto(Forma f1, Forma f2);

int retanguloSobrepoeLinha(Forma f1, Forma f2);

int retanguloSobrepoeRetangulo(Forma f1, Forma f2);

int retanguloSobrepoeTexto(Forma f1, Forma f2);

int linhaSobrepoeTexto(Forma f1, Forma f2);

int formasSobrepoem(Forma f1, Forma f2);