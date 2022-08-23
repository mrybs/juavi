# [Juavi Module](https://github.com/mrybs/juavi/blob/main/juavi_module.hpp)
### [This library is under GNU General Public Licence 3](https://github.com/mrybs/juavi/blob/main/LICENSE)
## About
Library for creating your own modules for Juavi Engine

## Connecting
To connect modules, enter at the beginning of the code

`#include "path/to/module.hpp"`

## Initializing
To initialize the module write

`juavi::juavi_kernel screen(x, y, aspect);`

`moduleName mn(x, y, aspect, &screen);`

To use any function from the module write something like this

`mn.helloWorld(void);`

## Creating custom module
To create a new module, create a file *.hpp and write the code in it as in the example
### Example
***
    #include "juavi_module.hpp"

    #pragma once

    #ifndef JUAVI_CUSTOM_MODULE_H
    #define JUAVI_CUSTOM_MODULE_H

    namespace juavi{
      class juavi_custom_module : public juavi::juavi_module{
      public:
          juavi::juavi_kernel* screen;//Object of main class
          
          //Constructors
          juavi_custom_module(float x, float y, float aspect) : juavi::juavi_module(x, y, aspect){}
          juavi_custom_module(float x, float y, float aspect, std::string background) : juavi_custom_module(x, y, aspect){
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
