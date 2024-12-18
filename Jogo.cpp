#include "Jogo.h"

Jogo::Jogo(std::string nome)
	:_GerenciadorGr�fico()
{
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
}

void Jogo::Menu()
{

}
