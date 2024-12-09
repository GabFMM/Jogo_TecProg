#include "Jogador.h"
#include "stdlib.h"

Entidades::Jogador::Jogador(float inlX, float inY, Gerenciadores::Gerenciador_Grafico* pgra, std::string name)
	:Personagem(inlX, inY, pgra,10), _pontos(0), nome(name), tempoPulo(200),_velocidade(0.2f),_mover(true)
{
	

	sf::Texture* textura = new sf::Texture();
	
	if (!textura->loadFromFile("assets/Player1.png")) 
	{
		std::cout << "Falha ao carregar textura!" << std::endl;
	}

	setTexture(textura);
	_body.setScale(0.1f, 0.1f);

	
}

Entidades::Jogador::~Jogador()
{
  
    if (_pTexture)
    {
        delete _pTexture;
    }

	_pGraf = nullptr;
    _pTexture = nullptr;
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

void Entidades::Jogador::setMover(const bool mover) {
	_mover = mover;
}

void Entidades::Jogador::AumentarPontos(int i)
{
	_pontos += i;
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
		if (tempoPulo >= 80)
		{
			pular();
			tempoPulo = 0;
			
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
	if(_mover)
		mover();

	if(_speed.x>0.3f)


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


void Entidades::Jogador::salvar()
{
}

void Entidades::Jogador::render()
{
}
