
#pragma once 

#include <SFML/Graphics.hpp>
#include "ListaEntidade.hpp"
#include <cmath>

namespace EspadaLendaria {

    namespace Gerenciador {

        class GerenciadorColisao {
        private:
            Lista::ListaEntidade* listaPersonagem;
            Lista::ListaEntidade* listaObstaculo;
        public:
            GerenciadorColisao(Lista::ListaEntidade* listaPersonagem, Lista::ListaEntidade* listaObstaculo);
            ~GerenciadorColisao();
            const sf::Vector2f calculaColisao(EspadaLendaria::Entidade::Entidade* ent1, EspadaLendaria::Entidade::Entidade* ent2); //coloquei o EspadaLendaria
            void executar();
        };

    }

}
//Creditos ao Codigo Animacao do Monitor Giovane Limas Salvi
// Lido,Estudado e Adaptado para ser implementado ao Jogo Espada Lendaria
