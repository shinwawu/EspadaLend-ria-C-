#pragma once

#include "Obstaculo.hpp"
#include "Personagem.hpp"

#define CAMINHO_TEXTURA_PLATAFORMA_PADRAO "img/Obstaculo/floor_tile_2.png"
#define CAMINHO_TEXTURA_PLATAFORMA_FLUTUANTE_1 "img/Obstaculo/Flutuante1.png"
#define CAMINHO_TEXTURA_PLATAFORMA_FLUTUANTE_2 "img/Obstaculo/floor_wood_3.png"
#define CAMINHO_TEXTURA_PAREDE "img/Obstaculo/wall_6.png"
#define ESCALA_PLATAFORMA_X 1
#define ESCALA_PLATAFORMA_Y 1
#define TAMANHO_PLATAFORMA_X 350.0f
#define TAMANHO_PLATAFORMA_Y 50.0f
#define TAMANHO_FLUTUANTE_X 80.0f
#define TAMANHO_FLUTUANTE_Y 40.0f

namespace EspadaLendaria {

    namespace Entidade {

        namespace Obstaculo {
            //padrao template method
            class Plataforma : public Obstaculo {
            protected:
                std::string type;
                sf::Vector2f escala;

                void InicializarAnimacao();
                const std::string salvarPlataforma();
            public:
                Plataforma(const IDs::IDs ID, const sf::Vector2f pos, const sf::Vector2f tam, const std::string type);
                Plataforma(const std::vector<std::string> atributos);
                ~Plataforma();
                void setEscala(const sf::Vector2f escala);
                virtual void Colisao(Entidade* outraEntidade, sf::Vector2f ds = sf::Vector2f(0.0f, 0.0f));
                virtual const std::string salvar();
            };

        }

    }
    //Creditos ao Codigo Animacao do Monitor Giovane Limas Salvi
    // Lido,Estudado e Adaptado para ser implementado ao Jogo Espada Lendaria
}