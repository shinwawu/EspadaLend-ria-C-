#include "FasePrimeira.hpp"

namespace EspadaLendaria {

	namespace Fase {

		FasePrimeira::FasePrimeira(const std::vector<std::string> vectorEntidades, const std::vector<std::string> vectorInfoFase, const IDs::IDs ID) :
			Fase(ID, IDs::IDs::fundo_FasePrimeira), numMagos(0) {
			criarFundo();
			recuperarJogada(vectorEntidades, vectorInfoFase);
		}

		FasePrimeira::FasePrimeira(const IDs::IDs ID) :
			Fase(ID, IDs::IDs::fundo_FasePrimeira), numMagos(0) {
			criarFundo();
			criarMapa(ID);
		}

		FasePrimeira::~FasePrimeira() {
		}

		void FasePrimeira::recuperarJogada(const std::vector<std::string> vectorEntidades, const std::vector<std::string> vectorInfoFase) {
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
				
				for (size_t i = 0; i < vectorEntidades.size(); ++i) {
					std::string linha = vectorEntidades[i];
					int id = std::stoi(linha.substr(0, linha.find(" ")));
					const std::vector<std::string> atributos = getAtributosEntidade(linha);
					
					switch (id)
					{
					case (5): // Esqueleto
						criarEntidade(IDs::IDs::esqueleto, atributos, getAtributosEntidade(vectorEntidades[i + 1]), true);
						break;

					case (7): // Mago
						criarEntidade(IDs::IDs::mago, atributos, getAtributosEntidade(vectorEntidades[i + 1]), true);
						break;

					case (8): // Plataforma
						criarEntidade(IDs::IDs::plataforma, atributos, {}, false);
						break;

					case (12): // Vida
						criarEntidade(IDs::IDs::vida, atributos, {}, false);
						break;

					case (44): // Plataforma móvel
						criarEntidade(IDs::IDs::plataforma_movel, atributos, {}, false);
						break;

					case (50): // Espinho
						criarEntidade(IDs::IDs::espinho, atributos, {}, false);
						break;

					case (51): // Boss
						criarEntidade(IDs::IDs::boss, atributos, {}, true);
						break;

					case (62): // Jogador 1
						
						break;

					case (2): // Espada do Jogador
						criarEntidade(IDs::IDs::espada_jogador, atributos, {}, false);
						
						break;

					default:
						
						break;
					}
				}
			}
			

			catch (const std::exception& e) {
				std::cerr << "Erro ao recuperar jogada: " << e.what() << std::endl;
				exit(1);
			}
		}



		void FasePrimeira::setNumMagos(int m) {
			numMagos = m;
		}

		int FasePrimeira::getNumMagos() {
			return numMagos;
		}

		void FasePrimeira::setNumEspinhos(int e) {
			numEspinhos = e;
		}

		int FasePrimeira::getNumEspinhos() {
			return numEspinhos;
		}

		void FasePrimeira::criarEspinho(const sf::Vector2f pos, const sf::Vector2f tam) {
			Obstaculo::Espinho* espinho = new Obstaculo::Espinho(pos, tam);
			if (espinho == nullptr) {
				std::cout << "Fase::nao foi possivel criar espinhos" << std::endl;
				exit(1);
			}
			listaObstaculos->addEntidade(static_cast<EspadaLendaria::Entidade::Entidade*>(espinho)); 
		}

		void FasePrimeira::criarFundo() {
			fundo.addCamada("img/Fase/FasePrimeira/layer_1.png", 0.0f);
			fundo.addCamada("img/Fase/FasePrimeira/layer_2.png", 0.1f);
		}

		void FasePrimeira::criarMapa(const IDs::IDs ID_Mapa) {
			switch (ID_Mapa)
			{
			case (IDs::IDs::fase_1):
			{
				criarMapa();
			}
			break;
			case (IDs::IDs::fase_1_2jogadores):
			{
				jogadores2 = true;
				criarMapa();
			}
			break;
			default:
			{
				
				exit(1);
			}
			break;
			}
		}

		void FasePrimeira::criarMapa() {
			sf::Vector2f tamJanela = pGrafico->getTamJanela();
			limiteCamera.left = -550.0f + tamJanela.x / 2.0f - 75.f;
			limiteCamera.top = 150.0f;
			limiteCamera.width = 11 * 500.0f - 50.0f;
			limiteCamera.height = tamJanela.y - 350.0f;
			pGrafico->setLimiteCamera(limiteCamera);

			//primeira parede
			for (int i = 1; i < 12; i++) {
				criarPlataforma(sf::Vector2f(-550.0f, i * 50.0f), sf::Vector2f(50.f, 50.0f), "parede");
			}

			//chão
			for (int i = -10; i < 110; i++) {
				criarPlataforma(sf::Vector2f(i * 50.0f, 550.0f), sf::Vector2f(50.0f, 50.0f), "padrao");
			}

			//segunda parede
			for (int i = 1; i < 12; i++) {
				criarPlataforma(sf::Vector2f(5500.0f, i * 50.0f), sf::Vector2f(50.f, 50.0f), "parede");
			}

			//nascimento do jogador
			criarPersonagem(IDs::IDs::jogador1, sf::Vector2f(-400.0f, 250.0f));
			if (jogadores2 == true) {
				criarPersonagem(IDs::IDs::jogador2, sf::Vector2f(-300.0f, 250.0f));
			}

			//gerando esqueletos
			setNumEsqueletos(rand() % 8 + 3);
			int qntEsqueletos = getNumEsqueletos();
			for (int i = 0; i < qntEsqueletos; i++) {
				criarPersonagem(IDs::IDs::esqueleto, sf::Vector2f(100.0f + i * 500.0f, 0.0f), 1);
			}

			//gerando magos
			setNumMagos(rand() % 8 + 3);
			int qntMagos = getNumMagos();
			for (int i = 0; i < qntMagos; i++) {
				criarPersonagem(IDs::IDs::mago, sf::Vector2f(100.0f + i * 500.0f, 0.0f), 1);
			}

			//gerando espinhos
			setNumEspinhos(rand() % 10 + 1);
			int qntEspinhos = getNumEspinhos();
			for (int i = 0; i < qntEspinhos; i++) {
				criarEspinho(sf::Vector2f(300.0f + i * 500.0f, 530.0f), sf::Vector2f(50.0f, 50.0f));
				criarEspinho(sf::Vector2f(325.0f + i * 500.0f, 530.0f), sf::Vector2f(50.0f, 50.0f));
			}

			//gerando plataforma flutuante e plataforma movel
			setConjuntoDePlataformas(rand() % 5 + 1);
			int qntPlataformas = getConjuntoDePlataformas();
			int aux = (rand() % 2);
			for (int i = 0; i < qntPlataformas; i++) {
				criarPlataforma(sf::Vector2f(-50.0f + i * 1000.0f, 400.0f), sf::Vector2f(80.0f, 50.0f), 150.0f, false);
				for (int j = 1; j <= 5; j++) {
					criarPlataforma(sf::Vector2f(100.0f + j * 50.0f + i * 1000.0f , 400.0f), sf::Vector2f(50.0f, 50.0f), "flutuante2");
				}
				criarPlataforma(sf::Vector2f(450.0f + i * 1000.0f, 400.0f), sf::Vector2f(80.0f, 50.0f), 160.0f, aux);
				aux = (rand() % 2);

			}
			

		}

	}

}