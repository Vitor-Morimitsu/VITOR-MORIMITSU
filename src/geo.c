#include "texto.h"
#include "geo.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "formas.h"
#include <string.h>
#include <stdio.h>
#include "printSvg.h"

Estilo criarEstilo(char *fFamily, char *fWeight, char *fSize); 
#include "texto.h"

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
            Pacote pac = criarPacote();
            Circulo circ = criaCirculo(i,x,y,r,corb,corp);
            setFormaPacote(pac,(Forma)circ);
            setTipoPacote(pac, 'c');
            insereFila(chao,(Forma)pac);
            desenharCirculoSVG(arqSvgEntrada,circ);
            
        } else if (tipoForma == 'r') {
            int i;
            double x, y, w, h;
            char corb[32], corp[32];
            Pacote pac = criarPacote();
            sscanf(linha, "r %d %lf %lf %lf %lf %s %s", &i, &x, &y, &w, &h, corb, corp);
            Retangulo ret = criaRetangulo(i,x,y,w,h,corb,corp);
            setFormaPacote(pac, (Forma)ret);
            setTipoPacote(pac,'r');
            insereFila(chao,(Forma)pac);
            desenharRetanguloSVG(arqSvgEntrada,ret);
            
        } else if (tipoForma == 'l'){
            int i;
            double x1,y1,x2,y2;
            char cor[32];
            sscanf(linha, "l %d %lf %lf %lf %lf %s", &i, &x1, &y1, &x2, &y2, cor);
            Pacote pac = criarPacote();
            Linha lin = criarLinha(i,x1,y1,x2,y2,cor);
            setFormaPacote(pac, (Forma)lin);
            setTipoPacote(pac, 'l');
            insereFila(chao,(Forma)pac);     
            desenharLinhaSVG(arqSvgEntrada,lin);       
            
        } else if( tipoForma == 't'){
            int i;
            double x, y;
            char corb[32];
            char corp[32];
            char texto[50];
            char a;
            sscanf(linha, "t %d %lf %lf %s %s %c %s ", &i, &x, &y, corb, corp, &a, texto);
            Pacote pac = criarPacote();
            Texto text = criarTexto(i,x,y,corb,corp,a,texto);
            setFormaPacote(pac,(Texto)text);

            const char* ts_marker = strstr(linha, " ts ");
            if(ts_marker != NULL){
                char font[500], weight[500], size[500];
                sscanf(ts_marker, " ts %s %s %s", font, weight, size);
                Estilo ts = criarEstilo(font, weight, size);
                setEstiloTexto(text, ts);
            }

            insereFila(chao, (Forma)pac);
            desenharTextoSVG(arqSvgEntrada,text,getEstiloTexto(text));
        }
        
    }    
    fecharSVG(arqSvgEntrada);

}
