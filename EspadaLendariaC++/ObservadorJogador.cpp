#include "ObservadorJogador.hpp"
#include "EstadoJogar.hpp"
#include "Fase.hpp"
#include "Jogador.hpp"
#include "Jogador1.hpp"
#include "Jogador2.hpp"

namespace EspadaLendaria {

    namespace Observador {

        ObservadorJogador::ObservadorJogador(EspadaLendaria::Entidade::Personagem::Jogador::Jogador* pJoga1,
            EspadaLendaria::Entidade::Personagem::Jogador::Jogador* pJoga2) :
            Observador(), pJogador1(pJoga1), pJogador2(pJoga2)
        {
        }

        ObservadorJogador::~ObservadorJogador() {
            pJogador1 = nullptr;
            pJogador2 = nullptr;
        }

        void ObservadorJogador::teclaPressionada(const sf::Keyboard::Key tecla) {
            if (pJogador1 != NULL && !pJogador1->getMorrer()) {
                if (tecla == sf::Keyboard::A) {
                    pJogador1->andar(true);
                }
                else if (tecla == sf::Keyboard::D) {
                    pJogador1->andar(false);
                }
                else if (tecla == sf::Keyboard::W) {
                    pJogador1->pular();
                }
                else if (tecla == sf::Keyboard::S) {
                    if (pJogador1->getNoChao() && !pJogador1->getAndando()) {
                        pJogador1->atacar(true);
                    }
                }
                else if (tecla == sf::Keyboard::F) {
                    pJogador1->setAbrirPorta(true);
                }
                else if (tecla == sf::Keyboard::G) {  
                    dynamic_cast<EspadaLendaria::Entidade::Personagem::Jogador::Jogador1*>(pJogador1)->ativarFuria();
                }
            }

            if (pJogador2!=NULL && !pJogador2->getMorrer()) {
                if (tecla == sf::Keyboard::Left) {
                    pJogador2->andar(true);
                }
                else if (tecla == sf::Keyboard::Right) {
                    pJogador2->andar(false);
                }
                else if (tecla == sf::Keyboard::Up) {
                    pJogador2->pular();
                }
                else if (tecla == sf::Keyboard::Down) {
                    if (pJogador2->getNoChao() && !pJogador2->getAndando()) {
                        pJogador2->atacar(true);
                    }
                }
                else if (tecla == sf::Keyboard::K) {
                    pJogador2->setAbrirPorta(true);
                }
                else if (tecla == sf::Keyboard::L) {  
                    dynamic_cast<EspadaLendaria::Entidade::Personagem::Jogador::Jogador2*>(pJogador2)->ativarEsquiva();
                }
            }
        }

        void ObservadorJogador::teclaSolta(const sf::Keyboard::Key tecla) {
            if (pJogador1 !=NULL  && !pJogador1->getMorrer()) {
                if (tecla == sf::Keyboard::A || tecla == sf::Keyboard::D) {
                    pJogador1->parar();
                }
                else if (tecla == sf::Keyboard::W || tecla == sf::Keyboard::S) {
                    pJogador1->atacar(false);
                }
                else if (tecla == sf::Keyboard::K) {
                    pJogador1->setAbrirPorta(false);
                }
            }

            if (pJogador2 != NULL && !pJogador2->getMorrer()) {
                if (tecla == sf::Keyboard::Left || tecla == sf::Keyboard::Right) {
                    pJogador2->parar();
                }
                else if (tecla == sf::Keyboard::Down || tecla == sf::Keyboard::Up) {
                    pJogador2->atacar(false);
                }
                else if (tecla == sf::Keyboard::L) {
                    pJogador2->setAbrirPorta(false);
                }
            }
        }

        void ObservadorJogador::atualizarPontuacao(const unsigned int pontos) {
            Estado::Estado* estado = pGEstado->getEstadoAtual();
            if (estado->getID() == IDs::IDs::jogar_FasePrimeira1 || estado->getID() == IDs::IDs::jogar_FaseSegunda1 || estado->getID() == IDs::IDs::jogar_FaseSegunda2 || estado->getID() == IDs::IDs::jogar_FasePrimeira2) {
                Estado::EstadoJogar* estadoJogar = dynamic_cast<Estado::EstadoJogar*>(estado);
                Fase::Fase* fase = estadoJogar->getFase();
                if (fase == nullptr) {
                    std::cout << "ObservadorJogador::Fase eh nullptr" << std::endl;
                    exit(1);
                }
                fase->setPontuacao(pontos);
            }
        }

        void ObservadorJogador::setJogador2(EspadaLendaria::Entidade::Personagem::Jogador::Jogador* pJoga2) {
            pJogador2 = pJoga2;
        }
        void ObservadorJogador::setJogador1(EspadaLendaria::Entidade::Personagem::Jogador::Jogador* pJoga1) {
            pJogador1 = pJoga1;
        }

    }

}
