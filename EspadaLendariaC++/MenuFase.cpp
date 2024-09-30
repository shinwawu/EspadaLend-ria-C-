#include "MenuFase.hpp"

namespace EspadaLendaria {

	namespace Menu {

		MenuFase::MenuFase() :
			MenuPrincipal(IDs::IDs::menu_fases, "FASES", 100)
		{
			titulo.setCorTexto(sf::Color{ 255,0,0 });
			titulo.setPos(sf::Vector2f(tamJanela.x / 2.0f - titulo.getTam().x / 2.0f, 25.0f));
		}

		MenuFase::~MenuFase() {

		}

		void MenuFase::criarBotoes() {
			const float posBotaoX = tamJanela.x / 2.0f - tamBotao.x / 2.0f;
			addBotao("Fase 1", sf::Vector2f(posBotaoX, tamJanela.y / 2.0f), IDs::IDs::botao_fase_1, sf::Color{ 255, 0, 0 });
			addBotao("Fase 2", sf::Vector2f(posBotaoX, tamJanela.y / 2.0f + tamBotao.y * 1.2f), IDs::IDs::botao_fase_2, sf::Color{ 255, 0, 0 });
			addBotao("Voltar", sf::Vector2f(posBotaoX, tamJanela.y / 2.0f + tamBotao.y * 4.8f), IDs::IDs::botao_voltar, sf::Color{ 255, 0, 0 });
			inicializarIterator();
		}

		void MenuFase::executar() {
			posFundo = sf::Vector2f(posFundo.x + pGrafico->getTempo() * 80.0f, posFundo.y);
			pGrafico->atualizarCamera(sf::Vector2f(posFundo.x + tamJanela.x / 2.0f, posFundo.y + tamJanela.y / 2.0f));
			fundo.executar();
			pGrafico->resetarJanela();

			desenhar();
			pGrafico->desenhaElemento(titulo.getTexto());
		}
	}
}
