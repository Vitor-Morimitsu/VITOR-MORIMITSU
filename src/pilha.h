#ifndef PILHA_H
#define PILHA_H

#include <stdio.h>
#include <stdlib.h>
#include "fila.h"



/*
    Arquivo .h relacionado a criação e uso de uma pilha, a qual segue o princípio LIFO(last in first out), ou seja, o último elemento que entra, é o primeiro a sair.
*/

typedef void* Pilha;
typedef void* NoPilha_t;
typedef void (*DestruidorConteudo)(void* conteudo);

/// @brief Cria e retorna uma pilha vazia
/// @return Pilha vazia
Pilha criarPilha(int d);

/// @brief Insere um conteúdo no topo da pilha
/// @param p Pilha
/// @param conteudo Conteudo a ser inserido
void inserirPilha(Pilha p, void* conteudo);

/// @brief Remove a celula do inicio da pilha
/// @param p Pilha p
void* removerPilha(Pilha p);

/// @brief Retorna o conteúdo da célula no início da pilha
/// @param p Pilha p
/// @return Conteúdo da primeira célula
void* getConteudoPilha(Pilha p);

/// @brief Retorna o identificador da pilha
/// @param p Pilha
/// @return Identificador da pilha
int getIDPilha(Pilha p);

/// @brief Retorna o tamanho da pilha
/// @param p Pilha
/// @return Tamanho da pilha
int getTamanhoPilha(Pilha p);

/// @brief Retorna a nó do topo da pilha
/// @param p Pilha
/// @return Nó do topo
NoPilha_t getNoTopoPilha(Pilha p);

/// @brief Retorna o próximo nó da pilha
/// @param p Pilha
/// @return Próximo nó da pilha
NoPilha_t getProximoNoPilha(NoPilha_t no);

/// @brief Retorna o conteúdo do nó da pilha
/// @param p Pilha
/// @return Conteúdo do nó da pilha
void* getConteudoDoNoPilha(NoPilha_t p);

/// @brief Libera toda a memória associada à pilha, incluindo nós e conteúdo.
/// @param p A pilha a ser liberada.
/// @param destruir Ponteiro para a função que sabe como liberar o 'conteudo' de cada nó (ex: // free, liberarForma).
void liberarMemoriaPilha(Pilha p, DestruidorConteudo destruir);
#endif      