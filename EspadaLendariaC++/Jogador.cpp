#include "Jogador.hpp"
#include "ObservadorJogador.hpp"
#include "Inimigo.hpp"
#include "Vida.hpp"
#include "Projetil.hpp"
#include "Espinho.hpp"
#include "Jogador2.hpp"
#include <cmath>

namespace EspadaLendaria {
    namespace Entidade {
        namespace Personagem {
            namespace Jogador {

                Observador::ObservadorJogador* Jogador::pObservadorJogador = nullptr;

                Jogador::Jogador(const sf::Vector2f pos, Item::Arma* arma,IDs::IDs id) :
                    Personagem(pos, sf::Vector2f(JOGADOR_TAMANHO_X, JOGADOR_TAMANHO_Y), JOGADOR_VELOCIDADE, id, JOGADOR_TEMPO_MORTE, JOGADOR_TEMPO_RECEBERDANO),
                    noChao(false),
                    textoExp(pGrafico->carregarFonte("fonte/menuColocacao.ttf"), "", 20),
                    colidindoPorta(false), abrirPorta(false)

                {
                    if (pObservadorJogador != NULL && id == IDs::IDs::jogador1)
                    {
                        pObservadorJogador->setJogador1(this);
                    }
                    else if (pObservadorJogador == nullptr && id == IDs::IDs::jogador1)
                    {
                        pObservadorJogador = new Observador::ObservadorJogador(this, nullptr);
                    }
                    else if (id == IDs::IDs::jogador2 && pObservadorJogador != NULL)
                    {
                        pObservadorJogador->setJogador2(this);
                    }
                    else
                    {
                        pObservadorJogador->setJogador2(this);
                    }
                    this->pontos = 0;


                    inicializarBarraVida();
                    inicializarBarraXP();
                    InicializarNivel();
                    inicializarExp();

                    if (arma != nullptr) {
                        setArma(arma);
                        arma->setDano(nivel.getForca());
                    }

                    pGrafico->setLimiteObjeto(sf::IntRect(pos.x, pos.y, tam.x, tam.y));
                }

                Jogador::Jogador(const std::vector<std::string> atributos, IDs::IDs id) :
                    Personagem(pos, sf::Vector2f(JOGADOR_TAMANHO_X, JOGADOR_TAMANHO_Y), JOGADOR_VELOCIDADE, id, JOGADOR_TEMPO_MORTE, JOGADOR_TEMPO_RECEBERDANO),
                    noChao(false),
                    textoExp(pGrafico->carregarFonte("fonte/menuColocacao.ttf"), "", 20)
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
                        const bool noChaoAtual = atributos[18] == "1";
                        const bool colidindoPortaAtual = atributos[19] == "1";
                        const bool abrirPortaAtual = atributos[20] == "1";
                        const std::string imgAtual = atributos[21];
                        const unsigned int quadroAtual = std::stoi(atributos[22]);
                        const float tempoTotalAtual = std::stof(atributos[23]);
                        const unsigned int pontosAtual = std::stoi(atributos[24]);

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
                        this->pontos = pontosAtual;
                        nivel.setNivel(nivelAtual);
                        nivel.addExp(experienciaAtual);
                        InicializarNivel();
                        this->noChao = noChaoAtual;
                        this->colidindoPorta = colidindoPortaAtual;
                        this->abrirPorta = abrirPortaAtual;


                        inicializarBarraVida();
                        inicializarBarraXP();
                        inicializarExp();
                        animacao.setImgAtual(imgAtual);
                        animacao.setQuadroAtual(quadroAtual);
                        animacao.setTempoTotal(tempoTotalAtual);

                        pGrafico->setLimiteObjeto(sf::IntRect(pos.x, pos.y, tam.x, tam.y));
                    }
                    catch (const std::exception& e) {
                        std::cerr << e.what() << std::endl;
                        podeRemover = true;
                    }
                }
                Jogador::~Jogador() {
                    
                }

                void Jogador::addPontuacao(const unsigned int pontos) {
                    this->pontos += pontos;
                    pObservadorJogador->atualizarPontuacao(this->pontos);
                }
                void Jogador::inicializarBarraVida() {
                    sf::Vector2f tamTubo = sf::Vector2f(BARRA_VIDA_JOGADOR_X, BARRA_VIDA_JOGADOR_Y);
                    tuboBarraVida.setSize(tamTubo);
                    barraVida.setSize(tamTubo);
                    sf::Texture* texturaVida = new sf::Texture();
                    sf::Texture* texturaBarra = new sf::Texture();
                    texturaVida->loadFromFile("img/Personagem/Vida/VidaJogador.png");
                    texturaBarra->loadFromFile("img/Personagem/Vida/BarraVida.png");
                    barraVida.setTexture(texturaVida);
                    tuboBarraVida.setTexture(texturaBarra);
                }

                void Jogador::inicializarBarraXP() {
                    sf::Vector2f tamTubo = sf::Vector2f(BARRA_VIDA_JOGADOR_X, BARRA_VIDA_JOGADOR_Y);
                    tuboBarraXP.setSize(tamTubo);
                    sf::Texture* texturaXP = new sf::Texture();
                    sf::Texture* texturaBarra = new sf::Texture();
                    texturaXP->loadFromFile("img/Personagem/Vida/XPJogador.png");
                    texturaBarra->loadFromFile("img/Personagem/Vida/BarraXP.png");
                    barraXP.setTexture(texturaXP);
                    tuboBarraXP.setTexture(texturaBarra);
                }

                void Jogador::inicializarExp() {
                    std::string expAtual = std::to_string(nivel.getExp());
                    expAtual = expAtual.substr(0, expAtual.find(".") + 2);
                    std::string expProxNivel = std::to_string(nivel.getExpProxNivel());
                    expProxNivel = expProxNivel.substr(0, expProxNivel.find(".") + 2);
                    textoExp.setString(expAtual + "/" + expProxNivel);
                    textoExp.setTamanhoBorda(2);
                }

                void Jogador::InicializarNivel() {
                    textoNivel.setTamFonte(20);
                    textoNivel.setString("Lv." + std::to_string(nivel.getNivel()));
                    textoNivel.setTamanhoBorda(2);
                    nivel.setForca(JOGADOR_FORCA);
                    nivel.setDefesa(JOGADOR_DEFESA);
                    nivel.setVitalidade(JOGADOR_VIDA);
                }

                

                void Jogador::Colisao(Entidade* outraEntidade, sf::Vector2f ds) {
                    switch (outraEntidade->getID()) {
                    case(IDs::IDs::plataforma):
                    {

                    }
                    break;
                    case(IDs::IDs::espada_inimigo):
                    {
                        //std::cout << "Tomar dano do inimigo" << std::endl;
                        Item::Arma* arma = dynamic_cast<Item::Arma*>(outraEntidade);
                        if (ID == IDs::IDs::jogador2)
                        {
                            Jogador2* jogador2 = dynamic_cast<Jogador2*>(this);
                            if (jogador2) {
                                if (jogador2->getEsquiva()) {
                                    return;
                                }
                            }
                        }
                        ReceberDano(arma->getDano());
                    }
                    break;
                    case(IDs::IDs::garra):
                    {

                        Item::Arma* arma = dynamic_cast<Item::Arma*>(outraEntidade);
                        Jogador2* jogador2 = dynamic_cast<Jogador2*>(this);
                        if (jogador2) {
                            if (jogador2->getEsquiva()) {
                                return;
                            }
                        }
                        ReceberDano(arma->getDano());
                    }
                    break;
                    case(IDs::IDs::mago):
                    case(IDs::IDs::esqueleto):
                    case(IDs::IDs::boss):
                    {
                        Inimigo::Inimigo* inimigo = dynamic_cast<Inimigo::Inimigo*>(outraEntidade);
                        if (inimigo) {
                            sf::Vector2f posInimigo = inimigo->getPos();

                            
                            if (fabs(ds.x) < fabs(ds.y)) { 
                                if (pos.x < posInimigo.x) {
                                    pos.x = posInimigo.x - tam.x; 
                                    velFinal.x = -120.0f;
                                }
                                else {
                                    pos.x = posInimigo.x + inimigo->getTam().x; 
                                    velFinal.x = 120.0f;
                                }
                            }
                            else if (fabs(ds.y) < 0.1f) { 
                                if (pos.y < posInimigo.y) {
                                    pos.y = posInimigo.y - tam.y; 
                                    velFinal.y = 0;
                                    noChao = true; 
                                }
                                else {
                                    pos.y = posInimigo.y + inimigo->getTam().y; 
                                    velFinal.y = 0; 
                                }
                            }
                        
                            
                            
                        }
                        inimigo->parar();
                        inimigo->atacar(true);
                    }
                    break;
                    case (IDs::IDs::vida):
                    {
                        Item::Vida* vida = dynamic_cast<Item::Vida*>(outraEntidade);
                        setVida(vida->getVida());
                        vida->remover();
                    }
                    break;
                    case(IDs::IDs::magia):
                    {
                        Item::Projetil* projetil = dynamic_cast<Item::Projetil*>(outraEntidade);
                        Jogador2* jogador2 = dynamic_cast<Jogador2*>(this);
                        if (jogador2) {
                            if (jogador2->getEsquiva()) {
                                return;
                            }
                        }
                        ReceberDano(projetil->getDano());
                        projetil->setColidiu(true);
                    }

                    break;
                    case (IDs::IDs::espinho):
                    {
                        Obstaculo::Espinho* espinho = dynamic_cast<Obstaculo::Espinho*>(outraEntidade);
                        ReceberDano(espinho->getDano());
                        if (!morrendo) {
                            velFinal.y = -sqrt(2.0f * GRAVIDADE * PULO_TAMANHO);
                        }
                    }
                    break;

                    }
                    }
                
                void Jogador::pular() {
                    if (noChao) {
                        velFinal.y = -sqrt(2.0f * GRAVIDADE * PULO_TAMANHO);
                        noChao = false;
                        atacando = false;
                    }
                }

                const bool Jogador::getNoChao() const {
                    return noChao;
                }

                const bool Jogador::getAndando() const {
                    return andando;
                }

                void Jogador::setColidindoPorta(const bool colidindoPorta) {
                    this->colidindoPorta = colidindoPorta;
                }
                void Jogador::mudarEstadoObservador() {
                    pObservadorJogador->mudarEstadoAtivar();
                }

                const bool Jogador::getColidindoPorta() const {
                    return colidindoPorta;
                }

                void Jogador::setAbrirPorta(const bool abrirPorta) {
                    this->abrirPorta = abrirPorta;
                }

                const bool Jogador::getAbrirPorta() const {
                    return abrirPorta;
                }

                void Jogador::podePular() {
                    noChao = true;
                }

               

                void Jogador::addExperiencia(const float experiencia) {
                    nivel.addExp(experiencia);
                    textoNivel.setString("Lv." + std::to_string(nivel.getNivel()));
                    inicializarExp();
                }

                void Jogador::setVida(const float vida) {
                    this->vida += vida;
                    if (this->vida > 100.0f) {
                        this->vida = 100.0f;
                    }
                }

                const std::string Jogador::salvar() {
                    std::string linha = salvarPersonagem();
                    linha += std::to_string(noChao) + ' ';
                    linha += std::to_string(colidindoPorta) + ' ';
                    linha += std::to_string(abrirPorta) + ' ';
                    linha += animacao.getImgAtual() + ' ';
                    linha += std::to_string(animacao.getQuadroAtual()) + ' ';
                    linha += std::to_string(animacao.getTempoTotal()) + ' ';
                    linha += std::to_string(pontos);
                    return linha;
                }

                void Jogador::desenhar() {
                    pGrafico->desenhaElemento(Corpo);
                    pGrafico->desenhaElemento(tuboBarraVida);
                    pGrafico->desenhaElemento(barraVida);
                    pGrafico->desenhaElemento(textoNivel.getTexto());
                    pGrafico->desenhaElemento(tuboBarraXP);
                    pGrafico->desenhaElemento(barraXP);
                    pGrafico->desenhaElemento(textoExp.getTexto());
                }

                void Jogador::atualizar() {
                    atualizarPosicao();

                    if (atacando) {
                        sf::Vector2f tamEspada = arma->getTam();
                        const float posY = pos.y;
                        sf::Vector2f posEspada = (paraEsquerda ? sf::Vector2f(pos.x - tamEspada.x, pos.y) : sf::Vector2f(pos.x + tam.x, pos.y));
                        arma->setPos(posEspada);
                    }
                    else {
                        arma->setPos(sf::Vector2f(-1000.0f, -1000.0f));
                    }

 
                    colidindoPorta = false;
                }


                
            }
        }
    }
}
