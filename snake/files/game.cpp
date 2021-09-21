#include "game.h"


//Imprimi um quadrado com dimensões personalizadas.//
void print_quadrado(int inix=25,int iniy=6,int tamx=50,int tamy=18)
{
    system("cls");                  //Limpa a tela//
    goto_XY(inix,iniy);             //Move o cursor//
    for(int i=0;i<tamx;i++)         //Loop de tamanho//
        std::cout << (char)223;     //Imprime o charactere específico//
    goto_XY(inix,tamy);
    for(int i=0;i<tamx+1;i++)
        std::cout << (char)223;
    goto_XY(inix,iniy);
    for(int i=0;i<tamy-iniy;i++)
    {
        std::cout << (char)219;
        goto_XY(inix+tamx,iniy+i);
        std::cout << (char)219;
        goto_XY(inix,iniy+1+i);
    }
}


//Imprimi o menu.//
void print_menu()
{
    print_quadrado();                                       //Imprime quadrado de contorno//
    goto_XY(32,8);                                          //Move o cursor no console//
    std::cout << "<< Bem Vindo ao Jogo da Cobrinha!!! >>";  //Imprimi as informações//
    goto_XY(45,10);
    std::cout << "[ 1 ] Jogar";
    goto_XY(45,12);
    std::cout << "[ 2 ] Record";
    goto_XY(45,14);
    std::cout << "[ 3 ] Sair";
    goto_XY(47,16);
    std::cout << "<     >";
}


//Imprimi o record.//
void print_record()
{
    std::ifstream input("record.txt");                //Abre o arquivo para leitura do record.
    if(!input.is_open())
    {
        std::cout << "Erro ao abrir o arquivo!\n";    //Confere se foi possível abrir o arquivo.
        return;
    }
    int record;
    input >> record;                                  //Armazena o record ja escrito//
    print_quadrado();                                 //Imprimi quadrado de contorno//
    goto_XY(44,8);                                    //Move o cursor no console//
    std::cout << "<< Record >>";
    goto_XY(45,11);
    std::cout << record << " pontos";                 //Imprimi o valor do record//
    goto_XY(45,14);
    std::cout << "Voltar <<";
    getch();                                          //Espera entrada de qualquer valor para sair//
    menu();                                           //Volta para o menu//
}


//Função de menu.//
void menu()
{
    int c;                          //Variável de escolha//
    do
    {
        print_menu();               //Imprimi o menu//
        goto_XY(50,16);             //Move o cursor no console//
        c=getchar();                //Recebe a escolha do teclado//
    }while(c!=49&&c!=50&&c!=51);    //Só sai do loop a hora que a escolha for válida//

    switch(c)                       //Switch da escola//
    {
        case 49:
            system("cls");          //Limpa a tela//
            game();                 //Chama a função do jogo//
            menu();                 //A hora que o jogo termina retorna ao menu//
            break;
        case 50:
            print_record();         //Imprimi o record//
            system("cls");
            break;
        case 51:                    //Apenas finaliza a aplicação//
            system("cls");
            exit(0);
            break;
    }
}


//Funão para conferir record.//
void record(int pontos)
{
    std::ifstream input("record.txt");                //Abre o arquivo para leitura do record.
    if(!input.is_open())
    {
        std::cout << "Erro ao abrir o arquivo!\n";    //Confere se foi possível abrir o arquivo.
        return;
    }
    int record;
    input >> record;                                  //Le o record do arquivo.
    std::ofstream output("record.txt");               //Abre o arquivo para escrita do record.
    if(!output.is_open())
    {
        std::cout << "Erro ao abrir o arquivo!\n";    //Confere se o arquivo existe.
        return;
    }
    if(pontos>record)                                 //Se a tentativa for menor que o record...
        output << pontos;                             //Grava o novo record.
    else
        output << record;                             //Grava o antigo record.
}


//Função principal do jogo.//
void game()
{
    Info info;                                  //Novo objeto do tipo Info//
    Maca maca;                                  //Novo objeto do tipo Maca//
    Cobra cobra;                                //Novo objeto do tipo Cobra//
    Campo campo;                                //Novo objeto do tipo Campo//
    char saida='a';                             //Variavel de escape//

    campo.print_campo();                        //Método para imprimir o campo//

    maca.new_maca(campo.get_tamx(),campo.get_tamy());       //Gera uma nova maça no campo//

    while(saida!='s')                           //Enquanto o escape for diferente se 's'//
    {
        while(saida!='s'&&!(saida=kbhit()))     //Enquanto não houver entrada do teclado//
        {

            for(int i=cobra.get_t();i>0;i--)    //Atualiza as posições da cobra//
            {
                cobra.cx[i]=cobra.cx[i-1];
                cobra.cy[i]=cobra.cy[i-1];
            }

            switch(cobra.get_d())
            {
                case 0: cobra.cx[0]--; break;
                case 1: cobra.cy[0]--; break;
                case 2: cobra.cx[0]++; break;
                case 3: cobra.cy[0]++; break;
            }

            goto_XY(cobra.cx[cobra.get_t()],cobra.cy[cobra.get_t()]);   //Limpa o rastro desnecessário da cobra//
            std::cout << " ";

            if(maca.get_mx()==cobra.cx[0]&&maca.get_my()==cobra.cy[0])  //Se a cobra come a maça//
            {
                cobra.att_t(1);                             //Tamanho aumenta em 1//
                cobra.set_cx(1);                            //Adiciona uma posição x//
                cobra.set_cy(1);                            //Adiciona uma posição y//
                info.att_pontos(1);                         //Adiciona 1 ponto//
                for(int i=0;i<cobra.get_t();i++)            //Confere se nova maça gerada não está encima da cobra//
                {
                    if(cobra.cx[i]==maca.get_mx()&&cobra.cy[i]==maca.get_my())
                    {
                        maca.new_maca(campo.get_tamx(),campo.get_tamy());
                        i=0;
                    }
                    else
                        continue;
                }
                if(info.get_vel2()%5==0)                    //Atualiza a velocidade a cada 5 pontos//
                    info.att_vel(-1);
                info.att_vel2(1);
            }

            info.att_nivel(20);                               //Confere o nível atual//

            goto_XY(cobra.cx[0],cobra.cy[0]);               //Imprimi a ponta da cobra//
            std::cout << (char)219;

            goto_XY(maca.get_mx(),maca.get_my());           //Imprimi a maça//
            std::cout << (char)1;


            goto_XY(campo.get_tamx()+3,1);                  //Imprimi as informações//
            std::cout << "Pressione [ s ] para sair!";
            goto_XY(campo.get_tamx()+3,4);
            std::cout << "Pressione as setas para jogar!";
            goto_XY(campo.get_tamx()+3,7);
            std::cout << campo.get_nome();
            goto_XY(campo.get_tamx()+3,10);
            std::cout << "Velocidade: " << info.get_vel2();
            goto_XY(campo.get_tamx()+3,13);
            std::cout << "Nivel: " << info.get_nivel();
            goto_XY(campo.get_tamx()+3,16);
            std::cout << "Pontos: " << info.get_pontos();
            goto_XY(campo.get_tamx()+3,campo.get_tamy());
            std::cout << "By Willian Ayres";


            Sleep(info.get_vel());                          //Atualiza o console depedendo da velocidade//

            for(int i=1;i<=cobra.get_t();i++)               //Confere colisão com a própria cobra//
            {
                if(cobra.cx[0]==cobra.cx[i]&&cobra.cy[0]==cobra.cy[i])
                {
                    saida='s';
                    break;
                }                                           //Confere colisão com as bordas do campo//
            }
            if(cobra.cy[0]==0||cobra.cy[0]==campo.get_tamy()||cobra.cx[0]==0||cobra.cx[0]==campo.get_tamx())
                saida='s';

        }
        if(saida!='s')
            saida=getch();
        if(saida=='K')          //Valor ascii da seta para esquerda//
            cobra.att_d(0);
        if(saida=='H')          //Valor ascii da seta para cima//
            cobra.att_d(1);
        if(saida=='M')          //Valor ascii da seta para direita//
            cobra.att_d(2);
        if(saida=='P')          //Valor ascii da seta para baixo//
            cobra.att_d(3);
        if(cobra.cy[0]==0||cobra.cy[0]==campo.get_tamy()||cobra.cx[0]==0||cobra.cx[0]==campo.get_tamx())
            saida='s';

    }

    system("cls");              //Limpa a tela e diz mensagem de game over//

    goto_XY(43,10);
    std::cout << "Voce perdeu...";
    goto_XY(39,13);
    std::cout << "Voce esta no nivel " << info.get_nivel() << "!";
    goto_XY(40,16);
    std::cout << "Voce fez " << info.get_pontos() << " pontos!";
    goto_XY(44,19);
    std::cout << "Menu << ";

    record(info.get_pontos());  //Confere o record//

    getch();                    //Espera entrada aleatória//
}


