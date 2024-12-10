#pragma once
#include "Entidade.h"

namespace Entidades
{
	class Personagem :public Entidade
	{
	protected:
		int _num_vidas;
		bool _onGround;
		bool _vivo;
		bool _mover;
		sf::Vector2f _speed;

	public:
		Personagem(float inicialX = 0, float inicialY = 0, Gerenciadores::Gerenciador_Grafico* pgra = nullptr, int vidas=1 );
		
		virtual ~Personagem();

		bool getOnGround()const;
		void setGround(bool ong);

		bool getVivo()const;
		void setVivo(bool vivo);

		int getVidas()const;
		void setVidas(int vid);

		void setSpeed(float x, float y);
		float getSpeedX()const;
		float getSpeedY()const;

		void setMover(const bool mover);

		void operator++();
		void operator--();

		void sofrerGravidade(float gravidade);

		void pular();

		virtual void executar() = 0;
		virtual void salvar() = 0;
		virtual void render() = 0;
	};
}