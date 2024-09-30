#pragma once

#include "Menu.hpp"
#include "Fundo.hpp"

#define CAMINHO_TEXTURA_MENU_PRINCIPAL "img/Menu/menuPrincipal.png"

namespace EspadaLendaria {

    namespace Menu {

        class MenuPrincipal : public Menu { //padrao de projeto template method 
        protected:
            Parallax::Fundo fundo;

        private:
            void criarFundo();

        public:
            MenuPrincipal();
            MenuPrincipal(const IDs::IDs ID, std::string nome, const unsigned int tamFonte = 180);
            virtual ~MenuPrincipal();
            virtual void criarBotoes();
            virtual void executar();
        };

    }

}
//Creditos ao Codigo Animacao do Monitor Giovane Limas Salvi
// Lido,Estudado e Adaptado para ser implementado ao Jogo Espada Lendaria
