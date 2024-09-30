#pragma once

#include "MenuPrincipal.hpp"

#define CAMINHO_TEXTURA_MENU_PRINCIPAL "img/Menu/menuPrincipal.png"

namespace EspadaLendaria {

    namespace Menu {

        class Menuqntjogadores : public MenuPrincipal { //padrao de projeto template method
        public:
            Menuqntjogadores();
            ~Menuqntjogadores();
            void criarBotoes();
            void executar();
        };

    }

}