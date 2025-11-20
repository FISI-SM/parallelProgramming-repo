#include <math.h>
#include <stdlib.h>
#include "nbody_basic.h"

const double G = 6.673e-11;

void Gen_init_cond(struct particle_s curr[], int n) {
    int part;
    double mass  = 5.0e24;
    double gap   = 1.0e5;
    double speed = 3.0e4;

    for (part = 0; part < n; part++) {
        curr[part].m    = mass;
        curr[part].s[X] = part * gap;
        curr[part].s[Y] = 0.0;
        curr[part].v[X] = 0.0;

        if (part % 2 == 0)
            curr[part].v[Y] = speed;
        else
            curr[part].v[Y] = -speed;
    }
}

void Compute_force(int part, vect_t forces[], struct particle_s curr[], int n) {

    forces[part][X] = 0.0;
    forces[part][Y] = 0.0;

    for (int k = 0; k < n; k++) {
        if (k == part) continue;

        double dx = curr[part].s[X] - curr[k].s[X];
        double dy = curr[part].s[Y] - curr[k].s[Y];

        double len = sqrt(dx*dx + dy*dy);
        if (len == 0) continue;

        double len3 = len * len * len;
        double fact = -G * curr[part].m * curr[k].m / len3;

        forces[part][X] += dx * fact;
        forces[part][Y] += dy * fact;
    }
}

void Update_part(int part, vect_t forces[], struct particle_s curr[],
                 int n, double delta_t) {

    (void)n;

    double fact = delta_t / curr[part].m;

    curr[part].s[X] += delta_t * curr[part].v[X];
    curr[part].s[Y] += delta_t * curr[part].v[Y];

    curr[part].v[X] += fact * forces[part][X];
    curr[part].v[Y] += fact * forces[part][Y];
}
