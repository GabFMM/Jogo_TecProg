#include "Cavaleiro.h"
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include "Constantes.h"

Entidades::Cavaleiro::Cavaleiro(float inicialX, float inicialY, Gerenciadores::Gerenciador_Grafico* pgra,
	Entidades::Jogador* pJog1,Entidades::Jogador*pJog2, int vidas)
	:Inimigo(inicialX, inicialY, pgra, pJog1,pJog2, vidas),_loucura()
{
	srand((unsigned int)time(NULL));

	// Atributo pertinente ao ataque
	_loucura = rand() % 7;

	setTipo(Constantes::TIPO_CAVALEIRO);

	// Corresponde ao dano base
	setMaldade(Constantes::MALDADE_CAVALEIRO);

	_speed.x = Constantes::VEL_CAVALEIRO;

	// Define em qual direcao andara
	if (rand() % 2)
	{
		_speed.x *= -1;
	}

	// Define a imagem
	sf::Texture* textura = _pGraf->getTextura("Cavaleiro");
	setTexture(textura);
	_body.setScale(0.1f, 0.1f);

	_clock.restart();
}

Entidades::Cavaleiro::~Cavaleiro()
{
	_pJog1 = nullptr;
	_pJog2 = nullptr;
}

void Entidades::Cavaleiro::executar()
{
	// controla a frequencia para bater no jogador
	_segundos += _clock.restart().asSeconds();

	mover();
	if (_num_vidas <= 0)
	{
		setVivo(false);
	}

	desenhar();
}

// Move em duas direcoes ao depender da distancia de criacao
void Entidades::Cavaleiro::mover()
{
	if (abs(getDistanciaInicioVector().x) >= Constantes::DISTANCIA_INICIO_CAVALEIRO)
	{
		_direcao *= -1;
		_speed.x *= _direcao;
	}
	Position += _speed;
	_body.setPosition(Position);
}

void Entidades::Cavaleiro::danificar(Entidades::Jogador* pJog)
{
	// Intervalo de tempo entre cada ataque
	if (_segundos > 0.75f) 
	{
		_segundos = 0.f;

		srand(time(NULL));
		int aleatorio = rand() % 7;

		if(aleatorio == _loucura)
			pJog->operator--(getMaldade());

		pJog->operator--(getMaldade());
		pJog->knockBack(this);
	}
}

// Coloca as informacoes do buffer no arquivo
void Entidades::Cavaleiro::SalvarDataBuffer(std::ofstream& arquivo)
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

void Entidades::Cavaleiro::registraDados()
{
	Entidades::Inimigo::registraDados();
	buffer << _loucura << "\n";
}

void Entidades::Cavaleiro::setLoucura(int loc)
{
	_loucura = loc;
}
