#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED



// Fun��o para iniciar o programa chamando a fun��o de menu com as o��es iniciais.

void Inicio();

// Fun��o de menu para acessar os campos pre definidos na fun��o Inicio.

void menu(int *op);

// Fun��o para printar as op��es de tabuleiro na tela.

void qualTab();

// Fun��o para executar o jogo conforme escolhido a op��o 2 no menu 1.

void menuS(int opS);

// Fun��o para printar os op��es ap�s termino de jogo.

void escolha();

// Fun��o para exercutar op��o escolhida da fun��o escolha.

void menuT(int opT);

// Fun��o para abrir as op��es no menu de Hist�rico.

void menuEstat();



#endif // MENU_H_INCLUDED


