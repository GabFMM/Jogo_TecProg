#pragma once

#include "Entidade.h"
#include "Jogador.h"

namespace Entidades
{
	class Obstaculo :public Entidades::Entidade
	{
	protected:
		bool _danoso;

	public:
		Obstaculo(float inicialX = 0, float inicialY = 0, Gerenciadores::Gerenciador_Grafico* pgra = nullptr);
		virtual ~Obstaculo();

		void setDanoso(bool dan);
		bool getDanoso()const;

		virtual void executar() = 0;
		virtual void obstacular(Entidades::Jogador* pJog) = 0;
		virtual void SalvarDataBuffer(std::ofstream& arquivo) = 0;
		virtual void registraDados();	
	};
}