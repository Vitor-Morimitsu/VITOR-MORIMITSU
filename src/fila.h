#ifndef FILA_H
#define FILA_H

#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"
#include "disparador.h"
#include "carregador.h"

/*
    Arquivo .h criado com o intuito de criar uma fila no primeiro trabalho de estrutura de dados.
    A fila segue o princípio FIFO(first in, first out) cujo o primeiro elemento a entrar, também é o primeiro a sair
*/

typedef void* Fila;
typedef void* Forma;
typedef void* Disparador;

/// @brief Cria uma fila vazia
/// @return Ponteiro para a fila criada
Fila criarFila();

/// @brief Insere um elemento na fila
/// @param f Fila
/// @param form Forma a ser inserida
void insereFila(Fila f, Forma forma);

/// @brief Remove o primeiro elemento da fila
/// @param f Fila
void removeFila(Fila f);

/// @brief Mostra o primeiro elemento da fila
/// @param f Fila
Forma getPrimeiroConteudoFila(Fila f);

/// @brief Retorna o tamanho da fila
/// @param f Fila
/// @return Tamanho da fila
int getTamanhoFila(Fila f);

/// @brief Encontra e retorna um disparador específico
/// @param disparadores Fila dos disparadores
/// @param id Id do disparador
/// @return Disparador com o mesmo id passado por parametro
Disparador encontrarDisparadorPorId(Fila disparadores,int id);

/// @brief Encontra e retorna um carreagador específico
/// @param carregadores Fila dos carregadores
/// @param id Id do carregador
/// @return Carregador com o mesmo id passado por parametro
Carregador encontrarCarregadorPorId(Fila carregadores, int id);


#endif