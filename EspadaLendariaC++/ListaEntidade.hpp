#pragma once

#include "Lista.hpp"
#include "Entidade.hpp"

namespace EspadaLendaria {

    namespace Lista {

        class ListaEntidade { //padrao de projeto facade
        private:
            Lista<EspadaLendaria::Entidade::Entidade> objListaEntidade; //coloquei o EspadaLendaria

        public:
            ListaEntidade();
            ~ListaEntidade();
            void addEntidade(EspadaLendaria::Entidade::Entidade* entidade); //coloquei o EspadaLendaria
            void addEntidade(EspadaLendaria::Entidade::Entidade* entidade, int pos); //coloquei o EspadaLendaria
            void removerEntidade(EspadaLendaria::Entidade::Entidade* entidade, const bool deletar = true); //coloquei o EspadaLendaria
            void removerEntidade(int pos, const bool deletar = true);
            const int getTam();
            EspadaLendaria::Entidade::Entidade* operator[](int pos); //coloquei o EspadaLendaria
            std::vector<EspadaLendaria::Entidade::Entidade*> getEntidades(const IDs::IDs ID); //coloquei o EspadaLendaria
            void limparLista();
            void executar();
            void desenharEntidades();
        };

    }

}
//Creditos ao Codigo Animacao do Monitor Giovane Limas Salvi
// Lido,Estudado para ser implementado ao Jogo Espada Lendaria