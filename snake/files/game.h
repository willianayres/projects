#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED


#include <iostream>
#include <fstream>
#include <conio.h>
#include "position.h"
#include "classes.h"


//Imprimi um quadrado com dimens�es personalizadas.//
void print_quadrado(int inix,int iniy,int tamx,int tamy);

//Imprimi o menu.//
void print_menu();

//Imprimi o record.//
void print_record();

//Fun��o de menu.//
void menu();

//Fun�o para conferir record.//
void record(int);

//Fun��o principal do jogo.//
void game();


#endif // GAME_H_INCLUDED
