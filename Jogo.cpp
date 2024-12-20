#include "Jogo.h"
#include <iostream>


/*
	StateNum � uma variavel que permite o fluxo de diferentes estados no jogo
	Tipos de stateNum's:

	10 - menu
	11 - menu de ranking (exemplo)
	20 - fase 1, floresta
	21 - fase 2, ...
*/

Jogo::Jogo(std::string nome) : stateNum(10)

{
	_GerenciadorGr�fico = Gerenciadores::Gerenciador_Grafico::getInstancia();
	_jogador1 = new Entidades::Jogador(0, 0, _GerenciadorGr�fico, nome);

	_florest = nullptr;
	_menu = nullptr;

}

Jogo::~Jogo()
{
	if (_jogador1)
	{
		delete _jogador1;
	}
	if (_GerenciadorGr�fico)
	{
		delete _GerenciadorGr�fico;
	}
	if (_florest)
	{
		delete _florest;
	}
}

void Jogo::executar()
{
	while (_GerenciadorGr�fico->getOpen()) 
	{
		sf::Event event;
		while (_GerenciadorGr�fico->getWindow()->pollEvent(event)) 
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				_GerenciadorGr�fico->closeWindow();
				
		}

		_GerenciadorGr�fico->clear();

		switch (stateNum) 
		{
			// Cria menu principal
		case 10:
			criaMenu();
			JogarMenu();
			stateNum = _menu->getStateNum();
			break;

			// Cria o menu de ranking
		case 11:
			break;

			// Cria a fase 1, floresta
		case 20:
			criaFloresta();
			JogarFloresta();
			break;
		}

		_GerenciadorGr�fico->display();
	}
}

void Jogo::JogarFloresta()
{
	_florest->executar();
}



void Jogo::criaMenu() {
	if (_menu == nullptr) {
		_menu = new Menu(_GerenciadorGr�fico);

		// Destroi o estado anterior
		if (_florest != nullptr) 
		{
			delete _florest;
			_florest = nullptr;
		}
	}
}

void Jogo::JogarMenu() 
{
	_menu->executar();
}

void Jogo::criaFloresta() 
{
	if (_florest == nullptr) {
		_florest = new Fases::Floresta(_GerenciadorGr�fico, _jogador1);

		_florest->criarInimigos();
		_florest->criarObstaculos();

		
		// destroi o estado anterior
		if(_menu != nullptr){
			delete _menu;
			_menu = nullptr;
		}
		
	}
}


