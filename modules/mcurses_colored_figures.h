#include "../mcurses_module.h"
#include <random>

#pragma once

#ifndef MCURSES_BACKGROUNDS_H
#define MCURSES_BACKGROUNDS_H

using namespace mcurses;

namespace mcurses{
    class mcurses_colored_figures : public mcurses_module{
    public:
        mcurses_kernel* screen;

        //mcurses_simple_figures() : mcurses_module(){}
        mcurses_colored_figures(int x,int y,float aspect,mcurses_kernel*screen) : mcurses_module(x, y, aspect){this->screen=screen;}
        mcurses_colored_figures(int x,int y,float aspect,mcurses_kernel*screen,std::string background) : mcurses_colored_figures(x, y, aspect,screen){this->screen=screen;}

        mcurses_colored_figures* drawPointStripesH(int x,int y,const std::string firstColor,const std::string secondColor){
            if(int(x)%2==0) screen->drawPoint(y, x, firstColor, secondColor);
            else screen->drawPoint(y, x, secondColor, firstColor);
            return this;
        }
        mcurses_colored_figures* drawPointStripesV(int x,int y,const std::string firstColor,const std::string secondColor){
            if(int(y)%2==0) screen->drawPoint(x, y, firstColor, secondColor);
            else screen->drawPoint(x, y, secondColor, firstColor);
            return this;
        }
        mcurses_colored_figures* drawPointCross(int x,int y,const std::string firstColor,const std::string secondColor,bool type){
            if (int(y) % 2 == type) screen->drawPoint( x, y, firstColor, secondColor);
            else screen->drawPoint(y, x, secondColor, firstColor);
            if (int(x) % 2 == type) screen->drawPoint(x, y, firstColor, secondColor);
            return this;
        }
        mcurses_colored_figures* drawPointRandom(int x, int y){
            screen->drawPoint(x, y, randomColorName(), randomColorName());
            return this;
        }
        mcurses_colored_figures* drawPointStripesH(int x,int y,const std::string firstColor,const std::string secondColor,std::string background){
            if(int(x)%2==0) screen->drawPoint(x, y, secondColor, firstColor, background);
            else screen->drawPoint(x, y, firstColor, secondColor, background);
            return this;
        }
        mcurses_colored_figures* drawPointStripesV(int x,int y,const std::string firstColor,const std::string secondColor,std::string background){
            if(int(y)%2==0) screen->drawPoint(x, y, firstColor, firstColor);
            else screen->drawPoint(x, y, secondColor, secondColor);
            return this;
        }
        mcurses_colored_figures* drawPointCross(int x,int y,const std::string firstColor,const std::string secondColor,bool type,std::string background){
            if (int(y) % 2 == type) screen->drawPoint(x, y, firstColor, firstColor);
            else screen->drawPoint(x, y, secondColor, secondColor);
            if (int(x) % 2 == type) screen->drawPoint(x, y, firstColor, firstColor);
            return this;
        }
        mcurses_colored_figures* drawPointRandom(int x,int y,std::string background){
            screen->drawPoint(x, y, randomColorName(), randomColorName());
            return this;
        }

        mcurses_colored_figures* drawRectangleStripesH(int x,int y,float width,float height,const std::string firstColor,const std::string secondColor) {
            for (int i = 0; i < int(y + width); i++)
                if (i >= y && i <= y + width)
                    for (int k = 0; k < int(x + height); k += (int(screen->getAspect()) - 1))
                        if (k >= x && k <= x + height)
                            drawPointStripesH(k,i,firstColor, secondColor);
            return this;
        }
        mcurses_colored_figures* drawRectangleStripesHRandom(int x,int y,float width,float height) {
            return drawRectangleStripesH(x, y, width, height, randomColorName(), randomColorName());
        }
        mcurses_colored_figures* drawRectangleStripesV(int x,int y,float width,float height,const std::string firstColor,const std::string secondColor) {
            for (int i = 0; i < int(y + width); i++)
                if (i >= y && i <= y + width)
                    for (int k = 0; k < int(x + height); k += (int(screen->getAspect()) - 1))
                        if (k >= x && k <= x + height)
                            drawPointStripesV(k,i,firstColor, secondColor);
            return this;
        }
        mcurses_colored_figures* drawRectangleStripesVRandom(int x,int y,float width,float height) {
            return drawRectangleStripesV(x,y,width,height,randomColorName(),randomColorName());
        }
        mcurses_colored_figures* drawRectangleCross(int x,int y,float width,float height,const std::string firstColor,const std::string secondColor,bool type) {
            for (int k = 0; k < int(screen->getX() / screen->getAspect()); k++)
                if (k >= x && k <= x + height)
                    for (int i = 0; i < int(screen->getY()); i++)
                        if (i >= y && i <= y + width)
                            drawPointCross(k, i, firstColor, secondColor, type);
            return this;
        }
        mcurses_colored_figures* drawRectangleCrossRandom(int x,int y,float width,float height,bool type) {
            return drawRectangleCross(x,y,width,height,randomColorName(),randomColorName(),type);
        }
        mcurses_colored_figures* drawRectangleRandom(int x, int y, float width, float height) {
            for (int i = 0; i < int(y + width); i++)
                if (i >= y && i <= y + width)
                    for (int k = 0; k < int(x + height); k += (int(screen->getAspect()) - 1))
                        if (k >= x && k <= x + height)
                            drawPointRandom(i,k);
            return this;
        }
        mcurses_colored_figures* drawRectangleStripesH(int x,int y,float width,float height,const std::string firstColor,const std::string secondColor,std::string background) {
            for (int i = 0; i < int(y + width); i++)
                if (i >= y && i <= y + width)
                    for (int k = 0; k < int(x + height); k += (int(screen->getAspect()) - 1))
                        if (k >= x && k <= x + height)
                            drawPointStripesH(k,i,firstColor,secondColor,background);
            return this;
        }
        mcurses_colored_figures* drawRectangleStripesHRandom(int x,int y,float width,float height,std::string background) {
            return drawRectangleStripesH(x,y,width,height,randomColorName(),randomColorName(),background);
        }
        mcurses_colored_figures* drawRectangleStripesV(int x,int y,float width,float height,const std::string firstColor,const std::string secondColor,std::string background) {
            for (int i = 0; i < int(y + width); i++)
                if (i >= y && i <= y + width)
                    for (int k = 0; k < int(x + height); k += (int(screen->getAspect()) - 1))
                        if (k >= x && k <= x + height)
                            drawPointStripesV(k,i,firstColor,secondColor,background);
            return this;
        }
        mcurses_colored_figures* drawRectangleStripesVRandom(int x,int y,float width,float height,std::string background) {
            return drawRectangleStripesV(x,y,width,height,randomColorName(),randomColorName(),background);
        }
        mcurses_colored_figures* drawRectangleCross(int x,int y,float width,float height,const std::string firstColor,const std::string secondColor,bool type,std::string background) {
            for (int k = 0; k < int(screen->getX() / screen->getAspect()); k++)
                if (k >= x && k <= x + height)
                    for (int i = 0; i < int(screen->getY()); i++)
                        if (i >= y && i <= y + width)
                            drawPointCross(k, i, firstColor, secondColor, type, background);
            return this;
        }
        mcurses_colored_figures* drawRectangleCrossRandom(int x,int y,float width,float height,const bool type,std::string background) {
            return drawRectangleCross(x,y,width,height,randomColorName(),randomColorName(),type,background);
        }
        mcurses_colored_figures* drawRectangleRandom(int x,int y,float width,float height,std::string background) {
            for (int i = 0; i < int(y + width); i++)
                if (i >= y && i <= y + width)
                    for (int k = 0; k < int(x + height); k += (int(screen->getAspect()) - 1))
                        if (k >= x && k <= x + height)
                            drawPointRandom(k,i,background);
            return this;
        }

        mcurses_colored_figures* drawLineStripesH(int x,int y,float size,bool vertical,const std::string firstColor,const std::string secondColor) {
            if (vertical) for(int i = y; i < size+y; i++) drawPointStripesH(x, i, firstColor, secondColor);
            else for(int k = x; k < size+x; k++) drawPointStripesH(k, y, firstColor, secondColor);
            return this;
        }
        mcurses_colored_figures* drawLineStripesHRandom(int x,int y,float size,bool vertical) {
            return drawLineStripesH(x,y,size,vertical,randomColorName(),randomColorName());
        }
        mcurses_colored_figures* drawLineStripesV(int x,int y,float size,bool vertical,const std::string firstColor,const std::string secondColor)  {
            if (vertical) for(int i = y; i < size+y; i++) drawPointStripesV(x,i,firstColor,secondColor);
            else for(int k = x; k < size+x; k++) drawPointStripesV(k,y,firstColor,secondColor);
            return this;
        }
        mcurses_colored_figures* drawLineStripesVRandom(int x,int y,float size,bool vertical) {
            return drawLineStripesV(x,y,size,vertical,randomColorName(),randomColorName());
        }
        mcurses_colored_figures* drawLineRandom(int x,int y,float size,bool vertical) {
            if (vertical) for(int i = y; i < size+y; i++) drawPointRandom(x,i);
            else for(int k = x; k < size+x; k++) drawPointRandom(k,y);
            return this;
        }
        mcurses_colored_figures* drawLineStripesH(int x,int y,float size,bool vertical,const std::string firstColor,const std::string secondColor,std::string background)  {
            if (vertical) for(int i = y; i < size+y; i++) drawPointStripesH(x,i,firstColor,secondColor,background);
            else for(int k = x; k < size+x; k++) drawPointStripesH(k,y,firstColor,secondColor,background);
            return this;
        }
        mcurses_colored_figures* drawLineStripesHRandom(int x,int y,float size,bool vertical,std::string background) {
            return drawLineStripesH(x,y,size,vertical,randomColorName(),randomColorName(),background);
        }
        mcurses_colored_figures* drawLineStripesV(int x, int y, float size, bool vertical,const std::string firstColor, const std::string secondColor, std::string background)  {
            if (vertical) for(int i = y; i < size+y; i++) drawPointStripesV(x,i,firstColor,secondColor,background);
            else for(int k = x; k < size+x; k++) drawPointStripesV(k,y,firstColor,secondColor,background);
            return this;
        }
        mcurses_colored_figures* drawLineStripesVRandom(int x, int y, float size, bool vertical, std::string background) {
            return drawLineStripesV(x,y,size,vertical,randomColorName(),randomColorName(),background);
        }
        mcurses_colored_figures* drawLineRandom(int x, int y, float size, bool vertical, std::string background) {
            if (vertical) for(int i = y; i < size+y; i++) drawPointRandom(x,i,background);
            else for(int k = x; k < size+x; k++) drawPointRandom(k,y,background);
            return this;
        }

        mcurses_colored_figures* drawBorderStripesH(int x,int y,float width,float height,float size,const std::string firstColor,const std::string secondColor) {
            while(size >= width || size >= height)size-=1;
            drawLineStripesH(x, y, width, false, firstColor, secondColor);//x-up
            drawLineStripesH(x, y, width, true, firstColor, secondColor);//y-left
            drawLineStripesH(x, y + height, width, false, firstColor, secondColor);//x-down
            drawLineStripesH(x + width-1, y, width + 1, true, firstColor, secondColor);//y-right
            if(size != 1) drawBorderStripesH(x+1,y+1,width-2,height-2,size-1, firstColor, secondColor);
            return this;
        }
        mcurses_colored_figures* drawBorderStripesHRandom(int x,int y,float width,float height,float size) {
            return drawBorderStripesH(x,y,width,height,size, randomColorName(), randomColorName());
        }
        mcurses_colored_figures* drawBorderStripesV(int x,int y,float width,float height,float size,const std::string firstColor,const std::string secondColor) {
            while(size >= width || size >= height)size-=1;
            drawLineStripesV(x, y, width, false, firstColor, secondColor);//x-up
            drawLineStripesV(x, y, width, true, firstColor, secondColor);//y-left
            drawLineStripesV(x, y + height, width, false, firstColor, secondColor);//x-down
            drawLineStripesV(x + width-1, y, width + 1, true, firstColor, secondColor);//y-right
            if(size != 1) drawBorderStripesV(x+1,y+1,width-2,height-2,size-1, firstColor, secondColor);
            return this;
        }
        mcurses_colored_figures* drawBorderStripesVRandom(int x,int y,float width,float height,float size) {
            return drawBorderStripesV(x,y,width,height,size, randomColorName(), randomColorName());
        }
        mcurses_colored_figures* drawBorderRandom(int x,int y,float width,float height,float size) {
            while(size >= width || size >= height)size--;
            drawLineRandom(x, y, width, false);//y-up
            drawLineRandom(x, y, height, true);//x-left
            drawLineRandom(x, y + height-1, width, false);//y-down
            drawLineRandom(x + width-1, y, height-1, true);//x-right
            if(size != 1) drawBorderRandom(x+1,y+1,width-2,height-2,size-1);
            return this;
        }
        mcurses_colored_figures* drawBorderStripesH(int x,int y,float width,float height,float size,const std::string firstColor,const std::string secondColor,std::string background) {
            while(size >= width || size >= height)size-=1;
            drawLineStripesH(x, y, width, false, firstColor, secondColor, background);
            drawLineStripesH(x, y, height, true, firstColor, secondColor, background);
            drawLineStripesH(x, y + height-1, width, false, firstColor, secondColor, background);
            drawLineStripesH(x + width-1, y, height + 1, true,  firstColor, secondColor, background);
            if(size != 1) drawBorderStripesH(x+1,y+1,width-2,height-2,size-1,firstColor, secondColor, background);
            return this;
        }
        mcurses_colored_figures* drawBorderStripesHRandom(int x,int y,float width,float height,float size,std::string background) {
            return drawBorderStripesH(x,y,width,height,size, randomColorName(), randomColorName(), background);
        }
        mcurses_colored_figures* drawBorderStripesV(int x,int y,float width,float height,float size,const std::string firstColor,const std::string secondColor,std::string background) {
            while(size >= width || size >= height)size-=1;
            drawLineStripesV(x, y, width, false, firstColor, secondColor, background);
            drawLineStripesV(x, y, width, true, firstColor, secondColor, background);
            drawLineStripesV(x, y + height, width, false, firstColor, secondColor, background);
            drawLineStripesV(x + width, y, width + 1, true, firstColor, secondColor, background);
            if(size != 1) drawBorderStripesV(x+1,y+1,width-2,height-2,size-1,firstColor, secondColor, background);
            return this;
        }
        mcurses_colored_figures* drawBorderStripesVRandom(int x,int y,float width,float height,float size,std::string background) {
            return drawBorderStripesV(x,y,width,height,size, randomColorName(), randomColorName(), background);
        }
        mcurses_colored_figures* drawBorderRandom(int x,int y,int width,int height,int size,std::string background) {
            while(size >= width || size >= height)size-=1;
            drawLineRandom(x, y, width, false, background);//y-up
            drawLineRandom(x, y, height, true, background);//x-left
            drawLineRandom(x, y + height, width, false, background);//y-down
            drawLineRandom(x + width, y, height, true, background);//x-right
            if(size != 1) drawBorderRandom(x+1,y+1,width-2,height-2,size-1,background);
            return this;
        }

        mcurses_colored_figures* drawBackgroundStripesH(const std::string firstColor,const std::string secondColor){
            int screenX = screen->getX();
            int screenY = screen->getY();
            int screenAspect = screen->getAspect();
            for (int k = 0; k < int(screenX/screenAspect); k++)
                for (int i = 0; i < int(screenY); i++)
                    if(k%2==0) screen->drawPoint(i, k, firstColor, firstColor);
                    else screen->drawPoint(i, k, secondColor, secondColor);
            return this;
        }
        mcurses_colored_figures* drawBackgroundStripesHRandom(){
            return drawBackgroundStripesH(randomColorName(), randomColorName());
        }
        mcurses_colored_figures* drawBackgroundStripesV(const std::string firstColor,const std::string secondColor) {
            for (int k = 0; k < int(screen->getX()/screen->getAspect()); k++)
                for (int i = 0; i < int(screen->getY()); i++)
                    if (i % 2 == 0) screen->drawPoint(k, i, firstColor, secondColor);
                    else screen->drawPoint( k, i, secondColor, firstColor);
            return this;
        }
        mcurses_colored_figures* drawBackgroundStripesVRandom() {
            return drawBackgroundStripesV(randomColorName(), randomColorName());
        }
        mcurses_colored_figures* drawBackgroundCross(const std::string firstColor,const std::string secondColor,bool type) {
            for (int k = 0; k < int(screen->getX() / screen->getAspect()); k++)
                for (int i = 0; i < int(screen->getY()); i++)
                    drawPointCross(k, i, firstColor, secondColor, type);
            return this;
        }
        mcurses_colored_figures* drawBackgroundCrossRandom(bool type) {
            return drawBackgroundCross(randomColorName(), randomColorName(), type);
        }
        mcurses_colored_figures* drawBackgroundRandom(){
            for (int k = 0; k < int(screen->getX()/screen->getAspect()); k++)
                for (int i = 0; i < int(screen->getY()); i++) {
                  std::string firstColor = randomColorName();
                  std::string secondColor = randomColorName();
                  screen->drawPoint(i, k, firstColor, secondColor);
                }
            return this;
        }

        int randomINT(int min,int max){
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> dist6(min,max);
            return dist6(rng);
        }
        std::string randomColorName(){
            return getColorName(randomINT(0,16));
        }
    };
}

#endif