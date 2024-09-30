#include "Arma.hpp"
#include "Esqueleto.hpp"
#include "Mago.hpp"
#include "Boss.hpp"

namespace EspadaLendaria {

    namespace Entidade {

        namespace Item {

            Arma::Arma(const IDs::IDs ID, Personagem::Personagem* personagem) :
                Entidade(sf::Vector2f(-1000.0f, -1000.0f), ID), dano(0.0f), personagem(personagem)
            {
            }

            Arma::Arma(const IDs::IDs ID, const std::vector<std::string> atributos) :
                Entidade(sf::Vector2f(-1000.0f, -1000.0f), ID), dano(0.0f), personagem(nullptr)
            {
                try {
                    const sf::Vector2f posAtual = sf::Vector2f(std::stof(atributos[1]), std::stof(atributos[2]));
                    const sf::Vector2f tamAtual = sf::Vector2f(std::stof(atributos[3]), std::stof(atributos[4]));
                    const float danoAtual = std::stof(atributos[5]);

                    setPos(posAtual);
                    setTam(tamAtual);
                    this->dano = danoAtual;
                }
                catch (const std::exception& e) {
                    std::cerr << e.what() << std::endl;
                    //Generalizando a posição, tamanho e dano se algo der errado;
                    setPos(sf::Vector2f(-1000.0f, -1000.0f));
                    setTam(sf::Vector2f(50.0f, 90.0f));
                    dano = 20.0f;
                }

            }

            Arma::~Arma() {

            }

            const std::string Arma::salvarArma() {
                std::string linha = salvarEntidade();
                linha += std::to_string(dano) + ' ';
                return linha;
            }

            void Arma::setPersonagem(Personagem::Personagem* personagem) {
                this->personagem = personagem;
                dano = personagem->getForca();
            }

            void Arma::setDano(const float dano) {
                this->dano = dano;
            }

            const float Arma::getDano() const {
                return dano;
            }

            Personagem::Personagem* Arma::getPersona() {
                return personagem;
            }

            void Arma::aumentarDano(const float bonus) {
                dano += bonus;
            }

            void Arma::resetarDano() {
                dano = personagem->getForca();  // Reseta o dano base da arma
            }

            void Arma::Colisao(Entidade* outraEntidade, sf::Vector2f ds) {
                if (ID == IDs::IDs::espada_jogador || ID == IDs::IDs::espada_jogador2) {
                    if (
                        outraEntidade->getID() == IDs::IDs::esqueleto ||
                        outraEntidade->getID() == IDs::IDs::mago ||
                        outraEntidade->getID() == IDs::IDs::boss
                        ) {
                        if (outraEntidade->getID() == IDs::IDs::boss) {
                            Personagem::Inimigo::Boss* boss = dynamic_cast<Personagem::Inimigo::Boss*>(outraEntidade);

                            if (!boss->getMorrer()) { // Verifica se o boss ainda está vivo
                                if (boss->getDefender()) { // Verifica se o boss está em modo de defesa
                                    boss->setDefender(); // Reseta o estado de defesa, se necessário
                                    return; // Sai da função, o boss não recebe dano enquanto defende
                                }
                                
                                boss->ReceberDano(dano);
                                if (boss->getMorrer()) {
                                    Personagem::Jogador::Jogador* jogador = dynamic_cast<Personagem::Jogador::Jogador*>(personagem);
                                    jogador->addPontuacao(boss->getPontos());
                                    jogador->addExperiencia(boss->getExperiencia());
                                    boss->setcont();
                                    
                                    return;
                                }
                            }
                        }
                            Personagem::Inimigo::Inimigo* inimigo = dynamic_cast<Personagem::Inimigo::Inimigo*>(outraEntidade);
                        if (!inimigo->getMorrer()) {
                            inimigo->ReceberDano(dano);
                            if (inimigo->getMorrer()) {
                                Personagem::Jogador::Jogador* jogador = dynamic_cast<Personagem::Jogador::Jogador*>(personagem);
                                jogador->addPontuacao(inimigo->getPontos());
                                jogador->addExperiencia(inimigo->getExperiencia());
                                
                                inimigo->setcont();
                            }
                        }
                    }
                }

                else if (ID == IDs::IDs::espada_inimigo)
                {
                    if (outraEntidade->getID() == IDs::IDs::jogador1)
                    {
                        Personagem::Jogador::Jogador* jogador = dynamic_cast<Personagem::Jogador::Jogador*>(personagem);
                        if (jogador) {
                            jogador->ReceberDano(dano);
                        }
                    }
                    else if (outraEntidade->getID() == IDs::IDs::jogador2)
                    {
                        Personagem::Jogador::Jogador2* jogador2 = dynamic_cast<Personagem::Jogador::Jogador2*>(personagem);
                        if (jogador2) {
                            if (jogador2->getEsquiva()) {
                                return;
                            }
                            jogador2->ReceberDano(dano);
                        }
                    }
                }
                else if (ID == IDs::IDs::magia) {
                    if (outraEntidade->getID() == IDs::IDs::jogador|| outraEntidade->getID() == IDs::IDs::jogador1 || outraEntidade->getID() == IDs::IDs::jogador2) {
                        std::cout << "projetil colidiu com jogador" << std::endl;
                    }
                }
                else if (ID == IDs::IDs::garra) {
                    if (outraEntidade->getID() == IDs::IDs::jogador || outraEntidade->getID() == IDs::IDs::jogador1 || outraEntidade->getID() == IDs::IDs::jogador2) {
                        std::cout << "projetil colidiu com jogador" << std::endl;
                    }
                }
            }

            const std::string Arma::salvar() {
                std::string linha = salvarEntidade();
                linha += std::to_string(dano);
                return linha;
            }

            void Arma::atualizar() {

            }

            void Arma::desenhar() {

            }

        }

    }
}//Creditos ao Codigo Animacao do Monitor Giovane Limas Salvi
// Lido,Estudado e Adaptado para ser implementado ao Jogo Espada Lendaria