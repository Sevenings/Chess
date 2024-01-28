#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "chess.h"



const ID_PECA tabuleiro_inicial[8][8] = {
    TP, CP, BP, DP, RP, BP, CP, TP,
    PP, PP, PP, PP, PP, PP, PP, PP, 
    NA, NA, NA, NA, NA, NA, NA, NA, 
    NA, NA, NA, NA, NA, NA, NA, NA, 
    NA, NA, NA, NA, NA, NA, NA, NA, 
    NA, NA, NA, NA, NA, NA, NA, NA, 
    PB, PB, PB, PB, PB, PB, PB, PB, 
    TB, CB, BB, DB, RB, BB, CB, TB
};



void verificarEntradasMovimento(Cor cor, int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal) {
    // Verificações de validade das entradas
    assert(!foraTabuleiro(linhaInicial, colunaInicial));
    assert(!foraTabuleiro(linhaFinal, colunaFinal));
    assert(cor == PRETO || cor == BRANCO);
}

int podeMoverTorre(Tabuleiro tabuleiro, Cor cor, int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal) {
    verificarEntradasMovimento(cor, linhaInicial, colunaInicial, linhaFinal, colunaFinal);

    // Não existe movimento em que a Torre não saia do lugar
    if (linhaInicial == linhaFinal && colunaInicial == colunaFinal) {
        return 0;
    }
    // Caso o destino seja uma peça de mesma cor não é possível
    if (TabuleiroGetCor(tabuleiro, linhaFinal, colunaFinal) == cor)
        return 0;

    // Nos movimentos da Torre, ou a linha ou a coluna devem ser iguais
    if (linhaInicial != linhaFinal && colunaInicial != colunaFinal) {
        return 0;
    }

    // Caso ela ande numa LINHA, verificando se não há peças no caminho
    if (linhaInicial == linhaFinal) {
        int colunaMenor = min(colunaInicial, colunaFinal);
        int colunaMaior = max(colunaInicial, colunaFinal);
        for (int coluna=colunaMenor+1; coluna<colunaMaior; coluna++) {
            // Se houver uma sequer peça entre, já não é possível movimentar
            if (TabuleiroGet(tabuleiro, linhaInicial, coluna) != NA) 
                return 0;
        }
    } else
    // Caso ela ande numa COLUNA, verificando se não há peças no caminho
    if (colunaInicial == colunaFinal) {
        int linhaMenor = min(linhaInicial, linhaFinal);
        int linhaMaior = max(linhaInicial, linhaFinal);
        for (int linha=linhaMenor+1; linha<linhaMaior; linha++) {
            // Se houver uma sequer peça entre, já não é possível movimentar
            if (TabuleiroGet(tabuleiro, linha, colunaInicial) != NA) 
                return 0;
        }
    } else {
        // Erro de Movimentação
        printf("Movimento inexperado de Torre. Encerrando...\n");
        exit(-1);
    }

    // Passando por todos os testes, é possível
    return 1;
}


int podeMoverCavalo(Tabuleiro tabuleiro, Cor cor, int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal) {
    verificarEntradasMovimento(cor, linhaInicial, colunaInicial, linhaFinal, colunaFinal);

    // Não existe movimento em que a Peça não saia do lugar
    if (linhaInicial == linhaFinal && colunaInicial == colunaFinal) {
        return 0;
    }
    // Caso o destino seja uma peça de mesma cor não é possível
    if (TabuleiroGetCor(tabuleiro, linhaFinal, colunaFinal) == cor)
        return 0;

    // Caso o movimento seja em L, é possível
    int dist_linhas = abs(linhaFinal - linhaInicial);
    int dist_colunas = abs(colunaFinal - colunaInicial);
    if (dist_linhas == 2 && dist_colunas == 1) {
        return 1;
    } else 
    if (dist_linhas == 1 && dist_colunas == 2) {
        return 1;
    }
    
    // Do contrário, não é possível
    return 0;
}



void print_tabuleiro(Tabuleiro tabuleiro) {
    for (int lin=0; lin<8; lin++) {
        for (int col=0; col<8; col++) {
            printf("%d ", tabuleiro[8*lin + col]);
        }
        printf("\n");
    }
}


Tabuleiro novoTabuleiro() {
    Tabuleiro tabuleiro = (Tabuleiro) malloc(64*sizeof(ID_PECA));

    for (int lin=0; lin<8; lin++) {
        for (int col=0; col<8; col++) {
            tabuleiro[8*lin + col] = tabuleiro_inicial[lin][col];
        }
    }
    return tabuleiro;
}


ID_PECA TabuleiroGet(Tabuleiro t, int linha, int coluna) {
    return t[8*linha + coluna];
}

void TabuleiroSet(Tabuleiro t, int linha, int coluna, ID_PECA valor) {
    t[8*linha + coluna] = valor;
}


void TabuleiroGetPecaDetails(Tabuleiro tabuleiro, int linha, int coluna, int *tipo, int *cor) {
    ID_PECA num_peca = TabuleiroGet(tabuleiro, linha, coluna);

    *tipo= (num_peca + 1)/2;
    *cor = num_peca % 2;
}

Cor TabuleiroGetCor(Tabuleiro tabuleiro, int linha, int coluna) {
    ID_PECA num_peca = TabuleiroGet(tabuleiro, linha, coluna);
    if (num_peca == NA) return NO_COLOR;
    return num_peca % 2;
}

TipoPeca TabuleiroGetTipoPeca(Tabuleiro tabuleiro, int linha, int coluna) {
    ID_PECA num_peca = TabuleiroGet(tabuleiro, linha, coluna);
    return (num_peca + 1)/2;
}

// Retira uma peça de lugar e a coloca em outro no tabuleiro. Não faz verificações de validade
void TabuleiroMoverPeca(Tabuleiro t, int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal) {
    ID_PECA peca = TabuleiroGet(t, linhaInicial, colunaInicial);
    TabuleiroSet(t, linhaInicial, colunaInicial, NA);
    TabuleiroSet(t, linhaFinal, colunaFinal, peca);
}


int foraTabuleiro(int linha, int coluna) {
    if (linha < 0 || linha >= 8 || coluna < 0 || coluna >= 8)
        return 1;
    return 0;
}


int main() {
    // Teste novoTabuleiro
    Tabuleiro t = novoTabuleiro();
    print_tabuleiro(t);



    // Teste TabuleiroGet e TabuleiroGetPeca
    int x=1, y=0;
    int v = TabuleiroGet(t, y, x);
    printf("Valor na posicao (%d, %d): %d\n", x, y, v);

    int id, cor;
    TabuleiroGetPecaDetails(t, y, x, &id, &cor);
    printf("Id: %d. Cor: %d\n", id, cor);


    // Teste TabuleiroMoverPeca
    TabuleiroMoverPeca(t, 0, 0, 4, 0);
    print_tabuleiro(t);

    // Teste podeMoverTorre
    int podeMover = podeMoverTorre(t, PRETO, 4, 0, 0, 0);
    if (podeMover) {
        printf("Movimento válido ");
    } else {
        printf("Movimento inválido ");
    } printf("de Torre\n");

    // Teste podeMoverCavalo
    podeMover = podeMoverCavalo(t, PRETO, 0, 1, 2, 2);
    if (podeMover) {
        printf("Movimento válido ");
    } else {
        printf("Movimento inválido ");
    } printf("de Cavalo\n");
}
