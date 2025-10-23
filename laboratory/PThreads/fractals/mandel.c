/*
 * Emilio Francesquini <e.francesquini@ufabc.edu.br>
 * 2019-04-03
 */

#include <stdio.h>
#include <stdlib.h>

/* Dimensões da imagem gerada */
#define DIMS 4096
/* Limites do plano complexo */
#define MAX_COMPLEX 2.0
/* Fator de conversão imagem plano complexo */
#define FATOR (MAX_COMPLEX * 2.0 / (double)DIMS)
/* Limite para bailout da iteração */
#define BAILOUT 4.0
/* Limite de iterações */
#define MAX_ITERS 1000
/* Cores da paleta */
#define CORES 256
/* Nome do arquivo gerado */
#define NOME_ARQ "mandel.ppm"

/* Representa um pixel rgb */
typedef struct {
    unsigned char r, g, b;
} rgb;

/* Representa um número complexo */
typedef struct {
    double r;
    double i;
} complexo;

/* Múltiplica dois números complexos */
complexo mul(complexo x1, complexo x2) {
    complexo ret;
    ret.r = x1.r * x2.r - x1.i * x2.i;
    ret.i = x1.r * x2.i + x2.r * x1.i;
    return ret;
}

/* Soma dois números complexos */
complexo soma (complexo x1, complexo x2) {
    complexo ret;
    ret.r = x1.r + x2.r;
    ret.i = x1.i + x2.i;
    return ret;
}

/* Calcula o número de iterações para o ponto complexo ix + iy i */
int calculaMandel(double ix, double iy) {
    int iter;
    complexo z, c;
    double norma2;

    iter = 0;
    c.r = ix;
    c.i = iy;
    z.r = 0;
    z.i = 0;
    do {
        iter++;
        z = soma(mul(z, z), c);
        norma2 = z.r * z.r + z.i + z.i;
    } while (iter <= MAX_ITERS && norma2 <= BAILOUT);

    return iter % CORES;
}

/* Converte coordenadas da imagem para o plano complexo e calcula o
   número de iterações daquele ponto */
int mandelPixel (int x, int y) {
    double ix, iy;
    ix = (double)(x - DIMS / 2) * FATOR;
    iy = (double)(y - DIMS / 2) * FATOR;
    /* Apenas um ajuste para mostrar uma região interessante da
       imagem */
    ix = ix / 8.0 - 0.5;
    iy = iy / 8.0 + 0.5;

    return calculaMandel (ix, iy);
}

int main(void) {
    int i, j;
    rgb paleta[CORES];
    rgb pixel;

    /* Cálculo totalmente arbitrário para o número de cores. O mais
       natural talvez fosse utilizar uma imagem em tons de cinza
       baseados no número de iterações. Mas colorido fica mais
       divertido! :) */
    for (i = 0; i < CORES; i++) {
        paleta[i].r = (255 - i * 2) % 256;
        paleta[i].g = (i * 11) % 256;
        paleta[i].b = (i * 7) % 256;
    }


    /* Calcula pixels e escreve PPM binário*/
    FILE * fp = fopen(NOME_ARQ, "wb");
    fprintf(fp, "P6\n%d %d\n255\n", DIMS, DIMS);

    for (j = 0; j < DIMS; ++j)
        for (i = 0; i < DIMS; ++i) {
            pixel = paleta[mandelPixel(i, j)];
            fwrite(&pixel, 1, 3, fp);
        }
    fclose(fp);

    return 0;
}
