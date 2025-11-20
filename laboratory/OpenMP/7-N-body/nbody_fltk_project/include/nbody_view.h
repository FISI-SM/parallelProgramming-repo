#ifndef NBODY_VIEW_H
#define NBODY_VIEW_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Widget.H>
#include <FL/fl_draw.H>

extern "C" {
#include "nbody_basic.h"
}

/* Widget que muestra el sistema N-body en 2D usando FLTK */
class NBodyWidget : public Fl_Widget {
public:
    NBodyWidget(int X, int Y, int W, int H, int n_particles, double delta_t);
    virtual ~NBodyWidget();

    void step();  // Avanza una iteración de la simulación

protected:
    void draw() override;

private:
    int n;
    double dt;
    particle_s* curr;
    vect_t* forces;

    void compute_bounds(double& minx, double& maxx,
                        double& miny, double& maxy);
    void world_to_screen(double wx, double wy,
                         double minx, double miny,
                         double dx, double dy,
                         int& sx, int& sy);
};

/* Callback de temporizador para animación */
void timer_cb(void* data);

#endif
