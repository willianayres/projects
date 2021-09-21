#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>

// Função para iniciar o programa chamando a função de menu com as oções iniciais.
void inicio();

// Função de menu para acessar os campos pre definidos na função Inicio.
void menu(int*);

// Função para printar as opções de tabuleiro na tela.
void printTabs();

// Função para escolher o tabuleiro a ser jogado.
void escolheTab();

// Função para executar o jogo conforme escolhido a opção 2 no menu 1.
void preJogo(int);

// Função para exercutar opção escolhida da função escolha.
void menuT();

// Função para abrir as opções no menu de Histórico.
void menuH();

// Função para abrir as opções no menu de Records.
void menuR();


#endif // MENU_H_INCLUDED
