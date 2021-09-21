#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<locale.h>
#include<conio.h>
#include<ctype.h>
#include <time.h>
#include "Menu.h"
#include "Tabuleiro.h"
#include "Principal.h"
#include "Estatistica.h"



void jogEmMenu(tabuleiro *t1, int n){
    int opT;
    tempo *temp;
    temp = (tempo *)malloc(sizeof(tempo));
    struct tm *hora_atual;
    struct tm *hora_atual2;
    int segu, segu2;
    time_t segundos;
    time_t segundos2;
    time(&segundos);
    hora_atual = localtime(&segundos);
    segu=hora_atual->tm_sec+60*(hora_atual->tm_hour*60+hora_atual->tm_min);
    system("cls");
    Nome(t1);
    Imprimi(t1);
    Jogada(t1,temp,segu);
    time(&segundos2);
    hora_atual2 = localtime(&segundos2);
    segu2=hora_atual2->tm_sec+60*(hora_atual2->tm_hour*60+hora_atual2->tm_min);
    temp->segt=(segu2-segu)%60;
    temp->mint=(segu2-segu)/60;
    SalvaEstatis(t1,temp);
    verifica(t1,temp,n);
    free(t1);
    free(temp);
    escolha();
    do{
    opT = getch();
    }while(opT<49||opT>52);
    menuT(opT);
}



int ContaTabuleiro(tabuleiro *t1){
            int volta=0;
            int i, j;
            for(i=1;i<9;i++){
                for(j=1;j<9;j++){
                    if(((*t1).campo[i][j]!='*')&&((*t1).campo[i][j]=='I')&&
                    (((*t1).campo[i+1][j]=='I')||((*t1).campo[i][j+1]=='I')||
                    ((*t1).campo[i-1][j]=='I')||((*t1).campo[i][j-1]=='I'))){
                    volta = 1;
                }
            }
        }
    return volta;
}



int GameOver(tabuleiro *t1){
            int verifica = 0;
            int i, j;
            for(i=1;i<9;i++){
                for(j=1;j<9;j++){
                    if((*t1).campo[i][j]=='I'){
                    verifica=verifica+1;
                    }
                }
            }
    if(verifica==1){
    return 1;}
    else{
    return 0;
    }
}



void Jogada(tabuleiro *t1, tempo *temp, int segu){
    if(ContaTabuleiro(t1)==0){
            if(GameOver(t1)==1){
            printf("VOCÊ GANHOU!!!\n\n");
            strcpy((*t1).resultado,"Ganhou");
            return;
        }else{
            printf("VOCÊ PERDEU!!!\n\n");
            strcpy((*t1).resultado,"Perdeu");
            return;
    }
    }
    int segu3;
    struct tm *hora_atual3;
    time_t segundos3;
    int linha = 0;
    int coluna = 0;
    char direcao;
    printf("(1)Qual posição deseja movimentar?\n");
    printf("\nLinha:   ");
    do{
    linha = getch();
    }while(linha>57||linha<49);
    linha = linha - 48;
    printf("%d",linha);
    printf("\n\nColuna:   ");
    do{
    coluna = getch();
    }while(coluna>57||coluna<49);
    coluna = coluna - 48;
    printf("%d",coluna);
    printf("\n\n");
    printf("(2)Para qual direção?\t(Digite V para sair)\n");
    printf("\nDirecão:   ");
    do{
    direcao = getch();
    if(direcao == (int)((char)224)) {
            direcao = getch();
            if(direcao==72||direcao==80||direcao==77||direcao==75) break;
    }
    else direcao=toupper(direcao);
    }while(direcao!='W'&&direcao!='A'&&direcao!='S'&&direcao!='D'&&direcao!='V');
        switch(direcao){
        case 'V':
                  time(&segundos3);
                  hora_atual3 = localtime(&segundos3);
                  segu3=hora_atual3->tm_sec+60*(hora_atual3->tm_hour*60+hora_atual3->tm_min);
                  temp->segt=(segu3-segu)%60;
                  temp->mint=(segu3-segu)/60;
                  strcpy((*t1).resultado,"Perdeu");
                  SalvaEstatis(t1,temp);
                  free(t1);
                  free(temp);
                  system("cls");
                  Inicio();
        break;
        case 72:
        case 'W' :
        if((*t1).campo[linha-2][coluna]=='I' || (*t1).campo[linha-2][coluna]=='*'||
           (*t1).campo[linha-1][coluna]=='O' || (*t1).campo[linha-1][coluna]=='*'||
           (*t1).campo[linha][coluna]=='O' || (*t1).campo[linha][coluna]=='*'){
            (*t1).contador=(*t1).contador+1;
            system("cls");
            printf("Jogada Inválida\n\n");
            Imprimi(t1);
            printf("\n");
            Jogada(t1,temp,segu);
        }
        else{
        (*t1).contador=(*t1).contador+1;
        (*t1).pinos=(*t1).pinos-1;
        (*t1).campo[linha][coluna]='O';
        (*t1).campo[linha-1][coluna]='O';
        (*t1).campo[linha-2][coluna]='I';
        system("cls");
        printf("\n");
        Imprimi(t1);
        Jogada(t1,temp,segu);
        }
        break;
        case 75:
        case 'A' :
         if((*t1).campo[linha][coluna-2]=='I' || (*t1).campo[linha][coluna-2]=='*'||
            (*t1).campo[linha][coluna-1]=='O' || (*t1).campo[linha][coluna-1]=='*'||
            (*t1).campo[linha][coluna]=='O' || (*t1).campo[linha][coluna]=='*'){
            (*t1).contador=(*t1).contador+1;
            system("cls");
            printf("Jogada Inválida\n\n");
            Imprimi(t1);
            printf("\n");
            Jogada(t1,temp,segu);
        }
        else{
        (*t1).contador=(*t1).contador+1;
        (*t1).pinos=(*t1).pinos-1;
        (*t1).campo[linha][coluna]='O';
        (*t1).campo[linha][coluna-1]='O';
        (*t1).campo[linha][coluna-2]='I';
        system("cls");
        printf("\n");
        Imprimi(t1);
        Jogada(t1,temp,segu);
        }
        break;
        case 80:
        case 'S' :
         if((*t1).campo[linha+2][coluna]=='I' || (*t1).campo[linha+2][coluna]=='*' ||
            (*t1).campo[linha+1][coluna]=='O' || (*t1).campo[linha+1][coluna]=='*' ||
            (*t1).campo[linha][coluna]=='O' || (*t1).campo[linha][coluna]=='*'){
            (*t1).contador=(*t1).contador+1;
            system("cls");
            printf("Jogada Inválida\n\n");
            Imprimi(t1);
            printf("\n");
            Jogada(t1,temp,segu);
        }
        else{
        (*t1).contador=(*t1).contador+1;
        (*t1).pinos=(*t1).pinos-1;
        (*t1).campo[linha][coluna]='O';
        (*t1).campo[linha+1][coluna]='O';
        (*t1).campo[linha+2][coluna]='I';
        system("cls");
        printf("\n");
        Imprimi(t1);
        Jogada(t1,temp,segu);
        }
        break;
        case 77:
        case 'D' :
         if((*t1).campo[linha][coluna+2]=='I' || (*t1).campo[linha][coluna+2]=='*' ||
            (*t1).campo[linha][coluna+1]=='O' || (*t1).campo[linha][coluna+1]=='*' ||
            (*t1).campo[linha][coluna]=='O' || (*t1).campo[linha][coluna]=='*'){
            (*t1).contador=(*t1).contador+1;
            system("cls");
            printf("Jogada Inválida\n\n");
            Imprimi(t1);
            printf("\n");
            Jogada(t1,temp,segu);
        }
        else{
        (*t1).contador=(*t1).contador+1;
        (*t1).pinos=(*t1).pinos-1;
        (*t1).campo[linha][coluna]='O';
        (*t1).campo[linha][coluna+1]='O';
        (*t1).campo[linha][coluna+2]='I';
        system("cls");
        printf("\n");
        Imprimi(t1);
        Jogada(t1,temp,segu);
        }
        break;
        default: system("cls");
                 printf("Jogada Inválida\n\n");
                 Imprimi(t1);
                 printf("\n");
                 Jogada(t1,temp,segu);

        }
}


