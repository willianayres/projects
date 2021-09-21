#include "Menu.h"
#include "Tabuleiro.h"
#include "Principal.h"
#include "Arquivos.h"


// Função para executar o decorrer do jogo.
void jogo(tabuleiro *t1,int n)
{
    tempo *temp=(tempo *)malloc(sizeof(tempo));     //Struct temp para armazenar tempo.//
    struct tm *hora_atual,*hora_atual2;             //Auxiliares para tempo.//
    int seg,seg2;
    time_t sec,sec2;                                //Contadores de tempo.//
    time(&sec);                                     //Recupera o informações do sistema operacional.//
    hora_atual=localtime(&sec);                     //Recebe o tempo das informações.//
    seg=hora_atual->tm_sec+60*(hora_atual->tm_hour*60+hora_atual->tm_min);
    system("cls");                                  //Converte para segundos.//
    leNome(t1);                                     //Leitura do nome do usuário.//
    imprimiInfo(t1);                                //Imprimi o tabuleiro.//
    excecutaJogada(t1,temp,seg);                    //Funçao para executar jogada.//
    time(&sec2);                                    //Recupera novamente as informações do sistema operacional.//
    hora_atual2 = localtime(&sec2);
    seg2=hora_atual2->tm_sec+60*(hora_atual2->tm_hour*60+hora_atual2->tm_min);
    temp->s=(seg2-seg)%60;                          //Converte o resto da divisão para segundos.//
    temp->m=(seg2-seg)/60;                          //Converte a divisão para minutos.//
    gravaArquivo(t1,temp,"historico.txt"," ");      //Salva as informações no arquivo de histórico.//
    limpaArquivo("retornatabuleiro.txt");           //Limpa arquivo auxiliar.//
    verificaRecord(t1,temp,n);                      //Verifica se bateu o record.//
    free(t1);
    free(temp);
    menuT();
}
// ------------------------------------- //

// Função para percorrer o tabuleiro e detectar se ainda existem jogadas possíveis.
int verificaJogo(tabuleiro *t1)
{
    int v=1;                    //Variável de retorno.
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

// Função para verificar se o jogador venceu ou ganhou o jogo.
int verificaResultado(tabuleiro *t1)
{
    int v=0;                            //Variável de retorno.//
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

// Função principal do jogo para ler do teclado a jogada perante escolha do jogador.
void excecutaJogada(tabuleiro *t1,tempo *temp,int segu)
{
    if(verificaJogo(t1))                        //Verifica se existem jogadas possíves.//
    {
        if(verificaResultado(t1))               //Verifica se o jogador ganhou ou perdeu.//
        {
            printf("VOCÊ GANHOU!!!\n\n");
            strcpy(t1->resultado,"Ganhou");
            return;                             //Retorna a função jogo.//
        }
        else
        {
            printf("VOCÊ PERDEU!!!\n\n");
            strcpy(t1->resultado,"Perdeu");
            return;
        }
    }
    int seg;                                    //Variáveis auxiliares para tempo.//
    struct tm *hora_atual3;
    time_t seg3;
    int linha=0,coluna=0,check=0;               //Linhas e colunas da matriz.//
    printf("(1)Qual posição deseja movimentar?\n\nLinha:   ");
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
    printf("%d\n\n(2)Para qual direção?\t(Digite V para sair ou R para voltar jogada)\n\nDirecão:   ",coluna);
    char d;
    setbuf(stdin,NULL);                             //Limpa o buffer de entrada.//
    do                                              //Le a direção.//
    {
        d=getch();
        if(d==(int)((char)224))                     //Se for alguma tecla nao disponivel na tabela ascii./
        {
            d=getch();                              //Se for alguma seta.//
            if(d==72||d==80||d==77||d==75)
                break;
        }
        else
            d=toupper(d);                           //Senão coloca em maiúsculo.//
    }while(d!='W'&&d!='A'&&d!='S'&&d!='D'&&d!='V'&&d!='R');
    switch(d)                                       //Switch da direção.//
    {
    case 'V':                                       //Caso o jogador decida sair.//
        time(&seg3);                                //Le o tempo do sistesma operacional.//
        hora_atual3=localtime(&seg3);
        seg=hora_atual3->tm_sec+60*(hora_atual3->tm_hour*60+hora_atual3->tm_min);
        temp->s=(seg-segu)%60;                      //Converte para segundos.//
        temp->m=(seg-segu)/60;                      //Converte para minutos.//
        strcpy(t1->resultado,"Perdeu");             //Afirma que perdeu.//
        gravaArquivo(t1,temp,"historico.txt"," ");  //Grava as informações no arquivo.//
        limpaArquivo("retornatabuleiro.txt");       //Limpa o arquivo auxiliar.//
        free(t1);                                   //Libera espaços alocados.//
        free(temp);
        inicio();                                   //Volta ao início.//
        break;
    case 'R':                                       //Caso decida retornar a jogada.//
        system("cls");
        if(retornaJogada(t1))                       //Confere se é possível.//
            printf("Não foi possível retornar jogada\n\n");
        imprimiInfo(t1);                            //Imprimi as informações mais o tabuleiro.//
        printf("\n");
        excecutaJogada(t1,temp,segu);               //Chama a função novamente.//
        return;                                     //Evita atualizações desnecessárias.//
        break;
    case 72:                                        //Caso direção seja para cima.//
    case 'W':
        if(verificaJogada(t1,linha,coluna,d))       //Verifica se é uma jogada válida.//
        {
            check=1;                                //Confirma jogada válida.//
            salvaJogada(t1);                        //Salva tabuleiro da jogada no arquivo auxiliar.//
            t1->campo[linha][coluna]='O';           //Posição seleciona torna-se campo vazio.//
            t1->campo[linha-1][coluna]='O';         //Posição adjacente a selecionada torna-se campo vazio.//
            t1->campo[linha-2][coluna]='I';         //Posição ligeriamente próxima a adjacente torna-se pino.//
        }
        break;
    case 75:                                        //Caso direção seja para esquerda.//
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
    case 80:                                        //Caso direção seja para baixo.//
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
    case 77:                                        //Caso direção seja para direita.//
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
    if(!check)                                      //Se jogada não válida.//
    {
        t1->contador++;                             //Contador atualiza.//
        system("cls");
        printf("Jogada Inválida\n\n");
    }
    else                                            //Caso jogada válida.//
    {
        t1->contador++;                             //Atualiza contador de jogadas e os pinos.//
        t1->pinos--;
        system("cls");
    }
    imprimiInfo(t1);                                //Imprime informações e o campo.//
    printf("\n");
    excecutaJogada(t1,temp,segu);                   //Chama-se a função novamente.//
}
// ------------------------------------------------------------------------------ //

// Função para verificar se uma jogada é válida ou não.
int verificaJogada(tabuleiro *t1,int linha,int coluna,char d)
{
    int v=1;        //Caso a posição onde deseja-se chegar for um pino ou um espaço inválido, ou a posição adjascente seja//
    switch(d)       //um espaço vazio ou espaço inválido, ou se onde deseja-se chegar for espaço vazio ou espaço inválido.//
    {               //A jogada então é considerada inválida.//
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
