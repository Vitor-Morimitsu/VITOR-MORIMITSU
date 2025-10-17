#ifndef CRIARTXT_H
#define CRIARTXT_H

#include "stdio.h"
#include "stdlib.h"
#include "pilha.h"
#include "formas.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "disparador.h"
#include "buscas.h"

/*
    Arquivo .h responsável por criar um arquivo .txt com as instruções contidas no primeiro trabalho de estruturas de dados.
*/

/// @brief Reportar os dados de cada uma das formas carregadas
/// @param arqTxt Arquivo destino
/// @param p Pilha
void escreverConteudoPilha(FILE* arqTxt, Pilha p);

/// @brief Reportar os dados da figura que resultou ficar no ponto de disparo
/// @param arqTxt Arquivo destino
void comandoShft(FILE* arqTxt, int idDis,Fila filaDisparadores, Fila filaCarregadores);

/// @brief Reportar os dados da forma disparada e a posição final da forma
/// @param arqTxt Arquivo destino
void comandoDsp(FILE* arqTxt, Fila listaDisparadores, int idDis, double dx, double dy);

/// @brief Reportar os dados das formas disapradas
/// @param arqTxt Arquivo destino
void comandoRjd(FILE* arqTxt, FILE* arqQry);

/// @brief Reportar o resultado de cada verificação; área total esmagada no round e a área total esmagada
/// @param arqTxt Arquivo destino
void comandoCalc(FILE* arqTxt, FILE* arqQry);

#endif