#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include "Lista.h"
#include "Gerenciador_Grafico.h"
#include "Jogador.h"
#include "Projetil.h"
#include "ListaEntidades.h"
#include "Plataforma.h"
#include "Gerenciador_Colisoes.h"
#include "Espinho.h"
#include "BarraMagica.h"
#include "Cavaleiro.h"
#include "Mago.h"
#include "Floresta.h"
#include "Jogo.h"

using namespace std;

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));
    Jogo* principal = new Jogo();
    principal->executar();
    return 0;
}