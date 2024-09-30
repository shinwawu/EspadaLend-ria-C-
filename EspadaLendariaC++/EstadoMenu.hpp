#pragma once

#include "Estado.hpp"

#include "Menu.hpp"
namespace EspadaLendaria {

    namespace Gerenciador {
        class GerenciadorEstado;
    }
    namespace Fase
    {
        class Fase;
    }
    namespace Estado {

        class EstadoMenu : public Estado {
        private:
            Menu::Menu* menu; //padrao de projeto state

            static Gerenciador::GerenciadorEstado* pGEstado; //padrao de projeto singleton
            void criarMenu();
        public:
            EstadoMenu(const IDs::IDs ID);
            ~EstadoMenu();
            void mudarEstadoObservador();
            EspadaLendaria::Fase::Fase* getFase();
            Menu::Menu* getMenu();
            void executar();
        };

    }

}//Creditos ao Codigo Animacao do Monitor Giovane Limas Salvi
// Lido,Estudado e Adaptado para ser implementado ao Jogo Espada Lendaria