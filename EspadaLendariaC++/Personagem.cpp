#include "Personagem.hpp"
#include "Arma.hpp"

namespace EspadaLendaria {

    namespace Entidade {

        namespace Personagem {

            Personagem::Personagem(const sf::Vector2f pos, const sf::Vector2f tam, const float vel, const IDs::IDs ID, const float tempoMorrer, const float tempoDano) :
                Entidade(tam, ID, pos), andando(false), paraEsquerda(false),
                dt(0.0f), velFinal(sf::Vector2f(vel, 0.0f)), velMax(vel), atacando(false),
                animacao(&Corpo), tempoAnimacaoMorrer(tempoMorrer), tempoMorrer(0.0f),
                vidaMaxima(100.0f), vida(100.0f), tempoAnimacaoTomarDano(tempoDano), tempoDano(0.0f),
                morrendo(false), arma(nullptr), pontos(0), nivel(),
                textoNivel(pGrafico->carregarFonte("fonte/menuColocacao.ttf"), "", 15)
            {

            }

            Personagem::~Personagem() {

            }

            const unsigned int Personagem::getPontos() const {
                return pontos;
            }

            void Personagem::andar(const bool paraEsquerda) {
                atacando = false;
                andando = true;
                this->paraEsquerda = paraEsquerda;
            }

            void Personagem::parar() {
                andando = false;
            }

            void Personagem::atacar(const bool atacando) {
                this->atacando = atacando;
            }

            void Personagem::atualizarPosicao() {
                dt = pGrafico->getTempo();
                sf::Vector2f ds(0.0f, 0.0f);

                if (andando && !morrendo) {
                    ds.x = velFinal.x * dt;
                    if (paraEsquerda) {
                        ds.x *= -1;
                    }
                }

                const float Vy = velFinal.y;
                velFinal.y = velFinal.y + GRAVIDADE * dt;
                ds.y = Vy * dt + (GRAVIDADE * dt * dt) / 2.0f;

                setPos(sf::Vector2f(pos.x + ds.x, pos.y + ds.y));

                velFinal.x = velMax;

                atualizarTomarDano();

                desenhar();
            }

            void Personagem::setVelFinal(const sf::Vector2f velFinal) {
                this->velFinal = velFinal;
            }

            const sf::Vector2f Personagem::getVelFinal() const {
                return velFinal;
            }

            const bool Personagem::getMorrer() const {
                return morrendo;
            }

            void Personagem::setArma(Item::Arma* arma) {
                this->arma = arma;
                this->arma->setPersonagem(this);
                this->arma->setTam(tam);
                this->arma->setDano(nivel.getForca());
            }

            Item::Arma* Personagem::getArma() {
                return arma;
            }

            const float Personagem::getForca() const {
                return nivel.getForca();
            }

            void Personagem::atualizarTomarDano() {
                tempoDano += pGrafico->getTempo();
                if (levandoDano && tempoDano > tempoAnimacaoTomarDano) {
                    levandoDano = false;
                    tempoDano = 0.0f;
                }
            }

            void Personagem::ReceberDano(const float dano) {
                if (!levandoDano) {
                    levandoDano = true;
                    andando = false;
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

            void Personagem::atualizarBarraVida() {
                sf::Vector2f posBarraVida(sf::Vector2f(pos.x + tam.x / 2.0f - Corpo.getSize().x / 2.0f, pos.y - 20.0f));
                barraVida.setPosition(posBarraVida);
                barraVida.setSize(sf::Vector2f((vida / 100.0f) * BARRA_VIDA_X, BARRA_VIDA_Y));
            }

            void Personagem::AtualizarNivel() {
                sf::Vector2f posBarraVida = barraVida.getPosition();
                textoNivel.setPos(sf::Vector2f(posBarraVida.x - textoNivel.getTam().x, posBarraVida.y - textoNivel.getTam().y / 2.0f));
            }

            const std::string Personagem::salvarPersonagem() {
                std::string linha = salvarEntidade();
                linha += std::to_string(velFinal.x) + ' ';
                linha += std::to_string(velFinal.y) + ' ';
                linha += std::to_string(andando) + ' ';
                linha += std::to_string(paraEsquerda) + ' ';
                linha += std::to_string(levandoDano) + ' ';
                linha += std::to_string(atacando) + ' ';
                linha += std::to_string(morrendo) + ' ';
                linha += std::to_string(vida) + ' ';
                linha += std::to_string(tempoDano) + ' ';
                linha += std::to_string(tempoMorrer) + ' ';
                linha += std::to_string(dt) + ' ';
                linha += std::to_string(nivel.getNivel()) + ' ';
                linha += std::to_string(nivel.getExp()) + ' ';
                return linha;
            }

            void Personagem::desenhar() {
                pGrafico->desenhaElemento(Corpo);
                pGrafico->desenhaElemento(barraVida);
                pGrafico->desenhaElemento(textoNivel.getTexto());
            }

        }

    }

}//Creditos ao Codigo Animacao do Monitor Giovane Limas Salvi
// Lido,Estudado e Adaptado para ser implementado ao Jogo Espada Lendaria