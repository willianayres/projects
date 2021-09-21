#ifndef PRINCIPAL_H_INCLUDED
#define PRINCIPAL_H_INCLUDED


// Fun��o para executar o decorrer do jogo.
void jogo(tabuleiro*,int);

// Fun��o para percorrer o tabuleiro e detectar se ainda existem jogadas poss�veis.
int verificaJogo(tabuleiro*);

// Fun��o para verificar se o jogador venceu ou ganhou o jogo.
int verificaResultado(tabuleiro*);

// Fun��o principal do jogo para ler do teclado a jogada perante escolha do jogador.
void excecutaJogada(tabuleiro*,tempo*,int);

// Fun��o para verificar se uma jogada � v�lida ou n�o.
int verificaJogada(tabuleiro*,int,int,char);


#endif // PRINCIPAL_H_INCLUDED
