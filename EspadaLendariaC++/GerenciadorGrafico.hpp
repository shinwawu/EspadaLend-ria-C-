#pragma once 

#define TELA_X 800.0f
#define TELA_Y 600.0f

#include "Camera.hpp"

namespace EspadaLendaria {

    namespace Gerenciador {

        class GerenciadorGrafico {
        private:
            sf::RenderWindow* window;

            //movimentar a camera
            Camera camera;
            sf::Clock relogio;
            static float tempo;

            //a construtora privada faz parte do padr�o de projeto singleton
            static GerenciadorGrafico* pGrafico;
            GerenciadorGrafico();
        public:
            ~GerenciadorGrafico();
            static GerenciadorGrafico* getGerenciadorGrafico();
            sf::RenderWindow* getWindow();
            sf::Texture carregarTextura(const char* caminhoTextura);
            sf::Font carregarFonte(const char* caminhoFonte);
            void limpaJanela();
            void resetarRelogio();
            const float getTempo() const;
            void desenhaElemento(sf::RectangleShape Corpo);
            void desenhaElemento(sf::Text texto);
            void mostraElementos();
            void fecharJanela();
            const bool verificaJanelaAberta();
            void atualizarCamera(const sf::Vector2f pos);
            void atualizarCamera(const sf::Vector2f pos, sf::Vector2f tam);
            const sf::View getCamera();
            void resetarJanela();
            const sf::Vector2f getTamJanela() const;
            void setLimiteCamera(const sf::IntRect limiteCamera);
            void setLimiteObjeto(const sf::IntRect objeto);
        };

    }

}
//Creditos ao Codigo Animacao do Monitor Giovane Limas Salvi
// Lido,Estudado  para ser implementado ao Jogo Espada Lendaria