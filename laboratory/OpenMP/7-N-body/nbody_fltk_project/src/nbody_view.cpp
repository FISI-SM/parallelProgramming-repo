#include "nbody_view.h"

NBodyWidget::NBodyWidget(int X, int Y, int W, int H, int n_particles, double delta_t)
    : Fl_Widget(X, Y, W, H), n(n_particles), dt(delta_t) {

    curr   = new particle_s[n];
    forces = new vect_t[n];
    Gen_init_cond(curr, n);
}

NBodyWidget::~NBodyWidget() {
    delete[] curr;
    delete[] forces;
}

void NBodyWidget::step() {
    for (int i = 0; i < n; i++)
        Compute_force(i, forces, curr, n);

    for (int i = 0; i < n; i++)
        Update_part(i, forces, curr, n, dt);

    redraw();
}

void NBodyWidget::compute_bounds(double& minx, double& maxx,
                                 double& miny, double& maxy) {
    if (n <= 0) {
        minx = maxx = miny = maxy = 0.0;
        return;
    }

    minx = maxx = curr[0].s[X];
    miny = maxy = curr[0].s[Y];

    for (int i = 1; i < n; i++) {
        if (curr[i].s[X] < minx) minx = curr[i].s[X];
        if (curr[i].s[X] > maxx) maxx = curr[i].s[X];
        if (curr[i].s[Y] < miny) miny = curr[i].s[Y];
        if (curr[i].s[Y] > maxy) maxy = curr[i].s[Y];
    }
}

void NBodyWidget::world_to_screen(double wx, double wy,
                                  double minx, double miny,
                                  double dx, double dy,
                                  int& sx, int& sy) {
    double fx = (wx - minx) / dx;
    double fy = (wy - miny) / dy;

    sx = x() + static_cast<int>(fx * w());
    sy = y() + h() - static_cast<int>(fy * h());
}

void NBodyWidget::draw() {
    fl_color(FL_WHITE);
    fl_rectf(x(), y(), w(), h());

    if (n <= 0) return;

    double minx, maxx, miny, maxy;
    compute_bounds(minx, maxx, miny, maxy);

    double dx = maxx - minx;
    double dy = maxy - miny;
    if (dx == 0.0) dx = 1.0;
    if (dy == 0.0) dy = 1.0;

    fl_color(FL_BLACK);
    const int radius = 4;

    for (int i = 0; i < n; i++) {
        int sx, sy;
        world_to_screen(curr[i].s[X], curr[i].s[Y],
                        minx, miny, dx, dy, sx, sy);
        fl_pie(sx - radius, sy - radius, 2 * radius, 2 * radius, 0, 360);
    }
}

void timer_cb(void* data) {
    NBodyWidget* w = static_cast<NBodyWidget*>(data);
    w->step();
    Fl::repeat_timeout(0.016, timer_cb, data);
}
