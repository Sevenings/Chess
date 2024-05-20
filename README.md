# Chess

Xadrez de Terminal. Xadrez é um jogo simples, quero fazer na linguagem simples e rápida que é C.

Fiz em C, tentando implementar da maneira mais simples possível
para poder, a partir desse projeto, complementá-lo com outras
coisas.

Os próximos passos seriam, após completar o sistema de terminal:
  - Encobrir com uma interface visual daora.
  - Tornar o jogo online.
  - Embarcar em um hardware tipo Arduino, rodar no LCD.
  - Fazer um hardware físico com peças magnéticas. (Xadrez de Bruxo)
  - Fazer input por voz usando NLP. (XADREZ DE BRUUXOO)

_Não necessariamente nessa ordem._

Nessa de encobrir a API com uma interface visual daora, já penso em
usar o OpenGL, com gráficos 3D e tudo mais. Seria lindo demais, só
pelo desafio.


### Atualizações

Fiz:
 * Criei a abstração turn\_server para depois juntar com a API de xadrez e fazer um chess\_server
 * Fazer com o turn\_client o mesmo que eu fiz com o turn\_server.
 * Implementei o chess\_server.
 * Implementar o client\_server.

Próxima:
 * Implementar Roque
 * Implementar Passante
 * Implementar Xeque
 * Implementar Xeque-Mate
