
#include "Jogador2.hpp"
#include "ObservadorJogador.hpp"
namespace EspadaLendaria {

    namespace Entidade {

        namespace Personagem {

            namespace Jogador {

                Jogador2::Jogador2(const sf::Vector2f pos, Item::Arma* arma) :
                    Jogador(pos, arma, IDs::IDs::jogador2),
                    emEsquiva(false),
                    tempoEsquiva(0.0f),
                    duracaoEsquiva(3.0f), 
                    cooldownEsquiva(8.0f)  
                {
                    InicializarAnimacao();
                }

                Jogador2::Jogador2(const std::vector<std::string> atributos) :
                    Jogador(atributos, IDs::IDs::jogador2),
                    emEsquiva(false),
                    tempoEsquiva(0.0f),
                    duracaoEsquiva(3.0f),
                    cooldownEsquiva(8.0f)  
                {
                    InicializarAnimacao();
                }

                Jogador2::~Jogador2() {
                    if (pObservadorJogador) {
                        pObservadorJogador->setJogador2(nullptr);
                    }
                }

                void Jogador2::InicializarAnimacao() {


                    const sf::Vector2f escala = sf::Vector2f(4.0f, 2.5f);
                    const sf::Vector2f origin = sf::Vector2f(
                        tam.x / 2.3f, 
                        tam.y / 1.8f 
                    );
                    //Creditos do Sprite ao LuizMelo
                    //https://luizmelo.itch.io/medieval-king-pack-2
                    animacao.addAnimacao("img/Personagem/Jogador/Jogador2/Anda.png", "ANDA", 8, 0.12f, escala, origin);

                    animacao.addAnimacao("img/Personagem/Jogador/Jogador2/Ataca.png", "ATACA", 4, 0.12f, escala, origin);

                    animacao.addAnimacao("img/Personagem/Jogador/Jogador2/Parado.png", "PARADO", 8, 0.12f, escala, origin);

                    animacao.addAnimacao("img/Personagem/Jogador/Jogador2/Pula.png", "PULA", 2, 0.12f, escala, origin);
                    animacao.addAnimacao("img/Personagem/Jogador/Jogador2/Cai.png", "CAI", 2, 0.12f, escala, origin);
                    animacao.addAnimacao("img/Personagem/Jogador/Jogador2/Morre.png", "MORRE", 6, 0.12f, escala, origin);
                    animacao.addAnimacao("img/Personagem/Jogador/Jogador2/tomaDano.png", "TOMADANO", 4, 0.12f, escala, origin);
                    corPadrao = Corpo.getFillColor();
                }
                void Jogador2::atualizarBarraVida() {
                    sf::Vector2f posJanela = pGrafico->getCamera().getCenter();
                    sf::Vector2f tamJanela = pGrafico->getTamJanela();

                    
                    sf::Vector2f posBarra = sf::Vector2f(posJanela.x + tamJanela.x / 2.0f - tuboBarraVida.getSize().x - 10.0f, posJanela.y + tamJanela.y / 2.0f - 30.0f);

                    tuboBarraVida.setPosition(posBarra);

                    
                    float larguraBarraVida = (tuboBarraVida.getSize().x - 35.0f) * (vida / 100.0f);

                    barraVida.setSize(sf::Vector2f(larguraBarraVida, BARRA_VIDA_JOGADOR_Y - 13.0f));

                    
                    barraVida.setPosition(sf::Vector2f(posBarra.x + 7.0f, posBarra.y + (tuboBarraVida.getSize().y / 2.0f) - (barraVida.getSize().y / 2.0f)));
                }


                void Jogador2::atualizarBarraXP() {
                    sf::Vector2f posJanela = pGrafico->getCamera().getCenter();
                    sf::Vector2f tamJanela = pGrafico->getTamJanela();

                    
                    sf::Vector2f posBarra = sf::Vector2f(posJanela.x + tamJanela.x / 2.0f - tuboBarraVida.getSize().x - 10.0f, posJanela.y - tamJanela.y / 2.0f + 100.0f); 

                    tuboBarraXP.setPosition(posBarra);

                    barraXP.setSize(sf::Vector2f((BARRA_VIDA_JOGADOR_X - 40.0f) * (nivel.getExp() / nivel.getExpProxNivel()), BARRA_VIDA_JOGADOR_Y - 13.0f));

                    barraXP.setPosition(sf::Vector2f(posBarra.x + 7.0f, posBarra.y + tuboBarraXP.getSize().y / 2.0f - barraXP.getSize().y / 2.0f));
                }

                void Jogador2::atualizarExp() {
                    sf::Vector2f posBarraXP(tuboBarraXP.getPosition());
                    textoExp.setPos(sf::Vector2f(posBarraXP.x + tuboBarraXP.getSize().x - textoExp.getTam().x - 5.0f, posBarraXP.y - textoExp.getTam().y - 12.0f));
                }

                void Jogador2::AtualizarNivel() {
                    sf::Vector2f posBarra = tuboBarraVida.getPosition();
                    textoNivel.setPos(sf::Vector2f(posBarra.x + 5.0f, posBarra.y - textoNivel.getTam().y - 12.0f));
                }


                void Jogador2::AtualizarAnimacao() {
                    if (morrendo) {
                        animacao.atualizar(paraEsquerda, "MORRE");
                        tempoMorrer += pGrafico->getTempo();
                        if (tempoMorrer > tempoAnimacaoMorrer / 2.f) {
                            podeRemover = true;
                            tempoMorrer = 0.0f;
                        }
                    }
                    else if (!noChao && velFinal.y > 0.0f) {
                        animacao.atualizar(paraEsquerda, "CAI");
                    }
                    else if (!noChao) {
                        animacao.atualizar(paraEsquerda, "PULA");
                    }
                    else if (levandoDano) {
                        animacao.atualizar(paraEsquerda, "TOMADANO");
                    }
                    else if (atacando) {
                        animacao.atualizar(paraEsquerda, "ATACA");
                    }
                    else if (andando) {
                        animacao.atualizar(paraEsquerda, "ANDA");
                    }
                    else {
                        animacao.atualizar(paraEsquerda, "PARADO");
                    }

                }
                void Jogador2::ativarEsquiva() {
                    if (podeUsarEsquiva()) {
                        emEsquiva = true;
                        tempoEsquiva = 0.0f;  
                        Corpo.setFillColor(sf::Color::Blue); 
                    }
                }

                bool Jogador2::podeUsarEsquiva() const {
                    return !emEsquiva && tempoEsquiva >= cooldownEsquiva;
                }

                void Jogador2::atualizar() {
                    AtualizarAnimacao();

                    atualizarBarraVida();

                    atualizarBarraXP();

                    AtualizarNivel();

                    atualizarExp();

                    Jogador::atualizar(); 

                    const float tempo = pGrafico->getTempo();

                    if (emEsquiva) {
                        tempoEsquiva += tempo;
                        if (tempoEsquiva >= duracaoEsquiva) {
                            emEsquiva = false;
                            tempoEsquiva = 0.0f;  
                            Corpo.setFillColor(corPadrao);
                        }
                    }
                    else {
                        if (tempoEsquiva < cooldownEsquiva) {
                            tempoEsquiva += tempo;
                        }
                    }
                }

                bool Jogador2::getEsquiva() {
                    return emEsquiva;
                }
            }

        }

    }

}
