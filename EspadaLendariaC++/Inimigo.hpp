#pragma once

#include "Personagem.hpp"
#include "Jogador.hpp"
#include "Jogador1.hpp"
#include "Jogador2.hpp"
#include "Arma.hpp"

// usado p/ gerar números aleatórios
#include <time.h>

// utiliza a função fabs
#include <cmath>
#include <vector>

#define RAIO_PERSEGUIR_X 200.0f
#define RAIO_PERSEGUIR_Y 200.0f
#define VELOCIDADE_INIMIGO 60.0f
#define TEMPO_MOVER_ALEATORIO 1.0f

namespace EspadaLendaria {

    namespace Entidade {

        namespace Personagem {

            namespace Inimigo {

                class Inimigo : public Personagem { // padrão de projeto template method e observer
                protected:
                    std::vector<Jogador::Jogador*> jogadores; // Lista de jogadores
                    short moveAleatorio;
                    float tempoMover;
                    const float tempoAnimacaoAtacar;
                    float tempoAtacar;
                    const float experiencia;
                    

                    virtual void MoverInimigo();
                    void atualizaMovimentoAleatorio();
                    virtual void InicializarAnimacao() = 0;
                    void inicializarBarraVida();
                    virtual void AtualizarTempoAtaque();
                    virtual void AtualizarAnimacao();
                    virtual void InicializarNivel() = 0;
                    const std::string salvarInimigo();
                public:
                    static int cont;
                    Inimigo(const sf::Vector2f pos, const sf::Vector2f tam, const std::vector<Jogador::Jogador*>& jogadores, const IDs::IDs ID, const float tempoMorrer, const float tempoAtacar, const float experiencia);
                    ~Inimigo();
                    int getcont();
                    void setcont();
                    virtual void ReceberDano(const float dano);
                    void Colisao(Entidade* outraEntidade, sf::Vector2f ds = sf::Vector2f(0.0f, 0.0f));
                    virtual const std::string salvar() = 0;
                    const float getExperiencia() const;
                    void atualizar();
                };

            }

        }

    }

}
