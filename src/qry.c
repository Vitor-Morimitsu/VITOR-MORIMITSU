#include "qry.h"

void qryAtch(Fila disparadores, Fila carregadores,int idDisparador, int idEsquerdo, int idDireito){
    Disparador d = encontrarDisparadorPorID(disparadores,idDisparador);
    if(d == NULL){
        printf("Disparador não encontrado no comando atch no qry.\n");
        return;
    }

    Pilha CE = encontrarPilhaPorID(carregadores,idEsquerdo);
    if(CE == NULL){
        printf("Carregador esquerdo não encontrado no comando atch no qry.\n");
        CE = criarPilha(idEsquerdo);
        insereFila(carregadores,(void*)CE,'p');
        printf("Carregador esquerdo com o id %i criado \n", idEsquerdo);
        
    }

    Pilha CD = encontrarPilhaPorID(carregadores,idDireito);
    if(CD == NULL){
        printf("Carregador direito não encontrado no comando atch no qry.\n"); 
        CD = criarPilha(idDireito);
        insereFila(carregadores, (void*)CD, 'p');
        printf("Carregador direitor com o id %i criado \n", idDireito);
        
    }

    //certeza que existem as coisas
    setCarregadorDisparador(d,idEsquerdo,idDireito);

    printf("Carregado direito %d\n", getIDPilhaDireita(d));//sucesso

}

void qryShft(Fila disparadores, Fila carregadores, int idDis, char lado, int n){
    Disparador d = encontrarDisparadorPorID(disparadores, idDis);
    if(d == NULL){
        printf("erro ao localizar o disparador no comando shft no qry.\n");
        return;
    }
    int idCe = getIDPilhaEsquerda(d);
    int idCd = getIDPilhaDireita(d);

    Pilha CE = encontrarPilhaPorID(carregadores,idCe);
    if(CE == NULL){
        printf("Carregador esquerdo não encontrado no comando shft\n");
        return;
    }
    Pilha CD = encontrarPilhaPorID(carregadores, idCd);     
    if(CD == NULL){
        printf("Carregador direito não encotrado no comando shft\n");
        return;
    }    

    
    if(lado == 'e'){
    
        for(int i = 0;i<n;i++){
            void* centro = getConteudoCentro(d); 
            if(centro == NULL){
                void* conteudo = removerPilha(CE);    
                if(conteudo == NULL){
                    printf("carregador esquerdo vazio no comando shft\n");
                    break;
                }
                setConteudoCentro(d,conteudo);

            }else{//tem coisa no centro
                void* conteudo = removerPilha(CE);
                if(conteudo == NULL){
                    printf("carregador esquerdo vazio no comando shft\n");
                    break;
                }
                inserirPilha(CD, centro);
                setConteudoCentro(d,conteudo);          
            }         
        }


    }else if(lado == 'd'){
        for(int i = 0;i<n;i++){
            void* centro = getConteudoCentro(d); 
            if(centro == NULL){//não tem nada no centro
                void* conteudo = removerPilha(CE);  
                if(conteudo == NULL){
                    printf("carregador direito vazio no comando shft\n");
                    break;
                }  
                setConteudoCentro(d,conteudo);

            }else{//tem coisa no centro
                void* conteudo = removerPilha(CD);
                if(conteudo == NULL){
                    printf("carregador direito vazio no comando shft\n");
                    break;
                }
                inserirPilha(CE, centro);
                setConteudoCentro(d,conteudo);            
            
            }         
        }
        
    }else{
        printf("Lado inválido no comando shft\n");
        return;
    }
}

void qryDsp(Fila disparadores,Fila arena, int idDis, double dx, double dy, char letra, int iteracao){
    Disparador d = encontrarDisparadorPorID(disparadores, idDis);
    if(d == NULL){
        printf("Erro ao localizar o disparador na função qryDsp\n");
        return;
    }

    double xDisparador = getXDisparador(d);
    double yDisparador = getYDisparador(d);

    int comando = 1;

    if(letra == 'v'){//anotar as dimensões do disparo

    }else if(letra == 'i'){//aumentar conforme iteração
        comando = iteracao;
    }

    void* conteudo = getConteudoCentro(d);
    if(conteudo == NULL){
        printf("nada a ser disparado\n");
    }else{
        Forma forma = conteudo;
        void* figura = getFiguraForma(forma);
        char tipoConteudo = getTipoForma(forma);
        if(tipoConteudo == 'c'){
            Circulo* circ = (Circulo*)figura;
            setXCirculo(circ, xDisparador + (comando * dx));
            setYCirculo(circ, yDisparador + (comando * dy));
            insereFila(arena,forma,'c');

        }else if(tipoConteudo == 'r'){
            Retangulo* ret = (Retangulo*)figura;
            setCoordXRetangulo(ret,xDisparador + (comando * dx));
            setCoordYRetangulo(ret,yDisparador + (comando * dy));
            insereFila(arena,forma,'r');

        }else if(tipoConteudo == 'l'){
            Linha* lin = (Linha*)figura;
            double vetorX = getX2Linha(lin) - getX1Linha(lin);
            double vetorY = getY2Linha(lin) - getY1Linha(lin);
            
            setX1Linha(lin, xDisparador + (comando * dx));
            setY1Linha(lin, yDisparador + (comando * dy));


            setX2Linha(lin, (xDisparador + (comando * dx)) + vetorX);
            setY2Linha(lin, (yDisparador + (comando * dy)) + vetorY);

            insereFila(arena,forma,'l');

        }else if(tipoConteudo == 't'){
            Texto* t = (Texto*)figura;
            setXTexto(t, xDisparador + (comando * dx));
            setYTexto(t, yDisparador + (comando * dy));
            insereFila(arena,forma,'t');
        }
        
    }

    setConteudoCentro(d, NULL);
}

void qryRjd(Fila disparadores, Fila carregadores, Fila arena,int idDis, char lado, double dx, double dy,double ix, double iy){ 
    Disparador d = encontrarDisparadorPorID(disparadores,idDis);
    if(d == NULL){
        printf("Erro ao localizar disparador no qryRjd\n");
        return;
    }

    int idE = getIDPilhaEsquerda(d);
    int idD = getIDPilhaDireita(d);

    Pilha esq = encontrarPilhaPorID(carregadores,idE);
    if(esq == NULL){
        printf("Pilha esquerda em qryRjd é nula\n");
        return;
    }

    Pilha dir = encontrarPilhaPorID(carregadores,idD);
    if(dir == NULL){
        printf("Pilha direita em qryRjd é nula\n");
        return;
    }

    int tamanhoEsq = getTamanhoPilha(esq);
    int tamanhoDir = getTamanhoPilha(dir);

    if(lado == 'e'){
        //Carregador esquerdo

        //se estiver vazio, usar o da direita
        int tamanho = (tamanhoEsq > 0) ? tamanhoEsq : tamanhoDir;

        char ladoReal = (tamanhoEsq > 0) ? 'd' : 'e';

        for(int i = 0; i< tamanhoEsq;i++){
            int iteracao = i;
            qryShft(disparadores,carregadores,idDis,lado,1);
            qryDsp(disparadores,arena, idDis, dx+iteracao*ix, dy+iteracao*iy,'i',iteracao);
        }
        
    }else if(lado == 'd'){
        //carregador direito

        //se estiver vazia ,usar a da esquerda
        int tamanho = (tamanhoDir > 0) ? tamanhoDir : tamanhoEsq;

        char ladoReal = (tamanhoDir > 0) ? 'd' : 'e';

        for(int i = 0;i<tamanhoDir;i++){
            int iteracao = i;
            qryShft(disparadores,carregadores,idDis,ladoReal,1);
            qryDsp(disparadores,arena, idDis, dx+iteracao*ix, dy+iteracao*iy,'i',iteracao);

        }

    }
 
}

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

            qryAtch(filaDisparadores,filaCarregadores,idDis,idCesq,idCDir);

            printf("passou no comando atch\n");//ok!
            
        }else if(strcmp(comando, "shft") == 0){
            printf("comando shft\n");
            //pressiona o botão esquerdo(e) ou o botão direito(d) do disparador d n vezes
            char lado;
            int n, idDis;
            sscanf(linha, "shft %i %c %i", &idDis,&lado, &n);
            printf("comando shft = idDis:%i  lado:%c  qunatidade de vezes:%i\n",idDis,lado,n);

            qryShft(filaDisparadores,filaCarregadores,idDis, lado,n);
            //printar no txt
            comandoShft(arqTxt,idDis, filaDisparadores);
            printf("passou no comando shft \n");
            
        }else if(strcmp(comando, "dsp") == 0){
            printf("comando disp\n");
            //posiciona a forma que está em posição de disparo a um deslocamento de dx, dy em relação à posição do disparador
            double dx, dy;
            int iteracao = 1;
            int idDis;
            char letra;
            sscanf(linha, "dsp %i %lf %lf %c", &idDis,&dx,&dy,&letra);
            printf("comando dsp = idDIs:%i  deslocX:%lf deslocY:%lf letra:%c\n",idDis,dx,dy,letra);

            qryDsp(filaDisparadores,chao,idDis,dx,dy,letra,iteracao);
            comandoDsp(arqTxt,filaDisparadores, idDis,dx,dy);
            printf("passando no comando dsp\n");
            
        }else if(strcmp(comando, "rjd") == 0){
            printf("comando rjd\n");
            //rajada de disparos até as formas do carregador se esgotarem
            char car;
            int idDis, idEsq, idDir;
            double dx, dy, ix, iy;
            sscanf(linha, "rjd %i %c %lf %lf %lf %lf", &idDis,&car,&dx,&dy,&ix,&iy);
            printf("comando rjd = idDis:%i  letra do carregador:%c dx:%lf  dy:%lf  ix:%lf iy:%lf\n",idDis,car,dx,dy,ix,iy);
            
            qryRjd(filaDisparadores,filaCarregadores,chao,idDis,car,dx,dy,ix,iy);
            
            printf("passou comando rjd\n");
            
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