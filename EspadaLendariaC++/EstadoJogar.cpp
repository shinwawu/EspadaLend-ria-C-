#include "EstadoJogar.hpp"
#include "Jogador1.hpp"
#include "Jogador2.hpp"
#include "FasePrimeira.hpp"
#include "FaseSegunda.hpp"
namespace EspadaLendaria {

    namespace Estado {

        EstadoJogar::EstadoJogar(const IDs::IDs ID) :
            Estado(ID), mapFase(), ID_FaseAtual(IDs::IDs::vazio)
        {

        }

        EstadoJogar::~EstadoJogar() {
            std::map<IDs::IDs, Fase::Fase*>::iterator it = mapFase.begin();
            Fase::Fase* fase = it->second;
            while (it != mapFase.end()) {
                fase = it->second;
                if (fase != nullptr) {
                    delete(fase);
                    fase = nullptr;
                }
                it++;
            }
            mapFase.clear();
            pGrafico->setLimiteCamera(sf::IntRect(-1, -1, -1, -1));
            pGrafico->setLimiteObjeto(sf::IntRect(-1, -1, -1, -1));
        }

        void EstadoJogar::criarFase(const std::string arquivoEntidades, std::vector<std::string> vectorInfoFase) {
            Gerenciador::GerenciadorArquivo GArquivo;
            std::vector<std::string> salvarEntidades = GArquivo.lerArquivo(arquivoEntidades.c_str());
            std::vector<std::string> salvarEntidadesAux;
            Fase::Fase* fase = nullptr;
            int i = 0;
            while (i < salvarEntidades.size()) {
                std::string linha = salvarEntidades[i];
                if (linha.find("=") != -1) {
                    int id = std::stoi(linha.substr(0, linha.find(' ') + 1));
                    linha = linha.erase(0, linha.find(' ') + 1);
                    sf::IntRect limiteCamera;
                    limiteCamera.left = std::stoi(linha.substr(0, linha.find(' ') + 1));
                    linha = linha.erase(0, linha.find(' ') + 1);
                    limiteCamera.width = std::stoi(linha.substr(0, linha.find(' ') + 1));
                    linha = linha.erase(0, linha.find(' ') + 1);
                    limiteCamera.top = std::stoi(linha.substr(0, linha.find(' ') + 1));
                    linha = linha.erase(0, linha.find(' ') + 1);
                    limiteCamera.height = std::stoi(linha.substr(0, linha.find(' ') + 1));
                    switch (id)
                    {
                    case (int(IDs::IDs::fase_1)):
                    {
                        fase = static_cast<Fase::Fase*>(new Fase::FasePrimeira(salvarEntidadesAux, vectorInfoFase, IDs::IDs::fase_1));
                        mapFase.insert(std::pair<IDs::IDs, Fase::Fase*>(IDs::IDs::fase_1, fase));
                        if (this->ID_FaseAtual == IDs::IDs::vazio) {
                            this->ID_FaseAtual = IDs::IDs::fase_1;
                        }
                    }
                    break;
                    case (int(IDs::IDs::fase_1_2jogadores)):
                    {
                        fase = static_cast<Fase::Fase*>(new Fase::FasePrimeira(salvarEntidadesAux, vectorInfoFase, IDs::IDs::fase_1_2jogadores));
                        mapFase.insert(std::pair<IDs::IDs, Fase::Fase*>(IDs::IDs::fase_1_2jogadores, fase));
                        if (this->ID_FaseAtual == IDs::IDs::vazio) {
                            this->ID_FaseAtual = IDs::IDs::fase_1_2jogadores;
                        }
                    }
                    break;
                    case(int(IDs::IDs::fase_2)):
                    {
                        fase = static_cast<Fase::Fase*>(new Fase::FasePrimeira(salvarEntidadesAux, vectorInfoFase, IDs::IDs::fase_2));
                        mapFase.insert(std::pair<IDs::IDs, Fase::Fase*>(IDs::IDs::fase_2, fase));
                        if (this->ID_FaseAtual == IDs::IDs::vazio) {
                            this->ID_FaseAtual = IDs::IDs::fase_2;
                        }
                    }
                    break;
                    case(int(IDs::IDs::fase_2_2jogadores)):
                    {
                        fase = static_cast<Fase::Fase*>(new Fase::FasePrimeira(salvarEntidadesAux, vectorInfoFase, IDs::IDs::fase_2_2jogadores));
                        mapFase.insert(std::pair<IDs::IDs, Fase::Fase*>(IDs::IDs::fase_2_2jogadores, fase));
                        if (this->ID_FaseAtual == IDs::IDs::vazio) {
                            this->ID_FaseAtual = IDs::IDs::fase_2_2jogadores;
                        }
                    }
                    break;
                    default:
                        std::cout << "EstadoJogar::Erro ao criar fase, pois o Id atual eh invalido" << std::endl;
                        exit(1);
                        break;
                    }
                    fase->setLimiteCamera(limiteCamera);
                    fase = nullptr;
                    salvarEntidadesAux.clear();
                }
                else {
                    salvarEntidadesAux.push_back(linha);
                }
                i++;
            }
            fase = mapFase[this->ID_FaseAtual];
            pGrafico->setLimiteCamera(fase->getLimiteCamera());
            EspadaLendaria::Entidade::Personagem::Jogador::Jogador* pJogador = fase->getJogador(); 
            if (pJogador != nullptr) {
                pGrafico->atualizarCamera(pJogador->getPos(), pJogador->getTam());
                pJogador = nullptr;
            }
            fase = nullptr;
        }

        void EstadoJogar::criarFase() {
            Fase::Fase* fase = nullptr;
            if (ID == IDs::IDs::jogar_FasePrimeira1) {
                fase = new Fase::FasePrimeira(IDs::IDs::fase_1);
                this->ID_FaseAtual = IDs::IDs::fase_1;
            }
            else if (ID == IDs::IDs::jogar_FasePrimeira2) {
                
                fase = new Fase::FasePrimeira(IDs::IDs::fase_1_2jogadores);
                fase->setJogadores2(true); // Set the flag to indicate 2 players
                this->ID_FaseAtual = IDs::IDs::fase_1_2jogadores;
            }
            else if (ID == IDs::IDs::jogar_FaseSegunda1) {
                fase = new Fase::FaseSegunda(IDs::IDs::fase_2);
                this->ID_FaseAtual = IDs::IDs::fase_2;
            }
            else if (ID == IDs::IDs::jogar_FaseSegunda2) {
                
                fase = new Fase::FaseSegunda(IDs::IDs::fase_2_2jogadores);
                fase->setJogadores2(true); // Set the flag to indicate 2 players
                this->ID_FaseAtual = IDs::IDs::fase_2_2jogadores;
            }

            if (fase != nullptr) {
                mapFase.insert(std::pair<IDs::IDs, Fase::Fase*>(ID_FaseAtual, fase));
            }
        }

        std::map<IDs::IDs, Fase::Fase*> EstadoJogar::getMapFase() {
            return mapFase;
        }

        const IDs::IDs EstadoJogar::getIDFaseAtual() const {
            return ID_FaseAtual;
        }

        Fase::Fase* EstadoJogar::getFase() {
            return mapFase[ID_FaseAtual];
        }

        void EstadoJogar::mudarEstadoObservador() {
            Fase::Fase* fase = mapFase[ID_FaseAtual]; // desativa os observadores dos jogadores
            EspadaLendaria::Entidade::Personagem::Jogador::Jogador* jogador = fase->getJogador();

            if (jogador != nullptr) {
                // verificar se o jogador é Jogador1
                EspadaLendaria::Entidade::Personagem::Jogador::Jogador1* jogador1 = dynamic_cast<EspadaLendaria::Entidade::Personagem::Jogador::Jogador1*>(jogador);
                if (jogador1 != nullptr) {
                    jogador1->mudarEstadoObservador();  
                    return;
                }

                // verificar se o jogador é Jogador2
                EspadaLendaria::Entidade::Personagem::Jogador::Jogador2* jogador2 = dynamic_cast<EspadaLendaria::Entidade::Personagem::Jogador::Jogador2*>(jogador);
                if (jogador2 != nullptr) {
                    jogador2->mudarEstadoObservador();  // chama o método específico de Jogador2
                    return;
                }
            }
        }
        void EstadoJogar::executar() {
            mapFase[ID_FaseAtual]->executar();
        }

    }

}