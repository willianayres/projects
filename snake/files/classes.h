#ifndef CLASSES_H_INCLUDED
#define CLASSES_H_INCLUDED


#include <iostream>     //Biblioteca padr�o//
#include <vector>       //Biblioteca de vetores//
#include <string>       //Biblioteca de strings//
#include <time.h>       //Biblioteca para timer//
#include "position.h"   //Biblioteca para checar posi��o//


/// Classe Campo ///
class Campo
{
    private:
        std::string nome;            //Nome do campo//
        int tamx;                    //Tamanho horizontal do campo//
        int tamy;                    //Tamanho vertical do campo//
    public:
        Campo();                     //M�todo Construct padr�o//
        Campo(int,int);              //M�todo Construct personalizado//
        std::string get_nome();      //M�todo para acessar o nome//
        int get_tamx();              //M�todo para acessar tamx//
        int get_tamy();              //M�todo para acessar tamy//
        void print_campo();          //M�todo de impress�o do campo//
};

/// Classe Cobra ///
class Cobra
{
    private:
        int t;                  //Tamanho da cobra//
        int d;                  //Dire��o que a cobra segue//
    public:
        Cobra();                //M�todo Construct padr�o//
        std::vector <int> cx;   //Vetor de posi��es x da cobra//
        std::vector <int> cy;   //Vetor de posi��es y da cobra//
        void set_cx(int);       //M�todo para empilhar a posi��o x//
        void set_cy(int);       //M�todo para empilhar a posi��o y//
        int get_t();            //M�todo para acessar t//
        void att_t(int);        //M�todo para atualizar o t//
        int get_d();            //M�todo para acessar d//
        void att_d(int);        //M�todo para atualizar o d//
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
        Info();                     //M�todo Construct padr�o//
        Info(int,int vel,int vel2); //M�todo Construct personalizado//
        int get_vel();              //Recupera vel//
        void att_vel(int);          //Atualiza a velocidade do timer//
        int get_vel2();             //Recupera vel2//
        void att_vel2(int);         //Atualiza a velocidade inicial//
        int get_pontos();           //Recupera pontos//
        void att_pontos(int);       //Atualiza a quantidade de pontos//
        int get_nivel();            //Recupera nivel//
        void att_nivel(int par);           //Confere o nivel//
};

/// Classe Ma�a ///
class Maca
{
    private:
        int mx;                     //Posi��o x da ma�a//
        int my;                     //Posi��o y da ma�a//
    public:
        int get_mx();               //Recupera mx//
        int get_my();               //Recupera my//
        void new_maca(int,int);     //Atualiza posi��o da ma�a//
};


#endif // CLASSES_H_INCLUDED
