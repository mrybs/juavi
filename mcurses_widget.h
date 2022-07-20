#include "mcurses_kernel.h"

using namespace mcurses;

namespace mcurses{
class Imcurses_widget{
public:
  virtual void render() =0;
  virtual void show() =0;
  virtual void hide() =0;

  int isHided = 1;
  int x, y;
};
}
