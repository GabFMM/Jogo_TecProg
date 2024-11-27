#include <SFML/Graphics.hpp>
#include <iostream>
#include "ListaTemplate.h"
#include "Lista2.h"
using namespace std;
class Pessoa
{
private:
    string nome;
public:
    Pessoa(const string& name = " ") :nome(name) {};
    ~Pessoa() {};
    void imprime()const{ cout << "Nome :" << nome << endl; }
};

int main()
{
    Pessoa* p1 = new Pessoa("Yago");
    Pessoa* p2 = new Pessoa("Joao");
    Pessoa* p3 = new Pessoa("Ana");
    Lista<Pessoa>* l1 = new Lista<Pessoa>();
    l1->insert_back(p1);
    l1->insert_back(p2);
    l1->insert_back(p3);
    int i = 0;
    for (i = 0; i < 3; i++)
    {
        (*l1)[i]->getInfo()->imprime();
    }

    ListaElementar<Pessoa>* l2 = new ListaElementar<Pessoa>();
    l2->insert_back(p1);
    l2->insert_back(p2);
    l2->insert_back(p3);

    for (i = 0; i < 3; i++)
    {
        (*l2)[i]->getInfo()->imprime();
    }

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}