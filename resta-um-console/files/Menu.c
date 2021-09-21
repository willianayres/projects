#include "Menu.h"
#include "Tabuleiro.h"
#include "Principal.h"
#include "Arquivos.h"


// Função para iniciar o programa chamando a função de menu com as oções iniciais.
void inicio()
{
    int op;                                 //Variável de controle.//
    do
    {
       system("cls");                       //Limpa a tela//
       printf("<<Menu Principal>>\n");      //Formatação de prints.//
       printf("\n(1) Instruções");
       printf("\n(2) Jogar");
       printf("\n(3) Histórico");
       printf("\n(4) Sair\n\n");
       op=getch();                          //Le op do teclado.//
       menu(&op);                           //Passa op como referencia para função menu.//
    }while(op>52||op<49);                   //Garante que o valor será entre 1 e 4.//
}
// ---------------------------------------------------------------------------- //

// Função de menu para acessar os campos pre definidos na função Inicio.
void menu(int *op)
{
    system("cls");                      //Limpa a tela.//
    switch(*op)
    {                                   //Switch com o valor do endereço que o ponteiro aponta.//
    case 49:                            //Caso 1.//
        leArquivo("regra.txt");
        system("cls");
        inicio();                       //Retorna para a função inicial.//
        break;
    case 50:                            //Caso 2.//
        escolheTab();
        break;
    case 51:                            //Caso 3.//
        menuH();                        //Chama a função de menu para estatísticas.//
        break;
    case 52:                            //Caso 4.//
        exit(0);                        //Fecha o programa.//
        break;
    }
}
// ------------------------------------------------------------------ //

// Função de menu para acessar os campos pre definidos na função Inicio.
void printTabs()
{
     system("cls");
     printf("<<Tipo de Tabuleiro>>\n\n");
     printf("(01) Padrão Inglês   (16) Abajur        (31) Floco de Neve\n");
     printf("(02) Padrão Francês  (17) Alvo          (32) Losângo\n");
     printf("(03) Iniciante       (18) Triângulo     (33) Forquilhas\n");
     printf("(04) L               (19) Anel          (34) Espiral\n");
     printf("(05) P               (20) Flecha        (35) Quadrado Francês\n");
     printf("(06) Cruz            (21) Auto Estrada  (36) Cruzamento\n");
     printf("(07) Quadrados       (22) Ampulheta     (37) Octógono\n");
     printf("(08) Mais            (23) Barra         (38) Ventilador\n");
     printf("(09) X               (24) Círculo       (39) Nave\n");
     printf("(10) Espelho         (25) Cristal       (40) Primeiro Buraco\n");
     printf("(11) Canto           (26) Prisão        (41) Quatro Buracos\n");
     printf("(12) Oito            (27) X Negrito     (42) Francês Alternativo\n");
     printf("(13) Cartola         (28) Foguete       (43) Voltar\n");
     printf("(14) Casinha         (29) Caveira\n");
     printf("(15) Plateia         (30) 5 Cruzes\n\n");
}
// ------------------------------------------------------------------ //

// Função para escolher o tabuleiro a ser jogado.
void escolheTab()
{
    int opS,p[2];                                    //Auxiliares.//
    printTabs();                                     //Imprimi as opções de tabuleiros.//
    do
    {
        p[0]=getche()-48;                            //Le o primeiro número da opção.//
        p[1]=getche()-48;                            //Le o segundo número da opção.//
        opS=10*p[0]+p[1];                            //Concatena os dois números.//
    }while(opS<1||opS>43);
    if(opS==43)                                      //Se igual a 43, retorna ao início.//
        inicio();
    else
        preJogo(opS);                                  //Confere o tabuleiro.//
}
// ------------------------------------------- //

// Função para executar o jogo conforme escolhido a opção 2 no menu 1.
void preJogo(int opS)
{
    tabuleiro *t1=(tabuleiro *)malloc(sizeof(tabuleiro));   //Declara o ponteiro e armazena espaço.//
    opS--;                                                  //Decremento de ajuste.//
    leTabu(t1,opS);                                         //Função para declarar o tabuleiro.//
    veTabu(t1,opS);                                         //Função para vizualizar o tabuleiro.//
}
// ---------------------------------------------------------------- //

// Função para exercutar opção escolhida da função escolha.
void menuT()
{
    int opT;
    printf("<Menu de Escolha>\n\n(1) Voltar ao Menu\n(2) Abrir Histórico\n");
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

// Função para abrir as opções no menu de Histórico.
void menuH()
{
    int opE;                            //Variável auxiliar.//
    system("cls");                      //Limpa a tela.//
    printf("<Menu de Histórico>\n\n(1) Voltar ao Menu\n");
    printf("(2) Abrir Histórico\n(3) Abrir Records\n(4) Limpar Histórico\n");
    do
    {
        opE=getch();                    //Le do teclado.//
    }while(opE>52||opE<49);             //Garante ser entre 1 e 4.//
    switch(opE)
    {
    case 49:                            //Caso 1.//
        system("cls");
        inicio();                       //Chama a função inicial.//
        break;
    case 50:                            //Caso 2.//
        system("cls");
        leArquivo("historico.txt");     //Le o arquivo texto de histórico.//
        menuH();                        //Retorna para essa função.//
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

// Função para abrir as opções no menu de Records.
void menuR()
{
    int opR;                    //Variável de escolha.//
    system("cls");              //Limpa a tela.//
    printf("<Records>\n\n(1) Página 1\n(2) Página 2\n");
    printf("(3) Página 3\n(4) Página 4\n(5) Voltar\n\n");
    do
    {
        opR=getch();            //Le a escolha do teclado.//
    }while(opR<49||opR>53);     //Garante que a escolha seja entre 1 e 5.//
    if(opR==53)                 //Se for 5.//
        menuH();                //Retorna ao menu de histórico.//
    else
    {
        system("cls");
        leArquivoRecord(opR);        //Abre a página de record selecionada.//
        menuR();                //Retorna a esse menu.//
    }
}
// -------------------------------------------- //
