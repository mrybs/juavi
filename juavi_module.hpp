///
/// Developed by mrybs
///
#include "juavi_kernel.hpp"

#pragma once
#ifndef JUAVI_MODULE_HPP
#define JUAVI_MODULE_HPP

using namespace juavi;

namespace juavi{
class juavi_module : public juavi_kernel{
public:
  juavi_module(float x, float y, float aspect) : juavi_kernel(x, y, aspect){}
  juavi_module(float x, float y, float aspect, std::string background) : juavi_kernel(x, y, aspect, background){}
};
}

#endif