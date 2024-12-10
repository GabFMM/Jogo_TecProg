#include <SFML/Graphics.hpp>
#include <iostream>
#include "ListaTemplate.h"
#include "Lista2.h"
#include "Gerenciador_Grafico.h"
#include "Jogador.h"
#include "Projetil.h"
#include "ListaEntidades.h"
#include "Plataforma.h"
#include "Gerenciador_Colisoes.h"
#include "Obst_Dificil.h"
#include "Obst_Medio.h"


using namespace std;
class Pessoa
{
private:
    string nome;
public:
    Pessoa(const string& name = " ") :nome(name) {};
    ~Pessoa() {};
    void imprime()const{ cout << "Nome :" << nome << endl; }
};

int main()
{
   
    Gerenciadores::Gerenciador_Grafico* gg = new Gerenciadores::Gerenciador_Grafico();
    sf::Event event;
    Listas::ListaEntidades Lista;
    
    Entidades::Jogador* jog = new Entidades::Jogador(10.f, 10.f, gg,"Player");
    Entidades::Projetil pro(1, 1.5f, gg);

    
    Entidades::Plataforma plat(5, 680, gg, 10);
    Entidades::Plataforma plat2(5+plat.getBody().getGlobalBounds().width, 680, gg, 10);
    

    Entidades::Obst_Dificil obs(1,plat2.getPositionX() + plat.getBody().getGlobalBounds().width, 680, gg);
    Entidades::Plataforma plat3(obs.getPositionX() + obs.getBody().getGlobalBounds().width, 680, gg, 10);
    Entidades::Plataforma plat4(plat.getPositionX() + plat.getBody().getGlobalBounds().width, 580, gg, 10);
    Entidades::Plataforma plat5(plat.getPositionX() + plat.getBody().getGlobalBounds().width, 280, gg, 10);
    Entidades::Obst_Medio obsMedio(5.f, plat5.getPositionX() + plat.getBody().getGlobalBounds().width / 2, 500, gg);


    Lista.insert_back(static_cast<Entidades::Entidade*>(jog));
    Lista.insert_back(static_cast<Entidades::Entidade*>(&pro));
    Lista.insert_back(static_cast<Entidades::Entidade*>(&plat));
    Lista.insert_back(static_cast<Entidades::Entidade*>(&plat2));
    Lista.insert_back(static_cast<Entidades::Entidade*>(&plat3));

    Lista.insert_back(static_cast<Entidades::Entidade*>(&plat4));
    Lista.insert_back(static_cast<Entidades::Entidade*>(&plat5));

    Lista.insert_back(static_cast<Entidades::Entidade*>(&obs));
    Lista.insert_back(static_cast<Entidades::Entidade*>(&obsMedio));
    Lista.percorrer();

    Gerenciadores::Gerenciador_Colisoes* gc = new Gerenciadores::Gerenciador_Colisoes(0.5f);
    //Poderiamos converter explicitamente para obstaculo
    gc->incluirObstaculo(&plat);
    gc->incluirObstaculo(&plat2);
    gc->incluirObstaculo(&plat3);

    gc->incluirObstaculo(&plat4);
    gc->incluirObstaculo(&plat5);
    gc->incluirObstaculo(&obs);
    gc->incluirObstaculo(&obsMedio);
    gc->setJogador1(jog);

    while (gg->getOpen() )
    {
        while (gg->getWindow()->pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) 
            {
                gg->closeWindow();
            }
            
        }

        gg->render();
        Lista.executar();
        gc->executar();
        gg->display();

        cout << jog->getVidas();
        
    }

}