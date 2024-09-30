#pragma once

#include "Observador.hpp"
#include "Menu.hpp"
#include "Botao.hpp"
#include "MenuGameOver.hpp"
#include "MenuSalvarJogada.hpp"
#include "MenuCarregarJogo.hpp"
#include "MenuFase.hpp"

namespace EspadaLendaria {

    namespace Observador {
        //padrao de objeto observer
        class ObservadorMenu : public Observador {
        private:
            Menu::Menu* menu;
        public:
            ObservadorMenu(Menu::Menu* menu);
            ~ObservadorMenu();
            void teclaPressionada(const sf::Keyboard::Key tecla);
            void teclaSolta(const sf::Keyboard::Key tecla);
            void moveMouse(const sf::Vector2f posMouse);
            void botaoMouseSolta(const sf::Mouse::Button botaoMouse);
        };

    }
    //Creditos ao Codigo Animacao do Monitor Giovane Limas Salvi
// Lido,Estudado e Adaptado para ser implementado ao Jogo Espada Lendaria
}