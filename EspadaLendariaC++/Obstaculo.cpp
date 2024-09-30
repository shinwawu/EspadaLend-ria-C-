#include "Obstaculo.hpp"

namespace EspadaLendaria {

    namespace Entidade {

        namespace Obstaculo {

            Obstaculo::Obstaculo(const sf::Vector2f pos, const sf::Vector2f tam, const IDs::IDs ID) :
                Entidade(tam, ID, pos)
            {

            }

            Obstaculo::~Obstaculo() {

            }

            const std::string Obstaculo::salvarObstaculo() {
                std::string linha = salvarEntidade();
                return linha;
            }

            void Obstaculo::atualizar() {
                desenhar();
            }

            void Obstaculo::ColisaoObstaculo(sf::Vector2f ds, Personagem::Personagem* pPersonagem) {
                sf::Vector2f posOutro = pPersonagem->getPos();
                sf::Vector2f tamOutro = pPersonagem->getTam();
                sf::Vector2f velFinal = pPersonagem->getVelFinal();
                if (ds.x < 0.0f && ds.y < 0.0f) { 
                    if (ds.x > ds.y) {
                        if (posOutro.x < pos.x) { 
                            posOutro.x += ds.x;
                        }
                        else {
                            posOutro.x -= ds.x;
                        }
                        velFinal.x = 0.0f;
                    }
                    else {
                        if (posOutro.y < pos.y) { 
                            posOutro.y += ds.y;
                            if (pPersonagem->getID() == IDs::IDs::jogador1) {
                                Personagem::Jogador::Jogador1* pJogador = static_cast<Personagem::Jogador::Jogador1*>(pPersonagem);
                                pJogador->podePular();
                            }
                            else if (pPersonagem->getID() == IDs::IDs::jogador2) {
                                Personagem::Jogador::Jogador2* pJogador = static_cast<Personagem::Jogador::Jogador2*>(pPersonagem);
                                pJogador->podePular();
                            }
                        }
                        else {
                            posOutro.y -= ds.y;
                        }
                        velFinal.y = 0.0f;
                    }
                }
                pPersonagem->setPos(posOutro);
                pPersonagem->setVelFinal(velFinal);
            }

            const std::string Obstaculo::salvar() {
                std::string linha = salvarEntidade();
                return linha;
            }

        }

    }

}