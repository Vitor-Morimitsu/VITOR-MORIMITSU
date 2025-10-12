#ifndef PRINTSVGGEO_H
#define PRINTSVGGEO_H

#include "formas.h"
#include "geo.h"

/*
    Arquivo .h destinado à criação das formas em SVG a partir das formas lidas no .geo
*/

typedef void* Forma;
typedef void* Fila;

/*
    Função responsável por gerar as formas em SVG a partir das formar geradas do arquivo .geo
*/
void printSVG(FILE* arqSvg,Fila* f);


#endif