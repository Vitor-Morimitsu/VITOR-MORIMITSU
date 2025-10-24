#include "criarTxt.h"

void escreverConteudoPilha(FILE* arqTxt, Pilha p){
    if(p == NULL || arqTxt == NULL){
        printf("Erro ao abrir arquivos.");
        exit(1);
    }

    No_t atual = getNoTopoPilha(p);  

    while(atual != NULL){
        Conteudo cont = getConteudoDoNoPilha(atual);
        if(cont != NULL){
            char tipo = getTipoForma(cont);
            
            int id = getIDForma(cont);
            double x = getXForma(cont);
            double y = getYForma(cont);

            if(tipo == 'c'){//círculo
                Circulo* circ = (Circulo*)cont;
                double raio = getRaioCirculo(circ);
                char* corb = getCorBCirculo(circ);
                char* corp = getCorPCirculo(circ);
                fprintf(arqTxt, "círculo id:%i x:%lf y:%lf raio:%lf corb:%s corp:%s\n", id,x,y,raio,corb,corp);
            }else if(tipo == 'r'){
                // retângulo
                Retangulo* ret = (Retangulo*)cont;
                double w = getWRetangulo(ret);
                double h = getHRetangulo(ret);
                char* corb = getCorBRetangulo(ret);
                char* corp = getCorPRetangulo(ret);
                fprintf(arqTxt, "re id:%i x:%lf y:%lf w:%lf h:%lf corB:%s corP:%s\n",id,x,y,w,h,corb,corp);
            }else if(tipo == 'l'){
                //linha
                Linha* l = (Linha*)cont;
                double x1 = getX1Linha(l);
                double y1 = getY1Linha(l);
                double x2 = getX2Linha(l);
                double y2 = getY2Linha(l);
                char* cor = getCorLinha(l);
                fprintf(arqTxt, "l id:%d x1:%lf y1:%lf x2:%lf y2:%lf cor:%s\n",id,x1,y1,x2,y2,cor);
            }else if(tipo == 't'){
                //texto 
                Texto* t = (Texto*)cont;
                char* corb = getCorBTexto(t);
                char* corp = getCorPTexto(t);
                char a = getATexto(t);
                char* txto = getTxtoTexto(t);

                Estilo ts = getEstiloTexto(t);
                char* fFamily = getfFamily(ts);
                char* fWeight = getfWeight(ts);
                char* fSize = getfSize(ts);
                fprintf(arqTxt, "t id:%d x:%lf y:%lf corb:%s corp:%s ancora:%c texto:%s family:%s weight:%s size:%s\n",id,x,y,corb,corp,a,txto,fFamily,fWeight,fSize);
            }
        }
        atual = getProximoNoPilha(atual);
    }
}

void comandoShft(FILE* arqTxt,int idDis, Fila filaDisparadores){
    if(arqTxt == NULL){
        printf("Erro ao abrir o arquivo txt.");
        exit(1);
    }

    Disparador disp = encontrarDisparadorPorID(filaDisparadores, idDis);
    if(disp == NULL){
        printf("Erro ao acessar o disparador.");
        return;
    }

    Conteudo centro = getConteudoCentro(disp);
    if(centro == NULL){
        printf("A posição de disparo está vazia.");
        return;
    }else{
        char fig = getTipoForma(centro);
        char* figura = "desconhecida";
        if(fig == 'c'){
            figura = "circulo";
        }else if(fig == 'r'){
            figura = "retangulo";
        }else if(fig == 'l'){
            figura = "linha";
        }else if(fig == 't'){
            figura = "texto";
        }
        fprintf(arqTxt, "A figura que está no centro é %s\n", figura);
    }
}

void comandoDsp(FILE* arqTxt, Fila filaDisparadores,int idDis, double dx, double dy){
    if(arqTxt == NULL){
        printf("Erro ao acessar o arquivo txt.");
        return;
    }
    Disparador d = encontrarDisparadorPorID(filaDisparadores, idDis);
    if(d == NULL){
        printf("Disparador não encontrado.");
        return;
    }
    Conteudo forma = getConteudoCentro(d);
    if(forma == NULL){
        printf("Nenhuma forma foi disparada.");
        return;
    }
    posicionaForma(forma, d, dx, dy);

    double xFinal = getXForma(forma);
    double yFinal = getYForma(forma);
    //caso da linha
    double x2Final = -1;
    double y2Final = -1;
    
    char* nomeFigura = "desconhecida";
    char tipo = getTipoForma(forma);
    if(tipo == 'c'){

        nomeFigura = "círculo";
    }else if(tipo == 'r'){

        nomeFigura = "retângulo";
    }else if(tipo == 'l'){
        nomeFigura = "linha";
        xFinal = getX1Linha((Linha*)forma);
        yFinal = getY1Linha((Linha*)forma);
        x2Final = getX2Linha((Linha*)forma);
        y2Final = getY2Linha((Linha*)forma);

    }else if(tipo == 't'){
        nomeFigura = "texto";
    }

    if(tipo == 'l'){
        fprintf(arqTxt, "forma:%s   X1 final:%lf   Y1 final:%lf  X2 final:%lf  Y2 final:%lf\n ", nomeFigura, xFinal, yFinal, x2Final, y2Final);
    }else{
        fprintf(arqTxt, "forma:%s  X final:%lf  Y final:%lf\n", nomeFigura, xFinal, yFinal);
    }
}

void comandoRjd(FILE* arqTxt, Fila filaDisparadores, int idDis,Fila filaCarregadores, char car){
    if (arqTxt == NULL) {
        fprintf(stderr, "Erro: Arquivo de texto nulo.\n");
        return;
    }

    Disparador d = encontrarDisparadorPorID(filaDisparadores, idDis);
    if (d == NULL) {
        printf("Disparador não encontrado para rajada.\n");
        return;
    }

    int idEsq = getIDPilhaEsquerda(d);
    int idDir = getIDPilhaDireita(d);
    Pilha pEsq = encontrarPilhaPorID(filaCarregadores, idEsq);
    Pilha pDir = encontrarPilhaPorID(filaCarregadores, idDir);
    
    if (pEsq == NULL || pDir == NULL) {
        printf("Pilhas para o disparador não encontradas.\n");
        return;
    }
    
    Pilha pilhaRajada;
    if (car == 'e') {
        pilhaRajada = pEsq;
    } else {
        pilhaRajada = pDir;
    }
        
    int totalTiros = 0;

    while (getTamanhoPilha(pilhaRajada) > 0) {
        pressionaBotao(d, car, 1, pEsq, pDir);
        
        Forma f = getConteudoCentro(d);
        if (f == NULL) break; 
        
        char tipo = getTipoForma(f);
        int id = getIDForma(f);
        const char* nomeFigura = "desconhecida";
        if(tipo == 'c') nomeFigura = "circulo";
        else if(tipo == 'r') nomeFigura = "retangulo";
        else if(tipo == 'l') nomeFigura = "linha";
        else if(tipo == 't') nomeFigura = "texto";
        
        fprintf(arqTxt, "Tiro %d: Forma disparada:%s ID:%d\n", totalTiros + 1, nomeFigura, id);
        
        char ladoOposto;
        if (car == 'e') {
            ladoOposto = 'd';
        } else {
            ladoOposto = 'e';
        }
        pressionaBotao(d, ladoOposto, -1, pEsq, pDir); 
        
        totalTiros++;
    }
}

void comandoCalc(FILE* arqTxt, Fila chao){
    if(arqTxt == NULL || chao == NULL ){
        printf("Erro ao realizar o comando calc.");
        return;
    }
    
    int quantidade = getTamanhoFila(chao);

    // ver a posição de cada forma e ver se elas se sobrepõem
    double area_esmagada_total = 0;
    for(int i  = 0;i< quantidade;i++){
        Forma f1 = percorreFila(chao,i);
        char tipo_f1 = getTipoForma(f1);

        int confirmacao = -1;
        double area_esmagada_round = 0;
 
        for(int j = 0;j< quantidade - 1;j++){
            Forma f2 = percorreFila(chao, j);
            char tipo_f2 = getTipoForma(f2);
            if(tipo_f1 == 'c'){
                if(tipo_f2 == 'c'){
                    confirmacao = circuloSobrepoeCirculo(f1,f2);
                    if(confirmacao == 1){
                        double area_f1 = getAreaCirculo((Circulo*)f1);
                        double area_f2 = getAreaCirculo((Circulo*)f2);
                        if(area_f1 < area_f2){
                            area_esmagada_round += area_f1;
                        }else{
                            area_esmagada_round += area_f2;
                        }   
                    }
                }else if(tipo_f2 == 'r'){
                    confirmacao = circuloSobrepoeRetangulo(f1,f2);
                    if(confirmacao == 1){
                        double area_f1 = getAreaCirculo((Circulo*)f1);;
                        double area_f2 = getAreaRetangulo((Retangulo*)f2);
                        if(area_f1 < area_f2){
                            area_esmagada_round += area_f1;
                        }else{
                            area_esmagada_round += area_f2;
                        }  
                    }
                }else if(tipo_f2 == 'l'){
                    confirmacao = circuloSobrepoeLinha(f1,f2);
                    if(confirmacao == 1){
                        double area_f1 = getAreaCirculo((Circulo*)f1);;
                        double area_f2 = getAreaLinha((Linha*)f2);
                        if(area_f1 < area_f2){
                            area_esmagada_round += area_f1;
                        }else{
                            area_esmagada_round += area_f2;
                        }     
                    }
                }else if(tipo_f2 == 't'){
                    confirmacao = circuloSobrepoeTexto(f1,f2);
                    if(confirmacao == 1){
                        double area_f1 = getAreaCirculo((Circulo*)f1);;
                        double area_f2 = getAreaTexto((Texto*)f2);
                        if(area_f1 < area_f2){
                            area_esmagada_round += area_f1;
                        }else{
                            area_esmagada_round += area_f2;
                        }     
                    }
                }

            }else if(tipo_f1 == 'r'){
                if(tipo_f2 == 'c'){
                    confirmacao = circuloSobrepoeRetangulo(f2,f1);
                    if(confirmacao == 1){
                        double area_f1 = getAreaRetangulo((Retangulo*)f1);
                        double area_f2 = getAreaCirculo((Circulo*)f2);
                        if(area_f1 < area_f2){
                            area_esmagada_round += area_f1;
                        }else{
                            area_esmagada_round += area_f2;
                        }     
                    }
                }else if(tipo_f2 == 'r'){
                    confirmacao = retanguloSobrepoeRetangulo(f1,f2);
                    if(confirmacao == 1){
                        double area_f1 = getAreaRetangulo((Retangulo*)f1);
                        double area_f2 = getAreaRetangulo((Retangulo*)f2);
                        if(area_f1 < area_f2){
                            area_esmagada_round += area_f1;
                        }else{
                            area_esmagada_round += area_f2;
                        }     
                    }
                }else if(tipo_f2 == 'l'){
                    confirmacao = retanguloSobrepoeLinha(f1,f2);
                    if(confirmacao == 1){
                        double area_f1 = getAreaRetangulo((Retangulo*)f1);
                        double area_f2 = getAreaLinha((Linha*)f2);
                        if(area_f1 < area_f2){
                            area_esmagada_round += area_f1;
                        }else{
                            area_esmagada_round += area_f2;
                        }     
                    }
                }else if(tipo_f2 == 't'){
                    confirmacao = retanguloSobrepoeTexto(f1,f2);
                    if(confirmacao == 1){
                        double area_f1 = getAreaRetangulo((Retangulo*)f1);
                        double area_f2 = getAreaTexto((Texto*)f2);
                        if(area_f1 < area_f2){
                            area_esmagada_round += area_f1;
                        }else{
                            area_esmagada_round += area_f2;
                        }     
                    }
                }

            }else if(tipo_f1 == 'l'){
                if(tipo_f2 == 'c'){
                    confirmacao = circuloSobrepoeLinha(f2,f1);
                    if(confirmacao == 1){
                        double area_f1 = getAreaLinha((Linha*)f1);
                        double area_f2 = getAreaCirculo((Circulo*)f2);
                        if(area_f1 < area_f2){
                            area_esmagada_round += area_f1;
                        }else{
                            area_esmagada_round += area_f2;
                        }     
                    }
                }else if(tipo_f2 == 'r'){
                    confirmacao = retanguloSobrepoeLinha(f2,f1);
                    if(confirmacao == 1){
                        double area_f1 = getAreaLinha((Linha*)f1);;
                        double area_f2 = getAreaRetangulo((Retangulo*)f2);
                        if(area_f1 < area_f2){
                            area_esmagada_round += area_f1;
                        }else{
                            area_esmagada_round += area_f2;
                        }     
                    }
                }else if(tipo_f2 == 'l'){
                    confirmacao = linhaSobrepoeLinha(f1,f2);
                    if(confirmacao == 1){
                        double area_f1 = getAreaLinha((Linha*)f1);
                        double area_f2 = getAreaLinha((Linha*)f2);
                        if(area_f1 < area_f2){
                            area_esmagada_round += area_f1;
                        }else{
                            area_esmagada_round += area_f2;
                        }     
                    }
                }else if(tipo_f2 == 't'){
                    confirmacao = linhaSobrepoeTexto(f1,f2);
                    if(confirmacao == 1){
                        double area_f1 = getAreaLinha((Linha*)f1);
                        double area_f2 = getAreaTexto((Texto*)f2);
                        if(area_f1 < area_f2){
                            area_esmagada_round += area_f1;
                        }else{
                            area_esmagada_round += area_f2;
                        }     
                    }
                }

            }else if(tipo_f1 == 't'){
                if(tipo_f2 == 'c'){
                    confirmacao = circuloSobrepoeTexto(f2,f1);
                    if(confirmacao == 1){
                        double area_f1 = getAreaTexto((Texto*)f1);
                        double area_f2 = getAreaCirculo((Circulo*)f2);
                        if(area_f1 < area_f2){
                            area_esmagada_round += area_f1;
                        }else{
                            area_esmagada_round += area_f2;
                        }     
                    }
                }else if(tipo_f2 == 'r'){
                    confirmacao = retanguloSobrepoeTexto(f2,f1);
                    if(confirmacao == 1){
                        double area_f1 = getAreaTexto((Texto*)f1);
                        double area_f2 = getAreaRetangulo((Retangulo*)f2);
                        if(area_f1 < area_f2){
                            area_esmagada_round += area_f1;
                        }else{
                            area_esmagada_round += area_f2;
                        }     
                    }
                }else if(tipo_f2 == 'l'){
                    confirmacao = linhaSobrepoeTexto(f2,f1);
                    if(confirmacao == 1){
                        double area_f1 = getAreaTexto((Texto*)f1);
                        double area_f2 = getAreaLinha((Linha*)f2);
                        if(area_f1 < area_f2){
                            area_esmagada_round += area_f1;
                        }else{
                            area_esmagada_round += area_f2;
                        }     
                    }
                }else if(tipo_f2 == 't'){
                    confirmacao = textoSobrepoeTexto(f1,f2);
                    if(confirmacao == 1){
                        double area_f1 = getAreaTexto((Texto*)f1);
                        double area_f2 = getAreaTexto((Texto*)f2);
                        if(area_f1 < area_f2){
                            area_esmagada_round += area_f1;
                        }else{
                            area_esmagada_round += area_f2;
                        }     
                    }
                }

            }
            fprintf(arqTxt, "Área esmagada do round: %lf.\n", area_esmagada_round);

        }
        area_esmagada_total += area_esmagada_round; 
        
    } 
    fprintf(arqTxt,"Área total esmagada: %lf.\n", area_esmagada_total);
}

