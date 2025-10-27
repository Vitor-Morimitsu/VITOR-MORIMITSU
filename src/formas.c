#include "formas.h"
#include "disparador.h"

typedef struct forma{
    int id;
    void* fig;
    char tipo;
}stForma;

Forma criaRetanguloForma(int i, char tipo,double x, double y, double w, double h, char* corb, char* corp){
    stForma* f = malloc(sizeof(stForma));
    if(f == NULL){
        printf("Erro ao alocar memória para a nova forma.");
        return NULL;
    }
    f->id = i;
    f->fig = criaRetangulo(i,x,y,w,h,corb,corp);
    f->tipo = 'r';

    return f;
}

Forma criaCirculoForma(int i, char tipo,double x, double y, double r, char* corb, char* corp){
    stForma* f = malloc(sizeof(stForma));
    if(f == NULL){
        printf("Erro ao alocar memória para a nova forma.");
        return NULL;
    }

    f->id = i;
    f->fig = criaCirculo(i,x,y,r,corb,corp);
    f->tipo = 'c';

    return f;
}

Forma criaLinhaForma(int i, char tipo,double x1, double y1, double x2, double y2, char* cor){
    stForma* f = malloc(sizeof(stForma));
    if(f == NULL){
        printf("Erro ao alocar memória para a nova forma.");
        return NULL;
    }

    f->id = i;
    f->fig = criarLinha(i,x1,y1,x2,y2,cor);
    f->tipo = 'l';

    return f;
}

Forma criaTextoForma(int i,char tipo, double x, double y, char* corb, char* corp, char a, char* txto, Estilo ts){
    stForma* f = malloc(sizeof(stForma));
    if(f == NULL){
        printf("Erro ao alocar memória para a nova forma.");
        return NULL;
    }

    f->id = i;
    f->fig = criarTexto(i,x,y,corb,corp,a,txto,ts);
    f->tipo = 't';

    return f;
}

int getIDForma(Forma f) {
    if (f == NULL) {
        printf("Erro ao buscar a ID da forma");
        return -1;
    }

    stForma* formaWrapper = (stForma*)f;

    switch (formaWrapper->tipo) {
        case 'r': {
            Retangulo ret = (Retangulo*)formaWrapper->fig;
            return getIDRetangulo(ret); 
        }
        case 'c': {
            Circulo circ = (Circulo*)formaWrapper->fig;
            return getIDCirculo(circ); 
        }
        case 'l': {
            Linha lin = (Linha*)formaWrapper->fig;
            return getIDLinha(lin);
        }
        case 't': {
            Texto txt = (Texto*)formaWrapper->fig;
            return getIDTexto(txt);
        }
        default:
            // Tipo de forma desconhecido
            return -1; 
    }
}

char getTipoForma(Forma f){
    if(f == NULL){
        printf("Não existe nada no centro do carregador\n");
        return 'n';
    } 
    stForma* forma = (stForma*)f;
    return forma->tipo;
}

double getXForma(Forma f){
    if(f == NULL){
        printf("Erro ao buscar a coordenada X da forma.");
        return NAN;
    }

    stForma* tipoForma = (stForma*)f;

    switch (tipoForma->tipo){
        case 'r':{
            Retangulo* ret =(Retangulo*)tipoForma->fig;
            return getCoordXRetangulo(ret);
        }
        case 'c':{
            Circulo* cir = (Circulo*)tipoForma->fig;
            return getCoordXCirculo(cir);
        }
        case 'l':{
            Linha* lin = (Linha*)tipoForma->fig;
            return getX1Linha(lin);
        }
        case 't':{
            Texto* txt=(Texto*)tipoForma->fig;
            return getCoordXTexto(txt);
        }
        default:
            return -1;
    }
}
double getYForma(Forma f){
    if(f == NULL){
        printf("Erro ao buscar a coordenada y da forma");
        return NAN;
    }

    stForma* tipoForma = (stForma*)f;
    switch (tipoForma->tipo){
        case 'r': {
            Retangulo* ret = (Retangulo*)tipoForma->fig;
            return getCoordYRetangulo(ret);
        }
        case 'c':{
            Circulo* circ = (Circulo*)tipoForma->fig;
            return getCoordYCirculo(circ);
        }
        case 'l':{
            Linha* lin = (Linha*)tipoForma->fig;
            return getY1Linha(lin);
        }
        case 't':{
            Texto* txt = (Texto*)tipoForma->fig;
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
    NoPilha_t atual = getNoTopoPilha(p);  
    fprintf(arqTxt, "Conteudo da pilha\n");
    while(atual != NULL){
        void* cont = getConteudoDoNoPilha(atual);
        if(cont != NULL){
            Forma forma = (Forma)cont;
            
            char tipo = getTipoForma(forma);
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

void* getFiguraForma(Forma f){
    return ((stForma*)f)->fig;
}

double getAreaForma(Forma f){
    if(f == NULL){
        printf("Erro ao acessar a forma.");
        return 0;
    }

    stForma* forma = (stForma*)f;
    if(forma->tipo == 'c'){
        //a forma é um círculo
        Circulo* cir = (Circulo*)forma->fig;
        return getAreaCirculo(cir);
    }else if(forma->tipo == 'r'){
        //a forma é um retângulo
        Retangulo* ret = (Retangulo*)forma->fig;
        return getAreaRetangulo(ret);
    }else if(forma->tipo == 'l'){
        //é uma linha
        Linha* lin = (Linha*)forma->fig;
        return getAreaLinha(lin);
    }else if(forma->tipo == 't'){
        //é um texto
        Texto* t = (Texto*)forma->fig;
        return getAreaTexto(t);
    }else{
        return 0.0;
    }
}

void liberarForma(void* f){
    if (f == NULL){
      printf("erro ao liberar a forma em forma.c\n");
      return;  
    } 
    Forma forma = (Forma)f;
    void* figura = getFiguraForma(forma);
    if (figura != NULL) free(figura); 
    free(forma); 
}

void posicionaForma(Forma f, Disparador d, double deslocX, double deslocY){
    if(f == NULL || d == NULL){
        printf("Erro ao acessar a figura para posicionar na arena.");
        exit(1);
    }
    double XD = getXDisparador(d);
    double YD = getYDisparador(d);

    double dx = XD + deslocX;
    double dy = YD + deslocY;

    char tipoForma = getTipoForma(f);
    void* figura = getFiguraForma(f);
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