#include "formas.h"
#include "disparador.h"

struct pacote{
    Forma fig;
    char tipo;
};

Pacote criarPacote(){
    Pacote pac = malloc(sizeof(struct pacote));
    return pac;
}

void setFormaPacote(Pacote pac, Forma forma){
    pac->fig = forma;
}

Forma getFormaPacote(Pacote pac){
    return pac->fig;
}

void setTipoPacote(Pacote pac, char tipo){
    pac->tipo = tipo;
}

char getTipoPacote(Pacote pac){
    return pac->tipo;
}

double getXPacote(Pacote pac){
    if(pac == NULL){
        printf("Erro ao acessar o pacote em getXPacote\n");
        return -1;
    }  

    switch (pac->tipo){
        case 'r':{
            Retangulo* ret =(Retangulo*)pac->fig;
            return getCoordXRetangulo(ret);
        }
        case 'c':{
            Circulo* cir = (Circulo*)pac->fig;
            return getCoordXCirculo(cir);
        }
        case 'l':{
            Linha* lin = (Linha*)pac->fig;
            return getX1Linha(lin);
        }
        case 't':{
            Texto* txt=(Texto*)pac->fig;
            return getCoordXTexto(txt);
        }
        default:
            return -1;
    }
}

double getYPacote(Pacote pac){
    if(pac == NULL){
        printf("Erro ao buscar a coordenada y da forma");
        return NAN;
    }

    char tipo = getTipoPacote(pac);

    switch (pac->tipo){
        case 'r': {
            Retangulo* ret = (Retangulo*)pac->fig;
            return getCoordYRetangulo(ret);
        }
        case 'c':{
            Circulo* circ = (Circulo*)pac->fig;
            return getCoordYCirculo(circ);
        }
        case 'l':{
            Linha* lin = (Linha*)pac->fig;
            return getY1Linha(lin);
        }
        case 't':{
            Texto* txt = (Texto*)pac->fig;
            return getCoordYTexto(txt);
        }
        default:
            return -1;
    }
}

void escreverConteudoPilha(FILE* arqTxt, Pilha p){
    if(p == NULL || arqTxt == NULL){
        printf("Erro ao abrir arquivos.");
        exit(1);
    }
       
    fprintf(arqTxt, "Conteudo da pilha\n");
    while( != NULL){
        void* cont = getConteudoDoNoPilha(atual);
        if(cont != NULL){
            Forma forma = (Forma)cont;
            
            char tipo = getTipoPacote(forma);
            int id = getIDForma(forma);
            
            void* figura = getFiguraForma(forma);

            if(tipo == 'c'){//círculo
                Circulo* circ = (Circulo*)figura;
                double x = getCoordXCirculo(circ);
                double y = getCoordYCirculo(circ);
                double raio = getRaioCirculo(circ);
                char* corb = getCorBCirculo(circ);
                char* corp = getCorPCirculo(circ);
                fprintf(arqTxt, "círculo id:%i x:%lf y:%lf raio:%lf corb:%s corp:%s\n", id,x,y,raio,corb,corp);
            }else if(tipo == 'r'){
                // retângulo
                Retangulo* ret = (Retangulo*)figura;
                int idRet = getIDRetangulo(ret);
                double CordX = getCoordXRetangulo(ret);
                double CordY = getCoordYRetangulo(ret);
                double w = getWRetangulo(ret);
                double h = getHRetangulo(ret);
                char* corb = getCorBRetangulo(ret);
                char* corp = getCorPRetangulo(ret);
                fprintf(arqTxt, "retângulo id:%i x:%lf y:%lf w:%lf h:%lf corB:%s corP:%s\n",idRet,CordX,CordY,w,h,corb,corp);
            }else if(tipo == 'l'){
                //linha
                Linha* l = (Linha*)figura;
                double x1 = getX1Linha(l);
                double y1 = getY1Linha(l);
                double x2 = getX2Linha(l);
                double y2 = getY2Linha(l);
                char* cor = getCorLinha(l);
                fprintf(arqTxt, "l id:%d x1:%lf y1:%lf x2:%lf y2:%lf cor:%s\n",id,x1,y1,x2,y2,cor);
            }else if(tipo == 't'){
                //texto 
                Texto* t = (Texto*)figura;
                double x = getCoordXTexto(t);
                double y = getCoordYTexto(t);
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

double getAreaPacote(Pacote pac){
    if(pac == NULL){
        printf("Erro ao acessar o pacote para getareaPacote.");
        return 0;
    }

    if(pac->tipo == 'c'){
        //o pacote é um círculo
        Circulo* cir = (Circulo*)pac->fig;
        return getAreaCirculo(cir);
    }else if(pac->tipo == 'r'){
        //o pacote é um retângulo
        Retangulo* ret = (Retangulo*)pac->fig;
        return getAreaRetangulo(ret);
    }else if(pac->tipo == 'l'){
        //o pacote é uma linha
        Linha* lin = (Linha*)pac->fig;
        return getAreaLinha(lin);
    }else if(pac->tipo == 't'){
        //o pacote é um texto
        Texto* t = (Texto*)pac->fig;
        return getAreaTexto(t);
    }else{
        return 0.0;
    }
}

void posicionaPacote(Pacote pac, Disparador d, double deslocX, double deslocY){
    if(pac == NULL || d == NULL){
        printf("Erro ao acessar o pacote ou o disparador para posicionar na arena.");
        exit(1);
    }
    double XD = getXDisparador(d);
    double YD = getYDisparador(d);

    double dx = XD + deslocX;
    double dy = YD + deslocY;

    char tipoForma = pac->tipo;
    Forma figura = pac->fig;
    if(figura == NULL){
        printf("Erro ao acessar a figura na função posicionaForma em formas.c\n");
        return;
    }

    if(tipoForma == 'c'){//Circulo
        Circulo* circ = (Circulo*)figura;
        setXCirculo(circ,dx);
        setYCirculo(circ,dy);
        printf("Circulo movido para %lf em x e %lf em y\n",dx,dy);
    }else if(tipoForma == 'r'){//Retangulo
        Retangulo* ret = (Retangulo*)figura;
        setCoordXRetangulo(ret, dx);
        setCoordYRetangulo(ret, dy);
        printf("Retangulo movido para %lf em x e %lf em y\n", dx,dy);
    }else if(tipoForma == 'l'){//Linha
        Linha* l = (Linha*)figura;
        double x1_antigo = getX1Linha(l);
        double y1_antigo = getY1Linha(l);
        double x2_antigo = getX2Linha(l);
        double y2_antigo = getY2Linha(l);

        double deltaX = dx - x1_antigo;
        double deltaY = dy - y1_antigo;

        double x1_novo = x1_antigo + deltaX; 
        double y1_novo = y1_antigo + deltaY; 
        double x2_novo = x2_antigo + deltaX;
        double y2_novo = y2_antigo + deltaY;

        setX1Linha(l, x1_novo);
        setY1Linha(l, y1_novo);
        setX2Linha(l, x2_novo);
        setY2Linha(l, y2_novo);
        printf("Linha movida para :%lf em x1 ,%lf em y1,%lf em x2,%lf em y2\n",x1_novo,y1_novo,x2_novo,y2_novo);
    }else if(tipoForma == 't'){//Texto
        Texto* text =(Texto*)figura;
        setXTexto(text, dx);
        setYTexto(text, dy);
        printf("Texto movido para %lf em x e %lf em y\n",dx,dy);
    }

}

void liberaFormaPacote(Pacote pac){
    if(pac == NULL){
        printf("Erro ao liberar o pacote em formas.c\n");
        return;
    }

    if(pac->tipo == 'c'){
        liberaCirculo((Circulo*)pac->fig);
    }else if(pac->tipo == 'r'){
        liberaRetangulo((Retangulo*)pac->fig);
    }else if(pac->tipo == 'l'){
        liberaLinha((Linha*)pac->fig);
    }else if(pac->tipo == 't'){
        liberaTexto((Texto*)pac->fig);
    }
}

void freePacote(Pacote pac){
    liberaFormaPacote(pac);
    free(pac);    
}