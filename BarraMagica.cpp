#include "BarraMagica.h"
#include "Constantes.h"
Entidades::BarraMagica::BarraMagica(float inicialX, float inicialY, Gerenciadores::Gerenciador_Grafico* pgra)
	:Obstaculo(inicialX,inicialY,pgra), _duracaoParalisia(Constantes::DURACAO_PARALISIA)
{
	setTipo(Constantes::TIPO_BARRA_MAGICA);

	// Imagem do obstaculo
	sf::Texture* textura = _pGraf->getTextura("BarraMagica");
	setTexture(textura);
	_body.setScale(1.f, 1.f);

	// Posicao
	setPositionX(inicialX);
	setPositionY(inicialY);
	_body.setPosition(Position);

	_segundos = 0;
	_danoso = true;
}

Entidades::BarraMagica::~BarraMagica() 
{
	_pGraf = nullptr;
	_danoso = false;

	if (_pTexture)
	{
		delete _pTexture;
	}
	_pTexture = nullptr;
}

void Entidades::BarraMagica::executar() 
{
	desenhar();
}

// Paralisa o jogador por um certo periodo, caso ele colida por cima a paralisia nao ocorre
void Entidades::BarraMagica::obstacular(Entidades::Jogador* pJog) 
{
	if (pJog == nullptr) 
	{
		std::cerr << "Erro ao acessar ponteiro jogador.\n";
		return;
	}

	sf::FloatRect JogBounds = pJog->getBody().getGlobalBounds();
	sf::FloatRect ObsBound = getBody().getGlobalBounds();

	if (JogBounds.top + JogBounds.height <= ObsBound.top + 3.f)
	{
		if (!pJog->getParalisado())
		{
			pJog->setGround(true);
			pJog->pular();
		}
	}
	else
	{
		pJog->setParalisado(true, _duracaoParalisia);
	}
}

// Coloca as informacoes do buffer no arquivo
void Entidades::BarraMagica::SalvarDataBuffer(std::ofstream& arquivo)
{
	try
	{
		arquivo.open("Salvamento.txt",std::ios::app);
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

void Entidades::BarraMagica::registraDados()
{
	Entidades::Obstaculo::registraDados();
	buffer << _duracaoParalisia << "\n";
}



