#include "MenuQntjogadores.hpp"

namespace EspadaLendaria {

    namespace Menu {

        Menuqntjogadores::Menuqntjogadores() :
            MenuPrincipal(IDs::IDs::menu_qntjogadores, "Selecione", 70)
        {
            titulo.setPos(sf::Vector2f(tamJanela.x / 2.0f - titulo.getTam().x / 2.0f, 100.0f));
            titulo.setCorTexto(sf::Color{ 200,0,0 });
        }

        Menuqntjogadores::~Menuqntjogadores()
        {

        }

        void Menuqntjogadores::criarBotoes() {
            const float posBotaoX = tamJanela.x / 2.0f - tamBotao.x / 2.0f;
            addBotao("Um jogador", sf::Vector2f(posBotaoX, tamJanela.y / 2.0f), IDs::IDs::botao_umjogador, sf::Color{ 255, 0, 0 });
            addBotao("Dois Jogadores", sf::Vector2f(posBotaoX, tamJanela.y / 2.0f + tamBotao.y * 1.2f), IDs::IDs::botao_doisjogadores, sf::Color{ 255, 0, 0 });
            addBotao("Voltar", sf::Vector2f(posBotaoX, tamJanela.y / 2.0f + tamBotao.y * 3.0f), IDs::IDs::botao_voltar, sf::Color{ 255, 0, 0 });
            inicializarIterator();
        }

        void Menuqntjogadores::executar() {
            posFundo = sf::Vector2f(posFundo.x + pGrafico->getTempo() * 80.0f, posFundo.y);
            pGrafico->atualizarCamera(sf::Vector2f(posFundo.x + tamJanela.x / 2.0f, posFundo.y + tamJanela.y / 2.0f));
            fundo.executar();
            pGrafico->resetarJanela();

            desenhar();
            pGrafico->desenhaElemento(titulo.getTexto());
        }

    }

}