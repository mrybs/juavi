# [MCurses](https://github.com/mrybs/mcurses/blob/main/mcurses_kernel.h)
### [This library is under GNU General Public Licence 3](https://github.com/mrybs/mcurses/blob/main/LICENSE)
## About
Engine for creating applications in a terminal with a pseudographic interface in unicode
## Libraries are used:
`iostream`, `string`, `algorithm`, `cstdio`, `clocale`,
`csignal`, `cmath`, `vector`, `list`, `iterator`, `chrono`, `thread` and `termios`
## Including
Copy `mcurses.h` file into your project. Include it into your main file:

`#include "mcurses.h"`
## Constructors
`mcurses()`

`mcurses(float x, float y, float aspect)`
### Where
`int x` - screen size by x-axis

`int y` - screen size by y-axis

`int aspect` - font height/width ratio

`mcurses(float x, float y, float aspect, std::string background)`
### Where
`int x` - screen size by x-axis

`int y` - screen size by y-axis

`int aspect` - font height/width ratio

`std::string background` - background char
## Functions
`mcurses_kernel setLocale(int category, const char* locale)` - sets locale

`static char getch()` - gets char from input stream

`mcurses_kernel clear()` - clears the screen

`string getColor(std::string color, bool fg)` - translates the name
of a color into a sequence corresponding to that color for the
background or foreground

`mcurses_kernel setCursor(int x, int y)` - Moving the cursor to
the specified coordinates

`mcurses_kernel moveCursorX(int xd)` - x-axis cursor shift

`mcurses_kernel moveCursorY(int yd)` - y-axis cursor shift

`mcurses_kernel moveCursor(int xd, int yd)` - xy-axises cursor shift

`mcurses_kernel drawPoint(int x, int y, std::string color)` - draws a point on
the coordinates

`mcurses_kernel drawPoint(int x, int y, std::string color, std::string backgroundd)` -
draws a point on the specified coordinates with a custom background char

`mcurses_kernel drawPoint(int x, int y, std::string color, std::string bgColor)` -
draws a point on the specified coordinates with a custom background color

`mcurses_kernel drawPoint(int x, int y, std::string color, std::string bgColor, std::string backgroundd)` -
draws a point on the coordinates with custom background color and char

`mcurses_kernel print(std::string text, int x, int y, std::string color, std::string bgColor)` -
print a text on the specified coordinates

`mcurses_kernel drawVector(const int x,const int y,std::vector<std::vector<bool>>V,const std::string color,const std::string bgColor)` -
draws a bool 2D vector

`mcurses_kernel drawVector(const int x,const int y,std::vector<std::vector<bool>>V,const std::string color,const std::string bgColor,const std::string background)` -
draws a bool 2D vector with custom background

`void exitProgram(int result, const char* message)` - exits from program

### Constants
`const std::string DEFAULT` - default color
