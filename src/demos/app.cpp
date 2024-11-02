#include "app.h"
#include "../ogl_headers.h"

void Application::initGraphics() 
{
  glClearColor(0.9f, 0.95f, 1.0f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);

  setView();
}

void Application::setView() 
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, (double)width / (double)height, 1.0, 500.0);
  glMatrixMode(GL_MODELVIEW);
}

void Application::display()
{
  glClear(GL_COLOR_BUFFER);

  glBegin(GL_LINES);
  glVertex2i(1, 1);
  glVertex2i(639, 639);
  glEnd();
}

void Application::update() 
{
  glutPostRedisplay();
}

void Application::deinit()
{
}

void Application::key(unsigned char key)
{
}

void Application::mouse(int button, int state, int x, int y)
{
}

void Application::renderText(float x, float y, const char *text, void *font)
{

}

const char* Application::getTitle()
{
  return "Cyclone Demo";
}