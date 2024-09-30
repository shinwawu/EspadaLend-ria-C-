#pragma once

#include "Observador.hpp"
#include "Menu.hpp"

namespace EspadaLendaria {

    namespace Fase {
        class Fase;
    }

    namespace Observador {
        //padrao de projeto observer e mediator
        class ObservadorFase : public Observador {
        private:
            Fase::Fase* fase;
        public:
            ObservadorFase();
            ~ObservadorFase();
            void setFase(Fase::Fase* fase);
            void teclaPressionada(const sf::Keyboard::Key tecla);
            void teclaSolta(const sf::Keyboard::Key tecla);
            void notificarJogadorMorreu();
        };

    }
//Creditos ao Codigo Animacao do Monitor Giovane Limas Salvi
// Lido,Estudado e Adaptado para ser implementado ao Jogo Espada Lendaria
}