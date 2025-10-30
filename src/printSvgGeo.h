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

/// @brief Realiza o comando de encerramento do arquivo svg
/// @param arqSvg Arquivo
void fecharSVG(FILE* arqSvg);
#endif