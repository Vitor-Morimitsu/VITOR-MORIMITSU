#include "qry.h"

void qryPd(Fila disparadores,int id, double x, double y){
    Disparador d = encontrarDisparadorPorId(disparadores, id);
    if(d == NULL){
        //Disparador inexistente. Preciso criar um 
        d = criarDisparador(id,x,y);
    }else{
        setPosicaoDisparador(d,x,y);
    }
}

void qryLc(Fila carregadores,Fila chao, int idCar, int n){
    if(chao == NULL){
        printf("Chão está vazio\n");
        return;
    }
    if(carregadores == NULL){
        printf("fila de carregadores está vazia\n");
        return;
    }

    Carregador car = encontrarCarregadorPorId(carregadores,idCar);
    if(car == NULL){
        //carregador inexistente. Preciso criar um.
        car = criarCarregador(idCar);
        insereFila(carregadores,car);
    }

    Pilha pCar = getPilhaCarregador(car);
    int tamanhoChao = getTamanhoFila(chao);
   
    for(int i = 0; i<n;i++){
        Forma f = getPrimeiroConteudoFila(chao);
        // if(f == NULL){
        //     printf("Chão está vazio\n");
        //     break;
        // }
        removeFila(chao);
        inserirPilha(pCar,f);
    }
    
}

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

    Carregador CE = getCarregadorDisparador(d, 'e');
    Carregador CD = getCarregadorDisparador(d,'d');

    int confirmacao = -1;
    if(lado == 'e'){
        // Pressiona botão esquerdo: move formas do carregador direito para o centro
        for(int i = 0;i<n;i++){
            Forma centro = getConteudoCentro(d); 
            if(centro == NULL){
                //centro vazio
                confirmacao = shft(d,'d');                   

            }else{
                //existe uma forma no centro
                inserirPilha(CE, centro);
                confirmacao = shft(d, 'd');                         
            }         
        }

    }else if(lado == 'd'){
        // Pressiona botão direito: move formas do carregador esquerdo para o centro
        for(int i = 0;i<n;i++){
            Forma centro = getConteudoCentro(d); 
            if(centro == NULL){
                //centro vazio
                confirmacao = shft(d, 'e');
            }else{
                //existe uma forma no centro
                inserirPilha(CD, centro);
                confirmacao = shft(d, 'e');          
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
        //anotar as dimensões do disparo no svg ----------------------------------------------------------------------falta terminar para printar no arqTxt
        
    }else if(letra == 'i'){
        // Modo iteração: multiplica deslocamento pela iteração
        comando = iteracao;
    }

    Pacote conteudoDisparado = dsp(d);
    if(conteudoDisparado == NULL){
        return;
    }else{
        char tipoConteudo = getTipoPacote(conteudoDisparado);
        Forma form = getFormaPacote(conteudoDisparado);
        if(form == NULL){
            fprintf(stderr, "ERRO [dsp]: Figura interna é NULL\n");
            return;
        }
        
        if(tipoConteudo == 'c'){
            Circulo* circ = (Circulo*)form;
            setXCirculo(circ, xDisparador +  dx);
            setYCirculo(circ, yDisparador + dy);
            insereFila(arena,form);

        }else if(tipoConteudo == 'r'){
            Retangulo* ret = (Retangulo*)form;
            setCoordXRetangulo(ret,xDisparador + dx);
            setCoordYRetangulo(ret,yDisparador + dy);
            insereFila(arena,form);

        }else if(tipoConteudo == 'l'){
            Linha* lin = (Linha*)form;
            double vetorX = getX2Linha(lin) - getX1Linha(lin);
            double vetorY = getY2Linha(lin) - getY1Linha(lin);
            
            setX1Linha(lin, xDisparador + dx);
            setY1Linha(lin, yDisparador + dy);


            setX2Linha(lin, (xDisparador + dx) + vetorX);
            setY2Linha(lin, (yDisparador + dy) + vetorY);

            insereFila(arena,form);

        }else if(tipoConteudo == 't'){
            Texto* t = (Texto*)form;
            setXTexto(t, xDisparador + dx);
            setYTexto(t, yDisparador + dy);
            insereFila(arena,form);
        }
    }
}

void qryRjd(Fila disparadores, Fila carregadores, Fila arena,int idDis, char lado, double dx, double dy,double ix, double iy){ 
    Disparador d = encontrarDisparadorPorId(disparadores,idDis);
    if(d == NULL){
        fprintf(stderr, "ERRO [rjd]: Disparador ID %d não encontrado\n", idDis);
        return;
    }

    Carregador CE = getCarregadorDisparador(d,'e');
    Carregador CD = getCarregadorDisparador(d,'d');

    Pilha pilhaEsquerda = getPilhaCarregador(CE);
    Pilha pilhaDireita = getPilhaCarregador(CD);

    int tamEsq = getTamanhoPilha(pilhaEsquerda);
    int tamDir = getTamanhoPilha(pilhaDireita);

    if(lado == 'e'){
        //esvazia o carregador direito
        for(int i = 0; i< tamDir;i++){
            int iteracao = i;
            qryShft(disparadores,carregadores,idDis,lado,1);
            qryDsp(disparadores,arena, idDis, dx+iteracao*ix, dy+iteracao*iy,'i',i);
        }
        
    }else if(lado == 'd'){
        //esvazia o carregador esquerdo        
        for(int i = 0;i<tamEsq;i++){
            int iteracao = i;
            qryShft(disparadores,carregadores,idDis,lado,1);
            qryDsp(disparadores,arena, idDis, dx+iteracao*ix, dy+iteracao*iy,'i',i);
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
            qryPd(filaDisparadores,idDis,x,y);
            
        }else if(strcmp(comando, "lc") == 0){
            // Comando lc: carrega formas no carregador
            int n;
            int idCar;
            sscanf(linha, "lc %i %i", &idCar, &n);   
            qryLc(filaCarregadores,chao,idCar,n);
            
        }else if(strcmp(comando, "atch") == 0){
            printf("comando atch\n");
            //encaixa no disparador d os carregadores cesq(na esquerda) e cdir(na direita)
            int idDis, idCesq, idCDir;
            sscanf(linha,"atch %i %i %i",&idDis,&idCesq,&idCDir);
            printf("comando atch = idDIs:%i  idEsq:%i  idDir:%i\n", idDis,idCesq,idCDir);
            qryAtch(filaDisparadores,filaCarregadores,idDis,idCesq,idCDir);
            
        }else if(strcmp(comando, "shft") == 0){
            printf("comando shft\n");
            //pressiona o botão esquerdo(e) ou o botão direito(d) do disparador d n vezes
            char lado;
            int n, idDis;
            sscanf(linha, "shft %i %c %i", &idDis,&lado, &n);
            printf("comando shft = idDis:%i  lado:%c  qunatidade de vezes:%i\n",idDis,lado,n);
            qryShft(filaDisparadores,filaCarregadores,idDis, lado,n);
            //printar no txt
            // comandoShft(arqTxt,idDis, filaDisparadores);  
            
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
            // comandoDsp(arqTxt,filaDisparadores, idDis,dx,dy);
            
        }else if(strcmp(comando, "rjd") == 0){
            printf("comando rjd\n");
            //rajada de disparos até as formas do carregador se esgotarem
            char car;
            int idDis, idEsq, idDir;
            double dx, dy, ix, iy;
            sscanf(linha, "rjd %i %c %lf %lf %lf %lf", &idDis,&car,&dx,&dy,&ix,&iy);
            printf("comando rjd = idDis:%i  letra do carregador:%c dx:%lf  dy:%lf  ix:%lf iy:%lf\n",idDis,car,dx,dy,ix,iy);
            qryRjd(filaDisparadores,filaCarregadores,chao,idDis,car,dx,dy,ix,iy);
            
        }else if(strcmp(comando, "calc") == 0){
            //processa as figuras da arena conforme descrito anteriormente em um novo arqSVg
            // comandoCalc(arqTxt,chao);
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