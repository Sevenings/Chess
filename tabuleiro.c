#include "chess.h"
#include <stdio.h>
#include <stdlib.h>


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


void print_tabuleiro(Tabuleiro tabuleiro) {
    int valor;
    for (int lin=0; lin<8; lin++) {
        for (int col=0; col<8; col++) {
            valor = tabuleiro[8*lin + col];
            if (valor < 10) printf(" ");
            printf("%d ", valor);
        }
        printf("\n");
    }
}


Tabuleiro allocTabuleiro () {
    return (Tabuleiro) malloc(64*sizeof(ID_PECA));
}


Tabuleiro novoTabuleiroVazio() {
    Tabuleiro tabuleiro = allocTabuleiro();

    for (int lin=0; lin<8; lin++) {
        for (int col=0; col<8; col++) {
            tabuleiro[8*lin + col] = NA;
        }
    }
    return tabuleiro;
}


Tabuleiro novoTabuleiro() {
    Tabuleiro tabuleiro = allocTabuleiro();

    for (int lin=0; lin<8; lin++) {
        for (int col=0; col<8; col++) {
            tabuleiro[8*lin + col] = tabuleiro_inicial[lin][col];
        }
    }
    return tabuleiro;
}


Tabuleiro TabuleiroCopy(Tabuleiro tabuleiro) {
    Tabuleiro tabuleiroCopia = allocTabuleiro();

    for (int lin=0; lin<8; lin++) {
        for (int col=0; col<8; col++) {
            tabuleiroCopia[8*lin + col] = TabuleiroGet(tabuleiro, lin, col);
        }
    }
    return tabuleiroCopia;
}


Tabuleiro mapaMovimentos(Tabuleiro tabuleiro, int linhaInicial, int colunaInicial) {
    Tabuleiro mapa = novoTabuleiroVazio();

    if (!TabuleiroTemPeca(tabuleiro, linhaInicial, colunaInicial)) {
        return NULL;
    }

    for (int lin=0; lin<8; lin++) {
        for (int col=0; col<8; col++) {
            if (podeMover(tabuleiro, linhaInicial, colunaInicial, lin, col)) {
                mapa[8*lin + col] = 1;
            } else {
                mapa[8*lin + col] = 0;
            }
        }
    }
    return mapa;
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


int TabuleiroTemPeca(Tabuleiro tabuleiro, int linha, int coluna) {
    return TabuleiroGet(tabuleiro, linha, coluna) != NA;
}


