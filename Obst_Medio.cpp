#include "Obst_Medio.h"

Entidades::Obst_Medio::Obst_Medio(float inicialX, float inicialY, Gerenciadores::Gerenciador_Grafico* pgra) 
	:Obstaculo(inicialX,inicialY,pgra), _duracaoParalisia(8000.f)
{

	// Gerenciador grafico
	//_pGraf = pgra; n�o precisa fazer isso aqui,� inicializado l� no Ente, basta chamar a construtura de Obstaculo
	// que a cadeia de construtoras garante a inicializa��o

	// Imagem do obstaculo
	sf::Texture* textura = new sf::Texture();

	if (!textura->loadFromFile("assets/BarreiraEletrica.png")) {
		std::cout << "Falha ao carregar textura!" << std::endl;
	}
	setTexture(textura);
	_body.setScale(1.f, 1.f);

	// Posicao
	setPositionX(inicialX);
	setPositionY(inicialY);
	_body.setPosition(Position);

	_segundos = 0;
	_danoso = true;
}

Entidades::Obst_Medio::~Obst_Medio() {
	_pGraf = nullptr;
	_danoso = false;

	if (_pTexture)
	{
		delete _pTexture;
	}
	_pTexture = nullptr;
}

void Entidades::Obst_Medio::executar() {
	desenhar();
}

void Entidades::Obst_Medio::obstacular(Entidades::Jogador* pJog) {
	if (pJog == nullptr) {
		std::cerr << "Erro ao acessar ponteiro jogador.\n";
		return;
	}

	pJog->setParalisado(true, _duracaoParalisia);
}

void Entidades::Obst_Medio::salvar() {

}

void Entidades::Obst_Medio::render() {

}