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
        mcurses_simple_figures(float x, float y, float aspect) : mcurses_module(x, y, aspect){
            //this->screen = screen;
        }
        mcurses_simple_figures(float x, float y, float aspect, char background, mcurses_kernel screen) : mcurses_simple_figures(x, y, aspect){}

        void drawRectangle(float x, float y, float width, float height, string bgColor) {
            float screenAspect = screen->getAspect();
            string pixel = string(bgColor);
            for (int i = 0; i < int(y + width); i++)
                if (i >= (int)y && i <= (int)y + (int)width)
                    for (int k = 0; k < int(x + height); k += (int(screenAspect) - 1))
                        if (k >= (int)x && k <= (int)x + (int)height)
                            screen->drawPoint((float)k, (float)i, bgColor);
        }
        void drawRectangle(float x, float y, float width, float height, string color, char backgroundd) {
            float screenAspect = screen->getAspect();
            string pixel = string(color);
            for (int i = 0; i < int(y + width); i++)
                if (i >= (int)y && i <= (int)y + (int)width)
                    for (int k = 0; k < int(x + height); k += (int(screenAspect) - 1))
                        if (k >= (int)x && k <= (int)x + (int)height)
                            screen->drawPoint((float)k, (float)i, color, backgroundd);
        }
        void drawLine(float x, float y, float size, bool vertical, string color) {
            float screenAspect = screen->getAspect();
            if (vertical) {
                for (int i = 0; i < int(y + size); i++)
                    if (i >= (int)y && i <= (int)y + (int)size)
                        screen->drawPoint(x,(float)i,color);
            } else {
                for (int k = 0; k < int(x + size)-1; k += (int(screenAspect) - 1))
                    if (k >= (int)x && k <= (int)x + (int)size)
                        screen->drawPoint((float)k, y, color);
            }
        }
        void drawLine(float x, float y, float size, bool vertical, string color, char backgroundd) {
            float screenAspect = screen->getAspect();
            if (vertical)
                for (int i = 0; i < int(y + size); i++)
                    if (i >= (int)y && i <= (int)y + (int)size) {
                        for (int j = 0; j < int(screenAspect); j++)
                            screen->drawPoint(x+(float)j,(float)i,color);
                    }
                    else {
                        for (int k = 0; k < int(x + size); k += (int(screenAspect) - 1))
                            if (k >= (int)x && k <= (int)x + (int)size)
                                screen->drawPoint((float)k, y, color, backgroundd);
                    }
            else {
                for (int k = 0; k < int(x + size); k += (int(screenAspect) - 1))
                    if (k >= (int)x && k <= (int)x + (int)size)
                        screen->drawPoint((float)k, y, color, backgroundd);
            }
        }
        void drawBorder(float x, float y, float width, float height, float size, string color) {
            while(size >= width || size >= height)size-=1;
            drawLine(x, y, width, false, color);//x-up
            drawLine(x, y, width, true, color);//y-left
            drawLine(x, y + height, width, false, color);//x-down
            drawLine(x + width-1, y, width + 1, true, color);//y-right
            if(size != 1) drawBorder(x+1,y+1,width-2,height-2,size-1,color);
        }
        void drawBorder(float x, float y, float width, float height, float size, string color, char background) {
            while(size >= width || size >= height)size-=1;
            drawLine(x, y, width, false, color, background);
            drawLine(x, y, width, true, color, background);
            drawLine(x, y + height, width, false, color, background);
            drawLine(x + width, y, width + 1, true, color, background);
            if(size != 1) drawBorder(x+1,y+1,width-2,height-2,size-1,color);
        }
        void print(string text, float x, float y, string color, string bgColor) {
            color = getColor(color, true);
            bgColor = getColor(bgColor, false);
            string pixel;
            for (int i = 0; i < text.length(); i++) {
                pixel += color;
                pixel += bgColor;
                pixel += text[i];
                pixel += DEFAULT;
                screen->setCursor(x+(float)i, y);
                cout << pixel;
            }
        }
        void drawBackground(string color) {
            float screenX = screen->getX();
            float screenY = screen->getY();
            float screenAspect = getAspect();
            for (int k = 0; k < int(screenX/screenAspect); k++)
                for (int i = 0; i < int(screenY); i++)
                    screen->drawPoint((float)i, (float)k, color, color);
            screen->setBackgroundColor(color);
        }
        void drawBackground(string &color, char backgroundd) {
            float screenX = screen->getX();
            float screenY = screen->getY();
            float screenAspect = getAspect();
            for (int i = 0; i < int(screenY); i++) {
                for (int k = 0; k < int(screenX/screenAspect); k++)
                    screen->drawPoint((float)k, (float)i, color, color, backgroundd);
            }
            screen->setBackgroundColor(color);
        }
    };
}

#endif