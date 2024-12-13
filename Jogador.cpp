#include "Jogador.h"
#include "stdlib.h"

Entidades::Jogador::Jogador(float inlX, float inY, Gerenciadores::Gerenciador_Grafico* pgra, std::string name)
	:Personagem(inlX, inY, pgra,10), _pontos(0), nome(name), tempoPulo(200.f),_velocidade(0.2f), _paralisado(false), _duracaoParalisia(0.f), _tempoParalisado(0.f)
{
	setTipo(3);

	sf::Texture* textura = new sf::Texture();
	
	if (!textura->loadFromFile("assets/Player1.png")) 
	{
		std::cout << "Falha ao carregar textura!" << std::endl;
	}

	setTexture(textura);
	_body.setScale(0.1f, 0.1f);

	// tela de paralisia
	texturaTela = new sf::Texture();

	if (!texturaTela->loadFromFile("assets/TelaParalisada.png")) {
		std::cout << "Falha ao carregar textura!" << std::endl;
	}

	telaParalisada.setTexture(*texturaTela);
	telaParalisada.setScale
	(
		5.0f,
		3.5f
	);

	// Posicao
	telaParalisada.setPosition(0.f, 0.f);
}

Entidades::Jogador::~Jogador()
{
  
    if (_pTexture)
    {
        delete _pTexture;
    }
	if (texturaTela)
	{
		delete texturaTela;
	}

	_pGraf = nullptr;
    _pTexture = nullptr;
	texturaTela = nullptr;
	Position.x = 0.0;
	Position.y = 0.0;
	
}

void Entidades::Jogador::setNome(std::string& name)
{
	nome = name;
}

std::string Entidades::Jogador::getNome()const
{
	return nome;
}

void Entidades::Jogador::setParalisado(const bool para, float duracao) 
{
	_paralisado = para;
	_duracaoParalisia = duracao;
}

void Entidades::Jogador::AumentarPontos(int pont)
{
	_pontos += pont;
}

int Entidades::Jogador::getPontos() const
{
	return _pontos;
}

void Entidades::Jogador::knockBack(Entidades::Entidade* ente)
{
	if (getPositionX() > ente->getPositionX()) 
	// se a posicao for maior que a do obstaculo, ele empurra para tras
	{
		_speed.x += 100;
	}
	// se n�o empurra pra frente 
	else
	{
		_speed.x -= 100;
	}

	Position += _speed;
	_body.setPosition(Position);
}

void Entidades::Jogador::mover()
{
	
	_speed.x = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && Position.x + _body.getGlobalBounds().width < _pGraf->getWindow()->getSize().x)
		_speed.x += _velocidade;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && (Position.y >= _speed.y))
	{
		
		tempoPulo += _clock.getElapsedTime().asMilliseconds();
		if (tempoPulo >= 80.f)
		{
			pular();
			tempoPulo = 0.f;
			
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && (Position.x >= _speed.x))
		_speed.x -= _velocidade;

	// (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && (Position.y + _body.getGlobalBounds().height <= _pGraf->getWindow()->getSize().y))
		//_speed.y = +_velocidade;

	Position += _speed;

}

void Entidades::Jogador::executar()
{
	if (!_paralisado) {
		mover();
		_clockParalisia.restart();
	}
	else {
		_tempoParalisado += _clockParalisia.getElapsedTime().asSeconds();

		if (_tempoParalisado > _duracaoParalisia) {
			_tempoParalisado = 0.f;
			_paralisado = false;
			_clockParalisia.restart();
		}

		_pGraf->getWindow()->draw(telaParalisada);
	}

	if (_speed.x > 0.3f)
	{
		setSpeed(0.3f, getSpeedY());
	}

 	if (_num_vidas <= 0)
	{
		setVivo(false);
	}

	if (_onGround)
	{
		restartClock();
	}

	_body.setPosition(Position);
	_pGraf->desenhar(this);

}
