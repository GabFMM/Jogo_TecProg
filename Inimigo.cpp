#include "Inimigo.h"

Entidades::Inimigo::Inimigo(float inicialX, float inicialY, Gerenciadores::Gerenciador_Grafico* pgra, 
	Entidades::Jogador* pJog1, Entidades::Jogador* pJog2,int vidas)
	: Personagem(inicialX,inicialY,pgra,vidas),
	_pJog1(pJog1), _pJog2(pJog2), 
	atacar(false), _nivel_maldade(0), posInicialX(inicialX), posInicialY(inicialY)
{

}

Entidades::Inimigo::~Inimigo()
{
	_pJog1 = nullptr;
	_pJog2 = nullptr;
}

void Entidades::Inimigo::setMaldade(int mal)
{
	_nivel_maldade = mal;
}

int Entidades::Inimigo::getMaldade() const
{
	return _nivel_maldade;
}

void Entidades::Inimigo::setJogador1(Entidades::Jogador* pJog)
{
	if (pJog)
	{
		_pJog1 = pJog;
	}
	else
	{
		std::cerr << "Erro: Jogador inválido ao setar no inimigo!" << std::endl;
	}
}

void Entidades::Inimigo::setJogador2(Entidades::Jogador* pJog)
{
	if (pJog)
	{
		_pJog2 = pJog;
	}
	else
	{
		std::cerr << "Erro: Jogador inválido ao setar no inimigo!" << std::endl;
	}
}

double Entidades::Inimigo::getDistanciaJogador1()
{
	
	if (!_pJog1)
	{
		std::cerr << "Erro: Ponteiro para jogador é nulo. Distância não pode ser calculada!" << std::endl;
		return -1.0;
	}
	//Pitagoras para calcular a distancia 
	return sqrt(pow(getPositionX() - _pJog1->getPositionX(), 2) + pow(getPositionY() - _pJog1->getPositionY(), 2));
}

double Entidades::Inimigo::getDistanciaJogador2()
{

	if (!_pJog2)
	{
		std::cerr << "Erro: Ponteiro para jogador é nulo. Distância não pode ser calculada!" << std::endl;
		return -1.0;
	}
	//Pitagoras para calcular a distancia 
	return sqrt(pow(getPositionX() - _pJog2->getPositionX(), 2) + pow(getPositionY() - _pJog2->getPositionY(), 2));
}

sf::Vector2f Entidades::Inimigo::getDistanciaJog1Vector()
{
	sf::Vector2f distancia;

	distancia.x = abs(getPositionX() - _pJog1->getPositionX());
	distancia.y = abs(getPositionY() - _pJog1->getPositionY());

	return distancia;
}

sf::Vector2f Entidades::Inimigo::getDistanciaJog2Vector()
{
	sf::Vector2f distancia;

	distancia.x = abs(getPositionX() - _pJog2->getPositionX());
	distancia.y = abs(getPositionY() - _pJog2->getPositionY());

	return distancia;
}

double Entidades::Inimigo::getDistanciaoInicio()
{
	return sqrt(pow(getPositionX() - posInicialX, 2) + pow(getPositionY() - posInicialY, 2));
}

sf::Vector2f Entidades::Inimigo::getDistanciaInicioVector()
{
	sf::Vector2f distancia;

	distancia.x = getPosition().x - posInicialX;
	distancia.y = getPosition().y - posInicialY;

	return distancia;
}

Entidades::Jogador* Entidades::Inimigo::getJogadorMaisProximo()
{

	double distanciaJog1 = -1;
	double distanciaJog2 = -1;

	if (_pJog1) distanciaJog1 = getDistanciaJogador1();
	if (_pJog2) distanciaJog2 = getDistanciaJogador2();

	if (_pJog1 != nullptr && _pJog2 != nullptr)
	{
		if (distanciaJog1 >= 0 && distanciaJog1 <= distanciaJog2)
		{
			return _pJog1;
		}
		else
		{
			return _pJog2;
		}
	}
	else
	{
		if (_pJog1)
		{	
			return _pJog1;
		}
		else if (_pJog2)
		{	
			return  _pJog2;
		}
	}
	return nullptr;
}

void Entidades::Inimigo::setPosInicial(float x, float y)
{
	posInicialX = x;
	posInicialY = y;
}

void Entidades::Inimigo::registraDados()
{
	Entidades::Personagem::registraDados();
	buffer << posInicialX << " " << posInicialY << " ";
}



