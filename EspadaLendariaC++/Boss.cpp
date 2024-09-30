#include "Boss.hpp"

namespace EspadaLendaria {

    namespace Entidade {

        namespace Personagem {

            namespace Inimigo {

                Boss::Boss(const sf::Vector2f pos, const int nivel, const std::vector<Jogador::Jogador*>& jogadores) :
                    Inimigo(pos, sf::Vector2f(TAMANHO_BOSS_X, TAMANHO_BOSS_Y), jogadores, IDs::IDs::boss, 0.6f, 1.0f, 2000.0f),
                    raiva(false),
                    tempoRaiva(0.0f)
                {
                    this->nivel.setNivel(nivel);
                    this->pontos = 2000;
                    InicializarAnimacao();
                    InicializarNivel();
                }

                Boss::Boss(const std::vector<std::string> atributos, const std::vector<Jogador::Jogador*>& jogadores) :
                    Inimigo(sf::Vector2f(std::stof(atributos[1]), std::stof(atributos[2])), sf::Vector2f(TAMANHO_BOSS_X, TAMANHO_BOSS_Y), jogadores, IDs::IDs::boss, 0.6f, 1.0f, 2000.0f),
                    raiva(false)
                {
                    try {
                        // atributos da classe base Inimigo
                        setPos(sf::Vector2f(std::stof(atributos[1]), std::stof(atributos[2])));
                        setTam(sf::Vector2f(std::stof(atributos[3]), std::stof(atributos[4])));
                        setVelFinal(sf::Vector2f(std::stof(atributos[5]), std::stof(atributos[6])));
                        this->andando = atributos[7] == "1";
                        this->paraEsquerda = atributos[8] == "1";
                        this->levandoDano = atributos[9] == "1";
                        this->atacando = atributos[10] == "1";
                        this->morrendo = atributos[11] == "1";
                        this->vida = std::stof(atributos[12]);
                        this->tempoDano = std::stof(atributos[13]);
                        this->tempoMorrer = std::stof(atributos[14]);
                        this->dt = std::stof(atributos[15]);
                        this->nivel.setNivel(std::stoi(atributos[16]));
                        this->nivel.addExp(std::stof(atributos[17]));
                        this->moveAleatorio = std::stoi(atributos[18]);
                        this->tempoMover = std::stof(atributos[19]);
                        this->tempoAtacar = std::stof(atributos[20]);
                        this->raiva = atributos[24] == "1";
                        this->tempoRaiva = std::stof(atributos[25]);

                        InicializarAnimacao();
                        animacao.setImgAtual(atributos[21]);
                        animacao.setQuadroAtual(std::stoi(atributos[22]));
                        animacao.setTempoTotal(std::stof(atributos[23]));
                    }
                    catch (const std::exception& e) {
                        std::cerr << e.what() << std::endl;
                        podeRemover = true;
                    }
                }

                Boss::~Boss() {

                    cont--;

                }

                void Boss::InicializarAnimacao() {
                    sf::Vector2f escala(sf::Vector2f(2.5f, 2.5f));
                    sf::Vector2f origin(
                        tam.x/2.3f, // centraliza horizontalmente cada quadro
                        tam.y / 4.0f // alinha a base do sprite ao chão
                    );
                    //Creditos ao https://elthen.itch.io pela Sprite do Minotauro/Boss
                    animacao.addAnimacao("img/Personagem/Inimigo/Boss/anda.png", "ANDA", 5, 0.1f, escala, origin);
                    animacao.addAnimacao("img/Personagem/Inimigo/Boss/parado.png", "PARADO", 5, 0.1f, escala, origin);
                    animacao.addAnimacao("img/Personagem/Inimigo/Boss/ataca.png", "ATACA", 9, 0.1f, escala, origin);
                    animacao.addAnimacao("img/Personagem/Inimigo/Boss/morre.png", "MORRE", 6, 0.1f, escala, origin);
                    animacao.addAnimacao("img/Personagem/Inimigo/Boss/tomaDano.png", "TOMADANO", 3, 0.1f, escala, origin);
                    corPadrao = Corpo.getFillColor();
                    if (raiva) {
                        Corpo.setFillColor(sf::Color(180, 0, 0));
                    }
                }

                void Boss::InicializarNivel() {
                    textoNivel.setString("Lv." + std::to_string(nivel.getNivel()));
                    textoNivel.setTamanhoBorda(2);
                    if (arma != nullptr) {
                        setArma(arma);
                        arma->setDano(this->nivel.getForca());
                    }
                }

                void Boss::DefendeDano() {
                    int a = rand() % 5;
                    if (a == 1) {
                        defender = true;
                    }
                }

                bool Boss::getDefender() {
                    return defender;
                }

                void Boss::setDefender() {
                    defender = false;
                }

                void Boss::AtualizarAnimacao() {
                    if (morrendo) {
                        animacao.atualizar(paraEsquerda, "MORRE");
                        tempoMorrer += pGrafico->getTempo();
                        if (tempoMorrer > tempoAnimacaoMorrer) {
                            podeRemover = true;
                            tempoMorrer = 0.0f;
                            if (arma != nullptr) {
                                arma->remover();
                            }
                        }
                    }
                    else if (levandoDano && !raiva) {
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

                void Boss::ReceberDano(const float dano) {
                    if (!levandoDano) {
                        levandoDano = true;
                        if (!raiva && (vida / 2 < 50.0)) {
                            Corpo.setFillColor(sf::Color(180, 0, 0));
                            raiva = true;
                        }
                        vida -= dano * (dano / (dano + nivel.getDefesa()));
                        if (vida <= 0.0f) {
                            morrendo = true;
                            vida = 0.0f;
                            if (arma != nullptr) {
                                arma->remover();
                            }
                        }
                        tempoDano = 0.0f;
                    }
                }

                const std::string Boss::salvar() {
                    std::string linha = salvarInimigo();
                    linha += std::to_string(raiva) + ' ';
                    linha += std::to_string(tempoRaiva);
                    return linha;
                }

                void Boss::AtualizarTempoAtaque() {
                    if (atacando && (raiva || !levandoDano)) {
                        tempoAtacar += pGrafico->getTempo();
                        if (tempoAtacar > tempoAnimacaoAtacar / 2.0f) {  
                            atacando = false;
                            if (arma) {
                                arma->setPos(sf::Vector2f(-1000.0f, -1000.0f));
                            }
                            tempoAtacar = 0.0f;
                        }
                        else if (tempoAtacar > tempoAnimacaoAtacar / 3.0f) {  
                            if (arma) {
                                arma->setPos(sf::Vector2f(-1000.0f, -1000.0f));
                            }
                        }
                        else if (tempoAtacar > tempoAnimacaoAtacar / 4.0f) {  
                            if (arma) {
                                sf::Vector2f posEspada = (paraEsquerda ? sf::Vector2f(pos.x - arma->getTam().x / 2.0f, pos.y) : sf::Vector2f(pos.x + tam.x / 2.0f, pos.y));
                                arma->setPos(posEspada);
                            }
                        }
                    }
                    else if (levandoDano && !raiva) {
                        tempoAtacar = 0.0f;
                        atacando = false;
                        if (arma) {
                            arma->setPos(sf::Vector2f(-1000.0f, -1000.0f));
                        }
                    }
                }


                void Boss::MoverInimigo() {
                    if ((raiva || !levandoDano) && !morrendo && !atacando) {
                        sf::Vector2f posJogador = { 0.0f, 0.0f };
                        float distanciaMinima = std::numeric_limits<float>::max();

                        // encontrar o jogador mais próximo
                        for (const auto& jogador : jogadores) {
                            if (jogador->getMorrer()) {
                                // se o jogador estiver morto, continue para o próximo
                                continue;
                            }

                            sf::Vector2f posJogadorTemp = jogador->getPos();
                            float distancia = std::sqrt(std::pow(posJogadorTemp.x - pos.x, 2) + std::pow(posJogadorTemp.y - pos.y, 2));
                            if (distancia < distanciaMinima) {
                                distanciaMinima = distancia;
                                posJogador = posJogadorTemp;
                            }
                        }

                        // se um jogador vivo foi encontrado
                        if (distanciaMinima < std::numeric_limits<float>::max()) {
                            sf::Vector2f posInimigo = getPos();
                            if (fabs(posJogador.x - posInimigo.x) <= RAIO_PERSEGUIR_X && fabs(posJogador.y - posInimigo.y) <= RAIO_PERSEGUIR_Y) {
                                if (posJogador.x - posInimigo.x > 0.0f) {
                                    andar(false);
                                }
                                else {
                                    andar(true);
                                }
                            }
                            else {
                                atualizaMovimentoAleatorio();
                            }
                        }
                        else {
                            // nenhum jogador vivo foi encontrado, parar movimento ou realizar outra ação
                            atualizaMovimentoAleatorio();
                        }
                    }
                    else {
                        tempoMover = 0.0f;
                    }
                }


            }

        }

    }

}
