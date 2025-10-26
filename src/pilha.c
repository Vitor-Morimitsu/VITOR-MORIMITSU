#include "pilha.h"
#include "fila.h"
typedef struct stcelula{
    void* conteudo;
    struct stcelula *prox;
}stCelula;
typedef struct stpilha{
    int id;
    stCelula *topo;
    int tamanho;
}stPilha;

Pilha criarPilha(int ID){
    stPilha* p = (stPilha*)malloc(sizeof(stPilha));
    if(p == NULL){
        printf("Erro ao alocar memória para a Pilha");
        exit(1);
    }
    p->id = ID;
    p->tamanho = 0;
    p->topo = NULL;
    return p;
}

void inserirPilha(Pilha p, void* conteudo){
    if(p == NULL){
        printf("Erro ao acessar a pilha.");
        return;
    }
    stPilha* pilha = (stPilha*)p;

    stCelula* novaCelula = (stCelula*)malloc(sizeof(stCelula));
    if(novaCelula == NULL){
        printf("Erro ao acessar a nova celula criada");
        return;
    }
    novaCelula->conteudo = conteudo;
    novaCelula->prox = pilha->topo;
    pilha->topo = novaCelula;
    pilha->tamanho++;
}

// void escreverConteudoPilha(FILE* arqTxt, Pilha p){
//     if(p == NULL || arqTxt == NULL){
//         printf("erro ao acessar os parametros para printar o conteudo da pilha\n");
//     }

//     stPilha* pilha =(stPilha*)p;
//     if(pilha == NULL || pilha->topo == NULL){
//         return NULL;
//     }        

//     stCelula* atual = pilha->topo;
//     void* conteudo = atual->conteudo;

//     while(atual != NULL){



//         atual = atual->prox;
//     }

    
// }

void* removerPilha(Pilha p){
    stPilha* pilha = (stPilha*)p;
    if(pilha == NULL||pilha->topo == NULL){
        return NULL;
    }

    stCelula* temp = pilha->topo;
    void* conteudo = temp->conteudo;

    pilha->topo = pilha->topo->prox;
    free(temp);
    pilha->tamanho--;

    return conteudo;
}

void* getConteudoPilha(Pilha p){
    if(p == NULL){
        printf("Erro ao acessar o conteúdo da pilha");
        return NULL;
    }

    stPilha* pilha = (stPilha*)p;
    if(pilha != NULL && pilha->topo != NULL){
        return pilha->topo->conteudo;
    }else{
        return NULL;
    }
}

int getIDPilha(Pilha p){
    if(p == NULL){
        printf("Erro ao acessar a pilha pela função getIDPilha.\n");
        return -1;
    }
    stPilha* pilha = (stPilha*)p;
    return pilha->id;
}

int getTamanhoPilha(Pilha p){
    if(p == NULL){
        printf("Erro ao acessar o tamanho da pilha.");
        return 0;
    }

    stPilha* pilha = (stPilha*)p;
    return pilha->tamanho;
}

NoPilha_t getNoTopoPilha(Pilha p) {
    if (p == NULL) return NULL;
    stPilha* pilha = (stPilha*)p;
    return (NoPilha_t)pilha->topo; 
}

NoPilha_t getProximoNoPilha(NoPilha_t no) {
    if (no == NULL) return NULL;
    stCelula* celula_interna = (stCelula*)no; 
    return (NoPilha_t)celula_interna->prox;
}

void* getConteudoDoNoPilha(NoPilha_t no) {
    if (no == NULL) return NULL;
    stCelula* celula_interna = (stCelula*)no;
    return celula_interna->conteudo;
}

void liberarMemoriaPilha(Pilha p){
    if (p == NULL) {
        return;
    }

    stPilha* pilha = (stPilha*)p;
    stCelula* atual = pilha->topo;
 
    while (atual != NULL) {
        stCelula* temp = atual;
        atual = atual->prox;

        free(temp); 
    }
    free(pilha); 
}