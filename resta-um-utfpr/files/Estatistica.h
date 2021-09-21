#ifndef ESTATISTICA_H_INCLUDED
#define ESTATISTICA_H_INCLUDED



// Fun��o para abrir o arquivo de hist�rico.

void estatis();

// Fun��o para abrir o arquivo de records.

void abreRecord();

// Fun��o para salvar no arquivo de hist�rico as informa��es do jogo.

void SalvaEstatis(tabuleiro *t1, tempo *temp);

// Fun��o para limpar o conte�do do arquivo de hist�rico.

void Conteudo();

// Fun��o para conferir se o jogo bate algum record.

void verifica(tabuleiro *t1, tempo *temp, int n);

// Fun��o para apagar o conte�do da linha espec�fica do arquivo de records.

void apagaRanking(tabuleiro *t1, tempo *temp, int n);

// Fun��o para armazenar os dados atualizados no arquivo de records.

void salvaRanking(tabuleiro *t1, tempo *temp);

// Fun��o para concatenar os arquivos auxiliares de records.

void armazenaRanking();

// Fun��o para armazenar o arquivo auxiliar no arquivo de records.

void arrumaRanking();



#endif // ESTATISTICA_H_INCLUDED


