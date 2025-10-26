#include "qry.h"

void lerQry(FILE* arqQry, FILE* arqTxt, Fila filaDisparadores,Fila filaCarregadores,Fila chao){
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
            printf("Erro ao acessar o arquivo .txt ");
            exit(1);
        }

        sscanf(linha, "%s", comando);
        fprintf(arqTxt, "%s\n" ,linha);

        if(strcmp(comando, "pd") == 0){
            printf("comando pd\n");
            //posiciona o disparador l na coordenada (x,y)
            double x,y;
            int idDis;
            sscanf(linha, "pd %i %lf %lf",&idDis, &x, &y);
            printf("Comando pd= idDis:%i coordX:%lf  coordY:%lf\n",idDis,x,y);
            Disparador d = criarDisparador(idDis,x,y,NULL,NULL);
            if(d == NULL){
                printf("erro ao criar o disparador no comando pd\n");
                continue;
            }
            insereFilaDisparadores(filaDisparadores, d);
            setPosicaoDisparador(d,x,y);
            printf("passou no comando pd\n");
            
        }else if(strcmp(comando, "lc") == 0){
            printf("comando lc\n");
            //Coloca no carregador c as primeiras n formas que estão no chão
            int n;
            int idCar; //id do carregador
            sscanf(linha, "lc %i %i", &idCar, &n);
            printf("comando lc = idCar:%i   quantidade de formas a serem carregadas:%i\n ", idCar,n);

            //ver se existe uma pilha com a mesma id
            Pilha p = encontrarPilhaPorID(filaCarregadores, idCar);
            if(p != NULL){
                printf("Já existe uma pilha com essa id\n");
                continue;
            }

            Pilha novaPilha = criarPilha(idCar);
            if(novaPilha == NULL){
                printf("Erro ao acessar a pilha no comando lc\n");
                continue;
            }            
            carregarPilhaPelaFila(novaPilha, chao, n);
            insereFila(filaCarregadores, (void*)novaPilha, 'p');
            escreverConteudoPilha(arqTxt, novaPilha);
            printf("passou no comando lc\n");
            
        }else if(strcmp(comando, "atch") == 0){
            printf("comando atch\n");
            //encaixa no disparador d os carregadores cesq(na esquerda) e cdir(na direita)
            int idDis, idCesq, idCDir;
            sscanf(linha,"atch %i %i %i",&idDis,&idCesq,&idCDir);
            printf("comando atch = idDIs:%i  idEsq:%i  idDir:%i\n", idDis,idCesq,idCDir);

            Disparador d = encontrarDisparadorPorID(filaDisparadores,idDis);
            if(d == NULL){
                printf("Erro ao encontrar o disparador no comando atch\n");
            }
            printf("O disparador %d foi carregado com as pilha %d na esquerda e %d na direita\n",idDis,idCesq,idCDir);
            setCarregadorDisparador(d, idCesq, idCDir);
            printf("passou no comando atch\n");//ok!
            
        }else if(strcmp(comando, "shft") == 0){
            printf("comando shft\n");
            //pressiona o botão esquerdo(e) ou o botão direito(d) do disparador d n vezes
            char lado;
            int n, idDis;
            sscanf(linha, "shft %i %c %i", &idDis,&lado, &n);
            printf("comando shft = idDis:%i  lado:%c  qunatidade de vezes:%i\n",idDis,lado,n);

            Disparador d = encontrarDisparadorPorID(filaDisparadores, idDis);
            if(d != NULL){
                printf("disparador encontrado no comando shft qry\n");
                int idEsq = getIDPilhaEsquerda(d);
                int idDir = getIDPilhaDireita(d);
                
                Pilha pEsq = encontrarPilhaPorID(filaCarregadores, idEsq);
                Pilha pDir = encontrarPilhaPorID(filaCarregadores, idDir);
                
                pressionaBotao(d,lado,n,pEsq,pDir);
                comandoShft(arqTxt, idDis, filaDisparadores);
            }
            printf("teste 2 no comando shft \n");
            
        }else if(strcmp(comando, "dsp") == 0){
            printf("comando disp\n");
            //posiciona a forma que está em posição de disparo a um deslocamento de dx, dy em relação à posição do disparador
            double dx, dy;
            int idDis;
            char letra;
            sscanf(linha, "dsp %i %lf %lf %c", &idDis,&dx,&dy,&letra);
            printf("comando dsp = idDIs:%i  deslocX:%lf deslocY:%lf letra:%c\n",idDis,dx,dy,letra);
            Disparador d = encontrarDisparadorPorID(filaDisparadores, idDis);
            if(d == NULL){
                printf("Disparador nao encontrado no comando disp qry\n");
            }
            Forma f = getConteudoCentro(d);
            posicionaForma(f,d,dx,dy);
            comandoDsp(arqTxt,filaDisparadores, idDis,dx,dy);
            printf("teste 3 no comando dsp\n");
            
        }else if(strcmp(comando, "rjd") == 0){
            printf("comando rjd\n");
            //rajada de disparos até as formas do carregador se esgotarem
            char car;
            int idDis, idEsq, idDir;
            double dx, dy, ix, iy;
            sscanf(linha, "rjd %i %c %lf %lf %lf %lf", &idDis,&car,&dx,&dy,&ix,&iy);
            printf("comando rjd = idDis:%i  letra do carregador:%c dx:%lf  dy:%lf  ix:%lf iy:%lf\n",idDis,car,dx,dy,ix,iy);
            
            Disparador d = encontrarDisparadorPorID(filaDisparadores, idDis);
            if(d == NULL){
                printf("Disparador nao encontrado no comando disp qry\n");
                continue;
            }

            printf("Id do disparador utilizado no comando rjd: %i\n", getIDDisparador(d));// tudo certo

            idEsq = getIDPilhaEsquerda(d);
            idDir = getIDPilhaDireita(d);
            printf("ID do carregador direito do comando rjd: %i ----- id do carregador esquerdo do comando rjd: %i\n",idDir, idEsq);

            Pilha esquerda = encontrarPilhaPorID(filaCarregadores,idEsq);

            No_t noDebug = getPrimeiroNoFila(filaCarregadores);
            int count = 0;
            while (noDebug != NULL) {
                void* conteudoDebug = getConteudoDoNoFila(noDebug);
                if (conteudoDebug != NULL) {
                    Pilha pilhaDebug = (Pilha)conteudoDebug;
                    // CUIDADO: Verifique se getIDPilha é seguro contra NULL se algo der errado
                    printf("  -> Item %d: Ponteiro Pilha=%p, ID=%d\n", count, (void*)pilhaDebug, getIDPilha(pilhaDebug));
                } else {
                    printf("  -> Item %d: Conteudo NULO!\n", count);
                }
                noDebug = getProximoNoFila(noDebug);
                count++;
            }
            if (count == 0) {
                    printf("  -> Fila de Carregadores está VAZIA!\n");
            }
            Pilha direita = encontrarPilhaPorID(filaCarregadores,idDir);

            if(esquerda == NULL){
                printf("Pilha esquerda do disparador é nula\n");
            }else{
                printf("Pilha esuqerda do disparador encontrada\n");
            }

            if(direita == NULL){
                printf("Pilha direita do disparador é nula\n");
            }else{
                printf("Pilha direita do disparador encontrada\n");
            }
            
            Forma centroAntes = getConteudoCentro(d);
            if(centroAntes == NULL){
                printf("centro está vazio\n");
            }else{
                char tipoAntes = getTipoForma(centroAntes);
                printf("tipo do conteudo do centro %c\n", tipoAntes);
            }

            pressionaBotao(d,car,1,esquerda, direita);

            Forma centroDepois = getConteudoCentro(d);
            if(centroDepois == NULL){
                printf("Centro depois está vazio.\n");
            }else{
                char tipoDepois = getTipoForma(centroDepois);
                printf("tipo do centro depois %c\n", tipoDepois);
            }

                      
            
        }else if(strcmp(comando, "calc") == 0){
            //processa as figuras da arena conforme descrito anteriormente em um novo arqSVg
            comandoCalc(arqTxt,chao);
            printf("passou no comando calc\n");
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