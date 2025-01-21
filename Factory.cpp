#include "Factory.h"
#include "Jogador.h"
#include "Cavaleiro.h"
#include "Bruxa.h"
#include "Mago.h"
#include "BruxaThread.h"
#include "Plataforma.h"
#include "BarraMagica.h"
#include "Espinho.h"
#include "Constantes.h"

namespace Entidades {

    // Criação de Jogador
    Entidade* EntidadeFactory::criarEntidade(
        float inicialX,
        float inicialY,
        Gerenciadores::Gerenciador_Grafico* pgra,
        const std::string& nome)
    {
        return new Entidades::Jogador(inicialX, inicialY, pgra, nome);
    }

    // Criação de Inimigo
    Entidade* EntidadeFactory::criarEntidade(
        float inicialX,
        float inicialY,
        Gerenciadores::Gerenciador_Grafico* pgra,
        Jogador* pJog1,
        Jogador* pJog2,
        int tipo)
    {
        

        switch (tipo) 
        {
        case Constantes::TIPO_CAVALEIRO:
            return new Entidades::Cavaleiro(inicialX, inicialY, pgra, pJog1, pJog2);

        case Constantes::TIPO_BRUXA:
            return new Entidades::Bruxa(inicialX, inicialY, pgra, pJog1, pJog2);

        case Constantes::TIPO_MAGO:
            return new Entidades::Mago(inicialX, inicialY, pgra, pJog1, pJog2);

        case Constantes::TIPO_BRUXA_THREAD : // BruxaThread
            return new Entidades::BruxaThread(inicialX, inicialY, pgra, pJog1, pJog2);

        default:
            return nullptr; // Tipo de inimigo não reconhecido.
        }
    }

    // Criação de Obstáculo
    Entidade* EntidadeFactory::criarEntidade(
        float inicialX,
        float inicialY,
        Gerenciadores::Gerenciador_Grafico* pgra,
        int tipo)
    {
        switch (tipo) 
        {
        case Constantes::TIPO_PLATAFORMA:
            return new Entidades::Plataforma(inicialX, inicialY, pgra);
            

        case Constantes::TIPO_BARRA_MAGICA:
            return new Entidades::BarraMagica(inicialX, inicialY, pgra);
            

        case Constantes::TIPO_ESPINHO:
            return new Entidades::Espinho(1,inicialX, inicialY, pgra);
            

        case Constantes::TIPO_PROJETIL:
            return new Entidades::Projetil(inicialX, inicialY, pgra);
            

        default:
            return nullptr; // Tipo de obstáculo não reconhecido.
        }
    }

    //Projetil

} // namespace Entidades
