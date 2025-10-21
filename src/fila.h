#ifndef FILA_H
#define FILA_H

#include <stdio.h>
#include <stdlib.h>

/*
    Arquivo .h criado com o intuito de criar uma fila no primeiro trabalho de estrutura de dados.
    A fila segue o princípio FIFO(first in, first out) cujo o primeiro elemento a entrar, também é o primeiro a sair
*/

typedef void* Fila;
typedef void* Forma;
typedef void* No_t;

/// @brief Cria uma fila vazia
/// @return Ponteiro para a fila criada
Fila criarFila();

/// @brief Insere um elemento na fila
/// @param f Fila
/// @param form Forma a ser inserida
void insereFila(Fila f, Forma form, char type);

/// @brief Remove o primeiro elemento da fila
/// @param f Fila
void removeFila(Fila f);

/// @brief Mostra o primeiro elemento da fila
/// @param f Fila
Forma getPrimeiraFormaFila(Fila f);

/// @brief Libera a memória ocupada pela fila
/// @param f Fila
void liberarFila(Fila f);

/// @brief Retorna o primeiro nó da fila para iniciar uma iteração.
/// @param f A fila.
/// @return O primeiro nó (como um No_t), ou NULL se a fila estiver vazia.
No_t getPrimeiroNoFila(Fila f);

/// @brief Dado um nó, retorna o próximo nó na sequência da fila.
/// @param no O nó atual (um No_t).
/// @return O nó seguinte, ou NULL se for o último.
No_t getProximoNoFila(No_t no);

/// @brief Retorna a Forma (o dado) armazenada dentro de um nó.
/// @param no O nó (um No_t).
/// @return A Forma contida no nó.
Forma getConteudoDoNoFila(No_t no);

/// @brief Retorna o tipo (char) da Forma armazenada dentro de um nó.
/// @param no O nó (um No_t).
/// @return O caractere de tipo da Forma.
char getTipoDoNoFila(No_t no);

/// @brief Retorna o tamanho da fila
/// @param f Fila
/// @return Tamanho da fila
int getTamanhoFila(Fila f);

/// @brief Retorna a forma que está em determinada posicao
/// @param f Fila
/// @param posicao Posicao da forma de interesse
/// @return Forma presente na posição desejada
Forma percorreFila(Fila f, int posicao);

#endif