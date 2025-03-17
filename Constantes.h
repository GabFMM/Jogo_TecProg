#pragma once

namespace Constantes
{
	// Gravidade
	constexpr float GRAVIDADE = 0.005f;
	constexpr float MAX_GRAVIDADE = 0.3f;

	// Personagem
	constexpr int TIPO_PERSONAGEM = 1;
	constexpr float PULO_PERSONAGEM = -1.55f;

	// Jogador
	constexpr int VIDAS_JOGADOR = 10;
	constexpr float TEMPO_PULO = 80.0f;
	constexpr float VEL_JOGADOR = 0.2f;
	constexpr int TIPO_JOGADOR = 3;
	constexpr float PULO_JOGADOR = -1.75f;

	// Cavaleiro
	constexpr int VIDAS_CAVALEIRO = 3;
	constexpr float VEL_CAVALEIRO = 0.03f;
	constexpr float DISTANCIA_INICIO_CAVALEIRO = 300.0f;
	constexpr int MALDADE_CAVALEIRO = 1;
	constexpr int TIPO_CAVALEIRO = 4;

	// Bruxa
	constexpr int VIDAS_MORTOVIVO = 5;
	constexpr float VEL_MORTOVIVO = 0.04f;
	constexpr double DISTANCIA_ATIVACAO_MORTOVIVO = 700.0f;
	constexpr int MALDADE_MORTOVIVO = 2;
	constexpr int TIPO_MORTOVIVO = 5;
	constexpr int TIPO_MORTOVIVO_THREAD = 7;

	// Mago
	constexpr int VIDAS_MAGO = 10;
	constexpr float VEL_MAGO = 0.06f;
	constexpr float VEL_MAGO_BUFF = 0.09f;
	constexpr double DISTANCIA_ATIVACAO_MAGO = 800.0f;
	constexpr int MALDADE_MAGO = 1;
	constexpr int TIPO_MAGO = 6;
	constexpr int DANO_BATER = 3;


	// Obstaculo
	constexpr int TIPO_OBSTACULO = 8;
	constexpr int TIPO_PLATAFORMA = 9;
	constexpr int TIPO_BARRA_MAGICA = 10;
	constexpr int TIPO_ESPINHO = 11;
	constexpr float DURACAO_PARALISIA = 8000.f;

	// Projetil
	constexpr float TEMPO_MAX_VOO = 22.f;
	constexpr int TIPO_PROJETIL = 33;

	// TelaFimDeJogo
	constexpr int TAMANHO_TITULO = 90;
	constexpr int TAMANHO_SUBTITULO = 85;
	constexpr int TAMANHO_BOTOES = 50;

	// Castelo
	constexpr int MAX_MAGOS = 4;

	// Fase
	constexpr int MAX_CAVALEIROS = 8;
	constexpr int MAX_PLATAFORMA = 7;

	// Floresta
	constexpr int MAX_MORTOVIVO = 5;
	constexpr int MAX_BARRAS_MAGICAS = 4;

	// Menu
	constexpr int MENU_TAMANHO_TITULO = 145;
	constexpr int MENU_TAMANHO_BOTOES = 50;

	// MenuFases
	constexpr int MENU_FASES_TAMANHO_BOTOES = 50;

	// MenuJogadores 
	constexpr int MENU_JOG_TAMANHO_BOTOES = 50;

	// MenuRanking
	constexpr int RANKING_TAMANHO_TITULO = 115;
	constexpr int RANKING_TAMANHO_BOTOES = 50;

	
	/*
	StateNum eh uma variavel que permite o fluxo de diferentes estados no jogo
		Tipos de stateNum's:

		-- - > MENUS
		10 - menu
		11 - menu de jogadores
		12 - menu de ranking
		13 - menu de fases

		-- - > FASES
		20 - fase 1, floresta
		21 - fase 2, castelo

		-- > EXTRAS
		30 - tela de fim de jogo
	*/

	// Estados
	constexpr int STATE_MENU = 10;
	constexpr int STATE_MENU_JOGADORES = 11;
	constexpr int STATE_MENU_RANKING = 12;
	constexpr int STATE_MENU_FASES = 13;
	constexpr int STATE_FLORESTA = 20;
	constexpr int STATE_CASTELO = 21;
	constexpr int STATE_FIM_JOGO = 30;
	constexpr int STATE_FECHAR_JANELA = 0;
}