#include "Jogo.h"
#include <iostream>
#include "Constantes.h"

// ESTATICOS

int Jogo::stateNum = Constantes::STATE_MENU;

void Jogo::mudarStateNum(int state) { stateNum = state; }

void Jogo::setJogador1(Entidades::Jogador* jog)
{
	_jogador1 = jog;
}

void Jogo::setJogador2(Entidades::Jogador* jog)
{
	_jogador2 = jog;
}

// DEMAIS

Jogo::Jogo() : _jogador1(nullptr), _jogador2(nullptr)
{
	_GerenciadorGrafico = Gerenciadores::Gerenciador_Grafico::getInstancia();
	rank = new Ranking();

	_castelo = nullptr;
	_florest = nullptr;
	_menu = nullptr;
	_menuJogadores = nullptr;
	_menuFases = nullptr;
	_menuRanking = nullptr;
	_telaFimDeJogo = nullptr;
}

Jogo::~Jogo()
{

	if (_jogador1)
	{
		delete _jogador1;
	}
	if (_jogador2)
	{
		delete _jogador2;
	}
	if (_GerenciadorGrafico)
	{
		delete _GerenciadorGrafico;
	}
	if (_castelo)
	{
		delete _castelo;
	}
	if (_florest)
	{
		delete _florest;
	}
	if (_menu)
	{
		delete _menu;
	}
	if (_menuJogadores)
	{
		delete _menuJogadores;
	}
	if (_menuFases) 
	{
		delete _menuFases;
	}
	if (rank)
	{
		delete rank;
	}
	if (_menuRanking)
	{
		delete _menuRanking;
	}
	if (_telaFimDeJogo)
	{
		delete _telaFimDeJogo;
	}

	_jogador1 = nullptr;
	_jogador2 = nullptr;
	_GerenciadorGrafico = nullptr;
	_florest = nullptr;
	_menu = nullptr;
	rank = nullptr;
	_telaFimDeJogo = nullptr;
	_menuJogadores = nullptr;
	_menuRanking = nullptr;
}

void Jogo::executar()
{
	while (_GerenciadorGrafico->getOpen()) 
	{
		// Escolhe o estado da janela

		switch (stateNum) {
			// Fecha janela
		case Constantes::STATE_FECHAR_JANELA:
			_GerenciadorGrafico->closeWindow();
			break;

			// Cria menu principal
		case Constantes::STATE_MENU:
			criaMenu();
			JogarMenu();
			break;

			// Cria o menu de jogadores
		case Constantes::STATE_MENU_JOGADORES:
			criaMenuJogadores();
			JogarMenuJogadores();
			break;

			// Cria o menu de ranking
		case Constantes::STATE_MENU_RANKING:
			criaMenuRanking();
			JogarMenuRanking();
			break;

		case Constantes::STATE_MENU_FASES: // Cria o menu de Fases
			criaMenuFases();
			JogarMenuFases();
			break;

			// Cria a fase 1, floresta
		case Constantes::STATE_FLORESTA:
			criaFloresta();
			JogarFloresta();
			atualizaRanking();
			break;

		case Constantes::STATE_CASTELO: // Cria a fase 2, castelo
			criaCastelo();
			JogarCastelo();
			atualizaRanking();
			break;

		case Constantes::STATE_FIM_JOGO: // Cria a tela de fim de jogo
			criaTelaFimDeJogo();
			JogarTelaFimDeJogo();
			break;
		}
	}
}

void Jogo::destroiEstadosAnteriores()
{
	if (_menu != nullptr)
	{
		delete _menu;
		_menu = nullptr;
	}
	if (_menuJogadores != nullptr)
	{
		delete _menuJogadores;
		_menuJogadores = nullptr;
	}
	if (_menuFases != nullptr)
	{
		delete _menuFases;
		_menuFases = nullptr;
	}
	if (_menuRanking != nullptr)
	{
		delete _menuRanking;
		_menuRanking = nullptr;
	}
	if (_florest != nullptr)
	{
		delete _florest;
		_florest = nullptr;
	}
	if (_castelo != nullptr)
	{
		delete _castelo;
		_castelo = nullptr;
	}
	if (_telaFimDeJogo != nullptr)
	{
		delete _telaFimDeJogo;
		_telaFimDeJogo = nullptr;
	}
}

bool Jogo::criarJogador1(string nome)
{
	if (_jogador1 == nullptr)
	{
		_jogador1 = new Entidades::Jogador(0, 0, _GerenciadorGrafico, nome);
		if (_jogador1)
		{
			rank->verificaPontos(_jogador1);
			return true;
		}
		return false;
	}
	cerr << "Jogador1 ja existente\n";
	return false;
}

bool Jogo::criarJogador2(string nome)
{
	if (_jogador2 == nullptr)
	{
		_jogador2 = new Entidades::Jogador(30, 0, _GerenciadorGrafico, nome);
		if (_jogador2) 
		{ 
			rank->verificaPontos(_jogador2);
			return true;
		};
		return false;
	}
	cerr << "Jogador2 ja existente\n";
	return false;
}

Ranking* Jogo::getRanking() const
{
	return rank;
}

void Jogo::atualizaRanking()
{
	if (rank)
	{
		cout << "Atualizando leaderboard..." << endl;

		rank->atualizaLeaderboard(_jogador1);
		rank->atualizaLeaderboard(_jogador2);

		rank->salvarDados();
	}
	else
	{
		cerr << "Erro: rank nao inicializado!" << endl;
	}
}

void Jogo::JogarCastelo()
{
	_castelo->executar();
}

void Jogo::JogarFloresta()
{
	_florest->executar();
}

void Jogo::criaMenu() 
{
	if (_menu == nullptr) 
	{
		// Destroi o estado anterior
		destroiEstadosAnteriores();

		_menu = new Menus::Menu(_GerenciadorGrafico);

		
	}
}

void Jogo::criaMenuFases()
{
	if (_menuFases == nullptr) {
		// Destroi o estado anterior
		destroiEstadosAnteriores();

		// Cria o estado atual
		_menuFases = new Menus::MenuFases(_GerenciadorGrafico);
	}
}

void Jogo::criaMenuJogadores()
{
	if (_menuJogadores == nullptr) {
		// Destroi o estado anterior
		destroiEstadosAnteriores();

		// Cria o estado atual
		deletarJogadores();
		_menuJogadores = new Menus::MenuJogadores(this, _GerenciadorGrafico);
	}
}

void Jogo::criaMenuRanking()
{
	if (_menuRanking == nullptr) {
		// Destroi o estado anterior
		destroiEstadosAnteriores();

		_menuRanking = new Menus::MenuRanking(_GerenciadorGrafico, rank);
	}
}

void Jogo::criaTelaFimDeJogo()
{
	if (_telaFimDeJogo == nullptr) {
		// Destroi o estado anterior
		destroiEstadosAnteriores();

		// Cria o estado atual
		_telaFimDeJogo = new TelaFimDeJogo(_GerenciadorGrafico, _jogador1, _jogador2);
	}
}

void Jogo::criaCastelo()
{
	if (_castelo == nullptr) {
		// destroi o estado anterior
		destroiEstadosAnteriores();

		// Cria o estado atual
		_castelo = new Fases::Castelo(_GerenciadorGrafico, _jogador1,_jogador2,this);
		//_castelo->setJogo(this);
	}
}

void Jogo::criaFloresta()
{
	if (_florest == nullptr) {
		// destroi o estado anterior
		destroiEstadosAnteriores();

		// Cria o estado atual
		_florest = new Fases::Floresta(_GerenciadorGrafico, _jogador1,_jogador2,this);
		//_florest->setJogo(this);
	}
}

void Jogo::JogarMenu()
{
	_menu->executar();
}

void Jogo::JogarMenuFases()
{
	_menuFases->executar();
}

void Jogo::JogarMenuJogadores()
{
	_menuJogadores->executar();
}

void Jogo::JogarTelaFimDeJogo()
{
	_telaFimDeJogo->executar();
}

void Jogo::JogarMenuRanking()
{
	_menuRanking->executar();
}

void Jogo::deletarJogadores()
{
	if (_jogador1 != nullptr) 
	{
		delete _jogador1;
		_jogador1 = nullptr;
	}
	if (_jogador2 != nullptr) 
	{
		delete _jogador2;
		_jogador2 = nullptr;
	}
}


