#include "MenuPrincipal.hpp"

namespace EspadaLendaria {

    namespace Menu {

        MenuPrincipal::MenuPrincipal() :
            Menu(IDs::IDs::menu_principal, sf::Vector2f(TAMANHO_BOTAO_X, TAMANHO_BOTAO_Y), "Espada Lendaria", 100),
            fundo(IDs::IDs::fundo_florestaNegra)
        {
            titulo.setPos(sf::Vector2f(tamJanela.x / 2.0f - titulo.getTam().x / 2.0f, 100.0f));
            titulo.setCorTexto(sf::Color{ 200,0,0 });
            criarFundo();
        }

        MenuPrincipal::MenuPrincipal(const IDs::IDs ID, std::string nome, const unsigned int tamFonte) :
            Menu(ID, sf::Vector2f(TAMANHO_BOTAO_X, TAMANHO_BOTAO_Y), nome, tamFonte),
            fundo(IDs::IDs::fundo_florestaNegra)
        {
            titulo.setPos(sf::Vector2f(tamJanela.x / 2.0f - titulo.getTam().x / 2.0f, 25.0f));
            titulo.setCorTexto(sf::Color{ 200,0,0 });

            criarFundo();
        }

        MenuPrincipal::~MenuPrincipal() {

        }

        void MenuPrincipal::criarFundo() {
            fundo.addCamada("img/Fase/FasePrimeira/layer_1.png", 0.0f);
            fundo.addCamada("img/Fase/FasePrimeira/layer_2.png", 0.05f);
            fundo.addCamada("img/Fase/FasePrimeira/layer_3.png", 0.6f);

        }

        void MenuPrincipal::criarBotoes() {
            const float posBotaoX = tamJanela.x / 2.0f - tamBotao.x / 2.0f;
            addBotao("Novo Jogo", sf::Vector2f(posBotaoX, tamJanela.y / 2.0f), IDs::IDs::botao_novoJogo, sf::Color{ 255, 0, 0 });
            addBotao("Carregar Jogo", sf::Vector2f(posBotaoX, tamJanela.y / 2.0f + tamBotao.y * 1.2f), IDs::IDs::botao_carregar_jogo, sf::Color{ 255, 0, 0 });
            addBotao("Colocacao", sf::Vector2f(posBotaoX, tamJanela.y / 2.0f + tamBotao.y * 2.4f), IDs::IDs::botao_colocacao, sf::Color{ 255, 0, 0 });
            addBotao("Sair", sf::Vector2f(posBotaoX, tamJanela.y / 2.0f + tamBotao.y * 3.6f), IDs::IDs::botao_sair, sf::Color{ 255, 0, 0 });
            inicializarIterator();
        }

        void MenuPrincipal::executar() {
            posFundo = sf::Vector2f(posFundo.x + pGrafico->getTempo() * 80.0f, posFundo.y);
            pGrafico->atualizarCamera(sf::Vector2f(posFundo.x + tamJanela.x / 2.0f, posFundo.y + tamJanela.y / 2.0f));
            fundo.executar();
            pGrafico->resetarJanela();

            desenhar();
            pGrafico->desenhaElemento(titulo.getTexto());
        }

    }

}//Creditos ao Codigo Animacao do Monitor Giovane Limas Salvi
// Lido,Estudado e Adaptado para ser implementado ao Jogo Espada Lendaria