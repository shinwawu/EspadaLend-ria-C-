#pragma once

#include "Jogador.hpp"

namespace EspadaLendaria {
    namespace Entidade {
        namespace Personagem {
            namespace Jogador {

                class Jogador1 : public Jogador {
                private:
                    bool emFuria;
                    float tempoFuria;
                    float duracaoFuria;
                    float cooldownFuria;
                    sf::Color corPadrao;

                public:
                    Jogador1(const sf::Vector2f pos, Item::Arma* arma);
                    Jogador1(const std::vector<std::string> atributos);
                    ~Jogador1();
                    void InicializarAnimacao();
                    void ativarFuria();
                    bool podeUsarFuria() const;
                    void atualizar();
                    void AtualizarAnimacao();
                    void atualizarBarraVida();
                    void atualizarBarraXP();
                    void atualizarExp();
                    void AtualizarNivel();
                };

            }
        }
    }
}
