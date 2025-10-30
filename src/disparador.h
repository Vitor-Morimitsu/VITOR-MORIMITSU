#ifndef DISPARADOR_H
#define DISPARADOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"
#include "fila.h"


/*
    Arquivo .h destinado à criação de um disparador e suas operações de uso no primeiro trabalho de estrutura de dados
*/

typedef void* Disparador;

/// @brief Cria e retorna o disparador
/// @param i Identificador do disparador
/// @param x Coordenada X do disparador
/// @param y Coordenada Y do disparador
/// @return Disparador criado
Disparador criarDisparador(int i,double x, double y);

/// @brief Retorna o conteudo que está no centro do disparador em posição de disparo
/// @param d Disparador
/// @return Conteudo do centro
Forma getConteudoCentro(Disparador d);

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

/// @brief Insere os n primeiros elementos da fila na pilha
/// @param p Pilha p
/// @param f Fila
/// @param n Quantidade de elementos da fila a serem inseridos na pilha
void carregarPilhaPelaFila(Pilha p, Fila f, int n);

/// @brief Define o identificador
/// @param i Identificador do disparador
void setIDDisparador(Disparador d, int i);

/// @brief Prepara uma forma para ser disparada
/// @param d Disparador
/// @param lado Lado do carregador que virá a forma 
/// @return 0 se a forma foi preparada para disparo e 1 caso não tenha sido reparada para disparo
int shft(Disparador d, char lado);

/// @brief Realiza o disparo da forma
/// @param d Disparador
/// @return Forma disparada
Forma dsp(Disparador d);

/// @brief Identifica qual forma está em posição de disparo
/// @param d Disparador
/// @return Forma em posição de disparo
Forma engatilhada(Disparador d);

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

/// @brief Pressiona um botão do disparador n vezes
/// @param d Disparador
/// @param lado Lado a ser alterado
/// @param n Quantidade de vezes a ser alterado
void pressionaBotao(Disparador d, char lado, int n, Pilha esq, Pilha dir);

/// @brief Destruir um disparador
/// @param d Disparador
void destruirDisparador(Disparador d);
#endif