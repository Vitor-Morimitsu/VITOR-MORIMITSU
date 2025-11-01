#ifndef PRINTSVG_H
#define PRINTSVG_H

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
void desenharCirculoSVG(FILE* arqSvg,Circulo circ);

/*
    Função responsável por gerar um retângulo em SVG.
*/
void desenharRetanguloSVG(FILE* arqSvg, Retangulo r);

/*
    Função responsável por gerar uma linha em SVG.
*/
void desenharLinhaSVG(FILE* arqSvg, Linha l);

/*
    Função responsável por gerar um texto em SVG.
*/
void desenharTextoSVG(FILE* arqSvg, Texto t, Estilo ts);

/// @brief Função responsável por gerar o Svg de saída
/// @param svg Arquivo do svg
/// @param pacotes Fila de pacotes contendo as formas
void gerarSvgSaida(FILE* svg, Fila pacotes);

/// @brief Insere as dimensões do disparo no arquivo svg
/// @param svg Arquivo svg
/// @param xDis Coordenada x do disparador
/// @param yDis Cooordenada y do dispardor
/// @param dx Distância dx
/// @param dy Distância dy
void dimensoesDisparo(FILE* svg, double xDis, double yDis, double dx, double dy);

/// @brief Realiza o comando de encerramento do arquivo svg
/// @param arqSvg Arquivo
void fecharSVG(FILE* arqSvg);
#endif