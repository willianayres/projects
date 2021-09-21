#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED



// Função para iniciar o programa chamando a função de menu com as oções iniciais.

void Inicio();

// Função de menu para acessar os campos pre definidos na função Inicio.

void menu(int *op);

// Função para printar as opções de tabuleiro na tela.

void qualTab();

// Função para executar o jogo conforme escolhido a opção 2 no menu 1.

void menuS(int opS);

// Função para printar os opções após termino de jogo.

void escolha();

// Função para exercutar opção escolhida da função escolha.

void menuT(int opT);

// Função para abrir as opções no menu de Histórico.

void menuEstat();



#endif // MENU_H_INCLUDED


