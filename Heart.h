#pragma once
#include "Ente.h"

namespace Fases
{
	class Heart :public Entidades::Ente
	{
	private:
		sf::Texture* fullHeart;
		sf::Texture* emptyHeart;

	public:
		Heart(Gerenciadores::Gerenciador_Grafico* pGraf = nullptr);
		~Heart();
		void setPosX(float x);
		void setPosY(float y);
		void updateHeart(int status);
		void executar();

	};
}
