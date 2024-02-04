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
    // Caso o destino seja uma peça de mesma cor, não é possível
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

int podeMoverPeao(Tabuleiro tabuleiro, Cor cor, int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal) {
    verificarEntradasMovimento(cor, linhaInicial, colunaInicial, linhaFinal, colunaFinal);

    // Não existe movimento em que a Peça não saia do lugar
    if (linhaInicial == linhaFinal && colunaInicial == colunaFinal) {
        return 0;
    }
    // Caso o destino seja uma peça de mesma cor não é possível
    if (TabuleiroGetCor(tabuleiro, linhaFinal, colunaFinal) == cor)
        return 0;

    // Indica a "direção" em que a peça olha
    int facing = 2*cor - 1;     // Branco -> -1
                                // Preto -> +1
    // Indica a linha em que o peão começa
    int linhaNatal = -5*cor + 6;  // Branco -> 6
                                 // Preto -> 1
    // Linha da frente do peão
    int linhaDaFrente = linhaInicial + facing;

    // Se o movimento for de andar reto
    if (colunaInicial == colunaFinal) {
        // Se a casa da frente estiver ocupada, não pode
        if (TabuleiroGetTipoPeca(tabuleiro, linhaDaFrente, colunaInicial) != NA)
            return 0;
        // Se o movimento for "Andar 1 para frente", pode
        if (linhaFinal == linhaDaFrente)
            return 1;
        
        // Caso seja o primeiro movimento do peão, ele quer andar 2 casas, e a final não está ocupada, pode
        int linhaDuasAfrente = linhaInicial + 2*facing;
        if (linhaInicial == linhaNatal && linhaFinal == linhaDuasAfrente && !TabuleiroTemPeca(tabuleiro, linhaFinal, colunaInicial)) {
            return 1;
        }
    }

    // Se o movimento for de capturar
    int dist_coluna = abs(colunaFinal - colunaInicial);
    // Se for na casa da diagonal para frente e tiver alguém, pode
    if (dist_coluna == 1 && linhaFinal == linhaDaFrente && TabuleiroTemPeca(tabuleiro, linhaFinal, colunaFinal)) {
        return 1;
    }

    // Do contrário, não pode
    return 0;
}

int podeMoverBispo(Tabuleiro tabuleiro, Cor cor, int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal) {
    verificarEntradasMovimento(cor, linhaInicial, colunaInicial, linhaFinal, colunaFinal);
    
    // Não existe movimento em que a Peça não saia do lugar
    if (linhaInicial == linhaFinal && colunaInicial == colunaFinal) {
        return 0;
    }

    // Se o destino tiver peça da mesma cor, não pode
    if (TabuleiroGetCor(tabuleiro, linhaFinal, colunaFinal) == cor)
        return 0;

    // Se movimento não for diagonal, não pode
    int dLinha = linhaFinal - linhaInicial;
    int dColuna = colunaFinal - colunaInicial;
    if (abs(dLinha) != abs(dColuna)) {
        return 0;
    }

    // dLinha e dColuna agora estão normalizados
    dLinha = dLinha > 0 ? 1 : -1;
    dColuna = dColuna > 0 ? 1 : -1;

    // Se tiver peça no caminho, não pode
    int l=linhaInicial+dLinha, c=colunaInicial+dColuna;
    while (l != linhaFinal && c != colunaFinal) {
        if (TabuleiroTemPeca(tabuleiro, l, c))
            return 0;
        l += dLinha; c += dColuna;
    }

    // Do contrário, pode
    return 1;
}


int podeMoverDama(Tabuleiro tabuleiro, Cor cor, int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal) {
    verificarEntradasMovimento(cor, linhaInicial, colunaInicial, linhaFinal, colunaFinal);
    int podeBispo = podeMoverBispo(tabuleiro, cor, linhaInicial, colunaInicial, linhaFinal, colunaFinal);
    int podeTorre = podeMoverTorre(tabuleiro, cor, linhaInicial, colunaInicial, linhaFinal, colunaFinal);
    return podeBispo || podeTorre;
}

int podeMoverRei(Tabuleiro tabuleiro, Cor cor, int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal) {
    verificarEntradasMovimento(cor, linhaInicial, colunaInicial, linhaFinal, colunaFinal);

    // Não existe movimento em que a Peça não saia do lugar
    if (linhaInicial == linhaFinal && colunaInicial == colunaFinal) {
        return 0;
    }

    // Se o destino tiver peça da mesma cor, não pode
    if (TabuleiroGetCor(tabuleiro, linhaFinal, colunaFinal) == cor)
        return 0;

    int dLinha = linhaFinal - linhaInicial;
    int dColuna = colunaFinal - colunaInicial;
    
    // O alcançe do rei é nos quadrados ao redor
    if (abs(dLinha) > 1 || abs(dColuna) > 1)
        return 0;

    Tabuleiro tabuleiroSemRei = TabuleiroCopy(tabuleiro);
    TabuleiroSet(tabuleiroSemRei, linhaInicial, colunaInicial, NA);

    // Verificar se o quadrado escolhido está em cheque
    for (int coluna = 0; coluna < 8; coluna++) {   // Varrer o tabuleiro
    for (int linha = 0; linha < 8; linha++) {
        // Se tiver vazio, ou tiver mesma cor, pula
        if (!TabuleiroTemPeca(tabuleiro, linha, coluna) || TabuleiroGetCor(tabuleiro, linha, coluna) == cor)    
            continue;

        // Se a posição estiver em cheque, não pode
        if (TabuleiroGetTipoPeca(tabuleiro, linha, coluna) != REI) {    // Se não for Rei é esse calculo
            if (podeMover(tabuleiroSemRei, linha, coluna, linhaFinal, colunaFinal))
                return 0;
        } else {    // Se for, é esse outro cálculo
            int dLinhaOutroRei = linhaFinal - linha;
            int dColunaOutroRei = colunaFinal - coluna;
            if (abs(dLinhaOutroRei) <= 1 && abs(dColunaOutroRei) <= 1) {
                return 0;
            }
        }
    }}

    // Se não for barrado por nada, pode sim
    return 1;
}


int podeMover(Tabuleiro tabuleiro, int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal) {
    int cor, peca;
    TabuleiroGetPecaDetails(tabuleiro, linhaInicial, colunaInicial, &peca, &cor);

    verificarEntradasMovimento(cor, linhaInicial, colunaInicial, linhaFinal, colunaFinal);

    switch (peca) {
        case PEAO:
            return podeMoverPeao(tabuleiro, cor, linhaInicial, colunaInicial, linhaFinal, colunaFinal);
            break;
        case BISPO:
            return podeMoverBispo(tabuleiro, cor, linhaInicial, colunaInicial, linhaFinal, colunaFinal);
            break;
        case CAVALO:
            return podeMoverCavalo(tabuleiro, cor, linhaInicial, colunaInicial, linhaFinal, colunaFinal);
            break;
        case TORRE:
            return podeMoverTorre(tabuleiro, cor, linhaInicial, colunaInicial, linhaFinal, colunaFinal);
            break;
        case DAMA:
            return podeMoverDama(tabuleiro, cor, linhaInicial, colunaInicial, linhaFinal, colunaFinal);
            break;
        case REI:
            return podeMoverRei(tabuleiro, cor, linhaInicial, colunaInicial, linhaFinal, colunaFinal);
            break;
        default:
            return 0;
    }
}


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
    TabuleiroMoverPeca(t, 0, 0, 5, 0);
    print_tabuleiro(t);

    // Teste podeMoverTorre
    int rPodeMover = podeMoverTorre(t, PRETO, 4, 0, 0, 0);
    if (rPodeMover) {
        printf("Movimento válido ");
    } else {
        printf("Movimento inválido ");
    } printf("de Torre\n");

    // Teste podeMoverCavalo
    rPodeMover = podeMoverCavalo(t, PRETO, 0, 1, 2, 2);
    if (rPodeMover) {
        printf("Movimento válido ");
    } else {
        printf("Movimento inválido ");
    } printf("de Cavalo\n");

    // Teste podeMoverPeao
    rPodeMover = podeMoverPeao(t, PRETO, 3, 0, 4, 0);
    if (rPodeMover) {
        printf("Movimento válido ");
    } else {
        printf("Movimento inválido ");
    } printf("de Peao\n");

    printf("BRANCO: %d\n", BRANCO);
    printf("PRETO: %d\n", PRETO);
    printf("NO_COLOR: %d\n", NO_COLOR);

    TabuleiroMoverPeca(t, 6, 3, 4, 3);
    print_tabuleiro(t);

    rPodeMover = podeMoverBispo(t, BRANCO, 7, 2, 5, 4);
    if (rPodeMover) {
        printf("Movimento válido ");
    } else {
        printf("Movimento inválido ");
    } printf("de Bispo\n");

    TabuleiroMoverPeca(t, 7, 4, 5, 5);
    print_tabuleiro(t);

    Tabuleiro mapa_movimentos = mapaMovimentos(t, 5, 5);
    if (mapa_movimentos) {
        print_tabuleiro(mapa_movimentos);
    } else {
        printf("Casa Vazia");
    }
}
