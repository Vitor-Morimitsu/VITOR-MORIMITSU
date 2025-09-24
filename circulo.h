#ifndef CIRCULO_H
#define CIRCULO_H

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h" 

typedef void *Circulo;
/*
    Este é um arquivo .h que se refere a um circulo e suas operações como get, set e cálculo de área
*/

/// @brief Cria e retorna um novo círculo com os atributos fornecidos.
/// @param i Identificador do círculo
/// @param x Coordenada x do centro do círculo
/// @param y Coordenada y do centro do círculo
/// @param r Raio do círculo
/// @param corBorda Cor da borda do círculo
/// @param cor Cor interna do círculo
/// @return Retorna o círculo criado
Circulo criaCirculo(int i, double x, double y, double r, char* corBorda, char* cor);

/// @brief Retorna o identificador do círculo
/// @param c Círculo
/// @return Identificador do círculo
int getIDCirculo(Circulo c);

/// @brief Retorna a coordenada X do centro do círculo
/// @param c Círculo
/// @return Coordenada X do centro do círculo
double getCoordXCirculo(Circulo c);

/// @brief Retorna a coordenada Y do centro do círculo
/// @param c Círculo
/// @return Coordenada Y do centro do círculo
double getCoordYCirculo(Circulo c);

/// @brief Retorna o raio do círculo
/// @param c Círculo
/// @return Raio do círculo
double getRaio(Circulo c);

/// @brief Retorna a cor da borda do círculo
/// @param c Círculo
/// @return Cor da borda do círculo
char* getCorBorda(Circulo c);

/// @brief Retorna a cor interna do círculo
/// @param c Círculo
/// @return Cor interna do círculo
char* getCor(Circulo c);

/// @brief Realiza o cálculo da área e o retorna
/// @param c Círculo
/// @return Área do círculo
double getArea(Circulo c);

/// @brief Define o identificador do círculo
/// @param c Círculo
/// @param i Novo identificador 
void setIDCirculo(Circulo c, int i);

/// @brief Define a coordenada X do centro do círculo
/// @param c Círculo
/// @param x Coordenada X do círculo
void setXCirculo(Circulo c, double x);

/// @brief Define a coordenada Y do centro do círculo
/// @param c Círculo
/// @param y Coordenada Y do círculo
void setYCirculo(Circulo c, double y);

/// @brief Define o raio do círculo
/// @param c Círculo
/// @param r Raio
void setRaioCirculo(Circulo c, double r);

/// @brief Define a cor da borda do círculo
/// @param c Círculo
/// @param corBorda Cor da borda do círculo
void setCorBordaCirculo(Circulo c, char* corBorda);

/// @brief Define a cor interna do círculo
/// @param c Círculo
/// @param cor Cor interna do círculo
void setCorCirculo(Circulo c, char* cor);

#endif