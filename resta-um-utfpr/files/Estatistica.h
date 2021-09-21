#ifndef ESTATISTICA_H_INCLUDED
#define ESTATISTICA_H_INCLUDED



// Função para abrir o arquivo de histórico.

void estatis();

// Função para abrir o arquivo de records.

void abreRecord();

// Função para salvar no arquivo de histórico as informações do jogo.

void SalvaEstatis(tabuleiro *t1, tempo *temp);

// Função para limpar o conteúdo do arquivo de histórico.

void Conteudo();

// Função para conferir se o jogo bate algum record.

void verifica(tabuleiro *t1, tempo *temp, int n);

// Função para apagar o conteúdo da linha específica do arquivo de records.

void apagaRanking(tabuleiro *t1, tempo *temp, int n);

// Função para armazenar os dados atualizados no arquivo de records.

void salvaRanking(tabuleiro *t1, tempo *temp);

// Função para concatenar os arquivos auxiliares de records.

void armazenaRanking();

// Função para armazenar o arquivo auxiliar no arquivo de records.

void arrumaRanking();



#endif // ESTATISTICA_H_INCLUDED


