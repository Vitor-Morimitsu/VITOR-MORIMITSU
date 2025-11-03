#include "texto.h"
#include "printSvg.h"
#include "formas.h"
#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include "geo.h"

char* getfFamily(Estilo ts); // Explicit declaration
char* getfSize(Estilo ts);   // Explicit declaration
char* getfWeight(Estilo ts); // Explicit declaration
#include "texto.h"
#include "texto.h"

void abrirSvg(FILE* arqSvg){
    fprintf(arqSvg, "<svg xmlns:svg=\"http://www.w3.org/2000/svg\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");
}
void desenharCirculoSVG(FILE* arqSvg, Circulo circ) {
    if(circ == NULL){
        fprintf(stderr, "ERRO: Forma NULL ao desenhar círculo SVG\n");
        return;
    }    

    fprintf(arqSvg, "\t<circle id=\"%i\" cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"0.5\"/>\n",
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
        fprintf(stderr, "Erro: Forma ou arquivo NULL ao desenhar Texto Svg\n");
        return;
    }
    if (ts != NULL) {
        fprintf(arqSvg, "<text id=\"%d\" x=\"%lf\" y=\"%lf\" style=\"font-family: '%s'; font-size: %spx; font-weight: %s; fill: %s;\"> %s </text>\n",
        getIDTexto(t), 
        getCoordXTexto(t),  
        getCoordYTexto(t), 
        getfFamily(ts),
        getfSize(ts),
        getfWeight(ts), 
        getCorPTexto(t),  
        getTxtoTexto(t));
    } else {
        fprintf(arqSvg, "<text id=\"%d\" x=\"%lf\" y=\"%lf\" fill=\"%s\"> %s </text>\n",
        getIDTexto(t), 
        getCoordXTexto(t),  
        getCoordYTexto(t), 
        getCorPTexto(t),  
        getTxtoTexto(t));
    }
}

void gerarSvgSaida(FILE* svg, Fila pacotes){
    if(svg == NULL || pacotes == NULL){
        printf("Erro ao gerar o svg de saída\n");
        return;
    }
    Fila clone = clonarFilaChao(pacotes);

    Pacote atual = getPrimeiroConteudoFila(clone);
    while(atual != NULL){
        char tipo = getTipoPacote(atual);
        Forma forma = getFormaPacote(atual);

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
        removeFila(clone);
        atual = getPrimeiroConteudoFila(clone);
    }
    liberarClone(clone);
}

void dimensoesDisparo(FILE* svg, double xDis, double yDis, double dx, double dy){
    if(svg == NULL){
        printf("erro ao gerar a dimensão do disparo\n");
        return;
    }
    // Linhas tracejadas azuis formando um retângulo
    // Linha horizontal superior: de (xDis, yDis) até (xDis+dx, yDis)
    fprintf(svg,"<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"blue\" stroke-width=\"2\" stroke-dasharray=\"2 2\" />\n", xDis, yDis, xDis+dx, yDis);
    // Linha vertical direita: de (xDis+dx, yDis) até (xDis+dx, yDis+dy)
    fprintf(svg,"<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"blue\" stroke-width=\"2\" stroke-dasharray=\"2 2\" />\n", xDis+dx, yDis, xDis+dx, yDis+dy);
    // Linha horizontal inferior: de (xDis+dx, yDis+dy) até (xDis, yDis+dy)
    fprintf(svg,"<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"blue\" stroke-width=\"2\" stroke-dasharray=\"2 2\" />\n", xDis+dx, yDis+dy, xDis, yDis+dy);
    // Linha vertical esquerda: de (xDis, yDis+dy) até (xDis, yDis)
    fprintf(svg,"<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"blue\" stroke-width=\"2\" stroke-dasharray=\"2 2\" />\n", xDis, yDis+dy, xDis, yDis);
}

void printAsterisco(FILE* svg, double x, double y){
    if(svg == NULL) return;
    // Asterisco centralizado na posição da forma esmagada
    fprintf(svg,"<text fill=\"red\" x=\"%.2lf\" y=\"%.2lf\" font-size=\"25\" "
                "text-anchor=\"middle\" dominant-baseline=\"middle\" "
                "font-weight=\"bold\">*</text>\n", x, y);
}

void fecharSVG(FILE* arqSvg) {
    fprintf(arqSvg, "</svg>\n");
}
