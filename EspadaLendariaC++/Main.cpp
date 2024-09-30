#include "Principal.hpp"
#include <time.h>

int main()
{
    time_t t;
    srand((unsigned)time(&t));

    EspadaLendaria::Principal objPrincipal;
    objPrincipal.executar();
    return 0;
}
