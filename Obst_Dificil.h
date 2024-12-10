#pragma once

#include <SFML/Graphics.hpp>
#include "Gerenciador_Grafico.h"
#include "Obstaculo.h"

namespace Entidades {
	class Obst_Dificil : public Obstaculo {
	private:
		// Dano
		int _dano;

	public:
		Obst_Dificil(int dano = 1, float inicialX = 0, float inicialY = 0, Gerenciadores::Gerenciador_Grafico * pgra = nullptr);
		~Obst_Dificil();

		void executar();
		void obstacular(Entidades::Jogador* pJog);

		void salvar();
		void render();
	};
}