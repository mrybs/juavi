# [Juavi](https://github.com/mrybs/juavi/blob/main/juavi_kernel.hpp)
### [This library is under GNU General Public Licence 3](https://github.com/mrybs/juavi/blob/main/LICENSE)
## About
Engine for creating applications in a terminal with a pseudographic interface in unicode
## Libraries are used:
`iostream`, `string`, `algorithm`, `cstdio`, `clocale`,
`csignal`, `cmath`, `vector`, `list`, `iterator`, `chrono`, `thread` and `termios`
## Including
Copy `juavi_kernel.hpp` file into your project. Include it into your main file:

`#include "juavi_kernel.hpp"`
## Constructors
`juavi_kernel()`

`juavi_kernel(float x, float y, float aspect)`

### Where
`int x` - screen size by x-axis

`int y` - screen size by y-axis

`int aspect` - font height/width ratio

`juavi_kernel(float x, float y, float aspect, std::string background)`
### Where
`int x` - screen size by x-axis

`int y` - screen size by y-axis

`int aspect` - font height/width ratio

`std::string background` - background char
## Functions
`juavi_kernel setLocale(int category, const char* locale)` - sets locale

`struct RGB hexToRGB(const char* hexValue)` - convert HEX(#RRGGBB) into RGB(R,G,B)

`static char getch()` - gets char from input stream

`juavi_kernel* clear()` - clears the screen

`string getColor(std::string color, bool fg)` - translates the name
of a color into a sequence corresponding to that color for the
background or foreground

`juavi_kernel* setCursor(int x, int y)` - Moving the cursor to
the specified coordinates

`juavi_kernel* moveCursorX(int xd)` - x-axis cursor shift

`juavi_kernel* moveCursorY(int yd)` - y-axis cursor shift

`juavi_kernel* moveCursor(int xd, int yd)` - xy-axises cursor shift

`juavi_kernel* drawPoint(int x, int y, std::string color)` - draws a point on
the coordinates

`juavi_kernel* drawPoint(int x, int y, std::string color, std::string backgroundd)` -
draws a point on the specified coordinates with a custom background char

`juavi_kernel* drawPoint(int x, int y, std::string color, std::string bgColor)` -
draws a point on the specified coordinates with a custom background color

`juavi_kernel* drawPoint(int x, int y, std::string color, std::string bgColor, std::string backgroundd)` -
draws a point on the coordinates with custom background color and char

`juavi_kernel* print(std::string text, std::string color, std::string bgColor)` -
prints a colored text

`juavi_kernel* print(std::string text, int x, int y, std::string color, std::string bgColor)` -
prints a colored text on the specified coordinates

`juavi_kernel* drawVector(const int x, const int y,std::vector<std::vector<bool>>V,const std::string color, const std::string bgColor)` -
draws a bool 2D vector

`juavi_kernel* drawVector(const int x, const int y, std::vector<std::vector<bool>>V,const std::string color, const std::string bgColor, const std::string background)` -
draws a bool 2D vector with custom background

`juavi_kernel* drawJuaviLogo(const int x, const int y)` - draws a Juavi logo

`void exitProgram(int result, const char* message)` - exits from program

### Constants
`const std::string DEFAULT` - default color
