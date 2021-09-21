#ifndef ESTATISTICA_H_INCLUDED
#define ESTATISTICA_H_INCLUDED


// Fun��o para abrir algum arquivo.
FILE *abreArquivo(char nome[],char t[]);

// Fun��o ler arquivo texto.
void leArquivo(char[]);

// Fun��o para limpar o conte�do do arquivo de hist�rico.
void resetaArquivo(char[]);

// Fun��o para limpar arquivo texto.
void limpaArquivo(char nome[]);

// Fun��o para abrir o arquivo de records.
void leArquivoRecord(int);

// Fun��o para salvar no arquivo de hist�rico as informa��es do jogo.
void gravaArquivo(tabuleiro*,tempo*,char[],char[]);

// Fun��o para conferir se o jogo bate algum record.
void verificaRecord(tabuleiro*,tempo*,int);

// Fun��o para apagar o conte�do da linha espec�fica do arquivo de records.
void separaArquivos(tabuleiro*,tempo*,int,char[]);

// Fun��o para concatenar os arquivos auxiliares de records.
void concatenaArquivos();

// Fun��o para armazenar o arquivo auxiliar no arquivo de records.
void copiaArquivos(char[]);


#endif // ESTATISTICA_H_INCLUDED
