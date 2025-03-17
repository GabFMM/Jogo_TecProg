#include "TelaFimDeJogo.h"
#include "Jogo.h"
#include "Constantes.h"

TelaFimDeJogo::TelaFimDeJogo(Gerenciadores::Gerenciador_Grafico* _pGraf, Entidades::Jogador* jog1, Entidades::Jogador* jog2) : Ente(_pGraf), cor(190, 190, 190), _mudouEstado(false), _jogador1(jog1), _jogador2(jog2)
{
	carregarFonte();

	criaBackground();
	criarTitulo();
	criarSubTitulo();
	criarBotao();
}

TelaFimDeJogo::~TelaFimDeJogo()
{

}

void TelaFimDeJogo::carregarFonte()
{
	_fonte = _pGraf->getFont();
}

void TelaFimDeJogo::criaBackground()
{
	sf::Texture* textura = new sf::Texture();

	textura = _pGraf->getTextura("Fim_De_Jogo");
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

void TelaFimDeJogo::criarTitulo()
{
	// Caracteristicas do conteudo
	_titulo.setFont(_fonte);
	_titulo.setString("Fim de jogo");
	_titulo.setCharacterSize(Constantes::TAMANHO_TITULO);
	_titulo.setStyle(sf::Text::Style::Regular);
	_titulo.setFillColor(cor);

	// Posicao
	sf::Vector2u tamJanela = _pGraf->getWindow()->getSize();
	sf::FloatRect tamTexto = _titulo.getGlobalBounds();

	sf::Vector2f posicao;
	posicao.x = ((float)tamJanela.x / 2.f) - (tamTexto.width / 2.f); // meio x da janela
	posicao.y = (float)tamJanela.y / 10.f;

	_titulo.setPosition(posicao);
}

void TelaFimDeJogo::criarSubTitulo()
{
	std::string nome;

	// Verifica quais jogadores foram criados

	// Caso 1: Ambos foram criados
	if (_jogador1 != nullptr && _jogador2 != nullptr) {
		
		// Verifica qual esta vivo

		// Caso 1: ambos estao vivos
		if (_jogador1->getVivo() && _jogador2->getVivo()) {
			nome = "Muito bem, parabens!";
		}
		// Caso 2: somente um esta vivo
		else if (_jogador1->getVivo() || _jogador2->getVivo()) {
			nome = "Parabens, mas valeu a pena?";
		}
		// Case 3: nenhum esta vivo
		else {
			nome = "Boa sorte na próxima vez.";
		}
	}
	// Caso 2: apenas o jogador 1 foi criado
	else if (_jogador1 != nullptr) {
		
		// Verifica se esta vivo
		if (_jogador1->getVivo()) {
			nome = "Muito bem, parabens!";
		}
		else {
			nome = "Boa sorte na próxima vez.";
		}
	}
	// Caso 3: apenas o jogador 2 foi criado
	else if (_jogador2 != nullptr) {

		// Verifica se esta vivo
		if (_jogador2->getVivo()) {
			nome = "Muito bem, parabens!";
		}
		else {
			nome = "Boa sorte na próxima vez.";
		}
	}

	// Caracteristicas do conteudo
	_subTitulo.setFont(_fonte);
	_subTitulo.setString(nome);
	_subTitulo.setCharacterSize(Constantes::TAMANHO_SUBTITULO);
	_subTitulo.setStyle(sf::Text::Style::Regular);
	_subTitulo.setFillColor(cor);

	// Posicao
	sf::Vector2u tamJanela = _pGraf->getWindow()->getSize();
	sf::FloatRect tamTexto = _subTitulo.getGlobalBounds();

	sf::Vector2f posicao;
	posicao.x = ((float)tamJanela.x / 2.f) - (tamTexto.width / 2.f); // meio x da janela
	posicao.y = (float)tamJanela.y / 10.f * 3.f;

	_subTitulo.setPosition(posicao);
}

void TelaFimDeJogo::criarBotao()
{
	// Caracteristicas do conteudo
	_botaoVoltarAoMenu.setFont(_fonte);
	_botaoVoltarAoMenu.setString("Voltar ao menu");
	_botaoVoltarAoMenu.setCharacterSize(Constantes::TAMANHO_BOTOES);
	_botaoVoltarAoMenu.setStyle(sf::Text::Style::Regular);
	_botaoVoltarAoMenu.setFillColor(cor);

	// Posicao
	sf::Vector2u tamJanela = _pGraf->getWindow()->getSize();
	sf::FloatRect tamTexto = _botaoVoltarAoMenu.getGlobalBounds();

	sf::Vector2f posicao;
	posicao.x = ((float)tamJanela.x / 2.f) - (tamTexto.width / 2.f); // meio x da janela
	posicao.y = (float)tamJanela.y / 10.f * 6.f;

	_botaoVoltarAoMenu.setPosition(posicao);
}

void TelaFimDeJogo::verificarMouse()
{
	bool houveClique = sf::Mouse::isButtonPressed(_mouse.Left);

	sf::Vector2i posicao = _mouse.getPosition();

	if (_botaoVoltarAoMenu.getGlobalBounds().contains((float)posicao.x, (float)posicao.y)) {
		destacar();

		if (houveClique) {
			Jogo::mudarStateNum(10);
			_mudouEstado = true;
		}
	}
	else {
		padronizar();
	}
}

void TelaFimDeJogo::destacar()
{
	char c = *(_botaoVoltarAoMenu.getString().begin());
	if (c != '>') {
		std::string frase = "> " + _botaoVoltarAoMenu.getString() + " <";
		_botaoVoltarAoMenu.setCharacterSize(Constantes::TAMANHO_BOTOES + 10);
		_botaoVoltarAoMenu.setString(frase);
		_botaoVoltarAoMenu.setStyle(sf::Text::Style::Underlined);

		// Reposiciona no meio da janela
		reposicionar();
	}
}

void TelaFimDeJogo::padronizar()
{
	_botaoVoltarAoMenu.setCharacterSize(Constantes::TAMANHO_BOTOES);
	_botaoVoltarAoMenu.setString("Voltar ao menu");
	_botaoVoltarAoMenu.setStyle(sf::Text::Style::Regular);

	// Reposiciona no meio da janela
	reposicionar();
}

void TelaFimDeJogo::reposicionar()
{
	sf::Vector2u tamJanela = _pGraf->getWindow()->getSize();
	sf::FloatRect tamTexto = _botaoVoltarAoMenu.getGlobalBounds();

	sf::Vector2f posicao;
	posicao.x = ((float)tamJanela.x / 2.f) - (tamTexto.width / 2.f);
	posicao.y = _botaoVoltarAoMenu.getPosition().y;

	_botaoVoltarAoMenu.setPosition(posicao);
}

void TelaFimDeJogo::desenharTela()
{
	_pGraf->getWindow()->draw(_body);
	_pGraf->getWindow()->draw(_titulo);
	_pGraf->getWindow()->draw(_subTitulo);
	_pGraf->getWindow()->draw(_botaoVoltarAoMenu);
}

void TelaFimDeJogo::executar()
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

		desenharTela();

		verificarMouse();

		_pGraf->display();
	}
}