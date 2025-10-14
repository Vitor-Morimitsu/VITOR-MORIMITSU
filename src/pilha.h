#ifndef PILHA_H
#define PILHA_H

#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

/*
    Arquivo .h relacionado a criação e uso de uma pilha, a qual segue o princípio LIFO(last in first out), ou seja, o último elemento que entra, é o primeiro a sair.
*/

typedef void* Pilha;
typedef void* Conteudo;
typedef void* Fila;

/// @brief Cria e retorna uma pilha vazia
/// @return Pilha vazia
Pilha criarPilha();

/// @brief Insere os n primeiros elementos da fila na pilha
/// @param p Pilha p
/// @param n Conteudo n
void carregarPilhaPelaFila(Pilha p, Fila f, int n);

/// @brief Remove a celula do inicio da pilha
/// @param p Pilha p
void removerPilha(Pilha p);

/// @brief Retorna o conteúdo da célula no início da pilha
/// @param p Pilha p
/// @return Conteúdo da primeira célula
Conteudo getConteudoPilha(Pilha p);

/// @brief Retorna o tamanho da pilha
/// @param p Pilha
/// @return Tamanho da pilha
int getTamanhoPilha(Pilha p);

/// @brief Libera memória da pilha
/// @param p Pilha 
void liberarMemoriaPilha(Pilha p);

#endif      