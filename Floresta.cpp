#include "Jogo.h"
#include "Floresta.h"
#include <iostream>
#include <vector>
#include <utility>
#include "BruxaThread.h"
#include "Constantes.h"
#include "Factory.h"


Fases::Floresta::Floresta(Gerenciadores::Gerenciador_Grafico* pgra, Entidades::Jogador* jog1, Entidades::Jogador* jog2)

    :Fase(pgra,jog1,jog2),maxBruxas(Constantes::MAX_BRUXAS),maxBarraMagicas(Constantes::MAX_BARRAS_MAGICAS)

{

    //_Lista->insert_back(static_cast<Entidades::Entidade*>(_jog));
    //_GC->setJogador1(jog);
    criarCenario();
   
}

Fases::Floresta::~Floresta()
{
    if (_Lista)
    {
        _Lista->joinThread();
        delete _Lista;
        _Lista = nullptr;
    }
    
    //Seto como nulo os ponteiros para o Gerenciador gráfico e jogador
   // _GG = nullptr;
    if (_pTexture)
    {
        delete _pTexture;
        _pTexture = nullptr;
    }
    _jog1 = nullptr;
    _jog2 = nullptr;
}

void Fases::Floresta::criaBarrasMagicas()
{
    // Determinar o número de barras mágicas a serem criadas: entre 1 e 3

    int n = rand() % 4 + 1;

    // Posições centrais das plataformas 2, 4 e 6 (caso a plataforma 6 exista)
    std::vector<std::pair<float, float>> posBarras =
    {

        {468+234 , 630.f},                               // Meio da plataforma 2
        {234,450.f},                                    // Meio da plataforma 4
        {_GG->getWindow()->getSize().x - 200, 450.f},  // Meio da plataforma 3 
        {936.f, 450}
    };

    for (int i = 0; i < n; i++)
    {
        float x = posBarras[i].first;
        float y = posBarras[i].second;


        //Entidades::BarraMagica* bar = new Entidades::BarraMagica(x, y, _GG);
        Entidades::BarraMagica* bar = static_cast<Entidades::BarraMagica*>
            (
                Entidades::EntidadeFactory::criarEntidade(x, y, _GG, Constantes::TIPO_BARRA_MAGICA)
                );

        _GC->incluirObstaculo(static_cast<Entidades::Obstaculo*>(bar));
        _Lista->insert_back(static_cast<Entidades::Entidade*>(bar));
    }
}


void Fases::Floresta::criaBruxas()
{

    int n = rand() % 5 + 1;
    int i;
    
    std::vector<std::pair<float, float>> posicaoBruxa =
    {
        {_GG->getWindow()->getSize().x -200, 430.f},
        {_GG->getWindow()->getSize().x - 200, 700.f},
        {450.f,400.f},
        {0.f, 700.f},									
        {468.f, 700.f},

    };

    for (i = 0; i < n; i++)
    {
        float x = posicaoBruxa[i].first;
        float y = posicaoBruxa[i].second;
        if (i < 2)
        {
            //Entidades::BruxaThread* bru = new Entidades::BruxaThread(x, y, _GG, _jog1, _jog2);
            Entidades::BruxaThread* bru = static_cast<Entidades::BruxaThread*>
                (
                    Entidades::EntidadeFactory::criarEntidade(x, y, _GG, _jog1, _jog2, Constantes::TIPO_BRUXA_THREAD)
                    );

            _GC->incluirInimigo(static_cast<Entidades::Inimigo*>(bru));
            _Lista->insert_back(static_cast<Entidades::Entidade*>(bru));
        }
        else
        {
            //Entidades::Bruxa* bru = new Entidades::Bruxa(x, y, _GG, _jog1, _jog2);
            Entidades::Bruxa* bru = static_cast<Entidades::Bruxa*>
                (
                    Entidades::EntidadeFactory::criarEntidade(x, y, _GG, _jog1, _jog2, Constantes::TIPO_BRUXA)
                    );
            _GC->incluirInimigo(static_cast<Entidades::Inimigo*>(bru));
            _Lista->insert_back(static_cast<Entidades::Entidade*>(bru));
        }
            
    }
}

void Fases::Floresta::executar()
{
    
    _Lista->startThread();
    while (!_mudouEstado) 
    {
        sf::Event event;
        while (_GG->getWindow()->pollEvent(event)) 
        {
            // Volta para o menu
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) 
            {
                Jogo::mudarStateNum(10);
                _mudouEstado = true;
                
            }
        }

        _GG->clear();
        desenhar();
        _GC->executar();

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

        verificarJogadores();

        //std::cout << _jog1->getPontos() << std::endl;
        _GG->display();
    }
    _Lista->joinThread();
    
}

void Fases::Floresta::criarInimigos()
{
    criaBruxas();
    criarCavaleiros();
}

void Fases::Floresta::criarObstaculos()
{
    criarPlataformas();
    criaBarrasMagicas();

}

void Fases::Floresta::criarCenario()
{
    _pTexture = new sf::Texture();
    _pTexture = _pGraf->getTextura("Fundo_Floresta");
    /*
    if (!_pTexture->loadFromFile("assets/FundoFlorest.png")) 
    {
        std::cerr << "Erro ao criar o background da fase Floresta.\n";
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

