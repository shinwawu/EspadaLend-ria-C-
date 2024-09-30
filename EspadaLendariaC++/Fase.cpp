#include "Fase.hpp"
#include "Inimigo.hpp"
#include "Jogador1.hpp"
#include "Jogador2.hpp"

namespace EspadaLendaria {

    using namespace Entidade;
    using namespace Personagem;

    namespace Fase {

        EspadaLendaria::Entidade::Personagem::Jogador::Jogador1* Fase::pJogador1 = nullptr;
        EspadaLendaria::Entidade::Personagem::Jogador::Jogador2* Fase::pJogador2 = nullptr;

        Observador::ObservadorFase* Fase::observadorFase = nullptr;
        unsigned int Fase::pontuacaoJogador = 0;
        Menu::Botao::Texto Fase::textoPontuacao = Menu::Botao::Texto(pGrafico->carregarFonte(CAMINHO_FONTE_FASE), "", 32);
        Menu::Botao::Texto Fase::textoTempo = Menu::Botao::Texto(pGrafico->carregarFonte(CAMINHO_FONTE_FASE), "", 32);

        Fase::Fase(const IDs::IDs ID_Fase, const IDs::IDs ID_Fundo) :
            Ente(ID_Fase), fundo(ID_Fundo), listaPersonagens(new Lista::ListaEntidade()), listaObstaculos(new Lista::ListaEntidade()),
            pColisao(new Gerenciador::GerenciadorColisao(listaPersonagens, listaObstaculos)),
            GArquivo(), tempo(0.0f),jogadores2(false), numEsqueletos(0), conjuntoDePlataformas(0)
        {
            if (listaPersonagens == nullptr || listaObstaculos == nullptr) {
                std::cout << "EspadaLendaria::Fase::nao foi possivel criar lista de entidades na fase" << std::endl;
                exit(1);
            }

            if (pColisao == nullptr) {
                std::cout << "EspadaLendaria::Fase::nao foi possivel criar um Gerenciador de Colisao" << std::endl;
                exit(1);
            }

            if (observadorFase == nullptr) {
                observadorFase = new Observador::ObservadorFase();
            }

            observadorFase->setFase(this);
            if (textoPontuacao.getString() == "" && textoTempo.getString() == "") {
                textoPontuacao.setString("Pontos: 00000");
                textoPontuacao.setTamanhoBorda(2);
                textoTempo.setString("Tempo 00:00");
                textoTempo.setTamanhoBorda(2);
            }
        }

        Fase::~Fase() {
            if (pColisao != nullptr) {
                delete(pColisao);
                pColisao = nullptr;
            }
            if (observadorFase != nullptr) {
                delete(observadorFase);
                observadorFase = nullptr;
            }

            if (listaPersonagens != nullptr) {
                 
                listaPersonagens->limparLista();
                listaPersonagens = nullptr;
            }
            
            if (listaObstaculos != nullptr) {
                listaObstaculos->limparLista();
                listaObstaculos = nullptr;
            }

            if (pontuacaoJogador > 0) {
                pontuacaoJogador = 0;
                textoPontuacao.setString("");
                textoTempo.setString("");
            }

            pJogador1 = NULL;
            pJogador2 = NULL;
            
            while (EspadaLendaria::Entidade::Personagem::Inimigo::Inimigo::cont != 0)
            {
                EspadaLendaria::Entidade::Personagem::Inimigo::Inimigo::cont--;
            }
        }

        std::vector<std::string> Fase::getAtributosEntidade(std::string linha) {
            std::string espaco = " ";
            size_t pos = 0;
            std::vector<std::string> atributos;
            while ((pos = linha.find(espaco)) != std::string::npos) {
                atributos.push_back(linha.substr(0, pos));
                linha.erase(0, pos + espaco.length());
            }
            return atributos;
        }

        void Fase::criarPlataforma(const sf::Vector2f pos, const sf::Vector2f tam, const std::string type, const sf::Vector2f escala) {
            Obstaculo::Plataforma* plataforma = new Obstaculo::Plataforma(IDs::IDs::plataforma, pos, tam, type);
            if (plataforma == nullptr) {
                std::cout << "Fase::nao foi possivel criar plataforma" << std::endl;
                exit(1);
            }
            plataforma->setEscala(escala);
            listaObstaculos->addEntidade(static_cast<EspadaLendaria::Entidade::Entidade*>(plataforma)); 
        }

        void Fase::criarPlataforma(const sf::Vector2f pos, const sf::Vector2f tam, const float distancia, const bool horizontal) {
            Obstaculo::PlataformaMovel* plataformaMovel = new Obstaculo::PlataformaMovel(pos, distancia, tam, horizontal);
            if (plataformaMovel == nullptr) {
                std::cout << "Fase::nao foi possivel criar plataformaMovel" << std::endl;
                exit(1);
            }
            listaObstaculos->addEntidade(static_cast<EspadaLendaria::Entidade::Entidade*>(plataformaMovel));
        }



        void Fase::criarVida(const sf::Vector2f pos) {
            Item::Vida* vida = new Item::Vida(pos);
            if (vida == nullptr) {
                std::cout << "Fase::nao foi possivel criar vida" << std::endl;
                exit(1);
            }
            listaPersonagens->addEntidade(static_cast<EspadaLendaria::Entidade::Entidade*>(vida)); 
        }

        void Fase::criarPersonagem(const IDs::IDs ID, const sf::Vector2f pos, const int nivel) {
            EspadaLendaria::Entidade::Entidade* personagem = nullptr;
            EspadaLendaria::Entidade::Entidade* arma = nullptr;

            if (ID == IDs::IDs::jogador1) {
                if (pJogador1 == nullptr) {
                    Item::Arma* espadaJogador1 = new Item::Arma(IDs::IDs::espada_jogador);
                    if (espadaJogador1 == nullptr) {
                        std::cout << "Fase::nao foi possivel criar espada do jogador1" << std::endl;
                        exit(1);
                    }
                    pJogador1 = new Jogador::Jogador1(pos, espadaJogador1);
                    if (pJogador1 == nullptr) {
                        std::cout << "Fase::nao foi possivel criar jogador1" << std::endl;
                        exit(1);
                    }
                    personagem = static_cast<EspadaLendaria::Entidade::Entidade*>(pJogador1);
                    arma = static_cast<EspadaLendaria::Entidade::Entidade*>(espadaJogador1);
                }
                else
                {
                    std::cout << "erro ao criar jogador 1";
                }

            }
            else if (ID == IDs::IDs::jogador2)
            {
                if (pJogador2 == nullptr) {
                    Item::Arma* espadaJogador2 = new Item::Arma(IDs::IDs::espada_jogador2);
                    if (espadaJogador2 == nullptr) {
                        std::cout << "Fase::nao foi possivel criar espada do jogador2" << std::endl;
                        exit(1);
                    }
                    pJogador2 = new Jogador::Jogador2(pos, espadaJogador2);
                    if (pJogador2 == nullptr) {
                        std::cout << "Fase::nao foi possivel criar jogador2" << std::endl;
                        exit(1);
                    }
                    personagem = static_cast<EspadaLendaria::Entidade::Entidade*>(pJogador2);
                    arma = static_cast<EspadaLendaria::Entidade::Entidade*>(espadaJogador2);
                }
                else
                {
                    std::cout << "erro ao criar jogador 2";
                }
            }
            else {
                if (pJogador1 == nullptr && pJogador2 == nullptr) {
                    std::cout << "ERRO::Fase o ponteiro dos jogadores é nullptr" << std::endl;
                    exit(1);
                }

                std::vector<Jogador::Jogador*> jogadores;
                if (pJogador1) jogadores.push_back(pJogador1);
                if (pJogador2) jogadores.push_back(pJogador2);

                if (ID == IDs::IDs::esqueleto) {
                    EspadaLendaria::Entidade::Personagem::Inimigo::Esqueleto* esqueleto = new EspadaLendaria::Entidade::Personagem::Inimigo::Esqueleto(pos, nivel, jogadores);
                    if (esqueleto == nullptr) {
                        std::cout << "Fase::nao foi possivel criar esqueleto" << std::endl;
                        exit(1);
                    }
                    Item::Arma* espadaInimigo = new Item::Arma(IDs::IDs::espada_inimigo);
                    if (espadaInimigo == nullptr) {
                        std::cout << "Fase::nao foi possivel criar espada esqueleto" << std::endl;
                        exit(1);
                    }
                    esqueleto->setArma(espadaInimigo);
                    personagem = static_cast<EspadaLendaria::Entidade::Entidade*>(esqueleto);
                    arma = static_cast<EspadaLendaria::Entidade::Entidade*>(espadaInimigo);
                }
                else if (ID == IDs::IDs::mago) {
                    Inimigo::Mago* mago = new Inimigo::Mago(pos, nivel, jogadores);
                    if (mago == nullptr) {
                        std::cout << "Fase::nao foi possivel criar mago" << std::endl;
                        exit(1);
                    }
                    Item::Projetil* projetil = new Item::Projetil();
                    if (projetil == nullptr) {
                        std::cout << "Fase::nao foi possivel criar projetil" << std::endl;
                        exit(1);
                    }
                    mago->setArma(projetil);
                    projetil->InicializarAnimacao();
                    personagem = static_cast<EspadaLendaria::Entidade::Entidade*>(mago);
                    arma = static_cast<EspadaLendaria::Entidade::Entidade*>(projetil);
                }
                else if (ID == IDs::IDs::boss) {
                    Inimigo::Boss* boss = new Inimigo::Boss(pos, nivel, jogadores);
                    if (boss == nullptr) {
                        std::cout << "Fase::nao foi possivel criar boss" << std::endl;
                        exit(1);
                    }
                    Item::Arma* garras = new Item::Arma(IDs::IDs::garra);
                    if (garras == nullptr) {
                        std::cout << "Fase::nao foi possivel criar garras do boss" << std::endl;
                        exit(1);
                    }
                    boss->setArma(garras);
                    personagem = static_cast<EspadaLendaria::Entidade::Entidade*>(boss);
                    arma = static_cast<EspadaLendaria::Entidade::Entidade*>(garras);
                }
            }

            if (personagem != nullptr) {
                listaPersonagens->addEntidade(personagem);
                if (arma != nullptr) {
                    listaPersonagens->addEntidade(arma);
                }
            }
            else {
                std::cout << "Erro: Personagem não foi criado corretamente" << std::endl;
            }
        }

        void Fase::criarEntidade(const IDs::IDs ID, const std::vector<std::string> primeiro, const std::vector<std::string> segundo, const bool ehPersonagem) {
            if (ehPersonagem) {
                EspadaLendaria::Entidade::Entidade* personagem = nullptr;
                EspadaLendaria::Entidade::Entidade* arma = nullptr;

                if (ID == IDs::IDs::jogador1) {
                    if (pJogador1 == nullptr) {
                        pJogador1 = new Jogador::Jogador1(primeiro);
                        if (pJogador1 == nullptr) {
                            std::cout << "ERRO::Fase nao foi possivel criar jogador1" << std::endl;
                            exit(1);
                        }
                        Item::Arma* espadaJogador1 = new Item::Arma(IDs::IDs::espada_jogador, segundo);
                        if (espadaJogador1 == nullptr) {
                            std::cout << "Fase::nao foi possivel criar espada do jogador1" << std::endl;
                            exit(1);
                        }
                        pJogador1->setArma(espadaJogador1);
                        personagem = static_cast<EspadaLendaria::Entidade::Entidade*>(pJogador1);
                        arma = static_cast<EspadaLendaria::Entidade::Entidade*>(espadaJogador1);
                    }
                    else {
                        std::cout << "ERRO::já existem dois jogadores" << std::endl;
                        exit(1);
                    }
                }
                else if (ID == IDs::IDs::jogador2) {
                    if (pJogador2 == nullptr) {
                        pJogador2 = new Jogador::Jogador2(primeiro);
                        if (pJogador2 == nullptr) {
                            std::cout << "ERRO::Fase nao foi possivel criar jogador1" << std::endl;
                            exit(1);
                        }
                        Item::Arma* espadaJogador2 = new Item::Arma(IDs::IDs::espada_jogador2, segundo);
                        if (espadaJogador2 == nullptr) {
                            std::cout << "Fase::nao foi possivel criar espada do jogador1" << std::endl;
                            exit(1);
                        }
                        pJogador2->setArma(espadaJogador2);
                        personagem = static_cast<EspadaLendaria::Entidade::Entidade*>(pJogador2);
                        arma = static_cast<EspadaLendaria::Entidade::Entidade*>(espadaJogador2);
                    }
                    else {
                        if (pJogador1 == nullptr && pJogador2 == nullptr) {
                            std::cout << "ERRO::Fase o ponteiro dos jogadores eh nullptr" << std::endl;
                            exit(1);
                        }

                        Inimigo::Esqueleto* esqueleto = nullptr;
                        Inimigo::Mago* mago = nullptr;
                        Inimigo::Boss* boss = nullptr;

                        std::vector<Jogador::Jogador*> jogadores;
                        if (pJogador1) jogadores.push_back(pJogador1);
                        if (pJogador2) jogadores.push_back(pJogador2);
                        if (ID == IDs::IDs::esqueleto) {
                            esqueleto = new Inimigo::Esqueleto(primeiro, jogadores);
                            if (esqueleto == nullptr) {
                                std::cout << "Fase::esqueleto não criado" << std::endl;
                                exit(1);
                            }
                            Item::Arma* espadaInimigo = new Item::Arma(IDs::IDs::espada_inimigo, segundo);
                            if (espadaInimigo == nullptr) {
                                std::cout << "Fase::nao foi possivel criar espada do esqueleto" << std::endl;
                                exit(1);
                            }
                            esqueleto->setArma(espadaInimigo);
                            personagem = static_cast<EspadaLendaria::Entidade::Entidade*>(esqueleto);
                            arma = static_cast<EspadaLendaria::Entidade::Entidade*>(espadaInimigo);
                        }
                        else if (ID == IDs::IDs::mago) {
                            mago = new Inimigo::Mago(primeiro, jogadores);
                            if (mago == nullptr) {
                                std::cout << "Fase::mago não criado" << std::endl;
                                exit(1);
                            }
                            Item::Projetil* projetil = new Item::Projetil();
                            if (projetil == nullptr) {
                                std::cout << "Fase::não foi possível criar projetil" << std::endl;
                                exit(1);
                            }
                            mago->setArma(projetil);
                            projetil->InicializarAnimacao();
                            personagem = static_cast<EspadaLendaria::Entidade::Entidade*>(mago);
                            arma = static_cast<EspadaLendaria::Entidade::Entidade*>(projetil);
                        }
                        else if (ID == IDs::IDs::boss) {
                            boss = new Inimigo::Boss(primeiro, jogadores);
                            if (boss == nullptr) {
                                std::cout << "Fase::boss não criado" << std::endl;
                                exit(1);
                            }
                            Item::Arma* garras = new Item::Arma(IDs::IDs::garra, segundo);
                            if (garras == nullptr) {
                                std::cout << "Fase::não foi possível criar garras do boss" << std::endl;
                                exit(1);
                            }
                            boss->setArma(garras);
                            personagem = static_cast<EspadaLendaria::Entidade::Entidade*>(boss);
                            arma = static_cast<EspadaLendaria::Entidade::Entidade*>(garras);
                        }
                    }

                    if (personagem != nullptr) {
                        listaPersonagens->addEntidade(personagem);
                        if (arma != nullptr) {
                            listaPersonagens->addEntidade(arma);
                        }
                    }
                    else {
                        std::cout << "Erro: Personagem não foi criado corretamente" << std::endl;
                    }
                }
            }

        }

        Jogador::Jogador* Fase::getJogador() {
            for (int i = 0; i < listaPersonagens->getTam(); i++) {
                EspadaLendaria::Entidade::Entidade* ent = listaPersonagens->operator[](i); 
                if (ent->getID() == IDs::IDs::jogador) {
                    return dynamic_cast<Jogador::Jogador1*>(ent);
                }
            }
            return nullptr;
        }

        Jogador::Jogador1* Fase::getJogador1() {
            for (int i = 0; i < listaPersonagens->getTam(); i++) {
                EspadaLendaria::Entidade::Entidade* ent = listaPersonagens->operator[](i); 
                if (ent->getID() == IDs::IDs::jogador1) {
                    return dynamic_cast<Jogador::Jogador1*>(ent);
                }
            }
            return nullptr;
        }

        Jogador::Jogador2* Fase::getJogador2() {
            for (int i = 0; i < listaPersonagens->getTam(); i++) {
                EspadaLendaria::Entidade::Entidade* ent = listaPersonagens->operator[](i); 
                if (ent->getID() == IDs::IDs::jogador2) {
                    return dynamic_cast<Jogador::Jogador2*>(ent);
                }
            }
            return nullptr;
        }

        void Fase::mudarEstadoObservador() {
            observadorFase->mudarEstadoAtivar();
        }


        void Fase::removerJogadorLista() {
            if (pJogador1 != nullptr) {
                listaPersonagens->removerEntidade(static_cast<EspadaLendaria::Entidade::Entidade*>(pJogador1), false);
                listaPersonagens->removerEntidade(static_cast<EspadaLendaria::Entidade::Entidade*>(pJogador1->getArma()), false);
                pJogador1 = nullptr;  
            }

            
            if (pJogador2 != nullptr) {
                listaPersonagens->removerEntidade(static_cast<EspadaLendaria::Entidade::Entidade*>(pJogador2), false);
                listaPersonagens->removerEntidade(static_cast<EspadaLendaria::Entidade::Entidade*>(pJogador2->getArma()), false);
                pJogador2 = nullptr;  
            }
        }

        void Fase::desenhar() {
            fundo.executar();
            pGrafico->desenhaElemento(textoPontuacao.getTexto());
            pGrafico->desenhaElemento(textoTempo.getTexto());

            for (int i = 0; i < listaObstaculos->getTam(); i++) {
                EspadaLendaria::Entidade::Entidade* entidade = (*listaObstaculos)[i];
                if (entidade) {
                    auto id = static_cast<int>(entidade->getID());
                    
                    entidade->desenhar();
                }
            }

            for (int i = 0; i < listaPersonagens->getTam(); i++) {
                EspadaLendaria::Entidade::Entidade* entidade = (*listaPersonagens)[i];
                if (entidade) {
                    auto id = static_cast<int>(entidade->getID());
                   
                    entidade->desenhar();
                }
            }
        }










        const unsigned int Fase::getPontuacaoJogador() const {
            return pontuacaoJogador;
        }

        void Fase::setPontuacao(const unsigned int pontuacaoJogador) {
            this->pontuacaoJogador = pontuacaoJogador;
            std::string pontos = std::to_string(this->pontuacaoJogador);
            while (pontos.size() < 5) {
                std::string aux = pontos;
                pontos = '0' + aux;
            }
            textoPontuacao.setString("Pontos: " + pontos);
        }

        void Fase::atualizarTempo() {
            //atualiza posição e o tempo
            tempo += pGrafico->getTempo();
            if (tempo >= 1.0f) {
                tempo = 0.0f;
                std::string stringCortada = textoTempo.getString().substr(6);
                std::string novaString = "Tempo ";
                //int doisPontos = stringCortada.find(":");
                int minutos = std::stoi(stringCortada.substr(0, 2));
                int segundos = std::stoi(stringCortada.substr(3, 5));
                if (segundos >= 59) {
                    minutos++;
                    segundos = 0;
                    //novaString += std::to_string(minutos)
                }
                else {
                    segundos++;
                }
                if (minutos < 10) {
                    novaString += "0" + std::to_string(minutos);
                }
                else {
                    novaString += std::to_string(minutos);
                }
                if (segundos < 10) {
                    novaString += ":0" + std::to_string(segundos);
                }
                else {
                    novaString += ":" + std::to_string(segundos);
                }
                textoTempo.setString(novaString);
            }
            sf::Vector2f posFundo(pGrafico->getCamera().getCenter());
            textoTempo.setPos(sf::Vector2f(posFundo.x - textoTempo.getTam().x / 2.0f + 20.0f, posFundo.y - pGrafico->getTamJanela().y / 2.0f + 10.0f));
            pGrafico->desenhaElemento(textoTempo.getTexto());
        }

        void Fase::atualizarPontuacao() {
            sf::Vector2f posFundo(pGrafico->getCamera().getCenter());
            sf::Vector2f tamJanela(pGrafico->getTamJanela());
            textoPontuacao.setPos(sf::Vector2f(posFundo.x - tamJanela.x / 2.0f + 20.0f, posFundo.y - tamJanela.y / 2.0f + 10.0f));
            pGrafico->desenhaElemento(textoPontuacao.getTexto());
        }

        const std::string Fase::salvar() {
            std::string linha = "";
            linha += std::to_string(static_cast<int>(ID)) + ' ';
            linha += 10;
            linha += std::to_string(this->pontuacaoJogador) + ' ';
            linha += 10;
            linha += textoTempo.getString();
            return linha;
        }

        const std::vector<std::string> Fase::salvarEntidades() {
            std::vector<std::string> linhas;
            for (int i = 0; i < listaPersonagens->getTam(); i++) {
                EspadaLendaria::Entidade::Entidade* entidade = listaPersonagens->operator[](i); //coloquei o EspadaLendaria
                if (entidade != nullptr) {
                    std::string linha = entidade->salvar();
                    linhas.push_back(linha);
                }
            }
            for (int i = 0; i < listaObstaculos->getTam(); i++) {
                EspadaLendaria::Entidade::Entidade* entidade = listaObstaculos->operator[](i); //coloquei o EspadaLendaria
                if (entidade != nullptr) {
                    std::string linha = entidade->salvar();
                    linhas.push_back(linha);
                }
            }
            return linhas;
        }

        void Fase::setLimiteCamera(sf::IntRect limiteCamera) {
            this->limiteCamera = limiteCamera;
        }

        const sf::IntRect Fase::getLimiteCamera() const {
            return limiteCamera;
        }

        void Fase::setNumEsqueletos(int esq) {
            numEsqueletos = esq;
        }

        int Fase::getNumEsqueletos() {
            return numEsqueletos;
        }

        void Fase::setConjuntoDePlataformas(int p) {
            conjuntoDePlataformas = p;
        }

        int Fase::getConjuntoDePlataformas() {
            return conjuntoDePlataformas;
        }

        void Fase::setJogadores2(bool p)
        {
            jogadores2 = p;
        }

        void Fase::executar() {
            pJogador1 = getJogador1();
            pJogador2 = getJogador2();

            bool temJogador1 = (pJogador1 != nullptr);
            bool temJogador2 = (pJogador2 != nullptr);

            if (!jogadores2) {

                if (temJogador1) 
                {
                    
                    fundo.executar();

                    if (temJogador1) {
                        pGrafico->atualizarCamera(pJogador1->getPos(), pJogador1->getTam());
                    }

                    listaObstaculos->executar();
                    listaPersonagens->executar();

                    atualizarTempo();
                    atualizarPontuacao();

                    pColisao->executar();

                    if (EspadaLendaria::Entidade::Personagem::Inimigo::Inimigo::cont == 0)
                    {
                        observadorFase->notificarJogadorMorreu();
                        pJogador1 = nullptr;
                    }
                }
                else {
                    observadorFase->notificarJogadorMorreu();
                    pJogador1 = nullptr;
                }
            }
            else {

                if (temJogador1 || temJogador2) {
                    fundo.executar();

                    if (temJogador1) {
                        pGrafico->atualizarCamera(pJogador1->getPos(), pJogador1->getTam());
                    }
                    if (temJogador2) {
                        pGrafico->atualizarCamera(pJogador2->getPos(), pJogador2->getTam());
                    }

                    listaObstaculos->executar();
                    listaPersonagens->executar();

                    atualizarTempo();
                    atualizarPontuacao();
                    pColisao->executar();
                    if (EspadaLendaria::Entidade::Personagem::Inimigo::Inimigo::cont == 0)
                    {
                        observadorFase->notificarJogadorMorreu();
                        pJogador1 = nullptr;
                        pJogador2 = nullptr;
                    }
                }
                else {
                    observadorFase->notificarJogadorMorreu();
                    pJogador1 = nullptr;
                    pJogador2 = nullptr;
                }

            }
        }



    }
}