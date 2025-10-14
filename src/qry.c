#include "qry.h"
#include "formas.h"
#include "pilha.c"
#include "geo.h"
#include "disparador.h"

void abrirQry(FILE* arqQry){
    fopen(arqQry, "w");
}

void abrirTxt(FILE* arqTxt){
    fopen(arqTxt, "w");
}

void lerQry(FILE* arqQry, Fila f, FILE* arqTxt, Disparador d){
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
            double x,y;
            sscanf(linha, "pd %lf %lf", &x, &y);
            setPosicaoDisparador(d,x,y);
        }else if(strcmp(comando, "lc") == 0){
            //Coloca no carregador c as primeiras n formas que estão no chão
            double n;
            int c; //id do carregador
            sscanf(linha, "lc %i %n", &c, &n);
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