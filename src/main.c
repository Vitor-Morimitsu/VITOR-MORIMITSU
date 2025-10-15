#include "chao.h"
#include "circulo.h"
#include "retangulo.h"
#include "disparador.h"
#include "fila.h"
#include "formas.h"
#include "geo.h"
#include "linha.h"
#include "pilha.h"
#include "printSvgGeo.h"
#include "texto.h"
#include <string.h>

int main(int argc, char* argv[])
{
    //inicializa o chão
    Fila chao = criarChao();

    //inicializa as filas
    Fila listaFormas = criarFila();
    Fila listaDisparadores = criarFila();
    Fila listaPilhas = criarFila();
    
    //ler os aquivos passados
    char* nomeArqGeo = NULL;
    char* nomeArqQry = NULL;
    FILE* arqSvg = fopen("arqSVG.svg", "w");
    if(arqSvg == NULL){
        printf("Erro ao gerar arquivo .svg.");
        return 1;
    }
    
    if(argc < 3){
        printf("Número de parâmetros insuficiente.");
        return 1;
    }else{
        for(int i = 1; i < argc; i++){
            if(strcmp(argv[i], "-f") == 0){ //entrada do geo
                if(i + 1 < argc){
                    nomeArqGeo = argv[i + 1];
                    i++;
                }
            }else if(strcmp(argv[i], "-o") == 0){ //saída svg
                if(i + 1 < argc){
                    nomeArqQry = argv[i + 1];
                    i++;
                }
            }

        }
    }
    if(nomeArqGeo == NULL){
        printf("Erro ao abrir o geo.");
        return 1;
    }else{
        lerGeo(nomeArqGeo, arqSvg,chao);//gera formas e printa elas no Svg
    }
    fclose(arqSvg);
}