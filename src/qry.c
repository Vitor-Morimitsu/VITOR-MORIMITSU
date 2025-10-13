#include "qry.h"
#include "formas.h"
#include "geo.h"
#include "disparador.h"

void abrirQry(FILE* arqQry){
    fopen(arqQry, "w");
}

void abrirTxt(FILE* arqTxt){
    fopen(arqTxt, "w");
}

void lerQry(FILE* arqQry, Fila f, FILE* arqTxt){
    if(arqQry == NULL){
        printf("Erro ao ler o arquivo .qry");
        exit(1);
    }
    
    char linha[500];
    char comando[500];

    while(fgets(linha, sizeof(linha), arqQry) != NULL){
        if(linha[0] == '\n' || linha[0] == '\r'){
            continue;
        }

        abrirTxt(arqTxt);

        if(arqTxt == NULL){
            printf("Erro ao acessar o arquivo .txt");
            exit(1);
        }else{
            fprintf(arqTxt, "%s", linha);
        }

        sscanf(linha, "%s", comando);

        if(strcmp(comando, "pd") == 0){
            //posiciona o disparador l na coordenada (x,y)
            
        }
    }
}

void fecharQry(FILE* arqQry){
    if(arqQry == NULL){
        printf("Erro ao acessar o arquvio .qry.");
        exit(1);
    }

    fclose(arqQry);
}

void fecharTxt(FILE* arqTxt){
    if(arqTxt == NULL){
        printf("Erro ao acessar o arquivo .txt");
        exit(1);
    }

    fclose(arqTxt);
}