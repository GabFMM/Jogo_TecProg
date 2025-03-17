#pragma once

#include "Gerenciador_Grafico.h"
#include "Jogador.h"
#include "Floresta.h"
#include "Castelo.h"
#include "Menu.h"
#include "MenuFases.h"
#include "MenuJogadores.h"
#include "Ranking.h"
#include "MenuRanking.h"
#include "TelaFimDeJogo.h"

class Jogo
{
private:
	Entidades::Jogador* _jogador1;
	Entidades::Jogador* _jogador2;

	Gerenciadores::Gerenciador_Grafico* _GerenciadorGrafico;
	Menus::Menu* _menu;
	Menus::MenuJogadores* _menuJogadores;
	Menus::MenuRanking* _menuRanking;
	Menus::MenuFases* _menuFases;
	Fases::Floresta* _florest;
	Fases::Castelo* _castelo;
	Ranking* rank;
	TelaFimDeJogo* _telaFimDeJogo;

	static int stateNum;

public:
	Jogo();
	~Jogo();

	void criaCastelo();
	void criaFloresta();
	void criaMenu();
	void criaMenuFases();
	void criaMenuJogadores();
	void criaMenuRanking();
	void criaTelaFimDeJogo();

	void JogarCastelo();
	void JogarFloresta();
	void JogarMenu();
	void JogarMenuFases();
	void JogarMenuJogadores();
	void JogarMenuRanking();
	void JogarTelaFimDeJogo();

	void deletarJogadores();
	void destroiEstadosAnteriores();
	void atualizaRanking();

	void executar();

	static void mudarStateNum(int state);
	
	void setJogador1(Entidades::Jogador* jog);
	void setJogador2(Entidades::Jogador* jog);

	bool criarJogador1(string nome);
	bool criarJogador2(string nome);
	Ranking* getRanking()const;
};