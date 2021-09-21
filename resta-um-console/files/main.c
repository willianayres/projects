#include <locale.h>
#include "Menu.h"


int main(){
    setlocale(LC_ALL,"portuguese");         //Função para utilizção de caracteres especiais.//
    system("title RestaUm");                //Função para redefinir nome do console.//
    system("mode con:cols=100 lines=30");   //Função para redefinir tamanho do console.//
    inicio();                               //Função para iniciar o jogo.//
    return 0;
}
