#pragma once

#include "MenuPausa.hpp"
#include "GerenciadorArquivo.hpp"
#include <map>

namespace EspadaLendaria {

    namespace Menu {

        class MenuSalvarJogada : public MenuPausa {
        private:
            Gerenciador::GerenciadorArquivo gerenciadorArquivo;
            std::list<FotoSalvar*> listaFotoSalvars;
            std::list<FotoSalvar*>::iterator itFotoSalvars;

            void inicializarFotoSalvars();
        public:
            MenuSalvarJogada(Fase::Fase* fase = nullptr);
            ~MenuSalvarJogada();
            void criarBotoes();
            void salvarJogada();
            void selecionaEsquerda();
            void selecionaDireita();
            void executar();
            std::string sanitizarLinha(const std::string& linha);
        };

    }
//Creditos ao Codigo Animacao do Monitor Giovane Limas Salvi
// Lido,Estudado para ser implementado ao Jogo Espada Lendaria


}