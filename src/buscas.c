#include "buscas.h"

Disparador encontrarDisparadorPorID(Fila disparadores, int id) {
    if (disparadores == NULL) {
        printf("Erro ao procurar o disparador pela ID");
        return NULL;
    }
    int tamanho = getTamanhoFila(disparadores);
    Disparador temp = getPrimeiroConteudoFila(disparadores);
}

Pilha encontrarPilhaPorID(Fila filaPilhas, int idPilha) {
    if (filaPilhas == NULL) {
        printf("fila de pilhas vazia na função encontrar pilha por id\n");
        return NULL;
    }  
}

Forma encontrarFormaPorID(Fila listaDeFormas, int id) {
    if (listaDeFormas == NULL) {
        return NULL;
    }
  
}