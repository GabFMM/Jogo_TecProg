#pragma once

#include "Entidade.h"
#include "Gerenciador_Grafico.h"

namespace Entidades {
	class Projetil : public Entidade{
	protected:
		int _dano;
		bool _lancar;
		float _tempoMaxVoo;

		float dt;

	public:
		Projetil(float inicialX = 0.f, float inicialY = 0.f, Gerenciadores::Gerenciador_Grafico* pGraf = nullptr);
		~Projetil();
		
		void setDano(int dano);
		const int getDano() const;

		void lancar(float speedX, float speedY, int dano);
		void setLancar(const bool lancar);
		const bool getLancar() const;

		void executar();
		void mover();

		const bool estaDentroDaJanela() const;
		const bool tempoDeVooExcedido() const;
		void resetar();

		void inverteLado();

		void render();
		void salvar();
	};
}