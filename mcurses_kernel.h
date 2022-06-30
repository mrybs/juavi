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

#pragma once
#ifndef MCURSES_H
#define MCURSES_H
#define COLOR_MAX_ID 16
#define COLOR1PART string("\033[0;")
#define COLOR2PART "m"

namespace mcurses{
class mcurses_kernel {
public:
    const string FBLACK = "30";//0
    const string FRED = "31";//1
    const string FGREEN = "32";//2
    const string FYELLOW = "33";//3
    const string FBLUE = "34";//4
    const string FMAGENTA = "35";//5
    const string FCYAN = "36";//6
    const string FGRAY = "37";//7
    const string FLRED = "38";//8
    const string FWHITE = "39";//9
    const string FLGREEN = "92";//10
    const string FLYELLOW = "93";//11
    const string FLBLUE = "94";//12
    const string FLMAGENTA = "95";//13
    const string FLCYAN = "96";//14
    const string FLGRAY = "97";//15
    const string FLWHITE = "39";//15

    const string BBLACK = "40";//0
    const string BRED = "41";//1
    const string BGREEN = "42";//2
    const string BYELLOW = "43";//3
    const string BBLUE = "44";//4
    const string BMAGENTA = "45";//5
    const string BCYAN = "46";//6
    const string BWHITE = "47";//7
    const string BGRAY = "100";//8
    const string BLGRAY = "100";//9
    const string BLRED = "101";//10
    const string BLGREEN = "102";//11
    const string BLYELLOW = "103";//12
    const string BLBLUE = "104";//13
    const string BLMAGENTA = "105";//14
    const string BLCYAN = "106";//15
    const string BLWHITE = "107";//16

    const string DEFAULT = "\033[0m";

    mcurses_kernel(){
        x = 1;
        y = 1;
        aspect = 1;
        cursorX = 0;
        cursorY = 0;
        background = ' ';
    }
    mcurses_kernel(float x, float y, float aspect) {
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
    mcurses_kernel(float x, float y, float aspect, char background) : mcurses_kernel(x, y, aspect){
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
            if (color == "BLACK") return COLOR1PART + FBLACK + COLOR2PART;
            if (color == "RED") return COLOR1PART + FRED + COLOR2PART;
            if (color == "GREEN") return COLOR1PART + FGREEN + COLOR2PART;
            if (color == "YELLOW") return COLOR1PART + FYELLOW + COLOR2PART;
            if (color == "BLUE") return COLOR1PART + FBLUE + COLOR2PART;
            if (color == "CYAN") return COLOR1PART + FCYAN + COLOR2PART;
            if (color == "MAGENTA") return COLOR1PART + FMAGENTA + COLOR2PART;
            if (color == "WHITE") return COLOR1PART + FWHITE + COLOR2PART;
            if (color == "GRAY") return COLOR1PART + FGRAY + COLOR2PART;
            if (color == "LRED") return COLOR1PART + FLRED + COLOR2PART;
            if (color == "LGREEN") return COLOR1PART + FLGREEN + COLOR2PART;
            if (color == "LYELLOW") return COLOR1PART + FLYELLOW + COLOR2PART;
            if (color == "LBLUE") return COLOR1PART + FLBLUE + COLOR2PART;
            if (color == "LCYAN") return COLOR1PART + FLCYAN + COLOR2PART;
            if (color == "LMAGENTA") return COLOR1PART + FLMAGENTA + COLOR2PART;
            if (color == "LGRAY") return COLOR1PART + FLGRAY + COLOR2PART;
            if (color == "LWHITE") return COLOR1PART + FLWHITE + COLOR2PART;
        }
        else{
            if (color == "BLACK") return COLOR1PART + BBLACK + COLOR2PART;
            if (color == "RED") return COLOR1PART + BRED + COLOR2PART;
            if (color == "GREEN") return COLOR1PART + BGREEN + COLOR2PART;
            if (color == "YELLOW") return COLOR1PART + BYELLOW + COLOR2PART;
            if (color == "BLUE") return COLOR1PART + BBLUE + COLOR2PART;
            if (color == "CYAN") return COLOR1PART + BCYAN + COLOR2PART;
            if (color == "MAGENTA") return COLOR1PART + BMAGENTA + COLOR2PART;
            if (color == "WHITE") return COLOR1PART + BWHITE + COLOR2PART;
            if (color == "GRAY") return COLOR1PART + BGRAY + COLOR2PART;
            if (color == "LRED") return COLOR1PART + BLRED + COLOR2PART;
            if (color == "LGREEN") return COLOR1PART + BLGREEN + COLOR2PART;
            if (color == "LYELLOW") return COLOR1PART + BLYELLOW + COLOR2PART;
            if (color == "LBLUE") return COLOR1PART + BLBLUE + COLOR2PART;
            if (color == "LCYAN") return COLOR1PART + BLCYAN + COLOR2PART;
            if (color == "LMAGENTA") return COLOR1PART + BLMAGENTA + COLOR2PART;
            if (color == "LWHITE") return COLOR1PART + BLWHITE + COLOR2PART;
            if (color == "LGRAY") return COLOR1PART + BLGRAY + COLOR2PART;
        }
        if (color == "NONE") return "";
        return DEFAULT;
    }
    string getColorName(int id){
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
    static void setLocale(int category, const char* locale) {setlocale(category, locale);}
    void exitProgram(int result, const char* message){
        setCursor(0,y);
        cout << "Exit message: " << message << endl;
        exit(result);
    }
    void setCursor(float x, float y){
        y++;
        cout << "\033[" + to_string(int(y)) + ";" + to_string(int(x)) + "f";
        cursorX = x;
        cursorY = y;
    }
    void moveCursorX(float x){
        if(x > 0) cout << "\033[" + to_string(int(x)) << "C";
        else if(x < 0) cout << "\033[" + to_string(int(x)) << "D";
        cursorX += x;
    }
    void moveCursorY(float y){
        y++;
        if(y > 0) cout << "\033[" + to_string(int(y)) << "A";
        else if(y < 0) cout << "\033[" + to_string(int(y)) << "B";
        cursorY += y;
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
    void print(string text, float x, float y, string color, string bgColor) {
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
    }

    float getX(){return x;}
    float getY(){return y;}
    float getAspect(){return aspect;}
    float getCursorX(){return cursorX;}
    float getCursorY(){return cursorY;}
    char getBackground(){return background;}
    void setBackground(char background){this->background=background;}
    string getBackgroundColor(){return backgroundColor;}
    void setBackgroundColor(string backgroundColor){this->backgroundColor=backgroundColor;}

private:
    float x, y, aspect, cursorX, cursorY;
    char background;
    string backgroundColor;

};
}

#endif