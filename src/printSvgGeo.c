#include "printSvgGeo.h"
#include "formas.h"
#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include "geo.h"

void desenharCirculoSVG(FILE* arqSvg, Forma forma) {
    Circulo* c = (Circulo*)forma;
    
    fprintf(arqSvg, "\t<circle cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"%s\" fill=\"%s\" />\n",getCirculoX(c), getCirculoY(c), getCirculoR(c), getCirculoCorb(c), getCirculoCorp(c));
}
void desenharRetanguloSVG(FILE* arqSvg, Forma forma){
    Retangulo* r = (Retangulo*)forma;

    fprintf(arqSvg, "\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" stroke=\"%s\" fill=\"%s\" />\n",getRetanguloX(r), getRetanguloY(r), getRetanguloW(r), getRetanguloH(r), getRetanguloCorb(r), getRetanguloCorp(r));
}
