#ifndef TABULEIRO_H_INCLUDED
#define TABULEIRO_H_INCLUDED


// Defini��o de vari�vel do tipo struct tabuleiro para utilizar no jogo RestaUm.
typedef struct{
int contador;           //Contador de jogadas.//
int pinos;              //Contador de pinos.//
char resultado[7];      //String para resultado.//
char jogador[20];       //String para nome do usu�rio.//
char nome[30];          //String para nome do tabuleiro.//
char campo[9][9];       //Array multidimensional para o campo.//
}tabuleiro;


// Defini��o de vari�vel do tipo struct tempo para utilizar como contador de tempo.
typedef struct{
int m;  //Vari�vel para minutos.//
int s;  //Vari�vel para segundos.//
}tempo;


// Fun��o para abrir e declarar o tabuleiro para jogo.
void leTabu(tabuleiro*,int);

// Fun��o para imprimir o tabuleiro formatado na tela.
void imprimiTabu(tabuleiro *t1,char[]);

// Fun��o para vizualizar o tabuleiro que foi escolhido para jogar.
void veTabu(tabuleiro*,int);

// Fun��o para armazenar nome escolhido pelo jogar no campo jogador da struct tabuleiro.
void leNome(tabuleiro*);

// Fun��o para imprimir o tabuleiro que est� sendo ultilizado no jogo.
void imprimiInfo(tabuleiro*);

// Fun��o para executar o retorno de jogada.
int retornaJogada(tabuleiro*);

// Fun��o para salvar o tabuleiro da jogada recem executada.
void salvaJogada(tabuleiro*);

// Fun��o para limpar o arquivo que est� sendo ultilizado para salvar o tabuleiro a cada jogada.
void limpaJogada();


#endif // TABULEIRO_H_INCLUDED
