#include "../mcurses_module.h"
#include <random>

#pragma once

#ifndef MCURSES_BACKGROUNDS_H
#define MCURSES_BACKGROUNDS_H

using namespace std;
using namespace mcurses;

namespace mcurses{
    class mcurses_colored_figures : public mcurses_module{
    public:
        mcurses_kernel* screen;

        //mcurses_simple_figures() : mcurses_module(){}
        mcurses_colored_figures(float x,float y,float aspect,mcurses_kernel*screen) : mcurses_module(x, y, aspect){this->screen=screen;}
        mcurses_colored_figures(float x,float y,float aspect,mcurses_kernel*screen,char background) : mcurses_colored_figures(x, y, aspect,screen){this->screen=screen;}

        void drawPointStripesH(float x,float y,const string firstColor,const string secondColor){
            if(int(x)%2==0) screen->drawPoint((float)y, (float)x, firstColor, secondColor);
            else screen->drawPoint((float)y, (float)x, secondColor, firstColor);
        }
        void drawPointStripesV(float x,float y,const string firstColor,const string secondColor) const{
            if(int(y)%2==0) screen->drawPoint((float)y, (float)x, firstColor, secondColor);
            else screen->drawPoint((float)y, (float)x, secondColor, firstColor);
        }
        void drawPointCross(float x,float y,const string firstColor,const string secondColor,bool type){
            if (int(y) % 2 == type) screen->drawPoint((float) y, (float) x, firstColor, secondColor);
            else screen->drawPoint((float) y, (float) x, secondColor, firstColor);
            if (int(x) % 2 == type) screen->drawPoint((float) y, (float) x, firstColor, secondColor);
        }
        void drawPointRandom(float x, float y){
            screen->drawPoint((float) x, (float) y, randomColorName(), randomColorName());
        }
        void drawPointStripesH(float x,float y,const string firstColor,const string secondColor,char background) const{
            if(int(x)%2==0) screen->drawPoint((float)y, (float)x, secondColor, firstColor, background);
            else screen->drawPoint((float)y, (float)x, firstColor, secondColor, background);
        }
        void drawPointStripesV(float x,float y,const string firstColor,const string secondColor,char background) const{
            if(int(y)%2==0) screen->drawPoint((float)y, (float)x, firstColor, firstColor);
            else screen->drawPoint((float)y, (float)x, secondColor, secondColor);
        }
        void drawPointCross(float x,float y,const string firstColor,const string secondColor,bool type,char background){
            if (int(y) % 2 == type)
                screen->drawPoint((float) y, (float) x, firstColor, firstColor);
            else
                screen->drawPoint((float) y, (float) x, secondColor, secondColor);
            if (int(x) % 2 == type)
                screen->drawPoint((float) y, (float) x, firstColor, firstColor);
        }
        void drawPointRandom(float x,float y,char background){
            screen->drawPoint((float) x, (float) y, randomColorName(), randomColorName());
        }

        void drawRectangleStripesH(float x,float y,float width,float height,const string firstColor,const string secondColor) {
            for (int i = 0; i < int(y + width); i++)
                if (i >= (int)y && i <= (int)y + (int)width)
                    for (int k = 0; k < int(x + height); k += (int(screen->getAspect()) - 1))
                        if (k >= (int)x && k <= (int)x + (int)height)
                            drawPointStripesH(k,i,firstColor, secondColor);
        }
        void drawRectangleStripesHRandom(float x,float y,float width,float height) {
            const string firstColor = randomColorName(), secondColor = randomColorName();
            drawRectangleStripesH(x, y, width, height, firstColor, secondColor);
        }
        void drawRectangleStripesV(float x,float y,float width,float height,const string firstColor,const string secondColor) {
            for (int i = 0; i < int(y + width); i++)
                if (i >= (int)y && i <= (int)y + (int)width)
                    for (int k = 0; k < int(x + height); k += (int(screen->getAspect()) - 1))
                        if (k >= (int)x && k <= (int)x + (int)height)
                            drawPointStripesV(k,i,firstColor, secondColor);
        }
        void drawRectangleStripesVRandom(float x,float y,float width,float height) {
            const string firstColor = randomColorName(), secondColor = randomColorName();
            drawRectangleStripesV(x,y,width,height,firstColor,secondColor);
        }
        void drawRectangleCross(float x,float y,float width,float height,const string firstColor,const string secondColor,bool type) {
            for (int k = 0; k < int(screen->getX() / screen->getAspect()); k++)
                if (k >= (int)x && k <= (int)x + (int)height)
                    for (int i = 0; i < int(screen->getY()); i++)
                        if (i >= (int)y && i <= (int)y + (int)width)
                            drawPointCross(k, i, firstColor, secondColor, type);
        }
        void drawRectangleCrossRandom(float x,float y,float width,float height,bool type) {
            const string firstColor = randomColorName(), secondColor = randomColorName();
            drawRectangleCross(x,y,width,height,firstColor,secondColor,type);
        }
        void drawRectangleRandom(float x, float y, float width, float height) {
            for (int i = 0; i < int(y + width); i++)
                if (i >= (int)y && i <= (int)y + (int)width)
                    for (int k = 0; k < int(x + height); k += (int(screen->getAspect()) - 1))
                        if (k >= (int)x && k <= (int)x + (int)height)
                            drawPointRandom(k,i);
        }
        void drawRectangleStripesH(float x,float y,float width,float height,const string firstColor,const string secondColor,char background) {
            for (int i = 0; i < int(y + width); i++)
                if (i >= (int)y && i <= (int)y + (int)width)
                    for (int k = 0; k < int(x + height); k += (int(screen->getAspect()) - 1))
                        if (k >= (int)x && k <= (int)x + (int)height)
                            drawPointStripesH(k,i,firstColor,secondColor,background);
        }
        void drawRectangleStripesHRandom(float x,float y,float width,float height,char background) {
            const string firstColor = randomColorName(), secondColor = randomColorName();
            drawRectangleStripesH(x,y,width,height,firstColor,secondColor,background);
        }
        void drawRectangleStripesV(float x,float y,float width,float height,const string firstColor,const string secondColor,char background) {
            for (int i = 0; i < int(y + width); i++)
                if (i >= (int)y && i <= (int)y + (int)width)
                    for (int k = 0; k < int(x + height); k += (int(screen->getAspect()) - 1))
                        if (k >= (int)x && k <= (int)x + (int)height)
                            drawPointStripesV(k,i,firstColor,secondColor,background);
        }
        void drawRectangleStripesVRandom(float x,float y,float width,float height,char background) {
            const string firstColor = randomColorName(), secondColor = randomColorName();
            drawRectangleStripesV(x,y,width,height,firstColor,secondColor,background);
        }
        void drawRectangleCross(float x,float y,float width,float height,const string firstColor,const string secondColor,bool type,char background) {
            for (int k = 0; k < int(screen->getX() / screen->getAspect()); k++)
                if (k >= (int)x && k <= (int)x + (int)height)
                    for (int i = 0; i < int(screen->getY()); i++)
                        if (i >= (int)y && i <= (int)y + (int)width)
                            drawPointCross(k, i, firstColor, secondColor, type, background);
        }
        void drawRectangleCrossRandom(float x,float y,float width,float height,const bool type,char background) {
            const string firstColor = randomColorName(), secondColor = randomColorName();
            drawRectangleCross(x,y,width,height,firstColor,secondColor,type,background);
        }
        void drawRectangleRandom(float x,float y,float width,float height,char background) {
            for (int i = 0; i < int(y + width); i++)
                if (i >= (int)y && i <= (int)y + (int)width)
                    for (int k = 0; k < int(x + height); k += (int(screen->getAspect()) - 1))
                        if (k >= (int)x && k <= (int)x + (int)height)
                            drawPointRandom(k,i,background);
        }

        void drawLineStripesH(float x,float y,float size,bool vertical,const string firstColor,const string secondColor) {
            if (!vertical)
                for(int i = y; i < size+y; i++)
                    drawPointStripesH(x, (float)i, firstColor, secondColor);
            else
                for(int k = x; k < size+x; k++)
                    drawPointStripesH((float)k, y, firstColor, secondColor);
        }
        void drawLineStripesHRandom(float x,float y,float size,bool vertical) {
            const string firstColor = randomColorName(), secondColor = randomColorName();
            drawLineStripesH(x,y,size,vertical,firstColor,secondColor);
        }
        void drawLineStripesV(float x,float y,float size,bool vertical,const string firstColor,const string secondColor) const {
            if (!vertical) {
                for(int i = y; i < size+y; i++)
                    drawPointStripesV(x,(float)i,firstColor,secondColor);
            } else {
                for(int k = x; k < size+x; k++)
                    drawPointStripesV((float)k,y,firstColor,secondColor);
            }
        }
        void drawLineStripesVRandom(float x,float y,float size,bool vertical) {
            const string firstColor = randomColorName(), secondColor = randomColorName();
            drawLineStripesV(x,y,size,vertical,firstColor,secondColor);
        }
        void drawLineRandom(float x,float y,float size,bool vertical) {
            if (vertical)
                for(int i = y; i < size+y; i++)
                    drawPointRandom(x,i);
            else
                for(int k = x; k < size+x; k++)
                    drawPointRandom(k,y);
        }
        void drawLineStripesH(float x,float y,float size,bool vertical,const string firstColor,const string secondColor,char background) const {
            if (!vertical)
                for(int i = y; i < size+y; i++)
                    drawPointStripesH(x,i,firstColor,secondColor,background);
            else
                for(int k = x; k < size+x; k++)
                    drawPointStripesH(k,y,firstColor,secondColor,background);
        }
        void drawLineStripesHRandom(float x,float y,float size,bool vertical,char background) {
            const string firstColor = randomColorName(), secondColor = randomColorName();
            drawLineStripesH(x,y,size,vertical,firstColor,secondColor,background);
        }
        void drawLineStripesV(float x, float y, float size, bool vertical,const string firstColor, const string secondColor, char background) const {
            if (!vertical) {
                for(int i = y; i < size+y; i++)
                    drawPointStripesV(x,i,firstColor,secondColor,background);
            } else {
                for(int k = x; k < size+x; k++)
                    drawPointStripesV(k,y,firstColor,secondColor,background);
            }
        }
        void drawLineStripesVRandom(float x, float y, float size, bool vertical, char background) {
            const string firstColor = randomColorName(), secondColor = randomColorName();
            drawLineStripesV(x,y,size,vertical,firstColor,secondColor,background);
        }
        void drawLineRandom(float x, float y, float size, bool vertical, char background) {
            if (vertical)
                for(int i = y; i < size+y; i++)
                    drawPointRandom(x,i,background);
            else
                for(int k = x; k < size+x; k++)
                    drawPointRandom(k,y,background);
        }

        void drawBorderStripesH(float x,float y,float width,float height,float size,const string firstColor,const string secondColor) {
            while(size >= width || size >= height)size-=1;
            drawLineStripesH(x, y, width, false, firstColor, secondColor);//x-up
            drawLineStripesH(x, y, width, true, firstColor, secondColor);//y-left
            drawLineStripesH(x, y + height, width, false, firstColor, secondColor);//x-down
            drawLineStripesH(x + width-1, y, width + 1, true, firstColor, secondColor);//y-right
            if(size != 1) drawBorderStripesH(x+1,y+1,width-2,height-2,size-1, firstColor, secondColor);
        }
        void drawBorderStripesHRandom(float x,float y,float width,float height,float size) {
            string firstColor = randomColorName(), secondColor = randomColorName();
            drawBorderStripesH(x,y,width,height,size, firstColor, secondColor);
        }
        void drawBorderStripesV(float x,float y,float width,float height,float size,const string firstColor,const string secondColor) {
            while(size >= width || size >= height)size-=1;
            drawLineStripesV(x, y, width, false, firstColor, secondColor);//x-up
            drawLineStripesV(x, y, width, true, firstColor, secondColor);//y-left
            drawLineStripesV(x, y + height, width, false, firstColor, secondColor);//x-down
            drawLineStripesV(x + width-1, y, width + 1, true, firstColor, secondColor);//y-right
            if(size != 1) drawBorderStripesV(x+1,y+1,width-2,height-2,size-1, firstColor, secondColor);
        }
        void drawBorderStripesVRandom(float x,float y,float width,float height,float size) {
            string firstColor = randomColorName(), secondColor = randomColorName();
            drawBorderStripesV(x,y,width,height,size, firstColor, secondColor);
        }
        void drawBorderRandom(float x,float y,float width,float height,float size) {
            while(size >= width || size >= height)size--;
            drawLineRandom(x, y, width, false);//y-up
            drawLineRandom(x, y, height, true);//x-left
            drawLineRandom(x, y + height-1, width, false);//y-down
            drawLineRandom(x + width-1, y, height-1, true);//x-right
            if(size != 1) drawBorderRandom(x+1,y+1,width-2,height-2,size-1);
        }
        void drawBorderStripesH(float x,float y,float width,float height,float size,const string firstColor,const string secondColor,char background) {
            while(size >= width || size >= height)size-=1;
            drawLineStripesH(x, y, width, false, firstColor, secondColor, background);
            drawLineStripesH(x, y, width, true, firstColor, secondColor, background);
            drawLineStripesH(x, y + height, width, false, firstColor, secondColor, background);
            drawLineStripesH(x + width, y, width + 1, true,  firstColor, secondColor, background);
            if(size != 1) drawBorderStripesH(x+1,y+1,width-2,height-2,size-1,firstColor, secondColor, background);
        }
        void drawBorderStripesHRandom(float x,float y,float width,float height,float size,char background) {
            string firstColor = randomColorName(), secondColor = randomColorName();
            drawBorderStripesH(x,y,width,height,size, firstColor, secondColor, background);
        }
        void drawBorderStripesV(float x,float y,float width,float height,float size,const string firstColor,const string secondColor,char background) {
            while(size >= width || size >= height)size-=1;
            drawLineStripesV(x, y, width, false, firstColor, secondColor, background);
            drawLineStripesV(x, y, width, true, firstColor, secondColor, background);
            drawLineStripesV(x, y + height, width, false, firstColor, secondColor, background);
            drawLineStripesV(x + width, y, width + 1, true, firstColor, secondColor, background);
            if(size != 1) drawBorderStripesV(x+1,y+1,width-2,height-2,size-1,firstColor, secondColor, background);
        }
        void drawBorderStripesVRandom(float x,float y,float width,float height,float size,char background) {
            string firstColor = randomColorName(), secondColor = randomColorName();
            drawBorderStripesV(x,y,width,height,size, firstColor, secondColor, background);
        }
        void drawBorderRandom(float x,float y,float width,float height,float size,char background) {
            while(size >= width || size >= height)size-=1;
            drawLineRandom(x, y, width, false, background);//y-up
            drawLineRandom(x, y, height, true, background);//x-left
            drawLineRandom(x, y + height, width, false, background);//y-down
            drawLineRandom(x + width, y, height, true, background);//x-right
            if(size != 1) drawBorderRandom(x+1,y+1,width-2,height-2,size-1,background);
        }

        void drawBackgroundStripesH(const string firstColor,const string secondColor){
            float screenX = screen->getX();
            float screenY = screen->getY();
            float screenAspect = screen->getAspect();
            for (int k = 0; k < int(screenX/screenAspect); k++)
                for (int i = 0; i < int(screenY); i++)
                    if(k%2==0)
                        screen->drawPoint((float)i, (float)k, firstColor, firstColor);
                    else
                        screen->drawPoint((float)i, (float)k, secondColor, secondColor);
        }
        void drawBackgroundStripesHRandom(){
            string firstColor = randomColorName(), secondColor = randomColorName();
            drawBackgroundStripesH(firstColor, secondColor);
        }
        void drawBackgroundStripesV(const string firstColor,const string secondColor) {
            for (int k = 0; k < int(screen->getX()/screen->getAspect()); k++)
                for (int i = 0; i < int(screen->getY()); i++)
                    if (i % 2 == 0)
                        screen->drawPoint((float) i, (float) k, firstColor, firstColor);
                    else
                        screen->drawPoint((float) i, (float) k, secondColor, secondColor);
        }
        void drawBackgroundStripesVRandom() {
            string firstColor = randomColorName(), secondColor = randomColorName();
            drawBackgroundStripesV(firstColor, secondColor);
        }
        void drawBackgroundCross(const string firstColor,const string secondColor,bool type) {
            for (int k = 0; k < int(screen->getX() / screen->getAspect()); k++)
                for (int i = 0; i < int(screen->getY()); i++)
                    drawPointCross(k, i, firstColor, secondColor, type);
        }
        void drawBackgroundCrossRandom(bool type) {
            string firstColor = randomColorName(), secondColor = randomColorName();
            drawBackgroundCross(firstColor, secondColor, type);
        }
        void drawBackgroundRandom(){
            for (int k = 0; k < int(screen->getX()/screen->getAspect()); k++)
                for (int i = 0; i < int(screen->getY()); i++)
                    screen->drawPoint((float) i, (float) k, randomColorName(), randomColorName());
        }

        int randomINT(int min,int max){

            random_device dev;
            mt19937 rng(dev());
            uniform_int_distribution<mt19937::result_type> dist6(min,max);
            int num = dist6(rng);
            return num;
        }
        string randomColorName(){
            return getColorName(randomINT(0,16));
        }
    };
}

#endif