#ifndef PILHA_H
#define PILHA_H

#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include "formas.h"



/*
    Arquivo .h relacionado a criação e uso de uma pilha, a qual segue o princípio LIFO(last in first out), ou seja, o último elemento que entra, é o primeiro a sair.
*/

typedef void* Pilha;
typedef void* Forma;

/// @brief Cria e retorna uma pilha vazia
/// @return Pilha vazia
Pilha criarPilha();

/// @brief Insere um conteúdo no topo da pilha
/// @param p Pilha
/// @param conteudo Conteudo a ser inserido
void inserirPilha(Pilha p, Forma forma);

/// @brief Remove a celula do inicio da pilha
/// @param p Pilha p
void removerPilha(Pilha p);

/// @brief Retorna o conteúdo da célula no início da pilha
/// @param p Pilha p
/// @return Conteúdo da primeira célula
 Forma getFormaTopoPilha(Pilha p);

/// @brief Retorna o tamanho da pilha
/// @param p Pilha
/// @return Tamanho da pilha
int getTamanhoPilha(Pilha p);

/// @brief Libera a memória de uma pilha
/// @param p Pilha
void destruirPilha(Pilha p);
#endif      