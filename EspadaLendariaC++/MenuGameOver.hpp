#pragma once 

#include "MenuPausa.hpp"
#include "Fase.hpp"
#include "GerenciadorArquivo.hpp"

#define TAMANHO_BOTAO_MENU_GAME_OVER_X 350.0f
#define TAMANHO_BOTAO_MENU_GAME_OVER_Y 80.0f
#define CAMINHO_FONTE_MENU_GAME_OVER "fonte/menu.ttf"

namespace EspadaLendaria {

    namespace Menu {

        class MenuGameOver : public MenuPausa { //padrao de projeto template method e factory method
        private:
            //template methodf
            sf::RectangleShape fundoCaracter;
            Botao::Texto texto;
            Botao::Texto pontuacao;
            Gerenciador::GerenciadorArquivo gerenciadorArquivo;

            void ajustarTexto();
        public:
            MenuGameOver(Fase::Fase* fase);
            ~MenuGameOver();
            void criarBotoes();
            void addCaracter(char caracter);
            void removerCaracter();
            void salvarColocacao();
            void executar();
        };

    }
    //Creditos ao Codigo Animacao do Monitor Giovane Limas Salvi
// Lido,Estudado e Adaptado para ser implementado ao Jogo Espada Lendaria


}