#ifndef CRIARTXT_H
#define CRIARTXT_H

#include <stdio.h>
#include <stdlib.h>
#include "colisoes.h"
#include "pilha.h"
#include "formas.h"
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "disparador.h"
#include "carregador.h"
#include "printSvg.h"

/*
    Arquivo .h responsável por criar um arquivo .txt com as instruções contidas no primeiro trabalho de estruturas de dados.
*/

/// @brief Reportar os dados de cada uma das formas carregadas
/// @param arqTxt Arquivo destino
/// @param p Pilha
void comandoLc(FILE* arqTxt, Pilha p);

/// @brief Reportar os dados da figura que resultou ficar no ponto de disparo
/// @param arqTxt Arquivo destino
void comandoShft(FILE* arqTxt, int idDis,Fila filaDisparadores);

/// @brief Reportar os dados da forma disparada e a posição final da forma
/// @param arqTxt Arquivo destino
/// @param pacote Pacote disparado
/// @param dx Deslocamento X
/// @param dy Deslocamento Y
void comandoDsp(FILE* arqTxt, Pacote pacote, double dx, double dy);

/// @brief Reportar o resultado de cada verificação; área total esmagada no round e a área total esmagada
/// @param arqTxt Arquivo destino
/// @param chao Fila com as formas na arena
void comandoCalc(FILE* arqTxt, FILE* svg, Fila chao);

#endif