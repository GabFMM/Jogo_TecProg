#include "Entidade.h"
#include "Constantes.h"
/*Criar Tratamentos para kcnockback diferentes para cada Inimigo
O atual atende a bruxa mas o cavaleiro deveria inverter a direcao ao tomar dano
Talvez seja melhor teleportar ao inves de mudar o speed para que nao tenhamos problemas como a bruxa ficar muito rapida
ou o Mago ficar muito rapido tambem,ou criar uma forma da speed voltar ao valor original simulando uma desacelera��o
*/
namespace Entidades
{

	Entidades::Entidade::Entidade(float inicialX, float inicialY, Gerenciadores::Gerenciador_Grafico* pgra):
		Ente(pgra), Position(inicialX, inicialY),_clock(),_segundos(0.0f),
		_speed(0,0),_Tipo(0),_onGround(false),_vivo(true),_ehThread(false)
	{
		_body.setPosition(Position);
	}

	float Entidade::getPositionX() const
	{
		return Position.x;
	}

	void Entidade::setPositionX(float x)
	{
		Position.x = x;
	}
	float Entidade::getPositionY() const
	{
		return Position.y;
	}

	void Entidade::setPositionY(float y)
	{
		Position.y = y;
	}

	bool Entidade::getOnGround() const
	{
		return _onGround;
	}

	void Entidade::setGround(bool ong)
	{
		_onGround = ong;
	}

	void Entidade::setPosition(float x, float y)
	{
		Position.x = x;
		Position.y = y;
		_body.setPosition(Position);
	}

	sf::Vector2f Entidade::getPosition() const
	{
		return Position;
	}

	void Entidade::setSpeed(float x, float y)
	{
		_speed.x = x;
		_speed.y = y;
	}

	float Entidade::getSpeedX() const
	{
		return _speed.x;
	}

	float Entidade::getSpeedY() const
	{
		return _speed.y;
	}
	void Entidade::restartClock()
	{
		_clock.restart();
	}

	void Entidade::knockBack(Entidades::Entidade* ente)
	{
		float posicaoCentroJog = getPositionX() + (getBody().getGlobalBounds().width / 2.f);
		float posicaoCentroEnte = ente->getPositionX() + (ente->getBody().getGlobalBounds().width / 2.f);

		if (posicaoCentroJog - posicaoCentroEnte < 0.f)
			// se a posicao for maior que a do obstaculo, ele empurra para tras
		{
			int tipo = getTipo();
			switch (tipo)
			{
				//Jogador
			case Constantes::TIPO_JOGADOR:
				_speed.x -= 100.0f;
				break;

				//Cavaleiro
			case Constantes::TIPO_CAVALEIRO:
				_speed.x *= -1;
				setPositionX((getPositionX() - 40.0f));
				break;

				//Bruxa
			case Constantes::TIPO_MORTOVIVO:
				setPositionX((getPositionX() - 40.0f));
				break;

			case Constantes::TIPO_MORTOVIVO_THREAD:
				setPositionX((getPositionX() - 40.0f));
				break;

				//Mago
			case Constantes::TIPO_MAGO:
				setPositionX((getPositionX() - 60.0f));
				break;
			}

		}
		// se n�o empurra pra frente 
		else
		{
			int tipo = getTipo();
			switch (tipo)
			{
				//Jogador
			case Constantes::TIPO_JOGADOR:
				_speed.x += 100.0f;
				break;

				//Cavaleiro
			case Constantes::TIPO_CAVALEIRO:
				_speed.x *= -1;
				setPositionX((getPositionX() + 40.0f));
				break;

				//Bruxa
			case Constantes::TIPO_MORTOVIVO:
				setPositionX((getPositionX() + 40.0f));
				break;

			case Constantes::TIPO_MORTOVIVO_THREAD:
				setPositionX((getPositionX() + 40.0f));
				break;

				//Mago
			case Constantes::TIPO_MAGO:
				setPositionX((getPositionX() + 60.0f));
				break;
			}

		}

		Position += _speed;
		_body.setPosition(Position);
	}

	void Entidade::sofrerGravidade(float gravidade)
	{
		const float maxGravidade = Constantes::MAX_GRAVIDADE; // Limite de velocidade da gravidade
		if (!_onGround)
		{
			_speed.y += gravidade;
			if (_speed.y > maxGravidade)
			{
				_speed.y = maxGravidade; // Limitar a velocidade m�xima da gravidade
			}
		}
		else
		{
			_speed.y = 0; // Zera a velocidade quando est� no ch�o
		}

		if (getTipo() >= 8) // Caso seja um Obstaculo � empurrado com a mesma for�a para a outra dire��o mantendo estatico
		{
			_speed.y -= gravidade;
		}
	}

	void Entidade::setTipo(int tip)
	{
		_Tipo = tip;
	}

	int Entidade::getTipo() const
	{
		return _Tipo;
	}

	bool Entidade::getVivo() const
	{
		return _vivo;
	}

	void Entidade::setVivo(bool vivo)
	{
		_vivo = vivo;
	}
	void Entidade::setEhThread(bool th)
	{
		_ehThread = th;
	}
	bool Entidade::getEhThread() const
	{
		return _ehThread;
	}
	
}