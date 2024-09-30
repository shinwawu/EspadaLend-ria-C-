#include "Esqueleto.hpp"

namespace EspadaLendaria {

    namespace Entidade {

        namespace Personagem {

            namespace Inimigo {

                Esqueleto::Esqueleto(const sf::Vector2f pos, const int nivel, const std::vector<Jogador::Jogador*>& jogadores) :
                    Inimigo(pos, sf::Vector2f(TAMANHO_ESQUELO_X, TAMANHO_ESQUELO_Y), jogadores, IDs::IDs::esqueleto, ESQUELETO_TEMPO_MORTE, 2.0f, ESQUELETO_EXPERIENCIA* nivel * 0.5f),
                    raiva(false), tempoRaiva(0.0f)
                {
                    this->nivel.setNivel(nivel);
                    this->pontos = ESQUELETO_PONTOS;
                    InicializarAnimacao();
                    InicializarNivel();
                }

                Esqueleto::Esqueleto(const std::vector<std::string> atributos, const std::vector<Jogador::Jogador*>& jogadores) :
                    Inimigo(
                        sf::Vector2f(0.0f, 0.0f),
                        sf::Vector2f(TAMANHO_ESQUELO_X, TAMANHO_ESQUELO_Y),
                        jogadores,
                        IDs::IDs::esqueleto,
                        ESQUELETO_TEMPO_MORTE,
                        2.0f,
                        ESQUELETO_EXPERIENCIA
                    ),
                    raiva(false), tempoRaiva(0.0f)
                {
                    this->pontos = ESQUELETO_PONTOS;
                    try {
                        const sf::Vector2f posAtual = sf::Vector2f(std::stof(atributos[1]), std::stof(atributos[2]));
                        const sf::Vector2f tamAtual = sf::Vector2f(std::stof(atributos[3]), std::stof(atributos[4]));
                        const sf::Vector2f velFinalAtual = sf::Vector2f(std::stof(atributos[5]), std::stof(atributos[6]));
                        const bool andandoAtual = atributos[7] == "1";
                        const bool paraEsquerdaAtual = atributos[8] == "1";
                        const bool levandoDanoAtual = atributos[9] == "1";
                        const bool atacandoAtual = atributos[10] == "1";
                        const bool morrendoAtual = atributos[11] == "1";
                        const float vidaAtual = std::stof(atributos[12]);
                        const float tempoDanoAtual = std::stof(atributos[13]);
                        const float tempoMorrerAtual = std::stof(atributos[14]);
                        const float dtAtual = std::stof(atributos[15]);
                        const float nivelAtual = std::stoi(atributos[16]);
                        const float experienciaAtual = std::stof(atributos[17]);
                        const short moveAleatorioAtual = std::stol(atributos[18]);
                        const float tempoMoverAtual = std::stof(atributos[19]);
                        const float tempoAtacarAtual = std::stof(atributos[20]);
                        const std::string imgAtual = atributos[21];
                        const unsigned int quadroAtual = std::stoi(atributos[22]);
                        const float tempoTotalAtual = std::stof(atributos[23]);
                        const bool raivaAtual = atributos[24] == "1";
                        const float tempoRaivaAtual = std::stof(atributos[25]);

                        setPos(posAtual);
                        setTam(tamAtual);
                        setVelFinal(velFinalAtual);
                        this->andando = andandoAtual;
                        this->paraEsquerda = paraEsquerdaAtual;
                        this->levandoDano = levandoDanoAtual;
                        this->atacando = atacandoAtual;
                        this->morrendo = morrendoAtual;
                        this->vida = vidaAtual;
                        this->tempoDano = tempoDanoAtual;
                        this->tempoMorrer = tempoMorrerAtual;
                        this->dt = dtAtual;
                        InicializarNivel();
                        nivel.setNivel(nivelAtual);
                        nivel.addExp(experienciaAtual);
                        this->moveAleatorio = moveAleatorioAtual;
                        this->tempoMover = tempoMoverAtual;
                        this->tempoAtacar = tempoAtacarAtual;
                        this->raiva = raivaAtual;
                        this->tempoRaiva = tempoRaivaAtual;

                        InicializarAnimacao();
                        animacao.setImgAtual(imgAtual);
                        animacao.setQuadroAtual(quadroAtual);
                        animacao.setTempoTotal(tempoTotalAtual);
                    }
                    catch (const std::exception& e)
                    {
                        std::cerr << e.what() << std::endl;
                        podeRemover = true;
                    }
                }

                Esqueleto::~Esqueleto() {
                    cont--;
                }

                void Esqueleto::InicializarAnimacao() {
                    sf::Vector2f escala(sf::Vector2f(2.f, 2.f));
                    sf::Vector2f origin(
                        tam.x / 3.f, // centraliza horizontalmente cada quadro
                        tam.y / 2.f // alinha a base do sprite ao chão
                    );
                    //Creditos da Sprite para https://www.behance.net/gallery/159947607/Free-Skeleton-Pixel-Art-Sprite-Sheets do Esqueleto
                    animacao.addAnimacao("img/Personagem/Inimigo/Esqueleto/Parado.png", "PARADO", 7, 0.1f, escala, origin);
                    animacao.addAnimacao("img/Personagem/Inimigo/Esqueleto/Anda.png", "ANDA", 8, 0.1f, escala, origin);
                    animacao.addAnimacao("img/Personagem/Inimigo/Esqueleto/Morre.png", "MORRE", 4, 0.1f, escala, origin);
                    animacao.addAnimacao("img/Personagem/Inimigo/Esqueleto/tomaDano.png", "TOMADANO", 2, 0.1f, escala, origin);
                    animacao.addAnimacao("img/Personagem/Inimigo/Esqueleto/Ataca.png", "ATACA", 4, 0.1f, escala, origin);
                    corPadrao = Corpo.getFillColor();
                    if (raiva) {
                        Corpo.setFillColor(sf::Color(180, 0, 0));
                    }
                }

                void Esqueleto::InicializarNivel() {
                    textoNivel.setString("Lv." + std::to_string(nivel.getNivel()));
                    textoNivel.setTamanhoBorda(2);
                    if (arma != nullptr) {
                        setArma(arma);
                        arma->setDano(this->nivel.getForca());
                    }
                }

                void Esqueleto::AtualizarRaiva() {
                    if (raiva) {
                        tempoRaiva += pGrafico->getTempo();
                        if (tempoRaiva > 8.0f) {
                            tempoRaiva = 0.0f;
                            Corpo.setFillColor(corPadrao);
                            raiva = false;
                        }
                    }
                }

                void Esqueleto::AtualizarAnimacao() {
                    if (morrendo) {
                        animacao.atualizar(paraEsquerda, "MORRE");
                        tempoMorrer += pGrafico->getTempo();
                        if (tempoMorrer > (tempoAnimacaoMorrer / 4.0f)) { 
                            podeRemover = true;
                            tempoMorrer = 0.0f;
                            if (arma != nullptr) {
                                arma->remover();
                            }
                        }
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

                void Esqueleto::AtualizarTempoAtaque() {
                    if (atacando && !levandoDano) {
                        tempoAtacar += pGrafico->getTempo();
                        if (tempoAtacar > tempoAnimacaoAtacar / 2.0f) {  
                            atacando = false;
                            arma->setPos(sf::Vector2f(-1000.0f, -1000.0f));
                            tempoAtacar = 0.0f;
                        }
                        else if (tempoAtacar > tempoAnimacaoAtacar / 3.0f) {  
                            arma->setPos(sf::Vector2f(-1000.0f, -1000.0f));
                        }
                        else if (tempoAtacar > tempoAnimacaoAtacar / 4.0f) {  
                            sf::Vector2f posEspada = (paraEsquerda ? sf::Vector2f(pos.x - arma->getTam().x / 2.0f, pos.y) : sf::Vector2f(pos.x + tam.x / 2.0f, pos.y));
                            arma->setPos(posEspada);
                        }
                    }
                    else if (levandoDano) {
                        tempoAtacar = 0.0f;
                        atacando = false;
                        if (arma != nullptr) {
                            arma->setPos(sf::Vector2f(-1000.0f, -1000.0f));
                        }
                    }
                }



                void Esqueleto::MoverInimigo() {
                    if (!levandoDano && !morrendo && !atacando) {
                        sf::Vector2f posJogadorMaisProximo;
                        float distanciaMinima = std::numeric_limits<float>::max();
                        bool jogadorEncontrado = false;

                        for (auto& jogador : jogadores) {
                            // verifica se o jogador está vivo
                            if (jogador->getMorrer()) {
                                continue; // pula para o próximo jogador se o atual estiver morto
                            }

                            sf::Vector2f posJogador = jogador->getPos();
                            sf::Vector2f posInimigo = getPos();
                            float distancia = sqrt(pow(posJogador.x - posInimigo.x, 2) + pow(posJogador.y - posInimigo.y, 2));

                            if (distancia < distanciaMinima) {
                                distanciaMinima = distancia;
                                posJogadorMaisProximo = posJogador;
                                jogadorEncontrado = true;
                            }
                        }

                        if (jogadorEncontrado && fabs(posJogadorMaisProximo.x - getPos().x) <= RAIO_PERSEGUIR_X &&
                            fabs(posJogadorMaisProximo.y - getPos().y) <= RAIO_PERSEGUIR_Y) {
                            if (posJogadorMaisProximo.x - getPos().x > 0.0f) {
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
                        tempoMover = 0.0f;
                    }
                }


                const std::string Esqueleto::salvar() {
                    std::string linha = salvarInimigo();
                    linha += (raiva ? "1" : "0") + ' ';
                    linha += std::to_string(tempoRaiva) + ' ';
                    return linha;
                }

                void Esqueleto::ReceberDano(const float dano) {
                    if (!levandoDano) {
                        levandoDano = true;
                        andando = false;
                        vida -= dano * (dano / (dano + nivel.getDefesa()));
                        if (vida <= 0.0f) {
                            morrendo = true;
                            vida = 0.0f;
                        }
                        tempoDano = 0.0f;
                        AtualizarRaiva();
                    }
                }

            }

        }

    }

}
