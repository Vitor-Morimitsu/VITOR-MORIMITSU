#ifndef GEO_H
#define GEO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "formas.h"

/*
    Arquivo .h destinado à leitura e processamento do arquivo .geo do primeiro trabalho de estrutura de dados.
*/
typedef void* Forma;
/// @brief Lê o .geo dado e preenche os comandos fornecidos em um arquivo svg contendo as formas
/// @param arqGeo Arquivo .geo fornecido pelo professor
/// @param arqSVG Arquivo .svg para a criação de formas fornecidas pelo .geo
/// @param quantidade Conta quantas formas serão fornecidas pelo .geo
void lerGeo(FILE* arqGeo, FILE* arqSVG,FILE* arqTxtDestino, FILE* arqSvgDestino, Forma* forma);

#endif