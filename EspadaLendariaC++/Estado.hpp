#pragma once

#include "Ente.hpp"

namespace EspadaLendaria {

    namespace Estado {

        class Estado : public Ente {
        private:
            bool remover; //padrao de projeto state
        public:
            Estado(const IDs::IDs ID);
            virtual ~Estado();
            virtual void executar() = 0;
            virtual void desenhar();
            void setRemover(const bool remover = true);
            const bool getRemover() const;
            virtual void mudarEstadoObservador() = 0;
        };

    }

}
//Creditos ao Codigo Animacao do Monitor Giovane Limas Salvi
// Lido,Estudado e Adaptado para ser implementado ao Jogo Espada Lendaria