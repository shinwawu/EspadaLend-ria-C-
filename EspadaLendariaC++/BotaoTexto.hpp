
#pragma once

#include "Botao.hpp"
#include "TextoAnimado.hpp"

#define CAMINHO_FONTE "fonte/menu.ttf"
#define TEMPO_TROCAR_COR 0.01f

namespace EspadaLendaria {

    namespace Menu {

        namespace Botao {

            class BotaoTexto : public Botao {
            protected:
                bool selecionado;
                sf::Color corSelecionado;
                TextoAnimado texto;

                const sf::Vector2f getTamTexto() const;
            public:
                BotaoTexto(const std::string info, const sf::Vector2f pos, const sf::Vector2f tam, const IDs::IDs ID, const sf::Color corSelecionado);
                virtual ~BotaoTexto();
                void AtualizarAnimacao();
                void atualizarPosicaoCaixa(const sf::Vector2f pos);
                void setSelecionado(bool selecionado);
                const bool getSelecionado() const;
                virtual void desenhar();

            };

        }

    }

}//Creditos ao Codigo Animacao do Monitor Giovane Limas Salvi
// Lido,Estudado e Adaptado para ser implementado ao Jogo Espada Lendaria
