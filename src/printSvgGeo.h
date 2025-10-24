#ifndef PRINTSVGGEO_H
#define PRINTSVGGEO_H

#include "formas.h"
#include "geo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

/*
    Arquivo .h destinado à criação das formas em SVG a partir das formas lidas no .geo
*/

/*
    Função responsável por abrir o arquivo Svg passado como parâmetro.
*/
void abrirSvg(FILE* arqSvg);
/*
    Função responsável por gerar um círculo em SVG.
*/
void desenharCirculoSVG(FILE* arqSvg,Forma f);

/*
    Função responsável por gerar um retângulo em SVG.
*/
void desenharRetanguloSVG(FILE* arqSvg, Forma f);

/*
    Função responsável por gerar uma linha em SVG.
*/
void desenharLinhaSVG(FILE* arqSvg, Forma f);

/*
    Função responsável por gerar um texto em SVG.
*/
void desenharTextoSVG(FILE* arqSvg, Forma f);

/*
    Função responsável por gerar um arquivo Svg com base no arquivo txt lido
*/ 
void gerarSvgSaida(FILE* arqTxt, FILE* arqSvg);
#endif