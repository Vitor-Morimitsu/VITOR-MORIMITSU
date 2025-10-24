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
    Circulo c = (Circulo)forma;
    
    fprintf(arqSvg, "\t<circle id=\"%i\" cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"%s\" fill=\"%s\" />\n",getIDCirculo(c), getCoordXCirculo(c),getCoordYCirculo(c),getRaioCirculo(c), getCorBCirculo(c), getCorPCirculo(c));
}
void desenharRetanguloSVG(FILE* arqSvg, Forma forma){
    Retangulo r = (Retangulo)forma;

    fprintf(arqSvg, "\t<rect id=\"%d\" x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" stroke=\"%s\" fill=\"%s\" />\n",getIDRetangulo(r), getCoordXRetangulo(r),getCoordYRetangulo(r),getWRetangulo(r),getHRetangulo(r), getCorBRetangulo(r),getCorPRetangulo(r));
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

void gerarSvgSaida(FILE* arqTxt, FILE* arqSvgSaida){
    if(arqTxt == NULL || arqSvgSaida == NULL){
        printf("Erro ao abrir arquivos.");
        exit(1);
    }

    
    abrirSvg(arqSvgSaida);
    
    char linha[200];
    char tipoForma;
    while(fgets(linha, sizeof(linha), arqTxt)!= NULL){
        if(linha[0] == '\n' || linha[0] == '#'){
            continue;
        }
        
        Forma forma = NULL;
        sscanf(linha, "%c", &tipoForma);

        if(tipoForma == 'c'){
            //círculo 
            int i;
            double x, y, r;
            char corb[32], corp[32];
            sscanf(linha, "c %d %lf %lf %lf %s %s", &i, &x, &y, &r, corb, corp);
            forma = criaCirculo(i,x,y,r,corb,corp);
            if(forma != NULL){
                desenharCirculoSVG(arqSvgSaida, forma);
            }            

        }else if(tipoForma == 'r'){
            //retângulo
            int i;
            double x, y, w, h;
            char corb[32], corp[32];
            sscanf(linha, "r %d %lf %lf %lf %lf %s %s", &i, &x, &y, &w, &h, corb, corp);
            forma = criaRetangulo(i,x,y,w,h,corb,corp);
            if(forma != NULL){
                desenharRetanguloSVG(arqSvgSaida, forma);
            }

        }else if(tipoForma == 'l'){
            //linha
            int i;
            double x1,y1,x2,y2;
            char cor[32];
            sscanf(linha, "l %d %lf %lf %lf %lf %s", &i, &x1, &y1, &x2, &y2, cor);
            forma = criarLinha(i,x1,y1,x2,y2,cor);
            if(forma != NULL){
                desenharLinhaSVG(arqSvgSaida,forma);
            }

        }else if(tipoForma == 't'){
            //texto
            int i;
            double x, y;
            char corb[32];
            char corp[32];
            char texto[50];
            char a;
            sscanf(linha, "t %d %lf %lf %s %s %c %s", &i, &x, &y, corb, corp, &a, texto);
            forma = criarTexto(i,x,y,corb,corp,a,texto,NULL);
            if(forma != NULL){
                desenharTextoSVG(arqSvgSaida, forma);
            }
        }
        free(forma);

    }
    fecharSVG(arqSvgSaida);
}