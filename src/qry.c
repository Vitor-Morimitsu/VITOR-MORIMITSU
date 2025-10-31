#include "qry.h"


void qryAtch(Fila disparadores, Fila carregadores,int idDisparador, int idEsquerdo, int idDireito){
    Disparador d = encontrarDisparadorPorId(disparadores,idDisparador);
    if(d == NULL){
        fprintf(stderr, "AVISO [atch]: Disparador ID %d não encontrado\n", idDisparador);
        return;
    }

    // Busca ou cria carregador esquerdo
    Pilha CE = encontrarDisparadorPorId(carregadores,idEsquerdo);
    if(CE == NULL){
        CE = criarPilha(idEsquerdo);
        insereFila(carregadores,CE);
    }

    // Busca ou cria carregador direito
    Pilha CD = encontrarDisparadorPorId(carregadores,idDireito);
    if(CD == NULL){
        CD = criarPilha(idDireito);
        insereFila(carregadores, CD);
    }

    // Associa os carregadores ao disparador
    atch(d,CE,'e');
    atch(d,CD,'d');
}

void qryShft(Fila disparadores, Fila carregadores, int idDis, char lado, int n){
    Disparador d = encontrarDisparadorPorId(disparadores, idDis);
    if(d == NULL){
        fprintf(stderr, "ERRO [shft]: Disparador ID %d não encontrado\n", idDis);
        return;
    }
    int idCe = getIDPilhaEsquerda(d);
    int idCd = getIDPilhaDireita(d);

    Pilha CE = encontrarDisparadorPorId(carregadores,idCe);
    if(CE == NULL){
        fprintf(stderr, "ERRO [shft]: Carregador esquerdo ID %d não encontrado\n", idCe);
        return;
    }
    Pilha CD = encontrarDisparadorPorId(carregadores, idCd);     
    if(CD == NULL){
        fprintf(stderr, "ERRO [shft]: Carregador direito ID %d não encontrado\n", idCd);
        return;
    }    

    int confirmacao = -1;
    if(lado == 'e'){
        // Pressiona botão esquerdo: move formas do carregador esquerdo para o centro
        for(int i = 0;i<n;i++){
            void* centro = getConteudoCentro(d); 
            if(centro == NULL){
                //centro vazio
                Forma f = getFormaTopoPilha(CE);
                removerPilha(CE);    
                int confirmacao = shft(d,'e');

            }else{
                //existe uma forma no centro
                Forma f = getFormaTopoPilha(CE);
                removerPilha(CE);                
                inserirPilha(CD, centro);
                int confirmacao = shft(d, 'e');          
            }         
        }

    }else if(lado == 'd'){
        // Pressiona botão direito: move formas do carregador direito para o centro
        for(int i = 0;i<n;i++){
            void* centro = getConteudoCentro(d); 
            if(centro == NULL){
                //centro vazio
                Forma f = getFormaTopoPilha(CD);  
                removerPilha(CD);
                confirmacao = shft(d, 'd');
            }else{
                //existe uma forma no centro
                Forma f = getFormaTopoPilha(CD);
                removerPilha(CD);
                inserirPilha(CE, centro);
                confirmacao = shft(d, 'd');          
            }         
        }
        
    }else{
        fprintf(stderr, "ERRO [shft]: Lado inválido '%c'. Use 'e' ou 'd'\n", lado);
        return;
    }
    if(confirmacao == 0){
        printf("Comando shft realizado com sucesso\n");
        return;
    }else{
        printf("Erro ao realizar o comando shft\n");
        return;
    }
}

void qryDsp(Fila disparadores,Fila arena, int idDis, double dx, double dy, char letra, int iteracao){
    Disparador d = encontrarDisparadorPorId(disparadores, idDis);
    if(d == NULL){
        fprintf(stderr, "ERRO [dsp]: Disparador ID %d não encontrado\n", idDis);
        return;
    }

    double xDisparador = getXDisparador(d);
    double yDisparador = getYDisparador(d);

    int comando = 1;

    if(letra == 'v'){
        // Modo vetor: usa deslocamento direto ----------------------------------------------------------------------falta terminar
    }else if(letra == 'i'){
        // Modo iteração: multiplica deslocamento pela iteração
        comando = iteracao;
    }

    void* conteudo = getConteudoCentro(d);
    if(conteudo == NULL){
        return;
    }else{
        Forma forma = conteudo;
        char tipoConteudo = getTipoForma(forma);
        void* figura = getFiguraForma(forma);
        
        if(figura == NULL){
            fprintf(stderr, "ERRO [dsp]: Figura interna é NULL\n");
            return;
        }
        
        if(tipoConteudo == 'c'){
            Circulo* circ = (Circulo*)figura;
            setXCirculo(circ, xDisparador +  dx);
            setYCirculo(circ, yDisparador + dy);
            insereFila(arena,forma);

        }else if(tipoConteudo == 'r'){
            Retangulo* ret = (Retangulo*)figura;
            setCoordXRetangulo(ret,xDisparador + dx);
            setCoordYRetangulo(ret,yDisparador + dy);
            insereFila(arena,forma);

        }else if(tipoConteudo == 'l'){
            Linha* lin = (Linha*)figura;
            double vetorX = getX2Linha(lin) - getX1Linha(lin);
            double vetorY = getY2Linha(lin) - getY1Linha(lin);
            
            setX1Linha(lin, xDisparador + dx);
            setY1Linha(lin, yDisparador + dy);


            setX2Linha(lin, (xDisparador + dx) + vetorX);
            setY2Linha(lin, (yDisparador + dy) + vetorY);

            insereFila(arena,forma);

        }else if(tipoConteudo == 't'){
            Texto* t = (Texto*)figura;
            setXTexto(t, xDisparador + dx);
            setYTexto(t, yDisparador + dy);
            insereFila(arena,forma);
        }
        
    }

    setConteudoCentro(d, NULL);
}

void qryRjd(Fila disparadores, Fila carregadores, Fila arena,int idDis, char lado, double dx, double dy,double ix, double iy){ 
    Disparador d = encontrarDisparadorPorId(disparadores,idDis);
    if(d == NULL){
        fprintf(stderr, "ERRO [rjd]: Disparador ID %d não encontrado\n", idDis);
        return;
    }

    int idE = getIDPilhaEsquerda(d);
    int idD = getIDPilhaDireita(d);

    Pilha esq = encontrarDisparadorPorId(carregadores,idE);
    if(esq == NULL){
        fprintf(stderr, "ERRO [rjd]: Carregador esquerdo ID %d não encontrado\n", idE);
        return;
    }

    Pilha dir = encontrarDisparadorPorId(carregadores,idD);
    if(dir == NULL){
        fprintf(stderr, "ERRO [rjd]: Carregador direito ID %d não encontrado\n", idD);
        return;
    }

    int tamanhoEsq = getTamanhoPilha(esq);
    int tamanhoDir = getTamanhoPilha(dir);

    if(lado == 'e'){
        //Carregador esquerdo
        for(int i = 0; i< tamanhoEsq;i++){
            int iteracao = i;
            qryShft(disparadores,carregadores,idDis,lado,1);
            qryDsp(disparadores,arena, idDis, dx+iteracao*ix, dy+iteracao*iy,'v',0);
        }
        
    }else if(lado == 'd'){
        //carregador direito
        // Se a pilha direita está vazia, usar a esquerda
        int tamanho = (tamanhoDir > 0) ? tamanhoDir : tamanhoEsq;
        char ladoReal = (tamanhoDir > 0) ? 'd' : 'e';
        
        for(int i = 0;i<tamanho;i++){
            int iteracao = i;
            qryShft(disparadores,carregadores,idDis,ladoReal,1);
            qryDsp(disparadores,arena, idDis, dx+iteracao*ix, dy+iteracao*iy,'v',0);

        }

    }
 
}

void lerQry(FILE* arqQry, FILE* arqTxt, Fila filaDisparadores,Fila filaCarregadores,Fila chao){
    if(arqQry == NULL){
        fprintf(stderr, "ERRO: Arquivo .qry é NULL\n");
        exit(1);
    }
    char linha[500];
    char comando[500];

    while(fgets(linha, sizeof(linha), arqQry) != NULL){
        if(linha[0] == '\n' || linha[0] == '\r'){
            continue;
        }

        if(arqTxt == NULL){
            fprintf(stderr, "ERRO: Arquivo .txt é NULL\n");
            exit(1);
        }

        sscanf(linha, "%s", comando);
        fprintf(arqTxt, "%s\n" ,linha);

        if(strcmp(comando, "pd") == 0){
            // Comando pd: posiciona disparador
            double x,y;
            int idDis;
            sscanf(linha, "pd %i %lf %lf",&idDis, &x, &y);
            Disparador d = criarDisparador(idDis,x,y);
            if(d == NULL){
                fprintf(stderr, "ERRO [pd]: Falha ao criar disparador ID %d\n", idDis);
                continue;
            }
            insereFilaDisparadores(filaDisparadores, d);
            setPosicaoDisparador(d,x,y);
            
        }else if(strcmp(comando, "lc") == 0){
            // Comando lc: carrega formas no carregador
            int n;
            int idCar;
            sscanf(linha, "lc %i %i", &idCar, &n);

            Pilha novaPilha = criarPilha(idCar);
            if(novaPilha == NULL){
                fprintf(stderr, "ERRO [lc]: Falha ao criar carregador ID %d\n", idCar);
                continue;
            }            
    
            
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
            // Disparador d = encontrarDisparadorPorID(filaDisparadores, idDis);
            // if(d == NULL){
            //     printf("Disparador nao encontrado no comando disp qry\n");
            // }
            // Forma f = getConteudoCentro(d);
            // posicionaForma(f,d,dx,dy);
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