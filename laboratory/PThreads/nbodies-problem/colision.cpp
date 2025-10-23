// main.cpp
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <pthread.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <cstdlib>

#define N 1000
#define DT 0.01f
#define G 6.67430e-11f
#define NUM_THREADS 4
#define COLLISION_RADIUS 0.005f

struct Body {
    float x, y;
    float vx, vy;
    float mass;
};

std::vector<Body> bodies(N);
pthread_barrier_t barrier;

void resolve_collision(Body& a, Body& b) {
    // Intercambiar velocidades como colisión elástica simple en 2D
    std::swap(a.vx, b.vx);
    std::swap(a.vy, b.vy);
}

void* simulate(void* arg) {
    int id = (long)arg;
    int chunk = N / NUM_THREADS;
    int start = id * chunk;
    int end = (id == NUM_THREADS - 1) ? N : start + chunk;

    for (;;) {
        for (int i = start; i < end; ++i) {
            float ax = 0.0f, ay = 0.0f;
            for (int j = 0; j < N; ++j) {
                if (i == j) continue;
                float dx = bodies[j].x - bodies[i].x;
                float dy = bodies[j].y - bodies[i].y;
                float dist = sqrtf(dx*dx + dy*dy + 1e-10f);

                // Colisión: intercambiar velocidades si muy cercanos
                if (dist < COLLISION_RADIUS) {
                    resolve_collision(bodies[i], bodies[j]);
                    continue;
                }

                float force = G * bodies[j].mass / (dist * dist);
                ax += force * dx / dist;
                ay += force * dy / dist;
            }
            bodies[i].vx += ax * DT;
            bodies[i].vy += ay * DT;
        }
        pthread_barrier_wait(&barrier);

        for (int i = start; i < end; ++i) {
            bodies[i].x += bodies[i].vx * DT;
            bodies[i].y += bodies[i].vy * DT;
        }
        pthread_barrier_wait(&barrier);
    }
    return nullptr;
}

std::string loadShader(const char* path) {
    std::ifstream file(path);
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "N-Body OpenGL", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glewInit();

    pthread_barrier_init(&barrier, nullptr, NUM_THREADS);
    for (int i = 0; i < N; ++i) {
        bodies[i].x = ((rand() % 1000) / 500.0f) - 1.0f;
        bodies[i].y = ((rand() % 1000) / 500.0f) - 1.0f;
        bodies[i].vx = bodies[i].vy = 0.0f;
        bodies[i].mass = 1e5f;
    }

    pthread_t threads[NUM_THREADS];
    for (long t = 0; t < NUM_THREADS; ++t)
        pthread_create(&threads[t], nullptr, simulate, (void*)t);

    std::vector<float> posData(N * 2);
    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * posData.size(), nullptr, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    std::string vsCode = loadShader("points.vert");
    std::string fsCode = loadShader("points.frag");
    const char* vsSrc = vsCode.c_str();
    const char* fsSrc = fsCode.c_str();

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vsSrc, nullptr);
    glCompileShader(vs);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fsSrc, nullptr);
    glCompileShader(fs);

    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glUseProgram(program);

    while (!glfwWindowShouldClose(window)) {
        for (int i = 0; i < N; ++i) {
            posData[2 * i] = bodies[i].x;
            posData[2 * i + 1] = bodies[i].y;
        }
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * posData.size(), posData.data());

        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_POINTS, 0, N);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(program);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
