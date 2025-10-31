#include "criarTxt.h"

void comandoLc(FILE* arqTxt, Pilha p){
    if(arqTxt == NULL || p == NULL){
        printf("Erro realizar o comando Lc no txt\n");
        return;
    }

    //TERMINAR A LÒGICA

}

void comandoShft(FILE* arqTxt,int idDis, Fila filaDisparadores){
    if(arqTxt == NULL){
        printf("Erro ao abrir o arquivo txt.");
        exit(1);
    }

    Disparador disp = encontrarDisparadorPorId(filaDisparadores, idDis);
    if(disp == NULL){
        printf("Erro ao acessar o disparador.");
        return;
    }

    Forma centro = getConteudoCentro(disp);
    if(centro == NULL){
        printf("A posição de disparo está vazia.");
        return;
    }else{
        char fig = getTipoPacote(centro);
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

// void comandoDsp(FILE* arqTxt, Fila filaDisparadores,int idDis, double dx, double dy){
//     if(arqTxt == NULL){
//         printf("Erro ao acessar o arquivo txt.");
//         return;
//     }
//     Disparador d = encontrarDisparadorPorId(filaDisparadores, idDis);
//     if(d == NULL){
//         printf("Disparador não encontrado.");
//         return;
//     }
//     Pacote pac = (Pacote)getConteudoCentro(d);
//     if(pac == NULL){
//         printf("Nenhuma forma foi disparada.");
//         return;
//     }
//     posicionaPacote(pac, d, dx, dy);

//     double xFinal = getXPacote(pac);
//     double yFinal = getYPacote(pac);
//     //caso da linha
//     double x2Final = -1;
//     double y2Final = -1;
    
//     char* nomeFigura = "desconhecida";
//     char tipo = getTipoPacote(pac);
//     if(tipo == 'c'){

//         nomeFigura = "círculo";
//     }else if(tipo == 'r'){

//         nomeFigura = "retângulo";
//     }else if(tipo == 'l'){
//         nomeFigura = "linha";
//         xFinal = getX1Linha((Linha*)pac);
//         yFinal = getY1Linha((Linha*)pac);
//         x2Final = getX2Linha((Linha*)pac);
//         y2Final = getY2Linha((Linha*)pac);

//     }else if(tipo == 't'){
//         nomeFigura = "texto";
//     }

//     if(tipo == 'l'){
//         fprintf(arqTxt, "forma:%s   X1 final:%lf   Y1 final:%lf  X2 final:%lf  Y2 final:%lf\n ", nomeFigura, xFinal, yFinal, x2Final, y2Final);
//     }else{
//         fprintf(arqTxt, "forma:%s  X final:%lf  Y final:%lf\n", nomeFigura, xFinal, yFinal);
//     }
// }

// void comandoRjd(FILE* arqTxt, Fila filaDisparadores, int idDis,Fila filaCarregadores, char car){
//     if (arqTxt == NULL) {
//         fprintf(stderr, "Erro: Arquivo de texto nulo.\n");
//         return;
//     }

//     Disparador d = encontrarDisparadorPorId(filaDisparadores, idDis);
//     if (d == NULL) {
//         printf("Disparador não encontrado para rajada.\n");
//         return;
//     }

//     int idEsq = getIDPilhaEsquerda(d);
//     int idDir = getIDPilhaDireita(d);
//     Pilha pEsq = encontrarPilhaPorID(filaCarregadores, idEsq);
//     Pilha pDir = encontrarPilhaPorID(filaCarregadores, idDir);
    
//     if (pEsq == NULL || pDir == NULL) {
//         printf("Pilhas para o disparador não encontradas.\n");
//         return;
//     }
    
//     Pilha pilhaRajada;
//     if (car == 'e') {
//         pilhaRajada = pEsq;
//     } else {
//         pilhaRajada = pDir;
//     }
        
//     int totalTiros = 0;

//     while (getTamanhoPilha(pilhaRajada) > 0) {
//         pressionaBotao(d, car, 1, pEsq, pDir);
        
//         Forma f = getConteudoCentro(d);
//         if (f == NULL) break; 
        
//         char tipo = getTipoPacote(f);
//         int id = getIDForma(f);
//         const char* nomeFigura = "desconhecida";
//         if(tipo == 'c') nomeFigura = "circulo";
//         else if(tipo == 'r') nomeFigura = "retangulo";
//         else if(tipo == 'l') nomeFigura = "linha";
//         else if(tipo == 't') nomeFigura = "texto";
        
//         fprintf(arqTxt, "Tiro %d: Forma disparada:%s ID:%d\n", totalTiros + 1, nomeFigura, id);
        
//         char ladoOposto;
//         if (car == 'e') {
//             ladoOposto = 'd';
//         } else {
//             ladoOposto = 'e';
//         }
//         pressionaBotao(d, ladoOposto, -1, pEsq, pDir); 
        
//         totalTiros++;
//     }
// }

// void comandoCalc(FILE* arqTxt, Fila chao) {
//     if (arqTxt == NULL || chao == NULL) {
//         printf("Erro: Arquivo Txt ou Fila 'chao' nulos no comando calc.\n");
//         return; 
//     }

//     double area_esmagada_total = 0.0;
//     int confirmacao = 0; 

//     printf("calculo das sobreposições\n");

//     Forma atual = getPrimeiroConteudoFila(chao);
//     while (atual != NULL) {
//         double areaEsmagadaRound = 0.0;
//         Forma f1 = getPrimeiroConteudoFila(chao);
//         if (f1 == NULL) {
//             atual = getProximoNoFila(atual);
//             continue;
//         }
//         char tipo_f1 = getTipoPacote(f1);
//         void* figura1 = getFiguraForma(f1);
//         if (figura1 == NULL) {
//              printf("  Aviso: Figura interna nula encontrada (Tipo %c).\n", tipo_f1);
//              atual = getProximoNoFila(atual);
//              continue;
//         }

//         Forma no2 = getProximoNoFila(atual);
//         while (no2 != NULL) {
//             Forma f2 = (Forma)getConteudoDoNoFila(no2);
//             if (f2 == NULL) {
//                 no2 = getProximoNoFila(no2);
//                 continue;
//             }
//             char tipo_f2 = getTipoPacote(f2);
//             void* figura2 = getFiguraForma(f2);
//              if (figura2 == NULL) {
//                 printf("  Aviso: Figura interna nula encontrada (Tipo %c).\n", tipo_f2);
//                 no2 = getProximoNoFila(no2);
//                 continue;
//             }

//             confirmacao = 0; 

//             if (tipo_f1 == 'c') {
//                 Circulo* c1 = (Circulo*)figura1;
//                 if (tipo_f2 == 'c') confirmacao = circuloSobrepoeCirculo(c1, (Circulo*)figura2);
//                 else if (tipo_f2 == 'r') confirmacao = circuloSobrepoeRetangulo(c1, (Retangulo*)figura2);
//                 else if (tipo_f2 == 'l') confirmacao = circuloSobrepoeLinha(c1, (Linha*)figura2);
//                 else if (tipo_f2 == 't') confirmacao = circuloSobrepoeTexto(c1, (Texto*)figura2);
//             } else if (tipo_f1 == 'r') {
//                 Retangulo* r1 = (Retangulo*)figura1;
//                 if (tipo_f2 == 'c') confirmacao = circuloSobrepoeRetangulo((Circulo*)figura2, r1); 
//                 else if (tipo_f2 == 'r') confirmacao = retanguloSobrepoeRetangulo(r1, (Retangulo*)figura2);
//                 else if (tipo_f2 == 'l') confirmacao = retanguloSobrepoeLinha(r1, (Linha*)figura2);
//                 else if (tipo_f2 == 't') confirmacao = retanguloSobrepoeTexto(r1, (Texto*)figura2);
//             } else if (tipo_f1 == 'l') {
//                 Linha* l1 = (Linha*)figura1;
//                 if (tipo_f2 == 'c') confirmacao = circuloSobrepoeLinha((Circulo*)figura2, l1); 
//                 else if (tipo_f2 == 'r') confirmacao = retanguloSobrepoeLinha((Retangulo*)figura2, l1); 
//                 else if (tipo_f2 == 'l') confirmacao = linhaSobrepoeLinha(l1, (Linha*)figura2);
//                 else if (tipo_f2 == 't') confirmacao = linhaSobrepoeTexto(l1, (Texto*)figura2);
//             } else if (tipo_f1 == 't') {
//                 Texto* t1 = (Texto*)figura1;
//                 if (tipo_f2 == 'c') confirmacao = circuloSobrepoeTexto((Circulo*)figura2, t1); 
//                 else if (tipo_f2 == 'r') confirmacao = retanguloSobrepoeTexto((Retangulo*)figura2, t1); 
//                 else if (tipo_f2 == 'l') confirmacao = linhaSobrepoeTexto((Linha*)figura2, t1); 
//                 else if (tipo_f2 == 't') confirmacao = textoSobrepoeTexto(t1, (Texto*)figura2);
//             }

//             if (confirmacao == 1) {
//                 double area_f1 = -1.0, area_f2 = -1.0;
//                 if (tipo_f1 == 'c') area_f1 = getAreaCirculo((Circulo*)figura1);
//                 else if (tipo_f1 == 'r') area_f1 = getAreaRetangulo((Retangulo*)figura1);
//                 else if (tipo_f1 == 'l') area_f1 = getAreaLinha((Linha*)figura1);
//                 else if (tipo_f1 == 't') area_f1 = getAreaTexto((Texto*)figura1);

//                 if (tipo_f2 == 'c') area_f2 = getAreaCirculo((Circulo*)figura2);
//                 else if (tipo_f2 == 'r') area_f2 = getAreaRetangulo((Retangulo*)figura2);
//                 else if (tipo_f2 == 'l') area_f2 = getAreaLinha((Linha*)figura2);
//                 else if (tipo_f2 == 't') area_f2 = getAreaTexto((Texto*)figura2);

//                 if (area_f1 >= 0.0 && area_f2 >= 0.0) {
//                     if (area_f1 < area_f2) {
//                         areaEsmagadaRound += area_f1;
//                         area_esmagada_total += area_f1;
//                         // printf("  Sobreposição: [%c %d] sobre [%c %d]. Menor área (%.2f) adicionada.\n",
//                         //         tipo_f1, getIDForma(f1), tipo_f2, getIDForma(f2), area_f1);
//                     } else {
//                         areaEsmagadaRound += area_f2;
//                         area_esmagada_total += area_f2;
//                         // printf("  Sobreposição: [%c %d] sobre [%c %d]. Menor área (%.2f) adicionada.\n",
//                         //         tipo_f1, getIDForma(f1), tipo_f2, getIDForma(f2), area_f2);
//                     }
//                 } else {
//                     // printf("  Sobreposição: [%c %d] sobre [%c %d]. Uma das áreas inválida (linha/texto?), não somado.\n",
//                     //             tipo_f1, getIDForma(f1), tipo_f2, getIDForma(f2));
//                 }
//             } 

//             no2 = getProximoNoFila(no2); 
//         } 
//         fprintf(arqTxt,"Área esmagada no Round: %.2f\n", areaEsmagadaRound);
//         atual = getProximoNoFila(atual);
//     } 
//     fprintf(arqTxt, "--- Fim dos Cálculos ---\n");
//     fprintf(arqTxt, "Área total esmagada: %.2f\n\n", area_esmagada_total);
// }