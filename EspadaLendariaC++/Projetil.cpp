#include "Projetil.hpp"

namespace EspadaLendaria {

    namespace Entidade {

        namespace Item {

            Projetil::Projetil(Personagem::Personagem* personagem) :
                Arma(IDs::IDs::magia, personagem), animacao(&Corpo),
                velocidade(sf::Vector2f(0.0f, 0.0f)), colidiu(true), paraEsquerda(false)
            {
                setPos(sf::Vector2f(-1000.0f, -1000.0f));
                if (personagem != nullptr) {
                    InicializarAnimacao();
                }
            }

            Projetil::Projetil(const std::vector<std::string> atributos, Personagem::Personagem* personagem) :
                Arma(IDs::IDs::magia, personagem), animacao(&Corpo),
                velocidade(sf::Vector2f(0.0f, 0.0f)), colidiu(true), paraEsquerda(false)
            {
                try {
                    const sf::Vector2f posAtual = sf::Vector2f(std::stof(atributos[1]), std::stof(atributos[2]));
                    const sf::Vector2f tamAtual = sf::Vector2f(std::stof(atributos[3]), std::stof(atributos[4]));
                    const float danoAtual = std::stof(atributos[5]);
                    const bool paraEsquerdaAtual = atributos[6] == "1";
                    const sf::Vector2f velocidadeAtual = sf::Vector2f(std::stof(atributos[7]), std::stof(atributos[8]));
                    const bool colidiuAtual = atributos[9] == "1";
                    const std::string imgAtual = atributos[10];
                    const unsigned int quadroAtual = std::stoi(atributos[11]);
                    const float tempoTotalAtual = std::stof(atributos[12]);

                    setPos(posAtual);
                    setTam(tamAtual);
                    this->dano = danoAtual;
                    this->paraEsquerda = paraEsquerdaAtual;
                    this->velocidade = velocidadeAtual;
                    this->colidiu = colidiuAtual;

                    if (personagem != nullptr) {
                        personagem->setArma(static_cast<Arma*>(this));
                        InicializarAnimacao();
                        animacao.setImgAtual(imgAtual);
                        animacao.setQuadroAtual(quadroAtual);
                        animacao.setTempoTotal(tempoTotalAtual);
                    }
                }
                catch (const std::exception& e) {
                    std::cerr << "ERRO::projetil::" << e.what() << std::endl;
                    podeRemover = true;
                }

            }

            Projetil::~Projetil() {
                
            }

            void Projetil::InicializarAnimacao() {
                if (personagem != nullptr) {
                    setTam(sf::Vector2f(TAMANHO_PROJETIL, TAMANHO_PROJETIL));
                    switch (personagem->getID())
                    {
                    case (IDs::IDs::mago):
                    {
                        const sf::Vector2f tamFrame(50.0f, 50.0f);

                        const sf::Vector2f originAtaca = sf::Vector2f(tamFrame.x / 4.5f, tamFrame.y / 4.5f);

                        const sf::Vector2f escalaAtaca(5.0f, 5.0f);

                        animacao.addAnimacao("img/Personagem/Inimigo/Mago/ProjetilMago.png", "ATACA", 4, 0.12f, escalaAtaca, originAtaca);
                        animacao.setImgAtual("ATACA");
                    }
                    break;
                    }
                }
            }

            void Projetil::setVelocidade(const sf::Vector2f velocidade) {
                this->velocidade = velocidade;
            }

            void Projetil::setColidiu(const bool colidiu) {
                this->colidiu = colidiu;
                if (colidiu) {
                    setPos(sf::Vector2f(-1000.0f, -1000.0f));
                    velocidade = sf::Vector2f(0.0f, 0.0f);
                }
            }

            const bool Projetil::getColidiu() const {
                return colidiu;
            }

            void Projetil::setSentido(const bool paraEsquerda) {
                this->paraEsquerda = paraEsquerda;
                if (paraEsquerda) {
                    velocidade.x = std::abs(velocidade.x) * -1; 
                }
                else {
                    velocidade.x = std::abs(velocidade.x); 
                }
            }


            void Projetil::verificaSaiuTela() {
                sf::Vector2f posCentro = pGrafico->getCamera().getCenter();
                sf::Vector2f tamJanela = pGrafico->getTamJanela();
                if (pos.x < posCentro.x - tamJanela.x / 2.0f || pos.x > posCentro.x + tamJanela.x / 2.0f ||
                    pos.y < posCentro.y - tamJanela.y / 2.0f || pos.y > posCentro.y + tamJanela.y / 2.0f
                    ) {
                    setVelocidade(sf::Vector2f(0.0f, 0.0f));
                    setColidiu(true);
                }
            }

            void Projetil::atualizarPosicao() {
                const float tempo = pGrafico->getTempo();
                sf::Vector2f posFinal(0.0f, 0.0f);

                posFinal.x = pos.x + velocidade.x * tempo;

                posFinal.y = pos.y + velocidade.y * tempo + (-GRAVIDADE * (tempo * tempo)) / 2;

                setPos(posFinal);
            }


            void Projetil::AtualizarAnimacao() {
                animacao.atualizar(paraEsquerda, "ATACA");
            }

            void Projetil::desenhar() {
                pGrafico->desenhaElemento(Corpo);
            }

            const std::string Projetil::salvar() {
                std::string linha = salvarArma();
                linha += std::to_string(paraEsquerda) + ' ';
                linha += std::to_string(velocidade.x) + ' ';
                linha += std::to_string(velocidade.y) + ' ';
                linha += std::to_string(colidiu) + ' ';
                linha += animacao.getImgAtual() + ' ';
                linha += std::to_string(animacao.getQuadroAtual()) + ' ';
                linha += std::to_string(animacao.getTempoTotal());
                return linha;
            }

            void Projetil::atualizar() {
                if (!colidiu) {
                    atualizarPosicao();
                    verificaSaiuTela();
                    AtualizarAnimacao();
                    desenhar();
                }
            }

        }

    }

}//Creditos ao Codigo Animacao do Monitor Giovane Limas Salvi
// Lido,Estudado e Adaptado para ser implementado ao Jogo Espada Lendaria