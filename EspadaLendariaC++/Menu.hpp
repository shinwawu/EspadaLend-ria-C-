#pragma once 

#include "Ente.hpp"
#include "FotoSalvar.hpp"
#include "BotaoTexto.hpp"
#include "Texto.hpp"
#include "Fundo.hpp"
#include <list>

#define TAMANHO_BOTAO_X 350.0f
#define TAMANHO_BOTAO_Y 50.0f

namespace EspadaLendaria {

    namespace Observador {
        class ObservadorMenu;
    }

    namespace Menu {

        class Menu : public Ente { //padrao de projeto template method, observer
        protected:
            Observador::ObservadorMenu* observadorMenu;
            std::list<Botao::BotaoTexto*> listaBotaoTexto;
            std::list<Botao::BotaoTexto*>::iterator it;
            const sf::Vector2f tamBotao;
            const sf::Vector2f tamJanela;
            sf::Vector2f posFundo;
            Botao::Texto titulo;
            bool mouseSelecionado;

            void atualizarPosicaoFundo();
            virtual void criarFundo() {};
            virtual void criarBotoes() = 0;
            void inicializarIterator();
        public:
            Menu(const IDs::IDs ID, const sf::Vector2f tamBotao, const std::string nome, const unsigned int tamFonte);
            ~Menu();
            void addBotao(const std::string info, const sf::Vector2f pos, const IDs::IDs ID, const sf::Color corSelecionado);
            void mudarEstadoObservador();
            void selecionaCima();
            void selecionaBaixo();
            virtual void selecionaEsquerda() {}
            virtual void selecionaDireita() {}
            const IDs::IDs getIDBotaoSelecionado() const;
            void eventoMouse(const sf::Vector2f posMouse);
            const bool getMouseSelecionado() const;
            virtual void executar() = 0;
            void desenhar();
        };

    }
//Creditos ao Codigo Animacao do Monitor Giovane Limas Salvi
// Lido,Estudado para ser implementado ao Jogo Espada Lendaria

}