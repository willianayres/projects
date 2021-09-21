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



void estatis(){
    FILE *file;
    file = fopen("estatistica.txt","r");
    if(file == NULL){
        printf("Erro ao abrir o arquivo");
    }
    int n = 0;
    char c = fgetc(file);
    while(c!= EOF){
        n++;
        c = fgetc(file);
    }
    rewind(file);
    char *lerEstat;
    lerEstat = (char *)calloc(n,sizeof(char));
    while(fgets(lerEstat,n,file) != NULL){
        printf("%s",lerEstat);
    }
    fclose(file);
    free(lerEstat);
    printf("\n\n\t\t   ");
    printf("** Aperte qualquer tecla para voltar ao Menu **");
    getch();
    system("cls");
    return;
}



void abreRecord(){
    FILE *file;
    file = fopen("ranking.txt","r");
    if(file==NULL){
    printf("Erro ao abrir o arquivo");
    exit(1);
    }
    char c=fgetc(file);
        while (c!= EOF) {
        if (c!='$'){
        printf("%c", c);}
        if (c=='$'){
        printf(" ");}
        c = fgetc(file);}
    fclose(file);
    printf("\n\n\n\t\t   ");
    printf("** Aperte qualquer tecla para voltar ao Menu **");
    getch();
    system("cls");
}



void SalvaEstatis(tabuleiro *t1, tempo *temp){
    FILE *estat;
    estat = fopen("estatistica.txt","a+");
    fprintf(estat,"%-20s ",(*t1).jogador);
    fprintf(estat,"%-30s ",(*t1).nome);
    fprintf(estat,"%-18s",(*t1).resultado);
    fprintf(estat,"%-11d",(*t1).contador);
    fprintf(estat,"%d:%02d\n\n",temp->mint,temp->segt);
    fclose(estat);
}



void Conteudo(){
    FILE *file1;
    file1 = fopen("estatisticaneutro.txt","r");
    if(file1 == NULL){
        printf("Erro ao abrir o arquivo");
        exit(1);
    }
    FILE *file2;
    file2 = fopen("estatistica.txt","w");
    int n=90;
    char *leitor;
    leitor = (char *)calloc(n,sizeof(char));
    while(fgets(leitor,n,file1)!=NULL){
            fputs(leitor,file2);}
    free(leitor);
    fclose(file1);
    fclose(file2);
}



void verifica(tabuleiro *t1, tempo *temp, int n){
    int segaux, njaux;
    int m;
    m = 2*n + 2;
    int aux=0, nj, nj2, nj3;
    char ch, re[7];
    FILE *veri;
    veri=fopen("ranking.txt","r");
    if(veri==NULL){
    printf("Erro ao abrir o arquivo"); exit(1);}
    ch = getc(veri);
    while(ch!=EOF){
        if(aux==m&&ch=='$'){
            fscanf(veri,"%s %d %d:%d",re,&nj,&nj2,&nj3);
        }
       if(ch=='\n'){
        aux++;
       }
    ch=getc(veri);
    }
    fclose(veri);
    njaux = 60*nj2 + nj3;
    segaux = 60*(temp->mint) + temp->segt;
    if((strcmp(re,t1->resultado)==0)&&nj>=t1->contador&&njaux>=segaux){
    apagaRanking(t1,temp,n);
    salvaRanking(t1,temp);
    armazenaRanking();
    arrumaRanking();
    }
}



void apagaRanking(tabuleiro *t1, tempo *temp, int n){
    int o;
    o = 2*n + 2;
    char cha;
    int cont=0;
    FILE *rnk, *rnk2, *rnk3;
    rnk=fopen("ranking.txt","r");
    if(rnk == NULL){
    printf("Erro ao abrir o arquivo");
    exit(1);}
    rnk2=fopen("rankingaux.txt","w");
    rnk3=fopen("rankingaux2.txt","w");
    cha=getc(rnk);
    while (cha != EOF){
        if(cha=='\n'){
            cont++;
        }
        if(cont<=o+1&&cont!=o){
            putc(cha,rnk2);
        }
        if(cont>o+1){
            putc(cha,rnk3);
        }
        cha=getc(rnk);
    }
    rewind(rnk);
    rewind(rnk2);
    rewind(rnk3);
    fclose(rnk);
    fclose(rnk2);
    fclose(rnk3);
}



void salvaRanking(tabuleiro *t1, tempo *temp){
    FILE *arma;
    arma=fopen("rankingaux.txt","a+");
    fprintf(arma,"%-20s ",(*t1).jogador);
    fprintf(arma,"%-29s ",(*t1).nome);
    fprintf(arma,"$%-18s",(*t1).resultado);
    fprintf(arma,"%-11d",(*t1).contador);
    fprintf(arma,"%d:%02d\n",temp->mint,temp->segt);
    fclose(arma);
}



void armazenaRanking(){
    FILE *amz, *amz2;
    amz = fopen("rankingaux2.txt","r");
    if(amz==NULL){
    printf("Erro ao abrir o arquivo"); exit(1);}
    amz2 = fopen("rankingaux.txt","a");
    int tam=850;
    char *leitura;
    leitura =(char *)calloc(tam,sizeof(char));
    while((fgets(leitura,850,amz))!=NULL){
        fputs(leitura,amz2);
    }
    free(leitura);
    fclose(amz);
    fclose(amz2);
}



void arrumaRanking(){
    FILE *rankaux;
    rankaux = fopen("rankingaux.txt","r");
    if(rankaux == NULL){
    printf("Erro ao abrir o arquivo");
    exit(1);}
    FILE *rankaux2;
    rankaux2 = fopen("ranking.txt","w");
    int no=850;
    char *leitorrank;
    leitorrank = (char *)calloc(no,sizeof(char));
    while(fgets(leitorrank,no,rankaux)!=NULL){
    fputs(leitorrank,rankaux2);}

    free(leitorrank);
    fclose(rankaux);
    fclose(rankaux2);

    FILE *limpa, *limpa2;
    limpa = fopen("rankingaux.txt","w+");
    limpa2= fopen("rankingaux2.txt","w+");
    fclose(limpa);
    fclose(limpa2);
}


