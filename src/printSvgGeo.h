#ifndef PRINTSVGGEO_H
#define PRINTSVGGEO_H

#include "formas.h"
#include "geo.h"
#include "stdio.h"
#include "fila.h"

/*
    Arquivo .h destinado à criação das formas em SVG a partir das formas lidas no .geo
*/

/*
    Função responsável por gerar um círculo em SVG.
*/
void desenharCirculoSVG(FILE* arqSvg,Forma f);

/*
    Função responsável por gerar um retângulo em SVG.
*/
void desenharRetanguloSVG(FILE* arqSvg, Fila f);

/*
    Função responsável por gerar uma linha em SVG.
*/
void desenharLinhaSVG(FILE* arqSvg, Fila f);

/*
    Função responsável por gerar um texto em SVG.
*/
void desenharTextoSVG(FILE* arqSvg, Fila f);

/*
    Função responsável por printar as formas no arquivo SVG.
*/
void printSVG(FILE* arqSvg, Fila f);


#endif