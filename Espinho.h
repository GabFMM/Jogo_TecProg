#pragma once

#include <SFML/Graphics.hpp>
#include "Gerenciador_Grafico.h"
#include "Obstaculo.h"

namespace Entidades {
	class Espinho : public Obstaculo {
	private:
		int _dano;

	public:
		Espinho(int dano = 1, float inicialX = 0, float inicialY = 0, Gerenciadores::Gerenciador_Grafico * pgra = nullptr);
		~Espinho();

		void executar();
		void obstacular(Entidades::Jogador* pJog);
		void SalvarDataBuffer(std::ofstream& arquivo);
		void registraDados();
	};
}