#ifndef CARREGADOR_H
#define CARREGADOR_H

typedef void* Pilha;

#include "formas.h"
#include "disparador.h"
#include "fila.h"
#include "pilha.h"

/*
    Arquivo .h destinado à criação e uso dos carregadores necessários ao primeiro trabalho de estrutura de dados.
*/

typedef void* Carregador;

/*
    Cria e retorna um carregaodor com o id passado.
*/ 
Carregador criarCarregador(int i);

/*
    Retorna o ID do carregador
*/
int getIDCarregador(Carregador car);

/*
    Libera a memória do carregador.
*/
void destruirCarregador(Carregador car);

/*
    Retorna a pilha do carregador.
*/
Pilha getPilhaCarregador(Carregador car);

#endif