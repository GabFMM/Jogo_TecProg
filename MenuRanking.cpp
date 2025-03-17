#include "MenuRanking.h"
#include "Jogo.h"
#include "Constantes.h"

using namespace Menus;

MenuRanking::MenuRanking(Gerenciadores::Gerenciador_Grafico* _pGraf, Ranking* rank)
	: Ente(_pGraf), _mudouEstado(false), _botaoVoltarMenuPrincipal(), _textosBotao(), _mouse(),
	_houveClique(false), _titulo(), _fonte(), _rank(rank)
{
	carregarFonte();
	criarBackground();
	criarTitulo();
	criarBotao();
}

MenuRanking::~MenuRanking()
{
	_pGraf = nullptr;
}

void MenuRanking::carregarFonte()
{
	_fonte = _pGraf->getFont();
}

void MenuRanking::criarBotao()
{
	// --------- >> Botao voltar

	// Caracteristicas do conteudo
	_textosBotao = "Voltar";
	_botaoVoltarMenuPrincipal.setFont(_fonte);
	_botaoVoltarMenuPrincipal.setString(_textosBotao);
	_botaoVoltarMenuPrincipal.setCharacterSize(Constantes::RANKING_TAMANHO_BOTOES);
	_botaoVoltarMenuPrincipal.setStyle(sf::Text::Style::Regular);
	_botaoVoltarMenuPrincipal.setFillColor(sf::Color::White);

	// Posicao
	sf::Vector2u tamJanela = _pGraf->getWindow()->getSize();
	sf::FloatRect tamTexto = _botaoVoltarMenuPrincipal.getGlobalBounds();

	sf::Vector2f posicao;
	posicao.x = ((float)tamJanela.x / 2.f) - (tamTexto.width / 2.f);
	posicao.y = (float)tamJanela.y / 10.f * 9.f;

	_botaoVoltarMenuPrincipal.setPosition(posicao);
}

void MenuRanking::criarTitulo()
{
	// Caracteristicas do conteudo
	_titulo.setFont(_fonte);
	_titulo.setString("Ranking");
	_titulo.setCharacterSize(Constantes::RANKING_TAMANHO_TITULO);
	_titulo.setStyle(sf::Text::Style::Regular);
	_titulo.setFillColor(sf::Color::White);

	// Posicao
	sf::Vector2u tamJanela = _pGraf->getWindow()->getSize();
	sf::FloatRect tamTexto = _titulo.getGlobalBounds();

	sf::Vector2f posicao;
	posicao.x = ((float)tamJanela.x / 2.f) - (tamTexto.width / 2.f);
	posicao.y = (float)tamJanela.y / 15.f;

	_titulo.setPosition(posicao);
}

void MenuRanking::criarBackground()
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

void MenuRanking::verificarMouse()
{
	verificarMovimento();

	_houveClique = sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

void MenuRanking::verificarMovimento()
{
	sf::Vector2i posicaoMouse = _mouse.getPosition();

	// Verifica onde o mouse esta e destaca o botao
	
		if (_botaoVoltarMenuPrincipal.getGlobalBounds().contains((float)posicaoMouse.x, (float)posicaoMouse.y)) {
			// Destaca
			destacarTexto(_botaoVoltarMenuPrincipal);

			// Aplica a funcao correspondente
			if (_houveClique)retornaMenuPrincipal();
		}
		else {
			padronizar(_botaoVoltarMenuPrincipal);
		}
	
}

void MenuRanking::destacarTexto(sf::Text& texto)
{
	char c = *(texto.getString().begin());
	if (c != '>') {
		std::string frase = "> " + texto.getString() + " <";
		texto.setCharacterSize(Constantes::RANKING_TAMANHO_BOTOES + 10);
		texto.setString(frase);
		texto.setStyle(sf::Text::Style::Underlined);

		// Reposiciona no meio da janela
		reposicionarTexto(texto);
	}
}

void MenuRanking::reposicionarTexto(sf::Text& texto)
{
	sf::Vector2u tamJanela = _pGraf->getWindow()->getSize();
	sf::FloatRect tamTexto = texto.getGlobalBounds();

	sf::Vector2f posicao;
	posicao.x = ((float)tamJanela.x / 2.f) - (tamTexto.width / 2.f);
	posicao.y = texto.getPosition().y;

	texto.setPosition(posicao);
}

void MenuRanking::padronizar(sf::Text& texto)
{
	texto.setCharacterSize(Constantes::RANKING_TAMANHO_BOTOES);
	texto.setString(_textosBotao);
	texto.setStyle(sf::Text::Style::Regular);

	// Reposiciona no meio da janela
	reposicionarTexto(texto);
}

void MenuRanking::desenharMenu()
{
	_pGraf->getWindow()->draw(_body);
	_pGraf->getWindow()->draw(_titulo);
	_pGraf->getWindow()->draw(_botaoVoltarMenuPrincipal);
}

void MenuRanking::executar()
{
	while (!_mudouEstado) {
		sf::Event event;
		while (_pGraf->getWindow()->pollEvent(event)) {

			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				retornaMenuPrincipal();
			}
		}

		_pGraf->clear();

		desenharMenu();
		mostrarRanking(_rank);

		verificarMouse();

		_pGraf->display();
	}
}

void MenuRanking::mostrarRanking(Ranking* rank)
{
	// Obtem os dados do Ranking
	std::vector<std::pair<std::string, int>> dados;
	dados = rank->getVector();

	// Configurações iniciais para os textos
	sf::Text texto;
	texto.setFont(_fonte);
	texto.setCharacterSize(Constantes::RANKING_TAMANHO_BOTOES);
	texto.setFillColor(sf::Color::Black);

	// Posição inicial para desenhar os textos
	sf::Vector2u tamJanela = _pGraf->getWindow()->getSize();
	float posicaoY = tamJanela.y / 4.5f; // Começar abaixo do título
	float incrementoY = Constantes::RANKING_TAMANHO_BOTOES + 12; // Espaçamento entre linhas

	for (int i = 0; i < dados.size(); ++i)
	{
		std::string nome = dados[i].first;
		int pontos = dados[i].second;

		// Cria o texto formatado
		std::string textoFormatado = nome;
		textoFormatado += std::string(30 - nome.size() - std::to_string(pontos).size(), '.');
		textoFormatado += std::to_string(pontos);

		// Configura o texto
		texto.setString(textoFormatado);

		// Agora que o texto foi configurado, calculamos o tamanho
		sf::FloatRect tamTexto = texto.getGlobalBounds();

		// Calcula a posição centralizada
		float posicaoX = ((float)tamJanela.x / 2.f) - (tamTexto.width / 2.f);

		// Condicao para que caiba o maior numero possivel de pontuacoes
		if (posicaoY + i * incrementoY >= _botaoVoltarMenuPrincipal.getPosition().y - _botaoVoltarMenuPrincipal.getGlobalBounds().height)
		{
			break;
		}

		texto.setPosition(posicaoX, posicaoY + i * incrementoY);

		// Desenha o texto
		_pGraf->getWindow()->draw(texto);
	}
}

void MenuRanking::retornaMenuPrincipal()
{
	Jogo::mudarStateNum(Constantes::STATE_MENU);
	_mudouEstado = true;
}
