#ifndef _APPLICATION_GUI_
#define _APPLICATION_GUI_

#include <nanogui/nanogui.h>
#include <nanogui/glutil.h>
#include "world.hpp"
#include "utilities/buildFunctions.hpp"

class AppGUI : public nanogui::Screen{
public:
  AppGUI(int, int, const std::string &, bool);
  ~AppGUI();

  virtual bool keyboardEvent(int, int, int, int);

  virtual void draw(NVGcontext *);

  virtual void drawContents();

private:
  nanogui::ImageView * viewer;
  nanogui::GLShader mShader;
  World * w;
  bool vai = false;
};

#endif
