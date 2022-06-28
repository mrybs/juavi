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
    const string FGREEN = "\033[0;32m";
    const string FYELLOW = "\033[0;33m";
    const string FBLUE = "\033[0;34m";
    const string FMAGENTA = "\033[1;35m";
    const string FCYAN = "\033[0;36m";
    const string FGRAY = "\033[0;37m";
    const string FLRED = "\033[0;38m";
    const string FWHITE = "\033[0;39m";
    const string FLGREEN = "\033[0;92m";
    const string FLYELLOW = "\033[0;93m";
    const string FLBLUE = "\033[0;94m";
    const string FLMAGENTA = "\033[1;95m";
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
    const string BLRED = "\033[0;101m";
    const string BLGREEN = "\033[0;102m";
    const string BLYELLOW = "\033[0;103m";
    const string BLBLUE = "\033[0;104m";
    const string BLMAGENTA = "\033[0;105m";
    const string BLCYAN = "\033[0;106m";
    const string BLGRAY = "\033[0;100m";
    const string BLWHITE = "\033[0;107m";
    const string DEFAULT = "\033[0m";

    char escape = 27; //escape-1
    char up[3] = {27,91,65}; //arrow up-3
    char down[3] = {27,91,66}; //arrow down-3
    char left[3] = {27,91,68}; //arrow left-3
    char right[3] = {27,91,67}; //arrow right-3
    char pgup[4] = {27,91,53,126}; //page up-3
    char pgdn[4] = {27,91,54,126}; //page down-3
    char home[3] = {27,91,72}; //home-3
    char end[3] = {27,91,70}; //end-3
    char tab = {'\t'}; //tab-1
    char backspace = 8; //backspace-1

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
        if (color == "NONE") return "NONE";
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

    void drawPoint(float xd, float yd, string bgColor) {
        bgColor = getColor(bgColor, false);
        xd *= 2;
        string pixel = string(bgColor);
        if (bgColor == "NONE") pixel = " ";
        else {
            pixel += background;
            pixel += string(DEFAULT);
        }
        for (int i = 0; i < aspect; i++){
            setCursor(xd-i+aspect,yd);
            cout << pixel;
        }
    }

    void drawPoint(float xd, float yd, string bgColor, char backgroundd) {
        bgColor = getColor(bgColor, false);
        xd *= 2;
        string pixel = string(bgColor);
        if (bgColor == "NONE") pixel = " ";
        else {
            pixel += backgroundd;
            pixel += string(DEFAULT);
        }
        for (int i = 0; i < aspect; i++){
            setCursor(xd-i+aspect,yd);
            cout << pixel;
        }
    }

    void drawPoint(float xd, float yd, string color, string bgColor) {
        color = getColor(color, true);
        bgColor = getColor(bgColor, false);
        xd *= 2;
        string pixel = string(color);
        pixel += string(bgColor);
        if (color == "NONE") pixel = " ";
        else {
            pixel += background;
            pixel += string(DEFAULT);
        }
        for (int i = 0; i < aspect; i++){
            setCursor(xd-i+aspect,yd);
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
            setCursor(xd-i+aspect,yd);
            cout << pixel;
        }
    }

    void drawRectangle(float xd, float yd, float width, float height, string bgColor) {
        string pixel = string(bgColor);
        for (int i = 0; i < int(yd + width); i++)
            if (i >= yd && i <= yd + width)
                for (int k = 0; k < int(xd + height); k += (aspect - 1))
                    if (k >= xd && k <= xd + height)
                        drawPoint(k, i, bgColor);
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
        for (int i = 0; i < int(y); i++) {
            for (int k = 0; k < int(x/aspect); k++)
                drawPoint(k, i, color, color);
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
        char ch, k;

};