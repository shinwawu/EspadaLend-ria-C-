#pragma once

//Classe Base
#include "Ente.hpp"

//Fundo efeito Parallax
#include "Fundo.hpp"

//Gerenciadores
#include "GerenciadorColisao.hpp"
#include "GerenciadorArquivo.hpp"

//Listas
#include "ListaEntidade.hpp"

#include "Esqueleto.hpp"
#include "Mago.hpp"
#include "Projetil.hpp"
#include "Vida.hpp"
#include "PlataformaMovel.hpp"

#include "ObservadorFase.hpp"
#include "Espinho.hpp"
#include "Boss.hpp"

#include "Texto.hpp"

#include <fstream>
#include "Jogador1.hpp"
#include "Jogador2.hpp"
#define CAMINHO_FONTE_FASE "fonte/menuColocacao.ttf"

namespace EspadaLendaria {

    using namespace Entidade;
    using namespace Personagem;

    namespace Fase {

        class Fase : public Ente {
        private:
            static Observador::ObservadorFase* observadorFase;
            float tempo;
        protected:
            int numEsqueletos;
            int conjuntoDePlataformas;
            bool jogadores2;
            sf::IntRect limiteCamera;
            Lista::ListaEntidade* listaPersonagens;
            Lista::ListaEntidade* listaObstaculos;
            Gerenciador::GerenciadorArquivo GArquivo;
            Gerenciador::GerenciadorColisao* pColisao;
            Parallax::Fundo fundo;
            
            static Menu::Botao::Texto textoTempo;
            static unsigned int pontuacaoJogador;
            static Menu::Botao::Texto textoPontuacao;
            static EspadaLendaria::Entidade::Personagem::Jogador::Jogador1* pJogador1;
            static EspadaLendaria::Entidade::Personagem::Jogador::Jogador2* pJogador2;

            void criarPlataforma(const sf::Vector2f pos, const sf::Vector2f tam, const std::string type, const sf::Vector2f escala = sf::Vector2f(1.0f, 1.0f));
            void criarPlataforma(const sf::Vector2f pos, const sf::Vector2f tam, const float distancia, const bool horizontal);
           
            void criarVida(const sf::Vector2f pos);
            
            void criarPersonagem(const IDs::IDs ID, const sf::Vector2f pos, const int nivel = 1);
            void criarEntidade(const IDs::IDs ID, const std::vector<std::string> primeiro, const std::vector<std::string> segundo, const bool ehPersonagem);

            std::vector<std::string> getAtributosEntidade(std::string linha);

        public:
            Fase(const IDs::IDs ID_Fase, const IDs::IDs ID_Fundo);
            ~Fase();
            void setNumEsqueletos(int esq);
            int getNumEsqueletos();
            void setConjuntoDePlataformas(int p);
            int getConjuntoDePlataformas();
            void setJogadores2(bool p);
            virtual void criarFundo() = 0;  //padrao de projeto template method
            virtual void criarMapa(const IDs::IDs ID_Mapa) = 0;
            Jogador::Jogador* getJogador();
            Jogador::Jogador1* getJogador1();
            Jogador::Jogador2* getJogador2();
            void mudarEstadoObservador(); //padrao de projeto state
            void mudarFase(const IDs::IDs ID_Fase = IDs::IDs::vazio);
            void removerJogadorLista();
            const unsigned int getPontuacaoJogador() const;
            virtual void recuperarJogada(const std::vector<std::string> vectorEntidades, const std::vector<std::string> vectorInfoFase) = 0;
            void setPontuacao(const unsigned int pontuacaoJogador);
            void atualizarTempo();
            void atualizarPontuacao();
            const std::vector<std::string> salvarEntidades();
            void setLimiteCamera(sf::IntRect limiteCamera);
            const sf::IntRect getLimiteCamera() const;
            const std::string salvar();
            void executar();
            void desenhar();
        };

    }
    //Creditos ao Codigo Animacao do Monitor Giovane Limas Salvi
// Lido,Estudado e Adaptado para ser implementado ao Jogo Espada Lendaria

}