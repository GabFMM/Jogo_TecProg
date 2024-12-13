#include "Projetil.h"

// ------------------------------- PUBLIC ----------------------------------------------------

Entidades::Projetil::Projetil(float inicialX, float inicialY, Gerenciadores::Gerenciador_Grafico* pGraf)
	: Entidade(inicialX, inicialY, pGraf), _lancar(false), _dano(0), dt(0.f), _tempoMaxVoo(6.f){

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

Entidades::Projetil::~Projetil() {
	_pGraf = nullptr;
	_dano = 0;

	if (_pTexture)
	{
		delete _pTexture;
	}
	_pTexture = nullptr;
}

void Entidades::Projetil::executar() {
	if (_lancar) {
		dt += _clock.restart().asSeconds();

		mover();

		desenhar();
	}
}

void Entidades::Projetil::mover() {
	if (estaDentroDaJanela() && !tempoDeVooExcedido()) {
		Position.x += getSpeedX();
		_body.setPosition(Position);
	}
	else {
		resetar();
	}
}

const bool Entidades::Projetil::estaDentroDaJanela() const {
	return 
		Position.x + getSpeedX() > 0.f &&
		Position.x + getSpeedX() < _pGraf->getWindow()->getSize().x;
}

const bool Entidades::Projetil::tempoDeVooExcedido() const {
	return dt >= _tempoMaxVoo;
}

void Entidades::Projetil::resetar() {
	dt = 0.f;
	_lancar = false;
	setPosition(0.f, 0.f);
}

void Entidades::Projetil::inverteLado() {
	// Para a direita
	if (getSpeedX() > 0.f) {
		_body.setRotation(180.f);
	}
	// Para a esquerda
	else {
		_body.setRotation(0.f);
	}
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

void Entidades::Projetil::salvar()
{
}

void Entidades::Projetil::render()
{
}