#include <allegro.h>
#include "file.h"

volatile int exit_program;
volatile int timer;

// Function to open a file that receives the name of the file and the way to open it. //
FILE* openFile(char name[],char type[])
{
    FILE* file=fopen(name,type);
    if(!strcmp(type,"r"))           // If it's for read, you should check if the file exists. //
    {
        if(file==NULL)
        {
            printf("\nERRO! FILE NOT FOUND!\n\n");
            exit(1);
        }
    }
    return file;
}
// ---------------------------------------------------------------------------------- //

// Function to close the a file that receives the file that was open. //
void closeFile(FILE* file)
{
    fclose(file);
}
// ------------------------------------------------------------------ //

// Function to clear the content that is in the file with this name. //
void clearFile(char name[],char c[])
{
    FILE* file=fopen(name,"w+"); // Just open the file to rewrite everything. //
    fprintf(file,"%s",c);
    closeFile(file);
}
// ----------------------------------------------------------------- //

// Function to copy a file to another. //
void copyFile(char f1[],char f2[],char t[])
{
    FILE* file1=openFile(f2,"r");           //Open the first file to read.//
    FILE* file2=openFile(f1,t);             //Open the second to append or write.//
    int n=0;
    char c=fgetc(file1);                    //Start reading the file until the end.//
    while(c!=EOF)
    {
        n++;                                //Count the number of characters.//
        c=fgetc(file1);
    }
    rewind(file1);                          //Rewind the file.//
    char *read=(char*)calloc(n,sizeof(char));
    while((fgets(read,n,file1))!=NULL)   //Read the file until the end.//
        fputs(read,file2);               //Save the reading into the file.//
    free(read);
    closeFile(file1);                       //Close the files.//
    closeFile(file2);
}
// ----------------------------------- //

// Function to save the previously move. //
void saveMove(Board *bd)
{
    FILE* file=openFile("files\\returnboard.txt","w+"); //Open the file for writing.//
    fprintf(file," ");                                  //Put a empty space.//
    int i,j;
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)                                //Put all the board on the file.//
            fprintf(file,"%c",bd->board[i][j]);
    }
    fprintf(file,"\n");                                 //Put a break line on the end of the file.//
    closeFile(file);                                    //Close the file.//
}
// ------------------------------------- //

// Function to return the board to the previously move. //
void returnMove(Board* bd)
{
    char ch,b[82];                                          //Auxiliary variables.//
    int i;
    bd->piece=0;                                            //Reset the number of pines.//
    FILE* file=openFile("files\\returnboard.txt","r");      //Open the file to read.//
    while(ch!=EOF)                                          //Read the file until the end.//
    {
        fscanf(file,"%s",b);                                //Get the board in string format.//
        ch=getc(file);
    }
    for(i=0;i<82;i++)                                       //Count the number of pines.//
    {
        if(b[i]=='I')
            bd->piece++;
    }
    memcpy(bd->board,b,sizeof(bd->board));                  //transform the string to a matrix board.//
    closeFile(file);                                        //Close the file.//
}
// ---------------------------------------------------- //

// Function to save the information of the game after ends. //
void saveHistoric(Board* bd)
{
    FILE* file=openFile("files\\historic.txt","a+");      //Open the file to append.//
    bd->player[strlen(bd->player)]='\0';                  //Put the END string character.//
    int i;
    for(i=0;i<strlen(bd->player);i++)                     //Find $ on the string and change to S.
    {
        if(bd->player[i]=='$')
            bd->player[i]='S';
    }                                                     //Save the information formated on the file.//
    fprintf(file,"%-20s %-30s %-18s%-11d",bd->player,bd->name,bd->result,bd->points);
    fprintf(file,"%d:%02d\n",(timer/60)%60,timer%60);
    closeFile(file);                                      //Close the file.//
}
// -------------------------------------------------------- //

// Function to check if the player bet the record. //
void checkRecord(Board* bd,int help)
{
    int aux=0,n,n2,n3,naux;                         //Auxiliary variables.//
    char ch,re[7];                                  //Auxiliary characters.//
    FILE* file=openFile("files\\ranking.txt","r");  //File for reading.//
    while(ch!=EOF)                                  //Read the file until the end.//
    {
        if(aux==help&&ch=='$')                      //Check for right line and ignore $.//
            fscanf(file,"%s %d %d:%d",re,&n,&n2,&n3);
        if(ch=='\n')                                //Check for break lines.//
            aux++;
        ch=getc(file);                              //Get the character from the file.//
    }
    closeFile(file);                                //Close the file.//
    naux=60*n2+n3;                                  //Convert the timer to secs.//
    if(!strcmp(re,bd->result)&&n>=bd->points&&naux>=timer)
    {                                               //Check if it beats the record.//
        clearRecord(bd,help);                       //Erase the actual record.//
        saveRecord(bd);                             //Save the new one.//
        copyFile("files\\rankinga1.txt","files\\rankinga2.txt","a");
        copyFile("files\\ranking.txt","files\\rankinga1.txt","w");
        clearFile("files\\rankinga1.txt","");       //Auxiliary functions.//
        clearFile("files\\rankinga2.txt","");
    }
}
// ----------------------------------------------- //

// Function to divide the file in 2. //
void clearRecord(Board* bd,int help)
{
    char c;                                             //Auxiliary variables.//
    int cont=0;
    FILE* file1=openFile("files\\ranking.txt","r");     //Open the files.//
    FILE* file2=openFile("files\\rankinga1.txt","w");
    FILE* file3=openFile("files\\rankinga2.txt","w");
    c=getc(file1);
    while(c!=EOF)                                       //Read the file until the end.//
    {
        if(c=='\n')                                     //Break line check.//
            cont++;
        if(cont<=help&&cont!=help)                      //Right line.//
            putc(c,file2);                              //Divide the main file in 2.//
        if(cont>help)
            putc(c,file3);
        c=getc(file1);
    }
    closeFile(file1);                                   //Close the files.//
    closeFile(file2);
    closeFile(file3);
}
// --------------------------------- //

// Function to save the new record on the auxiliary file. //
void saveRecord(Board *bd)
{
    FILE *file=openFile("files\\rankinga1.txt","a+");   //Open the file to append.//
    if(!strcmp(bd->name,"Padrao"))                      //Check if it's the first one.//
        fprintf(file," ");                              //Save the record formated.//
    fprintf(file,"\n%-20s %-30s $%-18s%-11d",bd->player,bd->name,bd->result,bd->points);
    fprintf(file,"%d:%02d",(timer/60)%60,timer%60);
    closeFile(file);                                    //Close the file.//
}
// ------------------------------------------------------ //

// Function to save the settings on a file. //
void saveSettings(Volume* vol,Paths *paths)
{
    FILE* file=openFile("files\\settings.txt","w"); //Open the file to write.//
                                                    //Save the settings formated.//
    fprintf(file," %s %s %s %s",paths->boardI,paths->boardF,paths->pieceBg,paths->bg);
    fprintf(file," %s %s %s %s",paths->buttonB,paths->logo,paths->buttonM,paths->buttonS);
    fprintf(file," %s %s %s",paths->title,paths->piece,paths->pieceV);
    fprintf(file," %d %d\n",vol->noise,vol->music);
    closeFile(file);                                //Close the file.//
}
// ---------------------------------------- //

// Function to get the appearance and sound settings from a file. //
void setSettings(Volume* vol,Paths *paths)
{
    char c;                                                 //Auxiliary variable to read the file.//
    FILE* file=openFile("files\\settings.txt","r");         //Open the file for reading.//
    while(c!=EOF)                                           //Until reach the end.//
    {
        fscanf(file,"%s %s %s %s %s %s %s %s %s %s %s %d %d",paths->boardI,paths->boardF,paths->pieceBg,
               paths->bg,paths->buttonB,paths->logo,paths->buttonM,paths->buttonS,paths->title,
               paths->piece,paths->pieceV,&vol->noise,&vol->music);
        c=fgetc(file);
    }
    if(paths->buttonM[21]=='5')                             //Check the font color.//
    {
        cor_state=PRETIN;
        fonte_state=BRANCO;
    }
    else
    {
        fonte_state=PRETO;                                  //Check for the blinking effect color.//
        if(paths->buttonM[21]=='1')
            cor_state=VERDIN;
        else if(paths->buttonM[21]=='2')
            cor_state=CINZA;
        else if(paths->buttonM[21]=='3')
            cor_state=VERDE;
        else if(paths->buttonM[21]=='4')
            cor_state=VERMELHO;
    }
    closeFile(file);                                        //Close the file.//
}
// -------------------------------------------------------------- //
