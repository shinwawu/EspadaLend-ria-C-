#pragma once

#include "Personagem.hpp"
#include "Arma.hpp"


#define JOGADOR_VELOCIDADE 200.0f
#define PULO_TAMANHO 120.0f
#define JOGADOR_TAMANHO_X 50.0f
#define JOGADOR_TAMANHO_Y 90.0f
#define ESPADA_TAMANHO 80.0f
#define JOGADOR_TEMPO_MORTE 1.0f
#define JOGADOR_TEMPO_RECEBERDANO 0.20f
#define BARRA_VIDA_JOGADOR_X 350.0f
#define BARRA_VIDA_JOGADOR_Y 20.0f
#define JOGADOR_DANO 40.0f
#define JOGADOR_FORCA 45.0f
#define JOGADOR_DEFESA 20.0f
#define JOGADOR_VIDA 25.0f

namespace EspadaLendaria {
    namespace Observador {
        class ObservadorJogador;
    }
    namespace Entidade {
        namespace Personagem {
            namespace Jogador {

                class Jogador : public Personagem {
                protected:
                    bool noChao;
                    bool colidindoPorta;
                    bool abrirPorta;
                    sf::Color corPadrao;
                    sf::RectangleShape tuboBarraVida;
                    sf::RectangleShape tuboBarraXP;
                    sf::RectangleShape barraXP;
                    Menu::Botao::Texto textoExp;
                    static Observador::ObservadorJogador* pObservadorJogador;

                    virtual void InicializarAnimacao() = 0;
                    void inicializarBarraVida();
                    virtual void AtualizarAnimacao() = 0;
                    virtual void atualizarBarraVida() = 0;
                    void InicializarNivel();
                    void inicializarBarraXP();
                    virtual void atualizarBarraXP() = 0;
                    virtual void AtualizarNivel() = 0;
                    void inicializarExp();
                    virtual void atualizarExp() = 0;

                public:
                    Jogador(const sf::Vector2f pos, Item::Arma* arma ,IDs::IDs id);
                    Jogador(const std::vector<std::string> atributos, IDs::IDs id);
                    virtual ~Jogador();
                    void Colisao(Entidade* outraEntidade, sf::Vector2f ds = sf::Vector2f(0.0f, 0.0f));
                    const bool getNoChao() const;
                    const bool getAndando() const;
                    void setColidindoPorta(const bool colidindoPorta);
                    const bool getColidindoPorta() const;
                    void setAbrirPorta(const bool abrirPorta);
                    const bool getAbrirPorta() const;
                    void pular();
                    void podePular();
                    void mudarEstadoObservador();
                    void addExperiencia(const float experiencia);
                    void setVida(const float vida);
                    const std::string salvar();
                    void atualizar();
                    void desenhar();
                    void addPontuacao(const unsigned int pontos);
                };

            }
        }
    }
}
