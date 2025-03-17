#pragma once

#include "Entidade.h"
#include "Jogador.h"
#include <iostream>
#include <math.h>

namespace Entidades
{
	class Inimigo : public Entidades::Personagem
	{
	protected:
		bool atacar;
		int _nivel_maldade;
		Entidades::Jogador* _pJog1;
		Entidades::Jogador* _pJog2;

		float posInicialX;
		float posInicialY;

	public:
		Inimigo(float inicialX = 0, float inicialY = 0, Gerenciadores::Gerenciador_Grafico* pgra = nullptr,
			Entidades::Jogador* pJog1 = nullptr, Entidades::Jogador* pJog2 = nullptr, int vidas = 1);
		virtual ~Inimigo();

		void setMaldade(int mal);
		int getMaldade()const;

		void setJogador1(Entidades::Jogador* pJog);
		void setJogador2(Entidades::Jogador* pJog);

		double getDistanciaJogador1();
		double getDistanciaJogador2();
		sf::Vector2f getDistanciaJog1Vector();
		sf::Vector2f getDistanciaJog2Vector();

		double getDistanciaoInicio();
		sf::Vector2f getDistanciaInicioVector();

		Entidades::Jogador* getJogadorMaisProximo();
		
		void setPosInicial(float x, float y);
		virtual void executar() = 0;
		virtual void mover() = 0;
		virtual void danificar(Entidades::Jogador* pJog) = 0;
		virtual void SalvarDataBuffer(std::ofstream& arquivo) = 0;
		virtual void registraDados();
	};
}