#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
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

	public:
		Entidade(float inicialX = 0, float inicialY = 0, Gerenciadores::Gerenciador_Grafico* pgra=nullptr);
		virtual ~Entidade() {};

		float getPositionX()const { return Position.x; }
		void setPositionX(float x) { Position.x = x; }

		float getPositionY()const { return Position.y; }
		void setPositionY(float y) { Position.y = y; }

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

		virtual void executar() = 0;
		virtual void salvar() = 0;
		virtual void render() = 0;
		
	};
}