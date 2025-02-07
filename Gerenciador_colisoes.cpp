#include "Gerenciador_Colisoes.h"
#include "Inimigo.h"
#include "Constantes.h"

/*
Os c�lculos vetoriais utilizados na fun��o calculaColisao foram desenvolvidos por Mateus Burda.
Cr�ditos ao autor:
GitHub: https://github.com/MatheusBurda
YouTube: https://www.youtube.com/@burdacanal9100

Agradecimentos pelo compartilhamento do conhecimento e pelas contribui��es � comunidade.
*/


//Singleton inicializando o atributo static
Gerenciadores::Gerenciador_Colisoes* Gerenciadores::Gerenciador_Colisoes::instancia = nullptr;

Gerenciadores::Gerenciador_Colisoes::Gerenciador_Colisoes(float gravidade)
	: _listaInimigos(), _listaObstaculos(), _listaProjetil(), _gravidade(gravidade)
{
	_jogador1 = nullptr;
	_jogador2 = nullptr;

	_listaInimigos.clear();
	_listaObstaculos.clear();
	_listaProjetil.clear();
}

Gerenciadores::Gerenciador_Colisoes* Gerenciadores::Gerenciador_Colisoes::getInstancia()
{
	if (instancia==nullptr)
	{
		instancia = new Gerenciadores::Gerenciador_Colisoes(Constantes::GRAVIDADE);
	}
	return instancia;
}

Gerenciadores::Gerenciador_Colisoes::~Gerenciador_Colisoes()
{
	_jogador1 = nullptr;
	_jogador2 = nullptr;

	_listaInimigos.clear();
	_listaObstaculos.clear();
	_listaProjetil.clear();
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

void Gerenciadores::Gerenciador_Colisoes::setJogador2(Entidades::Jogador* pJogador)
{
	if (pJogador == nullptr) {
		std::cerr << "Ponteiro de jogador invalido. Impossivel incluir em G.Colisoes.\n";
		return;
	}

	_jogador2 = pJogador;
}

void Gerenciadores::Gerenciador_Colisoes::incluirInimigo(Entidades::Inimigo* pInimigo)
{
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

void Gerenciadores::Gerenciador_Colisoes::incluirProjetil(Entidades::Projetil* pProjetil)
{
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
void Gerenciadores::Gerenciador_Colisoes::tratarColisoesJogsObstacs() {
	bool colidiuComChao1 = false; // Flag para verificar se o jogador 1 est� no ch�o
	bool colidiuComChao2 = false; // Flag para verificar se o jogador 2 est� no ch�o

	// Itera sobre todos os obst�culos
	for (itObstaculo = _listaObstaculos.begin(); itObstaculo != _listaObstaculos.end(); ++itObstaculo) {
		// Tratamento para o jogador 1
		if (_jogador1 != nullptr && _jogador1->getVivo()) {
			sf::Vector2f ds = calculaColisao(_jogador1, (*itObstaculo));
			if (ds.x < 0.0f && ds.y < 0.0f) // Verifica se h� colis�o
			{
				(*itObstaculo)->obstacular(_jogador1);

				if ((*itObstaculo)->getTipo() == 11) continue; // se for obstaculo dificil / espinho

				if (fabs(ds.x) < fabs(ds.y)) // Testa qual dire��o da colis�o � predominante (horizontal ou vertical)
				{
					// Colis�o predominante na dire��o horizontal
					if (_jogador1->getPosition().x < (*itObstaculo)->getPosition().x)
					{
						// Colis�o pela direita do jogador (esquerda do obst�culo)
						_jogador1->setPosition((*itObstaculo)->getPosition().x - _jogador1->getBody().getGlobalBounds().width, _jogador1->getPosition().y);
					}
					else
					{
						// Colis�o pela esquerda do jogador (direita do obst�culo)
						_jogador1->setPosition((*itObstaculo)->getPosition().x + (*itObstaculo)->getBody().getGlobalBounds().width, _jogador1->getPosition().y);
					}
					_jogador1->setSpeed(0, _jogador1->getSpeedY()); // Zera a velocidade horizontal do jogador
				}
				else
				{
					// Colis�o predominante na dire��o vertical
					if (_jogador1->getPosition().y < (*itObstaculo)->getPosition().y)
					{
						// Colis�o por baixo do obst�culo (jogador colide com o topo do obst�culo)
						colidiuComChao1 = true;
						_jogador1->setGround(true); // Marca que o jogador est� no ch�o
						_jogador1->setSpeed(_jogador1->getSpeedX(), 0); // Zera a velocidade vertical do jogador
						_jogador1->setPosition(_jogador1->getPosition().x, (*itObstaculo)->getPosition().y - _jogador1->getBody().getGlobalBounds().height);
						
					}
					else
					{
						// Colis�o por cima do jogador (jogador colide com a parte inferior do obst�culo)
						_jogador1->setSpeed(_jogador1->getSpeedX(), 0); // Zera a velocidade vertical para impedir que o jogador continue subindo
						_jogador1->setPosition(_jogador1->getPosition().x, (*itObstaculo)->getPosition().y + (*itObstaculo)->getBody().getGlobalBounds().height);
					}
				}
			}
		}

		// Tratamento para o jogador 2 (similar ao jogador 1)
		if (_jogador2 != nullptr && _jogador2->getVivo()) {

			sf::Vector2f ds = calculaColisao(_jogador2, (*itObstaculo));
			if (ds.x < 0.0f && ds.y < 0.0f) // Verifica se h� colis�o
			{
				(*itObstaculo)->obstacular(_jogador2);

				if ((*itObstaculo)->getTipo() == 11) continue; // se for obstaculo dificil / espinho

				if (fabs(ds.x) < fabs(ds.y)) // Testa qual dire��o da colis�o � predominante (horizontal ou vertical)
				{
					// Colis�o predominante na dire��o horizontal
					if (_jogador2->getPosition().x < (*itObstaculo)->getPosition().x)
					{
						// Colis�o pela direita do jogador (esquerda do obst�culo)
						_jogador2->setPosition((*itObstaculo)->getPosition().x - _jogador2->getBody().getGlobalBounds().width, _jogador2->getPosition().y);
					}
					else
					{
						// Colis�o pela esquerda do jogador (direita do obst�culo)
						_jogador2->setPosition((*itObstaculo)->getPosition().x + (*itObstaculo)->getBody().getGlobalBounds().width, _jogador2->getPosition().y);
					}
					_jogador2->setSpeed(0, _jogador2->getSpeedY()); // Zera a velocidade horizontal do jogador
				}
				else
				{
					// Colis�o predominante na dire��o vertical
					if (_jogador2->getPosition().y < (*itObstaculo)->getPosition().y)
					{
						// Colis�o por baixo do obst�culo (jogador colide com o topo do obst�culo)
						colidiuComChao2 = true;
						_jogador2->setGround(true); // Marca que o jogador est� no ch�o
						_jogador2->setSpeed(_jogador2->getSpeedX(), 0); // Zera a velocidade vertical do jogador
						_jogador2->setPosition(_jogador2->getPosition().x, (*itObstaculo)->getPosition().y - _jogador2->getBody().getGlobalBounds().height);
					}
					else
					{
						// Colis�o por cima do jogador (jogador colide com a parte inferior do obst�culo)
						_jogador2->setSpeed(_jogador2->getSpeedX(), 0); // Zera a velocidade vertical para impedir que o jogador continue subindo
						_jogador2->setPosition(_jogador2->getPosition().x, (*itObstaculo)->getPosition().y + (*itObstaculo)->getBody().getGlobalBounds().height);
					}
				}
			}
		}
	}

	// Caso nenhum dos jogadores tenha colidido com o ch�o, marca que n�o est�o no ch�o
	if (!colidiuComChao1 && _jogador1 != nullptr) _jogador1->setGround(false);
	if (!colidiuComChao2 && _jogador2 != nullptr) _jogador2->setGround(false);
}

void Gerenciadores::Gerenciador_Colisoes::tratarColisoesJogsInimgs()
{


	for (itInimigo = _listaInimigos.begin(); itInimigo != _listaInimigos.end(); itInimigo++)
	{
		bool colidiuComChao1 = false;
		if (*itInimigo != nullptr && (*itInimigo)->getVivo())
		{
			(*itInimigo)->setGround(false);


			//Para cada Inimigo vamos percorrer os Obstaculos, testar e tratar colis�es
			for (itObstaculo = _listaObstaculos.begin(); itObstaculo != _listaObstaculos.end(); ++itObstaculo)
			{
				colidiuComChao1 = false;

				sf::Vector2f ds = calculaColisao((*itInimigo), (*itObstaculo));
				if (ds.x < 0.0f && ds.y < 0.0f) //Verifica se h� colis�o
				{
					// Verifica qual o delta maior absoluto para saber em qual dire��o h� mais colis�o
					if (fabs(ds.x) < fabs(ds.y))
					{
						//Colis�o na horizontal
						if ((*itInimigo)->getPosition().x < (*itObstaculo)->getPosition().x)
						{
							//Colisao pela direita do Inimigo e esquerda do obstaculo
							(*itInimigo)->setPosition((*itObstaculo)->getPositionX() - (*itInimigo)->getBody().getGlobalBounds().width, (*itInimigo)->getPositionY());
							
						}
						else
						{
							// Colis�o pela esquerda do Inimigo direita do Obst�culo
							(*itInimigo)->setPosition((*itObstaculo)->getPosition().x + (*itObstaculo)->getBody().getGlobalBounds().width, (*itInimigo)->getPosition().y);
						}
							//Inverte o sentido do movimento do inimigo
							if((*itInimigo)->getTipo()==4)
								(*itInimigo)->setSpeed((*itInimigo)->getSpeedX()*-1, (*itInimigo)->getSpeedY());
							
					}
					else
					{
						// Colis�o predominante na dire��o vertical
						if ((*itInimigo)->getPosition().y < (*itObstaculo)->getPosition().y)
						{
							// Colis�o por baixo do obst�culo Inimigo colide com o topo do obst�culo
							colidiuComChao1 = true;
							(*itInimigo)->setGround(true); // Marca que o Inimigo est� no ch�o
							(*itInimigo)->setSpeed((*itInimigo)->getSpeedX(), 0); // Zera a velocidade vertical do Inimigo
							(*itInimigo)->setPosition((*itInimigo)->getPosition().x, (*itObstaculo)->getPosition().y - (*itInimigo)->getBody().getGlobalBounds().height );
						}
						else
						{
							// Colis�o por cima do Inimigo  colide com a parte inferior do obst�culo
							(*itInimigo)->setSpeed((*itInimigo)->getSpeedX(), 0); // Zera a velocidade vertical para impedir que o Inimigo continue subindo
							(*itInimigo)->setPosition((*itInimigo)->getPosition().x, (*itObstaculo)->getPosition().y + (*itObstaculo)->getBody().getGlobalBounds().height);
						}


					}
				}
				if (_jogador1 != nullptr)
				{
					sf::Vector2f dsInimigoJog = calculaColisao((*itInimigo), _jogador1);
					if (dsInimigoJog.x < 0.0f && dsInimigoJog.y < 0.0f && !_jogador1->getAtacando())
					{
						(*itInimigo)->danificar(_jogador1);
					}
					else if (dsInimigoJog.x < 10.0f && dsInimigoJog.y < 3.0f && _jogador1->getAtacando() &&
						((_jogador1->getDirecao() == 1 && (*itInimigo)->getPosition().x > _jogador1->getPosition().x) ||
							(_jogador1->getDirecao() == -1 && (*itInimigo)->getPosition().x < _jogador1->getPosition().x)))
					{
						_jogador1->atacarInimigo((*itInimigo));
					}
				}

				if (_jogador2 != nullptr)
				{
					sf::Vector2f dsInimigoJog2 = calculaColisao((*itInimigo), _jogador2);
					if (dsInimigoJog2.x < 0.0f && dsInimigoJog2.y < 0.0f && !_jogador2->getAtacando())
					{
						(*itInimigo)->danificar(_jogador2);
					}
					else if (dsInimigoJog2.x < 10.0f && dsInimigoJog2.y < 3.0f && _jogador2->getAtacando() &&
						((_jogador2->getDirecao() == 1 && (*itInimigo)->getPosition().x > _jogador2->getPosition().x) ||
							(_jogador2->getDirecao() == -1 && (*itInimigo)->getPosition().x < _jogador2->getPosition().x)))
					{
						_jogador2->atacarInimigo((*itInimigo));
					}
				}


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
				//for (int i = 0; i < (*itProjetil)->getDano(); i++)
					_jogador1->operator--((*itProjetil)->getDano());

				// Projetil desaparece
				(*itProjetil)->setLancar(false);
			}
			if (verificarColisao(static_cast<Entidades::Entidade*>(*itProjetil), static_cast<Entidades::Entidade*>(_jogador2))) {
				// Jogador toma dano
				//for (int i = 0; i < (*itProjetil)->getDano(); i++)
					_jogador2->operator--((*itProjetil)->getDano());

				// Projetil desaparece
				(*itProjetil)->setLancar(false);
			}
		}
	}
	// Caso 2: apenas um jogador foi criado
	else if (_jogador1 != nullptr)
	{
		for (itProjetil = _listaProjetil.begin(); itProjetil != _listaProjetil.end(); itProjetil++) {
			if (verificarColisao(static_cast<Entidades::Entidade*>(*itProjetil), static_cast<Entidades::Entidade*>(_jogador1))) {
				// Jogador toma dano
				//for (int i = 0; i < (*itProjetil)->getDano(); i++)
					_jogador1->operator--((*itProjetil)->getDano());

				// Projetil desaparece
				(*itProjetil)->setLancar(false);
				(*itProjetil)->setPosition(0.f, 0.f);
			}
		}
	}

}



void Gerenciadores::Gerenciador_Colisoes::tratarColisoesProjObstacs() {
	// Para cada projetil
	for (itProjetil = _listaProjetil.begin(); itProjetil != _listaProjetil.end(); itProjetil++) {
		// Se existir
		if ((*itProjetil) != nullptr)
			// Para cada obstaculo
			for (itObstaculo = _listaObstaculos.begin(); itObstaculo != _listaObstaculos.end(); ++itObstaculo) {
				// Se colidiram
				if (verificarColisao(*itProjetil, *itObstaculo)) {
					// Projetil desaparece
					(*itProjetil)->setLancar(false);
					(*itProjetil)->setPosition(0.f, 0.f);
				}
			}
	}
}

void Gerenciadores::Gerenciador_Colisoes::tratarColisoesTela() {
	// ------- >> Por qualquer lado

	// Para cada projetil
	for (itProjetil = _listaProjetil.begin(); itProjetil != _listaProjetil.end(); itProjetil++) {
		if (!(*itProjetil)->estaDentroDaJanela()) {
			(*itProjetil)->resetar();
		}
	}


	// ------- >> Pelos lados

	// Para cada inimigo
	for (itInimigo = _listaInimigos.begin(); itInimigo != _listaInimigos.end() && (*itInimigo)->getVivo(); itInimigo++) {
		// Lado esquerdo
		if ((*itInimigo)->getPosition().x < 0.f) 
		{
			(*itInimigo)->setSpeed((*itInimigo)->getSpeedX() * -1.f, (*itInimigo)->getSpeedY());
			//(*itInimigo)->setPosition(50.f, (*itInimigo)->getPosition().y);
		}

		// Lado direito
		else if
			(
				(*itInimigo)->getPosition().x + (*itInimigo)->getBody().getGlobalBounds().width
				>= (*itInimigo)->getGrafico()->getWindow()->getSize().x
				)
		{
			(*itInimigo)->setSpeed((*itInimigo)->getSpeedX() * -1.f, (*itInimigo)->getSpeedY());
			//(*itInimigo)->setPosition(10.f, (*itInimigo)->getPosition().y);
		}
	}

	// Para cada jogador

	if (_jogador1 != nullptr) {
		// Lado esquerdo
		if (_jogador1->getPositionX() <= 0.f) 
		{
			_jogador1->setSpeed(0.f, _jogador1->getSpeedY());
			_jogador1->setPositionX(0.f);
		}

		// Lado direito
		else if
			(
				_jogador1->getPositionX() + _jogador1->getBody().getGlobalBounds().width
				>= _jogador1->getGrafico()->getWindow()->getSize().x
				)
		{
			_jogador1->setSpeed(0.f, _jogador1->getSpeedY());
			_jogador1->setPositionX(_jogador1->getGrafico()->getWindow()->getSize().x - _jogador1->getBody().getGlobalBounds().width);
		}
	}
	if (_jogador2 != nullptr) {
		// Lado esquerdo
		if (_jogador2->getPositionX() <= 0.f) 
		{
			_jogador2->setSpeed(0.f, _jogador2->getSpeedY());
			_jogador2->setPositionX(0.f);
		}

		// Lado direito
		else if
			(
				_jogador2->getPositionX() + _jogador2->getBody().getGlobalBounds().width
				>= _jogador2->getGrafico()->getWindow()->getSize().x
				)
		{
			_jogador2->setSpeed(0.f, _jogador2->getSpeedY());
			_jogador2->setPositionX(_jogador2->getGrafico()->getWindow()->getSize().x - _jogador2->getBody().getGlobalBounds().width);
		}
	}


	// ------- >> Por baixo

	// Para cada inimigo
	for (itInimigo = _listaInimigos.begin(); itInimigo != _listaInimigos.end() && (*itInimigo)->getVivo(); itInimigo++) 
	{
		if ((*itInimigo)->getPositionY() + (*itInimigo)->getBody().getGlobalBounds().height >=
			(*itInimigo)->getGrafico()->getWindow()->getSize().y)
		{
			(*itInimigo)->setVivo(false);
			(*itInimigo)->setVidas(-1);
		}
	}

	// Para cada jogador
	if (_jogador1 != nullptr) 
	{
		if
			(
				_jogador1->getPositionY() + _jogador1->getBody().getGlobalBounds().height
				>= _jogador1->getGrafico()->getWindow()->getSize().y
				)
		{
			_jogador1->setVivo(false);
			_jogador1->setVidas(-1);
		}
	}
	if (_jogador2 != nullptr) 
	{
		if
			(
				_jogador2->getPositionY() + _jogador2->getBody().getGlobalBounds().height
				>= _jogador2->getGrafico()->getWindow()->getSize().y
				)
		{
			_jogador2->setVivo(false);
			_jogador2->setVidas(-1);
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
	for (itInimigo = _listaInimigos.begin(); itInimigo != _listaInimigos.end(); ++itInimigo)
	{
		if (*itInimigo)
		{
			(*itInimigo)->sofrerGravidade(_gravidade);
		}
	}
	for (itObstaculo = _listaObstaculos.begin(); itObstaculo != _listaObstaculos.end(); ++itObstaculo)
	{
		if (*itObstaculo)
		{
			(*itObstaculo)->sofrerGravidade(_gravidade);
		}
	}

	for (itProjetil = _listaProjetil.begin(); itProjetil != _listaProjetil.end(); ++itProjetil)
	{
		if (*itProjetil)
		{
			(*itProjetil)->sofrerGravidade(_gravidade);
		}
	}

	if (_jogador1)
	{
		_jogador1->sofrerGravidade(_gravidade);
	}

	if (_jogador2)
	{
		_jogador2->sofrerGravidade(_gravidade);
	}
}

void Gerenciadores::Gerenciador_Colisoes::executar()
{
	
	tratarColisoesJogsObstacs();
	tratarColisoesJogsProjeteis();
	tratarColisoesJogsInimgs();
	tratarColisoesProjObstacs();
	tratarColisoesTela();
	aplicarGravidade();
}

void Gerenciadores::Gerenciador_Colisoes::resetar()
{
	_listaInimigos.clear();
	_listaObstaculos.clear();
	_listaProjetil.clear();

	_jogador1 = nullptr;
	_jogador2 = nullptr;
}
