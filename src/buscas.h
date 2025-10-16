#ifndef BUSCAS_H
#define BUSCAS_H

#include "fila.h"
#include "disparador.h"
#include "pilha.h"
#include "formas.h" 

/*
    Arquivo .h responsável por buscar figuras necessárias ao primeiro trabalho de estrutura de dados.
*/

/// @brief Encontra um Disparador em uma Fila pelo seu ID.
/// @param listaDeDisparadores Fila que contém todos os disparadores.
/// @param id ID do disparador a ser procurado.
/// @return Disparador encontrado.
Disparador encontrarDisparadorPorID(Fila listaDeDisparadores, int id);

/// @brief Encontra uma Pilha em uma Fila pelo seu ID.
/// @param listaDePilhas Fila que contém todas as pilhas.
/// @param id ID da pilha a ser procurada.
/// @return Pilha encontrada.
Pilha encontrarPilhaPorID(Fila listaDePilhas, int id);

/// @brief Encontra uma Forma genérica em uma Fila pelo seu ID.
/// @param listaDeFormas Fila que contém todas as formas.
/// @param id ID da forma a ser procurada.
/// @return Forma encontrada.
Forma encontrarFormaPorID(Fila listaDeFormas, int id);

#endif