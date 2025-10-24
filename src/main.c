#include <stdio.h>
#include <stdlib.h>
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
#include "qry.h"

#define PATH_LEN 512
#define FILE_NAME_LEN 256

int main(int argc, char* argv[])
{
    FILE* arqGeo = NULL;
    char dirEntrada[PATH_LEN] = "";
    char dirSaida[PATH_LEN] = "";
    char nomeArquivoGeo[FILE_NAME_LEN] = "";
    char nomeArquivoQry[FILE_NAME_LEN] = "";
    char onlyQry[FILE_NAME_LEN] = "";
    int hasGeo = 0, hasSaida = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-e") == 0 && i + 1 < argc) {//Diretório base de entrada
            strcpy(dirEntrada, argv[++i]);
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {//Arquivo com a descrição 
            strcpy(dirSaida, argv[++i]);
            hasSaida = 1;
        } else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {//Diretório base de saída
            strcpy(nomeArquivoGeo, argv[++i]);
            hasGeo = 1;
        } else if (strcmp(argv[i], "-q") == 0 && i + 1 < argc) {//arquivo com consultas
            strcpy(nomeArquivoQry, argv[++i]);
            char *p = strrchr(argv[i], '/');
            strcpy(onlyQry, p ? p + 1 : argv[i]);
        } else {
            fprintf(stderr, "Parametro desconhecido ou invalido: %s\n", argv[i]);
            return EXIT_FAILURE;
        }
    }

    if (!hasGeo || !hasSaida) {
        fprintf(stderr, "Erro: parametros obrigatorios -f (geo) e -o (saida) nao fornecidos.\n");
        return EXIT_FAILURE;
    }

    char fullPathGeo[1024];
    snprintf(fullPathGeo, sizeof(fullPathGeo), "%s/%s", dirEntrada, nomeArquivoGeo);

    char fullPathQry[1024];
    if (strlen(nomeArquivoQry) > 0) {
        snprintf(fullPathQry, sizeof(fullPathQry), "%s/%s", dirEntrada, nomeArquivoQry);
    }

    char arquivoSaidaSvgGeo[1024];
    snprintf(arquivoSaidaSvgGeo, sizeof(arquivoSaidaSvgGeo), "%s/%s.svg", dirSaida, nomeArquivoGeo);

    char arquivoSaidaSvgQry[1024];
    if (strlen(nomeArquivoQry) > 0) {
        snprintf(arquivoSaidaSvgQry, sizeof(arquivoSaidaSvgQry), "%s/%s.svg", dirSaida, onlyQry);
    }

    char arquivoSaidaTxt[1024];
    if (strlen(nomeArquivoQry) > 0) {
        snprintf(arquivoSaidaTxt, sizeof(arquivoSaidaTxt), "%s/%s.txt", dirSaida, onlyQry);
    }
    
    //inicializar as filas
    Fila chao = criarFila();
    Fila filaFormas = criarFila();
    Fila filaDisparadores = criarFila();
    Fila filaPilhas = criarFila();

    //criar disparadores
    for(int i  = 0;i < 20;i++){
        Disparador
    }
    arqGeo = fopen(fullPathGeo, "r");
    if(arqGeo == NULL){
        printf("Nâo foi possível abrir o arquivo geo no main.");
        liberarTudo(filaFormas,filaDisparadores, filaPilhas,chao);
        return 1;
    }

    FILE* arqSvgEntrada = fopen(arquivoSaidaSvgGeo, "w");
    if(arqSvgEntrada == NULL){
        printf("Erro ao abrir arquivo Svg de entrada.");
        fclose(arqGeo);
        liberarTudo(filaFormas,filaDisparadores, filaPilhas,chao);
        return 1;
    }
    
    lerGeo(arqGeo,filaFormas,arqSvgEntrada);
    
    fclose(arqGeo);
    fclose(arqSvgEntrada);

    if (strlen(nomeArquivoQry) > 0) {
        FILE* arqQry = fopen(fullPathQry, "r");
        if (arqQry == NULL) {
            printf("Falha ao abrir arquivo qry no main.");
            liberarTudo(filaFormas,filaDisparadores, filaPilhas,chao);
            return 1;
        }

        FILE* arqTxt = fopen(arquivoSaidaTxt, "w");
        if(arqTxt == NULL){
            printf("Erro ao abrir txt para escrita.");
            fclose(arqQry);
            liberarTudo(filaFormas,filaDisparadores, filaPilhas,chao);
            return 1;
        }

        lerQry(arqQry,filaFormas,arqTxt,filaDisparadores,filaPilhas,chao);
        
        fclose(arqQry);
        fclose(arqTxt);
        
        //reabrir txt para leitura 
        arqTxt = fopen(arquivoSaidaTxt,"r");
        if(arqTxt == NULL){
            printf("Erro ao abrir aqruivo txt para leitura");
           
            liberarTudo(filaFormas,filaDisparadores, filaPilhas,chao);
            return 1;
        }

        //abrir svg de saida
        FILE* arqSvgSaida = fopen(arquivoSaidaSvgQry, "w"); 
        if(arqSvgSaida == NULL){
            printf("Erro ao abrir svg de saida\n");
            fclose(arqTxt);
            liberarTudo(filaFormas, chao, filaDisparadores, filaPilhas);
            return 1;
        }

        gerarSvgSaida(arqTxt, arqSvgSaida);   
        
        fclose(arqTxt);
        fclose(arqSvgSaida);
    }
    
    liberarTudo(filaFormas, chao, filaDisparadores, filaPilhas);

    return 0; 

}