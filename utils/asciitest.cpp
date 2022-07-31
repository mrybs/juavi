///
/// Developed by mrybs
///
#include "mcurses_kernel.h"

int main(){
    mcurses::mcurses_kernel screen(20,20,1);
    int input;
    std::cout << "ASCIITEST, (c) mrybs, 2022\n"
           "Press any key, <Ctrl+C> to exit\n";
    while(1){
        input = screen.getch();
        if((input == 0) || (input == 0xe0)){
            input = screen.getch();
            std::cout << "Extended code ASCII:\t";
        }
        else std::cout << "Code ASCII:\t";
        std::cout << input << "\n";
    }
}
