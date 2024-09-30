#pragma once

#include "Menu.hpp"
#include "Texto.hpp"

#define CAMINHO_FONTE_CARD "fonte/menu.ttf"

namespace EspadaLendaria {

    namespace Menu {

        class FotoSalvar {
        private:
            sf::Texture* textura;
            sf::RectangleShape* Corpo;
            Botao::Texto textoInfo;
            const std::string caminhoArquivoEntidades;
            const std::string caminhoArquivoFase;
            const std::string caminhoImage;
            sf::Color cor;
            bool selecionado;
            bool existe;

            static Gerenciador::GerenciadorGrafico* pGrafico;
        public:
            FotoSalvar(const sf::Vector2f pos, const std::string caminhoArquivoEntidades, const std::string caminhoArquivoFase, const std::string caminhoImage);
            ~FotoSalvar();
            const std::string getCaminhoArquivoEntidades() const;
            const std::string getCaminhoArquivoFase() const;
            const std::string getCaminhoImage() const;
            void setColor(const sf::Color cor);
            void setSelecionado(const bool selecionado);
            const bool getSelecionado() const;
            const bool getExiste() const;
            void deletarTextura();
            void desenhar();
        };

    }

}//Creditos ao Codigo Animacao do Monitor Giovane Limas Salvi
// Lido,Estudado e Adaptado para ser implementado ao Jogo Espada Lendaria