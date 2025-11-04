#include "colisoes.h"

int circuloSobrepoeCirculo(Pacote pac1, Pacote pac2){
    if(pac1 == NULL || pac2 == NULL){
        printf("Erro ao acessar as formas.");
        return -1;
    }

    Circulo* c1 = getFormaPacote(pac1);
    Circulo* c2 = getFormaPacote(pac2);

    double x1 = getCoordXCirculo(c1); 
    double y1 = getCoordYCirculo(c1);
    double r1 = getRaioCirculo(c1);

    double x2 = getCoordXCirculo(c2);
    double y2 = getCoordYCirculo(c2);
    double r2 = getRaioCirculo(c2);

    //ver se as figuras se sobrepõem
    double dx = x1 - x2;
    double dy = y1 - y2;
    double distanciaEntreCentros = sqrt(dx * dx + dy * dy);
    
    if(distanciaEntreCentros <= (r1+r2)){//figuras se sobrepõem
        return 1;
    }else{//as figura não se sobrepõem
        return 0;
    }
}

int circuloSobrepoeRetangulo(Pacote pac1, Pacote pac2){
    if(pac1 == NULL || pac2 == NULL){
        printf("Erro ao acessar as figuras.");
        return -1;
    }

    Circulo* c = (Circulo*)getFormaPacote(pac1);
    Retangulo* r = (Retangulo*)getFormaPacote(pac2);

    double xc = getCoordXCirculo(c);
    double yc = getCoordYCirculo(c);
    double raio = getRaioCirculo(c);

    double xr = getCoordXRetangulo(r);
    double yr = getCoordYRetangulo(r);
    double comp = getWRetangulo(r);
    double h = getHRetangulo(r);

    //pontos do retângulo mais próximos do centro do círculo
    double pontoRetMaisProximoX = fmax(xr, fmin(xc, xr + comp));
    double pontoRetMaisProximoY = fmax(yr, fmin(yc, yr + h));

    //diferenças nos eixos
    double dx = xc - pontoRetMaisProximoX;
    double dy = yc - pontoRetMaisProximoY;
    
    double distancia = sqrt(dx*dx + dy*dy);

    if(distancia <= raio){//as formas se sobrepõem
        return 1;
    }else{//não se sobrepõem
        return 0;
    }
}

int circuloSobrepoeLinha(Pacote pac1, Pacote pac2){
    if(pac1 == NULL || pac2 == NULL){
        printf("Erro ao acessar as formas passadas.\n");
        return -1; 
    }

    Circulo* c = (Circulo*)getFormaPacote(pac1);
    Linha* l = (Linha*)getFormaPacote(pac2);

    double xc = getCoordXCirculo(c);
    double yc = getCoordYCirculo(c);
    double raio = getRaioCirculo(c);

    double x1l = getX1Linha(l);
    double x2l = getX2Linha(l);
    double y1l = getY1Linha(l);
    double y2l = getY2Linha(l);

    double dx_segmento = x2l - x1l;
    double dy_segmento = y2l - y1l;
    double comprimentoSegmentoQuadrado = (dx_segmento * dx_segmento) + (dy_segmento * dy_segmento);

    if(comprimentoSegmentoQuadrado < 0.0000001){
        double dx = xc - x1l;
        double dy = yc - y1l;
        double distanciaQuadrada = dx * dx + dy * dy;
        return (distanciaQuadrada <= raio * raio) ? 1 : 0;
    }
    double t = ((xc - x1l) * dx_segmento + (yc - y1l) * dy_segmento) / comprimentoSegmentoQuadrado;

    double t_limitado = fmax(0.0, fmin(1.0, t));

    double pontoMaisProximoX = x1l + t_limitado * dx_segmento;
    double pontoMaisProximoY = y1l + t_limitado * dy_segmento;

    double dx_centro_prox = xc - pontoMaisProximoX;
    double dy_centro_prox = yc - pontoMaisProximoY;
    double distanciaQuadrada = (dx_centro_prox * dx_centro_prox) + (dy_centro_prox * dy_centro_prox);

    if (distanciaQuadrada <= (raio * raio)) {
        return 1; //sobrepõe
    } else {
        return 0; //não sobrepõe
    }
}

int circuloSobrepoeTexto(Pacote pac1, Pacote pac2){
    if(pac1 == NULL || pac2 == NULL){
        printf("Erro ao acessar as formas passadas.");
        return -1;
    }

    Circulo* c = (Circulo*)getFormaPacote(pac1);
    Texto* t = (Texto*)getFormaPacote(pac2);

    double xc = getCoordXCirculo(c);
    double yc = getCoordYCirculo(c);
    double raio = getRaioCirculo(c);

    double x1t,x2t,y1t,y2t;
    int comprimentoTxt = quantidadeLetras(t);
    if(comprimentoTxt <= 0) return 0;
    char ancora = getATexto(t);
    if(ancora == 'i'){
        x1t = getCoordXTexto(t);
        y1t = getCoordYTexto(t);
        x2t = x1t + 10*comprimentoTxt;
        y2t = y1t;
    }else if(ancora == 'f'){
        double xa = getCoordXTexto(t);
        double ya = getCoordYTexto(t);

        x1t = xa - 10*comprimentoTxt;
        y1t = ya;

        x2t = xa;
        y2t = ya;
    }else if(ancora == 'm'){
        double xa = getCoordXTexto(t);
        double ya = getCoordYTexto(t);

        x1t = xa - (10*comprimentoTxt)/2;
        y1t = ya;
        
        x2t = xa + (10*comprimentoTxt)/2;
        y2t = ya;
    }

    double dx_segmento = x2t - x1t;
    double dy_segmento = y2t - y1t; 
    double comprimentoSegmentoQuadrado = (dx_segmento * dx_segmento) + (dy_segmento * dy_segmento);

    if(comprimentoSegmentoQuadrado < 0.000001) {
        double dx = xc - x1t;
        double dy = yc - y1t;
        double distanciaQuadrada = dx * dx + dy * dy;
        return (distanciaQuadrada <= raio * raio) ? 1 : 0;
    }

    double z = ((xc - x1t) * dx_segmento + (yc - y1t) * dy_segmento) / comprimentoSegmentoQuadrado;

    double t_limitado = fmax(0.0, fmin(1.0, z));

    double pontoMaisProximoX = x1t + t_limitado * dx_segmento;
    double pontoMaisProximoY = y1t + t_limitado * dy_segmento;

    double dx_centro_prox = xc - pontoMaisProximoX;
    double dy_centro_prox = yc - pontoMaisProximoY;
    double distanciaQuadrada = (dx_centro_prox * dx_centro_prox) + (dy_centro_prox * dy_centro_prox);

    if (distanciaQuadrada <= (raio * raio)) {
        return 1; //sobrepõe
    } else {
        return 0; //não sobrepõe
    }    
}

int retanguloSobrepoeLinha(Pacote pac1, Pacote pac2) {
    if (pac1 == NULL || pac2 == NULL) {
        printf("Erro ao acessar as formas passadas.");
        return 0;
    }

    Retangulo* retangulo = (Retangulo*)getFormaPacote(pac1);
    Linha* linha = (Linha*)getFormaPacote(pac2);

    double retanguloX = getCoordXRetangulo(retangulo);
    double retanguloY = getCoordYRetangulo(retangulo);
    double retanguloLargura = getWRetangulo(retangulo);
    double retanguloAltura = getHRetangulo(retangulo);
    double retanguloDireita = retanguloX + retanguloLargura; 
    double retanguloBaixo = retanguloY + retanguloAltura; 

    double linhaX1 = getX1Linha(linha);
    double linhaY1 = getY1Linha(linha);
    double linhaX2 = getX2Linha(linha);
    double linhaY2 = getY2Linha(linha);

    double vetorLinhaX = linhaX2 - linhaX1;
    double vetorLinhaY = linhaY2 - linhaY1;

    //teste para ver se a borda superior é sobrposta pela linha
    {
        double bordaInicioX = retanguloX;
        double bordaInicioY = retanguloY;
        double vetorBordaX = retanguloDireita - retanguloX; 
        double vetorBordaY = 0; 
        
        double denominador = (-vetorBordaX * vetorLinhaY + vetorLinhaX * vetorBordaY);

        if (fabs(denominador) > 0.000001) {
            double parametroBorda_s = (-vetorLinhaY * (linhaX1 - bordaInicioX) + vetorLinhaX * (linhaY1 - bordaInicioY)) / denominador;
            
            double parametroLinha_t = ( vetorBordaX * (linhaY1 - bordaInicioY) - vetorBordaY * (linhaX1 - bordaInicioX)) / denominador;

            if (parametroBorda_s >= 0 && parametroBorda_s <= 1 && parametroLinha_t >= 0 && parametroLinha_t <= 1) {
                return 1; 
            }
        }
    }

    {
        double bordaInicioX = retanguloX;
        double bordaInicioY = retanguloBaixo;
        double vetorBordaX = retanguloDireita - retanguloX; 
        double vetorBordaY = 0;
        double denominador = (-vetorBordaX * vetorLinhaY + vetorLinhaX * vetorBordaY);

        if (fabs(denominador) > 0.000001) {
            double parametroBorda_s = (-vetorLinhaY * (linhaX1 - bordaInicioX) + vetorLinhaX * (linhaY1 - bordaInicioY)) / denominador;
            double parametroLinha_t = ( vetorBordaX * (linhaY1 - bordaInicioY) - vetorBordaY * (linhaX1 - bordaInicioX)) / denominador;
            if (parametroBorda_s >= 0 && parametroBorda_s <= 1 && parametroLinha_t >= 0 && parametroLinha_t <= 1) {
                return 1; 
            }
        }
    } 

    {
        double bordaInicioX = retanguloX;
        double bordaInicioY = retanguloY;
        double vetorBordaX = 0;      
        double vetorBordaY = retanguloBaixo - retanguloY; 
        double denominador = (-vetorBordaX * vetorLinhaY + vetorLinhaX * vetorBordaY);

        if (fabs(denominador) > 0.000001) {
            double parametroBorda_s = (-vetorLinhaY * (linhaX1 - bordaInicioX) + vetorLinhaX * (linhaY1 - bordaInicioY)) / denominador;
            double parametroLinha_t = ( vetorBordaX * (linhaY1 - bordaInicioY) - vetorBordaY * (linhaX1 - bordaInicioX)) / denominador;
            if (parametroBorda_s >= 0 && parametroBorda_s <= 1 && parametroLinha_t >= 0 && parametroLinha_t <= 1) {
                return 1; 
            }
        }
    } 

    {
        double bordaInicioX = retanguloDireita;
        double bordaInicioY = retanguloY;
        double vetorBordaX = 0; 
        double vetorBordaY = retanguloBaixo - retanguloY;    
        double denominador = (-vetorBordaX * vetorLinhaY + vetorLinhaX * vetorBordaY);

        if (fabs(denominador) > 0.000001) {
            double parametroBorda_s = (-vetorLinhaY * (linhaX1 - bordaInicioX) + vetorLinhaX * (linhaY1 - bordaInicioY)) / denominador;
            double parametroLinha_t = ( vetorBordaX * (linhaY1 - bordaInicioY) - vetorBordaY * (linhaX1 - bordaInicioX)) / denominador;
            if (parametroBorda_s >= 0 && parametroBorda_s <= 1 && parametroLinha_t >= 0 && parametroLinha_t <= 1) {
                return 1; 
            }
        }
    } 

    int ponto1Dentro = (linhaX1 >= retanguloX && linhaX1 <= retanguloDireita &&
                        linhaY1 >= retanguloY && linhaY1 <= retanguloBaixo);
    int ponto2Dentro = (linhaX2 >= retanguloX && linhaX2 <= retanguloDireita &&
                        linhaY2 >= retanguloY && linhaY2 <= retanguloBaixo);

    if (ponto1Dentro || ponto2Dentro) {
       return 1; 
    }

    return 0;
}

int retanguloSobrepoeRetangulo(Pacote pac1, Pacote pac2){
    if(pac1 == NULL || pac2 == NULL){
        printf("Erro ao acessar as formas passadas.");
        return -1;
    }
    Retangulo* r1 = (Retangulo*)getFormaPacote(pac1);
    Retangulo* r2 = (Retangulo*)getFormaPacote(pac2);

    //dados r1 
    double r1_x1 = getCoordXRetangulo(r1);
    double r1_y1 = getCoordYRetangulo(r1);
    double r1_w = getWRetangulo(r1);
    double r1_h = getHRetangulo(r1);
    double r1_x2 = r1_x1 + r1_w; 
    double r1_y2 = r1_y1 + r1_h; 

    //dados r2
    double r2_x1 = getCoordXRetangulo(r2);
    double r2_y1 = getCoordYRetangulo(r2);
    double r2_w = getWRetangulo(r2);
    double r2_h = getHRetangulo(r2);
    double r2_x2 = r2_x1 + r2_w; 
    double r2_y2 = r2_y1 + r2_h; 

    if (r1_x2 < r2_x1) {
        return 0; 
    }
   
    if (r1_x1 > r2_x2) {
        return 0; 
    }
  
    if (r1_y2 < r2_y1) {
        return 0; 
    }
    
    if (r1_y1 > r2_y2) {
        return 0; 
    }

    //nenhuma das condições de separação foi atendida, logo eles se sobrepõem
    return 1;
}

int retanguloSobrepoeTexto(Pacote pac1, Pacote pac2){
    if(pac1 == NULL || pac2 == NULL){
        printf("Erro ao acessar as formas passadas.");
        return -1;
    }

    Retangulo* r = (Retangulo*)getFormaPacote(pac1);
    Texto* t = (Texto*)getFormaPacote(pac2);

    //dados do retangulo
    double xRet = getCoordXRetangulo(r);
    double yRet = getCoordYRetangulo(r);
    double wRet = getWRetangulo(r);
    double hRet = getHRetangulo(r);
    double x2Ret = xRet + wRet;
    double y2Ret = yRet + hRet;

    //dados do texto
    double x2Text, y2Text, yText, xText;
    char* txt = getTxtoTexto(t);
    double comprimentoLinha = 10*strlen(txt);
    char ancora = getATexto(t);
    if(ancora == 'i'){
        xText = getCoordXTexto(t);
        yText = getCoordYTexto(t);
        x2Text = xText + comprimentoLinha;
        y2Text = yText;
    }else if(ancora == 'f'){
        xText = getCoordXTexto(t) - comprimentoLinha;
        yText = getCoordYTexto(t);
        x2Text = getCoordXTexto(t);
        y2Text = yText;
    }else if(ancora == 'm'){
        double xa = getCoordXTexto(t);
        yText = getCoordYTexto(t);

        xText = xa - comprimentoLinha/2;
        x2Text = xa + comprimentoLinha/2;
        y2Text = yText;
    }

    //casos de não sobreposição
    if(xRet > x2Text){//retangulo está depois do texto
        return 0;
    }

    if(x2Ret < xText){//retangulo está antes do texto
        return 0;
    }

    if(yRet > y2Text){//retangulo está em baixo do texto
        return 0;    
    }

    if(y2Ret < yText){//retangulo está em cima do texto
        return 0;    
    }

    return 1;
}

int linhaSobrepoeLinha(Pacote pac1, Pacote pac2){
    if(pac1 == NULL || pac2 == NULL){
        printf("Erro ao acessar as formas passadas.");
        return 0;
    }

    Linha* l1 = (Linha*)getFormaPacote(pac1);
    Linha* l2 = (Linha*)getFormaPacote(pac2);

    //dados linha 1
    double p0_x = getX1Linha(l1);
    double p0_y = getY1Linha(l1);
    double p1_x = getX2Linha(l1);
    double p1_y = getY2Linha(l1);

    //dados linha 2 
    double p2_x = getX1Linha(l2);
    double p2_y = getY1Linha(l2);
    double p3_x = getX2Linha(l2);
    double p3_y = getY2Linha(l2);

    double s1_x = p1_x - p0_x;
    double s1_y = p1_y - p0_y;

    double s2_x = p3_x - p2_x;
    double s2_y = p3_y - p2_y;

    double denominador = (-s2_x * s1_y + s1_x * s2_y);

    if (fabs(denominador) < 0.000001) {
        return 0;
    }

    double s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / denominador;
    double t = ( s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / denominador;

    if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
        return 1;// as linhas se cruzam.
    }

    return 0; //não se cruzam
}

int linhaSobrepoeTexto(Pacote pac1, Pacote pac2){
    if(pac1 == NULL || pac2 == NULL){
        printf("Erro ao acessar as formas passadas.");
        return -1;
    }

    Linha* l = (Linha*)getFormaPacote(pac1);
    Texto* t = (Texto*)getFormaPacote(pac2);

    //dados linha
    double p0_x = getX1Linha(l);
    double p0_y = getY1Linha(l);
    double p1_x = getX2Linha(l);
    double p1_y = getY2Linha(l);

    //dados texto 
    double x1Texto, x2Texto, yTexto;
    char* txt = getTxtoTexto(t);
    double comprimentoLinha = 10 * strlen(txt);
    char ancora = getATexto(t);
    
    if(ancora == 'i'){
        x1Texto = getCoordXTexto(t);
        yTexto = getCoordYTexto(t);
        x2Texto = x1Texto + comprimentoLinha;
    }else if(ancora == 'f'){
        x2Texto = getCoordXTexto(t);
        yTexto = getCoordYTexto(t);
        x1Texto = x2Texto - comprimentoLinha;
    }else if(ancora == 'm'){
        double xa = getCoordXTexto(t);
        yTexto = getCoordYTexto(t);
        x1Texto = xa - comprimentoLinha / 2;
        x2Texto = xa + comprimentoLinha / 2;
    }

    double p2_x = x1Texto;
    double p2_y = yTexto;
    double p3_x = x2Texto;
    double p3_y = yTexto;

    //interseção de segmentos
    double s1_x = p1_x - p0_x;
    double s1_y = p1_y - p0_y;
    double s2_x = p3_x - p2_x;
    double s2_y = 0;  //linha do texto é horizontal

    double denominador = (-s2_x * s1_y + s1_x * s2_y);

    if (fabs(denominador) < 0.000001) {
        //linhas paralelas
        return 0;
    }

    double s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / denominador;
    double t_param = (s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / denominador;

    if (s >= 0 && s <= 1 && t_param >= 0 && t_param <= 1) {
        return 1;  //linhas se cruzam
    }

    return 0;
}

int textoSobrepoeTexto(Pacote pac1, Pacote pac2){
    if(pac1 == NULL || pac2 == NULL){
        printf("Erro ao acessar as formas passadas.");
        return -1;
    }

    Texto* t1 = (Texto*)getFormaPacote(pac1);
    Texto* t2 = (Texto*)getFormaPacote(pac2);

    //dados do texto 1
    double x1_t1, x2_t1, y_t1;
    char* txt1 = getTxtoTexto(t1);
    double comprimentoLinha1 = 10 * strlen(txt1);
    char ancora1 = getATexto(t1);
    
    if(ancora1 == 'i'){
        x1_t1 = getCoordXTexto(t1);    
        y_t1 = getCoordYTexto(t1);
        x2_t1 = x1_t1 + comprimentoLinha1;
    }else if(ancora1 == 'f'){
        x2_t1 = getCoordXTexto(t1);
        y_t1 = getCoordYTexto(t1);
        x1_t1 = x2_t1 - comprimentoLinha1;
    }else if(ancora1 == 'm'){
        double xa1 = getCoordXTexto(t1);
        y_t1 = getCoordYTexto(t1);
        x1_t1 = xa1 - comprimentoLinha1 / 2;  
        x2_t1 = xa1 + comprimentoLinha1 / 2;  
    }

    //dados do texto 2
    double x1_t2, x2_t2, y_t2;
    char* txt2 = getTxtoTexto(t2);
    double comprimentoLinha2 = 10 * strlen(txt2);
    char ancora2 = getATexto(t2);
    
    if(ancora2 == 'i'){
        x1_t2 = getCoordXTexto(t2);
        y_t2 = getCoordYTexto(t2);
        x2_t2 = x1_t2 + comprimentoLinha2;
    }else if(ancora2 == 'f'){
        x2_t2 = getCoordXTexto(t2);
        y_t2 = getCoordYTexto(t2);
        x1_t2 = x2_t2 - comprimentoLinha2;
    }else if(ancora2 == 'm'){
        double xa2 = getCoordXTexto(t2);
        y_t2 = getCoordYTexto(t2);
        x1_t2 = xa2 - comprimentoLinha2 / 2;  
        x2_t2 = xa2 + comprimentoLinha2 / 2;  
    }


    if (fabs(y_t1 - y_t2) > 0.000001) {
        return 0;  //não estão na mesma linha horizontal
    }

    //lógica de sobreposição no eixo X
    if (x2_t1 <= x1_t2) {
        return 0;  //t1 à esquerda de t2
    }
    
    if (x1_t1 >= x2_t2) {
        return 0;  //t1 à direita de t2
    }

    return 1;  //se sobrepõem
}

int formasSobrepoem(Pacote pac1, Pacote pac2){
    if(pac1 == NULL || pac2 == NULL){
        printf("Erro ao acessar as formas passadas.");
        return -1;
    }
    char tipoF1 = getTipoPacote(pac1);
    char tipoF2 = getTipoPacote(pac2);

    if(tipoF1 == 'c'){
        if(tipoF2 == 'c'){
            return circuloSobrepoeCirculo(pac1,pac2);            
        }else if(tipoF2 == 'r'){
            return circuloSobrepoeRetangulo(pac1,pac2);
        }else if(tipoF2 == 'l'){
            return circuloSobrepoeLinha(pac1,pac2);
        }else if(tipoF2 == 't'){
            return circuloSobrepoeTexto(pac1,pac2);
        }
    }else if(tipoF1 == 'r'){
        if(tipoF2 == 'c'){
            return circuloSobrepoeRetangulo(pac2,pac1);
        }else if(tipoF2 == 'r'){
            return retanguloSobrepoeRetangulo(pac1,pac2);
        }else if(tipoF2 == 'l'){
            return retanguloSobrepoeLinha(pac1,pac2);
        }else if(tipoF2 == 't'){
            return retanguloSobrepoeTexto(pac1,pac2);
        }
    }else if(tipoF1 == 'l'){
        if(tipoF2 == 'c'){
            return circuloSobrepoeLinha(pac2,pac1);
        }else if(tipoF2 == 'r'){
            return retanguloSobrepoeLinha(pac2,pac1);
        }else if(tipoF2 == 'l'){
            return linhaSobrepoeLinha(pac1,pac2);
        }else if(tipoF2 == 't'){
            return linhaSobrepoeTexto(pac1,pac2);
        }
    }else if(tipoF1 == 't'){
        if(tipoF2 == 'c'){
            return circuloSobrepoeTexto(pac2, pac1);
        }else if(tipoF2 == 'r'){
            return retanguloSobrepoeTexto(pac2,pac1);
        }else if(tipoF2 == 'l'){
            return linhaSobrepoeTexto(pac2,pac1);
        }else if(tipoF2 == 't'){
            return textoSobrepoeTexto(pac1,pac2);
        }
    }

    return -1;
}