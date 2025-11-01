#include "printSvg.h"
#include "formas.h"
#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include "geo.h"

void abrirSvg(FILE* arqSvg){
    fprintf(arqSvg, "<svg xmlns:svg=\"http://www.w3.org/2000/svg\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");
}
void desenharCirculoSVG(FILE* arqSvg, Circulo circ) {
    if(circ == NULL){
        fprintf(stderr, "ERRO: Forma NULL ao desenhar círculo SVG\n");
        return;
    }    

    fprintf(arqSvg, "\t<circle id=\"%i\" cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"%s\" fill=\"%s\" />\n",
        getIDCirculo(circ), 
        getCoordXCirculo(circ),
        getCoordYCirculo(circ),
        getRaioCirculo(circ), 
        getCorBCirculo(circ), 
        getCorPCirculo(circ));
}

void desenharRetanguloSVG(FILE* arqSvg, Retangulo r){
    if(r == NULL || arqSvg == NULL){
        fprintf(stderr, "ERRO: Forma ou arquivo NULL ao desenhar retângulo SVG\n");
        return;
    }
    fprintf(arqSvg, "\t<rect id=\"%d\" x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" fill=\"%s\" opacity=\"0.5\" />\n", 
        getIDRetangulo(r), 
        getCoordXRetangulo(r),
        getCoordYRetangulo(r), 
        getWRetangulo(r), 
        getHRetangulo(r), 
        getCorBRetangulo(r), 
        getCorPRetangulo(r));
}
void desenharLinhaSVG(FILE* arqSvg, Linha l){
    if(l == NULL || arqSvg == NULL){
        fprintf(arqSvg,"Erro: Forma ou arquivo NULL ao desenhar Linha Svg\n");
        return;
    }
     fprintf(arqSvg, "<line id=\"%d\" x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\" stroke-width=\"2\" />\n", 
        getIDLinha(l), 
        getX1Linha(l), 
        getY1Linha(l), 
        getX2Linha(l), 
        getY2Linha(l), 
        getCorLinha(l));
}

void desenharTextoSVG(FILE* arqSvg, Texto t, Estilo ts){
    if(arqSvg == NULL || t == NULL){
        fprintf(arqSvg, "Erro: Forma ou arquivo NULL ao desenhar Texto Svg\n");
        return;
    }
    fprintf(arqSvg, "<text id=\"%d\" x=\"%lf\" y=\"%lf\" style=\"font-family: '%s'; font-size: %spx; font-weight: %s; fill: %s;\"> %s </text>\n",
    getIDTexto(t), 
    getCoordXTexto(t),  
    getCoordYTexto(t), 
    getfFamily(ts),
    getfSize(ts),
    getfWeight(ts), 
    getCorPTexto(t),  
    getTxtoTexto(t));
}

void gerarSvgSaida(FILE* svg, Fila pacotes){
    if(svg == NULL || pacotes == NULL){
        printf("Erro ao gerar o svg de saída\n");
        return;
    }

    while(noAtual != NULL){
        Pacote pac = getConteudoNo(noAtual);
        char tipo = getTipoPacote(pac);
        Forma forma = getFormaPacote(pac);

        if(forma == NULL){
            printf("Erro ao acessar a forma do pacote em gerarSvgSaida\n");
            noAtual = getProximoNo(noAtual);
            continue;
        }

        if(tipo == 'c'){
            desenharCirculoSVG(svg, (Circulo)forma);
        } else if(tipo == 'r'){
            desenharRetanguloSVG(svg, (Retangulo)forma);
        } else if(tipo == 'l'){
            desenharLinhaSVG(svg, (Linha)forma);
        } else if(tipo == 't'){
            Estilo es = getEstiloTexto((Texto)forma);
            desenharTextoSVG(svg, (Texto)forma, es);
        }
        
        noAtual = getProximoNo(noAtual);
    }
}

void fecharSVG(FILE* arqSvg) {
    fprintf(arqSvg, "</svg>\n");
}
