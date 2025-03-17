#include "Jogador.h"
#include "stdlib.h"
#include "Inimigo.h"
#include "Constantes.h"

int Entidades::Jogador::contador(0);

void Entidades::Jogador::setContador(int i)
{
	Jogador::contador = i;
}

Entidades::Jogador::Jogador(float inlX, float inY, Gerenciadores::Gerenciador_Grafico* pgra, std::string name)
	: Personagem(inlX, inY, pgra,Constantes::VIDAS_JOGADOR), _pontos(0), nome(name), tempoPulo(Constantes::TEMPO_PULO), _velocidade(Constantes::VEL_JOGADOR), _paralisado(false), _duracaoParalisia(0.f), _tempoParalisado(0.f), _clockParalisia(),
	_atacando(false), _texturas(), _texturasSword(), Sword(), _ehJogador1(!contador)
{
	contador++;

	Sword = new sf::Sprite();
	setTipo(Constantes::TIPO_JOGADOR);

	if (_ehJogador1)
	{
		sf::Texture* textura = _pGraf->getTextura("Jogador1_Direita");

		Ente::setTexture(textura);
		_body.setScale(0.1f, 0.1f);
		adicionarTextura("Jogador1_Direita");
		adicionarTextura("Jogador1_Esquerda");
		
	}
	else
	{
		sf::Texture* textura  = _pGraf->getTextura("Jogador2_Direita");

		Ente::setTexture(textura);
		_body.setScale(0.1f, 0.1f);
		adicionarTextura("Jogador2_Direita");
		adicionarTextura("Jogador2_Esquerda");
	}	

	// tela de paralisia
	texturaTela = _pGraf->getTextura("Tela_Paralisada");

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
	

	adicionarSword("Espada");
	adicionarSword("Espada_Direita");
	adicionarSword("Espada_Esquerda");
}

Entidades::Jogador::~Jogador()
{
	if (contador > 0)
		contador--;

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


bool Entidades::Jogador::getParalisado() const
{
	return _paralisado;
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
		_speed.y = Constantes::PULO_JOGADOR;
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
	sf::Texture* textura1 = _pGraf->getTextura(path);
	_texturas.push_back(textura1);
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
	sf::Texture* textura1 = _pGraf->getTextura(path);
	_texturasSword.push_back(textura1);
}

void Entidades::Jogador::atacarInimigo(Entidades::Inimigo* enemy)
{
	(enemy)->operator--(1);
	(enemy)->knockBack(this);
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
	else 
	{
		_tempoParalisado += _clockParalisia.getElapsedTime().asSeconds();

		if (_tempoParalisado > _duracaoParalisia) 
		{
			_tempoParalisado = 0.f;
			_paralisado = false;
			_clockParalisia.restart();
		}

		_pGraf->getWindow()->draw(telaParalisada);
	}

	// Limita a velocidade horizontal
	if (_speed.x > 0.3f)
		setSpeed(0.3f, getSpeedY());
	

	if (_num_vidas <= 0)
		setVivo(false);
	

	if (_onGround)
		restartClock();
	

	_body.setPosition(Position);
	desenhar();
	_pGraf->desenhar(Sword);
}

// Salva o buffer no arquivo Salvamento.txt
void Entidades::Jogador::SalvarDataBuffer(std::ofstream& arquivo)
{
	try
	{
		arquivo.open("Salvamento.txt", std::ios::app);

		if (!arquivo.is_open())
		{
			throw std::runtime_error("Erro ao abrir o arquivo para escrita.");
		}

		arquivo << buffer.str();

		arquivo.close();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exceção em salvarDados: " << e.what() << std::endl;
	}
}

void Entidades::Jogador::registraDados()
{
	Entidades::Personagem::registraDados();
	buffer << nome << "\n";
}


