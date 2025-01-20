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

/*void Gerenciadores::Gerenciador_Grafico::desenhar(sf::RectangleShape& shape)
{
    window->draw(shape);
}*/

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

void Gerenciadores::Gerenciador_Grafico::criaMap()
{
    //ifstream arquivoLeitura
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
        std::cerr << "Exce��o capturada " << e.what() << std::endl;
    }
   
}

sf::Texture* Gerenciadores::Gerenciador_Grafico::getTextura(std::string chave)
{
    std::map<std::string, std::string>::iterator it = _mapPathsTextures.find(chave);

    if (it != _mapPathsTextures.end())
    {
        sf::Texture* textura = new sf::Texture();  
        if (!textura->loadFromFile(it->second))  // Carregar a textura a partir do path
        {
            std::cout << "Falha ao carregar textura para a chave: " << chave << std::endl;
            delete textura;  // Garantir que a mem�ria seja liberada em caso de erro
            return nullptr;
        }
        return textura;  // Retorna o ponteiro para a textura carregada
    }
    else
    {
        std::cout << "Chave n�o encontrada no mapa: " << chave << std::endl;
        return nullptr;  // Retorna nullptr se a chave n�o for encontrada
    }
}

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

/*

Jogador1_Direita assets/Player1.png
Jogador1_Esquerda assets/Player1Esquerda.png
Jogador2_Direita assets/Player2.png
Jogador2_Esquerda assets/Player2Esquerda.png
Tela_Paralisada assets/TelaParalisada.png
Espada assets/EspadaReta1.png
Espada_Direita assets/EspadaDireita.png
Espada_Esquerda assets/EspadaEsquerda.png
Cavaleiro assets/Inimigo.png
MortoVivo assets/Mortovivo-.png
MortoVivoThread assets/MortovivoTH.png
Mago assets/chefe.png
Fim_De_Jogo assets/tela fim de jogo/background2.jpg
Projetil assets/fogo3.png
Barra_Magica assets/BarreiraEletrica.png
Espinho assets/PlataformaEspinho.png
Plataforma assets/TerrenoComFundo.png
Fundo_Castelo assets/Fase castelo/background.jpg
Fundo_Floresta assets/FundoFlorest.png
Heart_Full assets/HeartFULL.png
Heart_Empty assets/HeartEMPTY.png
FundoMedieval assets/menu/FundoMedieval.png
Pergaminho assets/menu/pergaminho.jpg
Floresta_Icone assets/menu/floresta.png
Castelo_Icone assets/menu/castelo.jpg
*/