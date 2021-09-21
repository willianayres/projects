#ifndef TABULEIRO_H_INCLUDED
#define TABULEIRO_H_INCLUDED



// Definição de variável do tipo struct tabuleiro para utilizar no jogo RestaUm.

typedef struct{
int contador;
int pinos;
char resultado[7];
char jogador[20];
char nome[30];
char campo[9][9];
}tabuleiro;



// Definição de variável do tipo struct tempo para utilizar como contador de tempo.

typedef struct{
int mint;
int segt;
}tempo;



// Função para abrir e declarar o tabuleiro para jogo.

void declaraTabu(tabuleiro *t1, int n);

// Função para vizualizar o tabuleiro que foi escolhido para jogar.

void preVisu(tabuleiro *t1, int n);

// Função para armazenar nome escolhido pelo jogar no campo jogador da struct tabuleiro.

void Nome(tabuleiro *t1);

// Função para imprimir o tabuleiro que está sendo ultilizado no jogo.

void Imprimi(tabuleiro *t1);



#endif // TABULEIRO_H_INCLUDED


