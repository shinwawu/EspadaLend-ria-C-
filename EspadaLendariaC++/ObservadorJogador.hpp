#pragma once

#include "Observador.hpp"
#include "GerenciadorEstado.hpp"
#include "Jogador.hpp"
namespace EspadaLendaria {
    namespace Entidade {
        namespace Personagem{
            namespace Jogador {
                class Jogador;
            }
        }
    }
    namespace Fase
    {
        class Fase;
    }
    namespace Observador {
        //padrao de objeto observer
        class ObservadorJogador : public Observador {
        protected:
            EspadaLendaria::Entidade::Personagem::Jogador::Jogador* pJogador1;
            EspadaLendaria::Entidade::Personagem::Jogador::Jogador* pJogador2;//coloquei o EspadaLendaria
        public:
            ObservadorJogador(EspadaLendaria::Entidade::Personagem::Jogador::Jogador* pJoga1, EspadaLendaria::Entidade::Personagem::Jogador::Jogador* pJoga2); //coloquei o EspadaLendaria
            ~ObservadorJogador();
            void teclaPressionada(const sf::Keyboard::Key tecla);
            void teclaSolta(const sf::Keyboard::Key tecla);
            void atualizarPontuacao(const unsigned int pontos);
            void setJogador2(EspadaLendaria::Entidade::Personagem::Jogador::Jogador* pJoga2);
            void setJogador1(EspadaLendaria::Entidade::Personagem::Jogador::Jogador* pJoga1);
        };

    }
}