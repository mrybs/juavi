# [MCurses Module](https://github.com/mrybs/mcurses/blob/main/mcurses_module.h)
### [This library is under GNU General Public Licence 3](https://github.com/mrybs/mcurses/blob/main/LICENSE)
## About
Library for creating custom widgets using mcurses in c++

## Connecting
To connect modules, enter at the beginning of the code

`#include "path/to/module.h"`

## Initializing
To initialize the module write

`mcurses_kernel screen(x, y, aspect);`

`moduleName mn(x, y, aspect);`

`mn.screen = screen;`

Or if yoou require a poiniter

`auto* screen = new mcurses_kernel(x, y, aspect);`

`auto* mn = new moduleName(x, y, aspect);`

`mn->screen = screen;`

To use any function from the module write something like this

`mn.helloWorld(void);`

or

`mn->helloWorld(void)`

## Creating custom module
To create a new module, create a file *.h and write the code in it as in the example
### Example
***
    #include "mcurses_module.h"
    #pragma once
    #ifndef MCURSES_EXAMPLE_MODULE_H
    #define MCURSES_EXAMPLE_MODULE_H
    using namespace std;
    using namespace mcurses;

    namespace mcurses{
      class mcurses_custom_module : public mcurses_module{
      public:
          mcurses_kernel* screen;//Object of main class
          
          //Constructors
          mcurses_backgrounds(float x, float y, float aspect) : mcurses_module(x, y, aspect){}
          mcurses_backgrounds(float x, float y, float aspect, char background) : mcurses_custom_module(x, y, aspect){}
          
          //Functions
          void helloWorld(void){
            screen->print("Hello, world!", 0, 0, "WHITE", "BLACK"); //Writes "Hello, world!" at x0 y0
            return void;
          }

      };
    }
    #endif
***

### Functions
`float getX()` - returnes the x coordinate

`float getY()` - returnes the y coordinate

`float getWidth()` - returnes the width

`float getHeight()` - returned the height

`string getDefaultColor()` - returnes the default color

`string getDefaultBackgroundColor()` - returnes the default background
color

`int setX(float x)` - sets the x coordinate

`int setY(float y)` - sets the y coordinate

`int setWidth(float width)` - sets the width

`int setHeight(float height)` - sets the height

`int setDefaultColor(string color)` - sets the default color

`int setDefaultBackgroundColor(string backgroundColor)` - sets the
default background color
