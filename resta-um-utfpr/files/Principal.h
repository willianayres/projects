#ifndef PRINCIPAL_H_INCLUDED
#define PRINCIPAL_H_INCLUDED



// Fun��o para executar o decorrer do jogo.

void jogEmMenu(tabuleiro *t1, int n);

// Fun��o para percorrer o tabuleiro e detectar se ainda existem jogadas poss�veis.

int ContaTabuleiro(tabuleiro *t1);

// Fun��o para verificar se o jogador venceu ou ganhou o jogo.

int GameOver(tabuleiro *t1);

// Fun��o principal do jogo para ler do teclado a jogada perante escolha do jogador.

void Jogada(tabuleiro *t1, tempo *temp, int segu);



#endif // PRINCIPAL_H_INCLUDED


