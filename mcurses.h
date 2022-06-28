#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
#include <clocale>
#include <csignal>
#include <cmath>
#include "termios.h"
using namespace std;

#ifndef MCURSES_H
#define MCURSES_H

class mcurses {
public:
    const string FBLACK = "\033[0;30m";
    const string FRED = "\033[0;31m";
    const string FGREEN = "\033[0;32m";
    const string FYELLOW = "\033[0;33m";
    const string FBLUE = "\033[0;34m";
    const string FMAGENTA = "\033[0;35m";
    const string FCYAN = "\033[0;36m";
    const string FGRAY = "\033[0;37m";
    const string FLRED = "\033[0;38m";
    const string FWHITE = "\033[0;39m";
    const string FLGREEN = "\033[0;92m";
    const string FLYELLOW = "\033[0;93m";
    const string FLBLUE = "\033[0;94m";
    const string FLMAGENTA = "\033[0;95m";
    const string FLCYAN = "\033[0;96m";
    const string FLGRAY = "\033[0;97m";

    const string BBLACK = "\033[0;40m";
    const string BRED = "\033[0;41m";
    const string BGREEN = "\033[0;42m";
    const string BYELLOW = "\033[0;43m";
    const string BBLUE = "\033[0;44m";
    const string BMAGENTA = "\033[0;45m";
    const string BCYAN = "\033[0;46m";
    const string BWHITE = "\033[0;47m";
    const string BGRAY = "\033[0;100m";
    const string BLGRAY = "\033[0;100m";
    const string BLRED = "\033[0;101m";
    const string BLGREEN = "\033[0;102m";
    const string BLYELLOW = "\033[0;103m";
    const string BLBLUE = "\033[0;104m";
    const string BLMAGENTA = "\033[0;105m";
    const string BLCYAN = "\033[0;106m";
    const string BLWHITE = "\033[0;107m";
    const string DEFAULT = "\033[0m";

mcurses(float x, float y, float aspect) {
    this->x = x;
    this->y = y;
    this->aspect = aspect;
    cursorX = 0;
    cursorY = 0;
    ch = 0;
    k = 0;
    this->x *= aspect;
    background = ' ';
    cout << "\033[u";
    clear();
}
mcurses(float x, float y, float aspect, char background) : mcurses(x, y, aspect){
    this->background = background;
}
static char getch() {
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if (tcgetattr(0, &old) < 0) perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN]  = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0) perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0) perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0) perror ("tcsetattr ~ICANON");
    return buf;
}
string getColor(string color, bool fg) {
    if(fg){
        if (color == "BLACK") return FBLACK;
        if (color == "RED") return FRED;
        if (color == "GREEN") return FGREEN;
        if (color == "YELLOW") return FYELLOW;
        if (color == "BLUE") return FBLUE;
        if (color == "CYAN") return FCYAN;
        if (color == "MAGENTA") return FMAGENTA;
        if (color == "WHITE") return FWHITE;
        if (color == "GRAY") return FGRAY;
        if (color == "LRED") return FLRED;
        if (color == "LGREEN") return FLGREEN;
        if (color == "LYELLOW") return FLYELLOW;
        if (color == "LBLUE") return FLBLUE;
        if (color == "LCYAN") return FLCYAN;
        if (color == "LMAGENTA") return FLMAGENTA;
        if (color == "LGRAY") return FLGRAY;
    }
    else{
        if (color == "BLACK") return BBLACK;
        if (color == "RED") return BRED;
        if (color == "GREEN") return BGREEN;
        if (color == "YELLOW") return BYELLOW;
        if (color == "BLUE") return BBLUE;
        if (color == "CYAN") return BCYAN;
        if (color == "MAGENTA") return BMAGENTA;
        if (color == "WHITE") return BWHITE;
        if (color == "GRAY") return BGRAY;
        if (color == "LRED") return BLRED;
        if (color == "LGREEN") return BLGREEN;
        if (color == "LYELLOW") return BLYELLOW;
        if (color == "LBLUE") return BLBLUE;
        if (color == "LCYAN") return BLCYAN;
        if (color == "LMAGENTA") return BLMAGENTA;
        if (color == "LWHITE") return BLWHITE;
        if (color == "LGRAY") return BLGRAY;
    }
    if (color == "NONE") return "";
    return DEFAULT;
}
static void setLocale(int category, const char* locale) {setlocale(category, locale);}
void exitProgram(int result, const char* message){
    setCursor(0,y);
    cout << "Exit message: " << message << endl;
    exit(result);
}
void setCursor(float xd, float yd){
    cout << "\033[" + to_string(int(yd)) + ";" + to_string(int(xd)) + "f";
    cursorX = xd;
    cursorY = yd;
}
void moveCursorX(float xd){
    if(xd > 0) cout << "\033[" + to_string(int(xd)) << "C";
    else if(xd < 0) cout << "\033[" + to_string(int(xd)) << "D";
    cursorX += xd;
}
void moveCursorY(float yd){
    if(yd > 0) cout << "\033[" + to_string(int(yd)) << "A";
    else if(yd < 0) cout << "\033[" + to_string(int(yd)) << "B";
    cursorY += yd;
}
void moveCursor(float xd, float yd){
    moveCursorX(xd);
    moveCursorY(yd);
    cursorX += xd;
    cursorY += yd;
}
void clear(){
    cout << "\033[2J";
    setCursor(0,0);
}
void drawPoint(float x, float y, string bgColor) {
    bgColor = getColor(bgColor, false);
    x *= 2;
    string pixel = string(bgColor);
    if (bgColor == "NONE") pixel = " ";
    else {
        pixel += background;
        pixel += string(DEFAULT);
    }
    for (int i = 0; i < this->aspect; i++){
        setCursor(x-i+this->aspect,y);
        cout << pixel;
    }
}
void drawPoint(float x, float y, string bgColor, char backgroundd) {
    bgColor = getColor(bgColor, false);
    x *= 2;
    string pixel = string(bgColor);
    if (bgColor == "NONE") pixel = " ";
    else {
        pixel += backgroundd;
        pixel += string(DEFAULT);
    }
    for (int i = 0; i < this->aspect; i++){
        setCursor(x-i+this->aspect,y);
        cout << pixel;
    }
}
void drawPoint(float x, float y, string color, string bgColor) {
    color = getColor(color, true);
    bgColor = getColor(bgColor, false);
    x *= 2;
    string pixel = string(color);
    pixel += string(bgColor);
    if (color == "NONE") pixel = " ";
    else {
        pixel += background;
        pixel += string(DEFAULT);
    }
    for (int i = 0; i < this->aspect; i++){
        setCursor(x-i+this->aspect,y);
        cout << pixel;
    }
}
void drawPoint(float x, float y, string color, string bgColor, char backgroundd) {
    color = getColor(color, true);
    bgColor = getColor(bgColor, false);
    x *= 2;
    string pixel = string(color);
    pixel += string(bgColor);
    if (color == "NONE") pixel = " ";
    else {
        pixel += backgroundd;
        pixel += string(DEFAULT);
    }
    for (int i = 0; i < this->aspect; i++) {
        setCursor(x-i+this->aspect,y);
        cout << pixel;
    }
}
void drawRectangle(float x, float y, float width, float height, string bgColor) {
    string pixel = string(bgColor);
    for (int i = 0; i < int(y + width); i++)
        if (i >= y && i <= y + width)
            for (int k = 0; k < int(x + height); k += (aspect - 1))
                if (k >= x && k <= x + height)
                    drawPoint(k, i, bgColor);
}
void drawRectangle(float x, float y, float width, float height, string color, char backgroundd) {
    string pixel = string(color);
    for (int i = 0; i < int(y + width); i++)
        if (i >= y && i <= y + width)
            for (int k = 0; k < int(x + height); k += (aspect - 1))
                if (k >= x && k <= x + height)
                    drawPoint(k, i, color, backgroundd);
}
void drawLine(float x, float y, float size, bool vertical, string color) {
    if (vertical) {
        for (int i = 0; i < int(y + size); i++)
            if (i >= y && i <= y + size)
                drawPoint(x,i,color);
    } else {
        for (int k = 0; k < int(x + size)-1; k += (aspect - 1))
            if (k >= x && k <= x + size)
                drawPoint(k, y, color);
    }
}
void drawLine(float x, float y, float size, bool vertical, string color, char backgroundd) {
    if (vertical)
        for (int i = 0; i < int(y + size); i++)
            if (i >= y && i <= y + size) {
                for (int j = 0; j < aspect; j++)
                    drawPoint(x+j,i,color);
            }
            else {
                for (int k = 0; k < int(x + size); k += (aspect - 1))
                    if (k >= x && k <= x + size)
                        drawPoint(k, y, color, backgroundd);
            }
    else {
        for (int k = 0; k < int(x + size); k += (aspect - 1))
            if (k >= x && k <= x + size)
                drawPoint(k, y, color, backgroundd);
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
void drawBorder(float x, float y, float width, float height, float size, string color, char backgroundd) {
    while(size >= width || size >= height)size-=1;
    drawLine(x, y, width, false, color, backgroundd);
    drawLine(x, y, width, true, color, backgroundd);
    drawLine(x, y + height, width, false, color, backgroundd);
    drawLine(x + width, y, width + 1, true, color, backgroundd);
}
void print(string text, float x, float y, string color, string bgColor) {
    color = getColor(color, true);
    bgColor = getColor(bgColor, false);
    string pixel = "";
    for (int i = 0; i < text.length(); i++) {
        pixel += color;
        pixel += bgColor;
        pixel += text[i];
        pixel += DEFAULT;
        setCursor(x+i, y);
        cout << pixel;
    }
}
void drawBackground(string color) {
    for (int k = 0; k < int(this->x/this->aspect); k++)
    for (int i = 0; i < int(this->y); i++)
    drawPoint(i, k, color, color);
    backgroundColor = color;
}
void drawBackground(string color, char backgroundd) {
    for (int i = 0; i < int(this->y); i++) {
        for (int k = 0; k < int(this->x/this->aspect); k++)
            drawPoint(k, i, color, color, backgroundd);
    }
    backgroundColor = color;
}

private:
    float x, y, aspect, cursorX, cursorY;
    char background;
    string backgroundColor;
    char ch, k;

};

#endif