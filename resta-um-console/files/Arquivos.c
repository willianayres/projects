#include "Menu.h"
#include "Tabuleiro.h"
#include "Principal.h"
#include "Arquivos.h"


// Fun��o para abrir algum arquivo.
FILE *abreArquivo(char nome[],char t[])
{
    FILE *file=fopen(nome,t);               //Abre o arquivo para alguma a��o.//
    if(!strcmp(t,"r"))                      //Se for para leitura.//
    {
        if(file==NULL)                      //Confere se o arquivo existe.//
        {
            printf("\n\nERRO AO ABRIR O ARQUIVO!\n\n");
            exit(1);
        }
    }
    return file;                            //Retorna o endere�o do ponteiro para o arquivo.//
}

// Fun��o ler arquivo texto.
void leArquivo(char nome[])
{
    FILE *file=abreArquivo(nome,"r");               //Abre o arquivo para leitura.//
    int n=0;
    char c;
    while(c!=EOF)                                   //Conta quantos caracteres o arquivo possu�.//
    {
        n++;
        c=fgetc(file);
    }
    rewind(file);                                   //Rebobina o arquivo.//
    char *leitor=(char *)calloc(n,sizeof(char));    //Aloca espa�o suficiente.//
    while(fgets(leitor,n,file)!=NULL)
        printf("%s",leitor);                        //Imprime o leitor na tela.//
    fclose(file);
    free(leitor);
    printf("\n\n\t\t   ");
    printf("** Aperte qualquer tecla para voltar ao Menu **");
    getch();
    system("cls");
}
// ---------------------- //

// Fun��o para limpar o conte�do do arquivo de hist�rico.
void resetaArquivo(char reset[])
{
    FILE *file=abreArquivo("historico.txt","w");        //Abre o arquivo de hist�rio para regrava��o.//
    fprintf(file,"%s",reset);                     //Escreve as informa��es formatadamente.//
    fclose(file);                                 //Fecha o arquivo.//
}
// --------------------------------------------------- //

// Fun��o para limpar arquivo texto.
void limpaArquivo(char nome[])
{
    FILE *file=abreArquivo(nome,"w+");
    fclose(file);
}
// ------------------------------ //

// Fun��o para abrir o arquivo de records.
void leArquivoRecord(int r)
{
    char aux[13]="ranking";         //Inicializa com nome ranking.//
    aux[7]=r;                       //Adiciona o numero do arquivo no final.//
    strcat(aux,".txt");             //Adiciona a extens�o do arquivo no final.//
    FILE *file=abreArquivo(aux,"r");//Abre o arquivo.//
    char c;
    while(c!=EOF)                   //Enquanto n�o chega ao final do arquivo.//
    {
        if(c!='$')                  //Caract�re arbitr�rio presente no arquivo para//
            printf("%c",c);         //auxilio na leitura das informa��es.//
        if (c=='$')
            printf(" ");
        c=fgetc(file);
    }
    fclose(file);
    printf("\n\n\n\t\t   ** Aperte qualquer tecla para voltar ao Menu **");
    getch();
    system("cls");
}
// ------------------------------------ //

// Fun��o para salvar no arquivo de hist�rico as informa��es do jogo.
void gravaArquivo(tabuleiro *t1,tempo *temp,char arq[],char c[])
{
    FILE *file=abreArquivo(arq,"a+");               //Abre arquivo para adicionar informa��es.//
    fprintf(file,"%-20s ",t1->jogador);             //Grava as informa��es conforme formata��o.//
    fprintf(file,"%-30s ",t1->nome);
    fprintf(file,"%s%-17s",c,t1->resultado);
    fprintf(file,"%-11d",t1->contador);
    fprintf(file,"%d:%02d\n",temp->m,temp->s);
    if(strcmp(c,"$")!=0)
        fprintf(file,"\n");
    fclose(file);                                   //Fecha o arquivo.//
}
// --------------------------------------------------------------- //

// Fun��o para conferir se o jogo bate algum record.
void verificaRecord(tabuleiro *t1,tempo *temp,int n)
{
    char arq[13]="ranking";                             //Inicializa com nome ranking.//
    arq[7]=(n/10)+49;                                   //Adiciona o numero do arquivo no final.//
    strcat(arq,".txt");                                 //Adiciona a extens�o do arquivo no final.//
    int n1,n2,n3,aux=0;                                 //Vari�veis auxiliares.//
    char ch, r[7];
    FILE *file=abreArquivo(arq,"r");                    //Abre o arquivo para leitura.//
    while(ch!=EOF)
    {
        if(aux==((n%10)*2+2) && ch=='$')                //Se o arquivo estiver na linha correta.//
            fscanf(file,"%s %d %d:%d",r,&n1,&n2,&n3);   //Recupera os valores espec�ficos dessa linha no arquivo.//
        if(ch=='\n')                                    //Se houver quebra de linha, auxiliar incrimenta.//
            aux++;
        ch=getc(file);                                  //Passa para o pr�ximo caract�re.//
    }
    fclose(file);                                       //Fecha o arquivo.
    if((strcmp(r,t1->resultado)==0)&&n1>=t1->contador&&(60*n2+n3)>=(60*temp->m+temp->s))
    {                                                   //Se o resultado por identico, o n�mero de jogados for menor ou igual//
        separaArquivos(t1,temp,(n%10)*2+2,arq);         //e o tempo for menor ou igual, grava o novo record.//
        gravaArquivo(t1,temp,"rankingaux.txt","$");
        concatenaArquivos();
        copiaArquivos(arq);
    }
}
// ---------------------------------------------- //

// Fun��o para apagar o conte�do da linha espec�fica do arquivo de records.
void separaArquivos(tabuleiro *t1,tempo *temp,int n,char arq[])
{
    char c='@';                                 //Inicializa vari�vel de controle com valor aleat�rio.//
    int l=0;                                    //Contador de linhas no arquivo.//
    FILE *file=abreArquivo(arq,"r");            //Abre o arquivo para leitura.//
    FILE *file2=abreArquivo("rankingaux.txt","w");  //Abre os arquivos para escrita.//
    FILE *file3=abreArquivo("rankingaux2.txt","w");
    while(c!=EOF)
    {
        if(c=='\n')                             //Contador de linhas.//
            l++;
        if(l<=n+1&&l!=n&&c!='@')                //Se estiver antes da linha especifica grava no primeiro arquivo.//
            putc(c,file2);
        if(l>n+1&&c!='@')                       //Se estiver depois da linha especifica grava no segundo arquivo.//
            putc(c,file3);
        c=getc(file);
    }
    fclose(file);                               //Fecha os arquivos.//
    fclose(file2);
    fclose(file3);
}
// --------------------------------------------------------------------- //

// Fun��o para concatenar os arquivos auxiliares de records.
void concatenaArquivos()
{
    FILE *file2=abreArquivo("rankingaux2.txt","r");
    FILE *file=abreArquivo("rankingaux.txt","a");       //Abre o arquivo para adicionar conte�do.//
    int n=1000;
    char aux[n];                                        //Array auxiliar.//
    while((fgets(aux,n,file2))!=NULL)                   //Le do arquivo 2 e adiciona no arquivo 1.//
        fputs(aux,file);
    fclose(file2);                                      //Fecha os arquivos.//
    fclose(file);
}
// ------------------------------------------------------ //

// Fun��o para armazenar o arquivo auxiliar no arquivo de records.
void copiaArquivos(char arq[])
{
    FILE *file=abreArquivo("rankingaux.txt","r");   //Abre o arquivo para leitura.//
    FILE *file2=abreArquivo(arq,"w");               //Abre o arquivo para escrita.//
    char c;
    int n=0;
    while(c!=EOF)                                   //Conta quantos caract�res existem no arquivo.//
    {
        n++;
        c=getc(file);
    }
    rewind(file);                                   //Rebobina o arquivo.//
    char *leitor=(char *)calloc(n,sizeof(char));    //Aloca espa�o suficiente para o leitor.//
    while(fgets(leitor,n,file)!=NULL)               //Le de um arquivo para escrever no outro.//
        fputs(leitor,file2);
    free(leitor);                                   //Libera espa�o e fecha os arquivos.//
    fclose(file);
    fclose(file2);

    limpaArquivo("rankingaux.txt");
    limpaArquivo("rankingaux2.txt");
}
// ------------------------------------------------------------ //
