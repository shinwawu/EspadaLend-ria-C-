#pragma once

#include "Inimigo.hpp"

#define TAMANHO_BOSS_X 120.0f
#define TAMANHO_BOSS_Y 150.0f
#define TEMPO_BOSS_MORRER 1.5f

namespace EspadaLendaria {

    namespace Entidade {

        namespace Personagem {

            namespace Inimigo {

                class Boss : public Inimigo {
                private:
                    bool raiva;
                    bool defender;
                    float tempoRaiva;
                    sf::Color corPadrao;

                    void InicializarAnimacao();
                    void InicializarNivel();
                    void AtualizarAnimacao();
                public:
                    Boss(const sf::Vector2f pos, const int nivel, const std::vector<Jogador::Jogador*>& jogadores);
                    Boss(const std::vector<std::string> atributos, const std::vector<Jogador::Jogador*>& jogadores);
                    ~Boss();
                    void DefendeDano();
                    bool getDefender();
                    void setDefender();
                    void ReceberDano(const float dano);
                    void AtualizarTempoAtaque();
                    void MoverInimigo();
                    const std::string salvar();
                };

            }

        }

    }

}