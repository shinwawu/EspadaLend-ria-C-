#pragma once

#include "MenuPrincipal.hpp"
#include "GerenciadorArquivo.hpp"
#include <vector> 

#define CAMINHO_ARQUIVO_COLOCACAO "arquivo/Colocacao/colocacao.txt"
#define QUANTIDADE_PALAVRAS 2
#define CAMINHO_FONTE_COLOCACAO "fonte/menuColocacao.ttf"

namespace EspadaLendaria {

    namespace Menu {

        class MenuColocacao : public MenuPrincipal {//padrao de projeto template method e factory method
        private:
            std::vector<Botao::Texto*> vectorTexto;
            Gerenciador::GerenciadorArquivo gerenciadorArquivo;

            void criarTexto(std::string linha);
            void criarColocacao();
            void desenharColocacao();
        public:
            MenuColocacao();
            ~MenuColocacao();
            void criarBotoes();
            void executar();
        };

    }

}
//Creditos ao Codigo Animacao do Monitor Giovane Limas Salvi
// Lido,Estudado para ser implementado ao Jogo Espada Lendaria