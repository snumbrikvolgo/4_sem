#include <cstring>
#include "ui.h"
#include "tui.h"
#include "gui.h"
#include "game.h"

Ui* Ui::instance;

Ui* Ui::get(const char* what) {
  if (!instance) {
    if (strcmp(what, "tty") == 0)
      instance = new Tty();
    if (strcmp(what, "gui") == 0)
      instance = new Gui();
  }
  return instance;
}

Ui::~Ui() {
  //printf("CALLED DESTRUCTOR ui\n" );
  instance = nullptr;
}
