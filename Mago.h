#pragma once

#include "Inimigo.h"
#include "Gerenciador_Grafico.h"
#include "Jogador.h"
#include "Projetil.h"

namespace Entidades {
	class Mago : public Entidades::Inimigo {
	private:
		// Delta tempo
		sf::Clock deltaTime;

		// Projetil
		Entidades::Projetil* _projetil;
		float _segundosIntervaloPro;

		// Vida
		int _vidasPerdidas;

		// Movimento
		int _direcao;


	public:
		Mago(float inicialX = 0, float inicialY = 0, Gerenciadores::Gerenciador_Grafico* pgra = nullptr,
			Entidades::Jogador* pJog = nullptr, int vidas = 10);
		~Mago();

		void setProjetil(Entidades::Projetil* pProj);

		void executar();
		void mover();
		void verificarVida();
		void danificar(Entidades::Jogador* pJog);
		
		void atirar();
		void bater();

		//void SalvarDataBuffer();
		
	};
}