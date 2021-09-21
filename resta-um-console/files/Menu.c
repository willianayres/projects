#include "Menu.h"
#include "Tabuleiro.h"
#include "Principal.h"
#include "Arquivos.h"


// Fun��o para iniciar o programa chamando a fun��o de menu com as o��es iniciais.
void inicio()
{
    int op;                                 //Vari�vel de controle.//
    do
    {
       system("cls");                       //Limpa a tela//
       printf("<<Menu Principal>>\n");      //Formata��o de prints.//
       printf("\n(1) Instru��es");
       printf("\n(2) Jogar");
       printf("\n(3) Hist�rico");
       printf("\n(4) Sair\n\n");
       op=getch();                          //Le op do teclado.//
       menu(&op);                           //Passa op como referencia para fun��o menu.//
    }while(op>52||op<49);                   //Garante que o valor ser� entre 1 e 4.//
}
// ---------------------------------------------------------------------------- //

// Fun��o de menu para acessar os campos pre definidos na fun��o Inicio.
void menu(int *op)
{
    system("cls");                      //Limpa a tela.//
    switch(*op)
    {                                   //Switch com o valor do endere�o que o ponteiro aponta.//
    case 49:                            //Caso 1.//
        leArquivo("regra.txt");
        system("cls");
        inicio();                       //Retorna para a fun��o inicial.//
        break;
    case 50:                            //Caso 2.//
        escolheTab();
        break;
    case 51:                            //Caso 3.//
        menuH();                        //Chama a fun��o de menu para estat�sticas.//
        break;
    case 52:                            //Caso 4.//
        exit(0);                        //Fecha o programa.//
        break;
    }
}
// ------------------------------------------------------------------ //

// Fun��o de menu para acessar os campos pre definidos na fun��o Inicio.
void printTabs()
{
     system("cls");
     printf("<<Tipo de Tabuleiro>>\n\n");
     printf("(01) Padr�o Ingl�s   (16) Abajur        (31) Floco de Neve\n");
     printf("(02) Padr�o Franc�s  (17) Alvo          (32) Los�ngo\n");
     printf("(03) Iniciante       (18) Tri�ngulo     (33) Forquilhas\n");
     printf("(04) L               (19) Anel          (34) Espiral\n");
     printf("(05) P               (20) Flecha        (35) Quadrado Franc�s\n");
     printf("(06) Cruz            (21) Auto Estrada  (36) Cruzamento\n");
     printf("(07) Quadrados       (22) Ampulheta     (37) Oct�gono\n");
     printf("(08) Mais            (23) Barra         (38) Ventilador\n");
     printf("(09) X               (24) C�rculo       (39) Nave\n");
     printf("(10) Espelho         (25) Cristal       (40) Primeiro Buraco\n");
     printf("(11) Canto           (26) Pris�o        (41) Quatro Buracos\n");
     printf("(12) Oito            (27) X Negrito     (42) Franc�s Alternativo\n");
     printf("(13) Cartola         (28) Foguete       (43) Voltar\n");
     printf("(14) Casinha         (29) Caveira\n");
     printf("(15) Plateia         (30) 5 Cruzes\n\n");
}
// ------------------------------------------------------------------ //

// Fun��o para escolher o tabuleiro a ser jogado.
void escolheTab()
{
    int opS,p[2];                                    //Auxiliares.//
    printTabs();                                     //Imprimi as op��es de tabuleiros.//
    do
    {
        p[0]=getche()-48;                            //Le o primeiro n�mero da op��o.//
        p[1]=getche()-48;                            //Le o segundo n�mero da op��o.//
        opS=10*p[0]+p[1];                            //Concatena os dois n�meros.//
    }while(opS<1||opS>43);
    if(opS==43)                                      //Se igual a 43, retorna ao in�cio.//
        inicio();
    else
        preJogo(opS);                                  //Confere o tabuleiro.//
}
// ------------------------------------------- //

// Fun��o para executar o jogo conforme escolhido a op��o 2 no menu 1.
void preJogo(int opS)
{
    tabuleiro *t1=(tabuleiro *)malloc(sizeof(tabuleiro));   //Declara o ponteiro e armazena espa�o.//
    opS--;                                                  //Decremento de ajuste.//
    leTabu(t1,opS);                                         //Fun��o para declarar o tabuleiro.//
    veTabu(t1,opS);                                         //Fun��o para vizualizar o tabuleiro.//
}
// ---------------------------------------------------------------- //

// Fun��o para exercutar op��o escolhida da fun��o escolha.
void menuT()
{
    int opT;
    printf("<Menu de Escolha>\n\n(1) Voltar ao Menu\n(2) Abrir Hist�rico\n");
    printf("(3) Jogar Novamente\n(4) Sair\n");
    do
    {
        opT=getch();
    }while(opT<49||opT>52);
    system("cls");
    switch(opT)
    {
    case 49:
        inicio();
        break;
    case 50:
        leArquivo("historico.txt");
        menuT();
        break;
    case 51:
        escolheTab();
        break;
    case 52:
        exit(0);
        break;
    }
}
// ----------------------------------------------------- //

// Fun��o para abrir as op��es no menu de Hist�rico.
void menuH()
{
    int opE;                            //Vari�vel auxiliar.//
    system("cls");                      //Limpa a tela.//
    printf("<Menu de Hist�rico>\n\n(1) Voltar ao Menu\n");
    printf("(2) Abrir Hist�rico\n(3) Abrir Records\n(4) Limpar Hist�rico\n");
    do
    {
        opE=getch();                    //Le do teclado.//
    }while(opE>52||opE<49);             //Garante ser entre 1 e 4.//
    switch(opE)
    {
    case 49:                            //Caso 1.//
        system("cls");
        inicio();                       //Chama a fun��o inicial.//
        break;
    case 50:                            //Caso 2.//
        system("cls");
        leArquivo("historico.txt");     //Le o arquivo texto de hist�rico.//
        menuH();                        //Retorna para essa fun��o.//
        break;
    case 51:                            //Caso 3.//
        system("cls");;
        menuR();                        //Abre o menu de records.//
        break;
    case 52:
        resetaArquivo("Nome                           Tabuleiro           Resultado       Jogadas      Tempo\n\n");
        system("cls");
        menuH();                        //Retor
        break;
    }
}
// ---------------------------------------------- //

// Fun��o para abrir as op��es no menu de Records.
void menuR()
{
    int opR;                    //Vari�vel de escolha.//
    system("cls");              //Limpa a tela.//
    printf("<Records>\n\n(1) P�gina 1\n(2) P�gina 2\n");
    printf("(3) P�gina 3\n(4) P�gina 4\n(5) Voltar\n\n");
    do
    {
        opR=getch();            //Le a escolha do teclado.//
    }while(opR<49||opR>53);     //Garante que a escolha seja entre 1 e 5.//
    if(opR==53)                 //Se for 5.//
        menuH();                //Retorna ao menu de hist�rico.//
    else
    {
        system("cls");
        leArquivoRecord(opR);        //Abre a p�gina de record selecionada.//
        menuR();                //Retorna a esse menu.//
    }
}
// -------------------------------------------- //
