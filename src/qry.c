#include "qry.h"
#include "formas.h"
#include "pilha.h"
#include "geo.h"
#include "disparador.h"
#include "fila.h"
#include "buscas.h"
#include "criarTxt.h"

void lerQry(FILE* arqQry, Fila filaFormas, FILE* arqTxt, Fila filaDisparadores,Fila filaCarregadores){
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
            int idDis;
            sscanf(linha, "pd %i %lf %lf",&idDis, &x, &y);
            Disparador d = encontrarDisparadorPorID(filaDisparadores, idDis);
            setPosicaoDisparador(d,x,y);
        }else if(strcmp(comando, "lc") == 0){
            //Coloca no carregador c as primeiras n formas que estão no chão
            int n;
            int idCar; //id do carregador
            sscanf(linha, "lc %i %i", &idCar, &n);
            Pilha p = encontrarPilhaPorID(filaCarregadores, idCar);
            carregarPilhaPelaFila(p, filaFormas, n);
            escreverConteudoPilha(arqTxt, p);
        }else if(strcmp(comando, "atch") == 0){
            //encaixa no disparador d os carregadores cesq(na esquerda) e cdir(na direita)
            int idDis, idCesq, idCDir;
            sscanf(linha,"atch %i %i %i",&idDis,&idCesq,&idCDir);
            Disparador d = encontrarDisparadorPorID(filaDisparadores,idDis);
            setCarregadorDisparador(d, idCesq, idCDir);
        }else if(strcmp(comando, "shft") == 0){
            //pressiona o botão esquerdo(e) ou o botão direito(d) do disparador d n vezes
            char lado;
            int n, idDis;
            sscanf(linha, "shft %i %c %i", &idDis,&lado, &n);
            Disparador d = encontrarDisparadorPorID(filaDisparadores, idDis);
            if(d != NULL){
                int idEsq = getIDPilhaEsquerda(d);
                int idDir = getIDPilhaDireita(d);

                Pilha pEsq = encontrarPilhaPorID(filaCarregadores, idEsq);
                Pilha pDir = encontrarPilhaPorID(filaCarregadores, idDir);

                pressionaBotao(d,lado,n,pEsq,pDir);
                comandoShft(arqTxt, idDis, filaDisparadores, filaCarregadores);
            }
        }else if(strcmp(comando, "dsp") == 0){
            //posiciona a forma que está em posição de disparo a um deslocamento de dx, dy em relação à posição do disparador
            double dx, dy;
            int idDis;
            char letra;
            sscanf(linha, "dsp %i %lf %lf %c", &idDis,&dx,&dy,&letra);
            Disparador d = encontrarDisparadorPorID(filaDisparadores, idDis);
            Forma f = getConteudoCentro(d);
            posicionaForma(f,d,dx,dy);
            comandoDsp(arqTxt,filaDisparadores, idDis,dx,dy);

        }else if(strcmp(comando, "rjd") == 0){
            //rajada de disparos até as formas do carregador se esgotarem
            char car;
            int idDis, idEsq, idDir;
            double dx, dy, ix, iy;
            sscanf(linha, "rjd %i %c %lf %lf %lf %lf", &idDis,&car,&dx,&dy,&ix,&iy);

            Disparador d = encontrarDisparadorPorID(filaDisparadores, idDis);
            idEsq = getIDPilhaEsquerda(d);
            idDir = getIDPilhaDireita(d);

            Pilha pEsq = encontrarPilhaPorID(filaCarregadores, idEsq);
            Pilha pDir = encontrarPilhaPorID(filaCarregadores, idDir);

            if(pEsq != NULL && pDir != NULL){
                Pilha pilhaRajada; 
                if (car == 'e') {
                    pilhaRajada = pEsq;
                } else {
                    pilhaRajada = pDir;
                }
                int i = 0;
                    
                while (getTamanhoPilha(pilhaRajada) > 0 || getConteudoCentro(d) != NULL) {
                    if (getConteudoCentro(d) == NULL) {
                        if (getTamanhoPilha(pilhaRajada) == 0) break; //Acabou tudo
                        pressionaBotao(d, car, 1, pEsq, pDir);
                    }
                
                    Forma f = getConteudoCentro(d);
                    
                    comandoDsp(arqTxt,filaDisparadores,idDis,dx+(i * ix),dy+(i * iy));
                    posicionaForma(f, d, dx + (i * ix), dy + (i * iy));
                    char ladoOposto;
                    if(car == 'e'){
                        ladoOposto = 'd';
                    }else {
                        ladoOposto = 'e';
                    }
                    pressionaBotao(d, ladoOposto, -1, pEsq, pDir); 
                    i++;
                }
            }

        }else if(strcmp(comando, "calc") == 0){
            //processa as figuras da arena conforme descrito anteriormente em um novo arqSVg
            
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