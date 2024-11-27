#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

namespace Gerenciadores{
	class Gerenciador_Grafico {
	private:
		// Atributos
		sf::RenderWindow* window;
		std::list<Ente*> listaEntes;
		std::list<Ente*>::iterator it;

		// Metodos
		void criarJanela();
		void update();
		void render();

	public:
		Gerenciador_Grafico();
		~Gerenciador_Grafico();

		// Metodos
		sf::RenderWindow* getWindow() const;
		void desenharEnte(Ente* pE);
		void removerEnte(Ente* pE);
	};
} 