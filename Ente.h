#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Gerenciador_Grafico.h"

namespace Entidades
{	
	class Ente
	{
	protected:
		//Atributos 
		int id;
		Gerenciadores::Gerenciador_Grafico* _pGraf;
		sf::Texture* _pTexture;
		sf::Sprite _body;
		
		// Contator de instancias
		static int _cont;		

	public:
		Ente(Gerenciadores::Gerenciador_Grafico* pgra = nullptr);
		Ente(Gerenciadores::Gerenciador_Grafico* pgra, sf::Texture* text, sf::Sprite bod);
		virtual  ~Ente() { };

		virtual void executar() = 0;
		void desenhar();

		int getId()const { return id; }
		Gerenciadores::Gerenciador_Grafico* getGrafico() { return _pGraf; }

		void setTexture(sf::Texture* pText);
		sf::Texture* getTexture()const { return _pTexture; }
		sf::Sprite getBody()const { return _body; }
	};
	
	
}