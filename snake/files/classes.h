#ifndef CLASSES_H_INCLUDED
#define CLASSES_H_INCLUDED


#include <iostream>     //Biblioteca padrão//
#include <vector>       //Biblioteca de vetores//
#include <string>       //Biblioteca de strings//
#include <time.h>       //Biblioteca para timer//
#include "position.h"   //Biblioteca para checar posição//


/// Classe Campo ///
class Campo
{
    private:
        std::string nome;            //Nome do campo//
        int tamx;                    //Tamanho horizontal do campo//
        int tamy;                    //Tamanho vertical do campo//
    public:
        Campo();                     //Método Construct padrão//
        Campo(int,int);              //Método Construct personalizado//
        std::string get_nome();      //Método para acessar o nome//
        int get_tamx();              //Método para acessar tamx//
        int get_tamy();              //Método para acessar tamy//
        void print_campo();          //Método de impressão do campo//
};

/// Classe Cobra ///
class Cobra
{
    private:
        int t;                  //Tamanho da cobra//
        int d;                  //Direção que a cobra segue//
    public:
        Cobra();                //Método Construct padrão//
        std::vector <int> cx;   //Vetor de posições x da cobra//
        std::vector <int> cy;   //Vetor de posições y da cobra//
        void set_cx(int);       //Método para empilhar a posição x//
        void set_cy(int);       //Método para empilhar a posição y//
        int get_t();            //Método para acessar t//
        void att_t(int);        //Método para atualizar o t//
        int get_d();            //Método para acessar d//
        void att_d(int);        //Método para atualizar o d//
};

/// Classe Info ///
class Info
{
    private:
        int vel;                    //Velocidade do time//
        int vel2;                   //Velocidade inical//
        int pontos;                 //Quantidade de pontos//
        int nivel;                  //Nivel//
    public:
        Info();                     //Método Construct padrão//
        Info(int,int vel,int vel2); //Método Construct personalizado//
        int get_vel();              //Recupera vel//
        void att_vel(int);          //Atualiza a velocidade do timer//
        int get_vel2();             //Recupera vel2//
        void att_vel2(int);         //Atualiza a velocidade inicial//
        int get_pontos();           //Recupera pontos//
        void att_pontos(int);       //Atualiza a quantidade de pontos//
        int get_nivel();            //Recupera nivel//
        void att_nivel(int par);           //Confere o nivel//
};

/// Classe Maça ///
class Maca
{
    private:
        int mx;                     //Posição x da maça//
        int my;                     //Posição y da maça//
    public:
        int get_mx();               //Recupera mx//
        int get_my();               //Recupera my//
        void new_maca(int,int);     //Atualiza posição da maça//
};


#endif // CLASSES_H_INCLUDED
