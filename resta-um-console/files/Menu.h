#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>

// Fun��o para iniciar o programa chamando a fun��o de menu com as o��es iniciais.
void inicio();

// Fun��o de menu para acessar os campos pre definidos na fun��o Inicio.
void menu(int*);

// Fun��o para printar as op��es de tabuleiro na tela.
void printTabs();

// Fun��o para escolher o tabuleiro a ser jogado.
void escolheTab();

// Fun��o para executar o jogo conforme escolhido a op��o 2 no menu 1.
void preJogo(int);

// Fun��o para exercutar op��o escolhida da fun��o escolha.
void menuT();

// Fun��o para abrir as op��es no menu de Hist�rico.
void menuH();

// Fun��o para abrir as op��es no menu de Records.
void menuR();


#endif // MENU_H_INCLUDED
