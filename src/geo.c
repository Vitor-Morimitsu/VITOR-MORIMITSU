#include "geo.h"
#include "circulo.h"
#include "texto.h"
#include "linha.h"
#include "retangulo.h"
#include "formas.h"
#include <string.h>
#include <stdio.h>
#include "printSvgGeo.h"

typedef void* Forma;

#define MAX_SIZE 200

void lerGeo(FILE* arqGeo, Fila chao, FILE* arqSvgEntrada){ 
    if(arqGeo == NULL){
        printf("Arquivo .geo não encontrado");
        exit(1);
    }

    char linha[MAX_SIZE];
    char tipoForma;
    
    abrirSvg(arqSvgEntrada);
    printf("\nPassou abertura svg\n");
    
    while(fgets(linha, sizeof(linha), arqGeo) != NULL){
        if(linha[0] == '\n' || linha[0] == '#'){
            continue;
        }
        
        sscanf(linha, "%c", &tipoForma);
        
        
        //Forma novaForma = NULL;
        
        if (tipoForma == 'c') {
            int i;
            double x, y, r;
            char corb[32], corp[32];
            sscanf(linha, "c %d %lf %lf %lf %s %s", &i, &x, &y, &r, corb, corp);
            printf("passou scanf circulo\n");
            Forma novaForma = criaCirculoForma(i, 'c',x, y, r, corb, corp);
            desenharCirculoSVG(arqSvgEntrada, getFiguraForma(novaForma));
            printf("passou desenho cirfculo svg");
            insereFila(chao, novaForma, 'c');
            printf("Circulo insere fila");
            
        } else if (tipoForma == 'r') {
            int i;
            double x, y, w, h;
            char corb[32], corp[32];
            sscanf(linha, "r %d %lf %lf %lf %lf %s %s", &i, &x, &y, &w, &h, corb, corp);
            Forma novaForma = criaRetanguloForma(i,'r', x, y, w, h, corb, corp);
            printf("passou novaForma retangulo\n");
            desenharRetanguloSVG(arqSvgEntrada,getFiguraForma(novaForma));
            printf("passou desenho retangulo");
            insereFila(chao, novaForma, 'r');
            printf("retangulo insere fila");
            
        } else if (tipoForma == 'l'){
            int i;
            double x1,y1,x2,y2;
            char cor[32];
            sscanf(linha, "l %d %lf %lf %lf %lf %s", &i, &x1, &y1, &x2, &y2, cor);
            printf("passou scanf linha\n");
            Forma novaForma = criaLinhaForma(i,'l', x1,y1,x2,y2,cor);
            desenharLinhaSVG(arqSvgEntrada, getFiguraForma(novaForma));
            printf("passou desenho linha");
            insereFila(chao,novaForma,'l');
            printf("linha insere fila");
            
            
        } else if( tipoForma == 't'){
            int i;
            double x, y;
            char corb[32];
            char corp[32];
            char texto[50];
            char a;
            sscanf(linha, "t %d %lf %lf %s %s %c %s", &i, &x, &y, corb, corp, &a, texto);
            printf("passou scanf texto\n");
            Forma novaForma = criaTextoForma(i,'t',x,y,corb,corp,a,texto,NULL);
            desenharTextoSVG(arqSvgEntrada, getFiguraForma(novaForma));
            printf("passou desenho texto");
            insereFila(chao, novaForma, 't');
            printf("texto insere fila");
        }
        
    }    
    fecharSVG(arqSvgEntrada);
}