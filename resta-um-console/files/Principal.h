#ifndef PRINCIPAL_H_INCLUDED
#define PRINCIPAL_H_INCLUDED


// Função para executar o decorrer do jogo.
void jogo(tabuleiro*,int);

// Função para percorrer o tabuleiro e detectar se ainda existem jogadas possíveis.
int verificaJogo(tabuleiro*);

// Função para verificar se o jogador venceu ou ganhou o jogo.
int verificaResultado(tabuleiro*);

// Função principal do jogo para ler do teclado a jogada perante escolha do jogador.
void excecutaJogada(tabuleiro*,tempo*,int);

// Função para verificar se uma jogada é válida ou não.
int verificaJogada(tabuleiro*,int,int,char);


#endif // PRINCIPAL_H_INCLUDED
