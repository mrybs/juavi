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
#include "classes/atimer.h"
using namespace std;

#pragma once
#ifndef MCURSES_H
#define MCURSES_H
#define COLOR1PART string("\033[0;"+ to_string(int(
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

    mcurses_kernel(){
        x = 1;
        y = 1;
        aspect = 1;
        cursorX = 0;
        cursorY = 0;
        background = ' ';
    }
    mcurses_kernel(float x, float y, float aspect) {
        for(int i = 0; i < INPUTBUFFER; i++)
            CFI.push_front('\0');
        y++;
        this->x = y;
        this->y = x;
        this->aspect = aspect;
        cursorX = 0;
        cursorY = 0;
        this->x *= aspect;
        background = ' ';
        cout << "\033[u";
        clear();
    }
    mcurses_kernel(float x, float y, float aspect, char background) : mcurses_kernel(x, y, aspect)
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
    //TODO: make key listener
    /*string keyListener(){
        while(true){
            string pressedKey = getPressedKeyOrCombination();
            if(pressedKey != "\0" && pressedKey[0] != '\0' && pressedKey != "") return pressedKey;
        }
    }*/

    string getColor(const string color, const bool fg) {
        if(fg){
            if (color == "BLACK") return COLOR1PART FBLACK COLOR2PART;
            if (color == "RED") return COLOR1PART FRED COLOR2PART;
            if (color == "GREEN") return COLOR1PART FGREEN COLOR2PART;
            if (color == "YELLOW") return COLOR1PART FYELLOW COLOR2PART;
            if (color == "BLUE") return COLOR1PART FBLUE COLOR2PART;
            if (color == "CYAN") return COLOR1PART FCYAN COLOR2PART;
            if (color == "MAGENTA") return COLOR1PART FMAGENTA COLOR2PART;
            if (color == "WHITE") return COLOR1PART FWHITE COLOR2PART;
            if (color == "GRAY") return COLOR1PART FGRAY COLOR2PART;
            if (color == "LRED") return COLOR1PART FLRED COLOR2PART;
            if (color == "LGREEN") return COLOR1PART FLGREEN COLOR2PART;
            if (color == "LYELLOW") return COLOR1PART FLYELLOW COLOR2PART;
            if (color == "LBLUE") return COLOR1PART FLBLUE COLOR2PART;
            if (color == "LCYAN") return COLOR1PART FLCYAN COLOR2PART;
            if (color == "LMAGENTA") return COLOR1PART FLMAGENTA COLOR2PART;
            if (color == "LGRAY") return COLOR1PART FLGRAY COLOR2PART;
            if (color == "LWHITE") return COLOR1PART FLWHITE COLOR2PART;
        }
        else{
            if (color == "BLACK") return COLOR1PART BBLACK COLOR2PART;
            if (color == "RED") return COLOR1PART BRED COLOR2PART;
            if (color == "GREEN") return COLOR1PART BGREEN COLOR2PART;
            if (color == "YELLOW") return COLOR1PART BYELLOW COLOR2PART;
            if (color == "BLUE") return COLOR1PART BBLUE COLOR2PART;
            if (color == "CYAN") return COLOR1PART BCYAN COLOR2PART;
            if (color == "MAGENTA") return COLOR1PART BMAGENTA COLOR2PART;
            if (color == "WHITE") return COLOR1PART BWHITE COLOR2PART;
            if (color == "GRAY") return COLOR1PART BGRAY COLOR2PART;
            if (color == "LRED") return COLOR1PART BLRED COLOR2PART;
            if (color == "LGREEN") return COLOR1PART BLGREEN COLOR2PART;
            if (color == "LYELLOW") return COLOR1PART BLYELLOW COLOR2PART;
            if (color == "LBLUE") return COLOR1PART BLBLUE COLOR2PART;
            if (color == "LCYAN") return COLOR1PART BLCYAN COLOR2PART;
            if (color == "LMAGENTA") return COLOR1PART BLMAGENTA COLOR2PART;
            if (color == "LWHITE") return COLOR1PART BLWHITE COLOR2PART;
            if (color == "LGRAY") return COLOR1PART BLGRAY COLOR2PART;
        }
        if (color == "NONE") return "";
        return DEFAULT;
    }
    string getColorName(const int id){
        /*while(id <= COLOR_MAX_ID)
            id -= COLOR_MAX_ID;*/
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
    mcurses_kernel setLocale(const int category, const char* locale) {setlocale(category, locale);return *this;}
    void exitProgram(const int result, const char* message){
        setCursor(0,y);
        cout << "Exit message: " << message << endl;
        exit(result);
    }
    mcurses_kernel setCursor(const float x, const float y){
        cout << "\033[" + to_string(int(y+1)) + ";" + to_string(int(x)) + "f";
        cursorX = x;
        cursorY = y+1;
        return *this;
    }
    mcurses_kernel moveCursorX(const float x){
        if(x > 0) cout << "\033[" + to_string(int(x)) << "C";
        else if(x < 0) cout << "\033[" + to_string(int(x)) << "D";
        cursorX += x;
        return *this;
    }
    mcurses_kernel moveCursorY(const float y){
        if(y > 0) cout << "\033[" + to_string(int(y+1)) << "A";
        else if(y < 0) cout << "\033[" + to_string(int(y+1)) << "B";
        cursorY += (y+1);
        return *this;
    }
    mcurses_kernel clear(){
        cout << "\033[2J";
        setCursor(0,0);
        return *this;
    }
    mcurses_kernel drawPoint(float x, float y, string bgColor) {
        bgColor = getColor(bgColor, false);
        x *= 2;
        string pixel = string(bgColor);
        if (bgColor == "NONE") pixel = " ";
        else {
            pixel += background;
            pixel += DEFAULT;
        }
        for (int i = 0; i < this->aspect; i++){
            setCursor(x-i+this->aspect,y);
            cout << pixel;
        }
        return *this;
    }
    mcurses_kernel drawPoint(float x, float y, string bgColor, char backgroundd) {
        bgColor = getColor(bgColor, false);
        x *= 2;
        string pixel = string(bgColor);
        if (bgColor == "NONE") pixel = " ";
        else {
            pixel += backgroundd;
            pixel += DEFAULT;
        }
        for (int i = 0; i < this->aspect; i++){
            setCursor(x-i+this->aspect,y);
            cout << pixel;
        }
        return *this;
    }
    mcurses_kernel drawPoint(float x, float y, string color, string bgColor) {
        color = getColor(color, true);
        bgColor = getColor(bgColor, false);
        x *= 2;
        string pixel = string(color);
        pixel += string(bgColor);
        if (color == "NONE") pixel = " ";
        else {
            pixel += background;
            pixel += DEFAULT;
        }
        for (int i = 0; i < this->aspect; i++){
            setCursor(x-i+this->aspect,y);
            cout << pixel;
        }
        return *this;
    }
    mcurses_kernel drawPoint(float x, float y, string color, string bgColor, char backgroundd) {
        color = getColor(color, true);
        bgColor = getColor(bgColor, false);
        x *= 2;
        string pixel = string(color);
        pixel += string(bgColor);
        if (color == "NONE") pixel = " ";
        else {
            pixel += backgroundd;
            pixel += DEFAULT;
        }
        for (int i = 0; i < this->aspect; i++) {
            setCursor(x-i+this->aspect,y);
            cout << pixel;
        }
        return *this;
    }
    mcurses_kernel print(string text, float x, float y, string color, string bgColor) {
        y++;
        color = getColor(color, true);
        bgColor = getColor(bgColor, false);
        string toOut;
        toOut += color;
        toOut += bgColor;
        toOut += text;
        toOut += DEFAULT;
        setCursor(x*aspect+1, y);
        cout << toOut;
        return *this;
    }

    float getX(){return x;}
    float getY(){return y;}
    float getAspect(){return aspect;}
    float getCursorX(){return cursorX;}
    float getCursorY(){return cursorY;}
    char getBackground(){return background;}
    string getBackgroundColor(){return backgroundColor;}
    mcurses_kernel setX(const float x){this->x=x;return *this;}
    mcurses_kernel setY(const float y){this->y=y;return *this;}
    mcurses_kernel setAspect(const float aspect){this->aspect=aspect;return *this;}
    mcurses_kernel setBackground(const char background){this->background=background;return *this;}
    mcurses_kernel setBackgroundColor(const string backgroundColor){this->backgroundColor=backgroundColor;return *this;}

private:
    float x, y, aspect, cursorX, cursorY;
    char background;
    string backgroundColor;
    list <char> CFI; //Chars From Input
    /*string getPressedKeyOrCombination() {
        ADuration ad;
        ad.start();
        CFI.push_front(getch());
        int j = 0;
        for (char i: CFI) {
            //escapeTimer = false;
            ulong dur = ad.getDuration();
            ad.start();
            ad.start();
            //cout << "j = " << j << ", escapeTimer = " << escapeTimer << ", i = " << int(i) << "\n";
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
                        cout << "l = " << int(l) << ", k = " << int(k) << ", c1 = " << int(c1) << ", c2 = " << int(c2) << ", c3 = " << int(c3) << endl;
                        //t->restart();
                    }
                    for (int i = 0; i < INPUTBUFFER; i++)
                        CFI.push_front('\0');
                    return "To return1 >>> " +
                           (to_string(char(c1)) + ";" + to_string(char(c2)) + ";" + to_string(char(c3)));
                } else if (i != '\0') return "To return2 >>> " + to_string(CFI.front());
                else return string("\0");
            }
            if (j > 2) break;
            j++;
        }
        while (CFI.size() < INPUTBUFFER)
            CFI.pop_back();
    }*/
};
}

#endif