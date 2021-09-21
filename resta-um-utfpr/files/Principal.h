#ifndef PRINCIPAL_H_INCLUDED
#define PRINCIPAL_H_INCLUDED



// Função para executar o decorrer do jogo.

void jogEmMenu(tabuleiro *t1, int n);

// Função para percorrer o tabuleiro e detectar se ainda existem jogadas possíveis.

int ContaTabuleiro(tabuleiro *t1);

// Função para verificar se o jogador venceu ou ganhou o jogo.

int GameOver(tabuleiro *t1);

// Função principal do jogo para ler do teclado a jogada perante escolha do jogador.

void Jogada(tabuleiro *t1, tempo *temp, int segu);



#endif // PRINCIPAL_H_INCLUDED


