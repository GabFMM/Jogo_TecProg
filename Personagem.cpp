#include "Personagem.h"

Entidades::Personagem::Personagem(float inicialX, float inicialY, Gerenciadores::Gerenciador_Grafico* pgra, int vidas)
	:Entidade(inicialX, inicialY, pgra), _num_vidas(vidas), _onGround(false), _vivo(true)
{
	_speed.x = 0.f;
	_speed.y = 0.f;
}



Entidades::Personagem::~Personagem()
{
}

bool Entidades::Personagem::getOnGround() const
{
	return _onGround;
}

void Entidades::Personagem::setGround(bool ong)
{
	_onGround = ong;
}

bool Entidades::Personagem::getVivo() const
{
	return _vivo;
}

void Entidades::Personagem::setVivo(bool vivo)
{
	_vivo = vivo;
}

int Entidades::Personagem::getVidas() const
{
	return _num_vidas;
}

void Entidades::Personagem::setVidas(int vid)
{
	_num_vidas = vid;
}

void Entidades::Personagem::setSpeed(float x, float y)
{
	_speed.x = x;
	_speed.y = y;
}

float Entidades::Personagem::getSpeedX() const
{
	return _speed.x;
}

float Entidades::Personagem::getSpeedY() const
{
	return _speed.y;
}

void Entidades::Personagem::operator++()
{
	_num_vidas++;
}

void Entidades::Personagem::operator--()
{
	if (_num_vidas > 0)
	{
		_num_vidas--;
	}
}

void Entidades::Personagem::sofrerGravidade(float gravidade)
{
	if (Position.y + _body.getGlobalBounds().height + gravidade <= _pGraf->getWindow()->getSize().y) 
	{
		_speed.y += gravidade;
	}
	_body.setPosition(Position);
}

void Entidades::Personagem::pular()
{
	if (_onGround)
	{
		_speed.y = -1.f;
		setGround(false);
	}
	
}
