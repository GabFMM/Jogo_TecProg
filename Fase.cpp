#include "Fase.h"
#include "Jogo.h"
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <utility>
#include "Constantes.h"
#include "Factory.h"
/*Implementar posteriormente:
Posso fazer um vector de pair<pair<float,float>,bool>(Esses vectores para plataforma e cavaleiro ficariam no .h)
uso o pair de float para as coordenadas e o booleano para saber
se a plataforma ja foi gerada, dai posso randomizar melhor os obstaculos dificeis e medios, al�m de ter mais de 5

op��es de plataformas, ou seja gero umas 10 posi��es, algumas plataformas podem se sobrepor a outras, portanto antes de
gerar elas verifico se outra plataforma muito proxima ja foi gerada, o mesmo pode ser feito para inimigos,posso gerar
todas as plataformas e depois verifico quais foram geradas e posso colocara inimigos em todas elas ao inves de me

limitar ao ch�o, pois � at� o momento a unica parte que certamente vai ser gerada
*/

Fases::Fase::Fase(Gerenciadores::Gerenciador_Grafico* pgra, Entidades::Jogador* j1,Entidades::Jogador*j2)
	:Ente(pgra), _GG(pgra), _jog1(j1),_jog2(j2), maxCavaleiros(Constantes::MAX_CAVALEIROS),
	maxPlataformas(Constantes::MAX_PLATAFORMA), _mudouEstado(false),_hudJog1(nullptr),_hudJog2(nullptr)
{
	_GC = Gerenciadores::Gerenciador_Colisoes::getInstancia();
	_Lista = new Listas::ListaEntidades();
	if (_jog1)
	{
		_GC->setJogador1(_jog1);
		_hudJog1 = new Hud(_jog1);
		
	}
	if (_jog2)
	{
		_GC->setJogador2(_jog2);
		_hudJog2 = new Hud(_jog2);
		
	}
	
}

Fases::Fase::~Fase()
{
	//Desaloco o Gerenciador de Colisoes e a ListaEntidades
	/*if (_GC)
		delete _GC;
		*/
	if (_Lista) 
	{
		_Lista->joinThread();
		delete _Lista;
	}
	if (_hudJog1)
	{
		delete _hudJog1;
		_hudJog1 = nullptr;
	}
	if (_hudJog2)
	{
		delete _hudJog2;
		_hudJog2 = nullptr;
	}
		

	//Seto como nulo os ponteiros para o Gerenciador gr�fico e jogador
	//_GG = nullptr;
	_jog1 = nullptr;
	_jog2 = nullptr;

}

void Fases::Fase::gerenciarColisoes()
{
	_GC->executar();
}

void Fases::Fase::criarCavaleiros()
{
	//Possibilidade de aleatorizar o y entre 700 e 150 rand()%(700-150)+150


	int n = (rand() % 5) + 4; // Quantidade varia de 3 a 7



	float x = 150.f;           //Posicao inicial
	float anteriorX = x;

	int larguraJanela = _GG->getWindow()->getSize().x; // Largura da janela para testar se nao saiu depois

	for (int i = 0; i < n; i++)
	{
		//Entidades::Cavaleiro* cav = new Entidades::Cavaleiro(x, 700.0f, _GG, _jog1,_jog2); // Novo cav na posicao x
		Entidades::Cavaleiro* cav = static_cast<Entidades::Cavaleiro*>
			(
			Entidades::EntidadeFactory::criarEntidade(x, 700.0f, _GG, _jog1, _jog2,Constantes::TIPO_CAVALEIRO
				));

		_Lista->insert_back(static_cast<Entidades::Entidade*>(cav)); // inserir na lista
		_GC->incluirInimigo(static_cast<Entidades::Inimigo*>(cav)); // inserir no Gerenciador de colisoes
		float larguraCavaleiro = cav->getBody().getGlobalBounds().width; // tamanho do cavaleiro

		x =(float) (rand() % (_GG->getWindow()->getSize().x) + 150.0f);
		if (x == anteriorX)
		{
			x =(float) ((rand() % _GG->getWindow()->getSize().x) + 150.0f);
		}
		if (x + 115 + larguraCavaleiro > larguraJanela) // testo se o tamanho do cavaleiro + 115 nao sai da janela
			x = (float)((rand() % _GG->getWindow()->getSize().x) + 150.0f);

		anteriorX = x;
	}

}

void Fases::Fase::criarPlataformas()
{

	int n = (rand() % 5) +4 ;        // Quantidade de plataformas: entre 3 e 8
	int i;

	std::vector<std::pair<float, float>> posicoes =
	{
		{0.f, 710.f},										// Plataforma 1
		{468.f, 710.f},										// Plataforma 2 
		{936.f, 710.f},										// Plataforma 3
		{0.f, 530.f},										// Plataforma 4
		{_GG->getWindow()->getSize().x - 468.f, 530.f},		// Plataforma 5
		{450.f, 360.f},										// Plataforma 6
		{0.f, 200.f},										// Plataforma 7
		{_GG->getWindow()->getSize().x - 468.f, 200.f}		// Plataforma 8
	};

	for (i = 0; i < n; i++)
	{
		float x = posicoes[i].first;
		float y = posicoes[i].second;

		//Entidades::Plataforma* plat = new Entidades::Plataforma(x, y, _GG);
		Entidades::Plataforma* plat = static_cast<Entidades::Plataforma*>
			(
				Entidades::EntidadeFactory::criarEntidade(x, y, _GG, Constantes::TIPO_PLATAFORMA)
				);
		_GC->incluirObstaculo(static_cast<Entidades::Obstaculo*>(plat));
		_Lista->insert_back(static_cast<Entidades::Entidade*>(plat));

	}

}

void Fases::Fase::criarCenario()
{
	//Implementar depois 
}

void Fases::Fase::verificarJogadores()
{
	// ------ >> verifica se o(s) jogador(es) estao morto(s)

	// Caso 1: os dois jogadores foram criados
	if (_jog1 != nullptr && _jog2 != nullptr) {
		if (!_jog1->getVivo() && !_jog2->getVivo()) {
			// Finaliza o jogo
			Jogo::mudarStateNum(30);
			_mudouEstado = true;
		}
	}
	// Caso 2: apenas o jogador 1 foi criado
	else if (_jog1 != nullptr) {
		if (!_jog1->getVivo()) {
			// Finaliza o jogo
			Jogo::mudarStateNum(30);
			_mudouEstado = true;
		}
	}
	// Caso 3: apenas o jogador 2 foi criado
	else if (_jog2 != nullptr) {
		if (!_jog2->getVivo()) {
			// Finaliza o jogo
			Jogo::mudarStateNum(30);
			_mudouEstado = true;
		}
	}
}
