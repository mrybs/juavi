#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
#include <clocale>
#include <csignal>
#include <cmath>
#include <list>
#include <iterator>
#include <chrono>
#include <thread>
#include "termios.h"

#define INPUTBUFFER 255
#define DEFAULTBG " "

#pragma once
#ifndef MCURSES_H
#define MCURSES_H
#define DEBUGGPKOC

#define COLOR1PART std::string("\033["+ std::to_string(int(
#define COLOR2PART ))+"m")
#define INPUTBUFFER 255


namespace mcurses{
class mcurses_kernel {
public:
    const char FBLACK = 30;//0
    const char FRED = 31;//1
    const char FGREEN = 32;//2
    const char FYELLOW = 33;//3
    const char FBLUE = 34;//4
    const char FMAGENTA = 35;//5
    const char FCYAN = 36;//6
    const char FGRAY = 37;//7
    const char FLRED = 38;//8
    const char FWHITE = 39;//9
    const char FLGREEN = 92;//10
    const char FLYELLOW = 93;//11
    const char FLBLUE = 94;//12
    const char FLMAGENTA = 95;//13
    const char FLCYAN = 96;//14
    const char FLGRAY = 97;//15
    const char FLWHITE = 39;//15

    const char BBLACK = 40;//0
    const char BRED = 41;//1
    const char BGREEN = 42;//2
    const char BYELLOW = 43;//3
    const char BBLUE = 44;//4
    const char BMAGENTA = 45;//5
    const char BCYAN = 46;//6
    const char BWHITE = 47;//7
    const char BGRAY = 100;//8
    const char BLGRAY = 100;//9
    const char BLRED = 101;//10
    const char BLGREEN = 102;//11
    const char BLYELLOW = 103;//12
    const char BLBLUE = 104;//13
    const char BLMAGENTA = 105;//14
    const char BLCYAN = 106;//15
    const char BLWHITE = 107;//16

    const char* DEFAULT = "\033[0m";

    struct RGB {
        double r;
        double g;
        double b;
    };

    struct HSV {
      double h;
      double s;
      double v;
    };

    mcurses_kernel(){
        x = 1;
        y = 1;
        aspect = 2;
        cursorX = 0;
        cursorY = 0;
        background = DEFAULTBG;
        for(int i = 0; i < INPUTBUFFER; i++) CFI.push_front('\0');
        clear();
    }
    mcurses_kernel(int x, int y, int aspect) {
        this->x = x;
        this->y = y;
        this->aspect = aspect;
        this->x *= aspect;
        cursorX = 0;
        cursorY = 0;
        background = DEFAULTBG;
        //for(int i = 0; i < INPUTBUFFER; i++) CFI.push_front('\0');
        clear();
        setCursor(37,37);
        std::cout<<this->x<<";"<<this->y<<".";
        setCursor(0, 0);
    }
    mcurses_kernel(int x, int y, int aspect, std::string background) : mcurses_kernel(x, y, aspect)
    {this->background = background;}

    //TODO: optimise getch()
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
#ifndef DEBUGGPKOC
    //TODO: make key listener
    std::string keyListener(){
        while(true){
            string pressedKey = getPressedKeyOrCombination();
            if(pressedKey != "\0" && pressedKey[0] != '\0' && pressedKey != "") return pressedKey;
        }
    }
#endif

    RGB HSVtoRGB (HSV in){
        double hh, p, q, t, ff;
        RGB out;
        if(in.s <= 0.0) {
            out.r = in.v;
            out.g = in.v;
            out.b = in.v;
            return out;
        }
        hh = in.h;
        if(hh >= 360.0) hh = 0.0;
        hh /= 60.0;
        long i = (long)hh;
        ff = hh - i;
        p = in.v * (1.0 - in.s);
        q = in.v * (1.0 - (in.s * ff));
        t = in.v * (1.0 - (in.s * (1.0 - ff)));
        switch(i) {
        case 0:
            out.r = in.v;
            out.g = t;
            out.b = p;
            break;
        case 1:
            out.r = q;
            out.g = in.v;
            out.b = p;
            break;
        case 2:
            out.r = p;
            out.g = in.v;
            out.b = t;
            break;
        case 3:
            out.r = p;
            out.g = q;
            out.b = in.v;
            break;
        case 4:
            out.r = t;
            out.g = p;
            out.b = in.v;
            break;
        case 5:
        default:
            out.r = in.v;
            out.g = p;
            out.b = q;
            break;
            return out;
        }
    };

    mcurses_kernel* setColor(const std::string color, const std::string bgColor){
        std::cout<<getColor(color, true)<< getColor(bgColor, false);
    }

    static struct RGB hexToRGB(const char* hexValue){
      int r, g, b;
      std::sscanf(hexValue, "#%02x%02x%02x", &r, &g, &b);
      return {double(r), double(g), double(b)};
    }

    std::string getColor(const std::string color, const bool fg){
        if(!color.empty())
            if(color[0] == '#'){
                if(color.size() == 7) {
                    if (fg)
                        return "\033[38;2;" +
                               std::to_string((int)hexToRGB(color.c_str()).r) + ";" +
                               std::to_string((int)hexToRGB(color.c_str()).g) + ";" +
                               std::to_string((int)hexToRGB(color.c_str()).b) + "m";
                    return "\033[48;2;" +
                           std::to_string((int)hexToRGB(color.c_str()).r) + ";" +
                           std::to_string((int)hexToRGB(color.c_str()).g) + ";" +
                           std::to_string((int)hexToRGB(color.c_str()).b) + "m";
                } else return "";
            }
            else {
                if (fg) {
                  if (color == "BLACK")
                    return COLOR1PART FBLACK COLOR2PART;
                  if (color == "RED")
                    return COLOR1PART FRED COLOR2PART;
                  if (color == "GREEN")
                    return COLOR1PART FGREEN COLOR2PART;
                  if (color == "YELLOW")
                    return COLOR1PART FYELLOW COLOR2PART;
                  if (color == "BLUE")
                    return COLOR1PART FBLUE COLOR2PART;
                  if (color == "CYAN")
                    return COLOR1PART FCYAN COLOR2PART;
                  if (color == "MAGENTA")
                    return COLOR1PART FMAGENTA COLOR2PART;
                  if (color == "WHITE")
                    return COLOR1PART FWHITE COLOR2PART;
                  if (color == "GRAY")
                    return COLOR1PART FGRAY COLOR2PART;
                  if (color == "LRED")
                    return COLOR1PART FLRED COLOR2PART;
                  if (color == "LGREEN")
                    return COLOR1PART FLGREEN COLOR2PART;
                  if (color == "LYELLOW")
                    return COLOR1PART FLYELLOW COLOR2PART;
                  if (color == "LBLUE")
                    return COLOR1PART FLBLUE COLOR2PART;
                  if (color == "LCYAN")
                    return COLOR1PART FLCYAN COLOR2PART;
                  if (color == "LMAGENTA")
                    return COLOR1PART FLMAGENTA COLOR2PART;
                  if (color == "LGRAY")
                    return COLOR1PART FLGRAY COLOR2PART;
                  if (color == "LWHITE")
                    return COLOR1PART FLWHITE COLOR2PART;
                } else {
                  if (color == "BLACK")
                    return COLOR1PART BBLACK COLOR2PART;
                  if (color == "RED")
                    return COLOR1PART BRED COLOR2PART;
                  if (color == "GREEN")
                    return COLOR1PART BGREEN COLOR2PART;
                  if (color == "YELLOW")
                    return COLOR1PART BYELLOW COLOR2PART;
                  if (color == "BLUE")
                    return COLOR1PART BBLUE COLOR2PART;
                  if (color == "CYAN")
                    return COLOR1PART BCYAN COLOR2PART;
                  if (color == "MAGENTA")
                    return COLOR1PART BMAGENTA COLOR2PART;
                  if (color == "WHITE")
                    return COLOR1PART BWHITE COLOR2PART;
                  if (color == "GRAY")
                    return COLOR1PART BGRAY COLOR2PART;
                  if (color == "LRED")
                    return COLOR1PART BLRED COLOR2PART;
                  if (color == "LGREEN")
                    return COLOR1PART BLGREEN COLOR2PART;
                  if (color == "LYELLOW")
                    return COLOR1PART BLYELLOW COLOR2PART;
                  if (color == "LBLUE")
                    return COLOR1PART BLBLUE COLOR2PART;
                  if (color == "LCYAN")
                    return COLOR1PART BLCYAN COLOR2PART;
                  if (color == "LMAGENTA")
                    return COLOR1PART BLMAGENTA COLOR2PART;
                  if (color == "LWHITE")
                    return COLOR1PART BLWHITE COLOR2PART;
                  if (color == "LGRAY")
                    return COLOR1PART BLGRAY COLOR2PART;
                }
                if (color == "NONE")
                    return "";
            }
        else
            return "";
        return DEFAULT;
    }
    std::string getColorName(const int id){
        switch(id){
            case 0:return "BLACK";
            case 1:return "WHITE";
            case 2:return "CYAN";
            case 3:return "RED";
            case 4:return "GREEN";
            case 5:return "GRAY";
            case 6:return "YELLOW";
            case 7:return "MAGENTA";
            case 8:return "LMAGENTA";
            case 9:return "LGREEN";
            case 10:return "LGRAY";
            case 11:return "LYELLOW";
            case 12:return "LRED";
            case 13:return "LCYAN";
            case 14:return "BLUE";
            case 15:return "LBLUE";
            case 16:return "LWHITE";
            default:return "NONE";
        }
    }
    mcurses_kernel* setLocale(const int category, const char* locale) {setlocale(category, locale);return this;}
    void exitProgram(const int result, const char* message){
        setCursor(0,y);
        std::cout << "Exit message: " << message << "\n";
        exit(result);
    }
    mcurses_kernel* setCursor(const float x,const float y){
      std::cout << "\033[" + std::to_string(int(y)) + ";" + std::to_string(int(x-1)) + "f";
        cursorX = x;
        cursorY = y;
        return this;
    }
    mcurses_kernel* moveCursorX(const int xd){
        if(xd > 0) std::cout << "\033[" + std::to_string(int(xd)) << "C";
        else if(xd < 0) std::cout << "\033[" + std::to_string(int(xd)) << "D";
        cursorX += xd;
        return this;
    }
    mcurses_kernel* moveCursorY(const int yd){
        if(yd > 0) std::cout << "\033[" + std::to_string(int(yd)) << "A";
        else if(yd < 0) std::cout << "\033[" + std::to_string(int(yd)) << "B";
        cursorY += (yd);
        return this;
    }
    mcurses_kernel* moveCursor(const int xd, const int yd){
        moveCursorX(xd);
        moveCursorY(yd);
        return this;
    }
    mcurses_kernel* clear(){
        std::cout << "\033[2J";
        setCursor(0,0);
        return this;
    }
    mcurses_kernel* drawPoint(int x, int y, std::string bgColor) {
        return drawPoint(x,y,bgColor,bgColor,background);
    }
    mcurses_kernel* drawPoint(int x, int y, std::string bgColor, std::string background, bool ifUseBackground) {
        return drawPoint(x,y,bgColor,bgColor,background);
    }
    mcurses_kernel* drawPoint(int x, int y, const std::string color, const std::string bgColor) {
        return drawPoint(x,y,color,bgColor,background);
    }
    mcurses_kernel* drawPoint(int x,int y,std::string color,std::string bgColor,const std::string background) {
        x *= aspect;
        color = getColor(color, true);
        bgColor = getColor(bgColor, false);
        std::string pixel = color;
        pixel += bgColor;
        if (color == "NONE") pixel = " ";
        else {
            pixel += background;
        }
        if(background != "\n")
            setCursor(x+this->aspect,y);
        for (int i = 0; i < this->aspect &&
             x <= this->x*aspect &&
             y <= this->y; i++) {
             std::cout << pixel;
        }
        return this;
    }
    mcurses_kernel* print(std::string text, int x, int y, std::string color, std::string bgColor) {
        std::string toOut =
            getColor(color, true)+
            getColor(bgColor, false)+
            text+
            DEFAULT;
        setCursor((x+1)*aspect, y);
        std::cout << toOut;
        return this;
    }
    mcurses_kernel* drawVector(const int x,const int y,std::vector<std::vector<bool>>V,const std::string color,const std::string bgColor){
        return drawVector(x,y,V,color,bgColor,background);
    }
    mcurses_kernel* drawVector(const int x,const int y,std::vector<std::vector<bool>>V,const std::string color,const std::string bgColor,const std::string background){
        for(int i = 0; i < V.size(); i++)
            for(int j = 0; j < V[i].size(); j++)
                if(V[i][j])
                    drawPoint(j, i, color, bgColor, background);
        return this;
    }

    int getX(){return x;}
    int getY(){return y;}
    int getAspect(){return aspect;}
    int getCursorX(){return cursorX;}
    int getCursorY(){return cursorY;}
    std::string getBackground(){return background;}
    std::string getBackgroundColor(){return backgroundColor;}
    mcurses_kernel* setX(const int x){this->x=x;return this;}
    mcurses_kernel* setY(const int y){this->y=y;return this;}
    mcurses_kernel* setAspect(const float aspect){this->aspect=aspect;return this;}
    mcurses_kernel* setBackground(const std::string background){this->background=background;return this;}
    mcurses_kernel* setBackgroundColor(const std::string backgroundColor){this->backgroundColor=backgroundColor;return this;}

public:
    int x, y, aspect, cursorX, cursorY;
    std::string background;
    std::string backgroundColor;
    std::list <char> CFI; //Chars From Input
#ifndef DEBUGGPKOC
    std::string getPressedKeyOrCombination() {
        ADuration ad;
        ad.start();
        CFI.push_front(getch());
        int j = 0;
        for (char i: CFI) {
            ulong dur = ad.getDuration();
            ad.start();
            ad.start();
            if (j == 2) {
                if (i == 27 && dur < 30) {
                    char c1 = 27, c2 = 0, c3 = 0;
                    int l = 0;
                    for (char k: CFI) {
                        l++;
                        if (l == 0) c1 = k;
                        else if (l == 1) c2 = k;
                        else if (l == 2) {
                            c3 = k;
                            break;
                        }
                    }
                    for (int i = 0; i < INPUTBUFFER; i++)
                        CFI.push_front('\0');
                    return "To return1 >>> " +
                           (std::to_string(char(c1)) + ";" + std::to_string(char(c2)) + ";" + std::to_string(char(c3)));
                } else if (i != '\0') return "To return2 >>> " + std::to_string(CFI.front());
                else return std::string("\0");
            }
            if (j > 2) break;
            j++;
        }
        while (CFI.size() < INPUTBUFFER)
            CFI.pop_back();
    }
#endif
};
}

#endif
