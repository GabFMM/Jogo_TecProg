#include "Obst_Dificil.h"

Entidades::Obst_Dificil::Obst_Dificil(int dano, float inicialX, float inicialY, Gerenciadores::Gerenciador_Grafico* pgra)
	: Obstaculo(inicialX,inicialY,pgra), _dano(dano)
{
	// Gerenciador grafico
	_pGraf = pgra;

	// Imagem
	sf::Texture* textura = new sf::Texture();

	if (!textura->loadFromFile("assets/PlataformaEspinho.png")) {
		std::cout << "Falha ao carregar textura!" << std::endl;
	}
	setTexture(textura);
	_body.setScale(1.f, 1.f);

	// Posicao
	setPositionX(inicialX);
	setPositionY(inicialY);
	_body.setPosition(Position);

	// Se da dano
	setDanoso(true);
}

Entidades::Obst_Dificil::~Obst_Dificil() 
{
	_pGraf = nullptr;
	_dano = 0;
	_danoso = false;

	if (_pTexture)
	{
		delete _pTexture;
	}
	_pTexture = nullptr;
}

void Entidades::Obst_Dificil::executar() 
{
	desenhar();

	// Tempo
	if (!_danoso){
		_segundos += _clock.getElapsedTime().asSeconds();

		if (_segundos > 5.f) {
			_danoso = true;
			_segundos = 0.f;
			_clock.restart();
		}
	}
	else {
		_clock.restart();
	}
	
}

void Entidades::Obst_Dificil::obstacular(Entidades::Jogador* pJog) 
{
	if (pJog == nullptr) {
		std::cerr << "Erro ao acessar ponteiro jogador.\n";
		return;
	}

	if (_danoso) {
		for (int i = 0; i < _dano; i++) {
			pJog->operator--();
			
		
		}
		_danoso = false;
	}
}

void Entidades::Obst_Dificil::salvar() 
{

}

void Entidades::Obst_Dificil::render() 
{

}