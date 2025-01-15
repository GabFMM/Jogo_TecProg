#pragma once
#include "Heart.h"
#include "Gerenciador_Grafico.h"

//class Heart;

namespace Entidades 
{
	class Jogador;
}

namespace Fases
{
	class Hud
	{
	private:
		Entidades::Jogador* _pJogador;
		Gerenciadores::Gerenciador_Grafico* _pGraf;
		sf::Text _pontos;
		std::vector<Fases::Heart*> _hearts;
		sf::Font _fonte;
		int _contadorVidas;

	public:
		Hud(Entidades::Jogador* pjog = nullptr);
		~Hud();
		void criaHeartsJog1();
		void criaHeartsJog2();

		void criaPontosJog1();
		void criaPontosJog2();

		void atualizaPontos();
		void atualizaHearts();
		void setContador(int vidas);

		void executar();
	};
}
