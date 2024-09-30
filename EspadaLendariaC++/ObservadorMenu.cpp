#include "ObservadorMenu.hpp"
#include "GerenciadorEstado.hpp"
#include "FotoSalvar.hpp"

namespace EspadaLendaria {

    namespace Observador {

        ObservadorMenu::ObservadorMenu(Menu::Menu* menu) :
            Observador(), menu(menu)
        {

        }

        ObservadorMenu::~ObservadorMenu() {

        }

        void ObservadorMenu::teclaPressionada(const sf::Keyboard::Key tecla) {
            if (tecladoEspecial[tecla] == "Enter") {
                IDs::IDs IDEstadoAtual = pGEstado->getEstadoAtual()->getID();
                switch (menu->getIDBotaoSelecionado())
                {
                case (IDs::IDs::botao_sair):
                {
                    pGEstado->removerEstado(2);
                }
                break;
                case (IDs::IDs::botao_voltar):
                {
                    pGEstado->removerEstado();
                }
                break;
                case (IDs::IDs::botao_novoJogo):
                {
                    Estado::Estado* estado = pGEstado->getEstadoAtual();
                    if (estado->getID() == IDs::IDs::estado_menu_principal) {
                        pGEstado->addEstado(IDs::IDs::estado_menu_qntjogadores);
                    }
                }
                break;
                case(IDs::IDs::botao_fase_1):
                {
                    Estado::Estado* estado = pGEstado->getEstadoAtual();
                    if (estado->getID() == IDs::IDs::estado_menu_fases1) {
                        pGEstado->addEstado(IDs::IDs::jogar_FasePrimeira1);
                        Estado::EstadoJogar* estadoJogar = dynamic_cast<Estado::EstadoJogar*>(pGEstado->getEstadoAtual());
                        estadoJogar->criarFase();
                    }
                    if (estado->getID() == IDs::IDs::estado_menu_fases2) {
                        pGEstado->addEstado(IDs::IDs::jogar_FasePrimeira2);
                        Estado::EstadoJogar* estadoJogar = dynamic_cast<Estado::EstadoJogar*>(pGEstado->getEstadoAtual());
                        estadoJogar->criarFase();
                    }

                    
                }
                break;
                case(IDs::IDs::botao_fase_2):
                {
                    Estado::Estado* estado = pGEstado->getEstadoAtual();
                    if (estado->getID() == IDs::IDs::estado_menu_fases1) {
                        pGEstado->addEstado(IDs::IDs::jogar_FaseSegunda1);
                        Estado::EstadoJogar* estadoJogar = dynamic_cast<Estado::EstadoJogar*>(pGEstado->getEstadoAtual());
                        estadoJogar->criarFase();
                    }
                    if (estado->getID() == IDs::IDs::estado_menu_fases2) {
                        pGEstado->addEstado(IDs::IDs::jogar_FaseSegunda2);
                        Estado::EstadoJogar* estadoJogar = dynamic_cast<Estado::EstadoJogar*>(pGEstado->getEstadoAtual());
                        estadoJogar->criarFase();
                    }
                }
                break;
                case(IDs::IDs::botao_umjogador):
                {
                    Estado::Estado* estado = pGEstado->getEstadoAtual();
                    if (estado->getID() == IDs::IDs::estado_menu_qntjogadores) {
                        pGEstado->addEstado(IDs::IDs::estado_menu_fases1);
                    }

                }
                break;
                case(IDs::IDs::botao_doisjogadores):
                {
                    Estado::Estado* estado = pGEstado->getEstadoAtual();
                    if (estado->getID() == IDs::IDs::estado_menu_qntjogadores) {
                        pGEstado->addEstado(IDs::IDs::estado_menu_fases2);
                    }
                }
                break;
                case (IDs::IDs::botao_salvar_colocacao):
                {
                    Estado::Estado* estado = pGEstado->getEstadoAtual();
                    if (estado->getID() == IDs::IDs::estado_menu_game_over) {
                        Estado::EstadoMenu* estadoMenuFase = dynamic_cast<Estado::EstadoMenu*>(estado);
                        Menu::MenuGameOver* menuGameOver = dynamic_cast<Menu::MenuGameOver*>(estadoMenuFase->getMenu());
                        menuGameOver->salvarColocacao();
                    }
                    pGEstado->removerEstado(2);
                }
                break;
                case (IDs::IDs::botao_colocacao):
                {
                    pGEstado->addEstado(IDs::IDs::estado_menu_colocacao);
                    pGEstado->addEstado(IDs::IDs::estado_menu_colocacao);
                }
                break;
                case(IDs::IDs::botao_salvar_jogada):
                {
                    pGEstado->addEstado(IDs::IDs::estado_menu_salvar_jogada);
                    pGEstado->addEstado(IDs::IDs::estado_menu_colocacao);
                }
                break;
                case(IDs::IDs::botao_salvar):
                {
                    Estado::Estado* estado = pGEstado->getEstadoAtual();
                    if (estado->getID() == IDs::IDs::estado_menu_salvar_jogada) {
                        Estado::EstadoMenu* estadoMenu = dynamic_cast<Estado::EstadoMenu*>(estado);
                        Menu::MenuSalvarJogada* menuSalvarJogada = dynamic_cast<Menu::MenuSalvarJogada*>(estadoMenu->getMenu());
                        menuSalvarJogada->salvarJogada();
                        pGEstado->removerEstado();
                    }
                }
                break;
                case (IDs::IDs::botao_carregar_jogo):
                {
                    pGEstado->addEstado(IDs::IDs::estado_menu_carregar_jogo);
                    pGEstado->addEstado(IDs::IDs::estado_menu_colocacao);
                }
                break;
                case (IDs::IDs::botao_carregar):
                {
                    Estado::Estado* estado = pGEstado->getEstadoAtual();
                    if (estado->getID() == IDs::IDs::estado_menu_carregar_jogo) {
                        Estado::EstadoMenu* estadoMenu = dynamic_cast<Estado::EstadoMenu*>(estado);
                        Menu::MenuCarregarJogo* menuCarregarJogo = dynamic_cast<Menu::MenuCarregarJogo*>(estadoMenu->getMenu());
                        Menu::FotoSalvar* card = menuCarregarJogo->getFotoSalvarSelecionado();
                        if (card->getExiste()) {
                            pGEstado->removerEstado();
                            const  std::string caminhoArquivoEntidades = card->getCaminhoArquivoEntidades();
                            const std::string caminhoArquivoFase = card->getCaminhoArquivoFase();
                            Gerenciador::GerenciadorArquivo GArquivo;
                            std::vector<std::string> vectorInfoFase = GArquivo.lerArquivo(caminhoArquivoFase.c_str());
                            std::cout << (int)vectorInfoFase.size() << std::endl;
                            int id = std::stoi(vectorInfoFase[0]);
                            if (id == 47) { 
                                pGEstado->addEstado(IDs::IDs::jogar_FasePrimeira1);

                            }
                            else if (id == 48) { 
                                pGEstado->addEstado(IDs::IDs::jogar_FaseSegunda1);

                            }
                            else if (id == 69) { 
                                pGEstado->addEstado(IDs::IDs::jogar_FasePrimeira2);

                            }
                            else if (id == 70) { 
                                pGEstado->addEstado(IDs::IDs::jogar_FaseSegunda2);

                            }
                            else {
                                std::cout << "ObservadorMenu::nao foi possivel criar uma fase" << std::endl;
                                exit(1);
                            }
                            Estado::EstadoJogar* estadoJogar = dynamic_cast<Estado::EstadoJogar*>(pGEstado->getEstadoAtual());
                            estadoJogar->criarFase(caminhoArquivoEntidades, vectorInfoFase);
                        }
                    }
                }
                break;
                case(IDs::IDs::botao_remover):
                {
                    Estado::Estado* estado = pGEstado->getEstadoAtual();
                    if (estado->getID() == IDs::IDs::estado_menu_carregar_jogo) {
                        Estado::EstadoMenu* estadoMenu = dynamic_cast<Estado::EstadoMenu*>(estado);
                        Menu::MenuCarregarJogo* menuCarregarJogo = dynamic_cast<Menu::MenuCarregarJogo*>(estadoMenu->getMenu());
                        menuCarregarJogo->deletarArquivos();
                    }
                }
                break;
                }
            }
            else if (tecladoEspecial[tecla] == "Left") {
                menu->selecionaEsquerda();
            }
            else if (tecladoEspecial[tecla] == "Right") {
                menu->selecionaDireita();
            }
        }

        void ObservadorMenu::teclaSolta(const sf::Keyboard::Key tecla) {
            if (tecladoEspecial[tecla] == "Up") {
                menu->selecionaCima();
            }
            else if (tecladoEspecial[tecla] == "Down") {
                menu->selecionaBaixo();
            }
            else if (menu->getID() == IDs::IDs::menu_game_over) {
                if (tecladoEspecial[tecla] == "BackSpace") {
                    Menu::MenuGameOver* menuGameOver = dynamic_cast<Menu::MenuGameOver*>(menu);
                    menuGameOver->removerCaracter();
                }
                else {
                    for (int i = 97; i < 123; i++) {
                        if (teclado[tecla] == i) {
                            Menu::MenuGameOver* menuGameOver = dynamic_cast<Menu::MenuGameOver*>(menu);
                            menuGameOver->addCaracter(teclado[tecla]);
                            break;
                        }
                    }
                    for (int i = 48; i < 58; i++) {
                        if (teclado[tecla] == i) {
                            Menu::MenuGameOver* menuGameOver = dynamic_cast<Menu::MenuGameOver*>(menu);
                            menuGameOver->addCaracter(teclado[tecla]);
                            break;
                        }
                    }
                }
            }
        }

        void ObservadorMenu::moveMouse(const sf::Vector2f posMouse) {
            menu->eventoMouse(posMouse);
        }

        void ObservadorMenu::botaoMouseSolta(const sf::Mouse::Button botaoMouse) {
            if (menu->getMouseSelecionado()) {
                switch (botaoMouse)
                {
                case (sf::Mouse::Left):
                {
                    switch (menu->getIDBotaoSelecionado())
                    {
                    case (IDs::IDs::botao_novoJogo):
                    {
                        Estado::Estado* estado = pGEstado->getEstadoAtual();
                        if (estado->getID() == IDs::IDs::estado_menu_principal) {
                            pGEstado->addEstado(IDs::IDs::estado_menu_qntjogadores);
                        }
                    }
                    break;
                    case(IDs::IDs::botao_fase_1):
                    {
                        Estado::Estado* estado = pGEstado->getEstadoAtual();
                        if (estado->getID() == IDs::IDs::estado_menu_fases1) {
                            pGEstado->addEstado(IDs::IDs::jogar_FasePrimeira1);
                            Estado::EstadoJogar* estadoJogar = dynamic_cast<Estado::EstadoJogar*>(pGEstado->getEstadoAtual());
                            estadoJogar->criarFase();
                        }
                        if (estado->getID() == IDs::IDs::estado_menu_fases2) {
                            pGEstado->addEstado(IDs::IDs::jogar_FasePrimeira2);
                            Estado::EstadoJogar* estadoJogar = dynamic_cast<Estado::EstadoJogar*>(pGEstado->getEstadoAtual());
                            estadoJogar->criarFase();
                        }
                    }
                    break;
                    case(IDs::IDs::botao_fase_2):
                    {
                        Estado::Estado* estado = pGEstado->getEstadoAtual();
                        if (estado->getID() == IDs::IDs::estado_menu_fases1) {
                            pGEstado->addEstado(IDs::IDs::jogar_FaseSegunda1);
                            Estado::EstadoJogar* estadoJogar = dynamic_cast<Estado::EstadoJogar*>(pGEstado->getEstadoAtual());
                            estadoJogar->criarFase();
                        }
                        if (estado->getID() == IDs::IDs::estado_menu_fases2) {
                            pGEstado->addEstado(IDs::IDs::jogar_FaseSegunda2);
                            Estado::EstadoJogar* estadoJogar = dynamic_cast<Estado::EstadoJogar*>(pGEstado->getEstadoAtual());
                            estadoJogar->criarFase();
                        }
                    }
                    break;
                    case(IDs::IDs::botao_umjogador):
                    {
                        Estado::Estado* estado = pGEstado->getEstadoAtual();
                        if (estado->getID() == IDs::IDs::estado_menu_qntjogadores) {
                            pGEstado->addEstado(IDs::IDs::estado_menu_fases1);
                        }
                    }
                    break;
                    case(IDs::IDs::botao_doisjogadores):
                    {
                        Estado::Estado* estado = pGEstado->getEstadoAtual();
                        if (estado->getID() == IDs::IDs::estado_menu_qntjogadores) {
                            pGEstado->addEstado(IDs::IDs::estado_menu_fases2);
                        }
                    }
                    break;
                    case (IDs::IDs::botao_sair):
                    {
                        pGEstado->removerEstado(4);
                    }
                    break;
                    case (IDs::IDs::botao_colocacao):
                    {
                        pGEstado->addEstado(IDs::IDs::estado_menu_colocacao);
                    }
                    break;
                    case (IDs::IDs::botao_voltar):
                    {
                        pGEstado->removerEstado();
                    }
                    break;
                    case (IDs::IDs::botao_salvar_colocacao):
                    {
                        Estado::Estado* estado = pGEstado->getEstadoAtual();
                        if (estado->getID() == IDs::IDs::estado_menu_game_over) {
                            Estado::EstadoMenu* estadoMenuFase = dynamic_cast<Estado::EstadoMenu*>(estado);
                            Menu::MenuGameOver* menuGameOver = dynamic_cast<Menu::MenuGameOver*>(estadoMenuFase->getMenu());
                            menuGameOver->salvarColocacao();
                        }
                        pGEstado->removerEstado(2);
                    }
                    break;
                    case (IDs::IDs::botao_salvar_jogada):
                    {
                        pGEstado->addEstado(IDs::IDs::estado_menu_salvar_jogada);
                    }
                    break;
                    case (IDs::IDs::botao_salvar):
                    {
                        Estado::Estado* estado = pGEstado->getEstadoAtual();
                        if (estado->getID() == IDs::IDs::estado_menu_salvar_jogada) {
                            Estado::EstadoMenu* estadoMenu = dynamic_cast<Estado::EstadoMenu*>(estado);
                            Menu::MenuSalvarJogada* menuSalvarJogada = dynamic_cast<Menu::MenuSalvarJogada*>(estadoMenu->getMenu());
                            menuSalvarJogada->salvarJogada();
                            pGEstado->removerEstado();
                        }
                    }
                    break;
                    case (IDs::IDs::botao_carregar_jogo):
                    {
                        pGEstado->addEstado(IDs::IDs::estado_menu_carregar_jogo);
                    }
                    break;
                    case (IDs::IDs::botao_carregar):
                    {
                        Estado::Estado* estado = pGEstado->getEstadoAtual();
                        if (estado->getID() == IDs::IDs::estado_menu_carregar_jogo) {
                            Estado::EstadoMenu* estadoMenu = dynamic_cast<Estado::EstadoMenu*>(estado);
                            Menu::MenuCarregarJogo* menuCarregarJogo = dynamic_cast<Menu::MenuCarregarJogo*>(estadoMenu->getMenu());
                            Menu::FotoSalvar* card = menuCarregarJogo->getFotoSalvarSelecionado();
                            if (card->getExiste()) {
                                pGEstado->removerEstado();
                                const std::string caminhoArquivoEntidades = card->getCaminhoArquivoEntidades();
                                const std::string caminhoArquivoFase = card->getCaminhoArquivoFase();
                                Gerenciador::GerenciadorArquivo GArquivo;
                                std::vector<std::string> vectorInfoFase = GArquivo.lerArquivo(caminhoArquivoFase.c_str());
                                int id = std::stoi(vectorInfoFase[0]);
                                //criar estado
                                if (id == 47) { //47 fase1,48fase2,69fase1 2jog,70 fase2 2jog
                                    pGEstado->addEstado(IDs::IDs::jogar_FasePrimeira1);

                                }
                                else if (id == 48) { //47 fase1,48fase2,69fase1 2jog,70 fase2 2jog
                                    pGEstado->addEstado(IDs::IDs::jogar_FaseSegunda1);

                                }
                                else if (id == 69) { //47 fase1,48fase2,69fase1 2jog,70 fase2 2jog
                                    pGEstado->addEstado(IDs::IDs::jogar_FasePrimeira2);

                                }
                                else if (id == 70) { //47 fase1,48fase2,69fase1 2jog,70 fase2 2jog
                                    pGEstado->addEstado(IDs::IDs::jogar_FaseSegunda2);

                                }
                                else {
                                    std::cout << "ObservadorMenu::nao foi possivel criar uma fase" << std::endl;
                                    exit(1);
                                }
                                Estado::EstadoJogar* estadoJogar = dynamic_cast<Estado::EstadoJogar*>(pGEstado->getEstadoAtual());
                                estadoJogar->criarFase(caminhoArquivoEntidades, vectorInfoFase);
                            }
                        }
                    }
                    break;
                    case(IDs::IDs::botao_remover):
                    {
                        Estado::Estado* estado = pGEstado->getEstadoAtual();
                        if (estado->getID() == IDs::IDs::estado_menu_carregar_jogo) {
                            Estado::EstadoMenu* estadoMenu = dynamic_cast<Estado::EstadoMenu*>(estado);
                            Menu::MenuCarregarJogo* menuCarregarJogo = dynamic_cast<Menu::MenuCarregarJogo*>(estadoMenu->getMenu());
                            menuCarregarJogo->deletarArquivos();
                        }
                    }
                    break;
                    }
                    break;
                }
                }
            }
        }

    }

}