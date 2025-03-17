#include "MortoVivo.h"
#include "Constantes.h"

Entidades::MortoVivo::MortoVivo(float inicialX, float inicialY, Gerenciadores::Gerenciador_Grafico* pgra,
	Entidades::Jogador* pJog1, Entidades::Jogador* pJog2, int vidas)
	: Inimigo(inicialX, inicialY, pgra, pJog1, pJog2, vidas), _energetico(rand() % 7)

{
	setTipo(Constantes::TIPO_MORTOVIVO);
	setMaldade(Constantes::MALDADE_MORTOVIVO);
	_speed.x = Constantes::VEL_MORTOVIVO;

	sf::Texture* textura = _pGraf->getTextura("MortoVivo");
	setTexture(textura);
	_body.setScale(1.f, 1.f);
}

Entidades::MortoVivo::~MortoVivo()
{
	_pJog1 = nullptr;
	_pJog2 = nullptr;
}

void Entidades::MortoVivo::executar()
{
	double distanciaJog1 = -1;
	double distanciaJog2 = -1;
	
	if(_pJog1) distanciaJog1 = getDistanciaJogador1();
	if(_pJog2) distanciaJog2 = getDistanciaJogador2();

	if (
		(distanciaJog1 > 0 && distanciaJog1 <= Constantes::DISTANCIA_ATIVACAO_MORTOVIVO)
		|| (distanciaJog2 > 0 && distanciaJog2 <= Constantes::DISTANCIA_ATIVACAO_MORTOVIVO)
		)
	{
		atacar = true;
	}
	else
	{
		atacar = false;
	}

	
	if (atacar)
	{
		mover();
	}
	else
	{
		Position.y += _speed.y;
		_body.setPosition(Position);
	}

	
	if (_num_vidas <= 0)
	{
		setVivo(false);
	}

	desenhar();
	_speed.x = 0.04f;
	
}

void Entidades::MortoVivo::setEnergetico(int ener)
{
	_energetico = ener;
}

void Entidades::MortoVivo::mover()
{
	Entidades::Jogador* jogadorMaisProximo = getJogadorMaisProximo();

	if (jogadorMaisProximo != nullptr)
	{
		if (jogadorMaisProximo->getPositionX() - getPositionX() < 0.f)
		{
			_direcao = -1; // Para a esquerda
		}
		else
		{
			_direcao = 1;  // Para a direita
		}

		if (getPositionY() - jogadorMaisProximo->getPositionY() >= 150)
		{
			pular();
		}
	}

	// Verificando se o jogador mais próximo não é nulo antes de se mexer
	if (jogadorMaisProximo != nullptr)
	{
		sf::Vector2f velocidadeAtual = _speed;
		velocidadeAtual.x *= _direcao;
		Position += velocidadeAtual;
		_body.setPosition(Position);
	}

	srand(time(NULL));
	int aleatorio = rand() % 7;
	if (aleatorio == _energetico)
	{
		pular();
	}
}

void Entidades::MortoVivo::danificar(Entidades::Jogador* pJog)
{
	pJog->operator--(2);
	
	pJog->knockBack(this);
}

// Salva o buffer no Salvamento.txt
void Entidades::MortoVivo::SalvarDataBuffer(std::ofstream& arquivo)
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

void Entidades::MortoVivo::registraDados()
{
	Entidades::Inimigo::registraDados();
	buffer << _energetico << "\n";
}

