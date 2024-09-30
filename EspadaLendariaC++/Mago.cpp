#include "Mago.hpp"
#include "Projetil.hpp"

namespace EspadaLendaria {

    namespace Entidade {

        namespace Personagem {

            namespace Inimigo {

                Mago::Mago(const sf::Vector2f pos, const int nivel, const std::vector<Jogador::Jogador*>& jogadores, Item::Arma* arma) :
                    Inimigo(pos, sf::Vector2f(MAGO_TAMANHO_X, MAGO_TAMANHO_Y), jogadores, IDs::IDs::mago, MAGO_TEMPO_MORTE, MAGO_TEMPO_ATAQUE, MAGO_EXPERIENCIA* nivel * 0.5f)
                {
                    this->nivel.setNivel(nivel);
                    this->pontos = MAGO_PONTOS;
                    InicializarAnimacao();
                    InicializarNivel();
                }

                Mago::Mago(const std::vector<std::string>& atributos, const std::vector<Jogador::Jogador*>& jogadores) :
                    Inimigo(sf::Vector2f(std::stof(atributos[1]), std::stof(atributos[2])), sf::Vector2f(MAGO_TAMANHO_X, MAGO_TAMANHO_Y), jogadores, IDs::IDs::mago, MAGO_TEMPO_MORTE, MAGO_TEMPO_ATAQUE, std::stof(atributos[17]))
                {
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
                        const bool invisivelAtual = atributos[24] == "1";
                        const float tempoInvisivelAtual = std::stof(atributos[25]);

                        this->pontos = MAGO_PONTOS;
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
                        //this->invisivel = invisivelAtual;
                        //this->tempoInvisivel = tempoInvisivelAtual;

                        InicializarAnimacao();
                        animacao.setImgAtual(imgAtual);
                        animacao.setQuadroAtual(quadroAtual);
                        animacao.setTempoTotal(tempoTotalAtual);
                    }
                    catch (const std::exception& e) {
                        std::cerr << "ERRO::Mago::" << e.what() << std::endl;
                        podeRemover = true;
                    }

                }

                Mago::~Mago() {
                    if (arma != nullptr) {
                        arma->remover();
                    }
                    cont--;
                }

                void Mago::InicializarAnimacao() {
                    
                    const sf::Vector2f escala = sf::Vector2f(3.0f, 3.0f);
                    const sf::Vector2f origin = sf::Vector2f(
                        tam.x / 2.9f, // Centraliza horizontalmente
                        tam.y / 2.9f // Alinha os pés ao chão
                    );
                    //Creditos do Sprite ao LuizMelo
                    //https://luizmelo.itch.io/evil-wizard-3
                    animacao.addAnimacao("img/Personagem/Inimigo/Mago/Parado.png", "PARADO", 10, 0.1f, escala, origin);
                    animacao.addAnimacao("img/Personagem/Inimigo/Mago/Anda.png", "ANDA", 8, 0.12f, escala, origin);
                    animacao.addAnimacao("img/Personagem/Inimigo/Mago/Morre.png", "MORRE", 18, 0.1f, escala, origin);
                    animacao.addAnimacao("img/Personagem/Inimigo/Mago/Ataca.png", "ATACA", 13, 0.1f, escala, origin);
                }
                

                void Mago::ReceberDano(const float dano) {
                    if (!levandoDano ) {
                        vida -= dano * (dano / (dano + nivel.getDefesa()));
                        if (vida <= 0.0f) {
                            morrendo = true;
                            vida = 0.0f;
                        }
                        else {
                            levandoDano = true;
                            //invisivel = true;
                            Corpo.setFillColor(sf::Color(110, 110, 110, 110));
                        }
                        tempoDano = 0.0f;
                    }
                }

                



                bool Mago::Podermax()
                {
                    if (Podercheio == true)
                    {
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
                void Mago::setPoder()
                {
                    int a = rand() % 3;
                    if (a == 1)
                        Podercheio = true;
                    else
                    {
                        Podercheio = false;
                    }
                }
                Jogador::Jogador* Mago::escolherJogadorAlvo() {
                    Jogador::Jogador* alvo = nullptr;
                    float menorDistancia = std::numeric_limits<float>::max();

                    for (auto& jogador : jogadores) {
                        float distancia = std::hypot(pos.x - jogador->getPos().x, pos.y - jogador->getPos().y);
                        if (distancia < menorDistancia) {
                            menorDistancia = distancia;
                            alvo = jogador;
                        }
                    }

                    return alvo;
                }
                void Mago::MoverInimigo() {
                    if (!morrendo && !atacando) {
                        Jogador::Jogador* jogadorAlvo = escolherJogadorAlvo();
                        if (jogadorAlvo) {
                            sf::Vector2f posJogador = jogadorAlvo->getPos();
                            sf::Vector2f tamJogador = jogadorAlvo->getTam();
                            const float x = std::fabs((posJogador.x + tamJogador.x / 2.0f) - (pos.x + tam.x / 2.0f));
                            const float y = std::fabs((posJogador.y + tamJogador.y / 2.0f) - (pos.y + tam.y / 2.0f));

                            if (x <= MAGO_AREAALERTA_X && y <= MAGO_AREAALERTA_Y) {
                                // Atualiza paraEsquerda com base na posição do jogador
                                paraEsquerda = (posJogador.x < pos.x);
                                parar(); // Parar o movimento

                                if (arma) {
                                    Item::Projetil* projetil = dynamic_cast<Item::Projetil*>(arma);
                                    if (projetil->getColidiu()) {
                                        tempoAtacar += pGrafico->getTempo() * 0.5f;
                                        if (tempoAtacar > tempoAnimacaoAtacar) {
                                            atacando = true;
                                            tempoAtacar = 0.0f;
                                        }
                                    }
                                }
                            }
                            else {
                                atualizaMovimentoAleatorio();
                                tempoAtacar = 0.0f;
                            }
                        }
                        else {
                            // Resetar o movimento se estiver morrendo
                            tempoMover = 0.0f;
                        }

                        AtualizarTempoAtaque();
                    }
                }

                void Mago::AtualizarTempoAtaque() {
                    const float tempo = pGrafico->getTempo();
                    if (atacando) {
                        tempoAtacar += tempo;
                        if (tempoAtacar > tempoAnimacaoAtacar/1.5f) {
                            if (arma == nullptr) {
                                exit(1);
                            }

                            Item::Projetil* projetil = dynamic_cast<Item::Projetil*>(arma);
                            setPoder();
                            if (Podermax() == true) {
                                // Define a posição e a velocidade do projétil com base em paraEsquerda
                                projetil->setPos(sf::Vector2f(pos.x + (paraEsquerda ? -tam.x / 2.0f : tam.x / 2.0f), pos.y + tam.y / 5.0f));
                                projetil->setSentido(paraEsquerda); // Define o sentido aqui

                                projetil->setColidiu(false);
                                projetil->setVelocidade(sf::Vector2f(paraEsquerda ? -250.0f : 250.0f, 5.0f));

                                
                                tempoAtacar = 0.25f;
                            }
                            projetil->setPos(sf::Vector2f(pos.x + (paraEsquerda ? -tam.x / 2.0f : tam.x / 2.0f), pos.y + tam.y / 5.0f));
                            projetil->setSentido(paraEsquerda); // Define o sentido aqui

                            projetil->setColidiu(false);
                            projetil->setVelocidade(sf::Vector2f(paraEsquerda ? -250.0f : 250.0f, 5.0f));

                            atacando = false;
                            tempoAtacar = 0.0f;
                        }
                    }
                }



                void Mago::InicializarNivel() {
                    textoNivel.setString("Lv." + std::to_string(nivel.getNivel()));
                    textoNivel.setTamanhoBorda(2);
                    nivel.setForca(MAGO_FORCA);
                    nivel.setDefesa(MAGO_DEFESA);
                    nivel.setVitalidade(MAGO_VIDA);
                    if (arma != nullptr) {
                        setArma(arma);
                        arma->setDano(this->nivel.getForca());
                    }
                }

                const std::string Mago::salvar() {
                    std::string linha = salvarInimigo();
                    /* linha += std::to_string(invisivel) + ' ';
                     linha += std::to_string(tempoInvisivel);*/
                    return linha;
                }

                void Mago::AtualizarAnimacao() {
                    if (morrendo) {
                        animacao.atualizar(paraEsquerda, "MORRE");
                        tempoMorrer += pGrafico->getTempo();
                        if (tempoMorrer > tempoAnimacaoMorrer) {
                            if (arma != nullptr) {
                                Item::Projetil* projetil = dynamic_cast<Item::Projetil*>(arma);
                                if (projetil->getColidiu()) {
                                    arma->remover();
                                    arma = nullptr;
                                    podeRemover = true;
                                }
                                //tempoMorrer = 0.0f;
                                else {
                                    podeRemover = true;
                                }
                            }
                            Corpo.setFillColor(sf::Color::Transparent);
                            textoNivel.setCorTexto(sf::Color::Transparent);
                        }
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

            }

        }

    }

}