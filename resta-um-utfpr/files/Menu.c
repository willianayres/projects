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



void Inicio(){
    int op;
    do{
       system("cls");
       printf("<<Menu Principal>>\n");
       printf("\n(1) Instruções do Jogo");
       printf("\n(2) Jogar");
       printf("\n(3) Histórico");
       printf("\n(4) Sair\n\n");
       op = getch();
       menu(&op);
    }while(op>52||op<49);
}



void qualTab(){
    printf("<<Tipo de Tabuleiro>>\n\n");
    printf("(1) Cruz\n");
    printf("(2) Mais\n");
    printf("(3) Banquinho\n");
    printf("(4) Flecha\n");
    printf("(5) Pirâmide\n");
    printf("(6) Losango\n");
    printf("(7) Tradicional\n");
    printf("(8) Voltar\n");
}



void menu(int *op){
     int opS;
     FILE *fileregra;
     switch(*op){
         case 49 : system("cls");
                   fileregra = fopen("regra.txt","r");
                   if(fileregra==NULL){
                   printf("Erro ao abrir o arquivo");
                   }
                   int n = 0;
                   char c = fgetc(fileregra);
                   while(c!= EOF){
                   n++;
                   c = fgetc(fileregra);
                   }
                   rewind(fileregra);
                   char *leitura;
                   leitura = (char *)calloc(n,sizeof(char));
                   while(fgets(leitura,n,fileregra) != NULL){
                   printf("%s",leitura);
                   }
                   fclose(fileregra);
                   free(leitura);
                   printf("\n\n\t\t\t");
                   printf("** Aperte qualquer tecla para voltar ao Menu **");
                   getch();
                   system("cls");
                   Inicio();
         break;
         case 50 : system("cls");
                   qualTab();
                   do{
                   opS = getch();
                   }while(opS<49||opS>56);
                   menuS(opS);
         break;
         case 51 : system("cls");
                   menuEstat();
         break;
         case 52 : system("cls");
                   exit(0);
         break;
      }
}



void menuS(int opS){
     int n;
     tabuleiro *t1 = (tabuleiro *)malloc(sizeof(tabuleiro));
     switch(opS){
     case 49 :
         n=0;
         declaraTabu(t1,n);
         preVisu(t1,n);
     break;
     case 50 :
         n=1;
         declaraTabu(t1,n);
         preVisu(t1,n);
     break;
     case 51 :
         n=2;
         declaraTabu(t1,n);
         preVisu(t1,n);
     break;
     case 52 :
         n=3;
         declaraTabu(t1,n);
         preVisu(t1,n);
     break;
     case 53 :
         n=4;
         declaraTabu(t1,n);
         preVisu(t1,n);
     break;
     case 54 :
         n=5;
         declaraTabu(t1,n);
         preVisu(t1,n);
     break;
     case 55 :
         n=6;
         declaraTabu(t1,n);
         preVisu(t1,n);
     break;
     case 56 :
         free(t1);
         printf("\n");
         system("cls");
         Inicio();
     default :
         free(t1);
         printf("Opção Inválida !!!\n");
         system("cls");
         Inicio();
     }
}



void escolha(){
     printf("<Menu de Escolha>\n\n");
     printf("(1)Voltar ao Menu");
     printf("\n(2)Abrir Histórico");
     printf("\n(3)Jogar Novamente");
     printf("\n(4)Sair");
     printf("\n");
}



void menuT(int opT){
    int opS;
    switch(opT){
      case 49:
        system("cls");
        Inicio();
      break;
      case 50:
        system("cls");
        estatis();
        escolha();
        do{
         opT = getch();
         }while(opT<49||opT>52);
         menuT(opT);
      break;
      case 51:
         system("cls");
         qualTab();
         do{
         opS = getch();
         }while(opS<49||opS>56);
         menuS(opS);
      break;
      case 52:
        system("cls");
        exit(0);
      default :
        printf("Opção Inválida !!!\n");
        system("cls");
        Inicio();
    }
}



void menuEstat(){
    int opE;
    system("cls");
    printf("<Menu de Histórico>\n\n");
    printf("(1)Voltar ao Menu");
    printf("\n(2)Abrir Histórico");
    printf("\n(3)Abrir Records");
    printf("\n(4)Limpar Histórico\n");
    do{
    opE = getch();
    }while(opE>52||opE<49);
    switch(opE){
    case 49: system("cls");
             Inicio();
    break;
    case 50: system("cls");
             estatis();
             menuEstat();
    break;
    case 51: system("cls");
             abreRecord();
             menuEstat();
    break;
    case 52: Conteudo();
             system("cls");
             menuEstat();
    break;
    default: system("cls");
             Inicio();
    }
}


