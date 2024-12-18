#include "Fase.h"
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <utility>


Fases::Fase::Fase(Gerenciadores::Gerenciador_Grafico* pgra,Entidades::Jogador* j)
	:_GG(pgra),_jog(j),maxCavaleiros(7),maxPlataformas(8)
{
	_GC = new Gerenciadores::Gerenciador_Colisoes(0.005f);
	_Lista = new Listas::ListaEntidades();
}

Fases::Fase::~Fase()
{
	//Desaloco o Gerenciador de Colisoes e a ListaEntidades
	if (_GC)
		delete _GC;

	if (_Lista)
		delete _Lista;

	//Seto como nulo os ponteiros para o Gerenciador gr�fico e jogador
	_GG = nullptr;
	_jog = nullptr;
	
}

void Fases::Fase::gerenciarColisoes()
{
	_GC->executar();
}

void Fases::Fase::criarCavaleiros()
{
	//Possibilidade de aleatorizar o y entre 700 e 150 rand()%(700-150)+150

	int n = rand()% maxCavaleiros; // Quantidade varia de 3 a 7
    if (n < 3) n = 3;

	float x = 150.f;           //Posicao inicial
    float anteriorX = x;
	
	int larguraJanela = _GG->getWindow()->getSize().x; // Largura da janela para testar se nao saiu depois

	for (int i = 0; i < n; i++)
	{
		Entidades::Cavaleiro* cav = new Entidades::Cavaleiro(x, 700, _GG, _jog, 4); // Novo cav na posicao x
		_Lista->insert_back(static_cast<Entidades::Entidade*>(cav)); // inserir na lista
		_GC->incluirInimigo(static_cast<Entidades::Inimigo*>(cav)); // inserir no Gerenciador de colisoes
		float larguraCavaleiro = cav->getBody().getGlobalBounds().width; // tamanho do cavaleiro

        x = rand() % (_GG->getWindow()->getSize().x)+150;
        if (x == anteriorX)
        {
            x = (rand() % _GG->getWindow()->getSize().x)+150;
        }
		if (x +115+larguraCavaleiro>larguraJanela) // testo se o tamanho do cavaleiro + 115 nao sai da janela
            x = (rand() % _GG->getWindow()->getSize().x) + 150; 

        anteriorX = x;
	}

}

void Fases::Fase::criarPlataformas()
{
	int n =  rand() % maxPlataformas;        // Quantidade de plataformas: entre 3 e 8
    if (n < 4) n = 4;
	int i;
	
	std::vector<std::pair<float, float>> posicoes = 
	{
		{0, 710.f},										// Plataforma 1
		{468, 710.f},									// Plataforma 2
		{936, 710.f},									// Plataforma 3
		{0, 530.f},										// Plataforma 4
		{_GG->getWindow()->getSize().x - 468, 530.f},	// Plataforma 5
		{450, 360.f},									// Plataforma 6
		{0, 200.f},										// Plataforma 7
		{_GG->getWindow()->getSize().x - 468, 200.f}    // Plataforma 8
	};

	for (i = 0; i < n; i++)
	{
		float x = posicoes[i].first;
		float y = posicoes[i].second;

		Entidades::Plataforma* plat = new Entidades::Plataforma(x, y, _GG,0);
		_GC->incluirObstaculo(static_cast<Entidades::Obstaculo*>(plat));
		_Lista->insert_back(static_cast<Entidades::Entidade*>(plat));
		
	}
    
}

void Fases::Fase::criarCenario()
{
	//Implementar depois 
}


