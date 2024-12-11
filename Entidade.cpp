#include "Entidade.h"

namespace Entidades
{
	Entidades::Entidade::Entidade(float inicialX, float inicialY, Gerenciadores::Gerenciador_Grafico* pgra):
		Ente(pgra), Position(inicialX, inicialY),_clock(),_segundos(0.0f),_speed(0,0),_Tipo(0),_onGround()
	{
		_body.setPosition(Position);
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
	void Entidade::sofrerGravidade(float gravidade)
	{
		const float maxGravidade = 0.15f; // Limite de velocidade da gravidade
		if (!_onGround)
		{
			_speed.y += gravidade;
			if (_speed.y > maxGravidade)
			{
				_speed.y = maxGravidade; // Limitar a velocidade m�xima da gravidade
			}
		}
		else {
			_speed.y = 0; // Zera a velocidade quando est� no ch�o
		}
		if (getTipo() == 2) // Caso seja um Obstaculo � empurrado com a mesma for�a para a outra dire��o mantendo estatico
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
}

