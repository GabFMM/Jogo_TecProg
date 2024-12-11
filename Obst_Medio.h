#pragma once

#include "Jogador.h"
#include "Gerenciador_Grafico.h"
#include "Obstaculo.h"

namespace Entidades {
	class Obst_Medio : public Obstaculo
	{
	private:
		sf::Sprite telaParalisada;
		sf::Texture* textura2;

		//n�o acho que precise de ponteiro jogador, olhe o ObstaculoDificil, ele receber ponteiro para o jogador
		// l� no gerenciador de colis�es
		Entidades::Jogador* _pJog;

	public:
		Obst_Medio(float inicialX = 0, float inicialY = 0, Gerenciadores::Gerenciador_Grafico* pgra = nullptr);
		~Obst_Medio();

		void executar();
		void obstacular(Entidades::Jogador* pJog);

		void salvar();
		void render();
	};
}