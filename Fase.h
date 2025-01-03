#pragma once
#include "Ente.h"
#include "ListaEntidades.h"
#include "Gerenciador_Colisoes.h"
#include "Plataforma.h"
#include "Cavaleiro.h"


namespace Fases
{
	class Fase :public Entidades::Ente
	{
	protected:
		bool _mudouEstado;

		Gerenciadores::Gerenciador_Colisoes* _GC;
		Listas::ListaEntidades* _Lista;
		Gerenciadores::Gerenciador_Grafico* _GG;
		Entidades::Jogador* _jog1;
		Entidades::Jogador* _jog2;
		const int maxCavaleiros;
		const int maxPlataformas;

	public:
		Fase(Gerenciadores::Gerenciador_Grafico* pgra = nullptr,Entidades::Jogador* j1 = nullptr, Entidades::Jogador* j2 = nullptr);
		virtual ~Fase();
		void gerenciarColisoes();
		void criarCavaleiros();
		void criarPlataformas();
		virtual void criarCenario();

		virtual void executar() = 0;
		virtual void criarInimigos() = 0;
		virtual void criarObstaculos() = 0;
	};
}