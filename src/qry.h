#ifndef QRY_H
#define QRY_H

#include "fila.h"
#include "geo.h"
#include "formas.h"
#include "disparador.h"
#include "pilha.h"
#include "buscas.h"

/*
    Arquivo .h responsável por ler as instruções contidas no arquivo .qry e executa-las  
*/

typedef void* Forma;

typedef void* Fila;

/*
    Função responável por abrir o arquivo .qry fornecido 
*/
void abrirQry(FILE* arqQry);

/*
    Função responsável por abrir o arquivo .txt que será a cópia das instruções contidas no .qry
*/
void abrirTxt(FILE* arqTxt);
/*
    Função responsável por ler as instruções contidas no arquivo .qry, executá-las e fazer uma cópia das intruções em um arquivo .txt
*/
void lerQry(FILE* arqQry, Fila f, FILE* arqTxt, Fila filaDisparadores, Fila filaCarregadores);

/*
    Função responsável por fechar o arquivo .qry que havia sido previamente aberto.
*/
void fecharQry(FILE* arqQry);

/*
    Função responsável por fechar o arquivo .txt que havia sido previamente aberto.

*/
void fecharTxt(FILE* arqTxt);

#endif