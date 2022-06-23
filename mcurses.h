#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

#define CLEAR "clear"

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
        x *= aspect;
        background = backgroundd;
        screen.resize(y);
        for (int i = 0; i < int(y); i++)
            screen[i].resize(int(x));
    }

    void updateScreen() {
        system(CLEAR);
        for (int i = 0; i < int(y); i++) {
            for (int k = 0; k < int(x); k++)
                cout << screen[i][k];
            cout << endl;
        }
    }

    void drawPoint(float xd, float yd, string color) {
        color = getColor(color, true);
        xd *= aspect;
        string pixel = string(color);
        if (color == "NONE") {
            pixel = " ";
        } else {
            pixel += background;
            pixel += string(DEFAULT);
        }
        for (int i = 0; i < aspect; i++)
            screen[yd][xd + i] = pixel;
    }

    void drawPoint(float xd, float yd, string color, char backgroundd) {
        color = getColor(color, true);
        xd *= 2;
        string pixel = string(color);
        if (color == "NONE") {
            pixel = " ";
        } else {
            pixel += backgroundd;
            pixel += string(DEFAULT);
        }
        for (int i = 0; i < aspect; i++)
            screen[yd][xd + i] = pixel;
    }

    void drawPoint(float xd, float yd, string color, string bgColor) {
        color = getColor(color, true);
        xd *= 2;
        string pixel = string(color);
        pixel += string(bgColor);
        if (color == "NONE") {
            pixel = " ";
        } else {
            pixel += background;
            pixel += string(DEFAULT);
        }
        for (int i = 0; i < aspect; i++)
            screen[yd][xd + i] = pixel;
    }

    void drawPoint(float xd, float yd, string color, string bgColor, char backgroundd) {
        color = getColor(color, true);
        bgColor = getColor(bgColor, false);
        xd *= 2;
        string pixel = string(color);
        pixel += string(bgColor);
        if (color == "NONE") {
            pixel = " ";
        } else {
            pixel += backgroundd;
            pixel += string(DEFAULT);
        }
        for (int i = 0; i < aspect; i++)
            screen[yd][xd + i] = pixel;
    }

    void drawRectangle(float xd, float yd, float width, float height, string color) {
        height *= 2;
        xd *= 2;
        string pixel = string(color);
        for (int i = 0; i < int(yd + width); i++)
            if (i >= yd && i <= yd + width)
                for (int k = 0; k < int(xd + height); k += (aspect - 1))
                    if (k >= xd && k <= xd + height)
                        drawPoint(k, i, color);
    }

    void drawRectangle(float xd, float yd, float width, float height, string color, char backgroundd) {
        height *= 2;
        xd *= 2;
        string pixel = string(color);
        for (int i = 0; i < int(yd + width); i++)
            if (i >= yd && i <= yd + width)
                for (int k = 0; k < int(xd + height); k += (aspect - 1))
                    if (k >= xd && k <= xd + height)
                        drawPoint(k, i, color, backgroundd);
    }

    void drawLine(float xd, float yd, float size, bool vertical, string color) {
        xd *= 2;
        string pixel = string(color);
        if (color == "NONE") {
            pixel = " ";
        } else {
            pixel += background;
            pixel += string(DEFAULT);
        }
        if (vertical) {
            for (int i = 0; i < int(yd + size); i++)
                if (i >= yd && i <= yd + size)
                    for (int j = 0; j < aspect; j++)
                        drawPoint(xd+j,i,color);
        } else {
            size *= 2;
            for (int k = 0; k < int(xd + size); k += (aspect - 1))
                if (k >= xd && k <= xd + size)
                    drawPoint(k, yd, color);
        }
    }
    void drawLine(float xd, float yd, float size, bool vertical, string color, char backgroundd) {
        xd *= 2;
        if (vertical)
            for (int i = 0; i < int(yd + size); i++)
                if (i >= yd && i <= yd + size) {
                    for (int j = 0; j < aspect; j++)
                        drawPoint(xd+j,i,color);
                }
                else {
                    size *= 2;
                    for (int k = 0; k < int(xd + size); k += (aspect - 1))
                        if (k >= xd && k <= xd + size)
                            drawPoint(k, yd, color, backgroundd);
                }
    }
    void drawBorder(float xd, float yd, float width, float height, float size, string color) {
        drawLine(xd, yd, width, false, color);
        drawLine(xd, yd, width, true, color);
        drawLine(xd, yd + height, width, false, color);
        drawLine(xd + width, yd, width + 1, true, color);
    }
    void drawBorder(float xd, float yd, float width, float height, float size, string color, char backgroundd) {
        drawLine(xd, yd, width, false, color, backgroundd);
        drawLine(xd, yd, width, true, color, backgroundd);
        drawLine(xd, yd + height, width, false, color, backgroundd);
        drawLine(xd + width, yd, width + 1, true, color, backgroundd);
    }
    void print(string text, float xd, float yd, string color, string bgColor, bool bold) {
        color = getColor(color, true);
        bgColor = getColor(bgColor, false);
        for (int i = 0; i < text.length(); i++) {
            string pixel = color + bgColor + text[i] + DEFAULT;
            screen[yd][xd + i] = pixel;
            //drawPoint(xd + i, yd, color, bgColor,text[i]);
        }
    }
    void print(string text, float xd, float yd, string color, string bgColor, bool bold, char backgroundd) {
        bgColor = getColor(bgColor, false);
        for (int i = 0; i < text.length(); i++) {
            string pixel = color + bgColor + text[i] + DEFAULT;
            screen[yd][xd + i] = pixel;
            drawPoint(xd + i, yd, color, bgColor, backgroundd);
        }
    }

    void drawBackground(string color) {
        color = getColor(color, true);
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
        float x, y, aspect;
        char background;
        string backgroundColor;
        vector<vector<string>> screen;


};