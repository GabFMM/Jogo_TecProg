#include "MenuFases.h"
#include "Jogo.h"
#include "Constantes.h"

using namespace Menus;

MenuFases::MenuFases(Gerenciadores::Gerenciador_Grafico* _pGraf) : Entidades::Ente(_pGraf), _mudouEstado(false), _faseFloresta(false), _faseCastelo(false), _retangulos(), _textos(), sizeRetangulos(0), sizeTextos(0)
{
	carregarFonte();
	criaBackground();
	criaResto();

	carregarObjetos();
}

MenuFases::~MenuFases()
{
	_pGraf = nullptr;

	// Esvaziar o vetor de retangulos
	_retangulos.clear();

	// Esvaziar o vetor de textos
	_textos.clear();
}

void MenuFases::carregarFonte()
{
	_fonte = _pGraf->getFont();
}

void MenuFases::criaBackground()
{
	sf::Texture* textura = new sf::Texture();
	textura = _pGraf->getTextura("Pergaminho");
	setTexture(textura);

	// tamanho do background
	sf::Vector2u tamJanela = _pGraf->getWindow()->getSize();
	float escalaX = (float)tamJanela.x / _body.getGlobalBounds().width;
	float escalaY = (float)tamJanela.y / _body.getGlobalBounds().height;

	_body.setScale
	(
		escalaX,
		escalaY
	);
}

void MenuFases::criaResto()
{
	sf::Vector2u tamJanela = _pGraf->getWindow()->getSize();
	sf::Vector2f posicao;

	// ------ >> Cria texto Fases

	_textoFases.setFont(_fonte);
	_textoFases.setString("Selecione a fase:");
	_textoFases.setCharacterSize(Constantes::MENU_FASES_TAMANHO_BOTOES + 10);
	_textoFases.setStyle(sf::Text::Style::Regular);
	_textoFases.setFillColor(sf::Color::Black);

	posicao.x = ((float)tamJanela.x / 2.f) - ((float)_textoFases.getGlobalBounds().width / 2.f);
	posicao.y = (float)tamJanela.y / 10.f;

	_textoFases.setPosition(posicao);

	// ------ >> Cria o nome da fase Floresta

	_nomeFaseFloresta.setFont(_fonte);
	_nomeFaseFloresta.setString("A floresta");
	_nomeFaseFloresta.setCharacterSize(Constantes::MENU_FASES_TAMANHO_BOTOES);
	_nomeFaseFloresta.setStyle(sf::Text::Style::Regular);
	_nomeFaseFloresta.setFillColor(sf::Color::Black);

	posicao.x = ((float)tamJanela.x / 3.f) - ((float)_nomeFaseFloresta.getGlobalBounds().width / 2.f);
	posicao.y = (float)tamJanela.y / 10.f * 2.5f;

	_nomeFaseFloresta.setPosition(posicao);

	// ------ >> Cria o nome da fase Castelo

	_nomeFaseCastelo.setFont(_fonte);
	_nomeFaseCastelo.setString("O castelo");
	_nomeFaseCastelo.setCharacterSize(Constantes::MENU_FASES_TAMANHO_BOTOES);
	_nomeFaseCastelo.setStyle(sf::Text::Style::Regular);
	_nomeFaseCastelo.setFillColor(sf::Color::Black);

	posicao.x = ((float)tamJanela.x / 3.f * 2.f) - ((float)_nomeFaseCastelo.getGlobalBounds().width / 2.f);
	posicao.y = (float)tamJanela.y / 10.f * 2.5f;

	_nomeFaseCastelo.setPosition(posicao);

	// ------ >> Cria imagem da fase floresta

	sf::Texture* textura1 = new sf::Texture();
	textura1 = _pGraf->getTextura("Floresta_Icone");

	_imagemFaseFloresta.setSize(sf::Vector2f(textura1->getSize()));
	_imagemFaseFloresta.setTexture(textura1);
	_imagemFaseFloresta.setScale(3.f, 3.f);

	posicao.x = _nomeFaseFloresta.getPosition().x + (float)_nomeFaseFloresta.getGlobalBounds().width / 2.f;
	posicao.x -= (float)_imagemFaseFloresta.getGlobalBounds().width / 2.f;
	posicao.y = _nomeFaseFloresta.getPosition().y + (float)_nomeFaseFloresta.getGlobalBounds().height * 3.f;

	_imagemFaseFloresta.setPosition(posicao);

	// ------ >> Cria imagem da fase 2
	
	sf::Texture* textura2 = new sf::Texture();
	textura2 = _pGraf->getTextura("Castelo_Icone");
	
	_imagemFaseCastelo.setSize(sf::Vector2f(textura2->getSize()));
	_imagemFaseCastelo.setTexture(textura2);
	_imagemFaseCastelo.setScale(3.f, 3.f);

	posicao.x = _nomeFaseCastelo.getPosition().x + (float)_nomeFaseCastelo.getGlobalBounds().width / 2.f;
	posicao.x -= (float)_imagemFaseCastelo.getGlobalBounds().width / 2.f;
	posicao.y = _nomeFaseCastelo.getPosition().y + (float)_nomeFaseCastelo.getGlobalBounds().height * 3.f;

	_imagemFaseCastelo.setPosition(posicao);

	// ------ >> Cria botao para confirmar a sele��o da fase

	_botaoConfirmaFase.setFont(_fonte);
	_botaoConfirmaFase.setString("Confirmar fase");
	_botaoConfirmaFase.setCharacterSize(Constantes::MENU_FASES_TAMANHO_BOTOES);
	_botaoConfirmaFase.setStyle(sf::Text::Style::Regular);
	_botaoConfirmaFase.setFillColor(sf::Color::Black);

	posicao.x = ((float)tamJanela.x / 2.f) - ((float)_botaoConfirmaFase.getGlobalBounds().width / 2.f);
	posicao.y = tamJanela.y / 10.f * 8.f;

	_botaoConfirmaFase.setPosition(posicao);
}

// Preenche o vetor de objetos interagiveis com os seus respectivos metodos
void MenuFases::carregarObjetos()
{
	_retangulos.clear();
	_textos.clear();

	_retangulos.emplace_back
	(
		&_imagemFaseFloresta,
		[this]() { executarFaseFloresta(); }
	);

	_retangulos.emplace_back
	(
		&_imagemFaseCastelo,
		[this]() { executarFaseCastelo(); }
	);

	_textos.emplace_back
	(
		&_botaoConfirmaFase,
		[this]() { executarConfirmaFase(); }
	);

	sizeRetangulos = static_cast<int>(_retangulos.size());
	sizeTextos = static_cast<int>(_textos.size());
}

void MenuFases::verificarCliques()
{
	// verifica se houve clique esquerdo do mouse
	if (!mouse.isButtonPressed(sf::Mouse::Left)) return;

	// Procuro onde aconteceu
	
	sf::Vector2f posicaoMouse;
	posicaoMouse.x = (float)mouse.getPosition().x;
	posicaoMouse.y = (float)mouse.getPosition().y;

	// Nos retangulos
	for (int i = 0; i < _retangulos.size(); i++) {
		if (_retangulos[i].first != nullptr && _retangulos[i].first->getGlobalBounds().contains(posicaoMouse)) {
			_retangulos[i].second();
		}
	}
	
	// Nos botoes
	for (int i = 0; i < _textos.size(); i++) {
		if (_textos[i].first != nullptr && _textos[i].first->getGlobalBounds().contains(posicaoMouse)) {
			_textos[i].second();
		}
	}
}

void MenuFases::destacar(sf::Text* texto)
{
	// Deixa o texto sublinhado
	texto->setStyle(sf::Text::Style::Underlined);
}

void MenuFases::destacar(sf::RectangleShape* retangulo)
{
	// Deixa o retangulo com borda
	retangulo->setOutlineThickness(2.5f);
	retangulo->setOutlineColor(sf::Color::Black);
}

void MenuFases::padronizar(sf::Text* texto)
{
	// Deixa o texto nao sublinhado
	texto->setStyle(sf::Text::Style::Regular);
}

void MenuFases::padronizar(sf::RectangleShape* retangulo)
{
	// Deixa o retangulo sem borda
	retangulo->setOutlineThickness(0.f);
}

void MenuFases::desenhar()
{
	_pGraf->getWindow()->draw(_body);

	for (int i = 0; i < sizeRetangulos; i++) {
		_pGraf->getWindow()->draw(*(_retangulos[i].first));
	}
	for (int i = 0; i < sizeTextos; i++) {
		_pGraf->getWindow()->draw(*(_textos[i].first));
	}

	_pGraf->getWindow()->draw(_textoFases);
	_pGraf->getWindow()->draw(_nomeFaseFloresta);
	_pGraf->getWindow()->draw(_nomeFaseCastelo);
}

void MenuFases::executar()
{
	while (!_mudouEstado) {
		sf::Event event;
		while (_pGraf->getWindow()->pollEvent(event)) {
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				//Voltar para o menu Jogadores
				Jogo::mudarStateNum(Constantes::STATE_MENU_JOGADORES);
				_mudouEstado = true;
			}
		}

		_pGraf->clear();

		desenhar();
		verificarCliques();

		_pGraf->display();
	}
}

void MenuFases::executarFaseFloresta()
{
	if (!_faseFloresta) {
		// Destaco a imagem clicada
		_faseFloresta = true;
		destacar(&_imagemFaseFloresta);

		// Padronizo a outra imagem
		_faseCastelo = false;
		padronizar(&_imagemFaseCastelo);
	}
}

void MenuFases::executarFaseCastelo()
{
	if (!_faseCastelo) {
		// Destaco a imagem clicada
		_faseCastelo = true;
		destacar(&_imagemFaseCastelo);

		// Padronizo a outra imagem
		_faseFloresta = false;
		padronizar(&_imagemFaseFloresta);
	}
}

void MenuFases::executarConfirmaFase()
{
	if (_faseFloresta) {
		//Jogar Floresta
		Jogo::mudarStateNum(Constantes::STATE_FLORESTA);
		_mudouEstado = true;
	}
	else if (_faseCastelo) {
		//Jogar Castelo
		Jogo::mudarStateNum(Constantes::STATE_CASTELO);
		_mudouEstado = true;
	}
}