#include "Jogo.h"
#include <iostream>
Jogo::Jogo(std::string nome)

{
	_GerenciadorGr�fico = new Gerenciadores::Gerenciador_Grafico();
	_jogador1 = new Entidades::Jogador(0, 0, _GerenciadorGr�fico, nome);
	_florest = new Fases::Floresta(_GerenciadorGr�fico, _jogador1);
	
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
	Menu();
}

void Jogo::JogarFloresta()
{
	_florest->executar();
}

void Jogo::mostrarRanking()
{
}

void Jogo::Menu()
{
	int op = -1;
	while (op != 0)
	{
		std::cout << "1 Fase Floresta" << std::endl;
		std::cout << "2 Ranking " << std::endl;
		std::cout << "0 Sair" << std::endl;
		std::cin >> op;
		switch(op)
		{
		case 1:
			JogarFloresta();
			break;

		case 2:
			mostrarRanking();
			break;

		case 0:
			exit(1);

		}
	}
}
