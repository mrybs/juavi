#include "../mcurses_module.h"

#pragma once

#ifndef MCURSES_BACKGROUNDS_H
#define MCURSES_BACKGROUNDS_H

using namespace std;
using namespace mcurses;

namespace mcurses{
    class mcurses_backgrounds : public mcurses_module{
    public:
        mcurses_kernel* screen;
        //mcurses_simple_figures() : mcurses_module(){}
        mcurses_backgrounds(float x, float y, float aspect) : mcurses_module(x, y, aspect){
            //this->screen = screen;
        }
        mcurses_backgrounds(float x, float y, float aspect, char background) : mcurses_backgrounds(x, y, aspect){}

        void drawBackground(){
            float screenX = screen->getX();
            float screenY = screen->getY();
            float screenAspect = screen->getAspect();
            for (int k = 0; k < int(screenX/screenAspect); k++)
                for (int i = 0; i < int(screenY); i++)
                    if(k%2==0)
                        screen->drawPoint((float)i, (float)k, "GREEN", "GREEN");
                    else
                        screen->drawPoint((float)i, (float)k, "RED", "RED");
        }
    };
}

#endif