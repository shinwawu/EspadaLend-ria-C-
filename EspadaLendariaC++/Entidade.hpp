#pragma once

#include "Ente.hpp"
#include <string>

namespace EspadaLendaria {

    namespace Entidade {

        class Entidade : public Ente {
        protected:
            sf::RectangleShape Corpo;
            sf::Vector2f pos;
            sf::Vector2f tam;

            bool podeRemover;
            const std::string salvarEntidade();
        public:
            Entidade(const sf::Vector2f tam, const IDs::IDs ID, const sf::Vector2f pos = sf::Vector2f(0.0f, 0.0f));
            virtual ~Entidade();
            const sf::RectangleShape getCorpo() const;
            void setPos(const sf::Vector2f pos);
            const sf::Vector2f getPos() const;
            void setTam(const sf::Vector2f tam);
            const sf::Vector2f getTam() const;
            virtual void Colisao(Entidade* outraEntidade, sf::Vector2f ds = sf::Vector2f(0.0f, 0.0f)) = 0;
            const bool getRemover() const;
            void remover();
            virtual const std::string salvar() = 0;
            virtual void atualizar() = 0;
            virtual void desenhar();
        };

    }
//Creditos ao Codigo Animacao do Monitor Giovane Limas Salvi
// Lido,Estudado para ser implementado ao Jogo Espada Lendaria
}