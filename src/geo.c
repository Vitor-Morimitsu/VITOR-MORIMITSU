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
    
    while(fgets(linha, sizeof(linha), arqGeo) != NULL){
        if(linha[0] == '\n' || linha[0] == '#'){
            continue;
        }
        
        sscanf(linha, "%c", &tipoForma);
        
        if (tipoForma == 'c') {
            int i;
            double x, y, r;
            char corb[32], corp[32];
            sscanf(linha, "c %d %lf %lf %lf %s %s", &i, &x, &y, &r, corb, corp);
            Pacote pac = criarPacote;
            Circulo circ = criaCirculo(i,x,y,r,corb,corp);
            setFormaPacote(pac, circ);
            setTipoPacote(pac, 'c');
            insereFila(chao, pac);
            desenharCirculoSVG(arqSvgEntrada,circ);
            
        } else if (tipoForma == 'r') {
            int i;
            double x, y, w, h;
            char corb[32], corp[32];
            sscanf(linha, "r %d %lf %lf %lf %lf %s %s", &i, &x, &y, &w, &h, corb, corp);
            Pacote pac = criarPacote();
            Retangulo ret = criaRetangulo(i,x,y,w,h,corb,corp);
            setFormaPacote(pac, ret);
            setTipoPacote(pac,'r');
            insereFila(chao,pac);
            desenharRetanguloSVG(arqSvgEntrada,ret);
            
        } else if (tipoForma == 'l'){
            int i;
            double x1,y1,x2,y2;
            char cor[32];
            sscanf(linha, "l %d %lf %lf %lf %lf %s", &i, &x1, &y1, &x2, &y2, cor);
            printf("passou scanf linha\n");
            Pacote pac = criarPacote();
            Linha lin = criarLinha(i,x1,y1,x2,y2,cor);
            setFormaPacote(pac, lin);
            setTipoPacote(pac, 'l');
            insereFila(chao,pac);     
            desenharLinhaSVG(arqGeo,lin)       
            
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