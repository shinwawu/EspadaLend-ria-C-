#include "Inimigo.hpp"

namespace EspadaLendaria {

    namespace Entidade {

        namespace Personagem {

            namespace Inimigo {

                int Inimigo::cont(0);
                Inimigo::Inimigo(const sf::Vector2f pos, const sf::Vector2f tam, const std::vector<Jogador::Jogador*>& jogadores, const IDs::IDs ID, const float tempoMorrer, const float tempoAtacar, const float experiencia) :
                    Personagem(pos, tam, VELOCIDADE_INIMIGO, ID, tempoMorrer), jogadores(jogadores),
                    tempoMover(0.0f), tempoAnimacaoAtacar(tempoAtacar), tempoAtacar(0.0f),
                    experiencia(experiencia)
                {
                    cont++;
                    srand(time(NULL));
                    moveAleatorio = rand() % 3;
                    if (moveAleatorio == 0) {
                        parar();
                    }
                    else if (moveAleatorio == 1) {
                        andar(true);
                    }
                    else {
                        andar(false);
                    }
                    inicializarBarraVida();
                }

                Inimigo::~Inimigo() {
                    if (barraVida.getTexture()) {
                        delete(barraVida.getTexture());
                    }
                }

                void Inimigo::inicializarBarraVida() {
                    barraVida.setSize((sf::Vector2f(BARRA_VIDA_X, BARRA_VIDA_Y)));
                    sf::Texture* textura = new sf::Texture();
                    textura->loadFromFile("img/Personagem/Vida/VidaInimigo.png");
                    barraVida.setTexture(textura);
                }

                void Inimigo::atualizaMovimentoAleatorio() {
                    if (tempoMover > TEMPO_MOVER_ALEATORIO) {
                        moveAleatorio = rand() % 3;
                        if (moveAleatorio == 0) {
                            parar();
                        }
                        else if (moveAleatorio == 1) {
                            andar(true);
                        }
                        else {
                            andar(false);
                        }
                        tempoMover = 0.0f;
                    }
                }

                void Inimigo::AtualizarTempoAtaque() {
                    if (atacando && !levandoDano) {
                        tempoAtacar += pGrafico->getTempo();
                        if (tempoAtacar > tempoAnimacaoAtacar) {
                            atacando = false;
                            arma->setPos(sf::Vector2f(-1000.0f, -1000.0f));
                            tempoAtacar = 0.0f;
                        }
                        else if (tempoAtacar > tempoAnimacaoAtacar / 1.5f) {
                            arma->setPos(sf::Vector2f(-1000.0f, -1000.0f));
                        }
                        else if (tempoAtacar > tempoAnimacaoAtacar / 1.7f) {
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
                int Inimigo::getcont()
                {
                    return cont;
                }
                void Inimigo::MoverInimigo() {
                    if (!levandoDano && !morrendo && !atacando) {
                        sf::Vector2f posJogadorMaisProximo;
                        float distanciaMinima = std::numeric_limits<float>::max();
                        bool jogadorEncontrado = false;

                        for (auto& jogador : jogadores) {
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
                            fabs(posJogadorMaisProximo.y - getPos().y) <= RAIO_PERSEGUIR_Y) 
                        {
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

                const float Inimigo::getExperiencia() const {
                    return experiencia;
                }

                void Inimigo::atualizar() {
                    MoverInimigo();

                    atualizarPosicao();

                    tempoMover += pGrafico->getTempo();

                    AtualizarTempoAtaque();

                    AtualizarAnimacao();

                    atualizarBarraVida();

                    AtualizarNivel();
                }

                void Inimigo::AtualizarAnimacao() {
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

                const std::string Inimigo::salvarInimigo() {
                    std::string linha = salvarPersonagem();
                    linha += std::to_string(moveAleatorio) + ' ';
                    linha += std::to_string(tempoMover) + ' ';
                    linha += std::to_string(tempoAtacar) + ' ';
                    linha += animacao.getImgAtual() + ' ';
                    linha += std::to_string(animacao.getQuadroAtual()) + ' ';
                    linha += std::to_string(animacao.getTempoTotal()) + ' ';
                    return linha;
                }

                void Inimigo::ReceberDano(const float dano) {
                    if (!levandoDano) {
                        levandoDano = true;
                        andando = false;
                        vida -= dano * (dano / (dano + nivel.getDefesa()));
                        if (vida <= 0.0f) {
                            morrendo = true;
                            vida = 0.0f;
                        }
                        tempoDano = 0.0f;
                    }
                }

                void Inimigo::Colisao(Entidade* outraEntidade, sf::Vector2f ds) {
                    switch (outraEntidade->getID()) {
                    case (IDs::IDs::jogador):
                    {
                        std::cout << "Bate jogador e jogador pode bater no inimigo" << std::endl;
                    }
                    break;
                    case (IDs::IDs::jogador1):
                    {
                        Jogador::Jogador* jogador1 = dynamic_cast<Jogador::Jogador*>(outraEntidade);
                        if (jogador1) {
                            std::cout << "Colidiu com Jogador1, aplicando dano" << std::endl;
                             
                        }
                        
                    }
                    break;
                    case (IDs::IDs::jogador2):
                    {
                        // Verifica se a outra entidade é Jogador2
                        Jogador::Jogador* jogador2 = dynamic_cast<Jogador::Jogador*>(outraEntidade);
                        if (jogador2) {
                            std::cout << "Colidiu com Jogador2, aplicando dano" << std::endl;
                             
                        }
                    }
                    break;
                    case (IDs::IDs::minotauro):
                    {
                        //std::cout << "Empurra inimigo" << std::endl;
                    }
                    break;

                    case (IDs::IDs::esqueleto):
                    {

                    }
                    break;
                    case(IDs::IDs::espada_jogador):
                    {
                        std::cout << "Colidiu com o inimigo" << std::endl;
                    }
                    break;
                    }
                }
                void Inimigo::setcont()
                {
                    cont--;
                }

            }

        }

    }

}//Creditos ao Codigo Animacao do Monitor Giovane Limas Salvi
// Lido,Estudado e Adaptado para ser implementado ao Jogo Espada Lendaria
