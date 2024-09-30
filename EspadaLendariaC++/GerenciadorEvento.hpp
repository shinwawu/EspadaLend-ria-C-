#pragma once

#include "GerenciadorGrafico.hpp"
#include "Jogador.hpp"
#include "ListaObservador.hpp"

namespace EspadaLendaria {

    namespace Gerenciador {

        class GerenciadorEstado;

        class GerenciadorEvento {//padrão de projeto singleton
        private:
            static GerenciadorGrafico* pGrafico;
            static GerenciadorEstado* pGEstado;
            static Lista::ListaObservador* listaObservador;

            
            static GerenciadorEvento* pEvento;
            GerenciadorEvento();
        public:
            ~GerenciadorEvento();
            static GerenciadorEvento* getGerenciadorEvento();
            void addObservador(Observador::Observador* observador);
            void removerObservador(Observador::Observador* observador);
            void removerObservador(int pos);
            void executar();
        };

    }

}
//Creditos ao Codigo Animacao do Monitor Giovane Limas Salvi
// Lido,Estudado e Adaptado para ser implementado ao Jogo Espada Lendaria