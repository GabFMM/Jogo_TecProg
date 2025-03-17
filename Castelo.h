#pragma once

#include <SFML/Graphics.hpp>
#include "Fase.h"
#include "Plataforma.h"
#include "Espinho.h"
#include "Cavaleiro.h"
#include "Mago.h"
#include "Projetil.h"
#include <iostream>
#include <vector>
#include <cstdlib>

namespace Fases {
	class Castelo : public Fase 
	{
	private:
		const int _maxMagos;
		int _maxEspinhos;

		bool _magosNaoCriados;

		std::vector<Entidades::Plataforma*> _platsBases;
		std::vector<Entidades::Plataforma*> _platsCavaleiros;
		std::vector<Entidades::Plataforma*> _platsBosses;

		std::vector<Entidades::Cavaleiro*> _cavaleiros;
		std::vector<Entidades::Mago*> _magos;

	public:
		Castelo(Gerenciadores::Gerenciador_Grafico* pgra = nullptr, Entidades::Jogador* j1 = nullptr, Entidades::Jogador* j2 = nullptr,Jogo* jog = nullptr);
		~Castelo();

		void criarCenario();

		void criarObstaculos();
		void criarPlataformas();
		void criarEspinhos();

		void criarInimigos();
		void criarCavaleiros();
		void criarMagos();

		void executar();

		void verificarCavaleiros();
		void recuperarFase();
	};
}