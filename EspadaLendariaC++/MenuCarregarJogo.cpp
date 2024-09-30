#include "MenuCarregarJogo.hpp"

namespace EspadaLendaria {

    namespace Menu {

        MenuCarregarJogo::MenuCarregarJogo() :
            MenuPrincipal(IDs::IDs::menu_carregar_jogo, "CARREGAR JOGO", 100), gerenciadorArquivo()
        {
            inicializarFotoSalvars();
        }

        MenuCarregarJogo::~MenuCarregarJogo() {
            std::list<FotoSalvar*>::iterator aux = listaFotoSalvars.begin();
            while (aux != listaFotoSalvars.end()) {
                FotoSalvar* card = *aux;
                if (card != nullptr) {
                    delete(card);
                    card = nullptr;
                }
            }
            listaFotoSalvars.clear();
        }

        void MenuCarregarJogo::inicializarFotoSalvars() {
            float espaco = (tamJanela.x / 5.0f) / 5.0f;
            for (int i = 0; i < 4; i++) {
                sf::Vector2f pos(sf::Vector2f(
                    (tamJanela.x / 5.0f) * i + (espaco) * (i + 1),
                    180.0f
                ));
                std::string caminhoArquivoEntidades = "arquivo/SalvarJogada/SalvarEntidades/salvar" + std::to_string(i + 1) + ".txt";
                std::string caminhoArquivoFase = "arquivo/SalvarJogada/SalvarFase/salvar" + std::to_string(i + 1) + ".txt";
                std::string caminhoImagem = "arquivo/SalvarJogada/SalvarImagem/salvar" + std::to_string(i + 1) + ".png";
                FotoSalvar* card = new FotoSalvar(pos, caminhoArquivoEntidades, caminhoArquivoFase, caminhoImagem);
                card->setColor(sf::Color(255, 0, 0));
                listaFotoSalvars.push_back(card);
            }
            itFotoSalvars = listaFotoSalvars.begin();
            (*itFotoSalvars)->setSelecionado(true);
        }

        void MenuCarregarJogo::selecionaEsquerda() {
            (*itFotoSalvars)->setSelecionado(false);
            if (itFotoSalvars == listaFotoSalvars.begin()) {
                itFotoSalvars = listaFotoSalvars.end();
            }
            itFotoSalvars--;
            (*itFotoSalvars)->setSelecionado(true);
        }

        void MenuCarregarJogo::selecionaDireita() {
            (*itFotoSalvars)->setSelecionado(false);
            itFotoSalvars++;
            if (itFotoSalvars == listaFotoSalvars.end()) {
                itFotoSalvars = listaFotoSalvars.begin();
            }
            (*itFotoSalvars)->setSelecionado(true);
        }

        void MenuCarregarJogo::deletarArquivos() {
            FotoSalvar* card = (*itFotoSalvars);
            if (card->getExiste()) {
                gerenciadorArquivo.removeArquivo(card->getCaminhoArquivoEntidades().c_str());
                gerenciadorArquivo.removeArquivo(card->getCaminhoArquivoFase().c_str());
                gerenciadorArquivo.removeArquivo(card->getCaminhoImage().c_str());
                card->deletarTextura();
            }
        }

        FotoSalvar* MenuCarregarJogo::getFotoSalvarSelecionado() const {
            return *itFotoSalvars;
        }

        void MenuCarregarJogo::criarBotoes() {
            const float posBotaoX = tamJanela.x / 2.0f - tamBotao.x / 2.0f;
            addBotao("Carregar", sf::Vector2f(posBotaoX, tamJanela.y / 2.0f + tamBotao.y * 2.4f), IDs::IDs::botao_carregar, sf::Color{ 255, 0, 0 });
            addBotao("Remover", sf::Vector2f(posBotaoX, tamJanela.y / 2.0f + tamBotao.y * 3.6f), IDs::IDs::botao_remover, sf::Color{ 255, 0, 0 });
            addBotao("Voltar", sf::Vector2f(posBotaoX, tamJanela.y / 2.0f + tamBotao.y * 4.8f), IDs::IDs::botao_voltar, sf::Color{ 255, 0, 0 });
            inicializarIterator();
        }

        void MenuCarregarJogo::executar() {
            //conteúdo do efeito Parallax
            posFundo = sf::Vector2f(posFundo.x + pGrafico->getTempo() * 80.0f, posFundo.y);
            pGrafico->atualizarCamera(sf::Vector2f(posFundo.x + tamJanela.x / 2.0f, posFundo.y + tamJanela.y / 2.0f));
            fundo.executar();
            pGrafico->resetarJanela();

            desenhar();
            pGrafico->desenhaElemento(titulo.getTexto());

            std::list<FotoSalvar*>::iterator aux = listaFotoSalvars.begin();
            while (aux != listaFotoSalvars.end()) {
                FotoSalvar* card = *aux;
                card->desenhar();
                aux++;
            }
        }

    }

}//Creditos ao Codigo Animacao do Monitor Giovane Limas Salvi
// Lido,Estudado e Adaptado para ser implementado ao Jogo Espada Lendaria