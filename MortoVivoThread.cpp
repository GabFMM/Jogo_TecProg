#include "MortoVivoThread.h"

Entidades::MortoVivoThread::MortoVivoThread(float inicialX, float inicialY, Gerenciadores::Gerenciador_Grafico* pgra,
	Entidades::Jogador* pJog1, Entidades::Jogador* pJog2, int vidas)
	:MortoVivo(inicialX, inicialY, pgra, pJog1, pJog2), ThreadCPP(),_rodar(false)
{
	setVidas(5);
	setTipo(Constantes::TIPO_MORTOVIVO_THREAD);
	setEhThread(true);

	sf::Texture* textura = _pGraf->getTextura("MortoVivoThread");
	setTexture(textura);
	_body.setScale(1.f, 1.f);
}

Entidades::MortoVivoThread::~MortoVivoThread()
{
}

void Entidades::MortoVivoThread::setRodar(bool rod)
{
	_rodar = rod;
}

void Entidades::MortoVivoThread::run()
{
	while (getVivo())
	{
		if (_rodar)
		{

			lockMutex();

			double distanciaJog1 = -1;
			double distanciaJog2 = -1;

			if (_pJog1) distanciaJog1 = getDistanciaJogador1();
			if (_pJog2) distanciaJog2 = getDistanciaJogador2();

			if ((distanciaJog1 > 0 && distanciaJog1 <= 700) || (distanciaJog2 > 0 && distanciaJog2 <= 700))
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

			int aleatorio = rand() % 7;
			if (aleatorio == _energetico)
			{
				pular();
			}
			
			unlockMutex();
			setRodar(false);
		}
	}
}

void Entidades::MortoVivoThread::executar()
{
	desenhar();
}

void Entidades::MortoVivoThread::SalvarDataBuffer(std::ofstream& arquivo)
{
	MortoVivo::SalvarDataBuffer(arquivo);
}

void Entidades::MortoVivoThread::registraDados()
{
	MortoVivo::registraDados();
}
