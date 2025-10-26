#include "printSvgGeo.h"
#include "formas.h"
#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include "geo.h"

void abrirSvg(FILE* arqSvg){
    fprintf(arqSvg, "<svg xmlns:svg=\"http://www.w3.org/2000/svg\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");
}
void desenharCirculoSVG(FILE* arqSvg, Circulo c) {    
    fprintf(arqSvg, "\t<circle id=\"%i\" cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"%s\" fill=\"%s\" />\n",getIDCirculo(c), getCoordXCirculo(c),getCoordYCirculo(c),getRaioCirculo(c), getCorBCirculo(c), getCorPCirculo(c));
}
void desenharRetanguloSVG(FILE* arqSvg, Forma forma){
    Retangulo r = (Retangulo)forma;

    fprintf(arqSvg, "\t<rect id=\"%d\" x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" stroke=\"%s\" fill=\"%s\" opacity=\"0.5\" />\n", getIDRetangulo(r), getCoordXRetangulo(r), getCoordYRetangulo(r), getWRetangulo(r), getHRetangulo(r), getCorBRetangulo(r), getCorPRetangulo(r));
}
void desenharLinhaSVG(FILE* arqSvg, Forma forma){
    Linha l = (Linha)forma;

     fprintf(arqSvg, "<line id=\"%d\" x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\" stroke-width=\"2\" />\n", getIDLinha(l), getX1Linha(l), getY1Linha(l), getX2Linha(l), getY2Linha(l), getCorLinha(l));
}

void desenharTextoSVG(FILE* arqSvg, Forma forma){
    Texto t = (Texto)forma;

    fprintf(arqSvg, "\t<text id=\"%d\" x=\"%f\" y=\"%f\" fill=\"%s\" text-anchor=\"%c\">%s</text>\n",getIDTexto(t),getCoordXTexto(t),getCoordYTexto(t), getCorPTexto(t),getATexto(t), getTxtoTexto(t)); 
}


void fecharSVG(FILE* arqSvg) {
    fprintf(arqSvg, "</svg>\n");
}

void gerarSvgSaida(Fila filaFormas, FILE* arqSvgSaida){
    if(filaFormas == NULL || arqSvgSaida == NULL){
        printf("Erro ao acessar os arquivos para gerar o svg de saída.\n");
    }
    abrirSvg(arqSvgSaida);

    No_t atual = getPrimeiroNoFila(filaFormas);
    if(atual == NULL){
        printf("Fila vazia\n");
        fecharSVG(arqSvgSaida);
        return;
    }
    printf("dentro do svg de saída\n");

    while(atual != NULL){
        Forma formaAtual = (Forma)getConteudoDoNoFila(atual);
        if(formaAtual == NULL){
            printf("Erro ao gerar a formaAtual no arquivo printSvgGeo\n");
        }

        char tipoForma = getTipoForma(formaAtual);
        void* figura = getFiguraForma(formaAtual);
        if(figura == NULL){
            printf("Erro ao acessar a figura void*\n");
        }

        if(tipoForma == 'c'){
            //círculo 
            desenharCirculoSVG(arqSvgSaida,(Circulo*)figura);          
            printf("Printar o círculo no arquivo de saída svg");

        }else if(tipoForma == 'r'){
            //retângulo
            desenharRetanguloSVG(arqSvgSaida,(Retangulo*)figura);          

        }else if(tipoForma == 'l'){
            //linha
            desenharLinhaSVG(arqSvgSaida,(Linha*)figura);
            
        }else if(tipoForma == 't'){
            //texto
            desenharTextoSVG(arqSvgSaida, (Texto*)figura);
            
        }else{
            continue;
        }
        atual = getProximoNoFila(atual);
    }
    fecharSVG(arqSvgSaida);
}