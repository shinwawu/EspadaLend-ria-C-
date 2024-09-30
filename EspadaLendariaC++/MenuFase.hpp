#pragma once
#include "MenuPrincipal.hpp"

namespace EspadaLendaria {
	
	namespace Menu {

		class MenuFase : public MenuPrincipal { //padrao de projeto template method e factory method
		private:
			
		public:
			MenuFase();
			~MenuFase();
			void criarBotoes();
			void executar();
		};
	}
}
