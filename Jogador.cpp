#include "Jogador.h"

Entidades::Jogador::Jogador(float inlX, float inY, Gerenciadores::Gerenciador_Grafico* pgra, std::string name)
	:Personagem(inlX, inY, pgra,4), _pontos(0), nome(name), tempoPulo(200),_velocidade(0.5f)
{
	

	sf::Texture* textura = new sf::Texture();
	
	if (!textura->loadFromFile("assets/Player1.png")) 
	{
		std::cout << "Falha ao carregar textura!" << std::endl;
	}

	setTexture(textura);
	_body.setScale(0.1f, 0.1f);

	//_body.setColor(sf::Color::Red);
	//_pGraf->desenhar(this);
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
	//Size.x = 0.0;
	//Size.y = 0.0;
}

void Entidades::Jogador::setNome(std::string& name)
{
	nome = name;
}

std::string& Entidades::Jogador::getNome()
{
	return nome;
}

void Entidades::Jogador::setPosition(float x, float y)
{
	Position.x = x;
	Position.y = y;
	_body.setPosition(Position);
}



void Entidades::Jogador::knockBack(Entidades::Entidade* ent)
{
	setPositionX(getPositionX() - 20);
	
}

void Entidades::Jogador::mover()
{
	//Esses testes de se a posicao mais o tamanho nao chegou na borda devem ser transferidos para o Gerenciador de Colisoes
 //Depois não sei se precisa desse Evento, não lembro como que o sfml captura o teclado, se usa o evento ou não

	_speed.x = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && Position.x + _body.getGlobalBounds().width < _pGraf->getWindow()->getSize().x)
		_speed.x += _velocidade;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && (Position.y >= _speed.y))
	{
		
		tempoPulo += _clock.getElapsedTime().asMilliseconds();
		if (tempoPulo >= 20)
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
