#ifndef RETANGULO_H
#define RETANGULO_H

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

typedef void *Retangulo;
/*
    Arquivo .h para criação do círculo e suas operações como set, get e cálculo de área.
*/

/// @brief Cria e retorna um novo retângulo com os atributos fornecidos
/// @param i Identificador do círculo
/// @param x Coordenada X do retângulo
/// @param y Coordenada Y do retângulo
/// @param comp Comprimento do retângulo
/// @param larg Largura do retângulo
/// @param corb Cor da borda do retângulo
/// @param corp Cor interna do retângulo
/// @return Retorna o retângulo criado
Retangulo criaRetangulo(int i, double x, double y, double comp, double larg, char* corb, char* corp);

/// @brief Retorna o identificador do retângulo
/// @param r Retângulo
/// @return Identificador do retângulo
int getIDRetangulo(Retangulo r);

/// @brief Retorna a coordenada X do retângulo
/// @param r Retângulo
/// @return Coordenada X do retângulo
double getCoordXRetangulo(Retangulo r);

/// @brief Retorna a coordenada Y do retângulo
/// @param r Retângulo
/// @return Coordenada Y do retângulo
double getCoordYRetangulo(Retangulo r);

/// @brief Retorna o comprimento do retângulo
/// @param r Retângulo
/// @return Comprimento do retângulo
double getCompRetangulo(Retangulo r); 

/// @brief Retorna a largura do retângulo
/// @param r Retângulo
/// @return Largura do retângulo
double getLargRetangulo(Retangulo r);

/// @brief Retorna a cor da borda do retângulo
/// @param r Retângulo
/// @return Cor da borda do retângulo
char* getCorBordaRetangulo(Retangulo r);

/// @brief Retorna a cor interna do círculo
/// @param r Retângulo
/// @return Cor interna do retângulo
char* getCorInternaRetangulo(Retangulo r);

/// @brief Realiza o cálculo de área e o retorna
/// @param r Retângulo
/// @return Área do retângulo
double getAreaRetangulo(Retangulo r);

/// @brief Define o identificador do retângulo
/// @param r Retângulo
/// @param i Novo identificador 
void setIDRetangulo(Retangulo r, int i);

/// @brief Define a coordenada X do retângulo
/// @param r Retângulo
/// @param x Coordenada X do retângulo
void setCoordXRetangulo(Retangulo r, double x);

/// @brief Define a coordenada Y do retângulo
/// @param r Retângulo
/// @param y Coordenada Y do retângulo
void setCoordYRetangulo(Retangulo r, double y);

/// @brief Define o comprimento do retângulo
/// @param r Retângulo
/// @param comp Comprimento do retângulo
void setCompRetangulo(Retangulo r, double comp);

/// @brief Define a largura do retângulo
/// @param r Retângulo
/// @param larg Largura do retângulo
void setLargRetangulo(Retangulo r, double larg);

/// @brief Define a cor da borda do retângulo
/// @param r Retângulo
/// @param corb Cor da borda do retângulo
void setCorBordaRetangulo(Retangulo r, char* corb);

/// @brief Define a cor interna do círculo
/// @param r Retângulo
/// @param corp Cor de preenchimento do retângulo
void setCorInternaRetangulo(Retangulo r, char* corp);

#endif