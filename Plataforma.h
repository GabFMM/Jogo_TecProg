#pragma once

#include "Obstaculo.h"

namespace Entidades
{
	class Plataforma :public Obstaculo
	{
	private:
		float altura;

	public:
		Plataforma(float inicialX=0, float inicialY=0, Gerenciadores::Gerenciador_Grafico* pgra=nullptr, float alt=0);
		~Plataforma();

		void executar();
		void obstacular(Entidades::Jogador* pJog);
		void SalvarDataBuffer(std::ofstream& arquivo);
		void registraDados();
	};
}