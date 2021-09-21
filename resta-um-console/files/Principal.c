#include "Menu.h"
#include "Tabuleiro.h"
#include "Principal.h"
#include "Arquivos.h"


// Fun��o para executar o decorrer do jogo.
void jogo(tabuleiro *t1,int n)
{
    tempo *temp=(tempo *)malloc(sizeof(tempo));     //Struct temp para armazenar tempo.//
    struct tm *hora_atual,*hora_atual2;             //Auxiliares para tempo.//
    int seg,seg2;
    time_t sec,sec2;                                //Contadores de tempo.//
    time(&sec);                                     //Recupera o informa��es do sistema operacional.//
    hora_atual=localtime(&sec);                     //Recebe o tempo das informa��es.//
    seg=hora_atual->tm_sec+60*(hora_atual->tm_hour*60+hora_atual->tm_min);
    system("cls");                                  //Converte para segundos.//
    leNome(t1);                                     //Leitura do nome do usu�rio.//
    imprimiInfo(t1);                                //Imprimi o tabuleiro.//
    excecutaJogada(t1,temp,seg);                    //Fun�ao para executar jogada.//
    time(&sec2);                                    //Recupera novamente as informa��es do sistema operacional.//
    hora_atual2 = localtime(&sec2);
    seg2=hora_atual2->tm_sec+60*(hora_atual2->tm_hour*60+hora_atual2->tm_min);
    temp->s=(seg2-seg)%60;                          //Converte o resto da divis�o para segundos.//
    temp->m=(seg2-seg)/60;                          //Converte a divis�o para minutos.//
    gravaArquivo(t1,temp,"historico.txt"," ");      //Salva as informa��es no arquivo de hist�rico.//
    limpaArquivo("retornatabuleiro.txt");           //Limpa arquivo auxiliar.//
    verificaRecord(t1,temp,n);                      //Verifica se bateu o record.//
    free(t1);
    free(temp);
    menuT();
}
// ------------------------------------- //

// Fun��o para percorrer o tabuleiro e detectar se ainda existem jogadas poss�veis.
int verificaJogo(tabuleiro *t1)
{
    int v=1;                    //Vari�vel de retorno.
    for(int i=1;i<9;i++){       //Se exister algum pino que possua um pino diratamente adjascente, ainda existem jogadas.
        for(int j=1;j<9;j++){
            if((t1->campo[i][j]!='*')&&(t1->campo[i][j]=='I')&&
               ((t1->campo[i+1][j]=='I'&&t1->campo[i+2][j]!='*'&&t1->campo[i+2][j]!='I')||
                (t1->campo[i][j+1]=='I'&&t1->campo[i][j+2]!='*'&&t1->campo[i][j+2]!='I')||
                (t1->campo[i-1][j]=='I'&&t1->campo[i-2][j]!='*'&&t1->campo[i-2][j]!='I')||
                (t1->campo[i][j-1]=='I'&&t1->campo[i][j-2]!='*'&&t1->campo[i][j-2]!='I')))
                    v=0;
        }
    }
    return v;
}
// ----------------------------------------------------------------------------- //

// Fun��o para verificar se o jogador venceu ou ganhou o jogo.
int verificaResultado(tabuleiro *t1)
{
    int v=0;                            //Vari�vel de retorno.//
    for(int i=1;i<9;i++)
    {
        for(int j=1;j<9;j++)            //Loop para percorrer a matriz.//
        {
            if(t1->campo[i][j]=='I')    //Conta os pinos no campo.//
                v++;
        }
    }
    if(v>1)                             //Se a quantidade de pinos for maior que 1, retorna 0.
        v=0;
    return v;
}
// -------------------------------------------------------- //

// Fun��o principal do jogo para ler do teclado a jogada perante escolha do jogador.
void excecutaJogada(tabuleiro *t1,tempo *temp,int segu)
{
    if(verificaJogo(t1))                        //Verifica se existem jogadas poss�ves.//
    {
        if(verificaResultado(t1))               //Verifica se o jogador ganhou ou perdeu.//
        {
            printf("VOC� GANHOU!!!\n\n");
            strcpy(t1->resultado,"Ganhou");
            return;                             //Retorna a fun��o jogo.//
        }
        else
        {
            printf("VOC� PERDEU!!!\n\n");
            strcpy(t1->resultado,"Perdeu");
            return;
        }
    }
    int seg;                                    //Vari�veis auxiliares para tempo.//
    struct tm *hora_atual3;
    time_t seg3;
    int linha=0,coluna=0,check=0;               //Linhas e colunas da matriz.//
    printf("(1)Qual posi��o deseja movimentar?\n\nLinha:   ");
    do                                          //Le a linha.//
    {
        linha=getch();
    }while(linha>57||linha<49);
    linha-=48;                                  //Ajuste para inteiro.//
    printf("%d\n\nColuna:  ",linha);
    do                                          //Le a coluna.//
    {
        coluna=getch();
    }while(coluna>57||coluna<49);
    coluna-=48;
    printf("%d\n\n(2)Para qual dire��o?\t(Digite V para sair ou R para voltar jogada)\n\nDirec�o:   ",coluna);
    char d;
    setbuf(stdin,NULL);                             //Limpa o buffer de entrada.//
    do                                              //Le a dire��o.//
    {
        d=getch();
        if(d==(int)((char)224))                     //Se for alguma tecla nao disponivel na tabela ascii./
        {
            d=getch();                              //Se for alguma seta.//
            if(d==72||d==80||d==77||d==75)
                break;
        }
        else
            d=toupper(d);                           //Sen�o coloca em mai�sculo.//
    }while(d!='W'&&d!='A'&&d!='S'&&d!='D'&&d!='V'&&d!='R');
    switch(d)                                       //Switch da dire��o.//
    {
    case 'V':                                       //Caso o jogador decida sair.//
        time(&seg3);                                //Le o tempo do sistesma operacional.//
        hora_atual3=localtime(&seg3);
        seg=hora_atual3->tm_sec+60*(hora_atual3->tm_hour*60+hora_atual3->tm_min);
        temp->s=(seg-segu)%60;                      //Converte para segundos.//
        temp->m=(seg-segu)/60;                      //Converte para minutos.//
        strcpy(t1->resultado,"Perdeu");             //Afirma que perdeu.//
        gravaArquivo(t1,temp,"historico.txt"," ");  //Grava as informa��es no arquivo.//
        limpaArquivo("retornatabuleiro.txt");       //Limpa o arquivo auxiliar.//
        free(t1);                                   //Libera espa�os alocados.//
        free(temp);
        inicio();                                   //Volta ao in�cio.//
        break;
    case 'R':                                       //Caso decida retornar a jogada.//
        system("cls");
        if(retornaJogada(t1))                       //Confere se � poss�vel.//
            printf("N�o foi poss�vel retornar jogada\n\n");
        imprimiInfo(t1);                            //Imprimi as informa��es mais o tabuleiro.//
        printf("\n");
        excecutaJogada(t1,temp,segu);               //Chama a fun��o novamente.//
        return;                                     //Evita atualiza��es desnecess�rias.//
        break;
    case 72:                                        //Caso dire��o seja para cima.//
    case 'W':
        if(verificaJogada(t1,linha,coluna,d))       //Verifica se � uma jogada v�lida.//
        {
            check=1;                                //Confirma jogada v�lida.//
            salvaJogada(t1);                        //Salva tabuleiro da jogada no arquivo auxiliar.//
            t1->campo[linha][coluna]='O';           //Posi��o seleciona torna-se campo vazio.//
            t1->campo[linha-1][coluna]='O';         //Posi��o adjacente a selecionada torna-se campo vazio.//
            t1->campo[linha-2][coluna]='I';         //Posi��o ligeriamente pr�xima a adjacente torna-se pino.//
        }
        break;
    case 75:                                        //Caso dire��o seja para esquerda.//
    case 'A':
        if(verificaJogada(t1,linha,coluna,d))
        {
            check=1;
            salvaJogada(t1);
            t1->campo[linha][coluna]='O';
            t1->campo[linha][coluna-1]='O';
            t1->campo[linha][coluna-2]='I';
        }
        break;
    case 80:                                        //Caso dire��o seja para baixo.//
    case 'S':
        if(verificaJogada(t1,linha,coluna,d))
        {
            check=1;
            salvaJogada(t1);
            t1->campo[linha][coluna]='O';
            t1->campo[linha+1][coluna]='O';
            t1->campo[linha+2][coluna]='I';
        }
        break;
    case 77:                                        //Caso dire��o seja para direita.//
    case 'D':
        if(verificaJogada(t1,linha,coluna,d))
        {
            check=1;
            salvaJogada(t1);
            t1->campo[linha][coluna]='O';
            t1->campo[linha][coluna+1]='O';
            t1->campo[linha][coluna+2]='I';
        }
        break;
    }                                               //Fim do switch.//
    if(!check)                                      //Se jogada n�o v�lida.//
    {
        t1->contador++;                             //Contador atualiza.//
        system("cls");
        printf("Jogada Inv�lida\n\n");
    }
    else                                            //Caso jogada v�lida.//
    {
        t1->contador++;                             //Atualiza contador de jogadas e os pinos.//
        t1->pinos--;
        system("cls");
    }
    imprimiInfo(t1);                                //Imprime informa��es e o campo.//
    printf("\n");
    excecutaJogada(t1,temp,segu);                   //Chama-se a fun��o novamente.//
}
// ------------------------------------------------------------------------------ //

// Fun��o para verificar se uma jogada � v�lida ou n�o.
int verificaJogada(tabuleiro *t1,int linha,int coluna,char d)
{
    int v=1;        //Caso a posi��o onde deseja-se chegar for um pino ou um espa�o inv�lido, ou a posi��o adjascente seja//
    switch(d)       //um espa�o vazio ou espa�o inv�lido, ou se onde deseja-se chegar for espa�o vazio ou espa�o inv�lido.//
    {               //A jogada ent�o � considerada inv�lida.//
        case 72:
        case 'W':
            if(t1->campo[linha-2][coluna]=='I' || t1->campo[linha-2][coluna]=='*'||
             t1->campo[linha-1][coluna]=='O' || t1->campo[linha-1][coluna]=='*'||
             t1->campo[linha][coluna]=='O' || t1->campo[linha][coluna]=='*')
                v=0;
            break;
        case 75:
        case 'A':
            if(t1->campo[linha][coluna-2]=='I' || t1->campo[linha][coluna-2]=='*'||
             t1->campo[linha][coluna-1]=='O' || t1->campo[linha][coluna-1]=='*'||
             t1->campo[linha][coluna]=='O' || t1->campo[linha][coluna]=='*')
                v=0;
            break;
        case 80:
        case 'S':
            if(t1->campo[linha+2][coluna]=='I' || t1->campo[linha+2][coluna]=='*' ||
             t1->campo[linha+1][coluna]=='O' || t1->campo[linha+1][coluna]=='*' ||
             t1->campo[linha][coluna]=='O' || t1->campo[linha][coluna]=='*')
                v=0;
            break;
        case 77:
        case 'D':
            if(t1->campo[linha][coluna+2]=='I' || t1->campo[linha][coluna+2]=='*' ||
             t1->campo[linha][coluna+1]=='O' || t1->campo[linha][coluna+1]=='*' ||
             t1->campo[linha][coluna]=='O' || t1->campo[linha][coluna]=='*')
                v=0;
            break;
    }
    return v;
}
// ------------------------------------------------- //
