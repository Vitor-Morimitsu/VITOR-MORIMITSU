#ifndef CHAO_H
#define CHAO_H

#include <stdio.h>
#include <stdlib.h>
#include "disparador.h"
#include "fila.h"
/*
    Arquivo .h criado com o intuito de ser o chão do jogo de bocha geométrica.
    O chão é uma fila, ou seja, segue o princípio FIFO(first in, first out) cujo o primeiro elemento a entrar, também é o primeiro a sair
*/

typedef void* Fila;
typedef void* Forma;

/// @brief Cria uma fila vazia
/// @return Ponteiro para a fila criada
Fila* criarChao();

/// @brief Insere um elemento na fila
/// @param f Fila
/// @param form Forma a ser inserida
void insereChao(Fila* f, Forma* form);

/// @brief Remove o primeiro elemento da fila
/// @param f Fila
void removeChao(Fila* f);

/// @brief Mostra o primeiro elemento da fila
/// @param f Fila
Forma getPrimeiroElementoChao(Fila* f);

/// @brief Libera a memória ocupada pela fila
/// @param f Fila
void liberarChao(Fila* f);

#endif