#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include "disparador.h"
#include "formas.h"
typedef struct stNo {
    void* conteudo;
    char type;
    struct stNo* prox;
} stNo;
typedef struct stFila {
    stNo* primeiro;
    stNo* ultimo;
    int tamanho;
} stFila;

Fila criarFila() {
    stFila* f = (stFila*)malloc(sizeof(stFila));
    if (f == NULL) {
        perror("Erro ao alocar memória para a fila");
        return NULL; 
    }

    f->primeiro = NULL;
    f->ultimo = NULL;
    f->tamanho = 0;
    return f;
}

void insereFila(Fila f,void* conteudo, char type) {
    stFila* fila = (stFila*)f;

    stNo* novoNo = (stNo*)malloc(sizeof(stNo));
    if (novoNo == NULL) {
        printf("Erro ao alocar memória para o novo nó");
        exit(1);
    }
    
    novoNo->conteudo = conteudo;
    novoNo->type = type;
    novoNo->prox = NULL;

    if (fila->primeiro == NULL) {
        fila->primeiro = novoNo;
        fila->ultimo = novoNo;
    } else {
        fila->ultimo->prox = novoNo;
        fila->ultimo = novoNo;
    }
    fila->tamanho++;
    
}

void insereFilaDisparadores(Fila FilaDisparadores, void* d){
    if(FilaDisparadores == NULL || d == NULL){
        printf("Erro ao acessar e inserir um disparador na fila de disparadores.");
        exit(1);
    }

    insereFila(FilaDisparadores,(void*)d,'d');

}

void removeFila(Fila f) {
    stFila* fila = (stFila*)f;
    
    if (fila == NULL || fila->primeiro == NULL) {
        return; 
    }
    
    stNo* temp = fila->primeiro;
    fila->primeiro = fila->primeiro->prox;
    free(temp);
    fila->tamanho--;

    if (fila->primeiro == NULL) {
        fila->ultimo = NULL;
    }
}


Forma getPrimeiraFormaFila(Fila f) {
    stFila* fila = (stFila*)f;

    if (fila == NULL || fila->primeiro == NULL) {
        return NULL;
    }
    
    return fila->primeiro->conteudo;
}

void liberarFilaComConteudo(Fila f, DestruidorConteudo destruir) {
    stFila* fila = (stFila*)f;
    if (fila == NULL) return;

    stNo* atual = fila->primeiro;
    while (atual != NULL) {
        stNo* temp = atual;
        atual = atual->prox;

        // --- A LINHA ESSENCIAL QUE FALTA NA SUA liberarFila ---
        if (destruir != NULL && temp->conteudo != NULL) {
            destruir(temp->conteudo); // Chama free() ou freeDisparador() no conteúdo
        }
        // --- Fim da linha essencial ---

        free(temp); // Libera o nó
    }
    free(fila); // Libera a fila
}
No_t getPrimeiroNoFila(Fila f) {
    stFila* fila = (stFila*)f;
    return fila->primeiro;
}

No_t getProximoNoFila(No_t no) {
    if (no == NULL) return NULL;
    stNo* no_interno = (stNo*)no; 
    return no_interno->prox;
}

Forma getConteudoDoNoFila(No_t no) {
    if (no == NULL) return NULL;
    stNo* no_interno = (stNo*)no;
    return no_interno->conteudo;
}

char getTipoDoNoFila(No_t no) {
    if (no == NULL) return '\0';
    stNo* no_interno = (stNo*)no;
    return no_interno->type;
}

int getTamanhoFila(Fila f){
    if(f == NULL){
        printf("Erro ao acessar a fila.");
        return -1;
    }

    stFila* fila = (stFila*)f;
    return fila->tamanho;
}

Forma percorreFila(Fila f, int posicao){
    if(f == NULL){
        printf("Fila vazia.");
        return NULL;
    }
    if(posicao < 0){
        printf("Posição negativa passada como parâmetro.");
        return NULL;
    }

    No_t noAtual = getPrimeiroNoFila(f);

    for(int i = 0;i<posicao;i++){
        noAtual = getProximoNoFila(noAtual);
    }

    if(noAtual == NULL){
        printf("Posição inválida.");
        return NULL;
    }

    return getConteudoDoNoFila(noAtual);
}

void liberarTudo( Fila disparadores, Fila carregadores, Fila arena){
    liberarFilaComConteudo(disparadores,free);
    liberarFilaComConteudo(carregadores,free);
    liberarFilaComConteudo(arena, free);
}

// void printarFilaTxt(Fila fila, FILE* arqTxt){
//     if(fila == NULL || arqTxt == NULL){
//         printf("Erro ao printar o conteúdo da fila no arquivo txt.");
//         exit(1);
//     }

//     No_t atual = getPrimeiroNoFila(fila);
//     fprintf(arqTxt, "conteúdo da fila: \n");
//     while (atual != NULL) {
//         // Pega o conteúdo genérico (void*)
//         void* conteudo = getConteudoDoNoFila(atual);
//         // Pega o tipo do nó
//         char tipoNo = getTipoDoNoFila(atual);

//         // Verifica o tipo e faz o cast apropriado
//         if (tipoNo == 'c') {
//             Circulo* c = (Circulo*)conteudo;
//             // Assumindo que você tem funções como getIDCirculo, etc.
//             fprintf(arqTxt, "  Tipo: Círculo | ID: %d | Centro: (%.2f, %.2f) | Raio: %.2f | CorB: %s | CorP: %s\n",
//                     getIDCirculo(c),
//                     getCoordXCirculo(c),
//                     getCoordYCirculo(c),
//                     getRaioCirculo(c),
//                     getCorBCirculo(c),
//                     getCorPCirculo(c));

//         } else if (tipoNo == 'r') {
//             Retangulo* r = (Retangulo*)conteudo;
//             fprintf(arqTxt, "  Tipo: Retângulo | ID: %d | Pos: (%.2f, %.2f) | W: %.2f | H: %.2f | CorB: %s | CorP: %s\n",
//                     getIDRetangulo(r),
//                     getCoordXRetangulo(r),
//                     getCoordYRetangulo(r),
//                     getWRetangulo(r),
//                     getHRetangulo(r),
//                     getCorBRetangulo(r),
//                     getCorPRetangulo(r));

//         } else if (tipoNo == 'l') {
//             Linha* l = (Linha*)conteudo;
//             fprintf(arqTxt, "  Tipo: Linha | ID: %d | P1: (%.2f, %.2f) | P2: (%.2f, %.2f) | Cor: %s\n",
//                     getIDLinha(l),
//                     getX1Linha(l),
//                     getY1Linha(l),
//                     getX2Linha(l),
//                     getY2Linha(l),
//                     getCorLinha(l));

//         } else if (tipoNo == 't') {
//             Texto* t = (Texto*)conteudo;
//             fprintf(arqTxt, "  Tipo: Texto | ID: %d | Pos: (%.2f, %.2f) | CorB: %s | CorP: %s | Âncora: %c | Texto: \"%s\"\n",
//                     getIDTexto(t),
//                     getCoordXTexto(t),
//                     getCoordYTexto(t),
//                     getCorBTexto(t),
//                     getCorPTexto(t),
//                     getATexto(t), // Assumindo que getATexto retorna a âncora
//                     getTxtoTexto(t));

//         } else if (tipoNo == 'd') { // Assumindo 'd' para Disparador
//             Disparador* d = (Disparador*)conteudo;
//             // Assumindo funções get para Disparador
//             fprintf(arqTxt, "  Tipo: Disparador | ID: %d | Pos: (%lf, %lf)\n", // Adicione mais infos se necessário
//                     getIDDisparador(d),
//                     getXDisparador(d), // Exemplo, adapte
//                     getYDisparador(d)); // Exemplo, adapte

//         } else {
//             // Tipo desconhecido
//             fprintf(arqTxt, "  Tipo: Desconhecido ('%c') | Endereço: %p\n", tipoNo, conteudo);
//         }

//         // Avança para o próximo nó
//         atual = getProximoNoFila(atual);
//     }
//     fprintf(arqTxt, "Fim da Fila.\n");
// }

