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

namespace mcurses{
class mcurses_kernel {
public:
    const string FBLACK = "\033[0;30m";//0
    const string FRED = "\033[0;31m";//1
    const string FGREEN = "\033[0;32m";//2
    const string FYELLOW = "\033[0;33m";//3
    const string FBLUE = "\033[0;34m";//4
    const string FMAGENTA = "\033[0;35m";//5
    const string FCYAN = "\033[0;36m";//6
    const string FGRAY = "\033[0;37m";//7
    const string FLRED = "\033[0;38m";//8
    const string FWHITE = "\033[0;39m";//9
    const string FLGREEN = "\033[0;92m";//10
    const string FLYELLOW = "\033[0;93m";//11
    const string FLBLUE = "\033[0;94m";//12
    const string FLMAGENTA = "\033[0;95m";//13
    const string FLCYAN = "\033[0;96m";//14
    const string FLGRAY = "\033[0;97m";//15
    const string FLWHITE = "\033[0;39m";//15

    const string BBLACK = "\033[0;40m";//0
    const string BRED = "\033[0;41m";//1
    const string BGREEN = "\033[0;42m";//2
    const string BYELLOW = "\033[0;43m";//3
    const string BBLUE = "\033[0;44m";//4
    const string BMAGENTA = "\033[0;45m";//5
    const string BCYAN = "\033[0;46m";//6
    const string BWHITE = "\033[0;47m";//7
    const string BGRAY = "\033[0;100m";//8
    const string BLGRAY = "\033[0;100m";//9
    const string BLRED = "\033[0;101m";//10
    const string BLGREEN = "\033[0;102m";//11
    const string BLYELLOW = "\033[0;103m";//12
    const string BLBLUE = "\033[0;104m";//13
    const string BLMAGENTA = "\033[0;105m";//14
    const string BLCYAN = "\033[0;106m";//15
    const string BLWHITE = "\033[0;107m";//16

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
            if (color == "LWHITE") return FLWHITE;
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
        cout << "\033[" + to_string(int(y)) + ";" + to_string(int(x)) + "f";
        cursorX = x;
        cursorY = y;
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
        y++;
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
        y++;
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
        y++;
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
        y++;
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
    float getX(){return x;}
    float getY(){return y;}
    float getAspect(){return aspect;}
    float getCursorX(){return cursorX;}
    float getCursorY(){return cursorY;}
    char getBackground(){return background;}
    string getBackgroundColor(){return backgroundColor;}
    void setBackgroundColor(string backgroundColor){this->backgroundColor=backgroundColor;}

private:
    float x, y, aspect, cursorX, cursorY;
    char background;
    string backgroundColor;

};
}

#endif