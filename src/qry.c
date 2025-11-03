#include "qry.h"
#include <math.h>

void qryPd(Fila disparadores,int id, double x, double y){
    Disparador d = encontrarDisparadorPorId(disparadores, id);
    if(d == NULL){
        //Disparador inexistente. Preciso criar um 
        d = criarDisparador(id,x,y);
        insereFila(disparadores, d);
        // printf("ID do disparador: %i\n", getIDDisparador(d));----------------------ok
    }else{
        setPosicaoDisparador(d,x,y);
    }
}

void qryLc(FILE* Txt,Fila carregadores,Fila chao, int idCar, int n){
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
    if(tamanhoChao<n){
        printf("Quantidade de fomras insuficentes para carregamento\n");
        return;
    }
    
    // Carrega as formas do chão para a pilha
    for(int i = 0; i<n;i++){
        Pacote pac = (Pacote)getPrimeiroConteudoFila(chao);
        inserirPilha(pCar,pac);
        removeFila(chao);
    }
    
    // Escreve no arquivo txt o conteúdo da pilha (sem remover)
    fprintf(Txt, "Conteúdo da pilha:\n");
    Pilha pilhaTemp = criarPilha();
    
    // Copia para pilha temporária e escreve
    while(getTamanhoPilha(pCar) > 0){
        Pacote pac = getPacoteTopoPilha(pCar);
        if(pac != NULL){
            Forma forma = getFormaPacote(pac);
            char tipoPac = getTipoPacote(pac);
            if(tipoPac == 'c'){
                fprintf(Txt, "Circulo com id:%d\n", getIDCirculo((Circulo)forma));            
            }else if(tipoPac == 'r'){
                fprintf(Txt, "Retângulo com id:%d\n", getIDRetangulo((Retangulo)forma));          
            }else if(tipoPac == 'l'){
                fprintf(Txt, "Linha com id:%d\n", getIDLinha((Linha)forma));           
            }else if(tipoPac == 't'){
                fprintf(Txt, "Texto com id:%d\n", getIDTexto((Texto)forma));            
            }
            inserirPilha(pilhaTemp, pac);
        }
        removerPilha(pCar);
    }
    fprintf(Txt, "\n");
    
    // Restaura a pilha original
    while(getTamanhoPilha(pilhaTemp) > 0){
        Pacote pac = getPacoteTopoPilha(pilhaTemp);
        inserirPilha(pCar, pac);
        removerPilha(pilhaTemp);
    }
    
    destruirPilha(pilhaTemp);
}


void qryAtch(Fila disparadores, Fila carregadores,int idDisparador, int idEsquerdo, int idDireito){
    Disparador d = encontrarDisparadorPorId(disparadores,idDisparador);
    if(d == NULL){
        fprintf(stderr, "AVISO [atch]: Disparador ID %d não encontrado\n", idDisparador);
        return;
    }

    // Busca ou cria carregador esquerdo
    Carregador CE = encontrarCarregadorPorId(carregadores,idEsquerdo);
    if(CE == NULL){
        //não existe carregador esquerdo
        CE = criarCarregador(idEsquerdo);
        insereFila(carregadores,CE);
    }

    // Busca ou cria carregador direito
    Carregador CD = encontrarCarregadorPorId(carregadores,idDireito);
    if(CD == NULL){
        //não existe carregador direito
        CD = criarCarregador(idDireito);
        insereFila(carregadores, CD);
    }

    // Associa os carregadores ao disparador
    atch(d,CE,'e');
    atch(d,CD,'d');

}

void qryShft(FILE* txt,Fila disparadores, Fila carregadores, int idDis, char lado, int n){
    Disparador d = encontrarDisparadorPorId(disparadores, idDis);
    if(d == NULL){
        fprintf(stderr, "ERRO [shft]: Disparador ID %d não encontrado\n", idDis);
        return;
    }
    
    Carregador CE = getCarregadorDisparador(d,'e');
    Carregador CD = getCarregadorDisparador(d,'d');
    
    if(CE == NULL || CD == NULL){
        fprintf(stderr, "ERRO [shft]: Carregadores não encontrados no disparador %d\n", idDis);
        return;
    }

    if(lado == 'e'){
        // Pressiona botão esquerdo: move formas do carregador DIREITO para o centro
        // (empurra o que está no centro para a esquerda)
        for(int i = 0; i < n; i++){
            shft(d, 'd');
        }
    }else if(lado == 'd'){
        // Pressiona botão direito: move formas do carregador ESQUERDO para o centro
        // (empurra o que está no centro para a direita)
        for(int i = 0; i < n; i++){
            shft(d, 'e');
        }
    }else{
        fprintf(stderr, "ERRO [shft]: Lado inválido '%c'. Use 'e' ou 'd'\n", lado);
        return;
    }
    
    // Escreve no txt apenas uma vez após todas as operações
    if(txt != NULL){
        comandoShft(txt, idDis, disparadores);
    }
}

Pacote qryDsp(Fila disparadores, Fila arena, int idDis, double dx, double dy, char letra, int iteracao, FILE* arqTxt, FILE* arqSvg){
    Disparador d = encontrarDisparadorPorId(disparadores, idDis);
    if(d == NULL){
        fprintf(stderr, "ERRO [dsp]: Disparador ID %d não encontrado\n", idDis);
        return;
    }

    double xDisparador = getXDisparador(d);
    double yDisparador = getYDisparador(d);

    int comando = 1;

    if(letra == 'v'){
        //registrar as dimensões do disparo        
    }else if(letra == 'i'){
        // Modo iteração: multiplica deslocamento pela iteração
        comando = iteracao;
    }
    
    Pacote pacoteDisparado = dsp(d);
    if(pacoteDisparado == NULL){
        printf("nada foi disparado\n");
        return NULL;
    }else{
        //registra as dimensões de disparo no modo 'v'
        if(letra == 'v'){
            double xDisp = getXDisparador(d);
            double yDisp = getYDisparador(d);
            double xFinal = xDisp + dx;
            double yFinal = yDisp + dy;
            double distancia = sqrt(dx*dx + dy*dy);
            
            char tipo = getTipoPacote(pacoteDisparado);
            const char* nomeTipo = (tipo == 'r') ? "Retângulo" : 
                                   (tipo == 'c') ? "Círculo" : 
                                   (tipo == 'l') ? "Linha" : "Texto";
            
            if(arqTxt != NULL){
                fprintf(arqTxt, "\n--- Dimensões do Disparo ---\n");
                fprintf(arqTxt, "Tipo da forma: %s\n", nomeTipo);
                fprintf(arqTxt, "Posição do disparador: (%.2lf, %.2lf)\n", xDisp, yDisp);
                fprintf(arqTxt, "Deslocamento aplicado: dx=%.2lf, dy=%.2lf\n", dx, dy);
                fprintf(arqTxt, "Posição final da forma: (%.2lf, %.2lf)\n", xFinal, yFinal);
                fprintf(arqTxt, "Distância percorrida: %.2lf\n", distancia);
            }
            
            // Desenha as linhas de dimensão no SVG
            if(arqSvg != NULL){
                dimensoesDisparo(arqSvg, xDisp, yDisp, dx, dy);
            }
        }
        
        char tipoConteudo = getTipoPacote(pacoteDisparado);
        Forma form = getFormaPacote(pacoteDisparado);
        if(form == NULL){
            fprintf(stderr, "ERRO [dsp]: Figura interna é NULL\n");
            return;
        }
        
        if(tipoConteudo == 'c'){
            Circulo* circ = (Circulo*)form;
            setXCirculo(circ, xDisparador +  dx);
            setYCirculo(circ, yDisparador + dy);

        }else if(tipoConteudo == 'r'){
            Retangulo* ret = (Retangulo*)form;
            setCoordXRetangulo(ret,xDisparador + dx);
            setCoordYRetangulo(ret,yDisparador + dy);

        }else if(tipoConteudo == 'l'){
            Linha* lin = (Linha*)form;
            double vetorX = getX2Linha(lin) - getX1Linha(lin);
            double vetorY = getY2Linha(lin) - getY1Linha(lin);
            
            setX1Linha(lin, xDisparador + dx);
            setY1Linha(lin, yDisparador + dy);

            setX2Linha(lin, (xDisparador + dx) + vetorX);
            setY2Linha(lin, (yDisparador + dy) + vetorY);

        }else if(tipoConteudo == 't'){
            Texto* t = (Texto*)form;
            setXTexto(t, xDisparador + dx);
            setYTexto(t, yDisparador + dy);
        }
        
        // Insere o PACOTE completo na arena, não apenas a forma
        insereFila(arena, pacoteDisparado);
        return pacoteDisparado;
    }
}

void qryRjd(FILE* txt,Fila disparadores, Fila carregadores, Fila arena,int idDis, char lado, double dx, double dy,double ix, double iy){ 
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
            qryShft(NULL,disparadores,carregadores,idDis,lado,1);
            qryDsp(disparadores,arena, idDis, dx+iteracao*ix, dy+iteracao*iy,'i',i,NULL,NULL);
        }
        
    }else if(lado == 'd'){
        //esvazia o carregador esquerdo        
        for(int i = 0;i<tamEsq;i++){
            int iteracao = i;
            qryShft(NULL,disparadores,carregadores,idDis,lado,1);
            qryDsp(disparadores,arena, idDis, dx+iteracao*ix, dy+iteracao*iy,'i',i,NULL,NULL);
        }
    }
}

void lerQry(FILE* arqQry, FILE* arqTxt, FILE* svg, Fila filaDisparadores,Fila filaCarregadores,Fila chao){
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
            qryLc(arqTxt,filaCarregadores,chao,idCar,n);
            
        }else if(strcmp(comando, "atch") == 0){
            //encaixa no disparador d os carregadores cesq(na esquerda) e cdir(na direita)
            int idDis, idCesq, idCDir;
            sscanf(linha,"atch %i %i %i",&idDis,&idCesq,&idCDir);
            qryAtch(filaDisparadores,filaCarregadores,idDis,idCesq,idCDir);
           
            
        }else if(strcmp(comando, "shft") == 0){
            //pressiona o botão esquerdo(e) ou o botão direito(d) do disparador d n vezes
            char lado;
            int n, idDis;
            sscanf(linha, "shft %i %c %i", &idDis,&lado, &n);
            qryShft(arqTxt,filaDisparadores,filaCarregadores,idDis, lado,n);
            
        }else if(strcmp(comando, "dsp") == 0){
            //posiciona a forma que está em posição de disparo a um deslocamento de dx, dy em relação à posição do disparador
            double dx, dy;
            int iteracao = 1;
            int idDis;
            char letra;
            sscanf(linha, "dsp %i %lf %lf %c", &idDis,&dx,&dy,&letra);
            Pacote pacDisparado = qryDsp(filaDisparadores,chao,idDis,dx,dy,letra,iteracao,arqTxt,svg);
            comandoDsp(arqTxt, pacDisparado, dx, dy);
            
        }else if(strcmp(comando, "rjd") == 0){
            //rajada de disparos até as formas do carregador se esgotarem
            char car;
            int idDis, idEsq, idDir;
            double dx, dy, ix, iy;
            sscanf(linha, "rjd %i %c %lf %lf %lf %lf", &idDis,&car,&dx,&dy,&ix,&iy);
            qryRjd(arqTxt,filaDisparadores,filaCarregadores,chao,idDis,car,dx,dy,ix,iy);
            
        }else if(strcmp(comando, "calc") == 0){
            //processa as figuras da arena conforme descrito anteriormente em um novo arqSVg
            comandoCalc(arqTxt, svg, chao);
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