
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

typedef ID_PECA* Tabuleiro;

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



// Tabuleiro
// Alloca memória para um Tabuleiro
Tabuleiro allocTabuleiro();

// Aloca e Inicializa um novo tabuleiro
Tabuleiro novoTabuleiro();

// Imprime as peças de tabuleiro na tela
void print_tabuleiro(Tabuleiro tabuleiro);

// Getters e Setters
ID_PECA TabuleiroGet(Tabuleiro t, int linha, int coluna);
void TabuleiroSet(Tabuleiro t, int linha, int coluna, ID_PECA valor);
void TabuleiroGetPecaDetails(Tabuleiro tabuleiro, int linha, int coluna, int *tipo, int *cor);
Cor TabuleiroGetCor(Tabuleiro tabuleiro, int linha, int coluna);
TipoPeca TabuleiroGetTipoPeca(Tabuleiro tabuleiro, int linha, int coluna);

void TabuleiroMoverPeca(Tabuleiro t, int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal);

// Verifica se a posição está fora do Tabuleiro
int foraTabuleiro(int linha, int coluna);

int TabuleiroTemPeca(Tabuleiro tabuleiro, int linha, int coluna);
Tabuleiro TabuleiroCopy(Tabuleiro tabuleiro);
Tabuleiro mapaMovimentos(Tabuleiro tabuleiro, int linhaInicial, int colunaInicial);


// Movimento
void verificarEntradasMovimento(Cor cor, int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal);
int podeMoverPeao(Tabuleiro tabuleiro, Cor cor, int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal);
int podeMoverCavalo(Tabuleiro tabuleiro, Cor cor, int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal);
int podeMoverBispo(Tabuleiro tabuleiro, Cor cor, int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal);
int podeMoverTorre(Tabuleiro tabuleiro, Cor cor, int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal);
int podeMoverDama(Tabuleiro tabuleiro, Cor cor, int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal);
int podeMoverRei(Tabuleiro tabuleiro, Cor cor, int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal);
int podeMover(Tabuleiro tabuleiro, int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal);
int jogadaValida(Tabuleiro tabuleiro, Cor vez, int linhaInicial, int colunaInicial, int linhaFinal, int colunaFinal);
