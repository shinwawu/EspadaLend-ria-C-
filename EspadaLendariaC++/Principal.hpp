
#pragma once

//Gerenciador
#include "GerenciadorGrafico.hpp"
#include "GerenciadorEvento.hpp"

//Fases
#include "FasePrimeira.hpp"
#include "FaseSegunda.hpp"

#include "GerenciadorEstado.hpp"


namespace EspadaLendaria {
    //padrao facade e singleton
    class Principal {
        private:
            static Gerenciador::GerenciadorGrafico* pGrafico;
            static Gerenciador::GerenciadorEvento* pEvento;
            static Gerenciador::GerenciadorEstado* pGerenciadorEstado;

            void inicializa();
        public:
            Principal();
            ~Principal();
            void executar();
    };
    //Creditos ao Codigo Animacao do Monitor Giovane Limas Salvi
    // Lido,Estudado e Adaptado para ser implementado ao Jogo Espada Lendaria
}
