///
/// Developed by mrybs
///
#include "juavi_kernel.hpp"

#ifndef JUAVI_WIDGET_HPP
#define JUAVI_WIDGET_HPP

using namespace juavi;

namespace juavi{
class Ijuavi_widget : public juavi_kernel{
public:
  virtual void render() = 0;
  virtual void show() = 0;
  virtual void hide() = 0;

  void cycle(){}

  int isHided = 1;
  int x, y, aspect;
};
}

#endif
