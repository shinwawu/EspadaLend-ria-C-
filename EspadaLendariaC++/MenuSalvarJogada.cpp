#include "MenuSalvarJogada.hpp"
#include "ListaEntidade.hpp"
#include "GerenciadorEstado.hpp"
#include "Fase.hpp"

namespace EspadaLendaria {

    namespace Menu {

        MenuSalvarJogada::MenuSalvarJogada(Fase::Fase* fase) :
            MenuPausa(IDs::IDs::menu_salvar_jogada, "SALVAR JOGADA", fase)
        {
            atualizarPosicaoFundo();
            fundoEscuro.setPosition(0.0, 0.0f);
            fundoEscuro.setFillColor(sf::Color{ 0, 0, 0, 230 });

            sf::Vector2f posFundoEscuro = sf::Vector2f(posFundo.x - tamJanela.x / 2.0f, posFundo.y - tamJanela.y / 2.0f);
            fundoEscuro.setPosition(posFundoEscuro);
            titulo.setPos(sf::Vector2f(posFundo.x - titulo.getTam().x / 2.1f, posFundo.y - tamJanela.y / 2.0f));

            inicializarFotoSalvars();
        }

        MenuSalvarJogada::~MenuSalvarJogada() {
            std::list<FotoSalvar*>::iterator aux = listaFotoSalvars.begin();
            while (aux != listaFotoSalvars.end()) {
                FotoSalvar* card = *aux;
                if (card != nullptr) {
                    delete(card);
                    card = nullptr;
                }
            }
            listaFotoSalvars.clear();
            fase = nullptr;
        }

        void MenuSalvarJogada::inicializarFotoSalvars() {
            float espaco = (tamJanela.x / 5.0f) / 5.0f;
            for (int i = 0; i < 4; i++) {
                sf::Vector2f pos(sf::Vector2f(
                    posFundo.x - tamJanela.x / 2.0f + (tamJanela.x / 5.0f) * i + (espaco) * (i + 1),
                    posFundo.y - tamJanela.y / 2.0f + 180.0f
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

        void MenuSalvarJogada::salvarJogada() {
            try {
                Gerenciador::GerenciadorEstado* pGEstado = Gerenciador::GerenciadorEstado::getGerenciadorEstado();
                Estado::Estado* estado = pGEstado->getEstado(2);
                Estado::EstadoJogar* pEstadoJogadr = dynamic_cast<Estado::EstadoJogar*>(estado);

                std::map<IDs::IDs, Fase::Fase*> mapFase = pEstadoJogadr->getMapFase();
                const IDs::IDs ID_FaseAtual = pEstadoJogadr->getIDFaseAtual();

                std::vector<std::string> linhas = fase->salvarEntidades();
                const std::string caminhoArquivoEntidades = (*itFotoSalvars)->getCaminhoArquivoEntidades();
                const std::string caminhoArquivoFase = (*itFotoSalvars)->getCaminhoArquivoFase();
                const std::string caminhoImagem = (*itFotoSalvars)->getCaminhoImage();

                gerenciadorArquivo.removeArquivo(caminhoArquivoEntidades.c_str());

                for (auto& linha : linhas) {
                    linha = sanitizarLinha(linha);
                    if (!linha.empty()) {
                        std::cout << "Salvando linha: " << linha << std::endl;
                        gerenciadorArquivo.gravarConteudo(caminhoArquivoEntidades.c_str(), { linha });
                    }
                    else {
                        std::cerr << "Erro: linha vazia ou mal formatada não será salva." << std::endl;
                    }
                }

                sf::IntRect limiteCamera = fase->getLimiteCamera();
                std::string limite = "";
                limite += ' ' + std::to_string(limiteCamera.left) + ' ';
                limite += std::to_string(limiteCamera.width) + ' ';
                limite += std::to_string(limiteCamera.top) + ' ';
                limite += std::to_string(limiteCamera.height) + ' ';

                std::string linhaLimite = std::to_string(static_cast<int>(fase->getID())) + limite + "==========";
                std::cout << "Salvando linha de limite: " << linhaLimite << std::endl;
                gerenciadorArquivo.gravarConteudo(caminhoArquivoEntidades.c_str(), { linhaLimite });

                std::string linhasFase = fase->salvar();
                gerenciadorArquivo.gravarConteudo(caminhoArquivoFase.c_str(), linhasFase);

                fase->desenhar();

                sf::RenderWindow* window = pGrafico->getWindow();
                sf::Texture textura;
                textura.create(window->getSize().x, window->getSize().y);
                textura.update(*(static_cast<sf::Window*>(window)));
                sf::Image imagem = textura.copyToImage();
                imagem.saveToFile(caminhoImagem);

                std::map<IDs::IDs, Fase::Fase*>::iterator itMapFase = mapFase.begin();
                while (itMapFase != mapFase.end()) {
                    Fase::Fase* aux = (*itMapFase).second;
                    if (aux != fase && aux != nullptr) {
                        linhas = aux->salvarEntidades();
                        for (auto& linha : linhas) {
                            linha = sanitizarLinha(linha);
                            if (!linha.empty()) {
                                std::cout << "Salvando linha para outra fase: " << linha << std::endl;
                                gerenciadorArquivo.gravarConteudo(caminhoArquivoEntidades.c_str(), { linha });
                            }
                            else {
                                std::cerr << "Erro: linha vazia ou mal formatada não será salva." << std::endl;
                            }
                        }

                        sf::IntRect limiteCamera = aux->getLimiteCamera();
                        limite = "";
                        limite += ' ' + std::to_string(limiteCamera.left) + ' ';
                        limite += std::to_string(limiteCamera.width) + ' ';
                        limite += std::to_string(limiteCamera.top) + ' ';
                        limite += std::to_string(limiteCamera.height) + ' ';

                        linhaLimite = std::to_string(static_cast<int>(aux->getID())) + limite + "==========";
                        std::cout << "Salvando linha de limite para outra fase: " << linhaLimite << std::endl;
                        gerenciadorArquivo.gravarConteudo(caminhoArquivoEntidades.c_str(), { linhaLimite });
                    }
                    itMapFase++;
                }
            }
            catch (const std::exception& e) {
                std::cerr << "Erro ao salvar jogada: " << e.what() << std::endl;
            }
        }

        std::string MenuSalvarJogada::sanitizarLinha(const std::string& linha) {
            std::string resultado = linha;
            resultado.erase(std::remove(resultado.begin(), resultado.end(), '÷'), resultado.end());
            resultado.erase(std::remove(resultado.begin(), resultado.end(), ''), resultado.end());
            return resultado;
        }


        void MenuSalvarJogada::selecionaEsquerda() {
            (*itFotoSalvars)->setSelecionado(false);
            if (itFotoSalvars == listaFotoSalvars.begin()) {
                itFotoSalvars = listaFotoSalvars.end();
            }
            itFotoSalvars--;
            (*itFotoSalvars)->setSelecionado(true);
        }

        void MenuSalvarJogada::selecionaDireita() {
            (*itFotoSalvars)->setSelecionado(false);
            itFotoSalvars++;
            if (itFotoSalvars == listaFotoSalvars.end()) {
                itFotoSalvars = listaFotoSalvars.begin();
            }
            (*itFotoSalvars)->setSelecionado(true);
        }

        void MenuSalvarJogada::criarBotoes() {
            const float posBotaoX = tamJanela.x / 2.0f - tamBotao.x / 2.0f;
            addBotao("Salvar", sf::Vector2f(0.0f, 0.0f), IDs::IDs::botao_salvar, sf::Color{ 255, 0, 0 });
            addBotao("Voltar", sf::Vector2f(0.0f, 0.0f), IDs::IDs::botao_voltar, sf::Color{ 255, 0, 0 });
            posBotaoY = 0.8f;
            atualizarBotoes();

            inicializarIterator();
        }

        void MenuSalvarJogada::executar() {
            fase->desenhar();

            pGrafico->desenhaElemento(fundoEscuro);

            pGrafico->desenhaElemento(titulo.getTexto());

            desenhar();

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