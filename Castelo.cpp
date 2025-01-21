#include "Castelo.h"
#include "Jogo.h"
#include "Constantes.h"
#include "Factory.h"

Fases::Castelo::Castelo(Gerenciadores::Gerenciador_Grafico* pgra, Entidades::Jogador* j1, Entidades::Jogador* j2)
	: Fase(pgra, j1,j2), _maxMagos(Constantes::MAX_MAGOS), _maxEspinhos(0), _platsCavaleiros(), _platsBosses(), 
	_platsBases(), _cavaleiros(), _magos(),_magosNaoCriados(true)
{
	_platsBases.clear();
	_platsCavaleiros.clear();
	_platsBosses.clear();
	_cavaleiros.clear();
	_magos.clear();

	//_GC->setJogador1(j);

	criarCenario();
	criarObstaculos();
	criarInimigos();

	if (_jog1)
	{
		_jog1->setPosition
		(
			_pGraf->getWindow()->getSize().x / 10.f,
			_platsBases[0]->getPosition().y - _jog1->getBody().getGlobalBounds().height
		);
	}
	if (_jog2)
	{
		_jog2->setPosition
		(
			_pGraf->getWindow()->getSize().x / 9.f,
			_platsBases[0]->getPosition().y - _jog2->getBody().getGlobalBounds().height
		);
	}
	
}

Fases::Castelo::~Castelo()
{
	_platsBases.clear();
	_platsCavaleiros.clear();
	_platsBosses.clear();
	_cavaleiros.clear();
	_magos.clear();
}

void Fases::Castelo::criarCenario()
{
	_pTexture = new sf::Texture();
	_pTexture = _pGraf->getTextura("Fundo_Castelo");
	/*
	if (!_pTexture->loadFromFile("assets/Fase castelo/background.jpg")) {
		std::cerr << "Erro ao criar o background da fase 2.\n";
		return;
	}
	*/
	_body.setTexture(*_pTexture);

	// redimensiona de acordo com o tamanho da janela
	sf::Vector2u tamJanela = _pGraf->getWindow()->getSize();
	float escalaX = (float)tamJanela.x / _body.getGlobalBounds().width;
	float escalaY = (float)tamJanela.y / _body.getGlobalBounds().height;

	_body.setScale
	(
		escalaX,
		escalaY
	);

	_body.setPosition(0.f, 0.f);
}

void Fases::Castelo::criarObstaculos()
{
	criarPlataformas();
	criarEspinhos();
}

void Fases::Castelo::criarPlataformas()
{
	// DIMENSOES DA PLATAFORMA
	sf::Vector2i platDi(468, 64);

	// Determina o numero de plataformas que atravessam a tela
	int numPlatBase = (_pGraf->getWindow()->getSize().x / platDi.x) + 1;
	int minPlataformas = numPlatBase;
	// Determina o numero de plataforams que vao ser a base dos bosses (3) e dos cavaleiros (3 no minimo)
	minPlataformas += 6;

	// Determina o numero adicional de plataformas
	int adicionalPlat = (_pGraf->getWindow()->getSize().y / (int)(platDi.y * 3.f)) - 4;
	// o 4 eh o numero minimo ja incluido

	if (adicionalPlat < 0) adicionalPlat = 0;

	maxPlataformas = minPlataformas + adicionalPlat;

	adicionalPlat = rand() % (adicionalPlat + 1);


	// Cria as plataformas da base

	float y = _pGraf->getWindow()->getSize().y - (float)platDi.y;
	float x = 0.f;

	Entidades::Plataforma* plat = nullptr;

	for (int i = 0; i < numPlatBase; i++) {
		//plat = new Entidades::Plataforma(x, y, _pGraf, 0.f);

		Entidades::Plataforma* plat = static_cast<Entidades::Plataforma*>
			(
				Entidades::EntidadeFactory::criarEntidade(x, y, _pGraf,Constantes::TIPO_PLATAFORMA)
				);

		_platsBases.push_back(plat);

		_GC->incluirObstaculo(static_cast<Entidades::Obstaculo*>(plat));
		_Lista->insert_back(static_cast<Entidades::Entidade*>(plat));

		x += (float)platDi.x;
	}

	// ------ >> Cria as plataformas dos chefes

	y = (float)_pGraf->getWindow()->getSize().y - (float)platDi.y - (float)platDi.y * 3.f;
	x = (float)_pGraf->getWindow()->getSize().x - 100.f; // 100 seria o tamanho visivel da plataforma

	for (int i = 0; i < 3; i++) {
		//plat = new Entidades::Plataforma(x, y, _pGraf, 0.f);
		Entidades::Plataforma* plat = static_cast<Entidades::Plataforma*>
			(
				Entidades::EntidadeFactory::criarEntidade(x, y, _pGraf, Constantes::TIPO_PLATAFORMA)
				);

		_platsBosses.push_back(plat);

		_GC->incluirObstaculo(static_cast<Entidades::Obstaculo*>(plat));
		_Lista->insert_back(static_cast<Entidades::Entidade*>(plat));

		y -= (float)platDi.y * 3.f;
	}

	// ------ >> Cria as plataformas dos cavaleiros

	y = (float)_pGraf->getWindow()->getSize().y - (float)platDi.y - (float)platDi.y * 3.f;
	x = 100.f - (float)platDi.x; // 100 seria o tamanho visivel da plataforma

	for (int i = 0; i < 3 + adicionalPlat; i++) {
		//plat = new Entidades::Plataforma(x, y, _pGraf, 0.f);
		Entidades::Plataforma* plat = static_cast<Entidades::Plataforma*>
			(
				Entidades::EntidadeFactory::criarEntidade(x, y, _pGraf, Constantes::TIPO_PLATAFORMA)
				);

		_platsCavaleiros.push_back(plat);

		_GC->incluirObstaculo(static_cast<Entidades::Obstaculo*>(plat));
		_Lista->insert_back(static_cast<Entidades::Entidade*>(plat));

		y -= (float)platDi.y * 3.f;
	}
}

void Fases::Castelo::criarEspinhos()
{
	_maxEspinhos = (int)_platsCavaleiros.size() + (int)_platsBosses.size() + 2;
	int minEspinhos = (int)_platsBosses.size() + 2;
	// o 2 faz parte das plataformas da base

	int adicionalEspinhos = rand() % (_maxEspinhos - minEspinhos + 1);

	sf::Vector2f dimEspinho(50.f, 15.f);

	// ------ >> Cria os espinhos nas plataformas dos bosses

	float
		x = _pGraf->getWindow()->getSize().x - dimEspinho.x,
		y = 0.f;

	Entidades::Espinho* espinho = nullptr;

	size_t tam = _platsBosses.size();
	for (size_t i = 0; i < tam; i++) {
		y = _platsBosses[i]->getPosition().y - dimEspinho.y;

		//espinho = new Entidades::Espinho(1, x, y, _pGraf);
		espinho = static_cast<Entidades::Espinho*>
			(
				Entidades::EntidadeFactory::criarEntidade(x, y, _pGraf, Constantes::TIPO_ESPINHO)
				);

		_GC->incluirObstaculo(static_cast<Entidades::Obstaculo*>(espinho));
		_Lista->insert_back(static_cast<Entidades::Entidade*>(espinho));
	}

	// ------ >> Cria os espinhos nas plataformas da base

	x = 0.f;
	y = _platsBases[0]->getPositionY() - dimEspinho.y;

	//espinho = new Entidades::Espinho(1, x, y, _pGraf);
	espinho = static_cast<Entidades::Espinho*>
		(
			Entidades::EntidadeFactory::criarEntidade(x, y, _pGraf, Constantes::TIPO_ESPINHO)
			);

	_GC->incluirObstaculo(static_cast<Entidades::Obstaculo*>(espinho));
	_Lista->insert_back(static_cast<Entidades::Entidade*>(espinho));

	x = _pGraf->getWindow()->getSize().x - dimEspinho.x;

	//espinho = new Entidades::Espinho(1, x, y, _pGraf);
	espinho = static_cast<Entidades::Espinho*>
		(
			Entidades::EntidadeFactory::criarEntidade(x, y, _pGraf, Constantes::TIPO_ESPINHO)
			);

	_GC->incluirObstaculo(static_cast<Entidades::Obstaculo*>(espinho));
	_Lista->insert_back(static_cast<Entidades::Entidade*>(espinho));

	// ------ >> Cria os espinhos nas plataformas dos cavaleiros

	x = 0.f,
	y = 0.f;

	espinho = nullptr;

	for (int i = 0; i < adicionalEspinhos; i++) {
		y = _platsCavaleiros[i]->getPosition().y - dimEspinho.y;

		//espinho = new Entidades::Espinho(1, x, y, _pGraf);
		espinho = static_cast<Entidades::Espinho*>
			(
				Entidades::EntidadeFactory::criarEntidade(x, y, _pGraf, Constantes::TIPO_ESPINHO)
				);

		_GC->incluirObstaculo(static_cast<Entidades::Obstaculo*>(espinho));
		_Lista->insert_back(static_cast<Entidades::Entidade*>(espinho));
	}
}

void Fases::Castelo::criarInimigos()
{
	criarCavaleiros();
}

void Fases::Castelo::criarCavaleiros()
{
	maxCavaleiros = (int)_platsCavaleiros.size();
	int minCavaleiros = 3;

	int adicionalCavaleiros = rand() % (maxCavaleiros - minCavaleiros + 1);

	sf::Vector2f dimCavaleiro(38.f, 63.f);

	// ------ >> Cria os cavaleiros nas plataformas

	float
		x = _platsCavaleiros[0]->getPosition().x + _platsCavaleiros[0]->getBody().getGlobalBounds().width - dimCavaleiro.x,
		y = 0.f;

	Entidades::Cavaleiro* cavaleiro = nullptr;

	for (int i = 0; i < minCavaleiros + adicionalCavaleiros; i++) {
		y = _platsCavaleiros[i]->getPosition().y - dimCavaleiro.y;

		//cavaleiro = new Entidades::Cavaleiro(x, y, _pGraf, _jog1);
		Entidades::Cavaleiro* cavaleiro = static_cast<Entidades::Cavaleiro*>
			(
				Entidades::EntidadeFactory::criarEntidade(x, 700.0f, _GG, _jog1, _jog2, Constantes::TIPO_CAVALEIRO
				));

		_GC->incluirInimigo(static_cast<Entidades::Inimigo*>(cavaleiro));
		_Lista->insert_back(static_cast<Entidades::Entidade*>(cavaleiro));

		_cavaleiros.push_back(cavaleiro);
	}
}

void Fases::Castelo::criarMagos()
{
	int minMagos = 3;

	int adicionalMagos = rand() % (_maxMagos - minMagos + 1);

	sf::Vector2f dimMago(35.f, 57.f);

	// ------ >> Cria os bosses nas plataformas

	float
		x = _platsBosses[0]->getPosition().x,
		y = 0.f;

	Entidades::Mago* mago          = nullptr;
	Entidades::Projetil* projetil  = nullptr;

	for (int i = 0; i < minMagos; i++) {
		y = _platsCavaleiros[i]->getPosition().y - dimMago.y;

		//mago = new Entidades::Mago(x, y, _pGraf, _jog1,_jog2);
		//projetil = new Entidades::Projetil(0.f, 0.f, _pGraf);

		mago = static_cast<Entidades::Mago*>
			(
				Entidades::EntidadeFactory::criarEntidade(x, y, _pGraf, _jog1, _jog2, Constantes::TIPO_MAGO)
				);

		projetil  = static_cast<Entidades::Projetil*>
			(
				Entidades::EntidadeFactory::criarEntidade(0.f, 0.f, _pGraf, Constantes::TIPO_PROJETIL)
				);

		mago->setProjetil(projetil);

		_GC->incluirInimigo(static_cast<Entidades::Inimigo*>(mago));
		_Lista->insert_back(static_cast<Entidades::Entidade*>(mago));

		_GC->incluirProjetil(projetil);
		_Lista->insert_back(static_cast<Entidades::Entidade*>(projetil));

		_magos.push_back(mago);
	}

	// ------ >> Cria o boss extra na plataforma da base

	if (!adicionalMagos) return;

	x = (_pGraf->getWindow()->getSize().x * 9.f) / 10.f;
	y = _platsBases[0]->getPosition().y - dimMago.y;

	//mago = new Entidades::Mago(x, y, _pGraf, _jog1);
	//projetil = new Entidades::Projetil(0.f, 0.f, _pGraf);
	mago = static_cast<Entidades::Mago*>
		(
			Entidades::EntidadeFactory::criarEntidade(x, y, _pGraf, _jog1, _jog2, Constantes::TIPO_MAGO)
			);

	projetil = static_cast<Entidades::Projetil*>
		(
			Entidades::EntidadeFactory::criarEntidade(0.f, 0.f, _pGraf, Constantes::TIPO_PROJETIL)
			);

	mago->setProjetil(projetil);

	_GC->incluirInimigo(static_cast<Entidades::Inimigo*>(mago));
	_Lista->insert_back(static_cast<Entidades::Entidade*>(mago));

	_GC->incluirProjetil(projetil);
	_Lista->insert_back(static_cast<Entidades::Entidade*>(projetil));

	_magos.push_back(mago);
}

void Fases::Castelo::executar()
{
	while (!_mudouEstado) {
		sf::Event event;
		while (_GG->getWindow()->pollEvent(event)) {
			// Volta para o menu
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				Jogo::mudarStateNum(10);
				_mudouEstado = true;
			}
		}

		_GG->clear();

		_GC->executar();

		desenhar();
		
		if (_jog1) 
        {
            _jog1->executar();
            if (_hudJog1)
            {
                _hudJog1->executar();
                _hudJog1->setContador(_jog1->getVidas());
            }
           
        }
		if (_jog2)
		{
			_jog2->executar();
			if (_hudJog2)
			{
				_hudJog2->executar();
				_hudJog2->setContador(_jog2->getVidas());
			}
			
		}
		
		_Lista->executar();

		verificarCavaleiros();
		verificarMagos();
		verificarJogadores();

		_GG->display();
	}
}

void Fases::Castelo::verificarCavaleiros()
{
	int vivos = 0;

	// Contabiliza quantos cavaleiros estao vivos
	size_t tam = _cavaleiros.size();
	for (size_t i = 0; i < tam; i++)
		vivos += (int)_cavaleiros[i]->getVivo();
	
	if (!vivos && _magosNaoCriados)
	{
		criarMagos();
		_magosNaoCriados = false;
	}
}

void Fases::Castelo::verificarMagos()
{
	int vivos = 0;

	// Contabiliza quantos cavaleiros estao vivos
	size_t tam = _magos.size();
	for (size_t i = 0; i < tam; i++)
		vivos += (int)_magos[i]->getVivo();

	// Finaliza o jogo
	if (!vivos) {

	}
}
