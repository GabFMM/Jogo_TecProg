#include "Heart.h"


Fases::Heart::Heart(Gerenciadores::Gerenciador_Grafico* pGraf):
	Ente(pGraf), fullHeart(new sf::Texture()), emptyHeart(new sf::Texture())
{
	fullHeart = _pGraf->getTextura("Heart_Full");

	emptyHeart = _pGraf->getTextura("Heart_Empty");

	setTexture(fullHeart);
	setPosX(0);
	setPosY(35);
	_body.setScale(0.5f, 0.5f);
}

Fases::Heart::~Heart()
{
	if (fullHeart != nullptr)
	{
		delete fullHeart;
		fullHeart = nullptr;
	}

	if (emptyHeart != nullptr)
	{
		delete emptyHeart;
		emptyHeart = nullptr;
	}
}

void Fases::Heart::setPosX(float x)
{
	_body.setPosition(x, _body.getPosition().y);
}

void Fases::Heart::setPosY(float y)
{
	_body.setPosition(_body.getPosition().x, y);
}

// A depender da vida do jogador, o coracao correspondente devera estar preenchido (com vida) ou vazio (sem vida)
void Fases::Heart::updateHeart(int status)
{
	if (status == 1)
	{
		setTexture(fullHeart);
	}
	else if (status == 0)
	{
		setTexture(emptyHeart);
	}
}

void Fases::Heart::executar()
{
	desenhar();
}
