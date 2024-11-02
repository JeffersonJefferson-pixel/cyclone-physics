#include <cstdlib>

#include <cyclone/cyclone.h>

class Application 
{
  protected:
    int height;
    int width;
  public:
    virtual void setView();
    virtual void update();
    virtual void display();
    virtual void key(unsigned char key);
    virtual void resize(int width, int height);
    virtual void mouse(int button, int state, int x, int y);
    virtual void initGraphics();
    virtual void deinit();
    virtual const char* getTitle();
    void renderText(float x, float y, const char *text, void* font=NULL);
};