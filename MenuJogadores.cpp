#include "MenuJogadores.h"
#include "Jogo.h"
#include "Constantes.h"

using namespace Menus;

MenuJogadores::MenuJogadores(Jogo* jogo, Gerenciadores::Gerenciador_Grafico* pGraf) : Ente(pGraf), _jogo(jogo), _mudouEstado(false), _estaDigitandoCaixa1(false), _estaDigitandoCaixa2(false), _primeiraVezCaixa1(true), _primeiraVezCaixa2(true)
{
	carregarFonte();

	criaBackground();
	criaResto();
}

MenuJogadores::~MenuJogadores()
{
}

void MenuJogadores::carregarFonte()
{
	_fonte = _pGraf->getFont();
}

void MenuJogadores::criaBackground()
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

void MenuJogadores::criaResto() {
	sf::Vector2u tamJanela = _pGraf->getWindow()->getSize();
	sf::Vector2f posicao;

	// ------ >> Cria o titulo

	_textoJogadores.setFont(_fonte);
	_textoJogadores.setString("Escreva o(s) nome(s) do(s) jogador(es):");
	_textoJogadores.setCharacterSize(Constantes::MENU_JOG_TAMANHO_BOTOES + 10);
	_textoJogadores.setStyle(sf::Text::Style::Regular);
	_textoJogadores.setFillColor(sf::Color::Black);

	posicao.x = ((float)tamJanela.x / 2.f) - ((float)_textoJogadores.getGlobalBounds().width / 2.f);
	posicao.y = (float)tamJanela.y / 10.f;
	_textoJogadores.setPosition(posicao);

	// ------ >> Cria o botao de um jogador

	_botaoUmJog.setFont(_fonte);
	_botaoUmJog.setString("Jogador 1:");
	_botaoUmJog.setCharacterSize(Constantes::MENU_JOG_TAMANHO_BOTOES);
	_botaoUmJog.setStyle(sf::Text::Style::Regular);
	_botaoUmJog.setFillColor(sf::Color::Black);

	posicao.x = ((float)tamJanela.x / 3.f) - ((float)_botaoUmJog.getGlobalBounds().width / 2.f);
	posicao.y = (float)tamJanela.y / 10.f * 3.f;
	_botaoUmJog.setPosition(posicao);

	// ------ >> Cria o botao de dois jogadores

	_botaoDoisJog.setFont(_fonte);
	_botaoDoisJog.setString("Jogador 2:");
	_botaoDoisJog.setCharacterSize(Constantes::MENU_JOG_TAMANHO_BOTOES);
	_botaoDoisJog.setStyle(sf::Text::Style::Regular);
	_botaoDoisJog.setFillColor(sf::Color::Black);

	posicao.x = ((float)tamJanela.x / 3.f * 2.f) - ((float)_botaoDoisJog.getGlobalBounds().width / 2.f);
	posicao.y = (float)tamJanela.y / 10.f * 3.f;
	_botaoDoisJog.setPosition(posicao);

	// ------ >> Cria a caixa de texto do jogador 1

	sf::Color cor(192, 192, 192);

	sf::FloatRect tamTextoJog = _textoJogadores.getGlobalBounds();
	sf::Vector2f tamCaixaTexto;
	tamCaixaTexto.x = (float)tamTextoJog.width / 2.f;
	tamCaixaTexto.y = (float)tamTextoJog.height / 4.f * 3.f;

	_caixaTexto1.setSize(tamCaixaTexto);
	_caixaTexto1.setFillColor(cor);

	posicao.x = _botaoUmJog.getPosition().x + (float)_botaoUmJog.getGlobalBounds().width / 2.f;
	posicao.x -= (float)_caixaTexto1.getGlobalBounds().width / 2.f;
	posicao.y = _botaoUmJog.getPosition().y + (float)_botaoUmJog.getGlobalBounds().height * 3.f;

	_caixaTexto1.setPosition(posicao);

	_nomeJog1.setFont(_fonte);
	_nomeJog1.setString("Nome jogador 1:");
	_nomeJog1.setCharacterSize(Constantes::MENU_JOG_TAMANHO_BOTOES - 10);
	_nomeJog1.setStyle(sf::Text::Style::Regular);
	_nomeJog1.setFillColor(sf::Color::Black);

	_nomeJog1.setPosition(_caixaTexto1.getPosition().x + 5.f, _caixaTexto1.getPosition().y - 8.f);

	// ------ >> Cria a caixa de texto do jogador 2

	_caixaTexto2.setSize(tamCaixaTexto);
	_caixaTexto2.setFillColor(cor);

	posicao.x = _botaoDoisJog.getPosition().x + (float)_botaoDoisJog.getGlobalBounds().width / 2.f;
	posicao.x -= (float)_caixaTexto2.getGlobalBounds().width / 2.f;
	posicao.y = _botaoDoisJog.getPosition().y + (float)_botaoDoisJog.getGlobalBounds().height * 3.f;

	_caixaTexto2.setPosition(posicao);

	_nomeJog2.setFont(_fonte);
	_nomeJog2.setString("Nome jogador 2:");
	_nomeJog2.setCharacterSize(Constantes::MENU_JOG_TAMANHO_BOTOES - 10);
	_nomeJog2.setStyle(sf::Text::Style::Regular);
	_nomeJog2.setFillColor(sf::Color::Black);

	_nomeJog2.setPosition(_caixaTexto2.getPosition().x + 5.f, _caixaTexto2.getPosition().y - 8.f);

	// ------ >> Cria o botao confirma nome(s)

	_botaoConfirmaNomes.setFont(_fonte);
	_botaoConfirmaNomes.setString("Confirmar nome(s)");
	_botaoConfirmaNomes.setCharacterSize(Constantes::MENU_JOG_TAMANHO_BOTOES);
	_botaoConfirmaNomes.setStyle(sf::Text::Style::Regular);
	_botaoConfirmaNomes.setFillColor(sf::Color::Black);

	posicao.x = ((float)tamJanela.x / 2.f) - ((float)_botaoConfirmaNomes.getGlobalBounds().width / 2.f);
	posicao.y = tamJanela.y / 10.f * 8.f;
	_botaoConfirmaNomes.setPosition(posicao);
}

void MenuJogadores::desenhar()
{
	_pGraf->getWindow()->draw(_body);
	_pGraf->getWindow()->draw(_textoJogadores);
	_pGraf->getWindow()->draw(_botaoUmJog);
	_pGraf->getWindow()->draw(_botaoDoisJog);
	_pGraf->getWindow()->draw(_caixaTexto1);
	_pGraf->getWindow()->draw(_caixaTexto2);
	_pGraf->getWindow()->draw(_nomeJog1);
	_pGraf->getWindow()->draw(_nomeJog2);
	_pGraf->getWindow()->draw(_botaoConfirmaNomes);
}

void MenuJogadores::verificarCliques()
{
	// verifica se houve clique esquerdo do mouse
	if (!_mouse.isButtonPressed(sf::Mouse::Left)) return;

	// Procuro onde aconteceu

	sf::Vector2f posicaoMouse;
	posicaoMouse.x = (float)_mouse.getPosition().x;
	posicaoMouse.y = (float)_mouse.getPosition().y;

	// Como ha poucos itens interagiveis, por opcao, prefiro fazer isso do que criar um vetor com funcoes

	if (_caixaTexto1.getGlobalBounds().contains(posicaoMouse.x, posicaoMouse.y))
		executarCaixaTexto1();
	else if (_caixaTexto2.getGlobalBounds().contains(posicaoMouse.x, posicaoMouse.y))
		executarCaixaTexto2();
	else if (_botaoConfirmaNomes.getGlobalBounds().contains(posicaoMouse.x, posicaoMouse.y))
		executarConfirmaNomes();
}

void MenuJogadores::destacar(sf::RectangleShape* retangulo)
{
	// Deixa o retangulo com borda
	retangulo->setOutlineThickness(2.5f);
	retangulo->setOutlineColor(sf::Color::Black);
}

void MenuJogadores::padronizar(sf::RectangleShape* retangulo)
{
	// Deixa o retangulo sem borda
	retangulo->setOutlineThickness(0.f);
}

void MenuJogadores::executarCaixaTexto1()
{
	if (_primeiraVezCaixa1) {
		_primeiraVezCaixa1 = false;
		_nomeJog1.setString("");
	}

	destacar(&_caixaTexto1);

	_estaDigitandoCaixa1 = true;

	sf::Event event;
	while (_estaDigitandoCaixa1) {
		while (_pGraf->getWindow()->pollEvent(event)) {
			// Detecta se o usu�rio pressionou Enter ou Escape
			if
			(
				event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Escape)
			)
			{
				_estaDigitandoCaixa1 = false; // Sai do modo de digita��o
			}

			// Captura o texto digitado
			if (event.type == sf::Event::TextEntered) {
				if (event.text.unicode < 32) { // Casos espec�ficos
					if (event.text.unicode == 8 && _nome1.size() > 0)
						// Apaga o ultimo caracter
						_nome1.pop_back();
				}
				else if (event.text.unicode < 128 && _nome1.size() < 12) { // Caso geral
					_nome1 += static_cast<char>(event.text.unicode);
				}
				_nomeJog1.setString(_nome1);
			}
		}
		_pGraf->clear();

		desenhar();

		_pGraf->display();
	}

	padronizar(&_caixaTexto1);
}

void MenuJogadores::executarCaixaTexto2()
{
	if (_primeiraVezCaixa2) {
		_primeiraVezCaixa2 = false;
		_nomeJog2.setString("");
	}

	destacar(&_caixaTexto2);

	_estaDigitandoCaixa2 = true;

	sf::Event event;
	while (_estaDigitandoCaixa2) {
		while (_pGraf->getWindow()->pollEvent(event)) {
			// Detecta se o usu�rio pressionou Enter ou Escape
			if
			(
				event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Escape)
			)
			{
				_estaDigitandoCaixa2 = false; // Sai do modo de digita��o
			}

			// Captura o texto digitado
			if (event.type == sf::Event::TextEntered) {
				if (event.text.unicode < 32) { // Casos espec�ficos
					if (event.text.unicode == 8 && _nome2.size() > 0)
						// Apaga o ultimo caracter
						_nome2.pop_back();
				}
				else if (event.text.unicode < 128 && _nome2.size() < 12) { // Caso geral
					_nome2 += static_cast<char>(event.text.unicode);
				}
				_nomeJog2.setString(_nome2);
			}
		}
		_pGraf->clear();

		desenhar();

		_pGraf->display();
	}

	padronizar(&_caixaTexto2);
}

void MenuJogadores::executarConfirmaNomes()
{
	// Verifica se o nome do jogador 1 nao foi preenchido
	if (!_nome1.empty() && !_primeiraVezCaixa1)
	{
		// Entra no menu de fases
		if (_jogo->criarJogador1(_nome1)) {
			Jogo::mudarStateNum(Constantes::STATE_MENU_FASES);
			_mudouEstado = true;
		}
	}
	// Verifica se o nome do jogador 2 nao foi preenchido
	if (!_nome2.empty() && !_primeiraVezCaixa2)
	{
		// Entra no menu de fases
		if (_jogo->criarJogador2(_nome2)) {
			Jogo::mudarStateNum(Constantes::STATE_MENU_FASES);
			_mudouEstado = true;
		}
	}
}


void MenuJogadores::executar()
{
	while (!_mudouEstado) {
		sf::Event event;
		while (_pGraf->getWindow()->pollEvent(event)) {
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				Jogo::mudarStateNum(10);
				_mudouEstado = true;
			}
		}

		_pGraf->clear();

		desenhar();

		verificarCliques();

		_pGraf->display();
	}
}
