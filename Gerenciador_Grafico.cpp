#include "Gerenciador_Grafico.h"

/*
	TO DO:
	1. preciso do sprite de entes
	2. verificar se sera necessario deletar os ponteiro no removeEnte
*/

// ---------------------------------- PRIVATE ----------------------------------------------

/*
	Objetivos do metodo:
	- Criar a janela em tela cheia do jogo
	- Setar a taxa de framerate
*/
void Gerenciadores::Gerenciador_Grafico::criarJanela() {
	window = new sf::RenderWindow(sf::VideoMode(800, 1200), "Jogo", sf::Style::Fullscreen);
	window->setFramerateLimit(60);
}

/*
	Objetivos do metodo:
	- Atualizar a janela conforme os updates da lista
*/
void Gerenciadores::Gerenciador_Grafico::update() {
	if (listaEntes.empty()) return;

	for (it = listaEntes.begin(); it != listaEntes.end(); it++) {
		(*it)->executar();
	}
}

/*
	Objetivos do metodo:
	- Renderizar, mostrar na janela os entes da lista
*/
void Gerenciadores::Gerenciador_Grafico::render() {	
	if (listaEntes.empty()) return;

	window->clear();

	for (it = listaEntes.begin(); it != listaEntes.end(); it++) {
		//window->draw((*it)->getShape());
	}

	window->display();
}

// ---------------------------------- PUBLIC -----------------------------------------------

/*
	Objetivos da construtora:
	- Limpar a lista de entes previamente
	- Chamar o metodo criarJanela
	- Enquanto a janela estiver aberta, chamar os metodos update e render
*/
Gerenciadores::Gerenciador_Grafico::Gerenciador_Grafico() : listaEntes(){
	listaEntes.clear();

	criarJanela();
	while (window->isOpen()) {
		update();
		render();
	}
}

/*
	Objetivos da destruidora:
	- Limpar a lista de entes
	- Destruir janela
*/
Gerenciadores::Gerenciador_Grafico::~Gerenciador_Grafico(){
	if (!listaEntes.empty()) {
		Ente* aux = nullptr;
		
		for (it = listaEntes.begin(); it != listaEntes.end(); it++) {
			aux = (*it);
			
			if (aux != nullptr) {
				delete aux;
				aux = nullptr;
			}
		}

		listaEntes.clear();
	}

	if (window != nullptr) {
		delete window;
		window = nullptr;
	}
}

/*
	Objetivos do metodo:
	- Retornar o endereco de janela
*/
sf::RenderWindow* Gerenciadores::Gerenciador_Grafico::getWindow() const {
	return window;
}

/*
	Objetivos do metodo:
	- Incluir na lista de Entes o ponteiro recebido para que possa afetar e ser desenhado na tela
	junto com os restantes
*/
void Gerenciadores::Gerenciador_Grafico::desenharEnte(Ente* pE) {
	if (pE == nullptr) {
		std::cerr << "Ponteiro de entidade nulo. Impossivel desenhar." << std::endl;
		return;
	}
	
	listaEntes.push_front(pe);
}

/*
	Objetivos do metodo:
	- Remover da lista de entes o ponteiro recebido, para que nao seja renderizado e nem afetar a janela
	- O ponteiro nao sera destruido 
*/
void Gerenciadores::Gerenciador_Grafico::removerEnte(Ente* pE) {
	if (pE == nullptr) {
		std::cerr << "Ponteiro de entidade nulo. Impossivel remover." << std::endl;
		return;
	}

	listaEntes.remove(pE);
}
