#pragma once

#include "MortoVivo.h"
#include "Thread.h"

namespace Entidades
{
	class MortoVivoThread :public MortoVivo, public ThreadCPP
	{
	private:
		bool _rodar;

	public:
		MortoVivoThread(float inicialX = 0, float inicialY = 0, Gerenciadores::Gerenciador_Grafico* pgra = nullptr,
			Entidades::Jogador* pJog1 = nullptr, Entidades::Jogador* pJog2 = nullptr, int vidas = 5);

		~MortoVivoThread();
		void setRodar(bool rod);

		void run();
		void executar();
		void SalvarDataBuffer(std::ofstream& arquivo);
		void registraDados();
	};
}