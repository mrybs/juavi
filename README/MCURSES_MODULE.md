# [MCurses Module](https://github.com/mrybs/mcurses/blob/main/mcurses_module.h)
### [This library is under GNU General Public Licence 3](https://github.com/mrybs/mcurses/blob/main/LICENSE)
## About
Engine for creating applications in a terminal with a pseudographic interface in unicode

## Connecting
To connect modules, enter at the beginning of the code

`#include "path/to/module.h"`

## Initializing
To initialize the module write

`mcurses_kernel screen(x, y, aspect);`

`moduleName mn(x, y, aspect, &screen);`

To use any function from the module write something like this

`mn.helloWorld(void);`

## Creating custom module
To create a new module, create a file *.h and write the code in it as in the example
### Example
***
    #include "mcurses_module.h"

    #pragma once

    #ifndef MCURSES_CUSTOM_MODULE_H
    #define MCURSES_CUSTOM_MODULE_H

    using namespace mcurses;

    namespace mcurses{
      class mcurses_custom_module : public mcurses_module{
      public:
          mcurses_kernel* screen;//Object of main class
          
          //Constructors
          mcurses_backgrounds(float x, float y, float aspect) : mcurses_module(x, y, aspect){}
          mcurses_backgrounds(float x, float y, float aspect, std::string background) : mcurses_custom_module(x, y, aspect){
            screen->setBackground(background)
          }
          
          //Functions
          void helloWorld(void){
            screen->print("Hello, world!", 0, 0, "WHITE", "BLACK"); //Writes "Hello, world!" at x0 y0
            return void;
          }

      };
    }
    #endif
***
