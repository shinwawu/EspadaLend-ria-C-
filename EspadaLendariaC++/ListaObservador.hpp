#pragma once

#include "Lista.hpp"
#include "Observador.hpp"
#include "SFML/Graphics.hpp"

namespace EspadaLendaria {

    namespace Lista {

        class ListaObservador { //padrao de projeto facade
        private:
            Lista<Observador::Observador> objListaObservador;
        public:
            ListaObservador();
            ~ListaObservador();
            void addObservador(Observador::Observador* observador);
            void removerObservador(Observador::Observador* observador);
            void removerObservador(int pos);
            int getTam();
            Observador::Observador* operator[](int pos);
            void notificarTeclaPressionada(const sf::Keyboard::Key tecla);
            void notificarTeclaSolta(const sf::Keyboard::Key tecla);
            void notificarMovimentoMouse(const sf::Event::MouseMoveEvent mouse);
            void notificarBotaoMouseSolta(const sf::Mouse::Button botaoMouse);
        };

    }

}
//Creditos ao Codigo Animacao do Monitor Giovane Limas Salvi
// Lido,Estudado para ser implementado ao Jogo Espada Lendaria