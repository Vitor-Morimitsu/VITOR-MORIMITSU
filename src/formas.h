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

typedef struct pacote* Pacote;

/// @brief Cria um pacote que armazenará uma Forma e o tipo dela
/// @return Pacote criado
Pacote criarPacote();

/// @brief Define a forma ao pacote
/// @param pac Pacote
/// @param forma Forma
void setFormaPacote(Pacote pac, Forma forma);

/// @brief Retorna a forma do pacote 
/// @param pac Pacote
Forma getFormaPacote(Pacote pac);

/// @brief Define o tipo do pacote
/// @param pac Pacote
/// @param tipo Tipo do pacote
void setTipoPacote(Pacote pac, char tipo);


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
void liberarForma(void* f);

/// @brief Reportar os dados de cada uma das formas carregadas
/// @param arqTxt Arquivo destino
/// @param p Pilha
void escreverConteudoPilha(FILE* arqTxt, Pilha p);

/// @brief Posiciona a forma f a um deslocamento dx,dy em relação à posição do disparador
/// @param f Forma 
/// @param d Diparador
void posicionaForma(Forma f, Disparador d, double deslocX, double deslocY);

#endif