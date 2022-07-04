#include "../mcurses_module.h"

#pragma once

#ifndef MCURSES_SIMPLE_WIDGETS_H
#define MCURSES_SIMPLE_WIDGETS_H

using namespace std;
using namespace mcurses;

namespace mcurses{
    class mcurses_simple_figures : public mcurses_module{
    public:
        mcurses_kernel* screen;
        mcurses_simple_figures(const float x,const float y,const float aspect,mcurses_kernel* screen) : mcurses_module(x,y,aspect)
        {this->screen = screen;}
        mcurses_simple_figures(const float x,const float y,const float aspect,mcurses_kernel* screen,const char background) : mcurses_simple_figures(x,y,aspect,screen)
        {screen->setBackground(background);}

        mcurses_simple_figures drawRectangle(const float x,const float y,const float width,const float height,const string bgColor) {
            for (int i = 0; i < int(y + width); i++) if (i >= (int)y && i <= (int)y + (int)width)
                for (int k = 0; k < int(x + height); k += (int(screen->getAspect()) - 1)) if (k >= (int)x && k <= (int)x + (int)height)
                    screen->drawPoint((float)k, (float)i, bgColor);
            return *this;
        }
        mcurses_simple_figures drawRectangle(const float x,const float y,const float width,const float height,const string color,const char background) {
            for (int i = 0; i < int(y + width) && (i >= (int)y && i <= (int)y + (int)width); i++)
                for (int k = 0; k < int(x + height) && (k >= (int)x && k <= (int)x + (int)height); k += (int(screen->getAspect()) - 1))
                    screen->drawPoint((float)k, (float)i, color, background);
            return *this;
        }
        mcurses_simple_figures drawLine(const float x,const float y,const float size,const bool vertical,const string color) {
            for (int i = 0; i < int(y + size) && (i >= (int)y && i <= (int)y + (int)size) && vertical; i++)
                screen->drawPoint(x,(float)i,color);
            for (int k = 0; k < int(x + size)-1 && (k >= (int)x && k <= (int)x + (int)size) && !vertical; k += (int(screen->getAspect()) - 1))
                screen->drawPoint((float)k, y, color);
            return *this;
        }
        mcurses_simple_figures drawLine(const float x,const float y,const float size,const bool vertical,const string color,const char background) {
            for (int i = 0; i < int(y + size) && vertical; i++) {
                for (int j = 0; j < int(screen->getAspect()) && (i >= (int)y && i <= (int)y + (int)size); j++)
                  screen->drawPoint(x + (float)j, (float)i, color);
                for (int k = 0; k < int(x + size) && (k >= (int)x && k <= (int)x + (int)size) && !(i >= (int)y && i <= (int)y + (int)size); k += (int(screen->getAspect()) - 1))
                  screen->drawPoint((float)k, y, color, background);
            }
            for (int k = 0; k < int(x + size) && (k >= (int)x && k <= (int)x + (int)size) && !vertical; k += (int(screen->getAspect()) - 1))
                screen->drawPoint((float)k, y, color, background);
            return *this;
        }
        mcurses_simple_figures drawBorder(const float x,float y,const float width,const float height,float size,const string color) {
            while(size >= width || size >= height)size-=1;
            drawLine(x, y, width, false, color);//x-up
            drawLine(x, y, width, true, color);//y-left
            drawLine(x, y + height, width, false, color);//x-down
            drawLine(x + width-1, y, width + 1, true, color);//y-right
            if(size != 1) drawBorder(x+1,y+1,width-2,height-2,size-1,color);
            return *this;
        }
        mcurses_simple_figures drawBorder(const float x,const float y,const float width,const float height,float size,const string color,const char background) {
            while(size >= width || size >= height)size-=1;
            drawLine(x, y, width, false, color, background);
            drawLine(x, y, width, true, color, background);
            drawLine(x, y + height, width, false, color, background);
            drawLine(x + width, y, width + 1, true, color, background);
            if(size != 1) drawBorder(x+1,y+1,width-2,height-2,size-1,color);
            return *this;
        }
        mcurses_simple_figures drawBackground(const string color) {
            for (int k = 0; k < int(screen->getX()/screen->getAspect()); k++)
                for (int i = 0; i < int(screen->getY()); i++)
                    screen->drawPoint((float)i, (float)k, color, color);
            screen->setBackgroundColor(color);
            return *this;
        }
        mcurses_simple_figures drawBackground(const string color, const char backgroundd) {
            for (int i = 0; i < int(screen->getY()); i++)
                for (int k = 0; k < int(screen->getX()/screen->getAspect()); k++)
                    screen->drawPoint((float)k, (float)i, color, color, backgroundd);
            screen->setBackgroundColor(color);
            return *this;
        }
    };
}

#endif