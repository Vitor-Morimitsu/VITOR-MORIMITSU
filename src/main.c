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
    Fila filaDisparadores = criarFila();
    Fila filaPilhas = criarFila();

    arqGeo = fopen(fullPathGeo, "r");

    if(arqGeo == NULL){
        printf("Nâo foi possível abrir o arquivo geo no main.");
        liberarFilaComConteudo(filaDisparadores,free);
            if(filaPilhas != NULL){
                No_t noPilhaAtual = getPrimeiroNoFila(filaPilhas);
                while(noPilhaAtual != NULL){
                    void* conteudo = getConteudoDoNoFila(noPilhaAtual);
                    if(conteudo != NULL){
                    Pilha p = (Pilha)conteudo; 
                    liberarMemoriaPilha(p,NULL);
                  }
                 noPilhaAtual = getProximoNoFila(noPilhaAtual);
                }
                liberarFilaComConteudo(filaPilhas,liberarForma);
                liberarFilaComConteudo(filaDisparadores, free);
            }
            liberarFilaComConteudo(chao,liberarForma);
        return 1;
    }

    FILE* arqSvgEntrada = fopen(arquivoSaidaSvgGeo, "w");
    if(arqSvgEntrada == NULL){
        printf("Erro ao abrir arquivo Svg de entrada.");
        liberarFilaComConteudo(filaDisparadores,free);
            if(filaPilhas != NULL){
                No_t noPilhaAtual = getPrimeiroNoFila(filaPilhas);
                while(noPilhaAtual != NULL){
                    void* conteudo = getConteudoDoNoFila(noPilhaAtual);
                    if(conteudo != NULL){
                    Pilha p = (Pilha)conteudo; 
                    liberarMemoriaPilha(p,NULL);
                  }
                 noPilhaAtual = getProximoNoFila(noPilhaAtual);
                }
                liberarFilaComConteudo(filaPilhas,NULL);
                liberarFilaComConteudo(filaDisparadores, NULL);
            }
            liberarFilaComConteudo(chao,NULL);
        fclose(arqGeo);
        return 1;
    }
    
    lerGeo(arqGeo,chao,arqSvgEntrada);
    
    fclose(arqGeo);
    fclose(arqSvgEntrada);

    if (strlen(nomeArquivoQry) > 0) {
        FILE* arqQry = fopen(fullPathQry, "r");
        if (arqQry == NULL) {
            printf("Falha ao abrir arquivo qry no main.");
            liberarFilaComConteudo(filaDisparadores,free);
            if(filaPilhas != NULL){
                No_t noPilhaAtual = getPrimeiroNoFila(filaPilhas);
                while(noPilhaAtual != NULL){
                    void* conteudo = getConteudoDoNoFila(noPilhaAtual);
                    if(conteudo != NULL){
                    Pilha p = (Pilha)conteudo; 
                    liberarMemoriaPilha(p,NULL);
                  }
                 noPilhaAtual = getProximoNoFila(noPilhaAtual);
                }
                liberarFilaComConteudo(filaPilhas,NULL);
                liberarFilaComConteudo(filaDisparadores, NULL);
            }
            liberarFilaComConteudo(chao,NULL);
            return 1;
        }

        FILE* arqTxt = fopen(arquivoSaidaTxt, "w");
        if(arqTxt == NULL){
            printf("Erro ao abrir txt para escrita.");
            liberarFilaComConteudo(filaDisparadores,free);
            if(filaPilhas != NULL){
                No_t noPilhaAtual = getPrimeiroNoFila(filaPilhas);
                while(noPilhaAtual != NULL){
                    void* conteudo = getConteudoDoNoFila(noPilhaAtual);
                    if(conteudo != NULL){
                    Pilha p = (Pilha)conteudo; 
                    liberarMemoriaPilha(p,NULL);
                  }
                 noPilhaAtual = getProximoNoFila(noPilhaAtual);
                }
                liberarFilaComConteudo(filaPilhas,NULL);
                liberarFilaComConteudo(filaDisparadores, NULL);
            }
            liberarFilaComConteudo(chao,NULL);
            fclose(arqQry);
            return 1;
        }
        
        lerQry(arqQry,arqTxt,filaDisparadores,filaPilhas,chao);
        printf("Passou a leitura do qry no main\n");
        fecharQry(arqQry);
        
        fclose(arqTxt);

        //abrir svg de saida
        FILE* arqSvgSaida = fopen(arquivoSaidaSvgQry, "w"); 
        if(arqSvgSaida == NULL){
            printf("Erro ao abrir svg de saida\n");
            liberarFilaComConteudo(filaDisparadores,free);
            if(filaPilhas != NULL){
                No_t noPilhaAtual = getPrimeiroNoFila(filaPilhas);
                while(noPilhaAtual != NULL){
                    void* conteudo = getConteudoDoNoFila(noPilhaAtual);
                    if(conteudo != NULL){
                    Pilha p = (Pilha)conteudo; 
                    liberarMemoriaPilha(p,NULL);
                  }
                 noPilhaAtual = getProximoNoFila(noPilhaAtual);
                }
                liberarFilaComConteudo(filaPilhas,NULL);
                liberarFilaComConteudo(filaDisparadores, NULL);
            }
            liberarFilaComConteudo(chao,NULL);
            return 1;
        }
        printf("Arquivo svg de saída criado no main\n");

        gerarSvgSaida(chao, arqSvgSaida);   
        
        printf("Passou arquivo Svg saída no main\n");
        
        // liberarFilaComConteudo(filaDisparadores,free);
        if(filaPilhas != NULL){
            No_t noPilhaAtual = getPrimeiroNoFila(filaPilhas);
            while(noPilhaAtual != NULL){
                void* conteudo = getConteudoDoNoFila(noPilhaAtual);
                if(conteudo != NULL){
                    Pilha p = (Pilha)conteudo; 
                    liberarMemoriaPilha(p,NULL);
                }
                noPilhaAtual = getProximoNoFila(noPilhaAtual);
            }
            liberarFilaComConteudo(filaPilhas,NULL);
            liberarFilaComConteudo(filaDisparadores, NULL);
            liberarFilaComConteudo(chao,NULL);
        }


        fclose(arqSvgSaida);
    }
    return 0; 

}