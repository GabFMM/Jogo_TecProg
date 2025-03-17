#pragma once

#include "Entidade.h"

namespace Entidades
{
	class Personagem :public Entidade
	{
	protected:
		int _num_vidas;
		int _direcao;

	public:
		Personagem(float inicialX = 0, float inicialY = 0, 
			Gerenciadores::Gerenciador_Grafico* pgra = nullptr, int vidas = 10 );
		
		virtual ~Personagem();


		int getVidas()const;
		void setVidas(int vid);
		
		void operator++();
		void operator--(int i);

		virtual void pular();

		int getDirecao()const;
		void setDirecao(int dir);

		virtual void executar() = 0;
		
		virtual void mover() = 0;
		virtual void SalvarDataBuffer(std::ofstream& arquivo) = 0;
		virtual void registraDados();
	};
}