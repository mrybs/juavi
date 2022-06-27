#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
#include <clocale>
#include <csignal>
#include "termios.h"
using namespace std;

class mcurses {
public:
    const string FBLACK = "\033[0;30m";
    const string FRED = "\033[0;31m";
    const string FGREEN = "\033[1;32m";
    const string FYELLOW = "\033[1;33m";
    const string FBLUE = "\033[0;34m";
    const string FMAGENTA = "\033[1;35m";
    const string FCYAN = "\033[0;36m";
    const string FWHITE = "\033[0;37m";
    const string BBLACK = "\033[0;40m";
    const string BRED = "\033[0;41";
    const string BGREEN = "\033[1;42m";
    const string BYELLOW = "\033[1;43m";
    const string BBLUE = "\033[0;44m";
    const string BMAGENTA = "\033[1;45m";
    const string BCYAN = "\033[0;46m";
    const string BWHITE = "\033[0;47m";
    const string DEFAULT = "\033[0m";

    char escape = 27; //escape-1
    char up = 72; //arrow up-3
    char down = 80; //arrow down-3
    char left = 75; //arrow left-3
    char right = 77; //arrow right-3
    char pgup = 126; //page up-3
    char pgdn = 81; //page down-3
    char home = 71; //home-3
    char end = 79; //end-3
    char tab = '\t'; //tab-1
    char backspace = 8; //backspace-1

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
        }
        if (color == "NONE") return "NONE";
        return DEFAULT;
    }

    mcurses(float xd, float yd, float aspectd, char backgroundd) {
        x = xd;
        y = yd;
        aspect = aspectd;
        cursorX = 0;
        cursorY = 0;
        x *= aspect;
        background = backgroundd;
        cout << "\033[u";
        clear();
    }

    static void setLocale(int category, const char* locale) {setlocale(category, locale);}

    void parseKey(){
        int input = getch();
        input = getch();
        input = getch();
        if(input == escape) exitProgram(0, "escape pressed"); else
        if(input == up) moveCursorY(1); else
        if(input == down) moveCursorY(-1); else
        if(input == left) moveCursorX(-1); else
        if(input == right) moveCursorX(1); else
        if(input == home) setCursor(0, cursorY); else
        if(input == end) setCursor(x, cursorY);
    }

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

    void drawPoint(float xd, float yd, string color) {
        color = getColor(color, true);
        xd *= aspect;
        string pixel = string(color);
        if (color == "NONE") pixel = " ";
        else {
            pixel += background;
            pixel += string(DEFAULT);
        }
        for (int i = 0; i < aspect; i++) {
            setCursor(xd+i,yd);
            cout << pixel;
        }

    }

    void drawPoint(float xd, float yd, string color, char backgroundd) {
        color = getColor(color, true);
        xd *= 2;
        string pixel = string(color);
        if (color == "NONE") pixel = " ";
        else {
            pixel += backgroundd;
            pixel += string(DEFAULT);
        }
        for (int i = 0; i < aspect; i++){
            setCursor(xd+i,yd);
            cout << pixel;
        }
    }

    void drawPoint(float xd, float yd, string color, string bgColor) {
        color = getColor(color, true);
        xd *= 2;
        string pixel = string(color);
        pixel += string(bgColor);
        if (color == "NONE") pixel = " ";
        else {
            pixel += background;
            pixel += string(DEFAULT);
        }
        for (int i = 0; i < aspect; i++){
            setCursor(xd+i,yd);
            cout << pixel;
        }
    }

    void drawPoint(float xd, float yd, string color, string bgColor, char backgroundd) {
        color = getColor(color, true);
        bgColor = getColor(bgColor, false);
        xd *= 2;
        string pixel = string(color);
        pixel += string(bgColor);
        if (color == "NONE") pixel = " ";
        else {
            pixel += backgroundd;
            pixel += string(DEFAULT);
        }
        for (int i = 0; i < aspect; i++) {
            setCursor(xd+i,yd);
            cout << pixel;
        }
    }

    void drawRectangle(float xd, float yd, float width, float height, string color) {
        string pixel = string(color);
        for (int i = 0; i < int(yd + width); i++)
            if (i >= yd && i <= yd + width)
                for (int k = 0; k < int(xd + height); k += (aspect - 1))
                    if (k >= xd && k <= xd + height)
                        drawPoint(k, i, color);
    }

    void drawRectangle(float xd, float yd, float width, float height, string color, char backgroundd) {
        string pixel = string(color);
        for (int i = 0; i < int(yd + width); i++)
            if (i >= yd && i <= yd + width)
                for (int k = 0; k < int(xd + height); k += (aspect - 1))
                    if (k >= xd && k <= xd + height)
                        drawPoint(k, i, color, backgroundd);
    }

    void drawLine(float xd, float yd, float size, bool vertical, string color) {
        if (vertical) {
            for (int i = 0; i < int(yd + size); i++)
                if (i >= yd && i <= yd + size)
                    drawPoint(xd,i,color);
        } else {
            for (int k = 0; k < int(xd + size)-1; k += (aspect - 1))
                if (k >= xd && k <= xd + size)
                    drawPoint(k, yd, color);
        }
    }
    void drawLine(float xd, float yd, float size, bool vertical, string color, char backgroundd) {
        if (vertical)
            for (int i = 0; i < int(yd + size); i++)
                if (i >= yd && i <= yd + size) {
                    for (int j = 0; j < aspect; j++)
                        drawPoint(xd+j,i,color);
                }
                else {
                    for (int k = 0; k < int(xd + size); k += (aspect - 1))
                        if (k >= xd && k <= xd + size)
                            drawPoint(k, yd, color, backgroundd);
                }
        else {
            for (int k = 0; k < int(xd + size); k += (aspect - 1))
                if (k >= xd && k <= xd + size)
                    drawPoint(k, yd, color, backgroundd);
        }
    }
    void drawBorder(float xd, float yd, float width, float height, float size, string color) {
        while(size >= width || size >= height){size-=1;}
        drawLine(xd, yd, width, false, color);//x-up
        drawLine(xd, yd, width, true, color);//y-left
        drawLine(xd, yd + height, width, false, color);//x-down
        drawLine(xd + width-1, yd, width + 1, true, color);//y-right
        if(size != 1) drawBorder(xd+1,yd+1,width-2,height-2,size-1,color);
    }
    void drawBorder(float xd, float yd, float width, float height, float size, string color, char backgroundd) {
        while(size >= width || size >= height){size-=1;}
        drawLine(xd, yd, width, false, color, backgroundd);
        drawLine(xd, yd, width, true, color, backgroundd);
        drawLine(xd, yd + height, width, false, color, backgroundd);
        drawLine(xd + width, yd, width + 1, true, color, backgroundd);
    }
    void print(string text, float xd, float yd, string color, string bgColor, bool bold) {
        color = getColor(color, true);
        bgColor = getColor(bgColor, false);
        for (int i = 0; i < text.length(); i++) {
            drawPoint(xd+i,yd,color,bgColor,text[i]);
        }
    }

    void drawBackground(string color) {
        string pixel = string(color);
        if (color == "NONE") {
            pixel = " ";

        } else {
            pixel += background;
            pixel += string(DEFAULT);
        }
        for (int i = 0; i < int(y); i++) {
            for (int k = 0; k < int(x/aspect); k++)
                drawPoint(k, i, color);
        }
        backgroundColor = color;
    }
    void drawBackground(string color, char backgroundd) {
        for (int i = 0; i < int(y); i++) {
            for (int k = 0; k < int(x/aspect); k++)
                drawPoint(k, i, color, backgroundd);
        }
        backgroundColor = color;
    }

    private:
        float x, y, aspect, cursorX, cursorY;
        char background;
        string backgroundColor;

};