#include <stdio.h>
#include "chess.h"


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
