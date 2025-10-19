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
    }else{//as figura não se sobrepõem
        return 0;
    }
}

int circuloSobrepoeRetangulo(Forma f1, Forma f2){
    if(f1 == NULL || f2 == NULL){
        printf("Erro ao acessar as figuras.");
        return -1;
    }

    Circulo* c = (Circulo*)f1;
    Retangulo* r =(Retangulo*)f2;

    double xc = getCoordXCirculo(c);
    double yc = getCoordYCirculo(c);
    double raio = getRaioCirculo(c);

    double xr = getCoordXRetangulo(r);
    double yr = getCoordYRetangulo(r);
    double comp = getWRetangulo(r);
    double h = getHRetangulo(r);

    //pontos do retângulo mais próximos do centro do círculo
    double pontoRetMaisProximoX = fmax(xr, fmin(xc, xr + comp));
    double pontoRetMaisProximoY = fmax(yr, fmin(yc, yr + h));

    //diferenças nos eixos
    double dx = xc - pontoRetMaisProximoX;
    double dy = yc - pontoRetMaisProximoY;
    
    double distancia = sqrt(dx*dx + dy*dy);

    if(distancia <= raio){//as formas se sobrepõem
        return 1;
    }else{//não se sobrepõem
        return 0;
    }
}

#include <math.h> // Essencial para fmin, fmax e cálculos
#include "formas.h"
#include "circulo.h"
#include "linha.h"
#include <stdio.h> // Para printf

int circuloSobrepoeLinha(Forma f1, Forma f2){
    if(f1 == NULL || f2 == NULL){
        printf("Erro ao acessar as formas passadas.\n");
        return -1; 
    }

    Circulo* c = (Circulo*)f1;
    Linha* l = (Linha*)f2;

    double xc = getCoordXCirculo(c);
    double yc = getCoordYCirculo(c);
    double raio = getRaioCirculo(c);

    double x1l = getX1Linha(l);
    double x2l = getX2Linha(l);
    double y1l = getY1Linha(l);
    double y2l = getY2Linha(l);

    double dx_segmento = x2l - x1l;
    double dy_segmento = y2l - y1l;
    double comprimentoSegmentoQuadrado = (dx_segmento * dx_segmento) + (dy_segmento * dy_segmento);

    double t = ((xc - x1l) * dx_segmento + (yc - y1l) * dy_segmento) / comprimentoSegmentoQuadrado;

    double t_limitado = fmax(0.0, fmin(1.0, t));

    double pontoMaisProximoX = x1l + t_limitado * dx_segmento;
    double pontoMaisProximoY = y1l + t_limitado * dy_segmento;

    double dx_centro_prox = xc - pontoMaisProximoX;
    double dy_centro_prox = yc - pontoMaisProximoY;
    double distanciaQuadrada = (dx_centro_prox * dx_centro_prox) + (dy_centro_prox * dy_centro_prox);

    if (distanciaQuadrada <= (raio * raio)) {
        return 1; // Sobrepõe
    } else {
        return 0; // Não sobrepõe
    }
}

int circuloSobrepoeTexto(Forma f1, Forma f2){
    if(f1 == NULL || f2 == NULL){
        printf("Erro ao acessar as formas passadas.");
        return -1;
    }

    Circulo* c = (Circulo*)f1;
    Texto* t = (Texto*)f2;

    double xc = getCoordXCirculo(c);
    double yc = getCoordYCirculo(c);
    double raio = getRaioCirculo(c);

    double x1t,x2t,y1t,y2t;
    int comprimentoTxt = quantidadeLetras(t);
    if(comprimentoTxt <= 0) return 0;
    char ancora = getATexto(t);
    if(ancora == 'i'){
        x1t = getCoordXTexto(t);
        y1t = getCoordYTexto(t);
        x2t = x1t + 10*comprimentoTxt;
        y2t = y1t;
    }else if(ancora == 'f'){
        double xa = getCoordXTexto(t);
        double ya = getCoordYTexto(t);

        x1t = xa - 10*comprimentoTxt;
        y1t = ya;

        x2t = xa;
        y2t = ya;
    }else if(ancora == 'm'){
        double xa = getCoordXTexto(t);
        double ya = getCoordYTexto(t);

        x1t = xa - 10*comprimentoTxt;
        y1t = ya;
        
        x2t = xa + 10*comprimentoTxt;
        y2t = ya;
    }

    double dx_segmento = x2t - x1t;
    double dy_segmento = y2t - y1t; 
    double comprimentoSegmentoQuadrado = (dx_segmento * dx_segmento) + (dy_segmento * dy_segmento);

    double z = ((xc - x1t) * dx_segmento + (yc - y1t) * dy_segmento) / comprimentoSegmentoQuadrado;

    double t_limitado = fmax(0.0, fmin(1.0, z));

    double pontoMaisProximoX = x1t + t_limitado * dx_segmento;
    double pontoMaisProximoY = y1t + t_limitado * dy_segmento;

    double dx_centro_prox = xc - pontoMaisProximoX;
    double dy_centro_prox = yc - pontoMaisProximoY;
    double distanciaQuadrada = (dx_centro_prox * dx_centro_prox) + (dy_centro_prox * dy_centro_prox);

    if (distanciaQuadrada <= (raio * raio)) {
        return 1; // Sobrepõe
    } else {
        return 0; // Não sobrepõe
    }    
}

int retanguloSobrepoeLinha(Forma f1, Forma f2) {
    if (f1 == NULL || f2 == NULL) {
        printf("Erro ao acessar as formas passadas.");
        return 0;
    }

    Retangulo* retangulo = (Retangulo*)f1;
    Linha* linha = (Linha*)f2;

    double retanguloX = getCoordXRetangulo(retangulo);
    double retanguloY = getCoordYRetangulo(retangulo);
    double retanguloLargura = getWRetangulo(retangulo);
    double retanguloAltura = getHRetangulo(retangulo);
    double retanguloDireita = retanguloX + retanguloLargura; 
    double retanguloBaixo = retanguloY + retanguloAltura; 

    double linhaX1 = getX1Linha(linha);
    double linhaY1 = getY1Linha(linha);
    double linhaX2 = getX2Linha(linha);
    double linhaY2 = getY2Linha(linha);

    double vetorLinhaX = linhaX2 - linhaX1;
    double vetorLinhaY = linhaY2 - linhaY1;

    //teste para ver se a borda superior é sobrposta pela linha
    {
        double bordaInicioX = retanguloX;
        double bordaInicioY = retanguloY;
        double vetorBordaX = retanguloDireita - retanguloX; 
        double vetorBordaY = 0; 
        
        double denominador = (-vetorBordaX * vetorLinhaY + vetorLinhaX * vetorBordaY);

        if (fabs(denominador) > 0.000001) {
            double parametroBorda_s = (-vetorLinhaY * (linhaX1 - bordaInicioX) + vetorLinhaX * (linhaY1 - bordaInicioY)) / denominador;
            
            double parametroLinha_t = ( vetorBordaX * (linhaY1 - bordaInicioY) - vetorBordaY * (linhaX1 - bordaInicioX)) / denominador;

            if (parametroBorda_s >= 0 && parametroBorda_s <= 1 && parametroLinha_t >= 0 && parametroLinha_t <= 1) {
                return 1; 
            }
        }
    }

    {
        double bordaInicioX = retanguloX;
        double bordaInicioY = retanguloBaixo;
        double vetorBordaX = retanguloDireita - retanguloX; 
        double vetorBordaY = 0;
        double denominador = (-vetorBordaX * vetorLinhaY + vetorLinhaX * vetorBordaY);

        if (fabs(denominador) > 0.000001) {
            double parametroBorda_s = (-vetorLinhaY * (linhaX1 - bordaInicioX) + vetorLinhaX * (linhaY1 - bordaInicioY)) / denominador;
            double parametroLinha_t = ( vetorBordaX * (linhaY1 - bordaInicioY) - vetorBordaY * (linhaX1 - bordaInicioX)) / denominador;
            if (parametroBorda_s >= 0 && parametroBorda_s <= 1 && parametroLinha_t >= 0 && parametroLinha_t <= 1) {
                return 1; 
            }
        }
    } 

    {
        double bordaInicioX = retanguloX;
        double bordaInicioY = retanguloY;
        double vetorBordaX = 0;      
        double vetorBordaY = retanguloBaixo - retanguloY; 
        double denominador = (-vetorBordaX * vetorLinhaY + vetorLinhaX * vetorBordaY);

        if (fabs(denominador) > 0.000001) {
            double parametroBorda_s = (-vetorLinhaY * (linhaX1 - bordaInicioX) + vetorLinhaX * (linhaY1 - bordaInicioY)) / denominador;
            double parametroLinha_t = ( vetorBordaX * (linhaY1 - bordaInicioY) - vetorBordaY * (linhaX1 - bordaInicioX)) / denominador;
            if (parametroBorda_s >= 0 && parametroBorda_s <= 1 && parametroLinha_t >= 0 && parametroLinha_t <= 1) {
                return 1; 
            }
        }
    } 

    {
        double bordaInicioX = retanguloDireita;
        double bordaInicioY = retanguloY;
        double vetorBordaX = 0; 
        double vetorBordaY = retanguloBaixo - retanguloY;    
        double denominador = (-vetorBordaX * vetorLinhaY + vetorLinhaX * vetorBordaY);

        if (fabs(denominador) > 0.000001) {
            double parametroBorda_s = (-vetorLinhaY * (linhaX1 - bordaInicioX) + vetorLinhaX * (linhaY1 - bordaInicioY)) / denominador;
            double parametroLinha_t = ( vetorBordaX * (linhaY1 - bordaInicioY) - vetorBordaY * (linhaX1 - bordaInicioX)) / denominador;
            if (parametroBorda_s >= 0 && parametroBorda_s <= 1 && parametroLinha_t >= 0 && parametroLinha_t <= 1) {
                return 1; 
            }
        }
    } 

    int ponto1Dentro = (linhaX1 >= retanguloX && linhaX1 <= retanguloDireita &&
                        linhaY1 >= retanguloY && linhaY1 <= retanguloBaixo);
    int ponto2Dentro = (linhaX2 >= retanguloX && linhaX2 <= retanguloDireita &&
                        linhaY2 >= retanguloY && linhaY2 <= retanguloBaixo);

    if (ponto1Dentro || ponto2Dentro) {
       return 1; 
    }

    return 0;
}

int retanguloSobrepoeRetangulo(Forma f1, Forma f2){
    if(f1 == NULL || f2 == NULL){
        printf("Erro ao acessar as formas passadas.");
        return -1;
    }

    Retangulo* r1 = (Retangulo*)f1;
    Retangulo* r2 = (Retangulo*)f2;
}

int retanguloSobrepoeTexto(Forma f1, Forma f2){
    if(f1 == NULL || f2 == NULL){
        printf("Erro ao acessar as formas passadas.");
        return -1;
    }
}

int linhaSobrepoeTexto(Forma f1, Forma f2){
    if(f1 == NULL || f2 == NULL){
        printf("Erro ao acessar as formas passadas.");
        return -1;
    }
}

int formasSobrepoem(Forma f1, Forma f2){
    if(f1 == NULL || f2 == NULL){
        printf("Erro ao acessar as formas passadas.");
        return -1;
    }
}