#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <string>
#include <fstream>

namespace Entidades { class Ente; }

namespace Gerenciadores{
	class Gerenciador_Grafico {
	private:
		// Atributos
		sf::RenderWindow* window;
		sf::View view;
		std::map<std::string, std::string> _mapPathsTextures;
		std::ifstream arquivoLeitura;

		//Implementando Singleton
		static Gerenciador_Grafico* instancia;
		Gerenciador_Grafico();

	public:
		
		static Gerenciador_Grafico* getInstancia();
		~Gerenciador_Grafico();

		void desenhar(Entidades::Ente* pE);
		void desenhar(sf::Text* texto);
		void desenhar(sf::Sprite* sprt);
		void clear();
		void display();
		sf::RenderWindow* getWindow()const;
		bool getOpen()const;
		void closeWindow();

		void criaMap();
		sf::Texture* getTextura(std::string chave);
		sf::Font getFont();
	};
} 