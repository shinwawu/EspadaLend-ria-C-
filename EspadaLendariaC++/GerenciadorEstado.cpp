#include "GerenciadorEstado.hpp"

namespace EspadaLendaria {

    namespace Gerenciador {

        GerenciadorEstado* GerenciadorEstado::pGerenciadorEstado = nullptr;

        GerenciadorEstado::GerenciadorEstado() :
            pilhaEstados()
        {

        }

        GerenciadorEstado* GerenciadorEstado::getGerenciadorEstado() {
            if (pGerenciadorEstado == nullptr) {
                pGerenciadorEstado = new GerenciadorEstado();
            }
            return pGerenciadorEstado;
        }

        GerenciadorEstado::~GerenciadorEstado() {
            //deleta todos os estados da minha pilha
            while (!pilhaEstados.empty()) {
                delete(pilhaEstados.top());
                pilhaEstados.top() = nullptr;
                pilhaEstados.pop();
            }

            if (pGerenciadorEstado) {
                delete(pGerenciadorEstado);
                pGerenciadorEstado = nullptr;
            }
        }

        void GerenciadorEstado::ativarObservadores() {
            //Ativa os observaores que estavam no estado atenrior
            Estado::Estado* estadoAtual = getEstadoAtual();

            //por enquanto...
            estadoAtual->mudarEstadoObservador();
        }


        void GerenciadorEstado::desativarObservadores() {
            //desativa os observaores que estavam no estado anterior
            Estado::Estado* estadoAtual = getEstadoAtual();

            //por enquanto...tem q arrumar
            estadoAtual->mudarEstadoObservador();
        }

        void GerenciadorEstado::addEstado(const IDs::IDs ID) {
            Estado::Estado* estado = nullptr;
            //estado = dynamic_cast<Estado::Estado*>(new Estado::EstadoMenu(ID));
            if (
                ID == IDs::IDs::estado_menu_carregar_jogo ||
                ID == IDs::IDs::estado_menu_colocacao ||
                ID == IDs::IDs::estado_menu_game_over ||
                ID == IDs::IDs::estado_menu_pausa ||
                ID == IDs::IDs::estado_menu_principal ||
                ID == IDs::IDs::estado_menu_salvar_jogada ||
                ID == IDs::IDs::estado_menu_fases1 || 
                ID == IDs::IDs::estado_menu_qntjogadores ||
                ID == IDs::IDs::estado_menu_fases2
                ) {
                estado = static_cast<Estado::Estado*>(new Estado::EstadoMenu(ID));
            }
            else if (
                ID == IDs::IDs::jogar_FasePrimeira1 ||
                ID == IDs::IDs::jogar_FasePrimeira2 ||
                ID == IDs::IDs::jogar_FaseSegunda1 ||
                ID == IDs::IDs::jogar_FaseSegunda2
                ) {
                estado = static_cast<Estado::Estado*>(new Estado::EstadoJogar(ID));
            }
            if (estado == nullptr) {
                std::cout << "ERROR::EspadaLendaria::Gerenciador::GerenciadorEstado::estado eh nullptr" << std::endl;
                exit(1);
            }
            if (!pilhaEstados.empty()) {
                desativarObservadores();
            }
            //arrumar...
            pilhaEstados.push(estado);
        }

        void GerenciadorEstado::removerEstado() {
            if (pilhaEstados.top() != nullptr && !pilhaEstados.empty()) {
                delete(pilhaEstados.top());
                pilhaEstados.top() = nullptr;
                pilhaEstados.pop();
            }
            if (!pilhaEstados.empty()) {
                ativarObservadores();
            }
            else {
                GerenciadorGrafico* pGrafico = pGrafico->getGerenciadorGrafico();
                pGrafico->fecharJanela();
            }
        }

        void GerenciadorEstado::removerEstado(const int qtd) {
            int i = 0;
            while (!pilhaEstados.empty() && i < qtd) {
                Estado::Estado* estado = pilhaEstados.top();
                if (estado != nullptr) {
                    delete(estado);
                    estado = nullptr;
                }
                pilhaEstados.pop();
                i++;
            }
            if (!pilhaEstados.empty()) {
                ativarObservadores();
            }
            else {
                GerenciadorGrafico* pGrafico = pGrafico->getGerenciadorGrafico();
                pGrafico->fecharJanela();
            }
        }

        Estado::Estado* GerenciadorEstado::getEstadoAtual() {
            if (!pilhaEstados.empty()) {
                return pilhaEstados.top();
            }
            return nullptr;
        }

        Estado::Estado* GerenciadorEstado::getEstado(const int qtdRemove) {
            std::stack<Estado::Estado*> pilhaEstadoAux = pilhaEstados;
            int i = 0;
            while (i < qtdRemove && !pilhaEstadoAux.empty()) {
                pilhaEstadoAux.pop();
                i++;
            }
            if (!pilhaEstadoAux.empty()) {
                return pilhaEstadoAux.top();
            }
            return nullptr;
        }

        void GerenciadorEstado::executar() {
            //executa o estado que est� no topo da minha pilha
            if (!pilhaEstados.empty()) {
                Estado::Estado* estado = pilhaEstados.top();
                estado->executar();
            }
        }

    }

}//Creditos ao Codigo Animacao do Monitor Giovane Limas Salvi
// Lido,Estudado e Adaptado para ser implementado ao Jogo Espada Lendaria