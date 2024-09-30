#include "Estado.hpp"

namespace EspadaLendaria {

    namespace Estado {

        Estado::Estado(const IDs::IDs ID) :
            Ente(ID), remover(false)
        {

        }

        Estado::~Estado() {

        }

        void Estado::desenhar() {

        }

        void Estado::setRemover(const bool remover) {
            this->remover = remover;
        }

        const bool Estado::getRemover() const {
            return remover;
        }

    }

}//Creditos ao Codigo Animacao do Monitor Giovane Limas Salvi
// Lido,Estudado e Adaptado para ser implementado ao Jogo Espada Lendaria