#include "Jogador.h"
#include "stdlib.h"
#include "Inimigo.h"
#include "BruxaThread.h"
int Entidades::Jogador::contador(0);

Entidades::Jogador::Jogador(float inlX, float inY, Gerenciadores::Gerenciador_Grafico* pgra, std::string name)
	:Personagem(inlX, inY, pgra, 10), _pontos(0), nome(name), tempoPulo(80.f), _velocidade(0.2f),
	_paralisado(false), _duracaoParalisia(0.f), _tempoParalisado(0.f), _clockParalisia(),
	_atacando(false), _texturas(), _texturasSword(), Sword(), _ehJogador1(!contador),
	_hudJogador(this)
{
	contador++;

	Sword = new sf::Sprite();
	setTipo(3);

	if (_ehJogador1)
	{
		sf::Texture* textura = new sf::Texture();

		if (!textura->loadFromFile("assets/Player1.png"))
		{
			std::cout << "Falha ao carregar textura!" << std::endl;
		}
		Ente::setTexture(textura);
		_body.setScale(0.1f, 0.1f);
		adicionarTextura("assets/Player1.png");
		adicionarTextura("assets/Player1Esquerda.png");
		
	}
	else
	{
		sf::Texture* textura = new sf::Texture();

		if (!textura->loadFromFile("assets/Player2.png"))
		{
			std::cout << "Falha ao carregar textura!" << std::endl;
		}
		Ente::setTexture(textura);
		_body.setScale(0.1f, 0.1f);
		adicionarTextura("assets/Player2.png");
		adicionarTextura("assets/Player2Esquerda.png");
	
	}
	
	

	sf::Texture* texturaSword = new sf::Texture();

	

	// tela de paralisia
	texturaTela = new sf::Texture();

	if (!texturaTela->loadFromFile("assets/TelaParalisada.png")) 
	{
		std::cout << "Falha ao carregar textura!" << std::endl;
	}

	telaParalisada.setTexture(*texturaTela);

	// tamanho da tela paralisada
	sf::Vector2u tamJanela = _pGraf->getWindow()->getSize();
	float escalaX = (float)tamJanela.x / telaParalisada.getGlobalBounds().width;
	float escalaY = (float)tamJanela.y / telaParalisada.getGlobalBounds().height;

	telaParalisada.setScale
	(
		escalaX,
		escalaY
	);

	// Posicao
	telaParalisada.setPosition(0.f, 0.f);
	

	adicionarSword("assets/EspadaReta1.png");
	adicionarSword("assets/EspadaDireita.png");
	adicionarSword("assets/EspadaEsquerda.png");
	
	
	
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
	if (Sword)
	{
		delete Sword;
	}

	_pGraf = nullptr;
	_pTexture = nullptr;
	texturaTela = nullptr;
	Sword = nullptr;
	Position.x = 0.0;
	Position.y = 0.0;

	int i;
	for (i = 0; i < 2; i++)
	{
		if (_texturas[i])
		{
			delete _texturas[i];
		}
	}
	_texturas.clear();

	for (i = 0; i < 3; i++)
	{
		if (_texturasSword[i])
		{
			delete _texturasSword[i];
		}
	}
	_texturasSword.clear();

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

void Entidades::Jogador::SetPontos(int pont)
{
	_pontos = pont;
}

int Entidades::Jogador::getPontos() const
{
	return _pontos;
}



void Entidades::Jogador::pular()
{
	if (_onGround)
	{
		_speed.y = -1.75f;
		setGround(false);
	}
}

void Entidades::Jogador::mover()
{

	_speed.x = 0;
	if (_ehJogador1)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			_speed.x += _velocidade;
			setDirecao(1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{

			tempoPulo += _clock.getElapsedTime().asMilliseconds();
			if (tempoPulo >= 80.f)
			{
				pular();
				tempoPulo = 0.f;

			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			_speed.x -= _velocidade;
			setDirecao(-1);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		{
			setAtacando(true);


			if (Sword)
			{
				setSword(getDirecao());
			}
		}
		else
		{
			setAtacando(false);
			if (Sword)
			{
				Sword->setTexture(*_texturasSword[0]);

			}
		}

	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			_speed.x += _velocidade;
			setDirecao(1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{

			tempoPulo += _clock.getElapsedTime().asMilliseconds();
			if (tempoPulo >= 80.f)
			{
				pular();
				tempoPulo = 0.f;

			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			_speed.x -= _velocidade;
			setDirecao(-1);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		{
			setAtacando(true);


			if (Sword)
			{
				setSword(getDirecao());
			}
		}
		else
		{
			setAtacando(false);
			if (Sword)
			{
				Sword->setTexture(*_texturasSword[0]);

			}
		}

	}
	
	// (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && (Position.y + _body.getGlobalBounds().height <= _pGraf->getWindow()->getSize().y))
		//_speed.y = +_velocidade;

	
	Sword->setPosition(getPosition().x + 12.0f*_direcao, getPosition().y+2.0f);
	Sword->setScale(0.1f, 0.05f);
	Position += _speed;
	setTexture(getDirecao());

}

void Entidades::Jogador::setTexture(int direcao)
{
	int index;
	if (direcao == 1)
		index = 0;
	
	else
		index = 1;
	_body.setTexture(*_texturas[index]);
}

void Entidades::Jogador::adicionarTextura(const std::string& path)
{
	sf::Texture* textura1 = new sf::Texture();
	

	if (textura1->loadFromFile(path))
	{
		_texturas.push_back(textura1);
	}
	else
	{
		std::cout << "Falha ao carregar texturas!" << std::endl;
	}
}

bool Entidades::Jogador::getAtacando() const
{
	return _atacando;
}

void Entidades::Jogador::setAtacando(bool atac)
{
	_atacando = atac;
}

void Entidades::Jogador::setSword(int direcao)
{
	int index;
	if (direcao == 1)
		index = 1;

	else
		index = 2;
	Sword->setTexture(*_texturasSword[index]);
}

void Entidades::Jogador::adicionarSword(const std::string& path)
{
	sf::Texture* textura1 = new sf::Texture();


	if (textura1->loadFromFile(path))
	{
		_texturasSword.push_back(textura1);
	}
	else
	{
		std::cout << "Falha ao carregar texturas!" << std::endl;
	}
}

void Entidades::Jogador::atacarInimigo(Entidades::Inimigo* enemy)
{
	if (enemy->getEhThread())
	{
		Entidades::BruxaThread* bru = static_cast<BruxaThread*>(enemy);
		bru->lockMutex();
		bru->operator--(1);
		bru->knockBack(this);
		bru->unlockMutex();
	}
	else
	{
		(enemy)->operator--(1);
		(enemy)->knockBack(this);
	}
	
	if (enemy->getVidas() <= 0)
	{
		SetPontos(getPontos() + enemy->getMaldade());
	}
}


bool Entidades::Jogador::getEhJogador1() const
{
	return _ehJogador1;
}

void Entidades::Jogador::executar()
{
	if (!_paralisado) 
	{
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
	_hudJogador.executar();
	_hudJogador.setContador(_num_vidas);
	
	desenhar();
	_pGraf->desenhar(Sword);

}