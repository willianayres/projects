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



void declaraTabu(tabuleiro *t1, int n){
    (*t1).contador = 0;
    char str[82];
    char nomi[30], ch;
    int no, aux=0;
    FILE *tab;
    tab = fopen("tabuleiro.txt","r");
    if(tab == NULL){
    printf("Erro ao abrir o arquivo");
    exit(1);}
    ch=getc(tab);
    while(ch != EOF){
        if(aux==n&&ch!='\n'){
            fscanf(tab,"%s",str);
            fscanf(tab,"%d",&no);
        }
        if (ch == '\n')
        aux++;
        if(aux==n+7&&ch!='\n'){
            fgets(nomi,30,tab);
            break;
        }
        ch = getc(tab);
    }
    for(int i=0;i<(strlen(nomi));i++){
    if(nomi[i]=='\n'){
        nomi[i]='\0';
    }
   }
    strcpy((*t1).nome,nomi);
   (*t1).pinos = no;
   memcpy((*t1).campo,str,sizeof((*t1).campo));
   fclose(tab);
}



void preVisu(tabuleiro *t1, int n){
    system("cls");
    char pos_x[11]="x 1234567 ";
    char pos_y[10]=" 1234567 ";
    int no, i, j;
    int opS;
    printf("O tabuleiro é assim:\n\n");
    for(i=0;i<10;i++){
    printf("%c ",pos_x[i]);
    }
    printf("\n");
    for(i=0;i<9;i++){
        printf("%c ",pos_y[i]);
        for(j=0;j<9;j++){
        if((*t1).campo[i][j]=='*'){
            printf("  ");
        }else{
        printf("%c ",(*t1).campo[i][j]);
         }
        }
        printf("\n");
    }
    printf("\n");
    printf("Continuar jogo?\n");
    printf("(1)Jogar\t(2)Voltar\n");
    do{
    no = getch();
    }while(no>50||no<49);
    if(no==49){
        jogEmMenu(t1,n);
    }else{
        system("cls");
        qualTab();
        do{
        opS = getch();
        }while(opS<49||opS>56);
        menuS(opS);
    }
}



void Nome(tabuleiro *t1){
    system("cls");
    printf("Digite seu nome/apelido: \n");
    setbuf(stdin,NULL);
    fgets((*t1).jogador,20,stdin);
    (*t1).jogador[strlen((*t1).jogador)-1]='\0';
    system("cls");
}



void Imprimi(tabuleiro *t1){
    char pos_x[11]="x 1234567 ";
    char pos_y[10]=" 1234567 ";
    int i,j;
    printf("      ");
    for(i=0;(*t1).nome[i]!='\0';i++){
        printf("%c",(*t1).nome[i]);
    }
    printf("\n\nJogada:");
    printf(" %d\t",(*t1).contador);
    printf("Pinos Restantes:");
    printf(" %d\n\n\t",(*t1).pinos);
    for(i=0;i<10;i++){
        printf("%c ",pos_x[i]);
    }
    printf("\n");
    for(i=0;i<9;i++){
        printf("\t%c ",pos_y[i]);
        for(j=0;j<9;j++){
        if((*t1).campo[i][j]=='*'){
            printf("  ");
        }else{
        printf("%c ",(*t1).campo[i][j]);
        }
        }
        printf("\n");
    }
    printf("\n");
}



