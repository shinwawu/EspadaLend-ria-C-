#pragma once

#include "Entidade.hpp"
#include "Jogador.hpp"
#include "Inimigo.hpp"

#include "Animacao.hpp"

namespace EspadaLendaria {

    namespace Entidade {

        namespace Obstaculo {
            //padrao d projeto template method
            class Obstaculo : public Entidade {
            protected:
                sf::Texture textura;

                virtual void InicializarAnimacao() = 0;
                const std::string salvarObstaculo();
            public:
                Obstaculo(const sf::Vector2f pos, const sf::Vector2f tam, const IDs::IDs ID);
                ~Obstaculo();
                virtual void Colisao(Entidade* outraEntidade, sf::Vector2f ds) = 0;
                virtual void atualizar();
                virtual void ColisaoObstaculo(sf::Vector2f ds, Personagem::Personagem* pPersonagem);
                virtual const std::string salvar();
            };

        }

    }
    //Creditos ao Codigo Animacao do Monitor Giovane Limas Salvi
    // Lido,Estudado e Adaptado para ser implementado ao Jogo Espada Lendaria

}