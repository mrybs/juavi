# [MCurses Widget](https://github.com/mrybs/mcurses/blob/main/mcurses_widget.h)
### [This library is under GNU General Public Licence 3](https://github.com/mrybs/mcurses/blob/main/LICENSE)
## About
Library for creating custom widgets using mcurses in c++

## Connecting
To connect widgets, enter at the beginning of the code

`#include "path/to/widget.h"`

## Initializing
To initialize the module write

`mcurses_kernel screen(x, y, aspect);`

`widgetName wn(x, y, aspect, screen);`


To use any function from the module write something like this

`wn.render(void);`


## Creating custom widget
To create a new module, create a file *.h and write the code in it as in the example
### Example
***
    #include "mcurses_widget.h"

    #pragma once

    #ifndef MCURSES_CUSTOM_WIDGET_H
    #define MCURSES_CUSTOM_WIDGET_H

    using namespace mcurses;

    namespace mcurses{
      class mcurses_custom_widget : public Imcurses_widget{
      public:
          mcurses_kernel* screen;//Object of main class
          
          //Constructors
          mcurses_backgrounds(float x, float y, float aspect) : mcurses_module(x, y, aspect){}
          mcurses_backgrounds(float x, float y, float aspect, std::string background) : mcurses_custom_module(x, y, aspect){
                screen->setBackground(background)
          }

          //Functions
          void render(void) override{
                screen->print("Hello, world!", 0, 0, "WHITE", "BLACK"); //Writes "Hello, world!" at x0 y0
                return void;
          }
          void show(void) override{
                isHided=0;
                return void;
          }
          void hide(void) override{
                isHided=2;
                return void;
          }

      };
    }
    #endif
***
