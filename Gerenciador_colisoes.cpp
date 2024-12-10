#include "Gerenciador_Colisoes.h"
#include "Inimigo.h"

Gerenciadores::Gerenciador_Colisoes::Gerenciador_Colisoes(float gravidade) 
	: _listaInimigos(), _listaObstaculos(), _listaProjetil(), _gravidade(gravidade)
{
	_jogador1 = nullptr;
	_jogador2 = nullptr;
	
	_listaInimigos.clear();
	_listaObstaculos.clear();
	_listaProjetil.clear();
}

Gerenciadores::Gerenciador_Colisoes::~Gerenciador_Colisoes() 
{
	_jogador1 = nullptr;
	_jogador2 = nullptr;
	
}


void Gerenciadores::Gerenciador_Colisoes::setJogador1(Entidades::Jogador* pJogador) 
{
	if (pJogador == nullptr) 
	{
		std::cerr << "Ponteiro de jogador invalido. Impossivel incluir em G.Colisoes.\n";
		return;
	}

	_jogador1 = pJogador;
}

void Gerenciadores::Gerenciador_Colisoes::setJogador2(Entidades::Jogador* pJogador) {
	if (pJogador == nullptr) {
		std::cerr << "Ponteiro de jogador invalido. Impossivel incluir em G.Colisoes.\n";
		return;
	}

	_jogador2 = pJogador;
}

void Gerenciadores::Gerenciador_Colisoes::incluirInimigo(Entidades::Inimigo* pInimigo) {
	if (pInimigo == nullptr) {
		std::cerr << "Ponteiro de inimigo invalido. Impossivel incluir em G.Colisoes.\n" << std::endl;
		return;
	}

	_listaInimigos.push_back(pInimigo);
}

void Gerenciadores::Gerenciador_Colisoes::incluirObstaculo(Entidades::Obstaculo* pObstaculo) {
	if (pObstaculo == nullptr) {
		std::cerr << "Ponteiro de obstaculo invalido. Impossivel incluir em G.Colisoes.\n" << std::endl;
		return;
	}

	_listaObstaculos.push_back(pObstaculo);
}

void Gerenciadores::Gerenciador_Colisoes::incluirProjetil(Entidades::Projetil* pProjetil) {
	if (pProjetil == nullptr) {
		std::cerr << "Ponteiro de projetil invalido. Impossivel incluir em G.Colisoes.\n" << std::endl;
		return;
	}

	_listaProjetil.insert(pProjetil);
}

sf::Vector2f Gerenciadores::Gerenciador_Colisoes::calculaColisao(Entidades::Entidade* ent1, Entidades::Entidade* ent2) {
	sf::Vector2f pos1 = ent1->getPosition();
	sf::Vector2f pos2 = ent2->getPosition();

	sf::FloatRect bounds1 = ent1->getBody().getGlobalBounds();
	sf::FloatRect bounds2 = ent2->getBody().getGlobalBounds();

	sf::Vector2f tam1(bounds1.width, bounds1.height);
	sf::Vector2f tam2(bounds2.width, bounds2.height);

	sf::Vector2f distanciaEntreCentros(
		fabs((pos1.x + tam1.x / 2.0f) - (pos2.x + tam2.x / 2.0f)),
		fabs((pos1.y + tam1.y / 2.0f) - (pos2.y + tam2.y / 2.0f))
	);

	sf::Vector2f somaMetades(
		tam1.x / 2.0f + tam2.x / 2.0f,
		tam1.y / 2.0f + tam2.y / 2.0f
	);

	return sf::Vector2f(distanciaEntreCentros.x - somaMetades.x, distanciaEntreCentros.y - somaMetades.y);
}

void Gerenciadores::Gerenciador_Colisoes::tratarColisoesJogsObstacs()
{
	bool colidiuComChao1 = false; // Flag para verificar se o jogador 1 está no chão
	bool colidiuComChao2 = false; // Flag para verificar se o jogador 2 está no chão

	// Itera sobre todos os obstáculos
	for (auto& obstaculo : _listaObstaculos)
	{
		// Tratamento para o jogador 1
		if (_jogador1 != nullptr) {
			sf::Vector2f ds = calculaColisao(_jogador1, obstaculo);
			if (ds.x < 0.0f && ds.y < 0.0f) // Verifica se há colisão
			{
				obstaculo->obstacular(_jogador1);
				if (fabs(ds.x) < fabs(ds.y)) // Testa qual direção da colisão é predominante (horizontal ou vertical)
				{
					// Colisão predominante na direção horizontal
					if (_jogador1->getPosition().x < obstaculo->getPosition().x)
					{
						// Colisão pela direita do jogador (esquerda do obstáculo)
						_jogador1->setPosition(obstaculo->getPosition().x - _jogador1->getBody().getGlobalBounds().width, _jogador1->getPosition().y);
					}
					else
					{
						// Colisão pela esquerda do jogador (direita do obstáculo)
						_jogador1->setPosition(obstaculo->getPosition().x + obstaculo->getBody().getGlobalBounds().width, _jogador1->getPosition().y);
					}
					_jogador1->setSpeed(0, _jogador1->getSpeedY()); // Zera a velocidade horizontal do jogador
				}
				else
				{
					// Colisão predominante na direção vertical
					if (_jogador1->getPosition().y < obstaculo->getPosition().y)
					{
						// Colisão por baixo do obstáculo (jogador colide com o topo do obstáculo)
						colidiuComChao1 = true;
						_jogador1->setGround(true); // Marca que o jogador está no chão
						_jogador1->setSpeed(_jogador1->getSpeedX(), 0); // Zera a velocidade vertical do jogador
						_jogador1->setPosition(_jogador1->getPosition().x, obstaculo->getPosition().y - _jogador1->getBody().getGlobalBounds().height);
					}
					else
					{
						// Colisão por cima do jogador (jogador colide com a parte inferior do obstáculo)
						_jogador1->setSpeed(_jogador1->getSpeedX(), 0); // Zera a velocidade vertical para impedir que o jogador continue subindo
						_jogador1->setPosition(_jogador1->getPosition().x, obstaculo->getPosition().y + obstaculo->getBody().getGlobalBounds().height);
					}
				}
			}
		}

		// Tratamento para o jogador 2 (similar ao jogador 1)
		if (_jogador2 != nullptr)
		{
			sf::Vector2f ds = calculaColisao(_jogador2, obstaculo);
			if (ds.x < 0.0f && ds.y < 0.0f) // Verifica se há colisão
			{
				obstaculo->obstacular(_jogador2);
				if (fabs(ds.x) < fabs(ds.y)) // Testa qual direção da colisão é predominante (horizontal ou vertical)
				{
					// Colisão predominante na direção horizontal
					if (_jogador2->getPosition().x < obstaculo->getPosition().x)
					{
						// Colisão pela direita do jogador (esquerda do obstáculo)
						_jogador2->setPosition(obstaculo->getPosition().x - _jogador2->getBody().getGlobalBounds().width, _jogador2->getPosition().y);
					}
					else
					{
						// Colisão pela esquerda do jogador (direita do obstáculo)
						_jogador2->setPosition(obstaculo->getPosition().x + obstaculo->getBody().getGlobalBounds().width, _jogador2->getPosition().y);
					}
					_jogador2->setSpeed(0, _jogador2->getSpeedY()); // Zera a velocidade horizontal do jogador
				}
				else
				{
					// Colisão predominante na direção vertical
					if (_jogador2->getPosition().y < obstaculo->getPosition().y)
					{
						// Colisão por baixo do obstáculo (jogador colide com o topo do obstáculo)
						colidiuComChao2 = true;
						_jogador2->setGround(true); // Marca que o jogador está no chão
						_jogador2->setSpeed(_jogador2->getSpeedX(), 0); // Zera a velocidade vertical do jogador
						_jogador2->setPosition(_jogador2->getPosition().x, obstaculo->getPosition().y - _jogador2->getBody().getGlobalBounds().height);
					}
					else
					{
						// Colisão por cima do jogador (jogador colide com a parte inferior do obstáculo)
						_jogador2->setSpeed(_jogador2->getSpeedX(), 0); // Zera a velocidade vertical para impedir que o jogador continue subindo
						_jogador2->setPosition(_jogador2->getPosition().x, obstaculo->getPosition().y + obstaculo->getBody().getGlobalBounds().height);
					}
				}
			}
		}
	}

	// Caso nenhum dos jogadores tenha colidido com o chão, marca que não estão no chão
	if (!colidiuComChao1 && _jogador1 != nullptr) _jogador1->setGround(false);
	if (!colidiuComChao2 && _jogador2 != nullptr) _jogador2->setGround(false);
}




void Gerenciadores::Gerenciador_Colisoes::tratarColisoesJogsInimgs() 
{
	// Caso 1: os dois jogadores foram criados
	if (_jogador1 != nullptr && _jogador2 != nullptr) {
		for (itInimigo = _listaInimigos.begin(); itInimigo != _listaInimigos.end(); itInimigo++) 
		{
			if (verificarColisao(static_cast<Entidades::Entidade*>(*itInimigo), static_cast<Entidades::Entidade*>(_jogador1))) 
			{
				// Jogador para de mover
				// Jogador toma dano, se preciso
				(*itInimigo)->danificar(_jogador1);
				
				// Inimigo para de mover
				// Inimigo toma dano, se preciso
			}

			if (verificarColisao(static_cast<Entidades::Entidade*>(*itInimigo), static_cast<Entidades::Entidade*>(_jogador2))) 
			{
				// Jogador para de mover
				// Jogador toma dano, se preciso
				(*itInimigo)->danificar(_jogador2);

				// Inimigo para de mover
				// Inimigo toma dano, se preciso
			}
		}
	}
	// Caso 2: apenas um jogador foi criado
	else if (_jogador1 != nullptr) {
		for (itInimigo = _listaInimigos.begin(); itInimigo != _listaInimigos.end(); itInimigo++) {
			if (verificarColisao(static_cast<Entidades::Entidade*>(*itInimigo), static_cast<Entidades::Entidade*>(_jogador1))) {
				// Jogador para de mover
				// Jogador toma dano, se preciso
				(*itInimigo)->danificar(_jogador1);

				// Inimigo para de mover
				// Inimigo toma dano, se preciso
			}
		}
	}

}

void Gerenciadores::Gerenciador_Colisoes::tratarColisoesJogsProjeteis() 
{
	// Caso 1: os dois jogadores foram criados
	if (_jogador1 != nullptr && _jogador2 != nullptr) {
		for (itProjetil = _listaProjetil.begin(); itProjetil != _listaProjetil.end(); itProjetil++) {
			if (verificarColisao(static_cast<Entidades::Entidade*>(*itProjetil), static_cast<Entidades::Entidade*>(_jogador1))) {
				// Jogador toma dano
				for (int i = 0; i < (*itProjetil)->getDano(); i++)
					_jogador1->operator--();
				// Projetil desaparece
				(*itProjetil)->~Projetil();
			}

			if (verificarColisao(static_cast<Entidades::Entidade*>(*itProjetil), static_cast<Entidades::Entidade*>(_jogador2))) {
				// Jogador toma dano
				for (int i = 0; i < (*itProjetil)->getDano(); i++)
					_jogador2->operator--();
				// Projetil desaparece
				(*itProjetil)->~Projetil();
			}

		}
	}
	// Caso 2: apenas um jogador foi criado
	else if (_jogador1 != nullptr) 
	{
		for (itProjetil = _listaProjetil.begin(); itProjetil != _listaProjetil.end(); itProjetil++) {
			if (verificarColisao(static_cast<Entidades::Entidade*>(*itProjetil), static_cast<Entidades::Entidade*>(_jogador1))) {
				// Jogador toma dano
				for (int i = 0; i < (*itProjetil)->getDano(); i++)
					_jogador1->operator--();
				// Projetil desaparece
				(*itProjetil)->~Projetil();
			}
		}
	}
}

const bool Gerenciadores::Gerenciador_Colisoes::verificarColisao(Entidades::Entidade* pEnt1, Entidades::Entidade* pEnt2) const
{
	if (pEnt1 == nullptr || pEnt2 == nullptr) 
	{
		std::cerr << "Ponteiro de entidade invalido. Impossivel verificar colisao.\n";
		return false;
	}

	return pEnt1->getBody().getGlobalBounds().intersects(pEnt2->getBody().getGlobalBounds());
}

void Gerenciadores::Gerenciador_Colisoes::aplicarGravidade() 
{
	// Caso 1: os dois jogadores foram criados
	if (_jogador1 != nullptr && _jogador2 != nullptr) 
	{
		if (!_jogador1->getOnGround())
		{
			_jogador1->sofrerGravidade(_gravidade);
		}
		
		if (!_jogador2->getOnGround())
		{
			_jogador2->sofrerGravidade(_gravidade);
		}

		
	}
	// Caso 2: apenas um jogador foi criado
	else if (_jogador1 != nullptr) 
	{

		if (!_jogador1->getOnGround())
		{
			_jogador1->sofrerGravidade(_gravidade);
		}
	}
}

void Gerenciadores::Gerenciador_Colisoes::executar()
{
	aplicarGravidade();
	tratarColisoesJogsObstacs();
	tratarColisoesJogsProjeteis();
	tratarColisoesJogsInimgs();
}
