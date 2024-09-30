#pragma once

#include "Inimigo.hpp"
#include <vector>

#define MAGO_AREAALERTA_X 390.0f
#define MAGO_AREAALERTA_Y 150.0f
#define MAGO_EXPERIENCIA 150.0f
#define MAGO_TAMANHO_X 60.0f
#define MAGO_TAMANHO_Y 95.0f
#define MAGO_TEMPO_MORTE 1.5f
#define MAGO_TEMPO_ATAQUE 1.5f
#define MAGO_PONTOS 300
#define MAGO_FORCA 40.0f
#define MAGO_DEFESA 10.0f
#define MAGO_VIDA 15.0f

namespace EspadaLendaria {

    namespace Entidade {

        namespace Personagem {

            namespace Inimigo {

                class Mago : public Inimigo {
                private:
                    bool Podercheio;
                    void InicializarAnimacao();
                    void InicializarNivel();
                    void AtualizarAnimacao();
                    void AtualizarTempoAtaque();
                    Jogador::Jogador* escolherJogadorAlvo();  // Método para escolher o jogador alvo mais próximo

                public:
                    Mago(const sf::Vector2f pos, int nivel, const std::vector<Jogador::Jogador*>& jogadores, Item::Arma* arma = nullptr);
                    Mago(const std::vector<std::string>& atributos, const std::vector<Jogador::Jogador*>& jogadores);
                    ~Mago();
                    bool Podermax();
                    void setPoder();
                    void MoverInimigo();
                    void ReceberDano(const float dano);
                    const std::string salvar();
                };

            }
        }
    }
}


//Créditos ao Brullov Studios pela sprite do Mago 