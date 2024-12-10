#include "Gerenciador_Grafico.h"
#include "Ente.h"

Gerenciadores::Gerenciador_Grafico::Gerenciador_Grafico() 
{
    window = new sf::RenderWindow(sf::VideoMode(), "Jogo", sf::Style::Fullscreen);
    view = new sf::View(sf::FloatRect(0, 0, 900, 600));
    
}

Gerenciadores::Gerenciador_Grafico::~Gerenciador_Grafico() 
{
    delete(window);
    delete(view);
}

void Gerenciadores::Gerenciador_Grafico::desenhar(Entidades::Ente* pE)
{
    if (pE)
    {
        window->draw(pE->getBody());
    }
}

void Gerenciadores::Gerenciador_Grafico::desenhar(sf::RectangleShape& shape)
{
    window->draw(shape);
}

void Gerenciadores::Gerenciador_Grafico::render()
{
    window->clear();
}

void Gerenciadores::Gerenciador_Grafico::display() 
{
    window->display();
}

sf::RenderWindow* Gerenciadores::Gerenciador_Grafico::getWindow() 
{
    return window;
}

sf::View* Gerenciadores::Gerenciador_Grafico::getView() const {
    return view;
}

bool Gerenciadores::Gerenciador_Grafico::getOpen() const
{
    return window->isOpen();
}

void Gerenciadores::Gerenciador_Grafico::closeWindow()
{
    window->close();
}
