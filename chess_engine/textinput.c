#include <assert.h>

int traduzirLinha(const char linha) {
    assert('1' <= linha && linha <= '8');
    return '8' - linha;
}

int traduzirColuna(const char coluna) {
    assert('a' <= coluna && coluna <= 'h');
    return coluna - 'a';
}

int notacaoValida(const char entrada[6+1]) {
    if (!('a' <= entrada[0] && entrada[0] <= 'h'))
        return 0;
    if (!('1' <= entrada[1] && entrada[1] <= '8'))
        return 0;
    if (!('a' <= entrada[4] && entrada[4] <= 'h'))
        return 0;
    if (!('1' <= entrada[5] && entrada[5] <= '8'))
        return 0;
    return 1;
}

void traduzirNotacao(const char entrada[6+1], int *linhaInicial, int *colunaInicial, int *linhaFinal, int *colunaFinal) {
    *colunaInicial = traduzirColuna(entrada[0]);
    *linhaInicial = traduzirLinha(entrada[1]);
    *colunaFinal = traduzirColuna(entrada[4]);
    *linhaFinal = traduzirLinha(entrada[5]);
}
