#ifndef ESTATISTICA_H_INCLUDED
#define ESTATISTICA_H_INCLUDED


// Função para abrir algum arquivo.
FILE *abreArquivo(char nome[],char t[]);

// Função ler arquivo texto.
void leArquivo(char[]);

// Função para limpar o conteúdo do arquivo de histórico.
void resetaArquivo(char[]);

// Função para limpar arquivo texto.
void limpaArquivo(char nome[]);

// Função para abrir o arquivo de records.
void leArquivoRecord(int);

// Função para salvar no arquivo de histórico as informações do jogo.
void gravaArquivo(tabuleiro*,tempo*,char[],char[]);

// Função para conferir se o jogo bate algum record.
void verificaRecord(tabuleiro*,tempo*,int);

// Função para apagar o conteúdo da linha específica do arquivo de records.
void separaArquivos(tabuleiro*,tempo*,int,char[]);

// Função para concatenar os arquivos auxiliares de records.
void concatenaArquivos();

// Função para armazenar o arquivo auxiliar no arquivo de records.
void copiaArquivos(char[]);


#endif // ESTATISTICA_H_INCLUDED
