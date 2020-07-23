#include <stdio.h>
#include <stdlib.h>

typedef struct movimento {
  float posicaoInicial, velocInicial, acelerac;
} sMovel;

int main(){

  FILE *arqPosic;
  FILE *arqData;
  FILE *gnuplot = popen("gnuplot", "w");

  fprintf(gnuplot, "plot '-'\n");

  arqPosic = fopen("posxtemp.csv", "w");
  arqData = fopen("data.csv", "w");

  if (arqPosic == NULL || arqData == NULL) {
    printf("ARQ DEU RUIM\n");
    exit(0);
  }

  sMovel mAux;
  float novaPosicao = 0, novaVeloc = 0;

  printf("De as caracteristicas do movel:\n");
  printf("Posicao inicial: ");
  scanf("%f", &mAux.posicaoInicial);
  printf("Velocidade inicial: ");
  scanf("%f", &mAux.velocInicial);
  printf("Aceleracao: ");
  scanf("%f", &mAux.acelerac);
  system("clear");

  for (float t = 0; t <= 4.01; t += 0.01) {
    novaVeloc = mAux.velocInicial + mAux.acelerac * t;
    novaPosicao = mAux.posicaoInicial + mAux.velocInicial * t;
    novaPosicao += (mAux.acelerac / 2) * (t * t);

    printf("Posicao: %.3f m, Velocidade: %.3f m/s, Tempo: %.2f s\n", novaPosicao, novaVeloc, t);
    fprintf(arqPosic, "%.3f, %.4f\n", t, novaPosicao);
    fprintf(arqData, "%.3f, %.3f\n", novaPosicao, novaVeloc);
    fprintf(gnuplot, "%g %g\n", t, novaPosicao);
    novaPosicao = 0;
    novaVeloc = 0;
  }

  fprintf(gnuplot, "e\n");
  fflush(gnuplot);

  fclose(arqPosic);
  fclose(arqData);

  system("sleep 30");

  return 0;
}
