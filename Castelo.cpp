#include "Castelo.h"
#include "Jogo.h"
#include "Constantes.h"
#include "MortoVivoThread.h"

Fases::Castelo::Castelo(Gerenciadores::Gerenciador_Grafico* pgra, Entidades::Jogador* j1, Entidades::Jogador* j2,Jogo* jog)
	: Fase(pgra, j1, j2, jog), _maxMagos(Constantes::MAX_MAGOS), _maxEspinhos(0), _platsCavaleiros(), _platsBosses(), 
	_platsBases(), _cavaleiros(), _magos(),_magosNaoCriados(true)
{
	setTipoFase(2);

	// Apenas por seguranca. Limpa os vetores
	_platsBases.clear();
	_platsCavaleiros.clear();
	_platsBosses.clear();
	_cavaleiros.clear();
	_magos.clear();

	// Recupera a jogada se estiver salva
	// Se não cria do zero

	int recuperar;
	std::ifstream Arquivo;
	Arquivo.open("Salvamento.txt", std::ios::in);
	Arquivo >> recuperar;
	Arquivo.close();
	if (recuperar)
	{
		criarCenario();
		recuperarFase();
	}
	else
	{
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
	
}

Fases::Castelo::~Castelo()
{
	_platsBases.clear();
	_platsCavaleiros.clear();
	_platsBosses.clear();
	_cavaleiros.clear();
	_magos.clear();

	if (_pTexture)
	{
		delete _pTexture;
		_pTexture = nullptr;
	}

	_jog1 = nullptr;
	_jog2 = nullptr;
}

// Cria o background da fase
void Fases::Castelo::criarCenario()
{
	_pTexture = new sf::Texture();
	_pTexture = _pGraf->getTextura("Fundo_Castelo");
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

	// insere as plataformas em suas defidas posicoes
	for (int i = 0; i < numPlatBase; i++) {
		plat = new Entidades::Plataforma(x, y, _pGraf, 0.f);
		_platsBases.push_back(plat);

		_GC->incluirObstaculo(static_cast<Entidades::Obstaculo*>(plat));
		_Lista->insert_back(static_cast<Entidades::Entidade*>(plat));

		x += (float)platDi.x;
	}

	// ------ >> Cria as plataformas dos chefes

	y = (float)_pGraf->getWindow()->getSize().y - (float)platDi.y - (float)platDi.y * 3.f;
	x = (float)_pGraf->getWindow()->getSize().x - 100.f; // 100 seria o tamanho visivel da plataforma

	// insere as plataformas em suas defidas posicoes
	for (int i = 0; i < 3; i++) {
		plat = new Entidades::Plataforma(x, y, _pGraf, 0.f);
		_platsBosses.push_back(plat);

		_GC->incluirObstaculo(static_cast<Entidades::Obstaculo*>(plat));
		_Lista->insert_back(static_cast<Entidades::Entidade*>(plat));

		y -= (float)platDi.y * 3.f;
	}

	// ------ >> Cria as plataformas dos cavaleiros

	y = (float)_pGraf->getWindow()->getSize().y - (float)platDi.y - (float)platDi.y * 3.f;
	x = 120.f - (float)platDi.x; // 100 seria o tamanho visivel da plataforma

	// insere as plataformas em suas defidas posicoes
	for (int i = 0; i < 3 + adicionalPlat; i++) {
		plat = new Entidades::Plataforma(x, y, _pGraf, 0.f);
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

	// insere os espinhos em suas defidas posicoes
	size_t tam = _platsBosses.size();
	for (size_t i = 0; i < tam; i++) {
		y = _platsBosses[i]->getPosition().y - dimEspinho.y;

		espinho = new Entidades::Espinho(1, x, y, _pGraf);

		_GC->incluirObstaculo(static_cast<Entidades::Obstaculo*>(espinho));
		_Lista->insert_back(static_cast<Entidades::Entidade*>(espinho));
	}

	// ------ >> Cria os espinhos nas plataformas da base

	x = 0.f;
	y = _platsBases[0]->getPositionY() - dimEspinho.y;

	espinho = new Entidades::Espinho(1, x, y, _pGraf);

	_GC->incluirObstaculo(static_cast<Entidades::Obstaculo*>(espinho));
	_Lista->insert_back(static_cast<Entidades::Entidade*>(espinho));

	x = _pGraf->getWindow()->getSize().x - dimEspinho.x;

	espinho = new Entidades::Espinho(1, x, y, _pGraf);

	_GC->incluirObstaculo(static_cast<Entidades::Obstaculo*>(espinho));
	_Lista->insert_back(static_cast<Entidades::Entidade*>(espinho));

	// ------ >> Cria os espinhos nas plataformas dos cavaleiros

	x = 0.f,
	y = 0.f;

	espinho = nullptr;

	// insere os espinhos em suas defidas posicoes
	for (int i = 0; i < adicionalEspinhos; i++) {
		y = _platsCavaleiros[i]->getPosition().y - dimEspinho.y;

		espinho = new Entidades::Espinho(1, x, y, _pGraf);

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
		x = _platsCavaleiros[0]->getPosition().x + _platsCavaleiros[0]->getBody().getGlobalBounds().width - dimCavaleiro.x - 20.f,
		y = 0.f;

	Entidades::Cavaleiro* cavaleiro = nullptr;

	// insere os cavaleiros em suas defidas posicoes
	for (int i = 0; i < minCavaleiros + adicionalCavaleiros; i++) {
		y = _platsCavaleiros[i]->getPosition().y - dimCavaleiro.y;

		cavaleiro = new Entidades::Cavaleiro(x, y, _pGraf, _jog1);

		_GC->incluirInimigo(static_cast<Entidades::Inimigo*>(cavaleiro));
		_Lista->insert_back(static_cast<Entidades::Entidade*>(cavaleiro));

		_cavaleiros.push_back(cavaleiro);

		x += 10.f;
	}
}

void Fases::Castelo::criarMagos()
{
	Entidades::Mago* mago          = nullptr;
	Entidades::Projetil* projetil  = nullptr;
	int n = (rand() % 3) + 3;
	float x, y;
	x = _pGraf->getWindow()->getSize().x - 40.f;
	y = _pGraf->getWindow()->getSize().y - 768.f - 57.f;

	// Gerados nas plataformas laterais

	// insere os magos em suas defidas posicoes
	for (int i = 0; i < n - 1; i++) 
	{
		mago = new Entidades::Mago(x, y, _pGraf, _jog1,_jog2);
		projetil = new Entidades::Projetil(0.f, 0.f, _pGraf);

		mago->setProjetil(projetil);

		_GC->incluirInimigo(static_cast<Entidades::Inimigo*>(mago));
		_Lista->insert_back(static_cast<Entidades::Entidade*>(mago));

		_GC->incluirProjetil(projetil);
		_Lista->insert_back(static_cast<Entidades::Entidade*>(projetil));

		_magos.push_back(mago);
		y += 192.f;
		x -= 10.f;
	}

	// Gerado na plataforma da base 

	x = _pGraf->getWindow()->getSize().x - (_pGraf->getWindow()->getSize().x / 10.f * 2.f);
	y = _pGraf->getWindow()->getSize().y - 192.f - 57.f;

	mago = new Entidades::Mago(x, y, _pGraf, _jog1, _jog2);
	projetil = new Entidades::Projetil(0.f, 0.f, _pGraf);

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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) 
			{
				pause();
			}
		}

		_GG->clear();

		_GC->executar();

		desenhar();
		
		executarJogadores();
		
		_Lista->executar();

		verificarCavaleiros();
		verificarJogadores();
		verificaInimigosVivos();

		_GG->display();
	}
}

void Fases::Castelo::verificarCavaleiros()
{
	int vivos = 0;

	// Contabiliza quantos cavaleiros estao vivos
	size_t tam = _cavaleiros.size();
	for (size_t i = 0; i < tam; i++)
		if(_cavaleiros[i])
			vivos += (int)_cavaleiros[i]->getVivo();
	

	if (!vivos && _magosNaoCriados)
	{
		criarMagos();
		_magosNaoCriados = false;
	}
}

// Recria as instancias, recuperando todas as informacoes pertinentes e reinserindo-as em suas construtoras
void Fases::Castelo::recuperarFase()
{
	int flagJogador1 = 1;
	std::ifstream arquivoFase("Salvamento.txt", std::ios::in);
	std::vector<Entidades::Mago*> magos;
	int ma = 0;

	if (!arquivoFase)
	{
		std::cerr << "Erro: Não foi possível abrir o arquivo de salvamento." << std::endl;
		return;
	}


	int recupera, terminado;

	if (!(arquivoFase >> recupera >> terminado))
	{
		std::cerr << "Erro: Arquivo de salvamento corrompido ou vazio." << std::endl;
		return;
	}

	int _Tipo;
	bool _ehThread, _onGround;
	float posX, posY, speedX, speedY;
	while (arquivoFase >> _Tipo >> _ehThread >> _onGround >> posX >> posY >> speedX >> speedY)
	{
		if (_Tipo == Constantes::TIPO_JOGADOR)
		{
			int vidas, direcao;
			std::string nome = " ";

			if (!(arquivoFase >> vidas >> direcao >> nome))
			{
				std::cerr << "Erro ao ler dados do Jogador." << std::endl;
				continue;
			}

			Entidades::Jogador* jog = new Entidades::Jogador(posX, posY, _GG, nome);
			jog->setDirecao(direcao);
			jog->setVidas(vidas);
			jog->setGround(_onGround);

			if (flagJogador1)
			{
				_jog1 = jog;
				_GC->setJogador1(jog);
				_jogo->setJogador1(_jog1);
				Ranking* rank = _jogo->getRanking();
				rank->verificaPontos(jog);
				_hudJog1 = new Hud(_jog1);
				flagJogador1 = 0;
			}
			else
			{
				_jog2 = jog;
				_GC->setJogador2(_jog2);
				_jogo->setJogador2(jog);
				Ranking* rank = _jogo->getRanking();
				rank->verificaPontos(jog);
				_hudJog2 = new Hud(jog);
			}
		}
		else if (_Tipo == Constantes::TIPO_CAVALEIRO)
		{
			int vidas, direcao, louc;
			float inX, inY;

			if (!(arquivoFase >> vidas >> direcao >> inX >> inY >> louc))
			{
				std::cerr << "Erro ao ler dados do Cavaleiro." << std::endl;
				continue;
			}

			Entidades::Cavaleiro* cav = new Entidades::Cavaleiro(posX, posY, _GG, _jog1, _jog2, vidas);
			cav->setDirecao(direcao);
			cav->setGround(_onGround);
			cav->setSpeed(speedX, speedY);
			cav->setLoucura(louc);
			cav->setPosInicial(inX, inY);
			_cavaleiros.push_back(cav);

			_Lista->insert_back(static_cast<Entidades::Entidade*>(cav));
			_GC->incluirInimigo(static_cast<Entidades::Inimigo*>(cav));
		}
		else if (_Tipo == Constantes::TIPO_MORTOVIVO)
		{
			int vidas, direcao, energ;
			float inX, inY;
			if (!(arquivoFase >> vidas >> direcao >> inX >> inY >> energ))
			{
				std::cerr << "Erro ao ler dados do MortoVivo" << std::endl;
				continue;
			}

			Entidades::MortoVivo* mort = new Entidades::MortoVivo(posX, posY, _GG, _jog1, _jog2, vidas);
			mort->setDirecao(direcao);
			mort->setGround(_onGround);
			mort->setSpeed(speedX, speedY);
			mort->setEnergetico(energ);
			mort->setPosInicial(inX, inY);

			_Lista->insert_back(static_cast<Entidades::Entidade*>(mort));
			_GC->incluirInimigo(static_cast<Entidades::Inimigo*>(mort));


		}
		else if (_Tipo == Constantes::TIPO_MORTOVIVO_THREAD)
		{
			int vidas, direcao, energ;
			float inX, inY;
			if (!(arquivoFase >> vidas >> direcao >> inX >> inY >> energ))
			{
				std::cerr << "Erro ao ler dados do MortoVivoThread" << std::endl;
				continue;
			}

			Entidades::MortoVivoThread* mort = new Entidades::MortoVivoThread(posX, posY, _GG, _jog1, _jog2, vidas);
			mort->setDirecao(direcao);
			mort->setGround(_onGround);
			mort->setSpeed(speedX, speedY);
			mort->setEnergetico(energ);
			mort->setPosInicial(inX, inY);

			_GC->incluirInimigo(static_cast<Entidades::Inimigo*>(mort));
			_Lista->insert_back(static_cast<Entidades::Entidade*>(mort));


		}
		else if (_Tipo == Constantes::TIPO_MAGO)
		{
			int vidas, direcao, vidasPerdidas;
			float secs ,inX, inY;
			if (!(arquivoFase >> vidas >> direcao >> inX >> inY >> secs >> vidasPerdidas))
			{
				std::cerr << "Erro ao ler dados do Mago" << std::endl;
				continue;
			}
			Entidades::Mago* mag = new Entidades::Mago(posX, posY, _GG, _jog1, _jog2, vidas);
			mag->setDirecao(direcao);
			mag->setGround(_onGround);
			mag->setSpeed(speedX, speedY);
			mag->setPosInicial(inX, inY);
			mag->setVidasPerdidas(vidasPerdidas);
			mag->setSegIntervalo(secs);

			_Lista->insert_back(static_cast<Entidades::Entidade*>(mag));
			_GC->incluirInimigo(static_cast<Entidades::Inimigo*>(mag));
			magos.push_back(mag);
			_magos.push_back(mag);
			_magosNaoCriados = false;
		}
		else if (_Tipo == Constantes::TIPO_PLATAFORMA)
		{
			bool danoso;
			if (!(arquivoFase >> danoso))
			{
				std::cerr << "Erro ao ler dados de Plataforma" << std::endl;
				continue;
			}
			Entidades::Plataforma* plat = new Entidades::Plataforma(posX, posY, _GG);
			_Lista->insert_back(static_cast<Entidades::Entidade*>(plat));
			_GC->incluirObstaculo(static_cast<Entidades::Obstaculo*>(plat));
		}
		else if (_Tipo == Constantes::TIPO_BARRA_MAGICA)
		{
			float duracaoParalisia;
			bool danoso;
			if (!(arquivoFase >> danoso >> duracaoParalisia))
			{
				std::cerr << "Erro ao ler dados de BarraMagica" << std::endl;
				continue;
			}
			Entidades::BarraMagica* bar = new Entidades::BarraMagica(posX, posY, _GG);
			_Lista->insert_back(static_cast<Entidades::Entidade*>(bar));
			_GC->incluirObstaculo(static_cast<Entidades::Obstaculo*>(bar));
		}
		else if (_Tipo == Constantes::TIPO_ESPINHO)
		{
			int dano;
			bool danoso;
			if (!(arquivoFase >> danoso >> dano))
			{
				std::cerr << "Erro ao ler dados de Espinho" << std::endl;
				continue;
			}
			Entidades::Espinho* esp = new Entidades::Espinho(dano, posX, posY, _GG);
			esp->setDanoso(danoso);
			_Lista->insert_back(static_cast<Entidades::Entidade*>(esp));
			_GC->incluirObstaculo(static_cast<Entidades::Obstaculo*>(esp));

		}
		else if (_Tipo == Constantes::TIPO_PROJETIL)
		{
			int dano;
			bool lancar;

			if (!(arquivoFase >> dano >> lancar))
			{
				std::cerr << "Erro ao ler dados de Projetil" << std::endl;
				continue;
			}
			Entidades::Projetil* proj = new Entidades::Projetil(posX, posY, _GG);
			if (ma >= magos.size())
			{
				std::cerr << "Erro: Índice 'ma' fora dos limites do vetor magos." << std::endl;
				break;
			}
			else
			{
				// Define o projetil para o mago correspondente
				magos[ma]->setProjetil(proj);
				ma++;
			}
			_Lista->insert_back(static_cast<Entidades::Entidade*>(proj));
			_GC->incluirProjetil(static_cast<Entidades::Projetil*>(proj));
			proj->setDano(dano);
			proj->setLancar(lancar);
			proj->setSpeed(speedX, speedY);



		}
		else
		{
			std::cerr << "Erro: Tipo de entidade desconhecido (" << _Tipo << ")." << std::endl;
			continue;
		}
	}

	arquivoFase.close();

	LimpaArquivo();
}
