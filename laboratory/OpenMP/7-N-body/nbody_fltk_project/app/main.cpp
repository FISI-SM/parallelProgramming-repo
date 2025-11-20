#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include "nbody_view.h"

int main(int argc, char** argv) {
    int n  = 10;
    double dt = 0.01;

    if (argc >= 2) {
        int tmp = atoi(argv[1]);
        if (tmp > 0) n = tmp;
    }
    if (argc >= 3) {
        double tmpdt = atof(argv[2]);
        if (tmpdt > 0) dt = tmpdt;
    }

    Fl_Window win(800, 600, "N-Body FLTK");
    NBodyWidget widget(10, 10, 780, 580, n, dt);
    win.end();
    win.show(argc, argv);

    Fl::add_timeout(0.016, timer_cb, &widget);

    return Fl::run();
}
