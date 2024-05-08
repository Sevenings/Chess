#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "chess.h"

int podeMoverTorre(Tabuleiro tabuleiro, Cor cor, int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal) {

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
    int podeBispo = podeMoverBispo(tabuleiro, cor, linhaInicial, colunaInicial, linhaFinal, colunaFinal);
    int podeTorre = podeMoverTorre(tabuleiro, cor, linhaInicial, colunaInicial, linhaFinal, colunaFinal);
    return podeBispo || podeTorre;
}


int podeMoverRei(Tabuleiro tabuleiro, Cor cor, int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal) {
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


void verificarEntradasMovimento(Cor cor, int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal) {
    // Verificações de validade das entradas
    assert(!foraTabuleiro(linhaInicial, colunaInicial));
    assert(!foraTabuleiro(linhaFinal, colunaFinal));
    assert(cor == PRETO || cor == BRANCO);
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

int jogadaValida(Tabuleiro tabuleiro, Cor vez, int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal) {
    // Se for a vez das Brancas e o movimento não for de Brancas, inválida.
    if (vez == BRANCO && TabuleiroGetCor(tabuleiro, linhaInicial, colunaInicial) != BRANCO) return 0;
    
    // Se for a vez das Pretas e o movimento não for de Pretas, inválida
    if (vez == PRETO && TabuleiroGetCor(tabuleiro, linhaInicial, colunaInicial) != PRETO) return 0;

    // E se puder mover, então pode.
    return podeMover(tabuleiro, linhaInicial, colunaInicial, linhaFinal, colunaFinal);
}
