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
    if(f == NULL) return;
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

void liberarForma(Forma f){
    if(f == NULL){
        return; 
    }

    stForma* formaWrapper = (stForma*)f;

    switch (formaWrapper->tipo) {
        case 'r':
            liberaRetangulo(formaWrapper->fig);
            break;
        case 'c':
            liberaCirculo(formaWrapper->fig);
            break;
        case 'l':
            liberaLinha(formaWrapper->fig);
            break;
        case 't':
            liberaTexto(formaWrapper->fig);
            break;
    }

    free(formaWrapper);
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
    stForma* forma = (stForma*)f;

    if(forma->tipo == 'c'){//Circulo
        setXCirculo((Circulo*)forma->fig,dx);
        setYCirculo((Circulo*)forma->fig,dy);
    }else if(forma->tipo == 'r'){//Retangulo
        setCoordXRetangulo((Retangulo*)forma->fig, dx);
        setCoordYRetangulo((Retangulo*)forma->fig, dy);
    }else if(forma->tipo == 'l'){//Linha
        setX1Linha((Linha*)forma->fig,dx);
        setY1Linha((Linha*)forma->fig,dy);
    }else if(forma->tipo == 't'){//Texto
        setXTexto((Texto*)forma->fig, dx);
        setYTexto((Texto*)forma->fig, dy);
    }

}