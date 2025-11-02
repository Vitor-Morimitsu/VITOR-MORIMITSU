#include "criarTxt.h"
#include "printSvg.h"

void comandoLc(FILE* arqTxt, Pilha p){
    if(arqTxt == NULL || p == NULL){
        printf("Erro realizar o comando Lc no txt\n");
        return;
    }
    
    fprintf(arqTxt, "Conteúdo da pilha:\n");
    while(getTamanhoPilha(p) > 0){
        Pacote pac = getPacoteTopoPilha(p);
        if(pac != NULL){

            Forma forma = getFormaPacote(pac);
            char tipoPac = getTipoPacote(pac);
            if(tipoPac == 'c'){
                fprintf(arqTxt, "Circulo com id:%d\n", getIDCirculo((Circulo)forma));            
            }else if(tipoPac == 'r'){
                fprintf(arqTxt, "Retângulo com id:%d\n", getIDRetangulo((Retangulo)forma));          
            }else if(tipoPac == 'l'){
                fprintf(arqTxt, "Linha com id:%d\n", getIDLinha((Linha)forma));           
            }else if(tipoPac == 't'){
                fprintf(arqTxt, "Texto com id:%d\n", getIDTexto((Texto)forma));            
            }
        }
        removerPilha(p);
    }
}

void comandoShft(FILE* arqTxt, int idDis, Fila filaDisparadores){
    if(arqTxt == NULL){
        return;
    }

    Disparador disp = encontrarDisparadorPorId(filaDisparadores, idDis);
    if(disp == NULL){
        fprintf(arqTxt, "Disparador ID %d não encontrado.\n", idDis);
        return;
    }

    Pacote centro = getConteudoCentro(disp);
    
    fprintf(arqTxt, "Estado do disparador %d após shft:\n", idDis);
    
    if(centro == NULL){
        fprintf(arqTxt, "  Posição de disparo: VAZIA\n");
    }else{
        char tipo = getTipoPacote(centro);
        Forma forma = getFormaPacote(centro);
        int id = getIdForma(forma, tipo);
        
        const char* nomeTipo = (tipo == 'c') ? "Círculo" : 
                               (tipo == 'r') ? "Retângulo" : 
                               (tipo == 'l') ? "Linha" : "Texto";
        
        fprintf(arqTxt, "  Posição de disparo: %s (ID: %d)\n", nomeTipo, id);
    }
    
    // Mostra estado dos carregadores
    Carregador ce = getCarregadorDisparador(disp, 'e');
    Carregador cd = getCarregadorDisparador(disp, 'd');
    
    if(ce != NULL){
        Pilha pe = getPilhaCarregador(ce);
        fprintf(arqTxt, "  Carregador esquerdo: %d formas\n", getTamanhoPilha(pe));
    }
    
    if(cd != NULL){
        Pilha pd = getPilhaCarregador(cd);
        fprintf(arqTxt, "  Carregador direito: %d formas\n", getTamanhoPilha(pd));
    }
    
    fprintf(arqTxt, "\n");
}

void comandoDsp(FILE* arqTxt, Fila chao, double dx, double dy){
    if(arqTxt == NULL){
        printf("Erro ao acessar o arquivo txt.");
        return;
    }
    
    // Pega a última forma adicionada na arena (chão)
    Pacote pac = (Pacote)getPrimeiroConteudoFila(chao);
    if(pac == NULL){
        fprintf(arqTxt, "Nenhuma forma foi disparada.\n");
        return;
    }

    double xFinal = getXPacote(pac);
    double yFinal = getYPacote(pac);
    double x2Final = -1;
    double y2Final = -1;
    
    char* nomeFigura = "desconhecida";
    char tipo = getTipoPacote(pac);
    Forma forma = getFormaPacote(pac);
    
    if(tipo == 'c'){
        nomeFigura = "círculo";
    }else if(tipo == 'r'){
        nomeFigura = "retângulo";
    }else if(tipo == 'l'){
        nomeFigura = "linha";
        Linha* lin = (Linha*)forma;
        xFinal = getX1Linha(lin);
        yFinal = getY1Linha(lin);
        x2Final = getX2Linha(lin);
        y2Final = getY2Linha(lin);
    }else if(tipo == 't'){
        nomeFigura = "texto";
    }

    if(tipo == 'l'){
        fprintf(arqTxt, "Forma disparada: %s | Deslocamento: dx=%.2lf dy=%.2lf | Posição final: X1=%.2lf Y1=%.2lf X2=%.2lf Y2=%.2lf\n", 
                nomeFigura, dx, dy, xFinal, yFinal, x2Final, y2Final);
    }else{
        fprintf(arqTxt, "Forma disparada: %s | Deslocamento: dx=%.2lf dy=%.2lf | Posição final: X=%.2lf Y=%.2lf\n", 
                nomeFigura, dx, dy, xFinal, yFinal);
    }
}

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

void comandoCalc(FILE* arqTxt,FILE* svg, Fila chao) {
    if (arqTxt == NULL || chao == NULL) {
        printf("Erro: Arquivo Txt ou Fila 'chao' nulos no comando calc.\n");
        return; 
    }

    double area_esmagada_total = 0.0;
    int tamanhoFila = getTamanhoFila(chao);
    
    fprintf(arqTxt, "\n=== Cálculo das Sobreposições ===\n");
    fprintf(arqTxt, "Total de formas na arena: %d\n\n", tamanhoFila);

    // Percorre todas as formas comparando com as seguintes
    for(int i = 0; i < tamanhoFila; i++) {
        double areaEsmagadaRound = 0.0;
        
        // Cria clone para pegar a forma i
        Fila clone1 = clonarFilaChao(chao);
        
        // Avança até a forma i
        for(int skip = 0; skip < i; skip++) {
            removeFila(clone1);
        }
        
        Pacote p1 = getPrimeiroConteudoFila(clone1);
        if(p1 == NULL) {
            liberarClone(clone1);
            break;
        }
        
        char tipo_p1 = getTipoPacote(p1);
        Forma f1 = getFormaPacote(p1);
        int id1 = getIdForma(f1, tipo_p1);
        
        // Compara com todas as formas seguintes (j > i)
        for(int j = i + 1; j < tamanhoFila; j++) {
            Fila clone2 = clonarFilaChao(chao);
            
            // Avança até a forma j
            for(int skip = 0; skip < j; skip++) {
                removeFila(clone2);
            }
            
            Pacote p2 = getPrimeiroConteudoFila(clone2);
            if(p2 == NULL) {
                liberarClone(clone2);
                break;
            }
            
            char tipo_p2 = getTipoPacote(p2);
            Forma f2 = getFormaPacote(p2);
            int id2 = getIdForma(f2, tipo_p2);
            
            // Verifica sobreposição usando a função genérica
            int sobrepoe = formasSobrepoem(p1, p2);
            
            if (sobrepoe == 1) {
                double area_f1 = getAreaPacote(p1);
                double area_f2 = getAreaPacote(p2);
                
                if (area_f1 >= 0.0 && area_f2 >= 0.0) {
                    double menorArea = (area_f1 < area_f2) ? area_f1 : area_f2;
                    areaEsmagadaRound += menorArea;
                    area_esmagada_total += menorArea;
                    
                    // Marca com asterisco a forma de menor área (esmagada)
                    if(svg != NULL){
                        if(area_f1 < area_f2){
                            // Calcula centro da forma 1
                            double xCentro = getXPacote(p1);
                            double yCentro = getYPacote(p1);
                            
                            if(tipo_p1 == 'r'){
                                Retangulo* ret = (Retangulo*)f1;
                                xCentro += getWRetangulo(ret) / 2.0;
                                yCentro += getHRetangulo(ret) / 2.0;
                            }
                            // Círculo já retorna o centro em getXPacote/getYPacote
                            
                            printAsterisco(svg, xCentro, yCentro);
                        }else{
                            // Calcula centro da forma 2
                            double xCentro = getXPacote(p2);
                            double yCentro = getYPacote(p2);
                            
                            if(tipo_p2 == 'r'){
                                Retangulo* ret = (Retangulo*)f2;
                                xCentro += getWRetangulo(ret) / 2.0;
                                yCentro += getHRetangulo(ret) / 2.0;
                            }
                            
                            printAsterisco(svg, xCentro, yCentro);
                        }
                    }
                    
                    fprintf(arqTxt, "Sobreposição detectada: [%c:%d] x [%c:%d] | Área esmagada: %.2lf\n",
                            tipo_p1, id1, tipo_p2, id2, menorArea);
                } else {
                    fprintf(arqTxt, "Sobreposição detectada: [%c:%d] x [%c:%d] | Área inválida (linha/texto)\n",
                            tipo_p1, id1, tipo_p2, id2);
                }
            }
            
            liberarClone(clone2);
        }
        
        if(areaEsmagadaRound > 0.0) {
            fprintf(arqTxt, "  → Área esmagada no Round %d: %.2lf\n\n", i+1, areaEsmagadaRound);
        }
        
        liberarClone(clone1);
    }
    
    fprintf(arqTxt, "=== Resultado Final ===\n");
    fprintf(arqTxt, "Área total esmagada: %.2lf\n\n", area_esmagada_total);
}