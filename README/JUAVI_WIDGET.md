# [Juavi Widget](https://github.com/mrybs/juavi/blob/main/juavi_widget.hpp)
### [This library is under GNU General Public Licence 3](https://github.com/mrybs/mcurses/blob/main/LICENSE)
## About
Library for creating your own widgets for Juavi Engine

## Connecting
To connect widgets, enter at the beginning of the code

`#include "path/to/widget.hpp"`

## Initializing
To initialize the widget just write

`juavi::juavi_kernel screen(x, y, aspect);`

`widgetName wn(x, y, aspect, &screen);`


To show widget write:

`wn.show(void);`


To render widget write:

`wn.render(void);`

To hide widget write:

`wn.hide(void);`


## Creating custom widget
To create a new module, create a file *.h and write the code in it as in the example
### Example
***
    #include "juavi_widget.hpp"

    #pragma once

    #ifndef JUAVI_CUSTOM_WIDGET_H
    #define JUAVI_CUSTOM_WIDGET_H

    namespace juavi{
      class juavi_custom_widget : public juavi::Ijuavi_widget{
      public:
          juavi::juavi_kernel* screen;//Object of main class
          
          //Constructors
          juavi_custom_widget(float x, float y, float aspect) : juavi_module(x, y, aspect){}
          juavi_custom_widget(float x, float y, float aspect, std::string background) : juavi_custom_widget(x, y, aspect){
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
