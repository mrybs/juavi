#include "../mcurses_module.h"
#include <random>

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

        void drawBackgroundStripesH(string firstColor, string secondColor){
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
            string firstColor = getColorName(randomINT(0,16));
            string secondColor = getColorName(randomINT(0,16));
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
        void drawBackgroundStripesV(string firstColor, string secondColor) {
            float screenX = screen->getX();
            float screenY = screen->getY();
            float screenAspect = screen->getAspect();
            for (int k = 0; k < int(screenX / screenAspect); k++)
                for (int i = 0; i < int(screenY); i++)
                    if (i % 2 == 0)
                        screen->drawPoint((float) i, (float) k, firstColor, firstColor);
                    else
                        screen->drawPoint((float) i, (float) k, secondColor, secondColor);
        }
        void drawBackgroundStripesVRandom() {
            string firstColor = getColorName(randomINT(0,16));
            string secondColor = getColorName(randomINT(0,16));
            float screenX = screen->getX();
            float screenY = screen->getY();
            float screenAspect = screen->getAspect();
            for (int k = 0; k < int(screenX / screenAspect); k++)
                for (int i = 0; i < int(screenY); i++)
                    if (i % 2 == 0)
                        screen->drawPoint((float) i, (float) k, firstColor, firstColor);
                    else
                        screen->drawPoint((float) i, (float) k, secondColor, secondColor);
        }
        void drawBackgroundCross(string firstColor, string secondColor, bool type) {
            float screenX = screen->getX();
            float screenY = screen->getY();
            float screenAspect = screen->getAspect();
            for (int k = 0; k < int(screenX / screenAspect); k++)
                for (int i = 0; i < int(screenY); i++)
                    if (i % 2 == type)
                        screen->drawPoint((float) i, (float) k, firstColor, firstColor);
                    else
                        screen->drawPoint((float) i, (float) k, secondColor, secondColor);
            for (int k = 0; k < int(screenX / screenAspect); k++)
                for (int i = 0; i < int(screenY); i++)
                    if (k % 2 == type)
                        screen->drawPoint((float) i, (float) k, firstColor, firstColor);
        }
        void drawBackgroundCrossRandom(bool type) {
            string firstColor = getColorName(randomINT(0,16));
            string secondColor = getColorName(randomINT(0,16));
            float screenX = screen->getX();
            float screenY = screen->getY();
            float screenAspect = screen->getAspect();
            for (int k = 0; k < int(screenX / screenAspect); k++)
                for (int i = 0; i < int(screenY); i++)
                    if (i % 2 == type)
                        screen->drawPoint((float) i, (float) k, firstColor, firstColor);
                    else
                        screen->drawPoint((float) i, (float) k, secondColor, secondColor);
            for (int k = 0; k < int(screenX / screenAspect); k++)
                for (int i = 0; i < int(screenY); i++)
                    if (k % 2 == type)
                        screen->drawPoint((float) i, (float) k, firstColor, firstColor);
        }
        void drawBackgroundRandom(){
            float screenX = screen->getX();
            float screenY = screen->getY();
            float screenAspect = screen->getAspect();
            for (int k = 0; k < int(screenX / screenAspect); k++)
                for (int i = 0; i < int(screenY); i++)
                    screen->drawPoint((float) i, (float) k, getColorName(randomINT(0,16)), getColorName(randomINT(0,16)));
        }

        int randomINT(int min, int max){

            random_device dev;
            mt19937 rng(dev());
            uniform_int_distribution<mt19937::result_type> dist6(min,max);
            int num = dist6(rng);
            return num;
        }
    };
}

#endif