#pragma once

#include "Inimigo.h"
#include "Gerenciador_Grafico.h"
#include "Jogador.h"
#include "Projetil.h"
#include "Constantes.h"

namespace Entidades {
	class Mago : public Inimigo 
	{
	private:
		// Delta tempo
		sf::Clock deltaTime;

		// Projetil
		Entidades::Projetil* _projetil;
		float _segundosIntervaloPro;

		// Vida
		int _vidasPerdidas;

	public:
		Mago(float inicialX = 0, float inicialY = 0, Gerenciadores::Gerenciador_Grafico* pgra = nullptr,
			Entidades::Jogador* pJog1 = nullptr, Entidades::Jogador* pJog2 = nullptr, int vidas = Constantes::VIDAS_MAGO);
		~Mago();

		void setProjetil(Entidades::Projetil* pProj);

		void executar();
		void mover();
		void verificarVida();
		void danificar(Entidades::Jogador* pJog);
		
		void atirar();
		void bater();
		void setVidasPerdidas(int vidas);
		void setSegIntervalo(float seg);

		void SalvarDataBuffer(std::ofstream& arquivo);
		void registraDados();
	};
}