#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ostream>
#include "Ente.h"

namespace Entidades
{
	class Entidade:public Entidades::Ente
	{
	protected:
		bool _onGround;
		int _Tipo;
		sf::Vector2f Position;
		sf::Vector2f _speed;
		sf::Clock _clock;
		float _segundos;
		bool _vivo;
		//ostream buffer;

	public:
		Entidade(float inicialX = 0, float inicialY = 0, Gerenciadores::Gerenciador_Grafico* pgra=nullptr);
		virtual ~Entidade() { if (_pTexture) delete _pTexture; };

		float getPositionX()const;
		void setPositionX(float x);

		float getPositionY()const;
		void setPositionY(float y);

		bool getOnGround()const;
		void setGround(bool ong);

		void setPosition(float x, float y);
		sf::Vector2f getPosition()const;

		void setSpeed(float x, float y);
		float getSpeedX()const;
		float getSpeedY()const;

		void restartClock();

		void sofrerGravidade(float gravidade);

		void setTipo(int tip);
		int getTipo()const;

		bool getVivo()const;
		void setVivo(bool vivo);

		virtual void executar() = 0;
		
		//void SalvarDataBuffer();

		
	};
}