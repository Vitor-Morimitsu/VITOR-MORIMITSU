#include "buscas.h"

Disparador encontrarDisparadorPorID(Fila filaDeDisparadores, int id) {
    if (filaDeDisparadores == NULL) {
        return NULL;
    }
    for (No_t no = getPrimeiroNoFila(filaDeDisparadores); no != NULL; no = getProximoNoFila(no)) {
        Disparador d = (Disparador)getConteudoDoNoFila(no);
        if (getIDDisparador(d) == id) {
            return d; 
        }
    }
    return NULL; 
}

Pilha encontrarPilhaPorID(Fila listaDePilhas, int id) {
    if (listaDePilhas == NULL) {
        return NULL;
    }
    for (No_t no = getNoTopoPilha(listaDePilhas); no != NULL; no = getProximoNoPilha(no)) {
        Conteudo p = getConteudoDoNoPilha(no);
        if (getIDPilha(p) == id) {
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