#include "Heart.h"


Fases::Heart::Heart(Gerenciadores::Gerenciador_Grafico* pGraf):
	Ente(pGraf),fullHeart(new sf::Texture()),emptyHeart(new sf::Texture())
{
	if (!fullHeart->loadFromFile("assets/HeartFULL.png"))
	{
		std::cerr << "Erro ao carregar a textura do coração cheio" << std::endl;
	}
	if (!emptyHeart->loadFromFile("assets/HeartEMPTY.png"))
	{
		std::cerr << "Erro ao carregar a textura do coração vazio" << std::endl;
	}
	setTexture(fullHeart);
	setPosX(0);
	setPosY(35);
	_body.setScale(0.5f, 0.5f);
}

Fases::Heart::~Heart()
{
	if (fullHeart)
	{
		delete fullHeart;
		fullHeart = nullptr;
	}
	if (emptyHeart)
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
