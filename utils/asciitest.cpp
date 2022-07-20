#include "mcurses_kernel.h"

int main(){
    mcurses::mcurses_kernel screen(20,20,1);
    int input;
    cout << "ASCIITEST, (c) mrybs, 2022\n"
           "Press any key, <Ctrl+C> to exit\n";
    while(1){
        input = screen.getch();
        if((input == 0) || (input == 0xe0)){
            input = screen.getch();
            cout << "Extended code ASCII:\t";
        }
        else cout << "Code ASCII:\t";
        cout << input << endl;
    }
}
