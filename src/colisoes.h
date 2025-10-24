#ifndef COLISOES_H
#define COLISOES_H

#include "formas.h"
#include <math.h>
#include "circulo.h"
#include "retangulo.h" 
#include "linha.h"
#include "texto.h"

/*
    Arquivo .h responsável por averiguar as "colisões" de formas no primeiro trabalho de estrutura de dados.
*/

/// @brief Averigua se um circulo se sobrepõe a outro
/// @param f1 Forma 1
/// @param f2 Forma 2
/// @return 0 se as figuras não se sobrepuserem e 1 se sobrupuserem
int circuloSobrepoeCirculo(Forma f1, Forma f2);

/// @brief Averigua se um circulo se sobrepõe a um retangulo
/// @param f1 Forma 1
/// @param f2 Forma 2
/// @return 0 se as figuras não se sobrepuserem e 1 se sobrupuserem
int circuloSobrepoeRetangulo(Forma f1, Forma f2);

/// @brief Averigua se um circulo se sobrepõe a uma linha
/// @param f1 Forma 1
/// @param f2 Forma 2
/// @return 0 se as figuras não se sobrepuserem e 1 se sobrupuserem
int circuloSobrepoeLinha(Forma f1, Forma f2);

/// @brief Averigua se um circulo se sobrepõe a um texto
/// @param f1 Forma 1
/// @param f2 Forma 2
/// @return 0 se as figuras não se sobrepuserem e 1 se sobrupuserem
int circuloSobrepoeTexto(Forma f1, Forma f2);

/// @brief Averigua se um retangulo se sobrepõe a uma linha
/// @param f1 Forma 1
/// @param f2 Forma 2
/// @return 0 se as figuras não se sobrepuserem e 1 se sobrupuserem
int retanguloSobrepoeLinha(Forma f1, Forma f2);

/// @brief Averigua se um retangulo se sobrepõe a outro retângulo
/// @param f1 Forma 1
/// @param f2 Forma 2
/// @return 0 se as figuras não se sobrepuserem e 1 se sobrupuserem
int retanguloSobrepoeRetangulo(Forma f1, Forma f2);

/// @brief Averigua se um retangulo se sobrepõe a um texto
/// @param f1 Forma 1 
/// @param f2 Forma 2
/// @return 0 se as figuras não se sobrepuserem e 1 se sobrupuserem
int retanguloSobrepoeTexto(Forma f1, Forma f2);

/// @brief Averigua se uma linha se sobrepõe a um texto
/// @param f1 Forma 1
/// @param f2 Forma 2
/// @return 0 se as figuras não se sobrepuserem e 1 se sobrupuserem
int linhaSobrepoeTexto(Forma f1, Forma f2);

/// @brief Averigua se uma linha se sobrepõe à outra
/// @param f1 Forma 1
/// @param f2 Forma 2
/// @return 0 se as figuras não se sobrepuserem e 1 se sobrepuserem
int linhaSobrepoeLinha(Forma f1,Forma f2);

/// @brief Averigua se um texto se sobrepõe à outro
/// @param f1 Forma 1
/// @param f2 Forma 2
/// @return 0 se as figuras não se sobrepuserem e 1 se sobrepuserem
int textoSobrepoeTexto(Forma f1, Forma f2);

/// @brief Averigua se as formas passadas por parâmetro se sobrepõe
/// @param f1 Primeira forma a ser comparada
/// @param f2 Segunda forma a ser comparada
/// @return 0 se as figuras não se sobrepuserem e 1 se sobrupuserem
int formasSobrepoem(Forma f1, Forma f2);
#endif