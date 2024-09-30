#include "FaseSegunda.hpp"

namespace EspadaLendaria {

	namespace Fase {

		FaseSegunda::FaseSegunda(const std::vector<std::string> vectorEntidades, const std::vector<std::string> vectorInfoFase, const IDs::IDs ID) :
			Fase(ID, IDs::IDs::fundo_FaseSegunda), numBosses(0){
			criarFundo();
			recuperarJogada(vectorEntidades, vectorInfoFase);
		}

		FaseSegunda::FaseSegunda(const IDs::IDs ID) :
			Fase(ID, IDs::IDs::fundo_FaseSegunda), numBosses(0) { 
			criarFundo();
			if (ID == IDs::IDs::fase_2_2jogadores) {
				jogadores2 = true; 
			}
			criarMapa(ID);
		}


		FaseSegunda::~FaseSegunda() {

		}

		void FaseSegunda::recuperarJogada(const std::vector<std::string> vectorEntidades, const std::vector<std::string> vectorInfoFase) {
			try {
				setPontuacao(std::stoi(vectorInfoFase[1]));
				textoTempo.setString(vectorInfoFase[2]);

				if (pJogador1 == nullptr && !vectorEntidades.empty()) {
					auto atributosJogador1 = getAtributosEntidade(vectorEntidades[0]);
					sf::Vector2f posJogador1(std::stof(atributosJogador1[1]), std::stof(atributosJogador1[2]));
					int nivelJogador1 = std::stoi(atributosJogador1[3]);
					criarPersonagem(IDs::IDs::jogador1, posJogador1, nivelJogador1);
				}

				if (pJogador2 == nullptr && vectorEntidades.size() > 1) {
					auto atributosJogador2 = getAtributosEntidade(vectorEntidades[1]);
					sf::Vector2f posJogador2(std::stof(atributosJogador2[1]), std::stof(atributosJogador2[2]));
					int nivelJogador2 = std::stoi(atributosJogador2[3]);
					criarPersonagem(IDs::IDs::jogador2, posJogador2, nivelJogador2);
				}
				setPontuacao(std::stoi(vectorInfoFase[1]));
				this->textoTempo.setString(vectorInfoFase[2]);
				std::vector<std::string> linhas = vectorEntidades;
				int i = 0;
				while (i < linhas.size()) {
					std::string linha = linhas[i];
					int id = std::stoi(linha.substr(0, linha.find(" ")));
					const std::vector<std::string> atributos = getAtributosEntidade(linhas[i]);
					switch (id)
					{
					case (5):
					{
						//criar 
						// com espada
						criarEntidade(IDs::IDs::esqueleto, atributos, getAtributosEntidade(linhas[i + 1]), true);
						i++;
					}
					break;
					case (7):
					{
						//criar mago com projetil
						criarEntidade(IDs::IDs::mago, atributos, getAtributosEntidade(linhas[i + 1]), true);
						i++;
					}
					break;
					case (8):
					{
						//cria plataforma
						criarEntidade(IDs::IDs::plataforma, atributos, {}, false);
					}
					break;
					case (12):
					{
						//criar vida
						criarEntidade(IDs::IDs::vida, atributos, {}, false);
					}
					break;
					case(44):
					{
						//criar plataforma
						criarEntidade(IDs::IDs::plataforma_movel, atributos, {}, false);
					}
					break;

					break;
					case(50):
					{
						criarEntidade(IDs::IDs::espinho, atributos, {}, false);
					}
					break;
					case (51):
						criarEntidade(IDs::IDs::boss, atributos, {}, true);

					}
					i++;
				}
			}
			catch (const std::exception& e) {
				std::cerr << e.what() << std::endl;
				exit(1);
			}
		}

		void FaseSegunda::setNumBosses(int b) {
			numBosses = b;
		}

		int FaseSegunda::getNumBosses() {
			return numBosses;
		}

		void FaseSegunda::criarFundo() {
			fundo.addCamada("img/Fase/FasePrimeira/layer_1.png", 0.0f);
			fundo.addCamada("img/Fase/FasePrimeira/layer_2.png", 0.1f);
		}

		void FaseSegunda::criarMapa(const IDs::IDs ID_Mapa) {
			sf::Vector2f tamJanela = pGrafico->getTamJanela();
			limiteCamera.left = -550.0f + tamJanela.x / 2.0f - 75.f;
			limiteCamera.top = 150.0f;
			limiteCamera.width = 500.0f - 50.0f;
			limiteCamera.height = tamJanela.y - 350.0f;
			pGrafico->setLimiteCamera(limiteCamera);

			//primeira parede
			for (int i = 1; i < 12; i++) {
				criarPlataforma(sf::Vector2f(-550.0f, i * 50.0f), sf::Vector2f(50.f, 50.0f), "parede");
			}

			//chão
			for (int i = -10; i < 10; i++) {
				criarPlataforma(sf::Vector2f(i * 50.0f, 550.0f), sf::Vector2f(50.0f, 50.0f), "padrao");
			}

			//segunda parede
			for (int i = 1; i < 12; i++) {
				criarPlataforma(sf::Vector2f(500.0f, i * 50.0f), sf::Vector2f(50.f, 50.0f), "parede");
			}

			//nascimento do jogador
			criarPersonagem(IDs::IDs::jogador1, sf::Vector2f(-400.0f, 250.0f));
			if (jogadores2 == true) {
				criarPersonagem(IDs::IDs::jogador2, sf::Vector2f(-300.0f, 250.0f));
			}

			//gerando esqueletos
			setNumEsqueletos(rand() % 3 + 3);
			int qntEsqueletos = getNumEsqueletos();
			for (int i = 0; i < qntEsqueletos; i++) {
				criarPersonagem(IDs::IDs::esqueleto, sf::Vector2f(100.0f + i * 50.0f, 0.0f), 1);
			}

			//gerando bosses
			setNumBosses(rand() % 2 + 1);
			int qntBosses = getNumBosses();
			for (int i = 0; i < qntBosses; i++) {
				criarPersonagem(IDs::IDs::boss, sf::Vector2f(200.0f + i * 40.0f, 250.0f), 1);
			}

			//gerando plataforma flutuante e plataforma movel
			setConjuntoDePlataformas(rand() % 2 + 1);
			int qntPlataformas = getConjuntoDePlataformas();
			int aux = (rand() % 2);
			for (int i = 0; i < qntPlataformas; i++) {
				criarPlataforma(sf::Vector2f(-400.0f + i * 150.0f, 400.0f), sf::Vector2f(80.0f, 50.0f), 150.0f, false);
				criarPlataforma(sf::Vector2f(200.0f + i * 150.0f, 400.0f), sf::Vector2f(80.0f, 50.0f), 160.0f, aux);
				if (i % 2 == 1){
					for (int j = 1; j <= 4; j++) {
						criarPlataforma(sf::Vector2f(j * 50.0f - 100.0f, 400.0f), sf::Vector2f(50.0f, 50.0f), "flutuante2");
					}
				}
				aux = (rand() % 2);

			}
		}

	}

}