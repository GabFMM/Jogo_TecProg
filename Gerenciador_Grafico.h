#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

namespace Entidades { class Ente; }

namespace Gerenciadores{
	class Gerenciador_Grafico {
	private:
		// Atributos
		sf::RenderWindow* window;
		sf::View* view;
		

	public:
		Gerenciador_Grafico();
		~Gerenciador_Grafico();

		void desenhar(Entidades::Ente* pE);
		void desenhar(sf::RectangleShape& shape);
		void render();
		void display();
		sf::RenderWindow* getWindow();
		sf::View* getView() const;
		bool getOpen()const;
		void closeWindow();
		

	};
} 