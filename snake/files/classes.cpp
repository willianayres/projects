#include "classes.h"

/// Classe Campo ///
Campo::Campo()
{
    tamx = 52;  //Atribui valor padrão//
    tamy = 22;  //Define o nome do campo conforme tamanho//
    this->nome="Campo [ "+std::to_string(this->tamx-2)+" x "+std::to_string(this->tamy-2)+" ]";
}

Campo::Campo(int x, int y)
{
    this->tamx=x;   //Atribui valor personalizado//
    this->tamx=y;   //Define o nome do campo conforme tamanho//
    this->nome="Campo [ "+std::to_string(this->tamx-2)+" x "+std::to_string(this->tamy-2)+" ]";
}

std::string Campo::get_nome()
{
    return nome; //Retorna o nome do campo//
}

int Campo::get_tamx()
{
    return tamx; //Retorna o tamx do campo//
}

int Campo::get_tamy()
{
    return tamy; //Recupera tamy//
}

void Campo::print_campo()
{
    for(int i=0;i<this->tamy;i++)   //Loop para conferir tamanho//
    {
        goto_XY(0,i); //Aresta vertical esquerda//
        std::cout << (char)219;
    }
    for(int i=1;i<this->tamx;i++)
    {
        goto_XY(i,0); //Aresta horizontal superior//
        std::cout << (char)219;
    }
    for(int i=0;i<this->tamy;i++)
    {
        goto_XY(this->tamx,i); //Arsta vertical direita//
        std::cout << (char)219;
    }
    for(int i=0;i<this->tamx+1;i++)
    {
        goto_XY(i,this->tamy); //Aresta horizontal inferior//
        std::cout << (char)219;
    }
}


/// Classe Cobra ///
Cobra::Cobra()
{
    t = 1;
    d = 2;
    cx.push_back(2);    //Empilha posição inicial//
    cx.push_back(2);
    cy.push_back(5);
    cy.push_back(5);
}

void Cobra::set_cx(int x)
{
    cx.push_back(x);    //Empilha um novo valor de posição x//
}

void Cobra::set_cy(int y)
{
    cy.push_back(y);    //Empilha um novo valor de posição y//
}

int Cobra::get_t()
{
    return t; //Recupera o valor de t//
}

void Cobra::att_t(int t)
{
    this->t+=t; //Atualiza o tamanho//
}

int Cobra::get_d()
{
    return d;
}

void Cobra::att_d(int d)
{
    this->d=d; //Atualiza a direção//
}

/// Classe Info ///
Info::Info()
{
    nivel = 1;  //Nivel inicial padrão//
    vel = 200;
    vel2 = 1;
    pontos = 0;
}

Info::Info(int nivel, int vel=200, int vel2=1)
{
    this->nivel=nivel;  //Nivel inicial personalizado//
    this->vel=vel;
    this->vel2=vel2;
    pontos = 0;
}

int Info::get_vel()
{
    return vel;
}

void Info::att_vel(int vel)
{
    this->vel+=vel;     //Atualiza velocidade do timer//
}

int Info::get_vel2()
{
    return vel2;
}

void Info::att_vel2(int vel2)
{
    this->vel2+=vel2;       //Atualiza velocidade da cobra//
}

int Info::get_pontos()
{
    return pontos;
}

void Info::att_pontos(int pontos)
{
    this->pontos+=pontos;   //Atualiza a quantidade de pontos//
}

int Info::get_nivel()
{
    return nivel;
}

void Info::att_nivel(int par)
{
    this->nivel = (this->vel2 / par)+1;  //Confere o nível atual//
}


/// Classe Maça ///
int Maca::get_mx()
{
    return mx; //Recupera mx//
}

int Maca::get_my()
{
    return my; //Recupera my//
}

void Maca::new_maca(int x, int y)
{
    srand(time(NULL));              //Setando timer//
    this->mx = (rand()%(x-1))+1;    //Posição x nova e valida da maçã//
    this->my = (rand()%(y-1))+1;    //Posição y nova e valida da maçã//
}


