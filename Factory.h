#pragma once
#include <string>
#include "Entidade.h"
#include "Gerenciador_Grafico.h"
#include "Jogador.h"

namespace Entidades {

    class EntidadeFactory {
    public:
        // M�todo para criar um Jogador
        static Entidade* criarEntidade(
            float inicialX,
            float inicialY,
            Gerenciadores::Gerenciador_Grafico* pgra,
            const std::string& nome
        );

        // M�todo para criar um Inimigo
        static Entidade* criarEntidade(
            float inicialX,
            float inicialY,
            Gerenciadores::Gerenciador_Grafico* pgra,
            Jogador* pJog1,
            Jogador* pJog2,
            int tipo
        );

        // M�todo para criar um Obst�culo
        static Entidade* criarEntidade(
            float inicialX,
            float inicialY,
            Gerenciadores::Gerenciador_Grafico* pgra,
            int tipo
        );
    };

} // namespace Entidades
