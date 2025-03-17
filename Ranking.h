#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include <stdexcept> // Para exceções
#include "Jogador.h"

using namespace std;

class Ranking
{
private:
	vector<pair<string, int>> leaderbord;
	ifstream arquivoEntrada;
	ofstream arquivoSaida;

public:
	Ranking();
	~Ranking();
	void ordenaVetor();
	void trocar(pair<string, int>& v1, pair<string, int>& v2);
	void imprimirLeaderboard();
	void recuperaDados();
	void salvarDados();
	void atualizaLeaderboard(Entidades::Jogador* pJog);
	void verificaPontos(Entidades::Jogador* pJog);
	vector<pair<string, int>> getVector()const;	
};