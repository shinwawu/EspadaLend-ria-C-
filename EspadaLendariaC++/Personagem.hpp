#pragma once

#include "Entidade.hpp"
#include "Animacao.hpp"
#include "Nivel.hpp"
#include "Texto.hpp"

#define GRAVIDADE 1400.0f

#define BARRA_VIDA_X 60.0f
#define BARRA_VIDA_Y 6.0f

namespace EspadaLendaria {

    namespace Entidade {

        namespace Item {
            class Arma;
        }

        namespace Personagem {
            //template method
            class Personagem : public Entidade {
            protected:
                sf::Vector2f velFinal;
                Animador::Animacao animacao;
                sf::RectangleShape barraVida;
                Menu::Botao::Texto textoNivel;
                Nivel nivel;
                Item::Arma* arma;
                const float velMax;
                bool andando;
                bool paraEsquerda;
                bool levandoDano;
                bool atacando;
                bool morrendo;
                const float vidaMaxima;
                float vida;
                const float tempoAnimacaoTomarDano;
                float tempoDano;
                const float tempoAnimacaoMorrer;
                float tempoMorrer;
                float dt;
                unsigned int pontos;

                virtual void AtualizarAnimacao() = 0;
                virtual void atualizarBarraVida();
                virtual void inicializarBarraVida() = 0;
                virtual void InicializarAnimacao() = 0;
                virtual void InicializarNivel() = 0;
                virtual void AtualizarNivel();
                const std::string salvarPersonagem();
            public:
                Personagem(const sf::Vector2f pos, const sf::Vector2f tam, const float vel, const IDs::IDs ID, const float tempoMorrer, const float tempoDano = 0.6f);
                virtual ~Personagem();
                void setVelFinal(const sf::Vector2f velFinal);
                const sf::Vector2f getVelFinal() const;
                void andar(const bool paraEsquerda);
                void parar();
                void atacar(const bool atacando);
                void atualizarPosicao();
                void atualizarTomarDano();
                virtual void ReceberDano(const float dano);
                const bool getMorrer() const;
                virtual void Colisao(Entidade* outraEntidade, sf::Vector2f ds = sf::Vector2f(0.0f, 0.0f)) = 0;
                const unsigned int getPontos() const;
                void setArma(Item::Arma* arma);
                Item::Arma* getArma();
                const float getForca() const;
                virtual const std::string salvar() = 0;
                virtual void desenhar();
                virtual void atualizar() = 0;
            };

        }

    }

}
//Creditos ao Codigo Animacao do Monitor Giovane Limas Salvi
// Lido,Estudado e Adaptado para ser implementado ao Jogo Espada Lendaria