#include <locale.h>
#include "Menu.h"


int main(){
    setlocale(LC_ALL,"portuguese");         //Fun��o para utiliz��o de caracteres especiais.//
    system("title RestaUm");                //Fun��o para redefinir nome do console.//
    system("mode con:cols=100 lines=30");   //Fun��o para redefinir tamanho do console.//
    inicio();                               //Fun��o para iniciar o jogo.//
    return 0;
}
