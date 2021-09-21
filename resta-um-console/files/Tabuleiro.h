#ifndef TABULEIRO_H_INCLUDED
#define TABULEIRO_H_INCLUDED


// Definição de variável do tipo struct tabuleiro para utilizar no jogo RestaUm.
typedef struct{
int contador;           //Contador de jogadas.//
int pinos;              //Contador de pinos.//
char resultado[7];      //String para resultado.//
char jogador[20];       //String para nome do usuário.//
char nome[30];          //String para nome do tabuleiro.//
char campo[9][9];       //Array multidimensional para o campo.//
}tabuleiro;


// Definição de variável do tipo struct tempo para utilizar como contador de tempo.
typedef struct{
int m;  //Variável para minutos.//
int s;  //Variável para segundos.//
}tempo;


// Função para abrir e declarar o tabuleiro para jogo.
void leTabu(tabuleiro*,int);

// Função para imprimir o tabuleiro formatado na tela.
void imprimiTabu(tabuleiro *t1,char[]);

// Função para vizualizar o tabuleiro que foi escolhido para jogar.
void veTabu(tabuleiro*,int);

// Função para armazenar nome escolhido pelo jogar no campo jogador da struct tabuleiro.
void leNome(tabuleiro*);

// Função para imprimir o tabuleiro que está sendo ultilizado no jogo.
void imprimiInfo(tabuleiro*);

// Função para executar o retorno de jogada.
int retornaJogada(tabuleiro*);

// Função para salvar o tabuleiro da jogada recem executada.
void salvaJogada(tabuleiro*);

// Função para limpar o arquivo que está sendo ultilizado para salvar o tabuleiro a cada jogada.
void limpaJogada();


#endif // TABULEIRO_H_INCLUDED
