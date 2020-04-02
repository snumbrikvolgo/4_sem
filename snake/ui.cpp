#include <cstring>

#include "ui.h"
#include "tui.h"

Ui* Ui::instance;

Ui* Ui::get(const char* what) {
  if (!instance) {
    if (strcmp(what, "tty") == 0)
      instance = new Tty();
    //if (strcmp(what, "sdl") == 0)
      //instance = new Sdl();
  }
  return instance;
}

Ui::~Ui() {
  instance = nullptr;
}
