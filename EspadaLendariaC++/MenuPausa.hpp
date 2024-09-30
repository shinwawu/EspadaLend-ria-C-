#pragma once

#include "Menu.hpp"
#include "Fase.hpp"

namespace EspadaLendaria {

    namespace Menu {

        class MenuPausa : public Menu { //padrao de projeto template method e factory method
        private:
            sf::RectangleShape fundoPainel;

        protected:
            Fase::Fase* fase;
            sf::RectangleShape fundoEscuro;
            float posBotaoY;

            void atualizarBotoes();
        public:
            MenuPausa(Fase::Fase* fase = nullptr);
            MenuPausa(const IDs::IDs ID, const std::string nome, Fase::Fase* fase = nullptr);
            ~MenuPausa();
            virtual void criarBotoes();
            void setFase(Fase::Fase* fase);
            Fase::Fase* getFase();
            virtual void executar();
        };

    }
    //Creditos ao Codigo Animacao do Monitor Giovane Limas Salvi
// Lido,Estudado e Adaptado para ser implementado ao Jogo Espada Lendaria
}