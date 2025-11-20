#ifndef NBODY_BASIC_H
#define NBODY_BASIC_H

#ifdef __cplusplus
extern "C" {
#endif

#define DIM 2
#define X 0
#define Y 1

typedef double vect_t[DIM];

struct particle_s {
    double m;
    vect_t s;
    vect_t v;
};

void Gen_init_cond(struct particle_s curr[], int n);
void Compute_force(int part, vect_t forces[], struct particle_s curr[], int n);
void Update_part(int part, vect_t forces[], struct particle_s curr[],
                 int n, double delta_t);

#ifdef __cplusplus
}
#endif

#endif
