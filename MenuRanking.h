#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Ente.h"
#include "Gerenciador_Grafico.h"
#include "Ranking.h"

namespace Menus
{
	class MenuRanking :public Entidades::Ente
	{
	private:
		bool _mudouEstado;

		sf::Mouse _mouse;
		bool _houveClique;

		sf::Text _titulo;

		sf::Text _botaoVoltarMenuPrincipal;
		std::string _textosBotao;

		sf::Font _fonte;
		Ranking* _rank;

	public:
		MenuRanking(Gerenciadores::Gerenciador_Grafico* _pGraf = nullptr, Ranking* rank = nullptr);
		~MenuRanking();

		void carregarFonte();

		void criarBotao();
		void criarTitulo();
		void criarBackground();

		void verificarMouse();
		void verificarMovimento();

		void destacarTexto(sf::Text& texto);
		void reposicionarTexto(sf::Text& texto);
		void padronizar(sf::Text& texto);

		void desenharMenu();

		void executar();
		void mostrarRanking(Ranking* rank);
		void retornaMenuPrincipal();
	};
}