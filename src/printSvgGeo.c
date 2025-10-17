#include "printSvgGeo.h"
#include "formas.h"
#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include "geo.h"
void abrirSvg(FILE* arqSvg){
    fprintf(arqSvg, "<svg xmlns:svg=\"http://www.w3.org/2000/svg\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");
}
void desenharCirculoSVG(FILE* arqSvg, Forma forma) {
    Circulo* c = (Circulo*)forma;
    
    fprintf(arqSvg, "\t<circle id=\"%i\" cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"%s\" fill=\"%s\" />\n",getIDCirculo(c), getCoordXCirculo(c),getCoordYCirculo(c),getRaioCirculo(c), getCorBCirculo(c), getCorPCirculo(c));
}
void desenharRetanguloSVG(FILE* arqSvg, Forma forma){
    Retangulo* r = (Retangulo*)forma;

    fprintf(arqSvg, "\t<rect id=\"%d\" x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" stroke=\"%s\" fill=\"%s\" />\n",getIDRetangulo(r), getCoordXRetangulo(r),getCoordYRetangulo(r),getWRetangulo(r),getHRetangulo(r), getCorBordaRetangulo(r),getCorPRetangulo(r));
}
void desenharLinhaSVG(FILE* arqSvg, Forma forma){
    Linha* l = (Linha*)forma;

     fprintf(arqSvg, "<line id=\"%d\" x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\" stroke-width=\"2\" />\n", getIDLinha(l), getX1Linha(l), getY1Linha(l), getX2Linha(l), getY2Linha(l), getCorLinha(l));
}

void desenharTextoSVG(FILE* arqSvg, Forma forma){
    Texto* t = (Texto*)forma;

 fprintf(arqSvg, "\t<text id=\"%d\" x=\"%f\" y=\"%f\" fill=\"%s\" text-anchor=\"%s\">%s</text>\n",getIDTexto(t),getCoordXTexto(t),getCoordYTexto(t), getCorPTexto(t),getAncoraTexto(t), getTextoConteudo(t)); 
}

void fecharSvg(FILE* arqSvg){
    fprintf(arqSvg, "</svg>\n");
}