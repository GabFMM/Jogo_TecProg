#include "Projetil.h"
#include "Constantes.h"
#include <exception>
#include <cmath>

// ------------------------------- PUBLIC ----------------------------------------------------

Entidades::Projetil::Projetil(float inicialX, float inicialY, Gerenciadores::Gerenciador_Grafico* pGraf)
	: Entidade(inicialX, inicialY, pGraf), _lancar(false), _dano(0), dt(0.f), _tempoMaxVoo(Constantes::TEMPO_MAX_VOO)
{
	setTipo(Constantes::TIPO_PROJETIL);

	sf::Texture* textura = new sf::Texture();

	if (!textura->loadFromFile("assets/fogo3.png")) {
		std::cout << "Falha ao carregar textura!" << std::endl;
	}

	setTexture(textura);
	_body.setScale(0.1f, 0.1f);

	// Velocidade
	setSpeed(0.f,0.f);

	_clock.restart();
}

Entidades::Projetil::~Projetil() 
{
	_pGraf = nullptr;
	_dano = 0;

	if (_pTexture)
	{
		delete _pTexture;
	}
	_pTexture = nullptr;
}

void Entidades::Projetil::executar() 
{
	if (_lancar) {
		dt += _clock.restart().asSeconds();

		mover();

		desenhar();
	}
}

void Entidades::Projetil::mover() {
	if (!tempoDeVooExcedido()) {
		Position += _speed;
		_body.setPosition(Position);
	}
	else {
		resetar();
	}
}

const bool Entidades::Projetil::estaDentroDaJanela() const {
	return 
		Position.x + getSpeedX() > 0.f &&
		Position.x + getSpeedX() + _body.getGlobalBounds().width < _pGraf->getWindow()->getSize().x &&
		Position.y + getSpeedY() > 0.f &&
		Position.y + getSpeedY() + _body.getGlobalBounds().width < _pGraf->getWindow()->getSize().y;
}

const bool Entidades::Projetil::tempoDeVooExcedido() const {
	return dt >= _tempoMaxVoo;
}

void Entidades::Projetil::resetar() {
	dt = 0.f;
	_lancar = false;
	setPosition(0.f, 0.f);
}

double Entidades::Projetil::calcularForcaY(double distancia, double gravidade, double forcaX)
{
	/*
		Usando a formula de lancamento obliquo:

		dS = V? * sin(2 * theta) / g
		theta = 45?
		dS = V? * 1 / g
		dS = ( Vx? + Vy? ) / g
		dS * g = ( Vx? + Vy? )
		dS * g - Vx? = Vy?

		Vy = sqrt( dS * g - Vx? )
	*/

	//double forcaY = std::sqrt(distancia * gravidade - forcaX * forcaX);
	double forcaY = std::sqrt(distancia * gravidade - forcaX * forcaX);

	return forcaY;
}

void Entidades::Projetil::inverteLado() {
	// Para a direita
	if (getSpeedX() > 0.f) 
	{
		_body.setRotation(180.f);
	}
	// Para a esquerda
	else {
		_body.setRotation(0.f);
	}
}

// Salva o buffer no Salvamento.txt
void Entidades::Projetil::SalvarDataBuffer(std::ofstream& arquivo)
{
	try
	{
		arquivo.open("Salvamento.txt", std::ios::app);

		if (!arquivo.is_open())
		{
			throw std::runtime_error("Erro ao abrir o arquivo para escrita.");
		}

		arquivo << buffer.str();

		arquivo.close();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exceção em salvarDados: " << e.what() << std::endl;
	}
}

void Entidades::Projetil::registraDados()
{
	Entidades::Entidade::registraDados();
	buffer << _dano << " " << _lancar <<"\n";
}

void Entidades::Projetil::setDano(int dano) {
	_dano = dano;
}

const int Entidades::Projetil::getDano() const {
	return _dano;
}

void Entidades::Projetil::lancar(float speedX, float speedY, int dano) {
	setSpeed(speedX, speedY);
	setDano(dano);
	inverteLado();

	_lancar = true;
}

void Entidades::Projetil::setLancar(const bool lancar) {
	_lancar = lancar;
}

const bool Entidades::Projetil::getLancar() const {
	return _lancar;
}