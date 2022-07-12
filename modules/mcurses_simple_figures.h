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
        mcurses_simple_figures(const float x,const float y,const float aspect,mcurses_kernel* screen) : mcurses_module(x,y,aspect){
            this->screen = screen;
            this->aspect = aspect;
            this->x = x;
            this->y = y;
        }
        mcurses_simple_figures(const float x,const float y,const float aspect,mcurses_kernel* screen,const char background) : mcurses_simple_figures(x,y,aspect,screen)
        {screen->setBackground(background);}

        mcurses_simple_figures drawRectangle(const float x,const float y,const float width,const float height,const string bgColor) {
            for (int i = 0; i < int(y + width); i++) if (i >= (int)y && i <= (int)y + (int)width)
                for (int k = 0; k < int(x + height); k += (int(screen->getAspect()) - 1)) if (k >= (int)x && k <= (int)x + (int)height)
                    screen->drawPoint((float)i, (float)k, bgColor);
            return *this;
        }
        mcurses_simple_figures drawRectangle(const float x,const float y,const float width,const float height,const string color,const char background) {
            for (int i = 0; i < int(y + width); i++) if (i >= (int)y && i <= (int)y + (int)width)
                for (int k = 0; k < int(x + height); k += (int(screen->getAspect()) - 1)) if (k >= (int)x && k <= (int)x + (int)height)
                    screen->drawPoint((float)i, (float)k, color, background);
            return *this;
        }
        mcurses_simple_figures drawRectangle(const float x,const float y,const float width,const float height,const string color,const string bgColor) {
          for (int i = 0; i < int(y + width); i++) if (i >= (int)y && i <= (int)y + (int)width)
              for (int k = 0; k < int(x + height); k += (int(screen->getAspect()) - 1)) if (k >= (int)x && k <= (int)x + (int)height)
                  screen->drawPoint((float)i, (float)k, color, bgColor);
          return *this;
        }
        mcurses_simple_figures drawRectangle(const float x,const float y,const float width,const float height,const string color,const string bgColor,const char background) {
          for (int i = 0; i < int(y + width); i++) if (i >= (int)y && i <= (int)y + (int)width)
              for (int k = 0; k < int(x + height); k += (int(screen->getAspect()) - 1)) if (k >= (int)x && k <= (int)x + (int)height)
                  screen->drawPoint((float)i, (float)k, color, bgColor,background);
          return *this;
        }
        mcurses_simple_figures drawLine(float x,float y,float size,bool vertical,const string color) {
          if (vertical) for(int i = y; i < size+y; i++) drawPoint(x,i,color);
          else for(int k = x; k < size+x; k++) drawPoint(k,y,color);
          return *this;
        }
        mcurses_simple_figures drawLine(const float x,const float y,const float size,const bool vertical,const string color,const char background) {
            if (vertical) for(int i = y; i < size+y; i++) drawPoint(x,i,color,background);
            else for(int k = x; k < size+x; k++) drawPoint(k,y,color,background);
            return *this;
        }
        mcurses_simple_figures drawLine(float x,float y,float size,bool vertical,const string color,const string bgColor) {
          if (vertical) for(int i = y; i < size+y; i++) drawPoint(x,i,color,bgColor);
          else for(int k = x; k < size+x; k++) drawPoint(k,y,color,bgColor);
          return *this;
        }
        mcurses_simple_figures drawLine(const float x,const float y,const float size,const bool vertical,const string color,const string bgColor,const char background) {
          if (vertical) for(int i = y; i < size+y; i++) drawPoint(x,i,color,bgColor,background);
          else for(int k = x; k < size+x; k++) drawPoint(k,y,color,bgColor,background);
          return *this;
        }
        mcurses_simple_figures drawBorder(const float x,float y,const float width,const float height,float size,const string color) {
            if(size!=0){
                while(size >= width || size >= height)size-=1;
                drawLine(x, y, width, false, color);//x-up
                drawLine(x, y, height, true, color);//y-left
                drawLine(x, y + height, width, false, color);//x-down
                drawLine(x + width-1, y, height + 1, true, color);//y-right
                if(size != 1) drawBorder(x+1,y+1,width-2,height-2,size-1,color);
                return *this;
            }
            return *this;
        }
        mcurses_simple_figures drawBorder(const float x,const float y,const float width,const float height,float size,const string color,const char background) {
            if(size!=0){
                while(size >= width || size >= height)size-=1;
                drawLine(x, y, width, false, color, background);
                drawLine(x, y, height, true, color, background);
                drawLine(x, y + height, width, false, color, background);
                drawLine(x + width-1, y, height + 1, true, color, background);
                if(size != 1) drawBorder(x+1,y+1,width-2,height-2,size-1,color,background);
            }
            return *this;
        }
        mcurses_simple_figures drawBorder(const float x,float y,const float width,const float height,float size,const string color,const string bgColor) {
          if(size!=0){
            while(size >= width || size >= height)size-=1;
            drawLine(x, y, width, false, color, bgColor);//x-up
            drawLine(x, y, height, true, color, bgColor);//y-left
            drawLine(x, y + height, width, false, color, bgColor);//x-down
            drawLine(x + width-1, y, height + 1, true, color, bgColor);//y-right
            if(size != 1) drawBorder(x+1,y+1,width-2,height-2,size-1,color, bgColor);
            return *this;
          }
          return *this;
        }
        mcurses_simple_figures drawBorder(const float x,const float y,const float width,const float height,float size,const string color,const string bgColor,const char background) {
          if(size!=0){
            while(size >= width || size >= height)size-=1;
            drawLine(x, y, width, false, color, bgColor, background);
            drawLine(x, y, height, true, color, bgColor, background);
            drawLine(x, y + height, width, false, color, bgColor, background);
            drawLine(x + width-1, y, height + 1, true, color, bgColor, background);
            if(size != 1) drawBorder(x+1,y+1,width-2,height-2,size-1,color, bgColor,background);
          }
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