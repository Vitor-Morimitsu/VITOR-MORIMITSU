#include "criarTxt.h"

// void escreverConteudoPilha(FILE* arqTxt, Pilha p){
//     if(p == NULL || arqTxt == NULL){
//         printf("Erro ao abrir arquivos.");
//         exit(1);
//     }
//     NoPilha_t atual = getNoTopoPilha(p);  
    
//     while(atual != NULL){
//         void* cont = getConteudoDoNoPilha(atual);
//         if(cont != NULL){

//             char tipo = getTipoForma(cont);
//             int id = getIDForma(cont);
//             double x = getXForma(cont);
//             double y = getYForma(cont);
            
//             if(tipo == 'c'){//círculo
//                 Circulo* circ = (Circulo*)cont;
//                 double raio = getRaioCirculo(circ);
//                 char* corb = getCorBCirculo(circ);
//                 char* corp = getCorPCirculo(circ);
//                 fprintf(arqTxt, "círculo id:%i x:%lf y:%lf raio:%lf corb:%s corp:%s\n", id,x,y,raio,corb,corp);
//             }else if(tipo == 'r'){
//                 // retângulo
//                 Retangulo* ret = (Retangulo*)cont;
//                 int idRet = getIDRetangulo(ret);
//                 double CordX = getCoordXRetangulo(ret);
//                 double CordY = getCoordYRetangulo(ret);
//                 double w = getWRetangulo(ret);
//                 double h = getHRetangulo(ret);
//                 char* corb = getCorBRetangulo(ret);
//                 char* corp = getCorPRetangulo(ret);
//                 printf("teste 6\n");
//                 fprintf(arqTxt, "retângulo id:%i x:%lf y:%lf w:%lf h:%lf corB:%s corP:%s\n",idRet,CordX,CordY,w,h,corb,corp);
//             }else if(tipo == 'l'){
//                 //linha
//                 Linha* l = (Linha*)cont;
//                 double x1 = getX1Linha(l);
//                 double y1 = getY1Linha(l);
//                 double x2 = getX2Linha(l);
//                 double y2 = getY2Linha(l);
//                 char* cor = getCorLinha(l);
//                 fprintf(arqTxt, "l id:%d x1:%lf y1:%lf x2:%lf y2:%lf cor:%s\n",id,x1,y1,x2,y2,cor);
//             }else if(tipo == 't'){
//                 //texto 
//                 Texto* t = (Texto*)cont;
//                 char* corb = getCorBTexto(t);
//                 char* corp = getCorPTexto(t);
//                 char a = getATexto(t);
//                 char* txto = getTxtoTexto(t);
                
//                 Estilo ts = getEstiloTexto(t);
//                 char* fFamily = getfFamily(ts);
//                 char* fWeight = getfWeight(ts);
//                 char* fSize = getfSize(ts);
//                 fprintf(arqTxt, "t id:%d x:%lf y:%lf corb:%s corp:%s ancora:%c texto:%s family:%s weight:%s size:%s\n",id,x,y,corb,corp,a,txto,fFamily,fWeight,fSize);
//             }
//         }
//         atual = getProximoNoPilha(atual);
//     }
// }

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

    void* centro = getConteudoCentro(disp);
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
    void* forma = getConteudoCentro(d);
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

void comandoCalc(FILE* arqTxt, Fila chao) {
    if (arqTxt == NULL || chao == NULL) {
        printf("Erro: Arquivo Txt ou Fila 'chao' nulos no comando calc.\n");
        return; 
    }

    double area_esmagada_total = 0.0;
    int confirmacao = 0; 

    printf("calculo das sobreposições\n");

    No_t no1 = getPrimeiroNoFila(chao);
    while (no1 != NULL) {
        double areaEsmagadaRound = 0.0;
        Forma f1 = (Forma)getConteudoDoNoFila(no1);
        if (f1 == NULL) {
            no1 = getProximoNoFila(no1);
            continue;
        }
        char tipo_f1 = getTipoForma(f1);
        void* figura1 = getFiguraForma(f1);
        if (figura1 == NULL) {
             printf("  Aviso: Figura interna nula encontrada (Tipo %c).\n", tipo_f1);
             no1 = getProximoNoFila(no1);
             continue;
        }

        No_t no2 = getProximoNoFila(no1);
        while (no2 != NULL) {
            Forma f2 = (Forma)getConteudoDoNoFila(no2);
            if (f2 == NULL) {
                no2 = getProximoNoFila(no2);
                continue;
            }
            char tipo_f2 = getTipoForma(f2);
            void* figura2 = getFiguraForma(f2);
             if (figura2 == NULL) {
                printf("  Aviso: Figura interna nula encontrada (Tipo %c).\n", tipo_f2);
                no2 = getProximoNoFila(no2);
                continue;
            }

            confirmacao = 0; 

            if (tipo_f1 == 'c') {
                Circulo* c1 = (Circulo*)figura1;
                if (tipo_f2 == 'c') confirmacao = circuloSobrepoeCirculo(c1, (Circulo*)figura2);
                else if (tipo_f2 == 'r') confirmacao = circuloSobrepoeRetangulo(c1, (Retangulo*)figura2);
                else if (tipo_f2 == 'l') confirmacao = circuloSobrepoeLinha(c1, (Linha*)figura2);
                else if (tipo_f2 == 't') confirmacao = circuloSobrepoeTexto(c1, (Texto*)figura2);
            } else if (tipo_f1 == 'r') {
                Retangulo* r1 = (Retangulo*)figura1;
                if (tipo_f2 == 'c') confirmacao = circuloSobrepoeRetangulo((Circulo*)figura2, r1); 
                else if (tipo_f2 == 'r') confirmacao = retanguloSobrepoeRetangulo(r1, (Retangulo*)figura2);
                else if (tipo_f2 == 'l') confirmacao = retanguloSobrepoeLinha(r1, (Linha*)figura2);
                else if (tipo_f2 == 't') confirmacao = retanguloSobrepoeTexto(r1, (Texto*)figura2);
            } else if (tipo_f1 == 'l') {
                Linha* l1 = (Linha*)figura1;
                if (tipo_f2 == 'c') confirmacao = circuloSobrepoeLinha((Circulo*)figura2, l1); 
                else if (tipo_f2 == 'r') confirmacao = retanguloSobrepoeLinha((Retangulo*)figura2, l1); 
                else if (tipo_f2 == 'l') confirmacao = linhaSobrepoeLinha(l1, (Linha*)figura2);
                else if (tipo_f2 == 't') confirmacao = linhaSobrepoeTexto(l1, (Texto*)figura2);
            } else if (tipo_f1 == 't') {
                Texto* t1 = (Texto*)figura1;
                if (tipo_f2 == 'c') confirmacao = circuloSobrepoeTexto((Circulo*)figura2, t1); 
                else if (tipo_f2 == 'r') confirmacao = retanguloSobrepoeTexto((Retangulo*)figura2, t1); 
                else if (tipo_f2 == 'l') confirmacao = linhaSobrepoeTexto((Linha*)figura2, t1); 
                else if (tipo_f2 == 't') confirmacao = textoSobrepoeTexto(t1, (Texto*)figura2);
            }

            if (confirmacao == 1) {
                double area_f1 = -1.0, area_f2 = -1.0;
                if (tipo_f1 == 'c') area_f1 = getAreaCirculo((Circulo*)figura1);
                else if (tipo_f1 == 'r') area_f1 = getAreaRetangulo((Retangulo*)figura1);
                else if (tipo_f1 == 'l') area_f1 = getAreaLinha((Linha*)figura1);
                else if (tipo_f1 == 't') area_f1 = getAreaTexto((Texto*)figura1);

                if (tipo_f2 == 'c') area_f2 = getAreaCirculo((Circulo*)figura2);
                else if (tipo_f2 == 'r') area_f2 = getAreaRetangulo((Retangulo*)figura2);
                else if (tipo_f2 == 'l') area_f2 = getAreaLinha((Linha*)figura2);
                else if (tipo_f2 == 't') area_f2 = getAreaTexto((Texto*)figura2);

                if (area_f1 >= 0.0 && area_f2 >= 0.0) {
                    if (area_f1 < area_f2) {
                        areaEsmagadaRound += area_f1;
                        area_esmagada_total += area_f1;
                        // printf("  Sobreposição: [%c %d] sobre [%c %d]. Menor área (%.2f) adicionada.\n",
                        //         tipo_f1, getIDForma(f1), tipo_f2, getIDForma(f2), area_f1);
                    } else {
                        areaEsmagadaRound += area_f2;
                        area_esmagada_total += area_f2;
                        // printf("  Sobreposição: [%c %d] sobre [%c %d]. Menor área (%.2f) adicionada.\n",
                        //         tipo_f1, getIDForma(f1), tipo_f2, getIDForma(f2), area_f2);
                    }
                } else {
                    // printf("  Sobreposição: [%c %d] sobre [%c %d]. Uma das áreas inválida (linha/texto?), não somado.\n",
                    //             tipo_f1, getIDForma(f1), tipo_f2, getIDForma(f2));
                }
            } 

            no2 = getProximoNoFila(no2); 
        } 
        fprintf(arqTxt,"Área esmagada no Round: %.2f\n", areaEsmagadaRound);
        no1 = getProximoNoFila(no1);
    } 
    fprintf(arqTxt, "--- Fim dos Cálculos ---\n");
    fprintf(arqTxt, "Área total esmagada: %.2f\n\n", area_esmagada_total);
}