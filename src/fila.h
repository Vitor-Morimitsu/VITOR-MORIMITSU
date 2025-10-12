#ifndef FILA_H
#define FILA_H

#include <stdio.h>
#include <stdlib.h>
#include "disparador.h"
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
void insereFila(Fila f, Forma form, char type);

/// @brief Remove o primeiro elemento da fila
/// @param f Fila
void removeFila(Fila f);

/// @brief Mostra o primeiro elemento da fila
/// @param f Fila
Forma getPrimeiraFormaFila(Fila f);

/// @brief Libera a memória ocupada pela fila
/// @param f Fila
void liberarFila(Fila* f);

#endif