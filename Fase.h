#pragma once
#include "Ente.h"
#include "ListaEntidades.h"
#include "Gerenciador_Colisoes.h"
#include "Plataforma.h"
#include "Cavaleiro.h"
#include "Hud.h"


namespace Fases
{
	class Fase :public Entidades::Ente
	{
	protected:
		bool _mudouEstado;

		Gerenciadores::Gerenciador_Colisoes* _GC;
		Listas::ListaEntidades* _Lista;
		Gerenciadores::Gerenciador_Grafico* _GG;

		Entidades::Jogador * _jog1;
		Entidades::Jogador* _jog2;
		Hud _hudJogador1;
		Hud _hudJogador2;
		int maxCavaleiros;
		int maxPlataformas; // Pois cada fase tem um numero diferente

	public:
		Fase(Gerenciadores::Gerenciador_Grafico* pgra = nullptr,Entidades::Jogador* j1 = nullptr, Entidades::Jogador* j2 = nullptr);
		virtual ~Fase();
		void gerenciarColisoes();
		
		virtual void criarCavaleiros();  // Pois cada fase determina onde será gerado
		virtual void criarPlataformas();
		virtual void criarCenario();

		virtual void executar() = 0;
		virtual void criarInimigos() = 0;
		virtual void criarObstaculos() = 0;
	};
}