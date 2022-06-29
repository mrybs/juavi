# [MCurses](https://github.com/mrybs/mcurses/blob/main/mcurses_kernel.h)
### [This library is under GNU General Public Licence 3](https://github.com/mrybs/mcurses/blob/main/LICENSE)
## About
Library for creating TUI and for console controlling in c++
## Libraries are used:
`iostream`, `string`, `algorithm`, `cstdio`, `clocale`,
`csignal`, `cmath` and `termios`
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

`string getColor(string color, bool fg)` - translates the name
of a color into a sequence corresponding to that color for the
background or foreground

`static void setCursor(float xd, float yd)` - Moving the cursor to
the specified coordinates

`static void moveCursorX(float xd)` - x-axis cursor shift

`static void moveCursorY(float xd)` - y-axis cursor shift

`static void moveCursor(float xd, float yd)` - xy-axises cursor shift

`void drawPoint(float xd, float yd, string color)` - draws a point on
the coordinates

`void drawPoint(float xd, float yd, string color, char backgroundd)` -
draws a point on the specified coordinates with a custom background char

`void drawPoint(float xd, float yd, string color, string bgColor)` -
draws a point on the specified coordinates with a custom background color

`void drawPoint(float xd, float yd, string color, string bgCo lor, char backgroundd)` -
draws a point on the coordinates with custom background color and char

`void print(string text, float xd, float yd, string color, string bgColor, bool bold)` -
print a text on the specified coordinates

`void drawLine(float xd, float yd, float size, bool vertical, string color)` -
draws a line

`void drawLine(float xd, float yd, float size, bool vertical, string color, char backgroundd)` -
draws a line with a custom background char

`void drawRectangle(float xd, float yd, float width, float height, string color)` -
draws a rectangle

`void drawRectangle(float xd, float yd, float width, float height, string color, char backgroundd)` -
draws a rectangle with a custom background char

`void drawBackground(string color)` - draws a background

`void drawBackground(string color, char backgroundd)` - draws a
background with a custom background char

`void drawBorder(float xd, float yd, float width, float height, float size, string color)` -
draws a border

`void drawBorder(float xd, float yd, float width, float height, float size, string color, char backgroundd)` -
draws a border with a custom background char

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
`const string FBLACK` - black color

`const string FRED` - red color

`const string FGREEN` - green color

`const string FYELLOW` - yellow color

`const string FBLUE` - blue color

`const string FMAGENTA` - magenta color

`const string FCYAN` - cyan color

`const string FCYAN` - gray color

`const string FWHITE` - white color

`const string FLRED` - light red color

`const string FLGREEN` - light green color

`const string FLYELLOW` - light yellow color

`const string FLBLUE` - light blue color

`const string FLMAGENTA` - light magenta color

`const string FLCYAN` - light cyan color

`const string FLGRAY` - light gray color
#### Background color
`const string BBLACK` - black color

`const string BRED` - red color

`const string BGREEN` - green color

`const string BYELLOW` - yellow color

`const string BBLUE` - blue color

`const string BMAGENTA` - magenta color

`const string BCYAN ` - cyan color

`const string BGRAY` - gray color

`const string BWHITE` - white color

`const string BLRED` - light red color

`const string BLGREEN` - light green color

`const string BLYELLOW` - light yellow color

`const string BLBLUE` - light blue color

`const string BLMAGENTA` - light magenta color

`const string BLCYAN` - light cyan color

`const string BLGRAY` - light gray color

`const string BLWHITE` - light whites color
#### Default color
`const string DEFAULT` - default color