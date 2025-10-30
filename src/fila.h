#ifndef FILA_H
#define FILA_H

#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"
//#include "disparador.h"
//#include "formas.h"

/*
    Arquivo .h criado com o intuito de criar uma fila no primeiro trabalho de estrutura de dados.
    A fila segue o princípio FIFO(first in, first out) cujo o primeiro elemento a entrar, também é o primeiro a sair
*/

typedef void* Fila;
typedef void* Forma;

/// @brief Cria uma fila vazia
/// @return Ponteiro para a fila criada
Fila criarFila();

/// @brief Insere um elemento na fila
/// @param f Fila
/// @param form Forma a ser inserida
void insereFila(Fila f, Pacote pac);

/// @brief Insere um disparador na fila de disparadores
/// @param FilaDisparadores Fila de disparadores
/// @param d Disparador a ser inserido
void insereFilaDisparadores(Fila FilaDisparadores, void* d);        

/// @brief Remove o primeiro elemento da fila
/// @param f Fila
void removeFila(Fila f);

/// @brief Mostra o primeiro elemento da fila
/// @param f Fila
Forma getPrimeiroConteudoFila(Fila f);

/// @brief Libera a memória ocupada pela fila
/// @param f Fila
void liberarFilaComConteudo(Fila f);

/// @brief Retorna o tamanho da fila
/// @param f Fila
/// @return Tamanho da fila
int getTamanhoFila(Fila f);

#endif