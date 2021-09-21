#include "Menu.h"
#include "Tabuleiro.h"
#include "Principal.h"
#include "Arquivos.h"


// Fun��o para abrir e declarar o tabuleiro para jogo.
void leTabu(tabuleiro *t1,int n)
{
    t1->contador=0;                             //Inicializa o contador de jogadas com 0.//
    t1->pinos=0;                                //Inicializa o contador de pinos com 0.
    char ch,str[82];                            //Vari�veis auxiliares.//
    int aux=0;
    FILE *file=abreArquivo("tabuleiro.txt","r");//Abre o arquivo de tabuleiros para leitura.//
    while(ch!=EOF)                              //Enquanto n�o chegar ao final do arquivo.//
    {
        if(aux==n&&ch!='\n')                    //Se estiver na linha correta, at� uma quebra de linha.//
            fscanf(file,"%s",str);              //Recupera a string do arquivo texto.//
        if(aux==n+42&&ch!='\n')
        {
            fgets(t1->nome,30,file);            //Le o nome do tabuleiro na linha correta.//
            break;
        }
        if(ch=='\n')                            //Conta as quebras de linha para chegar na linha correta.//
            aux++;
        ch=getc(file);                          //Passa para o pr�ximo caract�re no arquivo.//
    }
    for(int i=0;i<(strlen(t1->nome));i++)       //Varre e nome para atribuir caract�re de final de string.//
    {
        if(t1->nome[i]=='\n')
            t1->nome[i]='\0';
    }
    for(int i=0;i<strlen(str);i++)              //Varre a string para contar o n�mero de pinos no tabuleiro.//
    {
        if(str[i]=='I')
            t1->pinos++;
    }
    memcpy(t1->campo,str,sizeof(t1->campo));    //Converte a string em uma matriz.//
    fclose(file);                               //Fecha o arquivo texto.//
}
// ------------------------------------------------ //

// Fun��o para imprimir o tabuleiro formatado na tela.
void imprimiTabu(tabuleiro *t1,char t[])
{
    printf("x   ");
    for(int i=0;i<7;i++)                            //Imprimi o n�meros das colunas.//
        printf("%d ",i+1);
    printf("  \n");
    for(int i=0;i<9;i++)
    {
        if(i==0||i==8)
            printf("%s  ",t);
        else
            printf("%s%d ",t,i);                    //Impirmi o n�mero das linhas.//
        for(int j=0;j<9;j++)
        {
            if(t1->campo[i][j]=='*')                //Imprimi espa�os vazios no lugar de '*'.//
                printf("  ");
            else
                printf("%c ",t1->campo[i][j]);      //Imprimi os pinos e os espa�os do campo.//
        }
        printf("\n");
    }
}
// ------------------------------------------------ //

// Fun��o para vizualizar o tabuleiro que foi escolhido para jogar.
void veTabu(tabuleiro *t1,int n)
{
    system("cls");                                          //Limpa a tela.//
    printf("O tabuleiro � assim:\n\n");
    imprimiTabu(t1,"");                                     //Imprimi o tabuleiro na tela.//
    printf("\nContinuar jogo?\n(1)Jogar\t(2)Voltar\n");     //Mostra as op��es.//
    int no;
    do
    {
        no=getch();                                         //Le a op��o.//
    }while(no>50||no<49);                                   //Garante que a op��o seja entre 1 e 2.//
    if(no==49)
        jogo(t1,n);                                         //Chama a fun��o de continuidade do jogo.//
    else
    {
        free(t1);                                           //Libera espa�o alocado.//
        escolheTab();                                       //Retorna a escolha de tabuleiro.//
    }
}
// ------------------------------------------------------------- //

// Fun��o para armazenar nome escolhido pelo jogar no campo jogador da struct tabuleiro.
void leNome(tabuleiro *t1)
{
    system("cls");                              //Limpa a tela.//
    printf("Digite seu nome/apelido: \n");
    setbuf(stdin,NULL);                         //Limpa o buffer de entrada.//
    fgets(t1->jogador,20,stdin);                //Le o nome do teclado.//
    t1->jogador[strlen(t1->jogador)-1]='\0';    //Adiciona o caractere finalizador de string.//
    system("cls");
}
// ---------------------------------------------------------------------------------- //

// Fun��o para imprimir o tabuleiro que est� sendo ultilizado no jogo.
void imprimiInfo(tabuleiro *t1)
{
    printf("   ");
    for(int i=0;t1->nome[i]!='\0';i++)              //Imprime o nome do tabuleiro.//
        printf("%c",t1->nome[i]);
    printf("\n\nJogada: %d\t",t1->contador);        //Imprime o contador de jogadas.//
    printf("Pinos Restantes: %d\n\n\t",t1->pinos);  //Imprime o contador de pinos.//
    imprimiTabu(t1,"\t");                           //Imprime o tabuleiro.//
}
// ---------------------------------------------------------------- //

// Fun��o para executar o retorno de jogada.
int retornaJogada(tabuleiro *t1)
{
    if(t1->contador<1)                                  //Se o contador for menor igual a 0//
        return 1;                                       //n�o � permitido retornar jogada. //
    char ch,str[82];                                    //Vari�veis auxiliares.//
    FILE *file=abreArquivo("retornatabuleiro.txt","r"); //Abre o arquivo para leitura.//
    while(ch!=EOF)
    {
        fscanf(file,"%s",str);                      //Le do arquivo.//
        ch=getc(file);
    }
    t1->pinos=0;                                    //Reseta o n�mero de pinos.//
    for(int i=0;i<82;i++)
    {
        if(str[i]=='I')
            t1->pinos++;
    }
    memcpy(t1->campo,str,sizeof(t1->campo));        //Copia o tabuleiro da rodada anteriror.//
    fclose(file);
    return 0;
}
// -------------------------------------- //

// Fun��o para salvar o tabuleiro da jogada recem executada.
void salvaJogada(tabuleiro *t1)
{
    FILE *file=abreArquivo("retornatabuleiro.txt","w+");//Abre o arquivo para escrita.//
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)                            //La�o para percorrer a matriz campo.//
            fprintf(file,"%c",t1->campo[i][j]);         //Grave no arquivo texto o campo.//
    }
    fprintf(file,"\n");                                 //Grava uma quebra de linha.//
    fclose(file);                                       //Fecha o arquivo.//
}
