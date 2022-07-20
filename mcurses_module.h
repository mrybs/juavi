#include "mcurses_kernel.h"

#pragma once
#ifndef MCURSES_MODULE_H
#define MCURSES_MODULE_H

using namespace mcurses;

namespace mcurses{
class mcurses_module : public mcurses_kernel{
public:
    mcurses_module(float x, float y, float aspect) : mcurses_kernel(x, y, aspect){}
    mcurses_module(float x, float y, float aspect, std::string background) : mcurses_kernel(x, y, aspect, background){}
};
}

#endif