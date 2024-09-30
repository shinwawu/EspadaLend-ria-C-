#pragma once

#include "Elemento.hpp"

namespace EspadaLendaria {

    namespace Lista {

        template<class TIPO>
        class Lista { //padrao de projeto iterator
        private:
            Elemento<TIPO>* pInicio;
            Elemento<TIPO>* pUltimo;
            unsigned int tam;
        public:
            Lista();
            ~Lista();
            void addElemento(TIPO* elemento);
            void addElemento(TIPO* elemento, int pos);
            void removerElemento(TIPO* elemento, const bool deletar);
            void removerElemento(int pos, const bool deletar);
            int getTam();
            void limparLista();
            TIPO* operator[](int pos);
        };

        template<class TIPO>
        Lista<TIPO>::Lista() :
            pInicio(nullptr), pUltimo(nullptr), tam(0)
        {

        }

        template<class TIPO>
        Lista<TIPO>::~Lista() {
            //limparLista();
        }

        template<class TIPO>
        void Lista<TIPO>::addElemento(TIPO* elemento) {
            if (elemento == nullptr) {
                std::cout << "ERROR::Lista elemento eh nullptr" << std::endl;
                exit(1);
            }
            Elemento<TIPO>* novoElemento = new Elemento<TIPO>();
            if (novoElemento == nullptr) {
                std::cout << "ERROR::Lista aux eh nullptr" << std::endl;
                exit(1);
            }
            novoElemento->setElemento(elemento);
            if (pInicio == nullptr) {
                pInicio = novoElemento;
                pUltimo = novoElemento;
            }
            else {
                pUltimo->setProx(novoElemento);
                pUltimo = novoElemento;
            }
            tam++;
        }

        template<class TIPO>
        void Lista<TIPO>::addElemento(TIPO* elemento, int pos) {
            if (pos > tam || pos < 0) {
                std::cout << "ERRO::Lista::posicao nao eh compativel com o tamanho da lista" << std::endl;
                exit(1);
            }
            if (elemento == nullptr) {
                std::cout << "ERROR::Lista elemento eh nullptr" << std::endl;
                exit(1);
            }
            Elemento<TIPO>* novoElemento = new Elemento<TIPO>();
            if (novoElemento == nullptr) {
                std::cout << "ERROR::Lista novoElemento eh nullptr" << std::endl;
                exit(1);
            }
            novoElemento->setElemento(elemento);
            if (pInicio == nullptr) {
                pInicio = novoElemento;
                pUltimo = novoElemento;
            }
            else {
                Elemento<TIPO>* aux = pInicio;
                Elemento<TIPO>* aux2 = nullptr;
                for (int i = 0; i < pos; i++) {
                    aux2 = aux;
                    aux = aux->getProx();
                }
                if (aux2 == nullptr) {
                    novoElemento->setProx(aux);
                    pInicio = novoElemento;
                }
                else {
                    aux2->setProx(novoElemento);
                    novoElemento->setProx(aux);
                }
            }
            tam++;
        }

        template<class TIPO>
        void Lista<TIPO>::removerElemento(TIPO* elemento, const bool deletar) {
            if (elemento == nullptr) {
                std::cout << "ERROR::Lista elemento eh nullptr" << std::endl;
                exit(1);
            }
            Elemento<TIPO>* aux = pInicio;
            Elemento<TIPO>* aux2 = nullptr;
            while (aux != nullptr && aux->getElemento() != elemento) {
                aux2 = aux;
                aux = aux->getProx();
            }
            if (aux->getElemento() == elemento) {
                if (aux == pInicio) {
                    pInicio = aux->getProx();
                }
                else if (aux == pUltimo) {
                    pUltimo = aux2;
                }
                else {
                    aux2->setProx(aux->getProx());
                }
                if (deletar) {
                    delete(aux);
                    aux = nullptr;
                    aux2 = nullptr;
                }
                tam--;
            }

        }

        template<class TIPO>
        void Lista<TIPO>::removerElemento(int pos, const bool deletar) {
            TIPO* elemento = operator[](pos);
            return removerElemento(elemento, deletar);
        }

        template<class TIPO>
        int Lista<TIPO>::getTam() {
            return (int)tam;
        }

        template<class TIPO>
        TIPO* Lista<TIPO>::operator[](int pos) {
            if (pos >= (int)tam || pos < 0) {
                std::cout << "ERROR::Lista pos eh maior que o tamanho da lista" << std::endl;
                exit(1);
            }
            Elemento<TIPO>* aux = pInicio;
            for (int i = 0; i < pos; i++) {
                aux = aux->getProx();
            }
            return aux->getElemento();
        }

        template<class TIPO>
        void Lista<TIPO>::limparLista() {
            if (pInicio != nullptr) {
                Elemento<TIPO>* aux = pInicio;
                Elemento<TIPO>* aux2 = nullptr;
                int i = 0;
                while (aux != nullptr && i < tam) {
                    TIPO* elemento = aux->getElemento();
                    if (elemento != nullptr) {
                        delete(elemento);
                        elemento = nullptr;
                    }
                    aux2 = aux->getProx();
                    delete(aux);
                    aux = nullptr;
                    aux = aux2;
                    i++;
                }
            }
            pInicio = nullptr;
            pUltimo = nullptr;
            tam = 0;
        }

    }

}