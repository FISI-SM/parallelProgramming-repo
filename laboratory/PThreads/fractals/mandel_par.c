/*
 * Emilio Francesquini <e.francesquini@ufabc.edu.br>
 * 2019-04-03
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

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
#define NOME_ARQ "mandel_par.ppm"

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

/* Struct utilizada para passar os parâmetros necessários à execução
   para cada thread */
struct thread_params {
    int thread_count;
    int rank;
    rgb **matriz;
    rgb *paleta;
};

/* Função executada por cada uma das threads */
void *calcula_linhas_mod(void *thread_params0) {
    struct thread_params *params = (struct thread_params *)thread_params0;
    int tcount = params->thread_count;
    int rank = params->rank;
    rgb** matriz = params->matriz;
    rgb *paleta = params->paleta;
    int i, j;

    /* Threads dividem a tarefa por linhas, em round-robin */
    for (i = rank; i < DIMS; i += tcount)
        for (j = 0; j < DIMS; j++)
            matriz[i][j] = paleta[mandelPixel(i, j)];

    return NULL;
}

int main(int argc, char *argv[]) {
    int i, j;
    rgb *paleta;
    rgb **matriz;

    struct thread_params *params;
    pthread_t *threads;

    if (argc < 2) {
        printf("Indique o número de threads\n");
        exit(1);
    }

    int thread_count = atoi(argv[1]);
    printf("Usando %d threads\n", thread_count);

    /* Cálculo totalmente arbitrário para o número de cores. O mais
       natural talvez fosse utilizar uma imagem em tons de cinza
       baseados no número de iterações. Mas colorido fica mais
       divertido! :)
       O cálculo da paleta não é o gargalo. Mantemos
       sequencial, apesar de ser possível paralelizar. */
    paleta = malloc (sizeof(rgb) * CORES);
    for (i = 0; i < CORES; i++) {
        paleta[i].r = (255 - i * 2) % 256;
        paleta[i].g = (i * 11) % 256;
        paleta[i].b = (i * 7) % 256;
    }

    matriz = malloc (sizeof(rgb*) * DIMS);
    for (i = 0; i < DIMS; ++i) {
        matriz[i] = malloc (sizeof(rgb) * DIMS);
    }

    /* Inicia threads e aguarda a sua finalização */
    params = malloc (sizeof(struct thread_params) * thread_count);
    threads = malloc (sizeof(pthread_t) * thread_count);
    for (i = 0; i < thread_count; ++i) {
        params[i].thread_count = thread_count;
        params[i].rank = i;
        params[i].matriz = matriz;
        params[i].paleta = paleta;

        pthread_create(&threads[i], NULL, calcula_linhas_mod, (void*) &params[i]);
    }
    for (i = 0; i < thread_count; i++)
      pthread_join(threads[i], NULL);

    free(params);
    free(threads);
    free(paleta);


    /* A escrita no arquivo também não é o gargalo e pode ser
       sequencial. Também poderia ser paralelizado. Tente fazer!*/
    FILE * fp = fopen(NOME_ARQ, "wb");
    fprintf(fp, "P6\n%d %d\n255\n", DIMS, DIMS);
    for (j = 0; j < DIMS; ++j)
        for (i = 0; i < DIMS; ++i)
            fwrite(&matriz[i][j], 1, 3, fp);
    fclose(fp);

    for (i = 0; i < DIMS; ++i)
        free(matriz[i]);
    free(matriz);

    return 0;
}
