#include "Jogador1.hpp"
#include "ObservadorJogador.hpp"
#include "Arma.hpp"
namespace EspadaLendaria {
    namespace Entidade {
        namespace Personagem {
            namespace Jogador {

                Jogador1::Jogador1(const sf::Vector2f pos, Item::Arma* arma) :
                    Jogador(pos, arma, IDs::IDs::jogador1), emFuria(false), tempoFuria(0.0f), duracaoFuria(5.0f), cooldownFuria(10.0f)  // Cooldown ajustado para 10 segundos
                {
                    corPadrao = Corpo.getFillColor();

                    InicializarAnimacao();
                    atualizarBarraVida();

                    atualizarBarraXP();

                    AtualizarNivel();

                    atualizarExp();
                }

                Jogador1::Jogador1(const std::vector<std::string> atributos) :
                    Jogador(atributos, IDs::IDs::jogador1),
                    emFuria(false),
                    tempoFuria(0.0f),
                    duracaoFuria(5.0f), cooldownFuria(10.0f)  // Cooldown ajustado para 10 segundos
                {
                    corPadrao = Corpo.getFillColor();
                    InicializarAnimacao();
                    atualizarBarraVida();

                    atualizarBarraXP();

                    AtualizarNivel();

                    atualizarExp();
                }

                Jogador1::~Jogador1() {
                     if (pObservadorJogador) {
                            pObservadorJogador->setJogador1(nullptr);
                     }
                }
                void Jogador1::InicializarAnimacao() {


                    const sf::Vector2f escala = sf::Vector2f(6.0f, 4.0f);
                    const sf::Vector2f origin = sf::Vector2f(
                        tam.x / 2.3f, // Centraliza horizontalmente
                        tam.y / 2.55f // Alinha os pés ao chão
                    );

                    //Creditos do Sprite ao LuizMelo.
                    //https://luizmelo.itch.io/martial-hero-2
                    animacao.addAnimacao("img/Personagem/Jogador/Jogador1/Anda.png", "ANDA", 8, 0.12f, escala, origin);

                    animacao.addAnimacao("img/Personagem/Jogador/Jogador1/Ataca.png", "ATACA", 4, 0.065f, escala, origin);

                    animacao.addAnimacao("img/Personagem/Jogador/Jogador1/Parado.png", "PARADO", 4, 0.15f, escala, origin);

                    animacao.addAnimacao("img/Personagem/Jogador/Jogador1/Pula.png", "PULA", 2, 0.15f, escala, origin);
                    animacao.addAnimacao("img/Personagem/Jogador/Jogador1/Cai.png", "CAI", 2, 0.15f, escala, origin);
                    animacao.addAnimacao("img/Personagem/Jogador/Jogador1/Morre.png", "MORRE", 7, 0.10f, escala, origin);
                    animacao.addAnimacao("img/Personagem/Jogador/Jogador1/tomaDano.png", "TOMADANO", 3, 0.5f, escala, origin);
                    corPadrao = Corpo.getFillColor();
                }
                void Jogador1::atualizarBarraVida() {
                    sf::Vector2f posJanela = pGrafico->getCamera().getCenter();
                    sf::Vector2f tamJanela = pGrafico->getTamJanela();
                    sf::Vector2f posBarra = sf::Vector2f(posJanela.x - tamJanela.x / 2.0f + 10.0f, posJanela.y + tamJanela.y / 2.0f - 30.0f);
                    tuboBarraVida.setPosition(posBarra);
                    barraVida.setSize(sf::Vector2f((BARRA_VIDA_JOGADOR_X - 40.0f) * (vida / 100.0f), BARRA_VIDA_JOGADOR_Y - 13.0f));
                    barraVida.setPosition(sf::Vector2f(posBarra.x + 7.0f, posBarra.y + tuboBarraVida.getSize().y / 2.0f - barraVida.getSize().y / 2.0f));
                }

                void Jogador1::atualizarBarraXP() {
                    sf::Vector2f posJanela = pGrafico->getCamera().getCenter();
                    sf::Vector2f tamJanela = pGrafico->getTamJanela();

                    
                    sf::Vector2f posBarra = sf::Vector2f(posJanela.x - tamJanela.x / 2.0f + 20.0f, posJanela.y - tamJanela.y / 2.0f + 100.0f);
                    tuboBarraXP.setPosition(posBarra);

                   
                    barraXP.setSize(sf::Vector2f((BARRA_VIDA_JOGADOR_X - 40.0f) * (nivel.getExp() / nivel.getExpProxNivel()), BARRA_VIDA_JOGADOR_Y - 13.0f));
                    barraXP.setPosition(sf::Vector2f(posBarra.x + 10.0f, posBarra.y + tuboBarraXP.getSize().y / 2.0f - barraXP.getSize().y / 2.0f));
                }

                void Jogador1::atualizarExp() {
                    sf::Vector2f posBarraXP(tuboBarraXP.getPosition());

                   
                    textoExp.setPos(sf::Vector2f(posBarraXP.x + 10.0f, posBarraXP.y - textoExp.getTam().y - 10.0f));
                }

                void Jogador1::AtualizarNivel() {
                    sf::Vector2f posBarra = tuboBarraVida.getPosition();

                    
                    textoNivel.setPos(sf::Vector2f(posBarra.x + 10.0f, posBarra.y - textoNivel.getTam().y - 10.0f));
                }



                void Jogador1::AtualizarAnimacao() {
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
                void Jogador1::ativarFuria() {
                    if (podeUsarFuria()) {
                        emFuria = true;
                        tempoFuria = 0.0f;
                        arma->aumentarDano(20.0f); 
                        Corpo.setFillColor(sf::Color::Red); 
                    }
                }

                bool Jogador1::podeUsarFuria() const {
                    return tempoFuria >= cooldownFuria;
                }

                void Jogador1::atualizar() {
                    AtualizarAnimacao();

                    atualizarBarraVida();

                    atualizarBarraXP();

                    AtualizarNivel();

                    atualizarExp();
                    Jogador::atualizar(); 

                    if (emFuria) {
                        tempoFuria += pGrafico->getTempo();
                        if (tempoFuria >= duracaoFuria) {
                            emFuria = false;
                            tempoFuria = 0.0f; 
                            arma->resetarDano();
                            Corpo.setFillColor(corPadrao); 
                        }
                    }
                    else {
                        tempoFuria += pGrafico->getTempo(); 
                    }
                }
            }
        }
    }
}
