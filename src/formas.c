#include "texto.h"
#include "formas.h"
#include "disparador.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include <string.h>

void liberaTexto(Texto t);

typedef struct{
    Forma fig;
    char tipo;
}stPacote;

Pacote criarPacote(){
    stPacote* pac = (stPacote*)malloc(sizeof(stPacote));
    return pac;
}

int getIdForma(Forma f, char tipo){
    if(f == NULL) return -1;
    if(tipo == 'c') return getIDCirculo((Circulo)f);
    else if(tipo == 'r') return getIDRetangulo((Retangulo)f);
    else if(tipo == 'l') return getIDLinha((Linha)f);
    else if(tipo == 't') return getIDTexto((Texto)f);

    return -1;
}

void setFormaPacote(Pacote pac, Forma forma){
    stPacote* p = (stPacote*)pac;
    p->fig = forma;
}

Forma getFormaPacote(Pacote pac){
    stPacote* p = (stPacote*)pac;
    return p->fig;
}

void setTipoPacote(Pacote pac, char tipo){
    stPacote* p = (stPacote*)pac;
    p->tipo = tipo;
}

char getTipoPacote(Pacote pac){
    stPacote* p = (stPacote*)pac;
    return p->tipo;
}

double getXPacote(Pacote pac){
    if(pac == NULL){
        printf("Erro ao acessar o pacote em getXPacote\n");
        return -1;
    }  
    stPacote* p = (stPacote*)pac;

    switch (p->tipo){
        case 'r':{
            Retangulo* ret =(Retangulo*)p->fig;
            return getCoordXRetangulo(ret);
        }
        case 'c':{
            Circulo* cir = (Circulo*)p->fig;
            return getCoordXCirculo(cir);
        }
        case 'l':{
            Linha* lin = (Linha*)p->fig;
            return getX1Linha(lin);
        }
        case 't':{
            Texto* txt=(Texto*)p->fig;
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
    stPacote* p = (stPacote*)pac;
    char tipo = getTipoPacote(pac);

    switch (p->tipo){
        case 'r': {
            Retangulo* ret = (Retangulo*)p->fig;
            return getCoordYRetangulo(ret);
        }
        case 'c':{
            Circulo* circ = (Circulo*)p->fig;
            return getCoordYCirculo(circ);
        }
        case 'l':{
            Linha* lin = (Linha*)p->fig;
            return getY1Linha(lin);
        }
        case 't':{
            Texto* txt = (Texto*)p->fig;
            return getCoordYTexto(txt);
        }
        default:
            return -1;
    }
}

double getAreaPacote(Pacote pac){
    if(pac == NULL){
        printf("Erro ao acessar o pacote para getareaPacote.");
        return 0;
    }
    stPacote* p = (stPacote*)pac;

    if(p->tipo == 'c'){
        //o pacote é um círculo
        Circulo* cir = (Circulo*)p->fig;
        return getAreaCirculo(cir);
    }else if(p->tipo == 'r'){
        //o pacote é um retângulo
        Retangulo* ret = (Retangulo*)p->fig;
        return getAreaRetangulo(ret);
    }else if(p->tipo == 'l'){
        //o pacote é uma linha
        Linha* lin = (Linha*)p->fig;
        return getAreaLinha(lin);
    }else if(p->tipo == 't'){
        //o pacote é um texto
        Texto* t = (Texto*)p->fig;
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

    stPacote* p = (stPacote*)pac;
    char tipoForma = p->tipo;
    Forma figura = p->fig;
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

    stPacote* p = (stPacote*)pac;
    if(p->tipo == 'c'){
        liberaCirculo((Circulo*)p->fig);
    }else if(p->tipo == 'r'){
        liberaRetangulo((Retangulo*)p->fig);
    }else if(p->tipo == 'l'){
        liberaLinha((Linha*)p->fig);
    }else if(p->tipo == 't'){
        liberaTexto((Texto*)p->fig);
    }
}

void freePacote(Pacote pac){
    liberaFormaPacote(pac);
    free(pac);    
}
char*
 getCorPreenchimentoPacote(Pacote pac){
    if(pac == NULL) return NULL;
    
    stPacote* p = (stPacote*)pac;
    
    if(p->tipo == 'c'){
        return getCorPCirculo((Circulo)p->fig);
    }else if(p->tipo == 'r'){
        return getCorPRetangulo((Retangulo)p->fig);
    }else if(p->tipo == 't'){
        return getCorPTexto((Texto)p->fig);
    }
    
    return NULL; //linha não tem cor de preenchimento
}

void mudarCorBordaPacote(Pacote pac, char* novaCor){
    if(pac == NULL || novaCor == NULL) return;
    
    stPacote* p = (stPacote*)pac;
    
    //aloca memória para a nova cor
    char* corCopia = (char*)malloc(strlen(novaCor) + 1);
    strcpy(corCopia, novaCor);
    
    if(p->tipo == 'c'){
        setCorBCirculo((Circulo)p->fig, corCopia);
    }else if(p->tipo == 'r'){
        setCorBRetangulo((Retangulo)p->fig, corCopia);
    }else if(p->tipo == 't'){
        setCorBTexto((Texto)p->fig, corCopia);
    }else if(p->tipo == 'l'){
        setCorLinha((Linha)p->fig, corCopia);
    }
}

Pacote clonarPacoteComCoresInvertidas(Pacote pac){
    if(pac == NULL) return NULL;
    
    stPacote* p = (stPacote*)pac;
    Pacote novoPac = criarPacote();
    setTipoPacote(novoPac, p->tipo);
    
    if(p->tipo == 'c'){
        Circulo* orig = (Circulo*)p->fig;
        char* corb = getCorBCirculo(orig);
        char* corp = getCorPCirculo(orig);
        
        //cria novo círculo com cores invertidas
        Circulo novo = criaCirculo(
            getIDCirculo(orig),
            getCoordXCirculo(orig),
            getCoordYCirculo(orig),
            getRaioCirculo(orig),
            corp,  //borda = preenchimento original
            corb   //preenchimento = borda original
        );
        setFormaPacote(novoPac, (Forma)novo);
        
    }else if(p->tipo == 'r'){
        Retangulo* orig = (Retangulo*)p->fig;
        char* corb = getCorBRetangulo(orig);
        char* corp = getCorPRetangulo(orig);
        
        //cria novo retângulo com cores invertidas
        Retangulo novo = criaRetangulo(
            getIDRetangulo(orig),
            getCoordXRetangulo(orig),
            getCoordYRetangulo(orig),
            getWRetangulo(orig),
            getHRetangulo(orig),
            corp,  //borda = preenchimento original
            corb   //preenchimento = borda original
        );
        setFormaPacote(novoPac, (Forma)novo);
        
    }else if(p->tipo == 't'){
        Texto* orig = (Texto*)p->fig;
        char* corb = getCorBTexto(orig);
        char* corp = getCorPTexto(orig);
        
        //cria novo texto com cores invertidas
        Texto novo = criarTexto(
            getIDTexto(orig),
            getCoordXTexto(orig),
            getCoordYTexto(orig),
            corp,  //borda = preenchimento original
            corb,  //preenchimento = borda original
            getATexto(orig),
            getTxtoTexto(orig)
        );
        
        //copia o estilo se existir
        Estilo est = getEstiloTexto(orig);
        if(est != NULL){
            setEstiloTexto(novo, est);
        }
        
        setFormaPacote(novoPac, (Forma)novo);
        
    }else if(p->tipo == 'l'){
        //linha não tem cores invertidas (só tem uma cor)
        //retorna uma cópia simples
        Linha* orig = (Linha*)p->fig;
        Linha nova = criarLinha(
            getIDLinha(orig),
            getX1Linha(orig),
            getY1Linha(orig),
            getX2Linha(orig),
            getY2Linha(orig),
            getCorLinha(orig)
        );
        setFormaPacote(novoPac, (Forma)nova);
    }
    
    return novoPac;
}
