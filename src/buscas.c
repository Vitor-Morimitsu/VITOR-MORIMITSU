#include "buscas.h"

Disparador encontrarDisparadorPorID(Fila listaDeDisparadores, int id) {
    if (listaDeDisparadores == NULL) {
        return NULL;
    }
    for (No_t no = getPrimeiroNo(listaDeDisparadores); no != NULL; no = getProximoNo(no)) {
        Disparador d = (Disparador)getConteudoDoNo(no);
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
    for (No_t no = getPrimeiroNo(listaDePilhas); no != NULL; no = getProximoNo(no)) {
        Pilha p = (Pilha)getConteudoDoNo(no);
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
    for (No_t no = getPrimeiroNo(listaDeFormas); no != NULL; no = getProximoNo(no)) {
        Forma f = (Forma)getConteudoDoNo(no);
        
        Forma* base = (Forma*)f; 
        
        if (base == id) {
            return f; 
        }
    }
    return NULL; 
}