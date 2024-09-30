#include "ObservadorFase.hpp"
#include "GerenciadorEstado.hpp"
#include "Fase.hpp"

namespace EspadaLendaria {

    namespace Observador {

        ObservadorFase::ObservadorFase() :
            Observador(), fase(nullptr)
        {

        }

        ObservadorFase::~ObservadorFase() {
            fase = nullptr;
        }

        void ObservadorFase::setFase(Fase::Fase* fase) {
            this->fase = fase;
        }

        void ObservadorFase::notificarJogadorMorreu() {
            pGEstado->addEstado(IDs::IDs::estado_menu_game_over);
        }

        void ObservadorFase::teclaPressionada(const sf::Keyboard::Key tecla) {
            Estado::Estado* estadoAtual = pGEstado->getEstadoAtual();
            if (estadoAtual && estadoAtual->getID() != IDs::IDs::estado_menu_pausa) {
                if (tecla == sf::Keyboard::Escape || tecla == sf::Keyboard::P) {
                    pGEstado->addEstado(IDs::IDs::estado_menu_pausa);
                }
            }
        }

        void ObservadorFase::teclaSolta(const sf::Keyboard::Key tecla) {
            Estado::Estado* estadoAtual = pGEstado->getEstadoAtual();
            if (estadoAtual && estadoAtual->getID() != IDs::IDs::estado_menu_pausa) {
                if (tecla == sf::Keyboard::Escape || tecla == sf::Keyboard::P) {
                    pGEstado->addEstado(IDs::IDs::estado_menu_pausa);
                }
            }
        }

    }

}//Creditos ao Codigo Animacao do Monitor Giovane Limas Salvi
// Lido,Estudado e Adaptado para ser implementado ao Jogo Espada Lendaria