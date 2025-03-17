#include "Gerenciador_Grafico.h"
#include "Ente.h"

//Inicio o atributo statico como nullptr
Gerenciadores::Gerenciador_Grafico* Gerenciadores::Gerenciador_Grafico::instancia = nullptr;

Gerenciadores::Gerenciador_Grafico::Gerenciador_Grafico() :
    _mapPathsTextures(),arquivoLeitura()
{
    window = new sf::RenderWindow(sf::VideoMode(900, 600), "Jogo", sf::Style::Fullscreen);
    view = sf::View(sf::FloatRect(0, 0, 900, 600));
    criaMap();
    window->setMouseCursorVisible(true);
}

//Metodo do Singleton, se ja existir um gerenciador statico ele retorna o mesmo para manter 1, se nao ele instancia um novo
Gerenciadores::Gerenciador_Grafico* Gerenciadores::Gerenciador_Grafico::getInstancia() 
{
    if (instancia == nullptr) {
        instancia = new Gerenciador_Grafico();
    }
    return instancia;
}

Gerenciadores::Gerenciador_Grafico::~Gerenciador_Grafico()
{
    delete(window);
}

void Gerenciadores::Gerenciador_Grafico::desenhar(Entidades::Ente* pE)
{
    if (pE)
    {
        window->draw(pE->getBody());
    }
}

void Gerenciadores::Gerenciador_Grafico::desenhar(sf::Text* texto)
{
    if(texto)
    window->draw(*texto);
}

void Gerenciadores::Gerenciador_Grafico::desenhar(sf::Sprite* sprt)
{
    if (sprt)
    {
        window->draw(*sprt);
    }
}

void Gerenciadores::Gerenciador_Grafico::clear()
{
    window->clear();
}

void Gerenciadores::Gerenciador_Grafico::display() 
{
    window->display();
}

sf::RenderWindow* Gerenciadores::Gerenciador_Grafico::getWindow() const
{
    return window;
}

bool Gerenciadores::Gerenciador_Grafico::getOpen() const
{
    return window->isOpen();
}

void Gerenciadores::Gerenciador_Grafico::closeWindow()
{
    window->close();
}

// A partir do arquivo PathTexturas.txt, eh criado um map, o qual sera um facilitador ao criarmos texturas de diferentes classes
void Gerenciadores::Gerenciador_Grafico::criaMap()
{
    try
    {
        arquivoLeitura.open("PathTexturas.txt", std::ios::in);

        if (!arquivoLeitura.is_open())
        {
            throw std::runtime_error("Erro ao abrir o arquivo PathTexturas.txt.");
            
        }
       
        std::string path;
        std::string chave;

        // Ler linha por linha do arquivo
        while (arquivoLeitura>>chave >> path)
        {
            //std::cout << "Lendo chave: " << chave << " com caminho: " << path << std::endl;
            if (!path.empty())
            {
                _mapPathsTextures[chave] = path;
       
            }
        }
        arquivoLeitura.close(); // Fechar o arquivo ao final
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exceção capturada " << e.what() << std::endl;
    }
}

// A partir do nome da textura buscada, retorna o ponteiro da textura correspondente
sf::Texture* Gerenciadores::Gerenciador_Grafico::getTextura(std::string chave)
{
    std::map<std::string, std::string>::iterator it = _mapPathsTextures.find(chave);

    if (it != _mapPathsTextures.end())
    {
        sf::Texture* textura = new sf::Texture();  
        if (!textura->loadFromFile(it->second))  // Carregar a textura a partir do path
        {
            std::cout << "Falha ao carregar textura para a chave: " << chave << std::endl;
            delete textura;  // Garantir que a memória seja liberada em caso de erro
            return nullptr;
        }
        return textura;  // Retorna o ponteiro para a textura carregada
    }
    else
    {
        std::cout << "Chave não encontrada no mapa: " << chave << std::endl;
        return nullptr;  // Retorna nullptr se a chave não for encontrada
    }
}

// Retorna a fonte que eh utilizada em todos os textos presentes do jogo
sf::Font Gerenciadores::Gerenciador_Grafico::getFont()
{
    sf::Font fonte;
    if (!fonte.loadFromFile("assets/fontes/EnglishTowne.ttf"))
    {
        std::cerr << "Erro ao incluir fonte.\n";
        
        return sf::Font();
    }
    return fonte;
}