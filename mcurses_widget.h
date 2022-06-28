#include "mcurses.h"

#ifndef MCURSES_WIDGET_H
#define MCURSES_WIDGET_H

class mcurses_widget {
public:
    float getX(){return x}
    float getY(){return y}
    float getWidth(){return width}
    float getHeight(){return height}
    string getDefaultColor(){return color}
    string getDefaultBackgroundColor(){return backgroundColor}
    int setX(float x){this->x=x;}
    int setY(float y){this->y=y;}
    int setWidth(float width){this->width=width;}
    int setHeight(float height){this->height=height;}
    int setDefaultColor(string color){this->color=color;}
    int setDefaultBackgroundColor(string backgroundColor){this->backgroundColor=backgroundColor;}
    int render(s)
protected:
    float x, y, width, height;
    string color, backgroundColor;
};


#endif
