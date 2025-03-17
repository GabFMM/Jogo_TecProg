#include "Mago.h"
#include "Constantes.h"

// IMPORTANTE
// direcao = -1 eh esquerda, direcao = 1 eh direita
// _clock e _segundos controlam a frequencia de bater do boss

Entidades::Mago::Mago(float inicialX, float inicialY, Gerenciadores::Gerenciador_Grafico* pgra, Entidades::Jogador* pJog1, Entidades::Jogador* pJog2, int vidas)
	: Inimigo(inicialX, inicialY, pgra, pJog1,pJog2, vidas), 
	_vidasPerdidas(0), _projetil(nullptr), _segundosIntervaloPro(0.f) 
{

	setMaldade(Constantes::MALDADE_MAGO);
	setTipo(Constantes::TIPO_MAGO);
	_speed.x = Constantes::VEL_MAGO;

	sf::Texture* textura = _pGraf->getTextura("Mago");
	setTexture(textura);
	_body.setScale(0.1f, 0.1f);

	_clock.restart();
	deltaTime.restart();
}

Entidades::Mago::~Mago() 
{
	_projetil = nullptr;
	_pJog1 = nullptr;
	_pJog2 = nullptr;
	_vidasPerdidas = 0;
	_direcao = 0;
}

void Entidades::Mago::setProjetil(Entidades::Projetil* pProj) 
{
	if (pProj == nullptr) 
	{
		std::cerr << "Ponteiro de projetil invalido. Impossivel vincular com boss.\n";
		return;
	}

	_projetil = pProj;
}

void Entidades::Mago::executar() 
{
	if (_num_vidas <= 0)
	{
		setVivo(false);
	}

	float dt = deltaTime.restart().asSeconds();

	_segundos += dt;
	_segundosIntervaloPro += dt;

	verificarVida();

	desenhar();
	 
	danificar(_pJog1);
}

void Entidades::Mago::verificarVida() {
	if (_vidasPerdidas > _num_vidas / 2) {
		_speed.x = Constantes::VEL_MAGO_BUFF;
		//Maldade mudada para 2
		setMaldade(Constantes::MALDADE_MORTOVIVO);
	}
}

void Entidades::Mago::mover() 
{
	Entidades::Jogador* jogadorAlvo = getJogadorMaisProximo();
	if (jogadorAlvo) 
	{
		if ((jogadorAlvo->getPositionX() - getPositionX() < 0.f))
			_direcao = -1;
		else
			_direcao = 1;

		sf::Vector2f velocidadeAtual = _speed;
		velocidadeAtual.x *= _direcao;

		Position += velocidadeAtual;
		_body.setPosition(Position);
	}
}

void Entidades::Mago::danificar(Entidades::Jogador* pJog) {
	
	// Fora de alcance
	if (getDistanciaInicioVector().x > Constantes::DISTANCIA_ATIVACAO_MAGO) return;
	
	// Dentro do alcance para se mover
	mover();
	Entidades::Jogador* jogProximo = getJogadorMaisProximo();
	// Dentro do alcance para atirar
	if (jogProximo == _pJog1)
	{
		if (getDistanciaJogador1() > _body.getGlobalBounds().width * 2.f) 
		{
			atirar();
		}
		// Dentro do alcance para bater
		else 
		{
			bater();
		}
	}
	else
	{
		if (getDistanciaJogador2() > _body.getGlobalBounds().width * 2.f) 
		{
			atirar();
		}
		// Dentro do alcance para bater
		else 
		{
			bater();
		}
	}
	
}

void Entidades::Mago::atirar() 
{
	// Cria o projetil
	Entidades::Jogador* jogadorProximo = getJogadorMaisProximo();

	if (!_projetil->getLancar() && _segundosIntervaloPro > 3.f) {
		// Zera o cronometro
		_segundosIntervaloPro = 0.f;

		// "Cria" projetil
		_projetil->setPosition
		(
			getPositionX() + (float) getBody().getGlobalBounds().width / 2.f,
			getPositionY()
		);

		if (jogadorProximo == _pJog1) 
		{
			_projetil->lancar
			(
				0.30f * _direcao, 
				(float)_projetil->calcularForcaY(getDistanciaJogador1(), Constantes::GRAVIDADE, 0.30f) * -1,
				getMaldade()
			);
		}
		else
		{
			_projetil->lancar
			(
				0.30f * _direcao, (float)_projetil->calcularForcaY(getDistanciaJogador2(), Constantes::GRAVIDADE, 0.30f) * -1, getMaldade()
			);
		}
		
	}
}

void Entidades::Mago::bater() 
{
	// Intervalo entre cada ataque corpo a corpo
	if (_segundos > 0.5f) 
	{
		_segundos = 0;
		Entidades::Jogador* jogProximo = getJogadorMaisProximo();

		if (jogProximo == _pJog1)
		{
			_pJog1->operator--(Constantes::DANO_BATER);

			_pJog1->knockBack(this);
		}
		else
		{
			_pJog2->operator--(Constantes::DANO_BATER);

			_pJog2->knockBack(this);
		}
	}
}

void Entidades::Mago::setVidasPerdidas(int vidas)
{
	_vidasPerdidas = vidas;
}

void Entidades::Mago::setSegIntervalo(float seg)
{
	_segundosIntervaloPro = seg;
}

// Salva o buffer no Salvamento.txt
void Entidades::Mago::SalvarDataBuffer(std::ofstream& arquivo)
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

void Entidades::Mago::registraDados()
{
	Entidades::Inimigo::registraDados();
	buffer << _segundosIntervaloPro << " " << _vidasPerdidas << "\n";
}

