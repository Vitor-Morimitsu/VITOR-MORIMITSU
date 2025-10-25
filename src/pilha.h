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

/// @brief Cria e retorna uma pilha vazia
/// @return Pilha vazia
Pilha criarPilha(int d);

/// @brief Insere um conteúdo no topo da pilha
/// @param p Pilha
/// @param conteudo Conteudo a ser inserido
void inserirPilha(Pilha p, void* conteudo);

// /// @brief Insere os n primeiros elementos da fila na pilha
// /// @param p Pilha p
// /// @param f Fila
// /// @param n Quantidade de elementos da fila a serem inseridos na pilha
// void carregarPilhaPelaFila(Pilha p, Fila f, int n);

// /// @brief Reportar os dados de cada uma das formas carregadas
// /// @param arqTxt Arquivo destino
// /// @param p Pilha
// void escreverConteudoPilha(FILE* arqTxt, Pilha p);

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

/// @brief Libera memória da pilha.
/// @param p Pilha
void liberarMemoriaPilha(Pilha p);
#endif      