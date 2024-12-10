#pragma once

#include "Jogador.h"
#include "Gerenciador_Grafico.h"
#include "Obstaculo.h"

namespace Entidades {
	class Obst_Medio : public Obstaculo{
	private:
		sf::Sprite telaParalisada;
		sf::Texture* textura2;

		Entidades::Jogador* _pJog;

	public:
		Obst_Medio(float segundos = 0.f, float inicialX = 0, float inicialY = 0, Gerenciadores::Gerenciador_Grafico* pgra = nullptr);
		~Obst_Medio();

		void executar();
		void obstacular(Entidades::Jogador* pJog);

		void salvar();
		void render();
	};
}