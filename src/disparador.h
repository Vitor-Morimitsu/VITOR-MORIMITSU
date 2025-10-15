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
/// @return Disparador criado
Disparador criarDisparador(int i,double x, double y, int IDEsquerda, int IDDireita);

/// @brief Retorna o identificador do disparador
/// @return Identificador
int getIDDisparador(Disparador d);

/// @brief Retorna a coordenada X do disparador
/// @param d Disparador
/// @return Coordenada X do disparador
double getXDisparador(Disparador d);

/// @brief Retorna a coordenada Y do disparador
/// @param d Disparador
/// @return Coordenada Y do disparador
double getYDisparador(Disparador d);

/// @brief Retorna o identificador da pilha esquerda
/// @param d Disparador
/// @return Identificador da pilha esquerda
int getIDPilhaEsquerda(Disparador d);

/// @brief Retorna o identificador da pilha direita
/// @param d Disparador
/// @return Identificador da pilha direita
int getPilhaDireita(Disparador d);

/// @brief Define o identificador
/// @param i Identificador do disparador
void setIDDisparador(Disparador d, int i);

/// @brief Encaixa no disparador d os carregadores da esquerda e direita
/// @param d Disparador
/// @param idPilhaEsq Id do carregador da esquerda
/// @param idPilhaDir Id do carregador da direita
void setCarregadorDisparador(Disparador d, int idPilhaEsq,int idPilhaDir);

/// @brief Define a posição do disparador com base nas coordenadas passadas
/// @param d Disparador
/// @param x Coordenada X do disparador
/// @param y Coordenada Y do disparador
void setPosicaoDisparador(Disparador d, double x, double y);

/// @brief Destruir um disparador
/// @param d Disparador
void destruirDisparador(Disparador d);
#endif