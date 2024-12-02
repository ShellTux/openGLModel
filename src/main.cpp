#include "OBJModel.hpp"
#include "types.hpp"

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <cstdlib>
#include <iostream>

f64 angle = 0;

static void usage(const char *const program) {
  std::cerr << "Usage " << program << ": <model path>" << std::endl;
  exit(EXIT_FAILURE);
}

void configureLighting() {
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  GLfloat light_position[] = {5.0f, 5.0f, 5.0f, 1.0f};
  GLfloat ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
  GLfloat diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
  GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};

  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
}

void configureMaterial() {
  GLfloat ambient[] = {0.1f, 0.1f, 0.1f, 1.0f};
  GLfloat diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
  GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
  GLfloat shininess[] = {32.0f};

  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}

int main(int argc, char **argv) {
  if (argc < 2) {
    usage(argv[0]);
  }

  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  glfwWindowHintString(GLFW_X11_CLASS_NAME, "OpenGL");
  glfwWindowHintString(GLFW_WAYLAND_APP_ID, "OpenGL");

  GLFWwindow *window =
      glfwCreateWindow(800, 600, "OpenGL OBJ Model Viewer", nullptr, nullptr);

  if (!window) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  OBJModel model(argv[1]);
  std::cout << model << std::endl;

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  configureLighting();
  configureMaterial();
  glCullFace(GL_FRONT);

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(angle, 0, 1, 0);
    model.draw();

    glfwSwapBuffers(window);
    glfwPollEvents();

    angle += 1;
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
