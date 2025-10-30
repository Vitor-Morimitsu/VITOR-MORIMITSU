#ifndef QRY_H
#define QRY_H

#include "fila.h"
#include "geo.h"
#include "formas.h"
#include "disparador.h"
#include "pilha.h"
#include "buscas.h"
#include "criarTxt.h"

/*
    Arquivo .h responsável por ler as instruções contidas no arquivo .qry e executa-las  
*/

typedef void* Forma;

typedef void* Fila;

/*
    Função responsável por ler as instruções contidas no arquivo .qry, executá-las e fazer uma cópia das intruções em um arquivo .txt
*/
void lerQry(FILE* arqQry, FILE* arqTxt, Fila filaDisparadores, Fila filaCarregadores, Fila chao);

/*
    Função responsável por encaixar os carregadores no disparador
*/
void qryAtch(Fila disparadores, Fila carregadores,int idDisparador, int idEsquerdo, int idDireito);
/*
    Função que pressiona o botão esquerdo(e) ou o botão direito(d) do disparador d n vezes
*/
void qryShft(Fila disparadores, Fila carregadores, int idDis, char lado, int n);

/*
    Função responsável por fechar o arquivo .qry que havia sido previamente aberto.
*/
void fecharQry(FILE* arqQry);

/*
    Função que realiza uma rajada de disparos até as formas do carregador se esgotarem
*/
void qryRjd(Fila disparadores, Fila carregadores, Fila arena,int idDis, char lado,double dx, double dy,double ix, double iy);

/// @brief Função que posiciona a forma que está em posição de disparo a um deslocamento dx,dy em relação ao disparador
/// @param disparadores Fila de disparadores
/// @param idDis Id do disparador
void qryDsp(Fila disparadores,Fila arena, int idDis, double dx, double dy, char letra, int iteracao);

/*
    Função responsável por fechar o arquivo .txt que havia sido previamente aberto.

*/
void fecharTxt(FILE* arqTxt);

#endif