#include "buscas.h"

Disparador encontrarDisparadorPorID(Fila disparadores, int id) {
    if (disparadores == NULL) {
        printf("Erro ao procurar o disparador pela ID");
        return NULL;
    }
    int tamanho = getTamanhoFila(disparadores);
    Disparador temp;
}

Pilha encontrarPilhaPorID(Fila filaPilhas, int idPilha) {
    if (filaPilhas == NULL) {
        printf("fila de pilhas vazia na função encontrar pilha por id\n");
        return NULL;
    }

    for(No_t no = getPrimeiroNoFila(filaPilhas); no != NULL; no = getProximoNoFila(no)) {
        void* conteudo = getConteudoDoNoFila(no);
        if (conteudo == NULL) continue;

        Pilha p = (Pilha)conteudo;

        if (getIDPilha(p) == idPilha){
            return p; 
        }
    }
    return NULL; 
}

Forma encontrarFormaPorID(Fila listaDeFormas, int id) {
    if (listaDeFormas == NULL) {
        return NULL;
    }
    for (No_t no = getPrimeiroNoFila(listaDeFormas); no != NULL; no = getProximoNoFila(no)) {
        Forma f = getConteudoDoNoFila(no);
        int idForma = getIDForma(f);
        
        if(idForma == id){
            return f;
        }        
    }
    return NULL; 
}