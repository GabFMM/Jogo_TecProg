#include "Hud.h"
#include "Heart.h"
#include "Jogador.h"



Fases::Hud::Hud(Entidades::Jogador* pjog)
	:_pJogador(pjog),_pontos(),_hearts(),_fonte(),_contadorVidas(_pJogador->getVidas())

{
	_hearts.clear();
	_pGraf = Gerenciadores::Gerenciador_Grafico::getInstancia();
	if (!_fonte.loadFromFile("assets/fontes/EnglishTowne.ttf")) 
	{
		std::cerr << "Erro ao incluir fonte.\n";
	}

	if (_pJogador)
	{
		if (_pJogador->getEhJogador1())
		{
			criaHeartsJog1();
			criaPontosJog1();
		}
		else
		{
			criaHeartsJog2();
			criaPontosJog2();
		}
	}
	else
		std::cerr << "Hud recebeu um ponteiro para Jogador inválido" << std::endl;

}

Fases::Hud::~Hud()
{
	_pGraf = nullptr;
	_pJogador = nullptr;
	int i;
	for (i = 0; i < _hearts.size(); i++)
	{
		if (_hearts[i])
		{
			delete _hearts[i];
			_hearts[i] = nullptr;
		}
	}
	_hearts.clear();
	// delete [] _hearts
}

void Fases::Hud::criaHeartsJog1()
{
	float posicaoBaseX = 0;
	for (int i = 0; i < 10; ++i)
	{
		Heart* heart = new Fases::Heart(_pGraf);		
		heart->setPosX(posicaoBaseX);
		_hearts.push_back(heart);
		posicaoBaseX += heart->getBody().getGlobalBounds().width;
	}

}

void Fases::Hud::criaHeartsJog2()
{
	float posicaoBaseX = (float)_pGraf->getWindow()->getSize().x;
	for (int i = 0; i < 10; ++i)
	{
		Heart* heart = new Heart(_pGraf);
		heart->setPosX(posicaoBaseX);
		_hearts.push_back(heart);
		posicaoBaseX -= heart->getBody().getGlobalBounds().width;
	}
}

void Fases::Hud::criaPontosJog1()
{
	std::string str = std::to_string(_pJogador->getPontos());
	_pontos.setFont(_fonte);
	_pontos.setString(str);
	_pontos.setCharacterSize(30);
	_pontos.setStyle(sf::Text::Style::Regular);
	_pontos.setFillColor(sf::Color::White);
	_pontos.setPosition(0, 0);
}

void Fases::Hud::criaPontosJog2()
{
	//Os pontos do jogador2 ficam em cima do ultimo coração que é o primeiro da esquerda para a direita
	int i = _hearts.size()-1;
	float posCoracao1 =(float) _hearts[i]->getBody().getPosition().x;

	std::string str = std::to_string(_pJogador->getPontos());
	_pontos.setFont(_fonte);
	_pontos.setString(str);
	_pontos.setCharacterSize(30);
	_pontos.setStyle(sf::Text::Style::Regular);
	_pontos.setFillColor(sf::Color::White);
	_pontos.setPosition(posCoracao1, 0);
}

void Fases::Hud::atualizaPontos()
{
	std::string str = std::to_string(_pJogador->getPontos());
	_pontos.setString(str);
}

void Fases::Hud::atualizaHearts()
{
	int i;
	for (i = _contadorVidas; i < _hearts.size(); i++)
	{
		_hearts[i]->updateHeart(0);
	}
	/*
	Caso façamos alguma mecanica de recuperar vida temos que mudar aqui 

	int i;
	for (i = 0; i < _hearts.size(); i++)
	{
		if(i <= _contadorVidas)
			_hearts[i]->updateHeart(1);
		
		else
			_hearts[i]->updateHeart(0);
	}

	*/
}

void Fases::Hud::setContador(int vidas)
{
	_contadorVidas = vidas;
}

void Fases::Hud::executar()
{
	_pGraf->desenhar(&_pontos);
	int i;
	for (i = 0; i < _hearts.size(); i++)
	{
		_hearts[i]->executar();
	}
	atualizaHearts();
	atualizaPontos();
}
