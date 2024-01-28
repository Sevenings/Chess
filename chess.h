
#define max(a,b)             \
({                           \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a > _b ? _a : _b;       \
})

#define min(a,b)             \
({                           \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b;       \
})


typedef enum ID_PECA {
    NA,
    PP, PB,
    BP, BB,
    CP, CB,
    TP, TB,
    DP, DB,
    RP, RB
} ID_PECA;

typedef enum TipoPeca {
    PEAO=1,
    BISPO,
    CAVALO,
    TORRE,
    DAMA,
    REI
} TipoPeca;

typedef enum Cor {
    BRANCO=0,
    PRETO=1,
    NO_COLOR
} Cor;

typedef ID_PECA* Tabuleiro;


int podeMoverTorre(Tabuleiro tabuleiro, Cor cor, int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal);

Tabuleiro novoTabuleiro();
void print_tabuleiro(Tabuleiro tabuleiro);
ID_PECA TabuleiroGet(Tabuleiro t, int linha, int coluna);
void TabuleiroSet(Tabuleiro t, int linha, int coluna, ID_PECA valor);
void TabuleiroGetPecaDetails(Tabuleiro tabuleiro, int linha, int coluna, int *tipo, int *cor);
Cor TabuleiroGetCor(Tabuleiro tabuleiro, int linha, int coluna);
TipoPeca TabuleiroGetTipoPeca(Tabuleiro tabuleiro, int linha, int coluna);
void TabuleiroMoverPeca(Tabuleiro t, int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal);
int foraTabuleiro(int linha, int coluna);
void verificarEntradasMovimento(Cor cor, int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal);
int podeMoverCavalo(Tabuleiro tabuleiro, Cor cor, int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal);
int TabuleiroTemPeca(Tabuleiro tabuleiro, int linha, int coluna);
