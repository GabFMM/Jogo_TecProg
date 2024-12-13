#include "InimigoDificil.h"

// IMPORTANTE
// direcao = -1 é esquerda, direcao = 1 é direita
// _clock e _segundos controlam a frequencia de bater do boss

Entidades::InimigoDificil::InimigoDificil(float inicialX, float inicialY, Gerenciadores::Gerenciador_Grafico* pgra, Entidades::Jogador* pJog, int vidas) : Inimigo(inicialX, inicialY, pgra, pJog, vidas), _vidasPerdidas(0), _projetil(nullptr), _direcao(0), _segundosIntervaloPro(0.f) {

	setMaldade(1);
	_speed.x = 0.06f;

	sf::Texture* textura = new sf::Texture();

	if (!textura->loadFromFile("assets/chefe.png"))
	{
		std::cout << "Falha ao carregar textura!" << std::endl;
	}

	setTexture(textura);
	_body.setScale(0.1f, 0.1f);

	_clock.restart();
	deltaTime.restart();
}

Entidades::InimigoDificil::~InimigoDificil() {
	_projetil = nullptr;

	_vidasPerdidas = 0;
	_direcao = 0;
}

void Entidades::InimigoDificil::setProjetil(Entidades::Projetil* pProj) {
	if (pProj == nullptr) {
		std::cerr << "Ponteiro de projetil invalido. Impossivel vincular com boss.\n";
		return;
	}

	_projetil = pProj;
}

void Entidades::InimigoDificil::executar() {
	float dt = deltaTime.restart().asSeconds();

	_segundos += dt;
	_segundosIntervaloPro += dt;

	verificarVida();

	desenhar();
	 
	danificar(_pJog);
}

void Entidades::InimigoDificil::verificarVida() {
	if (_vidasPerdidas > _num_vidas / 2) {
		_speed.x = 0.09f;
		setMaldade(2);
	}
}

void Entidades::InimigoDificil::mover() {
	// Define a direcao do inimigo
	if (_pJog->getPositionX() - getPositionX() < 0.f) 
		_direcao = -1; // para a esquerda
	else 
		_direcao = 1;  // para a direita

	sf::Vector2f velocidadeAtual = _speed;
	velocidadeAtual.x *= _direcao;

	Position += velocidadeAtual;
	_body.setPosition(Position);
}

void Entidades::InimigoDificil::danificar(Entidades::Jogador* pJog) {
	// Fora de alcance
	if (getDistanciaJogador() > 500.f) return;
	
	// Dentro do alcance para se mover
	mover();

	// Dentro do alcance para atirar
	if (getDistanciaJogador() > _body.getGlobalBounds().width * 1.65f) {
		atirar();
	}
	// Dentro do alcance para bater
	else {
		bater();
	}
}

void Entidades::InimigoDificil::atirar() {
	// Cria o projetil
	if (!_projetil->getLancar() && _segundosIntervaloPro > 3.f) {
		// Zera o cronometro
		_segundosIntervaloPro = 0.f;

		// "Cria" projetil
		_projetil->setPosition
		(
			getPositionX(),
			_pJog->getPositionY() + (_pJog->getBody().getGlobalBounds().height / 4.f)
		);

		_projetil->lancar(0.15f * _direcao, 0.f, getMaldade());
	}
}

void Entidades::InimigoDificil::bater() {
	if (_segundos > 0.5f) {
		_segundos = 0;

		for (int i = 0; i < getMaldade(); i++)
			_pJog->operator--();

		_pJog->knockBack(this);
	}
}

void Entidades::InimigoDificil::salvar() {

}

void Entidades::InimigoDificil::render() {

}