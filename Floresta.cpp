#include "Jogo.h"
#include "Floresta.h"
#include <iostream>
#include <vector>
#include <utility>
#include "MortoVivoThread.h"
#include "Constantes.h"


Fases::Floresta::Floresta(Gerenciadores::Gerenciador_Grafico* pgra, Entidades::Jogador* jog1, Entidades::Jogador* jog2,Jogo*jog)

    : Fase(pgra,jog1,jog2,jog), maxMortovivo(Constantes::MAX_MORTOVIVO), maxBarraMagicas(Constantes::MAX_BARRAS_MAGICAS)

{
    setTipoFase(1);
    _inimigos.clear();

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
        criarInimigos();
        criarObstaculos();
    }
}

Fases::Floresta::~Floresta()
{
    if (_Lista)
    {
        _Lista->joinThread();
        delete _Lista;
        _Lista = nullptr;
    }
   
    if (_pTexture)
    {
        delete _pTexture;
        _pTexture = nullptr;
    }

    _jog1 = nullptr;
    _jog2 = nullptr;

    _inimigos.clear();
}

void Fases::Floresta::criaBarrasMagicas()
{
    // Determinar o número de barras mágicas a serem criadas: entre 1 e 3
    int n = (rand() % 3) + 3;

    // Posições centrais das plataformas 2, 4 e 6 (caso a plataforma 6 exista)
    std::vector<std::pair<float, float>> posBarras =
    {
        {468+234 , 640.f},                               // Meio da plataforma 2
        {234,460.f},                                    // Meio da plataforma 4
        {_GG->getWindow()->getSize().x - 200, 460.f},  // Meio da plataforma 3 
        {936.f, 460},
        {234,460}
    };

    // Insere as arras bagicas em suas devidas posicoes
    for (int i = 0; i < n; i++)
    {
        float x = posBarras[i].first;
        float y = posBarras[i].second;

        Entidades::BarraMagica* bar = new Entidades::BarraMagica(x, y, _GG);
        _GC->incluirObstaculo(static_cast<Entidades::Obstaculo*>(bar));
        _Lista->insert_back(static_cast<Entidades::Entidade*>(bar));
    }
}

void Fases::Floresta::criarCavaleiros()
{
    //Possibilidade de aleatorizar o y entre 700 e 150 rand()%(700-150)+150

    // (rand() % (max - min + 1)) + min
    int n = (rand() % 5) + 3; // Quantidade varia de 3 a 7

    float x = 310.f;           //Posicao inicial
    float anteriorX = x;

    int larguraJanela = _GG->getWindow()->getSize().x; // Largura da janela para testar se nao saiu depois

    // Insere os cavaleiros em suas devidas posicoes
    for (int i = 0; i < n; i++)
    {
        Entidades::Cavaleiro* cav = new Entidades::Cavaleiro(x, 700.0f, _GG, _jog1, _jog2); // Novo cav na posicao x
        _Lista->insert_back(static_cast<Entidades::Entidade*>(cav)); // inserir na lista
        _GC->incluirInimigo(static_cast<Entidades::Inimigo*>(cav)); // inserir no Gerenciador de colisoes

        float larguraCavaleiro = cav->getBody().getGlobalBounds().width; // tamanho do cavaleiro

        // Atualiza a coordenada x
        x = (float)((rand() % _GG->getWindow()->getSize().x) + 310.0f);

        // Caso a coordenada x seja igual a anterior, atualizamos o x
        while (x == anteriorX)
        {
            x = (float)((rand() % _GG->getWindow()->getSize().x) + 310.0f);
        }
        // testo se o tamanho do cavaleiro + 115 nao sai da janela
        while (x + 115 + larguraCavaleiro > larguraJanela) 
            x = (float)((rand() % _GG->getWindow()->getSize().x) + 310.0f);

        anteriorX = x;

        _inimigos.push_back(static_cast<Entidades::Inimigo*>(cav));
    }
}

void Fases::Floresta::criaBruxas()
{

    int n = (rand() % 4) + 3;
    int i;
    
    std::vector<std::pair<float, float>> posicaoBruxa =
    {
        {_GG->getWindow()->getSize().x -200, 430.f},
        {_GG->getWindow()->getSize().x - 200, 700.f},
        {450.f,400.f},
        {0.f, 700.f},									
        {468.f, 700.f},
        {234.f,700.f}
    };

    // Insere os mortos-vivos em suas devidas posicoes
    for (i = 0; i < n; i++)
    {
        float x = posicaoBruxa[i].first;
        float y = posicaoBruxa[i].second;
        if (i < 2)
        {

            Entidades::MortoVivoThread* morto = new Entidades::MortoVivoThread(x, y, _GG, _jog1, _jog2);
            _GC->incluirInimigo(static_cast<Entidades::Inimigo*>(morto));
            _Lista->insert_back(static_cast<Entidades::Entidade*>(morto));
        }
        else
        {
            Entidades::MortoVivo* morto = new Entidades::MortoVivo(x, y, _GG, _jog1, _jog2);
            _GC->incluirInimigo(static_cast<Entidades::Inimigo*>(morto));
            _Lista->insert_back(static_cast<Entidades::Entidade*>(morto));
       
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
            // Cria o menu de pause
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) 
            {
                pause();                
            }
        }

        _GG->clear();

        desenhar();
        _GC->executar();

        executarJogadores();

        _Lista->executar();

        verificarJogadores();
        verificaInimigosVivos();

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

// Cria somente a imagem do background
void Fases::Floresta::criarCenario()
{
    // Cria o background
    _pTexture = _pGraf->getTextura("Fundo_Floresta");
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

void Fases::Floresta::verificarInimigos()
{
    int vivos = 0;

    size_t tam = _inimigos.size();
    for (int i = 0; i < tam; i++)
        vivos += (int)_inimigos[i]->getVivo();

    // Muda para a fase Castelo
    if (!vivos) {
        Jogo::mudarStateNum(Constantes::STATE_FIM_JOGO);
        _mudouEstado = true;
    }
}