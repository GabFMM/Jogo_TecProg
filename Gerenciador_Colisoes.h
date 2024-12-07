#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <set>
#include "Obstaculo.h"
#include "Projetil.h"
#include "Jogador.h"

class Inimigo;

namespace Gerenciadores {
	class Gerenciador_Colisoes {
	private:

		// Jogadores
		Entidades::Jogador* _jogador1;
		Entidades::Jogador* _jogador2;

		// Listas
		std::vector<Inimigo*> _listaInimigos;
		std::list<Entidades::Obstaculo*> _listaObstaculos;
		std::set<Entidades::Projetil*> _listaProjetil;
	
		// Iteradores
		std::vector<Inimigo*>::iterator itInimigo;
		std::list<Entidades::Obstaculo*>::iterator itObstaculo;
		std::set<Entidades::Projetil*>::iterator itProjetil;

		// Velocidade da gravidade
		float _gravidade;

	public:
		Gerenciador_Colisoes(float gravidade = 10.f);
		~Gerenciador_Colisoes();

		void setJogador1(Entidades::Jogador* pJogador);
		void setJogador2(Entidades::Jogador* pJogador);

		void incluirInimigo(Inimigo* pInimigo);
		void incluirObstaculo(Entidades::Obstaculo* pObstaculo);
		void incluirProjetil(Entidades::Projetil* pProjetil);

		void tratarColisoesJogsObstacs();
		void tratarColisoesJogsInimgs();
		void tratarColisoesJogsProjeteis();

		const bool verificarColisao(Entidades::Entidade* pEnt1, Entidades::Entidade* pEnt2) const;

		void aplicarGravidade();

		void executar();
	};
}