# [MCurses](https://github.com/mrybs/mcurses)
### [This library is under GNU General Public License 3](https://github.com/mrybs/mcurses/blob/main/LICENSE)
## About
Library for creating TUI and for console controlling in c++

## Depends

`iostream`, `string`, `algorithm`, `cstdio`, `clocale`, `csignal` and `termios`

## Including
Copy `mcurses.h` file into your project. Include it into your main file:

`#include "mcurses.h"`

## Constructor

`mcurses(float xd, float yd, float aspectd, char backgroundd)`

### Where

`float xd` - screen size by x-axis

`float yd` - screen size by y-axis

`float aspectd` - font height/width ratio

`char backgroundd` - background char


## Functions
`static void setLocale(int category, const char* locale)` - sets locale

`static char getch()` - gets char from input stream

`void parseKey()` - parsing pressed keys

`static void clear()` - clears the screen

`string getColor(string color, bool fg)` - translates the name of a color into a sequence corresponding to that color for the background or foreground

`static void setCursor(float xd, float yd)` - Moving the cursor to the specified coordinates

`static void moveCursorX(float xd)` - x-axis cursor shift

`static void moveCursorY(float xd)` - y-axis cursor shift

`static void moveCursor(float xd, float yd)` - xy-axises cursor shift

`void drawPoint(float xd, float yd, string color)` - draws a point on the coordinates

`void drawPoint(float xd, float yd, string color, char backgroundd)` - draws a point on the specified coordinates with a custom background char

`void drawPoint(float xd, float yd, string color, string bgColor)` - draws a point on the specified coordinates with a custom background color

`void drawPoint(float xd, float yd, string color, string bgColor, char backgroundd)` - draws a point on the coordinates with custom background color and char

`void print(string text, float xd, float yd, string color, string bgColor, bool bold)` - print a text on the specified coordinates

`void drawLine(float xd, float yd, float size, bool vertical, string color)` - draws a line

`void drawLine(float xd, float yd, float size, bool vertical, string color, char backgroundd)` - draws a line with a custom background char

`void drawRectangle(float xd, float yd, float width, float height, string color)` - draws a rectangle

`void drawRectangle(float xd, float yd, float width, float height, string color, char backgroundd)` - draws a rectangle with a custom background char

`void drawBackground(string color)` - draws a background

`void drawBackground(string color, char backgroundd)` - draws a background with a custom background char

`void drawBorder(float xd, float yd, float width, float height, float size, string color)` - draws a border

`void drawBorder(float xd, float yd, float width, float height, float size, string color, char backgroundd)` - draws a border with a custom background char

`void exitProgram(int result, const char* message)` - exits from program

## Variables
### Keys
`char escape = 27` - escape

`char up = 72` - arrow up

`char down = 80` - arrow down

`char left = 75` - arrow left

`char right = 77` - arrow right

`char pgup = 126` - page up

`char pgdn = 81` - page down

`char home = 71` - home

`char end = 79` - end

`char tab = '\t'` - tab

`char backspace = 8` - backspace

## Constants
### Colors
#### Foreground color
`const string FBLACK = "\033[0;30m"` -black

`const string FRED = "\033[0;31m"` - red

`const string FGREEN = "\033[1;32m"` - green

`const string FYELLOW = "\033[1;33m"` - yellow

`const string FBLUE = "\033[0;34m"` - blue

`const string FMAGENTA = "\033[1;35m"` - magenta

`const string FCYAN = "\033[0;36m"` - cyan

`const string FWHITE = "\033[0;37m"` - white

#### Background color
`const string BBLACK = "\033[0;40m"` - black

`const string BRED = "\033[0;41"` - red

`const string BGREEN = "\033[1;42m"` - green

`const string BYELLOW = "\033[1;43m"` - yellow

`const string BBLUE = "\033[0;44m"` - blue

`const string BMAGENTA = "\033[1;45m"` - magenta

`const string BCYAN = "\033[0;46m"` - cyan

`const string BWHITE = "\033[0;47m"` - white

#### Default color
`const string DEFAULT = "\033[0m"`

# ASCIITEST
### [This c++ code is under GNU General Public License 3](https://github.com/mrybs/mcurses/blob/main/LICENSE)
## About
This program is based on the mcurses library. It outputs the character number entered by the user.

## Compilation
I use the gcc compiler. Just enter:

`gcc -lstdc++ asciitest.cpp -o asciitest`

In the mcurses folder

## Launch
To start, you need to enter

`./asciitest`
