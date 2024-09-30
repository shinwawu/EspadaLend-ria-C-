#pragma once

#include "Arma.hpp"
#include "Animacao.hpp"

#define TAMANHO_PROJETIL 25.0f

namespace EspadaLendaria {

    namespace Entidade {

        namespace Item {

            class Projetil : public Arma {
            private:
                bool paraEsquerda;
                sf::Vector2f velocidade;
                Animador::Animacao animacao;
                bool colidiu;

                void AtualizarAnimacao();
                void atualizarPosicao();
                void verificaSaiuTela();
            public:
                Projetil(Personagem::Personagem* personagem = nullptr);
                Projetil(const std::vector<std::string> atributos, Personagem::Personagem* personagem = nullptr);
                ~Projetil();
                void InicializarAnimacao();
                void setSentido(const bool paraEsquerda);
                void setVelocidade(const sf::Vector2f velocidade);
                void setColidiu(const bool colidiu);
                const bool getColidiu() const;
                const std::string salvar();
                void desenhar();
                void atualizar();
            };

        }

    }

}//Creditos ao Codigo Animacao do Monitor Giovane Limas Salvi
 // Lido,Estudado e Adaptado para ser implementado ao Jogo Espada Lendaria

//Créditos ao Brullov Studios pela sprite do Boss 