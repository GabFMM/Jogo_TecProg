#pragma once
#include "Inimigo.h"
#include "Constantes.h"
namespace Entidades
{
	class MortoVivo :public Inimigo
	{
	private:
	public:
		MortoVivo(float inicialX = 0, float inicialY = 0, Gerenciadores::Gerenciador_Grafico* pgra = nullptr,
			Entidades::Jogador* pJog1 = nullptr, Entidades::Jogador* pJog2 = nullptr, int vidas = Constantes::VIDAS_MORTOVIVO);
		virtual ~MortoVivo();

		virtual void executar();
	
		//void SalvarDataBuffer();
		virtual void mover();
		virtual void danificar(Entidades::Jogador* pJog);
	};
}