#ifndef DISPARADOR_H
#define DISPARADOR_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "formas.h"

/*
    Arquivo .h destinado à criação de um disparador e suas operações de uso no primeiro trabalho de estrutura de dados
*/

typedef void* Disparador;
typedef void* Pilha;
typedef void* Celula;

/// @brief Cria e retorna o disparador
/// @param i Identificador do disparador
/// @param x Coordenada X do disparador
/// @param y Coordenada Y do disparador
/// @param esquerda Carregador esquerdo
/// @param direita Carregador direito
/// @return Disparador criado
Disparador* criarDisparador(int i,double x, double y, Pilha* esquerda, Pilha* direita);

/// @brief Retorna o identificador do disparador
/// @return Identificador
int getIDDisparador(Disparador d);

/// @brief Retorna o primeiro conteúdo do carregador esquerdo
/// @return Primeiro conteúdo do carregador esquerdo
Celula getConteudoCarEsq(Disparador d);

/// @brief Retorna o primeiro conteúdo do carregador direito
/// @return Primeiro conteúdo do carregador direito
Celula getConteudoCarDir(Disparador d);

/// @brief Define o identificador
/// @param i Identificador do disparador
void setIDDisparador(Disparador d, int i);

void set

#endif