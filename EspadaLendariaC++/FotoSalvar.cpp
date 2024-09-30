#include "FotoSalvar.hpp"
#include "GerenciadorArquivo.hpp"
#include <fstream>

namespace EspadaLendaria {

    namespace Menu {

        Gerenciador::GerenciadorGrafico* FotoSalvar::pGrafico = Gerenciador::GerenciadorGrafico::getGerenciadorGrafico();

        FotoSalvar::FotoSalvar(const sf::Vector2f pos, const std::string caminhoArquivoEntidades, const std::string caminhoArquivoFase, const std::string caminhoImage) :
            caminhoArquivoEntidades(caminhoArquivoEntidades), caminhoArquivoFase(caminhoArquivoFase),
            textoInfo(pGrafico->carregarFonte(CAMINHO_FONTE_CARD), "", 25), caminhoImage(caminhoImage),
            textura(nullptr), Corpo(nullptr), selecionado(false),
            cor(sf::Color(0, 255, 0)), existe(false)
        {
            sf::Vector2f tamJanela = pGrafico->getTamJanela();
            Corpo = new sf::RectangleShape(sf::Vector2f(tamJanela.x / 5.0f, tamJanela.x / 5.0f - 20.0f));
            textura = new sf::Texture();
            std::ifstream arquivo(caminhoImage);
            if (arquivo) {
                if (!textura->loadFromFile(caminhoImage)) {
                    std::cout << "FotoSalvar::nao foi possivel carregar textura" << std::endl;
                    exit(1);
                }
                existe = true;
                Gerenciador::GerenciadorArquivo GArquivo;
                std::vector<std::string> vectorInfoFase = GArquivo.lerArquivo(caminhoArquivoFase.c_str());
                std::string pontos = vectorInfoFase[1];
                while (pontos.size() < 5) {
                    std::string aux = pontos;
                    pontos = '0' + pontos;
                }
                std::string textoInfoAux = "Pontos: " + pontos;
                const char quebraLinha = 10;
                textoInfoAux += quebraLinha;
                textoInfoAux += vectorInfoFase[2];
                textoInfo.setString(textoInfoAux);
                textoInfo.setPos(sf::Vector2f(
                    pos.x + Corpo->getSize().x / 2.0f - textoInfo.getTam().x / 2.0f,
                    pos.y + Corpo->getSize().y + 10.0f
                ));
                textoInfo.setTamanhoBorda(2);
            }
            else {
                if (!textura->loadFromFile("arquivo/SalvarJogada/SalvarImagem/FotoSalvarVazio.png")) {
                    std::cout << "FotoSalvar::nao foi possivel carregar textura" << std::endl;
                    exit(1);
                }
            }
            Corpo->setTexture(textura);
            Corpo->setPosition(pos);
            Corpo->setOutlineThickness(5);
            Corpo->setOutlineColor(sf::Color::Black);
            //Corpo->setOutlineColor(sf::Color::Transparent);
        }

        FotoSalvar::~FotoSalvar() {
            if (textura != nullptr) {
                delete(textura);
                textura = nullptr;
            }
            if (Corpo != nullptr) {
                delete(Corpo);
                Corpo = nullptr;
            }
        }

        const std::string FotoSalvar::getCaminhoArquivoEntidades() const {
            return caminhoArquivoEntidades;
        }

        const std::string FotoSalvar::getCaminhoArquivoFase() const {
            return caminhoArquivoFase;
        }

        const std::string FotoSalvar::getCaminhoImage() const {
            return caminhoImage;
        }

        void FotoSalvar::setColor(const sf::Color cor) {
            this->cor = cor;
        }

        void FotoSalvar::setSelecionado(const bool selecionado) {
            this->selecionado = selecionado;
            Corpo->setOutlineColor(selecionado ? cor : sf::Color::Black);
        }

        const bool FotoSalvar::getSelecionado() const {
            return selecionado;
        }

        const bool FotoSalvar::getExiste() const {
            return existe;
        }

        void FotoSalvar::deletarTextura() {
            if (textura) {
                sf::Vector2u tamImgAnt = textura->getSize();
                if (!textura->loadFromFile("arquivo/SalvarJogada/SalvarImagem/pngwing.com.png")) {
                    std::cout << "FotoSalvar::nao foi possivel carregar textura" << std::endl;
                    exit(1);
                }
                Corpo->setTexture(textura);
                sf::Vector2u tamImgAtual = textura->getSize();
                sf::Vector2f fator((float)tamImgAtual.x / (float)tamImgAnt.x, (float)tamImgAtual.y / (float)tamImgAnt.y);
                Corpo->setTextureRect(sf::IntRect(0.0f, 0.0f, tamImgAnt.x * fator.x, tamImgAnt.y * fator.y));
                textoInfo.setString("");
                existe = false;
            }
        }

        void FotoSalvar::desenhar() {
            pGrafico->desenhaElemento(*Corpo);
            if (selecionado) {
                pGrafico->desenhaElemento(textoInfo.getTexto());
            }
        }

    }

}//Creditos ao Codigo Animacao do Monitor Giovane Limas Salvi
// Lido,Estudado e Adaptado para ser implementado ao Jogo Espada Lendaria