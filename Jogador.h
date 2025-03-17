#pragma once

#include "Personagem.h"
#include <iostream>
#include <SFML/Graphics.hpp>

namespace Entidades
{
	class Inimigo;
	class Jogador :public Entidades::Personagem
	{
		private:
			// Estado de paralisia
			sf::Sprite telaParalisada;
			sf::Texture* texturaTela;
			sf::Clock _clockParalisia; // clock diferente do clock pulo
			float _duracaoParalisia;
			float _tempoParalisado;
			bool _paralisado;

			bool _atacando;

			float tempoPulo;
			int _pontos;

			std::string nome;
			float _velocidade;
			std::vector<sf::Texture*> _texturas;

			sf::Sprite* Sword;
			std::vector<sf::Texture*>_texturasSword;
			bool _ehJogador1;
			static int contador;


	public:
		Jogador(float inlX = 0, float inY = 0, Gerenciadores::Gerenciador_Grafico* pgra = nullptr,
			std::string name = "");

		~Jogador();

		void setNome(std::string& name);
		std::string getNome()const;

		void setParalisado(const bool para, float duracao);
		bool getParalisado()const;

		void SetPontos(int pont);
		int getPontos()const;

		void pular();
		void mover();

		void setTexture(int direcao);
		void adicionarTextura(const std::string& path);

		bool getAtacando()const;
		void setAtacando(bool atac);

		void setSword(int direcao);
		void adicionarSword(const std::string& path);

		void atacarInimigo(Entidades::Inimigo* enemy);
		bool getEhJogador1()const;

		void executar();
		void SalvarDataBuffer(std::ofstream& arquivo);
		void registraDados();
		static void setContador(int i);
	};
}