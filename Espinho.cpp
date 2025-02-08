#include "Espinho.h"
#include "Constantes.h"
Entidades::Espinho::Espinho(int dano, float inicialX, float inicialY, Gerenciadores::Gerenciador_Grafico* pgra)
	: Obstaculo(inicialX,inicialY,pgra), _dano(dano)
{
	setTipo(Constantes::TIPO_ESPINHO);
	// Gerenciador grafico
	//_pGraf = pgra;

	// Imagem
	sf::Texture* textura = _pGraf->getTextura("Espinho");

	/*
	if (!textura->loadFromFile("assets/PlataformaEspinho.png")) 
	{
		std::cout << "Falha ao carregar textura!" << std::endl;
	}
	*/


	setTexture(textura);
	_body.setScale(0.8f, 1.5f);

	// Posicao
	setPositionX(inicialX);
	setPositionY(inicialY);
	_body.setPosition(Position);

	// Se da dano
	setDanoso(true);
}

Entidades::Espinho::~Espinho()
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

void Entidades::Espinho::executar()
{
	desenhar();

	// Tempo
	if (!_danoso){
		_segundos += _clock.getElapsedTime().asSeconds();

		if (_segundos > 15.f) {
			_danoso = true;
			_segundos = 0.f;
			_clock.restart();
		}
	}
	else {
		_clock.restart();
	}
	
}

void Entidades::Espinho::obstacular(Entidades::Jogador* pJog)
{
	if (pJog == nullptr) 
	{
		std::cerr << "Erro ao acessar ponteiro jogador.\n";
		return;
	}

	if (_danoso) 
	{
			pJog->operator--(_dano);
		pJog->knockBack(this);
		_danoso = false;
	}
}

void Entidades::Espinho::SalvarDataBuffer(std::ofstream& arquivo)
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
		std::cerr << "Exce��o em salvarDados: " << e.what() << std::endl;
	}
}

void Entidades::Espinho::registraDados()
{
	/*
	int _dano;
	*/
	Entidades::Obstaculo::registraDados();
	buffer << _dano << "\n";
}


