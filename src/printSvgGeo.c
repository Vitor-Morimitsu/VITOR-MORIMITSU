/**
 * @file printSvgGeo.c
 * @brief Implementação das funções de geração de arquivos SVG
 */

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
    if(forma == NULL){
        fprintf(stderr, "ERRO: Forma NULL ao desenhar círculo SVG\n");
        return;
    }    

    Circulo* c = (Circulo*)forma;
    fprintf(arqSvg, "\t<circle id=\"%i\" cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"%s\" fill=\"%s\" />\n",getIDCirculo(c), getCoordXCirculo(c),getCoordYCirculo(c),getRaioCirculo(c), getCorBCirculo(c), getCorPCirculo(c));
}

void desenharRetanguloSVG(FILE* arqSvg, Forma forma){
    if(forma == NULL || arqSvg == NULL){
        fprintf(stderr, "ERRO: Forma ou arquivo NULL ao desenhar retângulo SVG\n");
        return;
    }

    Retangulo* r = (Retangulo*)forma;
    fprintf(arqSvg, "\t<rect id=\"%d\" x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" fill=\"%s\" opacity=\"0.5\" />\n", 
        getIDRetangulo(r), 
        getCoordXRetangulo(r),
        getCoordYRetangulo(r), 
        getWRetangulo(r), 
        getHRetangulo(r), 
        getCorBRetangulo(r), 
        getCorPRetangulo(r));
}
void desenharLinhaSVG(FILE* arqSvg, Forma forma){
    Linha* l = (Linha*)forma;

     fprintf(arqSvg, "<line id=\"%d\" x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\" stroke-width=\"2\" />\n", getIDLinha(l), getX1Linha(l), getY1Linha(l), getX2Linha(l), getY2Linha(l), getCorLinha(l));
}

void desenharTextoSVG(FILE* arqSvg, Forma forma){
    Texto* t = (Texto*)forma;

    fprintf(arqSvg, "\t<text id=\"%d\" x=\"%f\" y=\"%f\" fill=\"%s\" text-anchor=\"%c\">%s</text>\n",getIDTexto(t),getCoordXTexto(t),getCoordYTexto(t), getCorPTexto(t),getATexto(t), getTxtoTexto(t)); 
}


void fecharSVG(FILE* arqSvg) {
    fprintf(arqSvg, "</svg>\n");
}

void gerarSvgSaida(Fila filaFormas, FILE* arqSvgSaida){
    if(filaFormas == NULL || arqSvgSaida == NULL){
        fprintf(stderr, "ERRO: Fila ou arquivo NULL ao gerar SVG de saída\n");
        exit(1);
    }
    abrirSvg(arqSvgSaida);
    
    No_t atual = getPrimeiroNoFila(filaFormas);
    if(atual == NULL){
        fecharSVG(arqSvgSaida);
        return;
    }
    
    while(atual != NULL){
        char tipoAtual = getTipoDoNoFila(atual);
        void* conteudo = getConteudoDoNoFila(atual);
        if(conteudo == NULL){
            atual = getProximoNoFila(atual);
            continue;
        }
        Forma forma = (Forma)conteudo;
        void* figura = getFiguraForma(forma);
        
        if(figura == NULL){
            fprintf(stderr, "AVISO: Figura interna NULL, pulando forma\n");
            atual = getProximoNoFila(atual);
            continue;
        }
        
        if(tipoAtual == 'c'){
            Circulo* circ = (Circulo*)figura;
            desenharCirculoSVG(arqSvgSaida,circ);
        }else if(tipoAtual == 'r'){
            Retangulo* ret = (Retangulo*)figura;
            desenharRetanguloSVG(arqSvgSaida,ret);
        }else if(tipoAtual == 'l'){
            Linha* lin = (Linha*)figura;
            desenharLinhaSVG(arqSvgSaida,lin);
        }else if(tipoAtual == 't'){
            Texto* tex = (Texto*)figura;
            desenharTextoSVG(arqSvgSaida,tex);
        }
        atual = getProximoNoFila(atual);
    }
    
    fecharSVG(arqSvgSaida);

    // No_t atual = getPrimeiroNoFila(filaFormas);
    // if(atual == NULL){
    //     printf("chao vazia\n");
    //     fecharSVG(arqSvgSaida);
    //     return;
    // }

    // printf("dentro do svg de saída\n");

    // while(atual != NULL){
    //     Forma formaAtual = (Forma)getConteudoDoNoFila(atual);
    //     if(formaAtual == NULL){
    //         printf("Erro ao gerar a formaAtual no arquivo printSvgGeo\n");
    //         atual = getProximoNoFila(atual);
    //         continue;
    //     }

    //     char tipoForma = getTipoForma(formaAtual);
    //     void* figura = getFiguraForma(formaAtual);

    //     if(figura == NULL){
    //         printf("Erro ao acessar a figura void*\n");
    //         atual = getProximoNoFila(atual);
    //         continue;
    //     }

    //     if(tipoForma == 'c'){
    //         //círculo 
    //         desenharCirculoSVG(arqSvgSaida,(Circulo*)figura);          
    //         printf("Printar o círculo no arquivo de saída svg saida\n");

    //     }else if(tipoForma == 'r'){
    //         //retângulo
    //         desenharRetanguloSVG(arqSvgSaida,(Retangulo*)figura);    
    //         printf("printar retangulo no arquivo svg saida\n");      

    //     }else if(tipoForma == 'l'){
    //         //linha
    //         desenharLinhaSVG(arqSvgSaida,(Linha*)figura);
    //         printf("printar linha no arquivo svg saida\n");
            
    //     }else if(tipoForma == 't'){
    //         //texto
    //         desenharTextoSVG(arqSvgSaida, (Texto*)figura);
    //         printf("printar texto no arquivo svg saida\n");
            
    //     }
    //     atual = getProximoNoFila(atual);
    // }
}