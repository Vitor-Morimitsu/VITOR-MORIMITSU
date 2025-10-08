#ifndef DISPARADOR_H
#define DISPARADOR_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

/*
    Arquivo .h destinado à criação de um disparador e suas operações de uso no primeiro trabalho de estrutura de dados
*/

typedef void* Disparador;
typedef void* Pilha;
typedef void* Celula;
typedef void* Botao;


/// @brief Cria e retorna o disparador
/// @param i Identificador do disparador
/// @param esquerda Carregador esquerdo
/// @param direita Carregador direito
/// @param disparador Disparador responsável por atirar as formas na arena
/// @param bEsquerdo Botão esquerdo
/// @param bDireito Botão direito
/// @return Disparador criado
Disparador* criarDisparador(int i, Pilha* esquerda, Pilha* direita,Botao* disparador, Botao* bEsquerdo, Botao* bDireito);

/// @brief Retorna o identificador do disparador
/// @return Identificador
int getIDDisparador(Disparador* d);

/// @brief Retorna o primeiro conteúdo do carregador esquerdo
/// @return Primeiro conteúdo do carregador esquerdo
Celula getConteudoCarEsq(Disparador* d);

/// @brief Retorna o primeiro conteúdo do carregador direito
/// @return Primeiro conteúdo do carregador direito
Celula getConteudpCarDir(Disparador* d);

/// @brief Define o identificador
/// @param i Identificador do disparador
void setIDDisparador(Disparador* d, int i);

#endif