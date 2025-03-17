#pragma once
#include "Ente.h"
#include "ListaEntidades.h"
#include "Gerenciador_Colisoes.h"
#include "Plataforma.h"
#include "Cavaleiro.h"
#include "Hud.h"
#include "MenuPause.h"
#include <fstream>

class Jogo;

namespace Fases
{
	class Fase : public Entidades::Ente
	{
	protected:
		bool _mudouEstado;

		Gerenciadores::Gerenciador_Colisoes* _GC;
		Listas::ListaEntidades* _Lista;
		Gerenciadores::Gerenciador_Grafico* _GG;

		Menus::MenuPause* _menuPause;

		Entidades::Jogador* _jog1;
		Entidades::Jogador* _jog2;
		Hud* _hudJog1;
		Hud* _hudJog2;
		int maxCavaleiros;
		int maxPlataformas; // Pois cada fase tem um numero diferente
		std::ofstream _arquivoFase;
		bool _terminada;
		int _TipoFase;
		Jogo* _jogo;
		

	public:
		Fase(Gerenciadores::Gerenciador_Grafico* pgra = nullptr,Entidades::Jogador* j1 = nullptr, Entidades::Jogador* j2 = nullptr,Jogo* jog = nullptr);
		virtual ~Fase();

		void gerenciarColisoes();
		
		virtual void criarCavaleiros() = 0;  // Pois cada fase determina onde será gerado
		virtual void criarPlataformas();
		virtual void criarCenario() = 0;

		virtual void executar() = 0;
		virtual void criarInimigos() = 0;
		virtual void criarObstaculos() = 0;

		void pause();
		void verificarSaidaPause();
		void SalvarEntidades();
		void LimpaArquivo();
		void verificarJogadores();
		void verificaInimigosVivos();
		void setTipoFase(int i);
		void recuperarFase();
		void setJogo(Jogo* jo);
		void executarJogadores();
	};
}