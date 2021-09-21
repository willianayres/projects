#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "textos.h"

volatile int exit_program;
volatile int timer;
volume *vol;
bitmaps *apr;

// Function to save the previously move. //
void saveMove(board *t1)
{
    FILE *file=openFile("files\\returnboard.txt","w+"); //Open the file for writing.//
    fprintf(file," ");                                  //Put a empty space.//
    int i,j;
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)                                //Put all the board on the file.//
            fprintf(file,"%c",t1->board[i][j]);
    }
    fprintf(file,"\n");                                 //Put a break line on the end of the file.//
    closeFile(file);                                    //Close the file.//
}
// ------------------------------------- //

// Function to return the board to the previously move. //
void returnMove(board *t)
{
    char ch,b[82];                                      //Auxiliary variables.//
    int i;
    t->piece=0;                                         //Reset the number of pines.//
    FILE *file=openFile("files\\returnboard.txt","r");  //Open the file to read.//
    while(ch!=EOF)                                      //Read the file until the end.//
    {
        fscanf(file,"%s",b);                            //Get the board in string format.//
        ch=getc(file);
    }
    for(i=0;i<82;i++)                                   //Count the number of pines.//
    {
        if(b[i]=='I')
        t->piece++;
    }
    memcpy(t->board,b,sizeof(t1->board));               //Transform the string to a matrix board.//
    closeFile(file);                                    //Close the file.//
}
// ---------------------------------------------------- //

// Function to save the information of the game after ends. //
void saveHistoric(board *t1)
{
    FILE *file=openFile("files\\historic.txt","a+");      //Open the file to append.//
    t1->player[strlen(t1->player)]='\0';                  //Put the END string character.//
    int i;
    for(i=0;i<strlen(t1->player);i++)                     //Find $ on the string and change to S.
    {
        if(t1->player[i]=='$')
            t1->player[i]='S';
    }
    fprintf(file,"%-20s ",t1->player);                    //Save the information formated on the file.//
    fprintf(file,"%-30s ",t1->name);
    fprintf(file,"%-18s",t1->result);
    fprintf(file,"%-11d",t1->points);
    fprintf(file,"%d:%02d\n",(timer/60)%60,timer%60);
    closeFile(file);                                      //Close the file.//
}
// -------------------------------------------------------- //

// Function to check if the player bet the record. //
void checkRecord(board *t1,int help)
{
    int aux=0,n,n2,n3,naux;                         //Auxiliary variables.//
    char ch, re[7];                                 //Auxiliary characters.//
    FILE *file=openFile("files\\ranking.txt","r");  //File for reading.//
    while(ch!=EOF)                                  //Read the file until the end.//
    {
        if(aux==help&&ch=='$')                      //Check for right line and ignore $.//
        fscanf(file,"%s %d %d:%d",re,&n,&n2,&n3);   //Scan the variables.//
        if(ch=='\n')                                //Check for break lines.//
            aux++;
        ch=getc(file);                              //Get the character from the file.//
    }
    closeFile(file);                                //Close the file.//
    naux=60*n2+n3;                                  //Convert the timer to secs.//
    if(!strcmp(re,t1->result)&&n>=t1->points&&naux>=timer)
    {                                               //Check if it beats the record.//
        clearRecord(t1,help);                       //Erase the actual record.//
        saveRecord(t1);                             //Save the new one.//
        copyFile("files\\rankinga1.txt","files\\rankinga2.txt","a");
        copyFile("files\\ranking.txt","files\\rankinga1.txt","w");
        clearFile("files\\rankinga1.txt","");       //Auxiliary functions.//
        clearFile("files\\rankinga2.txt","");
    }
}
// ----------------------------------------------- //

// Function to divide the file in 2. //
void clearRecord(board *t1,int help)
{
    char cha;                                           //Auxiliary variables.//
    int cont=0;
    FILE *file1=openFile("files\\ranking.txt","r");     //Open the files.//
    FILE *file2=openFile("files\\rankinga1.txt","w");
    FILE *file3=openFile("files\\rankinga2.txt","w");
    cha=getc(file1);
    while(cha!=EOF)                                     //Read the file until the end.//
    {
        if(cha=='\n')                                   //Break line check.//
            cont++;
        if(cont<=help&&cont!=help)                      //Right line.//
            putc(cha,file2);                            //Divide the main file in 2.//
        if(cont>help)
            putc(cha,file3);
        cha=getc(file1);
    }
    closeFile(file1);                                   //Close the files.//
    closeFile(file2);
    closeFile(file3);
}
// --------------------------------- //

// Function to save the new record on the auxiliary file. //
void saveRecord(board *t1)
{
    FILE *file=openFile("files\\rankinga1.txt","a+");   //Open the file to append.//
    if(!strcmp(t1->name,"Padrao"))                      //Check if it's the first one.//
        fprintf(file," ");
    fprintf(file,"\n%-20s ",t1->player);                //Save the record formated.//
    fprintf(file,"%-30s ",t1->name);
    fprintf(file,"$%-18s",t1->result);
    fprintf(file,"%-11d",t1->points);
    fprintf(file,"%d:%02d",(timer/60)%60,timer%60);
    closeFile(file);                                    //Close the file.//
}
// ------------------------------------------------------ //

// Function to save the settings on a file. //
void saveSettings(volume* vol, bitmaps *apr)
{
    FILE *file=openFile("files\\settings.txt","w"); //Open the file to write.//
    fprintf(file," %s\n",apr->boardI);              //Save the settings formated.//
    fprintf(file," %s\n",apr->boardF);
    fprintf(file," %s\n",apr->pieceBg);
    fprintf(file," %s\n",apr->bg);
    fprintf(file," %s\n",apr->buttonB);
    fprintf(file," %s\n",apr->logo);
    fprintf(file," %s\n",apr->buttonM);
    fprintf(file," %s\n",apr->buttonS);
    fprintf(file," %s\n",apr->title);
    fprintf(file," %s\n",apr->piece);
    fprintf(file," %s\n",apr->pieceV);
    fprintf(file," %d %d\n",vol->som,vol->musica);
    closeFile(file);                                //Close the file.//
}
// ---------------------------------------- //

// Function to get the appearance and sound settings from a file. //
void setSettings(volume* vol,bitmaps *apr)
{
    char c;                                                 //Auxiliary variable to read the file.//
    int aux=0;                                              //Auxiliary counter.//
    FILE *file=openFile("files\\settings.txt","r");         //Open the file for reading.//
    while(c!= EOF)                                          //Until reach the end.//
    {
        if(c=='\n')                                         //Count for break lines.//
            aux++;
        if(aux==0&&c!='\n')
            fscanf(file,"%s",apr->boardI);                  //Get the English board bitmap.//
        if(aux==1&&c!='\n')
            fscanf(file,"%s",apr->boardF);                  //Get the French board bitmap.//
        if(aux==2&&c!='\n')
            fscanf(file,"%s",apr->pieceBg);                 //Get the space of the pine bitmap.//
        if(aux==3&&c!='\n')
            fscanf(file,"%s",apr->bg);                      //Get the background bitmap.//
        if(aux==4&&c!='\n')
            fscanf(file,"%s",apr->buttonB);                 //Get the button bitmap.//
        if(aux==5&&c!='\n')
            fscanf(file,"%s",apr->logo);                    //Get the logo bitmap.//
        if(aux==6&&c!='\n')
            fscanf(file,"%s",apr->buttonM);                 //Get the button bitmap.//
        if(aux==7&&c!='\n')
            fscanf(file,"%s",apr->buttonS);                 //Get the button bitmap.//
        if(aux==8&&c!='\n')
            fscanf(file,"%s",apr->title);                   //Get the title bitmap.//
        if(aux==9&&c!='\n')
            fscanf(file,"%s",apr->piece);                   //Get the pine bitmap.//
        if(aux==10&&c!='\n')
            fscanf(file,"%s",apr->pieceV);                  //Get the validation bitmap.//
        if(aux==11)
            fscanf(file,"%d %d",&vol->som,&vol->musica);    //Get the volume.
        c=fgetc(file);
    }
    if(!strcmp(apr->buttonM,"bitmaps\\button\\medium1.bmp"))   //Check the color.//
        cor_state=VERDIN;
    else if(!strcmp(apr->buttonM,"bitmaps\\button\\medium2.bmp"))
        cor_state=CINZA;
    else if(!strcmp(apr->buttonM,"bitmaps\\button\\medium3.bmp"))
        cor_state=VERDE;
    else if(!strcmp(apr->buttonM,"bitmaps\\button\\medium4.bmp"))
        cor_state=VERMELHO;
    else if(!strcmp(apr->buttonM,"bitmaps\\button\\medium5.bmp"))
        cor_state=PRETIN;
    if(!strcmp(apr->buttonM,"bitmaps\\button\\medium5.bmp"))   //Check the font color.//
        fonte_state=BRANCO;
    else
        fonte_state=PRETO;
    closeFile(file);                                        //Close the file.//
}
// -------------------------------------------------------------- //
