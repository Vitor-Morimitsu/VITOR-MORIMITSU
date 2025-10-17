#ifndef COLISOES_H
#define COLISOES_H

#include "formas.h"

/*
    Arquivo .h responsável por averiguar as "colisões" de formas no primeiro trabalho de estrutura de dados.
*/

/// @brief Averigua se um circulo se sobrepõe a outro
/// @param f1 Forma 1
/// @param f2 Forma 2
/// @return 1 se a primeira forma sobrepuser a segunda ou 2 se a segunda forma sobrepuser a primeira
int circuloSobrepoeCirculo(Forma f1, Forma f2);

/// @brief Averigua se um circulo se sobrepõe a um retangulo
/// @param f1 Forma 1
/// @param f2 Forma 2
/// @return 1 se a primeira forma sobrepuser a segunda ou 2 se a segunda forma sobrepuser a primeira
int circuloSobrepoeRetangulo(Forma f1, Forma f2);

/// @brief Averigua se um circulo se sobrepõe a uma linha
/// @param f1 Forma 1
/// @param f2 Forma 2
/// @return 1 se a primeira forma sobrepuser a segunda ou 2 se a segunda forma sobrepuser a primeira 
int circuloSobrepoeLinha(Forma f1, Forma f2);

/// @brief Averigua se um circulo se sobrepõe a um texto
/// @param f1 Forma 1
/// @param f2 Forma 2
/// @return 1 se a primeira forma sobrepuser a segunda ou 2 se a segunda forma sobrepuser a primeira
int circuloSobrepoeTexto(Forma f1, Forma f2);

/// @brief Averigua se um retangulo se sobrepõe a uma linha
/// @param f1 Forma 1
/// @param f2 Forma 2
/// @return 1 se a primeira forma sobrepuser a segunda ou 2 se a segunda forma sobrepuser a primeira
int retanguloSobrepoeLinha(Forma f1, Forma f2);

/// @brief Averigua se um retangulo se sobrepõe a outro retângulo
/// @param f1 Forma 1
/// @param f2 Forma 2
/// @return 
int retanguloSobrepoeRetangulo(Forma f1, Forma f2);

/// @brief Averigua se um retangulo se sobrepõe a um texto
/// @param f1 Forma 1 
/// @param f2 Forma 2
/// @return 1 se a primeira forma sobrepuser a segunda ou 2 se a segunda forma sobrepuser a primeira
int retanguloSobrepoeTexto(Forma f1, Forma f2);

/// @brief Averigua se uma linha se sobrepõe a um texto
/// @param f1 Forma 1
/// @param f2 Forma 2
/// @return 1 se a primeira forma sobrepuser a segunda ou 2 se a segunda forma sobrepuser a primeira
int linhaSobrepoeTexto(Forma f1, Forma f2);

/// @brief Averigua se as formas passadas por parâmetro se sobrepõe
/// @param f1 Primeira forma a ser comparada
/// @param f2 Segunda forma a ser comparada
/// @return 1 se a primeira forma sobrepuser a segunda ou 2 se a segunda forma sobrepuser a primeira
int formasSobrepoem(Forma f1, Forma f2);
#endif