#ifndef FORMAS_H
#define FORMAS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "disparador.h"
#include "pilha.h"
#include "fila.h"

/*
    Arquivo .h destinado à criação de um tipo genérico de forma que consiga armazenar e classificar outros tipos armazenados internamente.
*/

typedef void* Forma;

/// @brief Cria um retangulo com os parametros fornecidos.
Forma criaRetanguloForma(int i,char tipo, double x, double y, double w, double h, char* corb, char* corp);

/// @brief Cria um círculo com os parâmetros fornecidos.
Forma criaCirculoForma(int i,char tipo, double x, double y, double r, char* corb, char* corp);

/// @brief Cria uma linha com os parâmetros fornecidos.
Forma criaLinhaForma(int i,char tipo, double x1, double y1, double x2, double y2, char* cor);

/// @brief Cria um texto com os parâmetros fornecidos.
Forma criaTextoForma(int i,char tipo, double x, double y, char* corb, char* corp, char a, char* txto, Estilo ts);

/// @brief Retorna o identificador da forma criada
/// @param f Forma
/// @return Identificador da forma
int getIDForma(Forma f);

/// @brief Retorna o tipo da forma geométrica
/// @param f Forma f
/// @return Tipo da forma geométrica
char getTipoForma(Forma f);

void* getFiguraForma(Forma f);

/// @brief Retorna a coordenada X da forma
/// @param f Forma f
/// @return Coordenada X da forma
double getXForma(Forma f);

/// @brief Retorna a coordenada Y da forma
/// @param f Forma f
/// @return Coordenada Y da forma
double getYForma(Forma f);

/// @brief Retorna a área da forma
/// @param f Forma f
/// @return Área da forma
double getAreaForma(Forma f);

/// @brief Libera as formas criadas
/// @param f Forma f
void liberarForma(Forma f);

/// @brief Reportar os dados de cada uma das formas carregadas
/// @param arqTxt Arquivo destino
/// @param p Pilha
void escreverConteudoPilha(FILE* arqTxt, Pilha p);

/// @brief Posiciona a forma f a um deslocamento dx,dy em relação à posição do disparador
/// @param f Forma 
/// @param d Diparador
void posicionaForma(Forma f, Disparador d, double deslocX, double deslocY);

#endif