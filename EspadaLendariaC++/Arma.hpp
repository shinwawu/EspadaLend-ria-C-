#pragma once

#include "Personagem.hpp"

namespace EspadaLendaria {

    namespace Entidade {

        namespace Item {
            //padrao template method
            class Arma : public Entidade {
            protected:
                float dano;
                Personagem::Personagem* personagem;

                const std::string salvarArma();
            public:
                Arma(const IDs::IDs ID, Personagem::Personagem* personagem = nullptr);
                Arma(const IDs::IDs ID, const std::vector<std::string> atributos);
                virtual ~Arma();
                void setPersonagem(Personagem::Personagem* personagem);
                void setDano(const float dano);
                void aumentarDano(const float bonus);
                void resetarDano();
                Personagem::Personagem* getPersona();
                const float getDano() const;
                void Colisao(Entidade* outraEntidade, sf::Vector2f ds = sf::Vector2f(0.0f, 0.0f));
                virtual void desenhar();
                virtual void atualizar();
                const std::string salvar();
            };

        }

    }

}
