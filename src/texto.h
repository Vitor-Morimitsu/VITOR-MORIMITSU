#ifndef TEXTO_H
#define TEXTO_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

/*
    Este arquivo se refere à forma texto e suas respectivas características e propriedades úteis ao primeiro trabalho de estrutura de dados I.
*/

typedef void* Texto;
/*
    Arquivo .h para criação do texto e suas operações como set, get e cáculo de área.
*/

typedef void* Estilo;
/*
    Arquivo .h para criação e mudança de estilos de texto.
*/


// ------------------ FUNÇÕES DE TEXTO --------------------- //
/// @brief Cria e retorna um texto com os atributos fornecidos
/// @param i Identificador do texto
/// @param x Coordenada X do texto
/// @param y Coordenada Y do texto
/// @param corb Cor da borda
/// @param corp Cor de preenchimento 
/// @param a Posição da âncora do texto (inicio, meio, fim)
/// @param txto Texto
/// @return Retorna o texto criado
Texto criarTexto(int i, double x, double y, char* corb, char* corp, char a, char* txto);

/// @brief Retorna o identificador do texto
/// @param t Texto
/// @return Identificador do texto
int getIDTexto(Texto t);

/// @brief Retorna a coordenada X do texto
/// @param t Texto 
/// @return Coordenada X 
double getCoordXTexto(Texto t);

/// @brief Retorna a coordenada Y do texto
/// @param t Texto 
/// @return Coordenada Y do texto
double getCoordYTexto(Texto t);

/// @brief Retorna a cor da borda do texto
/// @param t Texto
/// @return Cor da borda do texto l
char* getCorBTexto(Texto t); 

/// @brief Retorna a cor de preenchimento
/// @param t Texto
/// @return Cor de preenchimento do texto
char* getCorPTexto(Texto t);

/// @brief Retorna a posição da âncora(inicio, meio, fim)
/// @param t Texto
/// @return Posição da âncora(início, meio, fim)
char getATexto(Texto t);

/// @brief
/// @param
/// @return

/// @brief
/// @param


/// @brief
/// @param

/// @brief
/// @param

// ---------------- FUNÇÕES DE ESTILO ----------------- //
/// @brief cria e retorna um estilo que vai ser associado a uma forma texto
/// @param family familia da fonte
/// @param weight weight da fonte
/// @param size tamanho da fonte
/// @return retorna o estilo
Estilo criarEstilo(char *family, char *weight, char *size);

/// @brief metodo get da familia da fonte  do texto 
/// @param ts Estilo ts
/// @return retorna a familia
char* getFamily(Estilo ts);

/// @brief metodo get do weight da fonte do texto 
/// @param ts Estilo ts
/// @return retorna o weight
char* getWeight(Estilo ts);

/// @brief metodo get do tamanho da fonte do texto
/// @param ts Estilo ts
/// @return retorna o tamanho da fonte
char* getSize(Estilo ts);

/// @brief metodo set da familia da fonte do texto 
/// @param ts Estilo ts
/// @param family nova familia da fonte
void setFamily(Estilo ts, char *family); 

/// @brief metodo set do weight da fonte do texto
/// @param ts Estilo ts
/// @param weight novo weight da fonte
void setWeight(Estilo ts, char *weight);

/// @brief metodo set do tamanho da fonte do texto
/// @param ts Estilo ts
/// @param size novo tamanho de fonte
void setSize(Estilo ts, char *size);


#endif