///
/// Developed by mrybs
///
#include "../mcurses_module.h"

#pragma once

#ifndef MCURSES_SIMPLE_WIDGETS_H
#define MCURSES_SIMPLE_WIDGETS_H

using namespace mcurses;

namespace mcurses{
    class mcurses_simple_figures : public mcurses_module{
    public:
        mcurses_kernel* screen;
        mcurses_simple_figures(const int x,const int y,const int aspect,mcurses_kernel* screen) : mcurses_module(x,y,aspect){
            this->screen = screen;
            this->aspect = aspect;
            this->x = x;
            this->y = y;
        }
        mcurses_simple_figures(const int x,const int y,const int aspect,mcurses_kernel* screen,const std::string background) : mcurses_simple_figures(x,y,aspect,screen)
        {screen->setBackground(background);}

        mcurses_simple_figures* drawRectangle(const int x,const int y,const int width,const int height,const std::string bgColor) {
            for (int i = 0; i < int(x + width); i++) if (i >= (int)x && i <= x + width)
                for (int k = 0; k < int(y + height); k += (int(screen->getAspect()) - 1)) if (k >= y && k <= y + height)
                    screen->drawPoint(i, k, bgColor);
            return this;
        }
        mcurses_simple_figures* drawRectangle(const int x,const int y,const int width,const int height,const std::string color,const std::string background, bool useBackground) {
            for (int i = 0; i < int(x + width); i++) if (i >= (int)x && i <= (int)x + (int)width)
                for (int k = 0; k < int(y + height); k += (int(screen->getAspect()) - 1)) if (k >= y && k <= y + height)
                    screen->drawPoint(i, k, color, background);
            return this;
        }
        mcurses_simple_figures* drawRectangle(const int x,const int y,const int width,const int height,const std::string color,const std::string bgColor) {
          for (int i = 0; i < int(x + width); i++) if (i >= (int)x && i <= (int)x + (int)width)
              for (int k = 0; k < int(y + height); k += (int(screen->getAspect()) - 1)) if (k >= y && k <= y + height)
                  screen->drawPoint(i, k, color, bgColor);
          return this;
        }
        mcurses_simple_figures* drawRectangle(const int x,const int y,const int width,const int height,const std::string color,const std::string bgColor,const std::string background) {
          for (int i = 0; i < x + width; i++) if (i >= (int)x && i <= (int)x + (int)width)
              for (int k = 0; k < y + height; k += (int(screen->getAspect()) - 1)) if (k >= (int)y && k <= (int)y + (int)height)
                  screen->drawPoint(i, k, color, bgColor,background);
          return this;
        }
        mcurses_simple_figures* drawLine(const int x,const int y,const int size,bool vertical,const std::string color) {
          if (vertical) for(int i = y; i < size+y; i++) drawPoint(x,i,color);
          else for(int k = x; k < size+x; k++) drawPoint(k,y,color);
          return this;
        }
        mcurses_simple_figures* drawLine(const int x,const int y,const int size,const bool vertical,const std::string color,const std::string background, bool useBackground) {
            if (vertical) for(int i = y; i < size+y; i++) drawPoint(x,i,color,background);
            else for(int k = x; k < size+x; k++) drawPoint(k,y,color,background);
            return this;
        }
        mcurses_simple_figures* drawLine(const int y,const int x,const int size,const bool vertical,const std::string color,const std::string bgColor) {
          if (vertical) for(int i = y; i < size+y; i++) drawPoint(x,i,color,bgColor);
          else for(int k = x; k < size+x; k++) drawPoint(k,y,color,bgColor);
          return this;
        }
        mcurses_simple_figures* drawLine(const int x,const int y,const int size,const bool vertical,const std::string color,const std::string bgColor,const std::string background) {
          if (vertical) for(int i = y; i < size+y; i++) drawPoint(x,i,color,bgColor,background);
          else for(int k = x; k < size+x; k++) drawPoint(k,y,color,bgColor,background);
          return this;
        }
        mcurses_simple_figures* drawBorder(const float x,float y,const float width,const float height,float size,const std::string color) {
            if(size!=0){
                while(size >= width || size >= height)size-=1;
                //drawLine(x, y, width, false, color);//x-up
                drawLine(x, y, height, true, color);//y-left
                //drawLine(x, y + height, width, false, color);//x-down
                drawLine(x + width-1, y, height + 1, true, color);//y-right
                if(size != 1) drawBorder(x+1,y+1,width-2,height-2,size-1,color);
                return this;
            }
            return this;
        }
        mcurses_simple_figures* drawBorder(const float x,const float y,const float width,const float height,float size,const std::string color,const std::string background, bool useBackground) {
            if(size!=0){
                while(size >= width || size >= height)size-=1;
                drawLine(x, y, width, false, color, background, useBackground);
                drawLine(x, y, height, true, color, background, useBackground);
                drawLine(x, y + height, width, false, color, background, useBackground);
                drawLine(x + width-1, y, height + 1, true, color, background, useBackground);
                if(size != 1) drawBorder(x+1,y+1,width-2,height-2,size-1,color,background, useBackground);
            }
            return this;
        }
        mcurses_simple_figures* drawBorder(const float x,float y,const float width,const float height,float size,const std::string color,const std::string bgColor) {
          if(size!=0){
            while(size >= width || size >= height)size-=1;
            drawLine(x, y, width, false, color, bgColor);//x-up
            drawLine(x, y, height, true, color, bgColor);//y-left
            drawLine(x, y + height, width, false, color, bgColor);//x-down
            drawLine(x + width-1, y, height + 1, true, color, bgColor);//y-right
            if(size != 1) drawBorder(x+1,y+1,width-2,height-2,size-1,color, bgColor);
            return this;
          }
          return this;
        }
        mcurses_simple_figures* drawBorder(const float x,const float y,const float width,const float height,float size,const std::string color,const std::string bgColor,const std::string background) {
          if(size!=0){
            while(size >= width || size >= height)size-=1;
            drawLine(x, y, width, false, color, bgColor, background);
            drawLine(x, y, height, true, color, bgColor, background);
            drawLine(x, y + height, width, false, color, bgColor, background);
            drawLine(x + width-1, y, height, true, color, bgColor, background);
            if(size != 1) drawBorder(x+1,y+1,width-2,height-2,size-1,color, bgColor,background);
          }
          return this;
        }
        mcurses_simple_figures* drawBackground(const std::string color) {
            for (int k = 0; k < screen->getX()/screen->getAspect(); k++)
                for (int i = 0; i < screen->getY(); i++)
                    screen->drawPoint(k, i, color, color);
            screen->setBackgroundColor(color);

            return this;
        }
        mcurses_simple_figures* drawBackground(const std::string color, const std::string backgroundd) {
            for (int i = 0; i < int(screen->getY()); i++)
                for (int k = 0; k < int(screen->getX()/screen->getAspect()); k++)
                    screen->drawPoint(k, i, color, color, backgroundd);
            screen->setBackgroundColor(color);
            return this;
        }
    };
}

#endif